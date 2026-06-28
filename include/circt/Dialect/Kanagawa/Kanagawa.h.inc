/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::kanagawa {

/// Kanagawa static block terminator
class BlockReturnOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa method call
/// Dispatch a call to an Kanagawa method.
class CallOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa class
/// Kanagawa has the notion of a class which can contain methods and member
/// variables.
/// 
/// In the low-level Kanagawa representation, the ClassOp becomes a container for
/// `kanagawa.port`s, `kanagawa.container`s, and contain logic for member variables.
class ClassOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa container instance
/// Instantiates an Kanagawa container.
class ContainerInstanceOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa container
/// An kanagawa container describes a collection of logic nested within an Kanagawa class.
class ContainerOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// DC-interfaced Kanagawa block
/// The `kanagawa.sblock.dc` operation is like an `kanagawa.sblock` operation with
/// a few differences, being:
/// 1. The operation is DC-interfaced, meaning that all arguments and results
///    are dc-value typed.
/// 2. The operation is IsolatedFromAbove.
class DCBlockOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa dataflow method
/// Kanagawa dataflow methods share the same interface as an `kanagawa.method` but
/// without imperative CFG-based control flow. Instead, this method implements a
/// graph region, and control flow is expected to be defined by dataflow operations.
class DataflowMethodOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// All Kanagawa containers must be inside this op
class DesignOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa get port
/// Given an Kanagawa class reference, returns a port of said class. The port
/// is specified by the symbol name of the port in the referenced class.
/// 
/// Importantly, the user must specify how they intend to use the op, by
/// specifying the direction of the portref type that this op is generated with.
/// If the request port is to be read from, the type must be `!kanagawa.portref<out T>`
/// and if the port is to be written to, the type must be `!kanagawa.portref<in T>`.
/// This is to ensure that the usage is reflected in the get_port type which in
/// turn is used by the tunneling passes to create the proper ports through the
/// hierarchy.
/// 
/// This implies that the portref direction of the get_port op is independent of
/// the actual direction of the target port, and only the inner portref type
/// must match.
class GetPortOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Dereferences an kanagawa member variable through a scoperef
class GetVarOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa inline static block begin marker
/// The `kanagawa.sblock.inline.begin` operation is a marker that indicates the
/// begin of an inline static block.
/// The operation is used to maintain `kanagawa.sblocks` while in the Kanagawa inline
/// phase (to facilitate e.g. mem2reg).
/// 
/// The operation:
/// 1. denotes the begin of the sblock
/// 2. carries whatever attributes that the source `kanagawa.sblock` carried.
/// 3. is considered side-effectfull.
class InlineStaticBlockBeginOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa inline static block end marker
/// The `kanagawa.sblock.inline.end` operation is a marker that indicates the
/// end of an inline static block.
/// The operation is used to maintain `kanagawa.sblocks` while in the Kanagawa inline
/// phase (to facilitate e.g. mem2reg).
class InlineStaticBlockEndOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa input port
/// An kanagawa port has an attached 'name' attribute. This is a name-hint used
/// to generate the final port name. The port name and port symbol are not
/// related, and all references to a port is done through the port symbol.
class InputPortOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa input wire
/// An input wire defines an `kanagawa.portref<in T>` port alongside a value
/// of type `T` which represents the value to-be-written to the wire.
class InputWireOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa class instance
/// Instantiates an Kanagawa class.
class InstanceOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa isolated block
/// The `kanagawa.sblock.isolated` operation is like an `kanagawa.sblock` operation
/// but with an IsolatedFromAbove condition, meaning that all arguments and
/// results are passed through the block as arguments and results.
class IsolatedStaticBlockOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa method
/// Kanagawa methods are a lot like software functions: a list of named arguments
/// and unnamed return values with imperative control flow.
class MethodOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa output port
/// An kanagawa port has an attached 'name' attribute. This is a name-hint used
/// to generate the final port name. The port name and port symbol are not
/// related, and all references to a port is done through the port symbol.
class OutputPortOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa output wire
/// An output wire defines an `kanagawa.portref<out T>` port that can be read.
/// The operation takes an input value of type `T` which represents the value
/// on the output portref.
class OutputWireOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa path
/// The `kanagawa.path` operation describes an instance hierarchy path relative to
/// the current scope. The path is specified by a list of either parent or
/// child identifiers (navigating up or down the hierarchy, respectively).
/// 
/// Scopes along the path are optionally typed, however, An `kanagawa.path` must
/// lways terminate in a fully typed specifier, i.e. never an `!kanagawa.scoperef<>`.
/// 
/// The operation returns a single `!kanagawa.scoperef`-typed value representing
/// the scope at the end of the path.
class PathOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa pipeline header operation
/// This operation defines the hardware-like values used to drive a pipeline,
/// such as clock and reset.
/// This is an intermediate operation, meaning that it's strictly used to
/// facilitate progressive lowering of kanagawa static blocks to scheduled pipelines.
class PipelineHeaderOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa port read
/// Read the value of a port reference.
class PortReadOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa port write
/// Write a value to a port reference.
class PortWriteOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa method terminator
class ReturnOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa block
/// The `kanagawa.sblock` operation defines a block wherein a group of operations
/// are expected to be statically scheduleable.
/// The operation is not isolated from above to facilitate ease of construction.
/// However, once a program has been constructed and lowered to a sufficient
/// level, the user may run `--kanagawa-argify-blocks` to effectively isolate the
/// block from above, by converting SSA values referenced through dominanes into
/// arguments of the block
/// 
/// The block may contain additional attributes to specify constraints on
/// the block further down the compilation pipeline.
class StaticBlockOp;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// Kanagawa variable definition
/// Defines an Kanagawa class member variable. The variable is typed with a
/// `memref.memref` type, and may define either a singleton or uni-dimensional
/// array of values.
/// `kanagawa.var` defines a symbol within the encompassing class scope which can
/// be dereferenced through a `!kanagawa.scoperef` value of the parent class.
class VarOp;

} // namespace circt::kanagawa
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::BlockReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BlockReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BlockReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock.return", odsAttrs.getContext());
  }

  BlockReturnOpGenericAdaptorBase(BlockReturnOp op);

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
class BlockReturnOpGenericAdaptor : public detail::BlockReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BlockReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_retValues = 0;
public:
  BlockReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BlockReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BlockReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BlockReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BlockReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BlockReturnOpGenericAdaptor(RangeT values, const BlockReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BlockReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, BlockReturnOp>>>
  BlockReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getRetValues() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BlockReturnOpAdaptor : public BlockReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BlockReturnOpGenericAdaptor::BlockReturnOpGenericAdaptor;
  BlockReturnOpAdaptor(BlockReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BlockReturnOp : public ::mlir::Op<BlockReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<StaticBlockOp, IsolatedStaticBlockOp, DCBlockOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BlockReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BlockReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_retValues = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<BlockReturnOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<BlockReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getRetValues() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getRetValuesMutable();
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
  static BlockReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static BlockReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange retValues);
  static BlockReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange retValues);
  static BlockReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange retValues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BlockReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BlockReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::BlockReturnOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::CallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CallOpGenericAdaptorBase {
public:
  struct Properties {
    using calleeTy = ::circt::hw::InnerRefAttr;
    calleeTy callee;

    auto getCallee() const {
      auto &propStorage = this->callee;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setCallee(const ::circt::hw::InnerRefAttr &propValue) {
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
      odsOpName.emplace("kanagawa.call", odsAttrs.getContext());
  }

  CallOpGenericAdaptorBase(CallOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerRefAttr getCalleeAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().callee);
    return attr;
  }

  ::circt::hw::InnerRefAttr getCallee();
};

} // namespace detail
template <typename RangeT>
class CallOpGenericAdaptor : public detail::CallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CallOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
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

  RangeT getOperands() {
    return getODSOperands(0);
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
class CallOp : public ::mlir::Op<CallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
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
    return ::llvm::StringLiteral("kanagawa.call");
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
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
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
  ::circt::hw::InnerRefAttr getCalleeAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().callee);
  }

  ::circt::hw::InnerRefAttr getCallee();
  void setCalleeAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().callee = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands);
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands);
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  MutableOperandRange getArgOperandsMutable() {
    return getOperandsMutable();
  }

  /// Get the argument operands to the called method.
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

  /// Return the callee of this operation.
  MethodOp getTarget(const hw::InnerRefNamespace &symbolTable);

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

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::CallOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::CallOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ClassOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClassOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
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
  ClassOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.class", odsAttrs.getContext());
  }

  ClassOpGenericAdaptorBase(ClassOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ClassOpGenericAdaptor : public detail::ClassOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClassOpGenericAdaptorBase;
public:
  ClassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClassOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClassOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClassOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClassOpGenericAdaptor(RangeT values, const ClassOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClassOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClassOp>>>
  ClassOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClassOpAdaptor : public ClassOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClassOpGenericAdaptor::ClassOpGenericAdaptor;
  ClassOpAdaptor(ClassOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClassOp : public ::mlir::Op<ClassOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<DesignOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::RegionKindInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::ScopeOpInterface::Trait, ::circt::igraph::ModuleOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClassOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClassOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("kanagawa.class");
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static ClassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static ClassOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static ClassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static ClassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClassOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClassOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  Block* getBodyBlock() { return &getBody().front(); }

  // For hw:InnerSymbol - the symbol targets the operation and not any result.
  static std::optional<size_t> getTargetResultIndex() {
    return std::nullopt;
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::ClassOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ClassOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ContainerInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ContainerInstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using targetNameTy = ::circt::hw::InnerRefAttr;
    targetNameTy targetName;

    auto getTargetName() const {
      auto &propStorage = this->targetName;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setTargetName(const ::circt::hw::InnerRefAttr &propValue) {
      this->targetName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.targetName == this->targetName &&
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
  ContainerInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.container.instance", odsAttrs.getContext());
  }

  ContainerInstanceOpGenericAdaptorBase(ContainerInstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::circt::hw::InnerRefAttr getTargetNameAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().targetName);
    return attr;
  }

  ::circt::hw::InnerRefAttr getTargetName();
};

} // namespace detail
template <typename RangeT>
class ContainerInstanceOpGenericAdaptor : public detail::ContainerInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ContainerInstanceOpGenericAdaptorBase;
public:
  ContainerInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ContainerInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ContainerInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ContainerInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ContainerInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ContainerInstanceOpGenericAdaptor(RangeT values, const ContainerInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ContainerInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ContainerInstanceOp>>>
  ContainerInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ContainerInstanceOpAdaptor : public ContainerInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ContainerInstanceOpGenericAdaptor::ContainerInstanceOpGenericAdaptor;
  ContainerInstanceOpAdaptor(ContainerInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ContainerInstanceOp : public ::mlir::Op<ContainerInstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::ScopeRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::circt::igraph::InstanceOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ContainerInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ContainerInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ContainerInstanceOp>::getTargetResult;
  using ::mlir::OpAsmOpInterface::Trait<ContainerInstanceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ContainerInstanceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ContainerInstanceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("targetName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTargetNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTargetNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.container.instance");
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

  ::mlir::TypedValue<::circt::kanagawa::ScopeRefType> getScopeRef() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::ScopeRefType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::circt::hw::InnerRefAttr getTargetNameAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().targetName);
  }

  ::circt::hw::InnerRefAttr getTargetName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setTargetNameAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().targetName = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static ContainerInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContainerInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContainerInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContainerInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContainerInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static std::optional<size_t> getTargetResultIndex();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  // Return the container this instance is instantiating.
  ContainerOp getContainer(const hw::InnerRefNamespace &symbolTable);

  llvm::StringRef getInstanceName() {
    return getInnerSym().getSymName().strref();
  }

  mlir::StringAttr getInstanceNameAttr() {
    return getInnerSymAttr().getSymName();
  }

  StringAttr getReferencedModuleNameAttr() {
    return getTargetNameAttr().getName();
  }

  // Operation* getReferencedModuleSlow();
  Operation* getReferencedModule(const hw::InnerRefNamespace &);
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::ContainerInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ContainerInstanceOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ContainerOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ContainerOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using isTopLevelTy = ::mlir::UnitAttr;
    isTopLevelTy isTopLevel;

    auto getIsTopLevel() const {
      auto &propStorage = this->isTopLevel;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsTopLevel(const ::mlir::UnitAttr &propValue) {
      this->isTopLevel = propValue;
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
        rhs.isTopLevel == this->isTopLevel &&
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
  ContainerOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.container", odsAttrs.getContext());
  }

  ContainerOpGenericAdaptorBase(ContainerOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::UnitAttr getIsTopLevelAttr();
  bool getIsTopLevel();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ContainerOpGenericAdaptor : public detail::ContainerOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ContainerOpGenericAdaptorBase;
public:
  ContainerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ContainerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ContainerOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ContainerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ContainerOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ContainerOpGenericAdaptor(RangeT values, const ContainerOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ContainerOp, typename = std::enable_if_t<std::is_same_v<LateInst, ContainerOp>>>
  ContainerOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ContainerOpAdaptor : public ContainerOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ContainerOpGenericAdaptor::ContainerOpGenericAdaptor;
  ContainerOpAdaptor(ContainerOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ContainerOp : public ::mlir::Op<ContainerOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::HasParent<DesignOp, ClassOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::ScopeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::circt::igraph::ModuleOpInterface::Trait, ::mlir::RegionKindInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ContainerOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ContainerOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::kanagawa::NamedInnerSymbolInterface::Trait<ContainerOp>::getNameHintAttr;
  using circt::kanagawa::NamedInnerSymbolInterface::Trait<ContainerOp>::getNameHint;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("isTopLevel"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsTopLevelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsTopLevelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.container");
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::UnitAttr getIsTopLevelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isTopLevel);
  }

  bool getIsTopLevel();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setIsTopLevelAttr(::mlir::UnitAttr attr) {
    getProperties().isTopLevel = attr;
  }

  void setIsTopLevel(bool attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeIsTopLevelAttr() {
      auto attr = getProperties().isTopLevel;
      getProperties().isTopLevel = {};
      return attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
  static ContainerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
  static ContainerOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
  static ContainerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
  static ContainerOp create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name = nullptr);
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
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  Block* getBodyBlock() { return &getBody().front(); }

  // For hw:InnerSymbol - the symbol targets the operation and not any result.
  static std::optional<size_t> getTargetResultIndex() {
    return std::nullopt;
  }

  // Override InstanceGraphModuleOpInterface::getModuleNameAttr to return the
  // inner_sym name of the container instead of the `name` which is the default
  // behavior of InstanceGraphModuleOpInterface.
  mlir::StringAttr getModuleNameAttr() {
    return getInnerSymAttr().getSymName();
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::ContainerOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ContainerOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DCBlockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DCBlockOpGenericAdaptorBase {
public:
  struct Properties {
    using maxThreadsTy = ::mlir::IntegerAttr;
    maxThreadsTy maxThreads;

    auto getMaxThreads() const {
      auto &propStorage = this->maxThreads;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setMaxThreads(const ::mlir::IntegerAttr &propValue) {
      this->maxThreads = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.maxThreads == this->maxThreads &&
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
  DCBlockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock.dc", odsAttrs.getContext());
  }

  DCBlockOpGenericAdaptorBase(DCBlockOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getMaxThreadsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
    return attr;
  }

  ::std::optional<uint64_t> getMaxThreads();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DCBlockOpGenericAdaptor : public detail::DCBlockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DCBlockOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  DCBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DCBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DCBlockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DCBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DCBlockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DCBlockOpGenericAdaptor(RangeT values, const DCBlockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DCBlockOp, typename = std::enable_if_t<std::is_same_v<LateInst, DCBlockOp>>>
  DCBlockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DCBlockOpAdaptor : public DCBlockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DCBlockOpGenericAdaptor::DCBlockOpGenericAdaptor;
  DCBlockOpAdaptor(DCBlockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DCBlockOp : public ::mlir::Op<DCBlockOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<BlockReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::AutomaticAllocationScope, circt::kanagawa::BlockOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DCBlockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DCBlockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("maxThreads")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMaxThreadsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMaxThreadsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock.dc");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getMaxThreadsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
  }

  ::std::optional<uint64_t> getMaxThreads();
  void setMaxThreadsAttr(::mlir::IntegerAttr attr) {
    getProperties().maxThreads = attr;
  }

  void setMaxThreads(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeMaxThreadsAttr() {
      auto attr = getProperties().maxThreads;
      getProperties().maxThreads = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static DCBlockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static DCBlockOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
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
  // The internal result types of a DC block op is the DC-type stripped
  // outer result values.
  llvm::SmallVector<Type> getInternalResultTypes() {
    llvm::SmallVector<Type> innerRes;
    for(Type outerRes : getResultTypes())
      innerRes.push_back(llvm::cast<dc::ValueType>(outerRes).getInnerType());
    return innerRes;
  }

  // Return the body of this block.
  Block* getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::DCBlockOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DCBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DataflowMethodOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DataflowMethodOpGenericAdaptorBase {
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
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
        rhs.argNames == this->argNames &&
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.inner_sym == this->inner_sym &&
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
  DataflowMethodOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.method.df", odsAttrs.getContext());
  }

  DataflowMethodOpGenericAdaptorBase(DataflowMethodOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
    return attr;
  }

  ::mlir::ArrayAttr getArgNames();
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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DataflowMethodOpGenericAdaptor : public detail::DataflowMethodOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DataflowMethodOpGenericAdaptorBase;
public:
  DataflowMethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DataflowMethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DataflowMethodOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DataflowMethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DataflowMethodOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DataflowMethodOpGenericAdaptor(RangeT values, const DataflowMethodOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DataflowMethodOp, typename = std::enable_if_t<std::is_same_v<LateInst, DataflowMethodOp>>>
  DataflowMethodOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DataflowMethodOpAdaptor : public DataflowMethodOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DataflowMethodOpGenericAdaptor::DataflowMethodOpGenericAdaptor;
  DataflowMethodOpAdaptor(DataflowMethodOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DataflowMethodOp : public ::mlir::Op<DataflowMethodOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<kanagawa::ReturnOp>::Impl, ::mlir::OpTrait::HasParent<ClassOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::circt::handshake::FineGrainedDataflowRegionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::MethodLikeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DataflowMethodOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DataflowMethodOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<DataflowMethodOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argNames"), ::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("res_attrs")};
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

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.method.df");
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().argNames = attr;
  }

  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataflowMethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DataflowMethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static std::optional<size_t> getTargetResultIndex();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  StringAttr getMethodName() {
    return getInnerSymAttr().getSymName();
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::DataflowMethodOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DataflowMethodOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DesignOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DesignOpGenericAdaptorBase {
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
  DesignOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.design", odsAttrs.getContext());
  }

  DesignOpGenericAdaptorBase(DesignOp op);

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
class DesignOpGenericAdaptor : public detail::DesignOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DesignOpGenericAdaptorBase;
public:
  DesignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DesignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DesignOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DesignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DesignOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DesignOpGenericAdaptor(RangeT values, const DesignOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DesignOp, typename = std::enable_if_t<std::is_same_v<LateInst, DesignOp>>>
  DesignOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DesignOpAdaptor : public DesignOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DesignOpGenericAdaptor::DesignOpGenericAdaptor;
  DesignOpAdaptor(DesignOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DesignOp : public ::mlir::Op<DesignOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::InnerSymbolTable, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DesignOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DesignOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("kanagawa.design");
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
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DesignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DesignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::DesignOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DesignOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::GetPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetPortOpGenericAdaptorBase {
public:
  struct Properties {
    using portSymbolTy = ::mlir::FlatSymbolRefAttr;
    portSymbolTy portSymbol;

    auto getPortSymbol() const {
      auto &propStorage = this->portSymbol;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setPortSymbol(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->portSymbol = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.portSymbol == this->portSymbol &&
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
  GetPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.get_port", odsAttrs.getContext());
  }

  GetPortOpGenericAdaptorBase(GetPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getPortSymbolAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().portSymbol);
    return attr;
  }

  ::llvm::StringRef getPortSymbol();
};

} // namespace detail
template <typename RangeT>
class GetPortOpGenericAdaptor : public detail::GetPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetPortOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
public:
  GetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GetPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetPortOpGenericAdaptor(RangeT values, const GetPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetPortOp>>>
  GetPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetPortOpAdaptor : public GetPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetPortOpGenericAdaptor::GetPortOpGenericAdaptor;
  GetPortOpAdaptor(GetPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetPortOp : public ::mlir::Op<GetPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::PortRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GetPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GetPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GetPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("portSymbol")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPortSymbolAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPortSymbolAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.get_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::kanagawa::ScopeRefType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::ScopeRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
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

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSResults(0).begin());
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
  ::mlir::FlatSymbolRefAttr getPortSymbolAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().portSymbol);
  }

  ::llvm::StringRef getPortSymbol();
  void setPortSymbolAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().portSymbol = attr;
  }

  void setPortSymbol(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction);
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction);
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  // Returns the direction requested by this get_port op.
  kanagawa::Direction getDirection() {
    return llvm::cast<PortRefType>(getPort().getType()).getDirection();
  }

  // Returns the port op that this operation is referencing.
  PortOpInterface getPort(const hw::InnerRefNamespace &symbolTable);
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::GetPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::GetPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::GetVarOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetVarOpGenericAdaptorBase {
public:
  struct Properties {
    using varNameTy = ::mlir::FlatSymbolRefAttr;
    varNameTy varName;

    auto getVarName() const {
      auto &propStorage = this->varName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setVarName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->varName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.varName == this->varName &&
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
  GetVarOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.get_var", odsAttrs.getContext());
  }

  GetVarOpGenericAdaptorBase(GetVarOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getVarNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().varName);
    return attr;
  }

  ::llvm::StringRef getVarName();
};

} // namespace detail
template <typename RangeT>
class GetVarOpGenericAdaptor : public detail::GetVarOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetVarOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
public:
  GetVarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetVarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GetVarOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetVarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetVarOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetVarOpGenericAdaptor(RangeT values, const GetVarOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetVarOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetVarOp>>>
  GetVarOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetVarOpAdaptor : public GetVarOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetVarOpGenericAdaptor::GetVarOpGenericAdaptor;
  GetVarOpAdaptor(GetVarOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetVarOp : public ::mlir::Op<GetVarOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::MemRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetVarOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetVarOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GetVarOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GetVarOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GetVarOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("varName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getVarNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getVarNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.get_var");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::kanagawa::ScopeRefType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::ScopeRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
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

  ::mlir::TypedValue<::mlir::MemRefType> getVar() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSResults(0).begin());
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
  ::mlir::FlatSymbolRefAttr getVarNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().varName);
  }

  ::llvm::StringRef getVarName();
  void setVarNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().varName = attr;
  }

  void setVarName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName);
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName);
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName);
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName);
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetVarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetVarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  // Return the `VarOp` that this operation is referencing.
  VarOp getVar(const hw::InnerRefNamespace &symbolTable);
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::GetVarOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::GetVarOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InlineStaticBlockBeginOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InlineStaticBlockBeginOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InlineStaticBlockBeginOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock.inline.begin", odsAttrs.getContext());
  }

  InlineStaticBlockBeginOpGenericAdaptorBase(InlineStaticBlockBeginOp op);

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
class InlineStaticBlockBeginOpGenericAdaptor : public detail::InlineStaticBlockBeginOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InlineStaticBlockBeginOpGenericAdaptorBase;
public:
  InlineStaticBlockBeginOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InlineStaticBlockBeginOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InlineStaticBlockBeginOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InlineStaticBlockBeginOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InlineStaticBlockBeginOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InlineStaticBlockBeginOpGenericAdaptor(RangeT values, const InlineStaticBlockBeginOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InlineStaticBlockBeginOp, typename = std::enable_if_t<std::is_same_v<LateInst, InlineStaticBlockBeginOp>>>
  InlineStaticBlockBeginOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InlineStaticBlockBeginOpAdaptor : public InlineStaticBlockBeginOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InlineStaticBlockBeginOpGenericAdaptor::InlineStaticBlockBeginOpGenericAdaptor;
  InlineStaticBlockBeginOpAdaptor(InlineStaticBlockBeginOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InlineStaticBlockBeginOp : public ::mlir::Op<InlineStaticBlockBeginOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<MethodOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InlineStaticBlockBeginOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InlineStaticBlockBeginOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock.inline.begin");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static InlineStaticBlockBeginOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static InlineStaticBlockBeginOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static InlineStaticBlockBeginOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static InlineStaticBlockBeginOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InlineStaticBlockBeginOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InlineStaticBlockBeginOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InlineStaticBlockBeginOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InlineStaticBlockBeginOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Return the `InlineStaticBlockEndOp` that this operation is referencing.
  InlineStaticBlockEndOp getEndOp();
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::InlineStaticBlockBeginOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InlineStaticBlockEndOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InlineStaticBlockEndOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InlineStaticBlockEndOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock.inline.end", odsAttrs.getContext());
  }

  InlineStaticBlockEndOpGenericAdaptorBase(InlineStaticBlockEndOp op);

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
class InlineStaticBlockEndOpGenericAdaptor : public detail::InlineStaticBlockEndOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InlineStaticBlockEndOpGenericAdaptorBase;
public:
  InlineStaticBlockEndOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InlineStaticBlockEndOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InlineStaticBlockEndOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InlineStaticBlockEndOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InlineStaticBlockEndOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InlineStaticBlockEndOpGenericAdaptor(RangeT values, const InlineStaticBlockEndOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InlineStaticBlockEndOp, typename = std::enable_if_t<std::is_same_v<LateInst, InlineStaticBlockEndOp>>>
  InlineStaticBlockEndOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InlineStaticBlockEndOpAdaptor : public InlineStaticBlockEndOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InlineStaticBlockEndOpGenericAdaptor::InlineStaticBlockEndOpGenericAdaptor;
  InlineStaticBlockEndOpAdaptor(InlineStaticBlockEndOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InlineStaticBlockEndOp : public ::mlir::Op<InlineStaticBlockEndOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<MethodOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InlineStaticBlockEndOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InlineStaticBlockEndOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock.inline.end");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static InlineStaticBlockEndOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static InlineStaticBlockEndOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static InlineStaticBlockEndOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static InlineStaticBlockEndOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InlineStaticBlockEndOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InlineStaticBlockEndOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InlineStaticBlockEndOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InlineStaticBlockEndOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Return the `InlineStaticBlockBeginOp` that this operation is referencing.
  InlineStaticBlockBeginOp getBeginOp();
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::InlineStaticBlockEndOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InputPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InputPortOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
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
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.type == this->type &&
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
  InputPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.port.input", odsAttrs.getContext());
  }

  InputPortOpGenericAdaptorBase(InputPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class InputPortOpGenericAdaptor : public detail::InputPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InputPortOpGenericAdaptorBase;
public:
  InputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InputPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InputPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InputPortOpGenericAdaptor(RangeT values, const InputPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InputPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, InputPortOp>>>
  InputPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InputPortOpAdaptor : public InputPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InputPortOpGenericAdaptor::InputPortOpGenericAdaptor;
  InputPortOpAdaptor(InputPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InputPortOp : public ::mlir::Op<InputPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::PortRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ClassOp, ContainerOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::PortOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InputPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InputPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InputPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InputPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InputPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("type")};
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

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.port.input");
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

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Type getPortType() {
    return getTypeAttr().getValue();
  }

  static kanagawa::Direction getPortDirection();

  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results) {
    Adaptor adaptor(operands, attrs, properties, regions);
    results.push_back(PortRefType::get(context, adaptor.getType(),
                      getPortDirection()));
    return success();
  }

  // For hw:InnerSymbol - the symbol targets the operation and not any result.
  static std::optional<size_t> getTargetResultIndex() {
    return std::nullopt;
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::InputPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InputPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InputWireOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InputWireOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
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
  InputWireOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.wire.input", odsAttrs.getContext());
  }

  InputWireOpGenericAdaptorBase(InputWireOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class InputWireOpGenericAdaptor : public detail::InputWireOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InputWireOpGenericAdaptorBase;
public:
  InputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InputWireOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InputWireOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InputWireOpGenericAdaptor(RangeT values, const InputWireOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InputWireOp, typename = std::enable_if_t<std::is_same_v<LateInst, InputWireOp>>>
  InputWireOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InputWireOpAdaptor : public InputWireOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InputWireOpGenericAdaptor::InputWireOpGenericAdaptor;
  InputWireOpAdaptor(InputWireOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InputWireOp : public ::mlir::Op<InputWireOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ClassOp, ContainerOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::PortOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InputWireOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InputWireOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InputWireOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InputWireOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InputWireOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InputWireOp>::getTargetResult;
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
    return ::llvm::StringLiteral("kanagawa.wire.input");
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

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name = nullptr);
  static InputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name = nullptr);
  static InputWireOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static InputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static InputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static InputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static InputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(InputWireOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  Type getPortType() {
    return getPort().getType();
  }

  static kanagawa::Direction getPortDirection();
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::InputWireOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InputWireOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using targetNameTy = ::circt::hw::InnerRefAttr;
    targetNameTy targetName;

    auto getTargetName() const {
      auto &propStorage = this->targetName;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setTargetName(const ::circt::hw::InnerRefAttr &propValue) {
      this->targetName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.targetName == this->targetName &&
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
      odsOpName.emplace("kanagawa.instance", odsAttrs.getContext());
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

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::circt::hw::InnerRefAttr getTargetNameAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().targetName);
    return attr;
  }

  ::circt::hw::InnerRefAttr getTargetName();
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
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::ScopeRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::circt::igraph::InstanceOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getTargetResult;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("targetName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTargetNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTargetNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.instance");
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

  ::mlir::TypedValue<::circt::kanagawa::ScopeRefType> getScopeRef() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::ScopeRefType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::circt::hw::InnerRefAttr getTargetNameAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().targetName);
  }

  ::circt::hw::InnerRefAttr getTargetName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setTargetNameAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().targetName = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static std::optional<size_t> getTargetResultIndex();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  // Return the class this instance is instantiating.
  ClassOp getClass(const hw::InnerRefNamespace &);

  llvm::StringRef getInstanceName() {
    return getInnerSym().getSymName().strref();
  }

  mlir::StringAttr getInstanceNameAttr() {
    return getInnerSymAttr().getSymName();
  }

  StringAttr getReferencedModuleNameAttr() {
    return getTargetNameAttr().getName();
  }

  // Operation* getReferencedModuleSlow();
  Operation* getReferencedModule(const hw::InnerRefNamespace &);
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::IsolatedStaticBlockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IsolatedStaticBlockOpGenericAdaptorBase {
public:
  struct Properties {
    using maxThreadsTy = ::mlir::IntegerAttr;
    maxThreadsTy maxThreads;

    auto getMaxThreads() const {
      auto &propStorage = this->maxThreads;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setMaxThreads(const ::mlir::IntegerAttr &propValue) {
      this->maxThreads = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.maxThreads == this->maxThreads &&
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
  IsolatedStaticBlockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock.isolated", odsAttrs.getContext());
  }

  IsolatedStaticBlockOpGenericAdaptorBase(IsolatedStaticBlockOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getMaxThreadsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
    return attr;
  }

  ::std::optional<uint64_t> getMaxThreads();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class IsolatedStaticBlockOpGenericAdaptor : public detail::IsolatedStaticBlockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IsolatedStaticBlockOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  IsolatedStaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IsolatedStaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : IsolatedStaticBlockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IsolatedStaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IsolatedStaticBlockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IsolatedStaticBlockOpGenericAdaptor(RangeT values, const IsolatedStaticBlockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IsolatedStaticBlockOp, typename = std::enable_if_t<std::is_same_v<LateInst, IsolatedStaticBlockOp>>>
  IsolatedStaticBlockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class IsolatedStaticBlockOpAdaptor : public IsolatedStaticBlockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IsolatedStaticBlockOpGenericAdaptor::IsolatedStaticBlockOpGenericAdaptor;
  IsolatedStaticBlockOpAdaptor(IsolatedStaticBlockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IsolatedStaticBlockOp : public ::mlir::Op<IsolatedStaticBlockOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<BlockReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::AutomaticAllocationScope, circt::kanagawa::BlockOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IsolatedStaticBlockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IsolatedStaticBlockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("maxThreads")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMaxThreadsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMaxThreadsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock.isolated");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getMaxThreadsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
  }

  ::std::optional<uint64_t> getMaxThreads();
  void setMaxThreadsAttr(::mlir::IntegerAttr attr) {
    getProperties().maxThreads = attr;
  }

  void setMaxThreads(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeMaxThreadsAttr() {
      auto attr = getProperties().maxThreads;
      getProperties().maxThreads = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static IsolatedStaticBlockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static IsolatedStaticBlockOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
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
  llvm::SmallVector<Type> getInternalResultTypes() {
    llvm::SmallVector<Type> outTypes;
    llvm::copy(getResultTypes(), std::back_inserter(outTypes));
    return outTypes;
  }

  // Return the body of this block.
  Block* getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::IsolatedStaticBlockOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::IsolatedStaticBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::MethodOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MethodOpGenericAdaptorBase {
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
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
        rhs.argNames == this->argNames &&
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.inner_sym == this->inner_sym &&
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
  MethodOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.method", odsAttrs.getContext());
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

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
    return attr;
  }

  ::mlir::ArrayAttr getArgNames();
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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class MethodOpGenericAdaptor : public detail::MethodOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MethodOpGenericAdaptorBase;
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
class MethodOp : public ::mlir::Op<MethodOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ClassOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::MethodLikeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MethodOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MethodOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<MethodOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<MethodOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MethodOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<MethodOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argNames"), ::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("res_attrs")};
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

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.method");
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().argNames = attr;
  }

  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  StringAttr getMethodName() {
    return getInnerSymAttr().getSymName();
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::MethodOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::MethodOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::OutputPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OutputPortOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
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
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.type == this->type &&
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
  OutputPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.port.output", odsAttrs.getContext());
  }

  OutputPortOpGenericAdaptorBase(OutputPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class OutputPortOpGenericAdaptor : public detail::OutputPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OutputPortOpGenericAdaptorBase;
public:
  OutputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OutputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OutputPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OutputPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OutputPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OutputPortOpGenericAdaptor(RangeT values, const OutputPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OutputPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, OutputPortOp>>>
  OutputPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OutputPortOpAdaptor : public OutputPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OutputPortOpGenericAdaptor::OutputPortOpGenericAdaptor;
  OutputPortOpAdaptor(OutputPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OutputPortOp : public ::mlir::Op<OutputPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::PortRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ClassOp, ContainerOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::PortOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutputPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutputPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<OutputPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<OutputPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<OutputPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("type")};
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

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.port.output");
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

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(OutputPortOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  Type getPortType() {
    return getTypeAttr().getValue();
  }

  static kanagawa::Direction getPortDirection();

  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results) {
    Adaptor adaptor(operands, attrs, properties, regions);
    results.push_back(PortRefType::get(context, adaptor.getType(),
                      getPortDirection()));
    return success();
  }

  // For hw:InnerSymbol - the symbol targets the operation and not any result.
  static std::optional<size_t> getTargetResultIndex() {
    return std::nullopt;
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::OutputPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::OutputPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::OutputWireOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OutputWireOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
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
  OutputWireOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.wire.output", odsAttrs.getContext());
  }

  OutputWireOpGenericAdaptorBase(OutputWireOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class OutputWireOpGenericAdaptor : public detail::OutputWireOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OutputWireOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  OutputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OutputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OutputWireOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OutputWireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OutputWireOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OutputWireOpGenericAdaptor(RangeT values, const OutputWireOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OutputWireOp, typename = std::enable_if_t<std::is_same_v<LateInst, OutputWireOp>>>
  OutputWireOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OutputWireOpAdaptor : public OutputWireOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OutputWireOpGenericAdaptor::OutputWireOpGenericAdaptor;
  OutputWireOpAdaptor(OutputWireOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OutputWireOp : public ::mlir::Op<OutputWireOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::PortRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<ClassOp, ContainerOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, circt::kanagawa::NamedInnerSymbolInterface::Trait, circt::kanagawa::PortOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutputWireOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutputWireOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<OutputWireOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<OutputWireOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<OutputWireOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<OutputWireOp>::getTargetResult;
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
    return ::llvm::StringLiteral("kanagawa.wire.output");
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

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputWireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputWireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(OutputWireOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  Type getPortType() {
    return getPort().getType();
  }

  static kanagawa::Direction getPortDirection();
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::OutputWireOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::OutputWireOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PathOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PathOpGenericAdaptorBase {
public:
  struct Properties {
    using pathTy = ::mlir::ArrayAttr;
    pathTy path;

    auto getPath() const {
      auto &propStorage = this->path;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPath(const ::mlir::ArrayAttr &propValue) {
      this->path = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.path == this->path &&
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
  PathOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.path", odsAttrs.getContext());
  }

  PathOpGenericAdaptorBase(PathOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getPathAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().path);
    return attr;
  }

  ::mlir::ArrayAttr getPath();
};

} // namespace detail
template <typename RangeT>
class PathOpGenericAdaptor : public detail::PathOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PathOpGenericAdaptorBase;
public:
  PathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PathOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PathOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PathOpGenericAdaptor(RangeT values, const PathOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PathOp, typename = std::enable_if_t<std::is_same_v<LateInst, PathOp>>>
  PathOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PathOpAdaptor : public PathOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PathOpGenericAdaptor::PathOpGenericAdaptor;
  PathOpAdaptor(PathOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PathOp : public ::mlir::Op<PathOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::kanagawa::ScopeRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PathOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PathOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PathOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PathOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PathOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("path")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPathAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.path");
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

  ::mlir::TypedValue<::circt::kanagawa::ScopeRefType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::ScopeRefType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getPathAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().path);
  }

  ::mlir::ArrayAttr getPath();
  void setPathAttr(::mlir::ArrayAttr attr) {
    getProperties().path = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instance, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instance, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instance, ::mlir::ArrayAttr path);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr path);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path);
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(PathOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results);

  auto getPathAsRange() {
    return getPath().getAsRange<PathStepAttr>();
  }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PathOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::PathOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PipelineHeaderOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PipelineHeaderOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PipelineHeaderOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.pipeline.header", odsAttrs.getContext());
  }

  PipelineHeaderOpGenericAdaptorBase(PipelineHeaderOp op);

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
class PipelineHeaderOpGenericAdaptor : public detail::PipelineHeaderOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PipelineHeaderOpGenericAdaptorBase;
public:
  PipelineHeaderOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PipelineHeaderOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PipelineHeaderOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PipelineHeaderOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PipelineHeaderOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PipelineHeaderOpGenericAdaptor(RangeT values, const PipelineHeaderOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PipelineHeaderOp, typename = std::enable_if_t<std::is_same_v<LateInst, PipelineHeaderOp>>>
  PipelineHeaderOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PipelineHeaderOpAdaptor : public PipelineHeaderOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PipelineHeaderOpGenericAdaptor::PipelineHeaderOpGenericAdaptor;
  PipelineHeaderOpAdaptor(PipelineHeaderOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PipelineHeaderOp : public ::mlir::Op<PipelineHeaderOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<4>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PipelineHeaderOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PipelineHeaderOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.pipeline.header");
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

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getStall() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall);
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall);
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineHeaderOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineHeaderOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PipelineHeaderOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PortReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PortReadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PortReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.port.read", odsAttrs.getContext());
  }

  PortReadOpGenericAdaptorBase(PortReadOp op);

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
class PortReadOpGenericAdaptor : public detail::PortReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PortReadOpGenericAdaptorBase;
  static constexpr int odsIndex_port = 0;
public:
  PortReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PortReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PortReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PortReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PortReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PortReadOpGenericAdaptor(RangeT values, const PortReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PortReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, PortReadOp>>>
  PortReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPort() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PortReadOpAdaptor : public PortReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PortReadOpGenericAdaptor::PortReadOpGenericAdaptor;
  PortReadOpAdaptor(PortReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PortReadOp : public ::mlir::Op<PortReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PortReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PortReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_port = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PortReadOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PortReadOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PortReadOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.port.read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPortMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value port);
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value port);
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value port);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port);
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port);
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port);
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port);
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortReadOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PortWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PortWriteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PortWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.port.write", odsAttrs.getContext());
  }

  PortWriteOpGenericAdaptorBase(PortWriteOp op);

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
class PortWriteOpGenericAdaptor : public detail::PortWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PortWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_port = 0;
  static constexpr int odsIndex_value = 1;
public:
  PortWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PortWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PortWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PortWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PortWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PortWriteOpGenericAdaptor(RangeT values, const PortWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PortWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, PortWriteOp>>>
  PortWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPort() {
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
class PortWriteOpAdaptor : public PortWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PortWriteOpGenericAdaptor::PortWriteOpGenericAdaptor;
  PortWriteOpAdaptor(PortWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PortWriteOp : public ::mlir::Op<PortWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PortWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PortWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_port = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.port.write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::kanagawa::PortRefType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::kanagawa::PortRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getPortMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port, ::mlir::Value value);
  static PortWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port, ::mlir::Value value);
  static PortWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value);
  static PortWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value);
  static PortWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PortWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PortWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortWriteOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ReturnOp declarations
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
      odsOpName.emplace("kanagawa.return", odsAttrs.getContext());
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
  static constexpr int odsIndex_retValues = 0;
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

  RangeT getRetValues() {
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<MethodOp, DataflowMethodOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_retValues = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getRetValues() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getRetValuesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange retValues);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange retValues);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange retValues);
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

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::ReturnOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::StaticBlockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticBlockOpGenericAdaptorBase {
public:
  struct Properties {
    using maxThreadsTy = ::mlir::IntegerAttr;
    maxThreadsTy maxThreads;

    auto getMaxThreads() const {
      auto &propStorage = this->maxThreads;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setMaxThreads(const ::mlir::IntegerAttr &propValue) {
      this->maxThreads = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.maxThreads == this->maxThreads &&
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
  StaticBlockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.sblock", odsAttrs.getContext());
  }

  StaticBlockOpGenericAdaptorBase(StaticBlockOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getMaxThreadsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
    return attr;
  }

  ::std::optional<uint64_t> getMaxThreads();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticBlockOpGenericAdaptor : public detail::StaticBlockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticBlockOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  StaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticBlockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticBlockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticBlockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticBlockOpGenericAdaptor(RangeT values, const StaticBlockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticBlockOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticBlockOp>>>
  StaticBlockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StaticBlockOpAdaptor : public StaticBlockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticBlockOpGenericAdaptor::StaticBlockOpGenericAdaptor;
  StaticBlockOpAdaptor(StaticBlockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticBlockOp : public ::mlir::Op<StaticBlockOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<BlockReturnOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, circt::kanagawa::BlockOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticBlockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticBlockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("maxThreads")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getMaxThreadsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getMaxThreadsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.sblock");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getMaxThreadsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().maxThreads);
  }

  ::std::optional<uint64_t> getMaxThreads();
  void setMaxThreadsAttr(::mlir::IntegerAttr attr) {
    getProperties().maxThreads = attr;
  }

  void setMaxThreads(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeMaxThreadsAttr() {
      auto attr = getProperties().maxThreads;
      getProperties().maxThreads = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static StaticBlockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
  static StaticBlockOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads = {});
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
  llvm::SmallVector<Type> getInternalResultTypes() {
    llvm::SmallVector<Type> outTypes;
    llvm::copy(getResultTypes(), std::back_inserter(outTypes));
    return outTypes;
  }

  // Return the body of this block.
  Block* getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::StaticBlockOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::StaticBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::VarOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VarOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.type == this->type &&
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
  VarOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("kanagawa.var", odsAttrs.getContext());
  }

  VarOpGenericAdaptorBase(VarOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  MemRefType getType();
};

} // namespace detail
template <typename RangeT>
class VarOpGenericAdaptor : public detail::VarOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VarOpGenericAdaptorBase;
public:
  VarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : VarOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VarOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VarOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VarOpGenericAdaptor(RangeT values, const VarOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VarOp, typename = std::enable_if_t<std::is_same_v<LateInst, VarOp>>>
  VarOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class VarOpAdaptor : public VarOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VarOpGenericAdaptor::VarOpGenericAdaptor;
  VarOpAdaptor(VarOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VarOp : public ::mlir::Op<VarOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VarOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VarOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<VarOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("kanagawa.var");
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::cast<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::circt::hw::InnerSymAttr getInnerSym();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  MemRefType getType();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static VarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static VarOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static VarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static VarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VarOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VarOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::VarOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::VarOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

