/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Interop.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::interop {

/// represents persistent state to be allocated
/// The `interop.procedural.alloc` operation returns a variadic list of values
/// that represent persistent state, i.e., state that has to persist across
/// multiple executions of the `interop.procedural.update` operation.
/// For example, it can be lowered to C++ class fields that are persistent
/// across multiple calls of a member function, or to global simulator state
/// that persists over simulation cycles, etc.
/// 
/// Additionally, it has an attribute that specifies the interop mechanism under
/// which the state types are valid. This is necessary to allow bridging patterns
/// to map the types to valid types in the other interop mechanism, e.g., to an
/// opaque pointer, if it does not support the same types.
class ProceduralAllocOp;

} // namespace circt::interop
namespace circt::interop {

/// performs some deallocation logic before the state is released
/// The `interop.procedural.dealloc` operation shall be executed right before
/// the state requested by the `interop.procedural.alloc` operation is
/// released. This allows the instance to do some cleanup, e.g., when the state
/// type was a pointer and the instance performed some `malloc`.
/// 
/// Structurally the operation is the same as the `interop.procedural.update`
/// operation, but without input and output values. The state is also passed
/// by value.
class ProceduralDeallocOp;

} // namespace circt::interop
namespace circt::interop {

/// computes the initial values for the allocated state
/// The `interop.procedural.init` operation takes the variadic list of states
/// from the `interop.procedural.alloc` operation as operands and has a body
/// with a `interop.return` operation that has a variadic list of operands that
/// matches the types of the states and represent the initial values to be
/// assigned to the state values.
/// The assignment will be inserted by the container-side lowering of the
/// interop operations.
/// The operation also has an interop mechanism attribute to allow bridging
/// patterns to map the types to valid types in another interop mechanism
/// and to wrap the operations in the body in a way to make them executable
/// in the other interop mechanism, e.g., wrap them in a `extern "C"` function
/// to make it callable from C or LLVM IR.
class ProceduralInitOp;

} // namespace circt::interop
namespace circt::interop {

/// takes some persistent state and inputs to compute some results
/// The `interop.procedural.update` operation has an interop mechanism attribute
/// to allow bridging patterns to map the types to valid types in another
/// interop mechanism and to wrap the operations in the body in a way to make
/// them executable using the other interop mechanism.
/// 
/// It takes the state values returned by the `interop.procedural.alloc`as
/// operands and passes them on to the body via block arguments using
/// pass-by-value semantics. In addition to the state values, it also takes a
/// variadic list of inputs and also passes them on to the body.
/// The `interop.return` inside the body then returns the result values after
/// doing some computation inside the body.
/// 
/// If the state needs to be mutated, it has to be a pointer type.
class ProceduralUpdateOp;

} // namespace circt::interop
namespace circt::interop {

/// a return operation
/// The `interop.return` operation lists the computed initial values when
/// inside the `init` operation or the computed results when inside the
/// `update` operation.
class ReturnOp;

} // namespace circt::interop
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralAllocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProceduralAllocOpGenericAdaptorBase {
public:
  struct Properties {
    using interopMechanismTy = ::InteropMechanismAttr;
    interopMechanismTy interopMechanism;

    auto getInteropMechanism() const {
      auto &propStorage = this->interopMechanism;
      return ::llvm::cast<::InteropMechanismAttr>(propStorage);
    }
    void setInteropMechanism(const ::InteropMechanismAttr &propValue) {
      this->interopMechanism = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.interopMechanism == this->interopMechanism &&
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
  ProceduralAllocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("interop.procedural.alloc", odsAttrs.getContext());
  }

  ProceduralAllocOpGenericAdaptorBase(ProceduralAllocOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::InteropMechanismAttr getInteropMechanismAttr() {
    auto attr = ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
    return attr;
  }

  ::InteropMechanism getInteropMechanism();
};

} // namespace detail
template <typename RangeT>
class ProceduralAllocOpGenericAdaptor : public detail::ProceduralAllocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProceduralAllocOpGenericAdaptorBase;
public:
  ProceduralAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProceduralAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ProceduralAllocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProceduralAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ProceduralAllocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProceduralAllocOpGenericAdaptor(RangeT values, const ProceduralAllocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProceduralAllocOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProceduralAllocOp>>>
  ProceduralAllocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ProceduralAllocOpAdaptor : public ProceduralAllocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProceduralAllocOpGenericAdaptor::ProceduralAllocOpGenericAdaptor;
  ProceduralAllocOpAdaptor(ProceduralAllocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProceduralAllocOp : public ::mlir::Op<ProceduralAllocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProceduralAllocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProceduralAllocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("interopMechanism")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInteropMechanismAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInteropMechanismAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("interop.procedural.alloc");
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

  ::mlir::Operation::result_range getStates() {
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
  ::InteropMechanismAttr getInteropMechanismAttr() {
    return ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
  }

  ::InteropMechanism getInteropMechanism();
  void setInteropMechanismAttr(::InteropMechanismAttr attr) {
    getProperties().interopMechanism = attr;
  }

  void setInteropMechanism(::InteropMechanism attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism);
  static ProceduralAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism);
  static ProceduralAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange states, ::InteropMechanism interopMechanism);
  static ProceduralAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange states, ::InteropMechanism interopMechanism);
  static ProceduralAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange states, ::InteropMechanism interopMechanism);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProceduralAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ProceduralAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProceduralAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ProceduralAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralAllocOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralAllocOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralDeallocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProceduralDeallocOpGenericAdaptorBase {
public:
  struct Properties {
    using interopMechanismTy = ::InteropMechanismAttr;
    interopMechanismTy interopMechanism;

    auto getInteropMechanism() const {
      auto &propStorage = this->interopMechanism;
      return ::llvm::cast<::InteropMechanismAttr>(propStorage);
    }
    void setInteropMechanism(const ::InteropMechanismAttr &propValue) {
      this->interopMechanism = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.interopMechanism == this->interopMechanism &&
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
  ProceduralDeallocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("interop.procedural.dealloc", odsAttrs.getContext());
  }

  ProceduralDeallocOpGenericAdaptorBase(ProceduralDeallocOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::InteropMechanismAttr getInteropMechanismAttr() {
    auto attr = ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
    return attr;
  }

  ::InteropMechanism getInteropMechanism();
  ::mlir::Region &getDeallocRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ProceduralDeallocOpGenericAdaptor : public detail::ProceduralDeallocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProceduralDeallocOpGenericAdaptorBase;
  static constexpr int odsIndex_states = 0;
public:
  ProceduralDeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProceduralDeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ProceduralDeallocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProceduralDeallocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ProceduralDeallocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProceduralDeallocOpGenericAdaptor(RangeT values, const ProceduralDeallocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProceduralDeallocOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProceduralDeallocOp>>>
  ProceduralDeallocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getStates() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ProceduralDeallocOpAdaptor : public ProceduralDeallocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProceduralDeallocOpGenericAdaptor::ProceduralDeallocOpGenericAdaptor;
  ProceduralDeallocOpAdaptor(ProceduralDeallocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProceduralDeallocOp : public ::mlir::Op<ProceduralDeallocOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProceduralDeallocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProceduralDeallocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_states = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("interopMechanism")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInteropMechanismAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInteropMechanismAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("interop.procedural.dealloc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getStates() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getStatesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getDeallocRegion() {
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
  ::InteropMechanismAttr getInteropMechanismAttr() {
    return ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
  }

  ::InteropMechanism getInteropMechanism();
  void setInteropMechanismAttr(::InteropMechanismAttr attr) {
    getProperties().interopMechanism = attr;
  }

  void setInteropMechanism(::InteropMechanism attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralDeallocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralDeallocOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange states, InteropMechanism interopMechanism);
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
};

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralDeallocOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralDeallocOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralInitOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProceduralInitOpGenericAdaptorBase {
public:
  struct Properties {
    using interopMechanismTy = ::InteropMechanismAttr;
    interopMechanismTy interopMechanism;

    auto getInteropMechanism() const {
      auto &propStorage = this->interopMechanism;
      return ::llvm::cast<::InteropMechanismAttr>(propStorage);
    }
    void setInteropMechanism(const ::InteropMechanismAttr &propValue) {
      this->interopMechanism = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.interopMechanism == this->interopMechanism &&
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
  ProceduralInitOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("interop.procedural.init", odsAttrs.getContext());
  }

  ProceduralInitOpGenericAdaptorBase(ProceduralInitOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::InteropMechanismAttr getInteropMechanismAttr() {
    auto attr = ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
    return attr;
  }

  ::InteropMechanism getInteropMechanism();
  ::mlir::Region &getInitRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ProceduralInitOpGenericAdaptor : public detail::ProceduralInitOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProceduralInitOpGenericAdaptorBase;
  static constexpr int odsIndex_states = 0;
public:
  ProceduralInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProceduralInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ProceduralInitOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProceduralInitOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ProceduralInitOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProceduralInitOpGenericAdaptor(RangeT values, const ProceduralInitOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProceduralInitOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProceduralInitOp>>>
  ProceduralInitOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getStates() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ProceduralInitOpAdaptor : public ProceduralInitOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProceduralInitOpGenericAdaptor::ProceduralInitOpGenericAdaptor;
  ProceduralInitOpAdaptor(ProceduralInitOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProceduralInitOp : public ::mlir::Op<ProceduralInitOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProceduralInitOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProceduralInitOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_states = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("interopMechanism")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInteropMechanismAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInteropMechanismAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("interop.procedural.init");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getStates() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getStatesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getInitRegion() {
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
  ::InteropMechanismAttr getInteropMechanismAttr() {
    return ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
  }

  ::InteropMechanism getInteropMechanism();
  void setInteropMechanismAttr(::InteropMechanismAttr attr) {
    getProperties().interopMechanism = attr;
  }

  void setInteropMechanism(::InteropMechanism attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralInitOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralInitOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange states, InteropMechanism interopMechanism);
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
};

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralInitOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralInitOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralUpdateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ProceduralUpdateOpGenericAdaptorBase {
public:
  struct Properties {
    using interopMechanismTy = ::InteropMechanismAttr;
    interopMechanismTy interopMechanism;

    auto getInteropMechanism() const {
      auto &propStorage = this->interopMechanism;
      return ::llvm::cast<::InteropMechanismAttr>(propStorage);
    }
    void setInteropMechanism(const ::InteropMechanismAttr &propValue) {
      this->interopMechanism = propValue;
    }
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
        rhs.interopMechanism == this->interopMechanism &&
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
  ProceduralUpdateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("interop.procedural.update", odsAttrs.getContext());
  }

  ProceduralUpdateOpGenericAdaptorBase(ProceduralUpdateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::InteropMechanismAttr getInteropMechanismAttr() {
    auto attr = ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
    return attr;
  }

  ::InteropMechanism getInteropMechanism();
  ::mlir::Region &getUpdateRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ProceduralUpdateOpGenericAdaptor : public detail::ProceduralUpdateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ProceduralUpdateOpGenericAdaptorBase;
  static constexpr int odsIndex_states = 0;
  static constexpr int odsIndex_inputs = 1;
public:
  ProceduralUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ProceduralUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ProceduralUpdateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ProceduralUpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ProceduralUpdateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ProceduralUpdateOpGenericAdaptor(RangeT values, const ProceduralUpdateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ProceduralUpdateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ProceduralUpdateOp>>>
  ProceduralUpdateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getStates() {
    return getODSOperands(0);
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
class ProceduralUpdateOpAdaptor : public ProceduralUpdateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ProceduralUpdateOpGenericAdaptor::ProceduralUpdateOpGenericAdaptor;
  ProceduralUpdateOpAdaptor(ProceduralUpdateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ProceduralUpdateOp : public ::mlir::Op<ProceduralUpdateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ProceduralUpdateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ProceduralUpdateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_states = 0;
  static constexpr int odsIndex_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("interopMechanism"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInteropMechanismAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInteropMechanismAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("interop.procedural.update");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getStates() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getStatesMutable();
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

  ::mlir::Region &getUpdateRegion() {
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
  ::InteropMechanismAttr getInteropMechanismAttr() {
    return ::llvm::cast<::InteropMechanismAttr>(getProperties().interopMechanism);
  }

  ::InteropMechanism getInteropMechanism();
  void setInteropMechanismAttr(::InteropMechanismAttr attr) {
    getProperties().interopMechanism = attr;
  }

  void setInteropMechanism(::InteropMechanism attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralUpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, ValueRange states, InteropMechanism interopMechanism);
  static ProceduralUpdateOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, ValueRange states, InteropMechanism interopMechanism);
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
};

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralUpdateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralUpdateOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ReturnOp declarations
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
      odsOpName.emplace("interop.return", odsAttrs.getContext());
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<ProceduralInitOp, ProceduralUpdateOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
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
    return ::llvm::StringLiteral("interop.return");
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
public:
};

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::ReturnOp)


#endif // GET_OP_CLASSES

