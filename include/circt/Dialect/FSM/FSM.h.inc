/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FSM.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::fsm {

/// Create a hardware-style instance of a state machine
/// `fsm.hw_instance` represents a hardware-style instance of a state machine,
/// including an instance name and a symbol reference of the machine. The inputs
/// and outputs are correponding to the inputs and outputs of the referenced
/// machine.
class HWInstanceOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Create an instance of a state machine
/// `fsm.instance` represents an instance of a state machine, including an
/// instance name and a symbol reference of the machine.
class InstanceOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Define a finite-state machine
/// `fsm.machine` represents a finite-state machine, including a machine name,
/// the type of machine state, and the types of inputs and outputs. This op also
/// includes a `$body` region that contains internal variables and states.
class MachineOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Output values from a state machine
/// "fsm.output" represents the outputs of a machine under a specific state. The
/// types of `$operands` should be consistent with the output types of the state
/// machine.
class OutputOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Return values from a region
/// "fsm.return" marks the end of a region of `fsm.transition` and return
/// values if the parent region is a `$guard` region.
class ReturnOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Define a state of a machine
/// `fsm.state` represents a state of a state machine. This op includes an
/// `$output` region with an `fsm.output` as terminator to define the machine
/// outputs under this state. This op also includes a `transitions` region that
/// contains all the transitions of this state.
class StateOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Define a transition of a state
/// `fsm.transition` represents a transition of a state with a symbol reference
/// of the next state. This op includes an optional `$guard` region with an `fsm.return`
/// as terminator that returns a Boolean value indicating the guard condition of
/// this transition. This op also includes an optional `$action` region that represents
/// the actions to be executed when this transition is taken.
class TransitionOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Trigger an instance
/// `fsm.trigger` triggers a state machine instance. The inputs and outputs are
/// correponding to the inputs and outputs of the referenced machine of the
/// instance.
class TriggerOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Update a variable in a state machine
/// `fsm.update` updates the `$variable` with the `$value`. The definition op of
/// `$variable` should be an `fsm.variable`. This op should *only* appear in the
/// `action` region of a transtion.
class UpdateOp;

} // namespace circt::fsm
namespace circt::fsm {

/// Declare a variable in a state machine
/// `fsm.variable` represents an internal variable in a state machine with an
/// initialization value.
class VariableOp;

} // namespace circt::fsm
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::HWInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HWInstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using machineTy = ::mlir::FlatSymbolRefAttr;
    machineTy machine;

    auto getMachine() const {
      auto &propStorage = this->machine;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setMachine(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->machine = propValue;
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
        rhs.machine == this->machine &&
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
  HWInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.hw_instance", odsAttrs.getContext());
  }

  HWInstanceOpGenericAdaptorBase(HWInstanceOp op);

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
  ::mlir::FlatSymbolRefAttr getMachineAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().machine);
    return attr;
  }

  ::llvm::StringRef getMachine();
};

} // namespace detail
template <typename RangeT>
class HWInstanceOpGenericAdaptor : public detail::HWInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HWInstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_reset = 2;
public:
  HWInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HWInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HWInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HWInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HWInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HWInstanceOpGenericAdaptor(RangeT values, const HWInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HWInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, HWInstanceOp>>>
  HWInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getReset() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class HWInstanceOpAdaptor : public HWInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HWInstanceOpGenericAdaptor::HWInstanceOpGenericAdaptor;
  HWInstanceOpAdaptor(HWInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HWInstanceOp : public ::mlir::Op<HWInstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::igraph::InstanceOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HWInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HWInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_reset = 2;
  using Properties = FoldAdaptor::Properties;
  using ::circt::igraph::InstanceOpInterface::Trait<HWInstanceOp>::getReferencedModuleNames;
  using ::circt::igraph::InstanceOpInterface::Trait<HWInstanceOp>::getReferencedModuleNamesAttr;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("machine"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMachineAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMachineAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.hw_instance");
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

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getResetMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutputs() {
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::FlatSymbolRefAttr getMachineAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().machine);
  }

  ::llvm::StringRef getMachine();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setMachineAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().machine = attr;
  }

  void setMachine(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static HWInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static HWInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::llvm::StringRef name, ::llvm::StringRef machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static HWInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::llvm::StringRef name, ::llvm::StringRef machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static HWInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::llvm::StringRef name, ::llvm::StringRef machine, ::mlir::ValueRange inputs, ::mlir::Value clock, ::mlir::Value reset);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HWInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HWInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HWInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HWInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::StringRef getInstanceName();
  ::mlir::StringAttr getInstanceNameAttr();
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
  /// Lookup the machine for the symbol. This returns null on invalid IR.
  MachineOp getMachineOp();

  /// Module name is the same as the machine name.
  StringRef getModuleName();

  FlatSymbolRefAttr getModuleNameAttr();

  StringAttr getReferencedModuleNameAttr() {
    return getModuleNameAttr().getAttr();
  }

  //===------------------------------------------------------------------===//
  // PortList Methods
  //===------------------------------------------------------------------===//
  SmallVector<::circt::hw::PortInfo> getPortList();
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::HWInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::HWInstanceOpGenericAdaptorBase::Properties)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using machineTy = ::mlir::FlatSymbolRefAttr;
    machineTy machine;

    auto getMachine() const {
      auto &propStorage = this->machine;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setMachine(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->machine = propValue;
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
        rhs.machine == this->machine &&
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
  InstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.instance", odsAttrs.getContext());
  }

  InstanceOpGenericAdaptorBase(InstanceOp op);

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
  ::mlir::FlatSymbolRefAttr getMachineAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().machine);
    return attr;
  }

  ::llvm::StringRef getMachine();
};

} // namespace detail
template <typename RangeT>
class InstanceOpGenericAdaptor : public detail::InstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceOpGenericAdaptorBase;
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
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::fsm::InstanceType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("machine"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMachineAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMachineAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.instance");
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

  ::mlir::TypedValue<::circt::fsm::InstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::fsm::InstanceType>>(*getODSResults(0).begin());
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
  ::mlir::FlatSymbolRefAttr getMachineAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().machine);
  }

  ::llvm::StringRef getMachine();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setMachineAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().machine = attr;
  }

  void setMachine(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instance, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instance, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instance, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr machine);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instance, ::llvm::StringRef name, ::llvm::StringRef machine);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instance, ::llvm::StringRef name, ::llvm::StringRef machine);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instance, ::llvm::StringRef name, ::llvm::StringRef machine);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef machine);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef machine);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef machine);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Lookup the machine for the symbol. This returns null on invalid IR.
  MachineOp getMachineOp();

  //===------------------------------------------------------------------===//
  // PortList Methods
  //===------------------------------------------------------------------===//
  SmallVector<::circt::hw::PortInfo> getPortList();
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::MachineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MachineOpGenericAdaptorBase {
public:
  struct Properties {
    using argNamesTy = ::mlir::ArrayAttr;
    argNamesTy argNames;

    auto getArgNames() const {
      auto &propStorage = this->argNames;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
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
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using initialStateTy = ::mlir::StringAttr;
    initialStateTy initialState;

    auto getInitialState() const {
      auto &propStorage = this->initialState;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInitialState(const ::mlir::StringAttr &propValue) {
      this->initialState = propValue;
    }
    using resNamesTy = ::mlir::ArrayAttr;
    resNamesTy resNames;

    auto getResNames() const {
      auto &propStorage = this->resNames;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResNames(const ::mlir::ArrayAttr &propValue) {
      this->resNames = propValue;
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.argNames == this->argNames &&
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.initialState == this->initialState &&
        rhs.resNames == this->resNames &&
        rhs.res_attrs == this->res_attrs &&
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
  MachineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.machine", odsAttrs.getContext());
  }

  MachineOpGenericAdaptorBase(MachineOp op);

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
  ::mlir::StringAttr getInitialStateAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().initialState);
    return attr;
  }

  ::llvm::StringRef getInitialState();
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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().argNames);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgNames();
  ::mlir::ArrayAttr getResNamesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().resNames);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResNames();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class MachineOpGenericAdaptor : public detail::MachineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MachineOpGenericAdaptorBase;
public:
  MachineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MachineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MachineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MachineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MachineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MachineOpGenericAdaptor(RangeT values, const MachineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MachineOp, typename = std::enable_if_t<std::is_same_v<LateInst, MachineOp>>>
  MachineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MachineOpAdaptor : public MachineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MachineOpGenericAdaptor::MachineOpGenericAdaptor;
  MachineOpAdaptor(MachineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MachineOp : public ::mlir::Op<MachineOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::SymbolTable, ::circt::igraph::ModuleOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MachineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MachineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::igraph::ModuleOpInterface::Trait<MachineOp>::getModuleName;
  using ::circt::igraph::ModuleOpInterface::Trait<MachineOp>::getModuleNameAttr;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argNames"), ::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("initialState"), ::llvm::StringRef("resNames"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name")};
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

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getInitialStateAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInitialStateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getResNamesAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getResNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.machine");
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
  ::mlir::StringAttr getInitialStateAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().initialState);
  }

  ::llvm::StringRef getInitialState();
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
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().argNames);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgNames();
  ::mlir::ArrayAttr getResNamesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().resNames);
  }

  ::std::optional< ::mlir::ArrayAttr > getResNames();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setInitialStateAttr(::mlir::StringAttr attr) {
    getProperties().initialState = attr;
  }

  void setInitialState(::llvm::StringRef attrValue);
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

  void setResNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().resNames = attr;
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

  ::mlir::Attribute removeArgNamesAttr() {
      auto attr = getProperties().argNames;
      getProperties().argNames = {};
      return attr;
  }

  ::mlir::Attribute removeResNamesAttr() {
      auto attr = getProperties().resNames;
      getProperties().resNames = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, StringRef initialState, FunctionType function_type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static MachineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, StringRef initialState, FunctionType function_type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static MachineOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, StringRef initialState, FunctionType function_type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
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
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Get the initial state of the machine.
  StateOp getInitialStateOp();

  /// Get the port information of the machine.
  void getHWPortInfo(SmallVectorImpl<hw::PortInfo> &);

  /// Returns the number of states in this machine.
  size_t getNumStates();

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// Returns the region on the current operation that is callable. This may
  /// return null in the case of an external callable object, e.g. an external
  /// function.
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }

  /// Verify the type attribute of this function. Returns failure and emits
  /// an error if the attribute is invalid.
  LogicalResult verifyType() {
    auto type = getFunctionTypeAttr().getValue();
    if (!llvm::isa<FunctionType>(type))
      return emitOpError("requires '" + getFunctionTypeAttrName().getValue() +
                         "' attribute of function type");
    return success();
  }

  /// Return the name of the i'th input to this machine.
  StringAttr getArgName(size_t i);

  /// Return the name of the i'th result of this machine.
  StringAttr getResName(size_t i);

  //===------------------------------------------------------------------===//
  // PortList Methods
  //===------------------------------------------------------------------===//
  SmallVector<::circt::hw::PortInfo> getPortList();
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::MachineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::MachineOpGenericAdaptorBase::Properties)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::OutputOp declarations
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
      odsOpName.emplace("fsm.output", odsAttrs.getContext());
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
  static constexpr int odsIndex_operands = 0;
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

  RangeT getOperands() {
    return getODSOperands(0);
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
class OutputOp : public ::mlir::Op<OutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<StateOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.output");
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
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
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
public:
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::OutputOp)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::ReturnOp declarations
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
      odsOpName.emplace("fsm.return", odsAttrs.getContext());
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
  static constexpr int odsIndex_operand = 0;
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

  ValueT getOperand() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<TransitionOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOperand() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getOperandMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Value operand);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Value operand);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Value operand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value operand);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value operand);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::Value operand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  // Assigns the guard operand to the provided value.
  void setOperand(Value operand);
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::ReturnOp)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::StateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StateOpGenericAdaptorBase {
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
  StateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.state", odsAttrs.getContext());
  }

  StateOpGenericAdaptorBase(StateOp op);

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
  ::mlir::Region &getOutput() {
    return *odsRegions[0];
  }

  ::mlir::Region &getTransitions() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StateOpGenericAdaptor : public detail::StateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StateOpGenericAdaptorBase;
public:
  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StateOpGenericAdaptor(RangeT values, const StateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StateOp, typename = std::enable_if_t<std::is_same_v<LateInst, StateOp>>>
  StateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StateOpAdaptor : public StateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StateOpGenericAdaptor::StateOpGenericAdaptor;
  StateOpAdaptor(StateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StateOp : public ::mlir::Op<StateOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<MachineOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StateOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("fsm.state");
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

  ::mlir::Region &getOutput() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getTransitions() {
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef stateName);
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef stateName);
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef stateName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef stateName, ValueRange outputs);
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef stateName, ValueRange outputs);
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef stateName, ValueRange outputs);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(StateOp op, ::mlir::PatternRewriter &rewriter);
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
  /// Returns all possible next states from this state.
  llvm::SetVector<StateOp> getNextStates();

  /// Returns the OutputOp of this state.
  OutputOp getOutputOp() {
    auto outputOp = getOutput().getOps<fsm::OutputOp>();
    assert(!outputOp.empty() &&
         "Expected an fsm.output op inside the state output region");
    return *outputOp.begin();
  }

  /// Ensures that this state has an output region with an output operation.
  /// Returns the inner block of the output region.
  Block* ensureOutput(OpBuilder& builder);
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::StateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::StateOpGenericAdaptorBase::Properties)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::TransitionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TransitionOpGenericAdaptorBase {
public:
  struct Properties {
    using nextStateTy = ::mlir::FlatSymbolRefAttr;
    nextStateTy nextState;

    auto getNextState() const {
      auto &propStorage = this->nextState;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setNextState(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->nextState = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.nextState == this->nextState &&
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
  TransitionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.transition", odsAttrs.getContext());
  }

  TransitionOpGenericAdaptorBase(TransitionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getNextStateAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().nextState);
    return attr;
  }

  ::llvm::StringRef getNextState();
  ::mlir::Region &getGuard() {
    return *odsRegions[0];
  }

  ::mlir::Region &getAction() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TransitionOpGenericAdaptor : public detail::TransitionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TransitionOpGenericAdaptorBase;
public:
  TransitionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TransitionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TransitionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TransitionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TransitionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TransitionOpGenericAdaptor(RangeT values, const TransitionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TransitionOp, typename = std::enable_if_t<std::is_same_v<LateInst, TransitionOp>>>
  TransitionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TransitionOpAdaptor : public TransitionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TransitionOpGenericAdaptor::TransitionOpGenericAdaptor;
  TransitionOpAdaptor(TransitionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TransitionOp : public ::mlir::Op<TransitionOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<StateOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TransitionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TransitionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("nextState")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNextStateAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNextStateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.transition");
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

  ::mlir::Region &getGuard() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getAction() {
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
  ::mlir::FlatSymbolRefAttr getNextStateAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().nextState);
  }

  ::llvm::StringRef getNextState();
  void setNextStateAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().nextState = attr;
  }

  void setNextState(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, fsm::StateOp nextState);
  static TransitionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, fsm::StateOp nextState);
  static TransitionOp create(::mlir::ImplicitLocOpBuilder &builder, fsm::StateOp nextState);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef nextState, llvm::function_ref<void()> guardCtor = {}, llvm::function_ref<void()> actionCtor = {});
  static TransitionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef nextState, llvm::function_ref<void()> guardCtor = {}, llvm::function_ref<void()> actionCtor = {});
  static TransitionOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef nextState, llvm::function_ref<void()> guardCtor = {}, llvm::function_ref<void()> actionCtor = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(TransitionOp op, ::mlir::PatternRewriter &rewriter);
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
  /// Lookup the next state for the symbol. This returns null on invalid IR.
  StateOp getNextStateOp();

  /// Get the current state, this should never fail.
  StateOp getCurrentState() {
    return (*this)->getParentOfType<StateOp>();
  }

  /// Get the return operation of the guard region, this should never fail.
  ReturnOp getGuardReturn() {
    assert(!getGuard().empty() && "this transition has no guard");
    return cast<ReturnOp>(getGuard().front().getTerminator());
  }

  /// Return whether this transition has a guard.
  bool hasGuard() {
    return !getGuard().empty();
  }

  /// Return whether this transition has an action.
  bool hasAction() {
    return !getAction().empty();
  }

  /// Returns true if this transition is always taken.
  bool isAlwaysTaken();

  /// Ensures that this transition has a guard region.
  Block* ensureGuard(OpBuilder& builder);

  /// Ensures that this transition has an action region.
  Block* ensureAction(OpBuilder& builder);
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::TransitionOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::TransitionOpGenericAdaptorBase::Properties)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::TriggerOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TriggerOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TriggerOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.trigger", odsAttrs.getContext());
  }

  TriggerOpGenericAdaptorBase(TriggerOp op);

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
class TriggerOpGenericAdaptor : public detail::TriggerOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TriggerOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_instance = 1;
public:
  TriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TriggerOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TriggerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TriggerOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TriggerOpGenericAdaptor(RangeT values, const TriggerOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TriggerOp, typename = std::enable_if_t<std::is_same_v<LateInst, TriggerOp>>>
  TriggerOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getInstance() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TriggerOpAdaptor : public TriggerOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TriggerOpGenericAdaptor::TriggerOpGenericAdaptor;
  TriggerOpAdaptor(TriggerOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TriggerOp : public ::mlir::Op<TriggerOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TriggerOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TriggerOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_instance = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.trigger");
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

  ::mlir::TypedValue<::circt::fsm::InstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::fsm::InstanceType>>(*getODSOperands(1).begin());
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::OpOperand &getInstanceMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutputs() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::ValueRange inputs, ::mlir::Value instance);
  static TriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::ValueRange inputs, ::mlir::Value instance);
  static TriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::ValueRange inputs, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TriggerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TriggerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Lookup the machine for the symbol. This returns null on invalid IR.
  MachineOp getMachineOp();
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::TriggerOp)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::UpdateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UpdateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UpdateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("fsm.update", odsAttrs.getContext());
  }

  UpdateOpGenericAdaptorBase(UpdateOp op);

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
class UpdateOpGenericAdaptor : public detail::UpdateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UpdateOpGenericAdaptorBase;
  static constexpr int odsIndex_variable = 0;
  static constexpr int odsIndex_value = 1;
public:
  UpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UpdateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UpdateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UpdateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UpdateOpGenericAdaptor(RangeT values, const UpdateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UpdateOp, typename = std::enable_if_t<std::is_same_v<LateInst, UpdateOp>>>
  UpdateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getVariable() {
    return (*getODSOperands(0).begin());
  }

  ValueT getValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UpdateOpAdaptor : public UpdateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UpdateOpGenericAdaptor::UpdateOpGenericAdaptor;
  UpdateOpAdaptor(UpdateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UpdateOp : public ::mlir::Op<UpdateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::HasParent<TransitionOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SameTypeOperands> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UpdateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UpdateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_variable = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.update");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getVariable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getVariableMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value variable, ::mlir::Value value);
  static UpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value variable, ::mlir::Value value);
  static UpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value variable, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::Value value);
  static UpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::Value value);
  static UpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value variable, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UpdateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UpdateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(UpdateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Get the targeted variable operation. This returns null on invalid IR.
  VariableOp getVariableOp();
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::UpdateOp)

namespace circt::fsm {


//===----------------------------------------------------------------------===//
// ::circt::fsm::VariableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VariableOpGenericAdaptorBase {
public:
  struct Properties {
    using initValueTy = ::mlir::Attribute;
    initValueTy initValue;

    auto getInitValue() const {
      auto &propStorage = this->initValue;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
    }
    void setInitValue(const ::mlir::Attribute &propValue) {
      this->initValue = propValue;
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
        rhs.initValue == this->initValue &&
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
      odsOpName.emplace("fsm.variable", odsAttrs.getContext());
  }

  VariableOpGenericAdaptorBase(VariableOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getInitValueAttr() {
    auto attr = ::llvm::cast<::mlir::Attribute>(getProperties().initValue);
    return attr;
  }

  ::mlir::Attribute getInitValue();
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
class VariableOp : public ::mlir::Op<VariableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<MachineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VariableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VariableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("initValue"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInitValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInitValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("fsm.variable");
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
  ::mlir::Attribute getInitValueAttr() {
    return ::llvm::cast<::mlir::Attribute>(getProperties().initValue);
  }

  ::mlir::Attribute getInitValue();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setInitValueAttr(::mlir::Attribute attr) {
    getProperties().initValue = attr;
  }

  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute initValue, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::VariableOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::detail::VariableOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

