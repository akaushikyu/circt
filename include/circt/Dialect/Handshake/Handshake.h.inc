/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Handshake.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::handshake {

/// branch operation
/// The branch operation represents an unconditional
/// branch.  The single data input is propagated to the single
/// successor.  The input must be triggered by some predecessor to
/// avoid continous triggering of a successor block.
/// 
/// Example:
/// ```mlir
/// %1 = br %0 : i32
/// ```
class BranchOp;

} // namespace circt::handshake
namespace circt::handshake {

/// buffer operation
/// The buffer operation represents a buffer operation. $slots
/// must be an unsigned integer larger than 0. $bufferType=BufferTypeEnum::seq indicates a
/// nontransparent buffer, while $bufferType=BufferTypeEnum::fifo indicates a transparent
/// buffer.
/// 
/// An 'initValues' attribute containing a list of integer values may be provided.
/// The list must be of the same length as the number of slots. This will
/// initialize the buffer with the given values upon reset.
/// For now, only sequential buffers are allowed to have initial values.
/// @todo: How to support different init types? these have to be stored (and
/// retrieved) as attributes, hence they must be of a known type.
class BufferOp;

} // namespace circt::handshake
namespace circt::handshake {

/// conditional branch operation
/// The cbranch operation represents a conditional
/// branch.  The data input is propagated to one of the two outputs
/// based on the condition input.
/// 
/// Example:
/// ```mlir
/// %true, %false = conditional_branch %cond, %data : i32
/// ```
class ConditionalBranchOp;

} // namespace circt::handshake
namespace circt::handshake {

/// constant operation
/// The const has a constant value. When triggered by its
/// single `ctrl` input, it sends the constant value to its single
/// successor.
/// 
/// Example:
/// ```mlir
/// %0 = constant %ctrl {value = 42 : i32} : i32
/// ```
class ConstantOp;

} // namespace circt::handshake
namespace circt::handshake {

/// control merge operation
/// The control_merge operation represents a
/// (nondeterministic) control merge.  Any input is propagated to the
/// first output and the index of the propagated input is sent to the
/// second output.  The number of inputs corresponds to the number of
/// predecessor blocks.
/// 
/// Example:
/// ```
/// %0, %idx = control_merge %a, %b, %c {attributes} : i32, index
/// ```
class ControlMergeOp;

} // namespace circt::handshake
namespace circt::handshake {

/// Instantiate a Handshake circuit
/// Instantiate (call) a Handshake function in a non-Handshake design using ESI
/// channels as the outside connections.
class ESIInstanceOp;

} // namespace circt::handshake
namespace circt::handshake {

/// external memory
/// An ExternalMemoryOp represents a wrapper around a memref input to a
/// handshake function. The semantics of the load/store operands are identical
/// to what is decribed for MemoryOp. The only difference is that the first
/// operand to this operand is a `memref` value.
/// Upon lowering to FIRRTL, a handshake interface will be created in the
/// top-level component for each load- and store which connected to this memory.
/// 
/// Example:
/// 
/// ```mlir
/// handshake.func @main(%i: index, %v: i32, %mem : memref<10xi32>, %ctrl: none) -> none {
///   %stCtrl = extmemory[ld = 0, st = 1](%mem : memref<10xi32>)(%vout, %addr) {id = 0 : i32} : (i32, index) -> (none)
///   %vout, %addr = store(%v, %i, %ctrl) : (i32, index, none) -> (i32, index)
///   ...
/// }
/// ```
class ExternalMemoryOp;

} // namespace circt::handshake
namespace circt::handshake {

/// fork operation
/// The fork operation represents a fork operation.  A
/// single input is replicated to N outputs and distributed to each
/// output as soon as the corresponding successor is available.
/// 
/// Example:
/// ```mlir
/// %1:2 = fork [2] %0 : i32
/// ```
class ForkOp;

} // namespace circt::handshake
namespace circt::handshake {

/// Handshake dialect function.
/// The func operation represents a handshaked function.
/// This is almost exactly like a standard FuncOp, except that it has
/// some extra verification conditions. In particular, each Value must
/// only have a single use.
class FuncOp;

} // namespace circt::handshake
namespace circt::handshake {

/// module instantiate operation
/// The `instance` operation represents the instantiation of a module.  This
/// is similar to a function call, except that different instances of the
/// same module are guaranteed to have their own distinct state.
/// The instantiated module is encoded as a symbol reference attribute named
/// "module". An instance operation takes a control input as its last argument
/// and returns a control output as its last result.
/// 
/// Example:
/// ```mlir
/// %2:2 = handshake.instance @my_add(%0, %1, %ctrl) : (f32, f32, none) -> (f32, none)
/// ```
class InstanceOp;

} // namespace circt::handshake
namespace circt::handshake {

/// join operation
/// A control-only synchronizer.  Produces a valid output when all
/// inputs become available.
/// 
/// Example:
/// ```mlir
/// %0 = join %a, %b, %c : i32, i1, none
/// ```
class JoinOp;

} // namespace circt::handshake
namespace circt::handshake {

/// lazy fork operation
/// The lazy_fork operation represents a lazy fork operation.
/// A single input is replicated to N outputs and distributed to each
/// output when all successors are available.
/// 
/// Example:
/// ```mlir
/// %1:2 = lazy_fork [2] %0 : i32
/// ```
class LazyForkOp;

} // namespace circt::handshake
namespace circt::handshake {

/// load operation
///  Load memory port, sends load requests to MemoryOp. From dataflow
///  predecessor, receives address indices and a control-only value
///  which signals completion of all previous memory accesses which
///  target the same memory.  When all inputs are received, the load
///  sends the address indices to MemoryOp. When the MemoryOp returns
///  a piece of data, the load sends it to its dataflow successor.
/// 
///  Operands: address indices (from predecessor), data (from MemoryOp), control-only input.
///  Results: data (to successor), address indices (to MemoryOp).
/// 
/// Example:
/// ```mlir
/// %dataToSucc, %addr1ToMem, %addr2ToMem = load [%addr1, %addr2] %dataFromMem, %ctrl : i8, i16, index
/// ```
class LoadOp;

} // namespace circt::handshake
namespace circt::handshake {

/// memory
/// Each MemoryOp represents an independent memory or memory region (BRAM or external memory).
/// It receives memory access requests from load and store operations. For every request,
/// it returns data (for load) and a data-less token indicating completion.
/// The memory op represents a flat, unidimensional memory.
/// Operands: all stores (stdata1, staddr1, stdata2, staddr2, ...), then all loads (ldaddr1, ldaddr2,...)
/// Outputs: all load outputs, ordered the same as
/// load data (lddata1, lddata2, ...), followed by all none outputs,
/// ordered as operands (stnone1, stnone2,...ldnone1, ldnone2,...)
class MemoryOp;

} // namespace circt::handshake
namespace circt::handshake {

/// merge operation
/// The merge operation represents a (nondeterministic)
/// merge operation. Any input is propagated to the single output. The
/// number of inputs corresponds to the number of predecessor
/// blocks.
/// 
/// Example:
/// ```
/// %0 = merge %a, %b, %c : i32
/// ```
class MergeOp;

} // namespace circt::handshake
namespace circt::handshake {

/// mux operation
/// The mux operation represents a(deterministic) merge operation.
/// Operands: select, data0, data1, data2, ...
/// 
/// The 'select' operand is received from ControlMerge of the same
/// block and it represents the index of the data operand that the mux
/// should propagate to its single output.  The number of data inputs
/// corresponds to the number of predecessor blocks.
/// 
/// The mux operation is intended solely for control+dataflow selection.
/// For purely dataflow selection, use the 'select' operation instead.
/// 
/// Example:
/// ```mlir
/// %0 = mux %select [%data0, %data1, %data2] {attributes}: index, i32
/// ```
class MuxOp;

} // namespace circt::handshake
namespace circt::handshake {

/// never operation
/// The never operation represents disconnected data
/// source. The source never sets any 'valid' signal which will
/// never trigger the successor at any point in time.
class NeverOp;

} // namespace circt::handshake
namespace circt::handshake {

/// packs a tuple
/// The `pack` operation constructs a tuple from separate values.
/// The number of operands corresponds to the number of tuple elements.
/// Similar to `join`, the output is ready when all inputs are ready.
/// 
/// Example:
/// ```mlir
/// %tuple = handshake.pack %a, %b {attributes} : tuple<i32, i64>
/// ```
class PackOp;

} // namespace circt::handshake
namespace circt::handshake {

/// Handshake dialect return.
/// The return operation represents a handshaked
/// function.  This is almost exactly like a standard ReturnOp, except
/// that it exists in a handshake.func.  It has the same operands as
/// standard ReturnOp which it replaces and an additional control -
/// only operand(exit point of control - only network).
class ReturnOp;

} // namespace circt::handshake
namespace circt::handshake {

/// sink operation
/// The sink operation discards any data that arrives at its
///      input.The sink has no successors and it can continuously consume data.
/// 
/// Example:
/// ```mlir
/// sink %data : i32
/// ```
class SinkOp;

} // namespace circt::handshake
namespace circt::handshake {

/// source operation
/// The source operation represents continuous token
/// source.  The source continously sets a 'valid' signal which the
/// successor can consume at any point in time.
class SourceOp;

} // namespace circt::handshake
namespace circt::handshake {

/// store operation
/// Store memory port, sends store requests to MemoryOp. From dataflow
/// predecessors, receives address indices, data, and a control-only
/// value which signals completion of all previous memory accesses
/// which target the same memory.  When all inputs are received, the
/// store sends the address and data to MemoryOp.
/// 
/// Operands: address indices, data, control-only input.
/// Results: data and address indices (sent to MemoryOp).
/// Types: data type followed by address type.
/// 
/// Example:
/// ```mlir
/// %dataToMem, %addrToMem = store [%addr1, %addr2] %dataFromPred , %ctrl : i8, i16, index
/// ```
class StoreOp;

} // namespace circt::handshake
namespace circt::handshake {

/// sync operation
/// Synchronizes an arbitrary set of inputs. Synchronization implies applying
/// join semantics in between all in- and output ports.
/// 
/// Example:
/// ```mlir
/// %aSynced, %bSynced, %cSynced = sync %a, %b, %c : i32, i1, none
/// ```
class SyncOp;

} // namespace circt::handshake
namespace circt::handshake {

/// unpacks a tuple
/// The `unpack` operation assigns each value of a tuple to a separate
/// value for further processing. The number of results corresponds
/// to the number of tuple elements.
/// Similar to `fork`, each output is distributed as soon as the corresponding
/// successor is ready.
/// 
/// Example:
/// ```mlir
/// %a, %b = handshake.unpack %tuple {attributes} : tuple<i32, i64>
/// ```
class UnpackOp;

} // namespace circt::handshake
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::BranchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BranchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BranchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.br", odsAttrs.getContext());
  }

  BranchOpGenericAdaptorBase(BranchOp op);

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
class BranchOpGenericAdaptor : public detail::BranchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BranchOpGenericAdaptorBase;
  static constexpr int odsIndex_dataOperand = 0;
public:
  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BranchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BranchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BranchOpGenericAdaptor(RangeT values, const BranchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BranchOp, typename = std::enable_if_t<std::is_same_v<LateInst, BranchOp>>>
  BranchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDataOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BranchOpAdaptor : public BranchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BranchOpGenericAdaptor::BranchOpGenericAdaptor;
  BranchOpAdaptor(BranchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BranchOp : public ::mlir::Op<BranchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BranchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BranchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dataOperand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::SOSTInterface::Trait<BranchOp>::getDataType;
  using ::circt::handshake::SOSTInterface::Trait<BranchOp>::getSize;
  using ::circt::handshake::SOSTInterface::Trait<BranchOp>::sostPrint;
  using ::circt::handshake::NamedIOInterface::Trait<BranchOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<BranchOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<BranchOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.br");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDataOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getDataOperandMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getDataResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dataResult, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataResult, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataResult, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dataOperand);
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  bool sostIsControl();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::BranchOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::BufferOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BufferOpGenericAdaptorBase {
public:
  struct Properties {
    using bufferTypeTy = ::circt::handshake::BufferTypeEnumAttr;
    bufferTypeTy bufferType;

    auto getBufferType() const {
      auto &propStorage = this->bufferType;
      return ::llvm::cast<::circt::handshake::BufferTypeEnumAttr>(propStorage);
    }
    void setBufferType(const ::circt::handshake::BufferTypeEnumAttr &propValue) {
      this->bufferType = propValue;
    }
    using initValuesTy = ::mlir::ArrayAttr;
    initValuesTy initValues;

    auto getInitValues() const {
      auto &propStorage = this->initValues;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setInitValues(const ::mlir::ArrayAttr &propValue) {
      this->initValues = propValue;
    }
    using slotsTy = ::mlir::IntegerAttr;
    slotsTy slots;

    auto getSlots() const {
      auto &propStorage = this->slots;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setSlots(const ::mlir::IntegerAttr &propValue) {
      this->slots = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.bufferType == this->bufferType &&
        rhs.initValues == this->initValues &&
        rhs.slots == this->slots &&
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
  BufferOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.buffer", odsAttrs.getContext());
  }

  BufferOpGenericAdaptorBase(BufferOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getSlotsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().slots);
    return attr;
  }

  uint32_t getSlots();
  ::circt::handshake::BufferTypeEnumAttr getBufferTypeAttr() {
    auto attr = ::llvm::cast<::circt::handshake::BufferTypeEnumAttr>(getProperties().bufferType);
    return attr;
  }

  ::BufferTypeEnum getBufferType();
  ::mlir::ArrayAttr getInitValuesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().initValues);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getInitValues();
};

} // namespace detail
template <typename RangeT>
class BufferOpGenericAdaptor : public detail::BufferOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BufferOpGenericAdaptorBase;
  static constexpr int odsIndex_operand = 0;
public:
  BufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BufferOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BufferOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BufferOpGenericAdaptor(RangeT values, const BufferOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BufferOp, typename = std::enable_if_t<std::is_same_v<LateInst, BufferOp>>>
  BufferOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BufferOpAdaptor : public BufferOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BufferOpGenericAdaptor::BufferOpGenericAdaptor;
  BufferOpAdaptor(BufferOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BufferOp : public ::mlir::Op<BufferOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::HasClock, ::mlir::OpTrait::SameOperandsAndResultType, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BufferOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BufferOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::SOSTInterface::Trait<BufferOp>::getDataType;
  using ::circt::handshake::SOSTInterface::Trait<BufferOp>::sostIsControl;
  using ::circt::handshake::SOSTInterface::Trait<BufferOp>::sostPrint;
  using ::circt::handshake::NamedIOInterface::Trait<BufferOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<BufferOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<BufferOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bufferType"), ::llvm::StringRef("initValues"), ::llvm::StringRef("slots")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBufferTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBufferTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInitValuesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInitValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSlotsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSlotsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.buffer");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandMutable() {
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
  ::mlir::IntegerAttr getSlotsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().slots);
  }

  uint32_t getSlots();
  ::circt::handshake::BufferTypeEnumAttr getBufferTypeAttr() {
    return ::llvm::cast<::circt::handshake::BufferTypeEnumAttr>(getProperties().bufferType);
  }

  ::BufferTypeEnum getBufferType();
  ::mlir::ArrayAttr getInitValuesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().initValues);
  }

  ::std::optional< ::mlir::ArrayAttr > getInitValues();
  void setSlotsAttr(::mlir::IntegerAttr attr) {
    getProperties().slots = attr;
  }

  void setSlots(uint32_t attrValue);
  void setBufferTypeAttr(::circt::handshake::BufferTypeEnumAttr attr) {
    getProperties().bufferType = attr;
  }

  void setBufferType(::BufferTypeEnum attrValue);
  void setInitValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().initValues = attr;
  }

  ::mlir::Attribute removeInitValuesAttr() {
      auto attr = getProperties().initValues;
      getProperties().initValues = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value operand, int slots, BufferTypeEnum bufferType);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value operand, int slots, BufferTypeEnum bufferType);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, Value operand, int slots, BufferTypeEnum bufferType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value operand, ::mlir::IntegerAttr slots, ::circt::handshake::BufferTypeEnumAttr bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value operand, uint32_t slots, ::BufferTypeEnum bufferType, /*optional*/::mlir::ArrayAttr initValues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  unsigned getSize();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  bool isSequential() {
    return this->getBufferType() == BufferTypeEnum::seq;
  }
  int getNumSlots() {
    return (*this)->getAttrOfType<IntegerAttr>("slots").getValue().getZExtValue();
  }
  SmallVector<int64_t> getInitValueArray() {
    assert(getInitValues() && "initValues attribute not set");
    SmallVector<int64_t> values;
    for (auto value : (*this)->getAttrOfType<ArrayAttr>("initValues"))
      values.push_back(llvm::cast<IntegerAttr>(value)
                       .getValue().getSExtValue());
    return values;
  }

};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::BufferOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::BufferOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ConditionalBranchOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConditionalBranchOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ConditionalBranchOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.cond_br", odsAttrs.getContext());
  }

  ConditionalBranchOpGenericAdaptorBase(ConditionalBranchOp op);

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
class ConditionalBranchOpGenericAdaptor : public detail::ConditionalBranchOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConditionalBranchOpGenericAdaptorBase;
  static constexpr int odsIndex_conditionOperand = 0;
  static constexpr int odsIndex_dataOperand = 1;
public:
  ConditionalBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConditionalBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConditionalBranchOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConditionalBranchOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConditionalBranchOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConditionalBranchOpGenericAdaptor(RangeT values, const ConditionalBranchOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConditionalBranchOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConditionalBranchOp>>>
  ConditionalBranchOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getConditionOperand() {
    return (*getODSOperands(0).begin());
  }

  ValueT getDataOperand() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ConditionalBranchOpAdaptor : public ConditionalBranchOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConditionalBranchOpGenericAdaptor::ConditionalBranchOpGenericAdaptor;
  ConditionalBranchOpAdaptor(ConditionalBranchOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConditionalBranchOp : public ::mlir::Op<ConditionalBranchOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConditionalBranchOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConditionalBranchOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_conditionOperand = 0;
  static constexpr int odsIndex_dataOperand = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<ConditionalBranchOp>::refineReturnTypes;
  using ::circt::handshake::NamedIOInterface::Trait<ConditionalBranchOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<ConditionalBranchOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<ConditionalBranchOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.cond_br");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getConditionOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getDataOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getConditionOperandMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDataOperandMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getTrueResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getFalseResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type trueResult, ::mlir::Type falseResult, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type trueResult, ::mlir::Type falseResult, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type trueResult, ::mlir::Type falseResult, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value conditionOperand, ::mlir::Value dataOperand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionalBranchOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConditionalBranchOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  bool isControl();
  std::string getOperandName(unsigned idx);
  std::string getResultName(unsigned idx);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  // These are the indices into the dests list.
  enum { trueIndex = 0, falseIndex = 1 };
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ConditionalBranchOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::TypedAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::TypedAttr>(propStorage);
    }
    void setValue(const ::mlir::TypedAttr &propValue) {
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
      odsOpName.emplace("handshake.constant", odsAttrs.getContext());
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

  ::mlir::TypedAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
    return attr;
  }

  ::mlir::TypedAttr getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantOpGenericAdaptor : public detail::ConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantOpGenericAdaptorBase;
  static constexpr int odsIndex_ctrl = 0;
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

  ValueT getCtrl() {
    return (*getODSOperands(0).begin());
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
class ConstantOp : public ::mlir::Op<ConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ctrl = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<ConstantOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<ConstantOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<ConstantOp>::isControl;
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
    return ::llvm::StringLiteral("handshake.constant");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::NoneType> getCtrl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::NoneType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getCtrlMutable() {
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
  ::mlir::TypedAttr getValueAttr() {
    return ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
  }

  ::mlir::TypedAttr getValue();
  void setValueAttr(::mlir::TypedAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypedAttr value, ::mlir::Value ctrl);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  std::string getOperandName(unsigned idx);
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

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::ConstantOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ControlMergeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ControlMergeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ControlMergeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.control_merge", odsAttrs.getContext());
  }

  ControlMergeOpGenericAdaptorBase(ControlMergeOp op);

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
class ControlMergeOpGenericAdaptor : public detail::ControlMergeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ControlMergeOpGenericAdaptorBase;
  static constexpr int odsIndex_dataOperands = 0;
public:
  ControlMergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ControlMergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ControlMergeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ControlMergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ControlMergeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ControlMergeOpGenericAdaptor(RangeT values, const ControlMergeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ControlMergeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ControlMergeOp>>>
  ControlMergeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDataOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ControlMergeOpAdaptor : public ControlMergeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ControlMergeOpGenericAdaptor::ControlMergeOpGenericAdaptor;
  ControlMergeOpAdaptor(ControlMergeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ControlMergeOp : public ::mlir::Op<ControlMergeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::MergeLikeOpInterface::Trait, ::mlir::OpTrait::HasClock, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ControlMergeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ControlMergeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dataOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<ControlMergeOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<ControlMergeOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<ControlMergeOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.control_merge");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDataOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDataOperandsMutable();
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

  ::mlir::TypedValue<::mlir::Type> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange operands, Type indexType = {});
  static ControlMergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange operands, Type indexType = {});
  static ControlMergeOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange operands, Type indexType = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Type index, ::mlir::ValueRange dataOperands);
  static ControlMergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Type index, ::mlir::ValueRange dataOperands);
  static ControlMergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Type index, ::mlir::ValueRange dataOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlMergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ControlMergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlMergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ControlMergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  std::string getResultName(unsigned idx);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ControlMergeOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ESIInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ESIInstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using instNameTy = ::mlir::StringAttr;
    instNameTy instName;

    auto getInstName() const {
      auto &propStorage = this->instName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInstName(const ::mlir::StringAttr &propValue) {
      this->instName = propValue;
    }
    using moduleTy = ::mlir::FlatSymbolRefAttr;
    moduleTy module;

    auto getModule() const {
      auto &propStorage = this->module;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModule(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->module = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.instName == this->instName &&
        rhs.module == this->module &&
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
  ESIInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.esi_instance", odsAttrs.getContext());
  }

  ESIInstanceOpGenericAdaptorBase(ESIInstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().module);
    return attr;
  }

  ::llvm::StringRef getModule();
  ::mlir::StringAttr getInstNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().instName);
    return attr;
  }

  ::llvm::StringRef getInstName();
};

} // namespace detail
template <typename RangeT>
class ESIInstanceOpGenericAdaptor : public detail::ESIInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ESIInstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_opOperands = 2;
public:
  ESIInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ESIInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ESIInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ESIInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ESIInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ESIInstanceOpGenericAdaptor(RangeT values, const ESIInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ESIInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ESIInstanceOp>>>
  ESIInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOpOperands() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ESIInstanceOpAdaptor : public ESIInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ESIInstanceOpGenericAdaptor::ESIInstanceOpGenericAdaptor;
  ESIInstanceOpAdaptor(ESIInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ESIInstanceOp : public ::mlir::Op<ESIInstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::OpTrait::HasClock, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ESIInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ESIInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_opOperands = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("instName"), ::llvm::StringRef("module")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInstNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInstNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.esi_instance");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
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

  ::mlir::Operation::operand_range getOpOperands() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getOpOperandsMutable();
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
  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().module);
  }

  ::llvm::StringRef getModule();
  ::mlir::StringAttr getInstNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().instName);
  }

  ::llvm::StringRef getInstName();
  void setModuleAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().module = attr;
  }

  void setModule(::llvm::StringRef attrValue);
  void setInstNameAttr(::mlir::StringAttr attr) {
    getProperties().instName = attr;
  }

  void setInstName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr module, ::mlir::StringAttr instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static ESIInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr module, ::mlir::StringAttr instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static ESIInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr module, ::mlir::StringAttr instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::llvm::StringRef module, ::llvm::StringRef instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static ESIInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::llvm::StringRef module, ::llvm::StringRef instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static ESIInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::llvm::StringRef module, ::llvm::StringRef instName, ::mlir::Value clk, ::mlir::Value rst, ::mlir::ValueRange opOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
  // Account for `clk` and `rst` operands vs call arguments.
  static constexpr int NumFixedOperands = 2;

  /// Get the argument operands to the called function.
  operand_range getArgOperands() {
    return {arg_operand_begin(), arg_operand_end()};
  }

  operand_iterator arg_operand_begin() { return operand_begin(); }
  operand_iterator arg_operand_end() { return operand_end(); }

  /// Return the module of this operation.
  CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<SymbolRefAttr>("module");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getModuleAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
  }

  MutableOperandRange getArgOperandsMutable() {
    return getOpOperandsMutable();
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

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ESIInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::ESIInstanceOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ExternalMemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExternalMemoryOpGenericAdaptorBase {
public:
  struct Properties {
    using idTy = ::mlir::IntegerAttr;
    idTy id;

    auto getId() const {
      auto &propStorage = this->id;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setId(const ::mlir::IntegerAttr &propValue) {
      this->id = propValue;
    }
    using ldCountTy = ::mlir::IntegerAttr;
    ldCountTy ldCount;

    auto getLdCount() const {
      auto &propStorage = this->ldCount;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLdCount(const ::mlir::IntegerAttr &propValue) {
      this->ldCount = propValue;
    }
    using stCountTy = ::mlir::IntegerAttr;
    stCountTy stCount;

    auto getStCount() const {
      auto &propStorage = this->stCount;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setStCount(const ::mlir::IntegerAttr &propValue) {
      this->stCount = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.id == this->id &&
        rhs.ldCount == this->ldCount &&
        rhs.stCount == this->stCount &&
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
  ExternalMemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.extmemory", odsAttrs.getContext());
  }

  ExternalMemoryOpGenericAdaptorBase(ExternalMemoryOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLdCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().ldCount);
    return attr;
  }

  uint32_t getLdCount();
  ::mlir::IntegerAttr getStCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().stCount);
    return attr;
  }

  uint32_t getStCount();
  ::mlir::IntegerAttr getIdAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().id);
    return attr;
  }

  uint32_t getId();
};

} // namespace detail
template <typename RangeT>
class ExternalMemoryOpGenericAdaptor : public detail::ExternalMemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExternalMemoryOpGenericAdaptorBase;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_inputs = 1;
public:
  ExternalMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExternalMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ExternalMemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExternalMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExternalMemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExternalMemoryOpGenericAdaptor(RangeT values, const ExternalMemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExternalMemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExternalMemoryOp>>>
  ExternalMemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemref() {
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
class ExternalMemoryOpAdaptor : public ExternalMemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExternalMemoryOpGenericAdaptor::ExternalMemoryOpGenericAdaptor;
  ExternalMemoryOpAdaptor(ExternalMemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExternalMemoryOp : public ::mlir::Op<ExternalMemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExternalMemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExternalMemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memref = 0;
  static constexpr int odsIndex_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<ExternalMemoryOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<ExternalMemoryOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<ExternalMemoryOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("id"), ::llvm::StringRef("ldCount"), ::llvm::StringRef("stCount")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLdCountAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLdCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStCountAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.extmemory");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getLdCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().ldCount);
  }

  uint32_t getLdCount();
  ::mlir::IntegerAttr getStCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().stCount);
  }

  uint32_t getStCount();
  ::mlir::IntegerAttr getIdAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().id);
  }

  uint32_t getId();
  void setLdCountAttr(::mlir::IntegerAttr attr) {
    getProperties().ldCount = attr;
  }

  void setLdCount(uint32_t attrValue);
  void setStCountAttr(::mlir::IntegerAttr attr) {
    getProperties().stCount = attr;
  }

  void setStCount(uint32_t attrValue);
  void setIdAttr(::mlir::IntegerAttr attr) {
    getProperties().id = attr;
  }

  void setId(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, ValueRange inputs, int ldCount, int stCount, int id);
  static ExternalMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, ValueRange inputs, int ldCount, int stCount, int id);
  static ExternalMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, ValueRange inputs, int ldCount, int stCount, int id);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  std::string getOperandName(unsigned idx);
  std::string getResultName(unsigned idx);
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
  mlir::MemRefType getMemRefType() {
    return llvm::cast<mlir::MemRefType>(getMemref().getType());
  }

  llvm::SmallVector<handshake::MemLoadInterface> getLoadPorts();
  llvm::SmallVector<handshake::MemStoreInterface> getStorePorts();
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ExternalMemoryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::ExternalMemoryOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ForkOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ForkOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ForkOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.fork", odsAttrs.getContext());
  }

  ForkOpGenericAdaptorBase(ForkOp op);

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
class ForkOpGenericAdaptor : public detail::ForkOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ForkOpGenericAdaptorBase;
  static constexpr int odsIndex_operand = 0;
public:
  ForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ForkOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ForkOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ForkOpGenericAdaptor(RangeT values, const ForkOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ForkOp, typename = std::enable_if_t<std::is_same_v<LateInst, ForkOp>>>
  ForkOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ForkOpAdaptor : public ForkOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ForkOpGenericAdaptor::ForkOpGenericAdaptor;
  ForkOpAdaptor(ForkOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ForkOp : public ::mlir::Op<ForkOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::HasClock, ::mlir::OpTrait::SameOperandsAndResultType, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ForkOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ForkOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::SOSTInterface::Trait<ForkOp>::getDataType;
  using ::circt::handshake::SOSTInterface::Trait<ForkOp>::sostIsControl;
  using ::circt::handshake::SOSTInterface::Trait<ForkOp>::sostPrint;
  using ::circt::handshake::NamedIOInterface::Trait<ForkOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<ForkOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<ForkOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.fork");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value operand, unsigned size);
  static ForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value operand, unsigned size);
  static ForkOp create(::mlir::ImplicitLocOpBuilder &builder, Value operand, unsigned size);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value operand);
  static ForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value operand);
  static ForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value operand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  unsigned getSize();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ForkOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::FuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FuncOpGenericAdaptorBase {
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
  FuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.func", odsAttrs.getContext());
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
class FuncOp : public ::mlir::Op<FuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::HasClock, ::circt::handshake::FineGrainedDataflowRegionOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs")};
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

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.func");
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, FunctionType type, ArrayRef<NamedAttribute> attrs = {});
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
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Add an entry block to an empty function, and set up the block arguments
  // to match the signature of the function.
  Block *addEntryBlock();

  /// Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  /// Returns the region on the current operation that is callable.
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// Returns the names of the arguments to this function.
  ArrayAttr getArgNames() {
    return (*this)->getAttrOfType<ArrayAttr>("argNames");
  }

  /// Returns the names of the results from this function.
  ArrayAttr getResNames() {
    return (*this)->getAttrOfType<ArrayAttr>("resNames");
  }

  /// Returns the argument name at the given index.
  StringAttr getArgName(unsigned idx) {
    return llvm::cast<StringAttr>(getArgNames()[idx]);
  }

  /// Returns the result name at the given index.
  StringAttr getResName(unsigned idx) {
    return llvm::cast<StringAttr>(getResNames()[idx]);
  }

  /// Resolve argument and result names. This can be used during building of
  /// a handshake.func operation to ensure that names provided by an incoming
  /// operation fulfills the name requirements of the handshake function.
  void resolveArgAndResNames();

  /// Hook for FunctionOpInterface, called after verifying that the 'type'
  /// attribute is present and checks if it holds a function type.  Ensures
  /// getType, getNumFuncArguments, and getNumFuncResults can be called
  /// safely.
  LogicalResult verifyType() {
    auto type = getFunctionTypeAttr().getValue();
    if (!llvm::isa<FunctionType>(type))
      return emitOpError(
          "requires '" + getFunctionTypeAttrName().getValue() +
          "' attribute of function type");
    return success();
  }

  /// Returns the body block of the function.
  Block* getBodyBlock() {
    return &getBody().front();
  }

  //===------------------------------------------------------------------===//
  // OpAsmOpInterface Methods
  //===------------------------------------------------------------------===//

  static ::llvm::StringRef getDefaultDialect() {
    return "handshake";
  }
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::FuncOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::FuncOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using moduleTy = ::mlir::FlatSymbolRefAttr;
    moduleTy module;

    auto getModule() const {
      auto &propStorage = this->module;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModule(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->module = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.module == this->module &&
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
      odsOpName.emplace("handshake.instance", odsAttrs.getContext());
  }

  InstanceOpGenericAdaptorBase(InstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().module);
    return attr;
  }

  ::llvm::StringRef getModule();
};

} // namespace detail
template <typename RangeT>
class InstanceOpGenericAdaptor : public detail::InstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_opOperands = 0;
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

  RangeT getOpOperands() {
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
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::OpTrait::HasClock, ::mlir::SymbolUserOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_opOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<InstanceOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<InstanceOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<InstanceOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("module")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getModuleAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getModuleAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.instance");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOpOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOpOperandsMutable();
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
  ::mlir::FlatSymbolRefAttr getModuleAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().module);
  }

  ::llvm::StringRef getModule();
  void setModuleAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().module = attr;
  }

  void setModule(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FuncOp module, ValueRange operands = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FuncOp module, ValueRange operands = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, FuncOp module, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr module, TypeRange results, ValueRange operands = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, SymbolRefAttr module, TypeRange results, ValueRange operands = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, SymbolRefAttr module, TypeRange results, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef module, TypeRange results, ValueRange operands = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef module, TypeRange results, ValueRange operands = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef module, TypeRange results, ValueRange operands = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  FunctionType getModuleType();

  /// Get the argument operands to the called function.
  operand_range getArgOperands() {
    return {arg_operand_begin(), arg_operand_end()};
  }

  operand_iterator arg_operand_begin() { return operand_begin(); }
  operand_iterator arg_operand_end() { return operand_end(); }

  /// Return the module of this operation.
  CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<SymbolRefAttr>("module");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getModuleAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
  }

  /// Get the control operand of this instance op
  Value getControl() {
    return getOperands().back();
  }

  MutableOperandRange getArgOperandsMutable() {
    return getOpOperandsMutable();
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

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::JoinOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class JoinOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  JoinOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.join", odsAttrs.getContext());
  }

  JoinOpGenericAdaptorBase(JoinOp op);

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
class JoinOpGenericAdaptor : public detail::JoinOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::JoinOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
public:
  JoinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  JoinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : JoinOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  JoinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : JoinOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  JoinOpGenericAdaptor(RangeT values, const JoinOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = JoinOp, typename = std::enable_if_t<std::is_same_v<LateInst, JoinOp>>>
  JoinOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getData() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class JoinOpAdaptor : public JoinOpGenericAdaptor<::mlir::ValueRange> {
public:
  using JoinOpGenericAdaptor::JoinOpGenericAdaptor;
  JoinOpAdaptor(JoinOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class JoinOp : public ::mlir::Op<JoinOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::NoneType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = JoinOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = JoinOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<JoinOp>::refineReturnTypes;
  using ::circt::handshake::NamedIOInterface::Trait<JoinOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<JoinOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<JoinOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.join");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getData() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDataMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::NoneType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::NoneType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange data);
  static JoinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange data);
  static JoinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange data);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JoinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JoinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JoinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JoinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JoinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JoinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JoinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JoinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  bool isControl();
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::JoinOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::LazyForkOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LazyForkOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LazyForkOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.lazy_fork", odsAttrs.getContext());
  }

  LazyForkOpGenericAdaptorBase(LazyForkOp op);

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
class LazyForkOpGenericAdaptor : public detail::LazyForkOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LazyForkOpGenericAdaptorBase;
  static constexpr int odsIndex_operand = 0;
public:
  LazyForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LazyForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LazyForkOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LazyForkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LazyForkOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LazyForkOpGenericAdaptor(RangeT values, const LazyForkOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LazyForkOp, typename = std::enable_if_t<std::is_same_v<LateInst, LazyForkOp>>>
  LazyForkOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LazyForkOpAdaptor : public LazyForkOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LazyForkOpGenericAdaptor::LazyForkOpGenericAdaptor;
  LazyForkOpAdaptor(LazyForkOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LazyForkOp : public ::mlir::Op<LazyForkOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LazyForkOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LazyForkOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::SOSTInterface::Trait<LazyForkOp>::getDataType;
  using ::circt::handshake::SOSTInterface::Trait<LazyForkOp>::sostPrint;
  using ::circt::handshake::NamedIOInterface::Trait<LazyForkOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<LazyForkOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<LazyForkOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.lazy_fork");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value operand, unsigned size);
  static LazyForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value operand, unsigned size);
  static LazyForkOp create(::mlir::ImplicitLocOpBuilder &builder, Value operand, unsigned size);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value operand);
  static LazyForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value operand);
  static LazyForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value operand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LazyForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LazyForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LazyForkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LazyForkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  unsigned getSize();
  bool sostIsControl();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::LazyForkOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::LoadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.load", odsAttrs.getContext());
  }

  LoadOpGenericAdaptorBase(LoadOp op);

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
class LoadOpGenericAdaptor : public detail::LoadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoadOpGenericAdaptorBase;
  static constexpr int odsIndex_addresses = 0;
  static constexpr int odsIndex_data = 1;
  static constexpr int odsIndex_ctrl = 2;
public:
  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LoadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoadOpGenericAdaptor(RangeT values, const LoadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoadOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoadOp>>>
  LoadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAddresses() {
    return getODSOperands(0);
  }

  ValueT getData() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCtrl() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoadOpAdaptor : public LoadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoadOpGenericAdaptor::LoadOpGenericAdaptor;
  LoadOpAdaptor(LoadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoadOp : public ::mlir::Op<LoadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_addresses = 0;
  static constexpr int odsIndex_data = 1;
  static constexpr int odsIndex_ctrl = 2;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<LoadOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<LoadOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<LoadOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.load");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAddresses() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::NoneType> getCtrl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::NoneType>>(*getODSOperands(2).begin());
  }

  ::mlir::MutableOperandRange getAddressesMutable();
  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCtrlMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDataResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::Operation::result_range getAddressResults() {
    return getODSResults(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memref, ValueRange indices);
  static LoadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memref, ValueRange indices);
  static LoadOp create(::mlir::ImplicitLocOpBuilder &builder, Value memref, ValueRange indices);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  std::string getOperandName(unsigned idx);
  std::string getResultName(unsigned idx);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::LoadOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::MemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryOpGenericAdaptorBase {
public:
  struct Properties {
    using idTy = ::mlir::IntegerAttr;
    idTy id;

    auto getId() const {
      auto &propStorage = this->id;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setId(const ::mlir::IntegerAttr &propValue) {
      this->id = propValue;
    }
    using ldCountTy = ::mlir::IntegerAttr;
    ldCountTy ldCount;

    auto getLdCount() const {
      auto &propStorage = this->ldCount;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLdCount(const ::mlir::IntegerAttr &propValue) {
      this->ldCount = propValue;
    }
    using lsqTy = ::mlir::IntegerAttr;
    lsqTy lsq;

    auto getLsq() const {
      auto &propStorage = this->lsq;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLsq(const ::mlir::IntegerAttr &propValue) {
      this->lsq = propValue;
    }
    using memRefTypeTy = ::mlir::TypeAttr;
    memRefTypeTy memRefType;

    auto getMemRefType() const {
      auto &propStorage = this->memRefType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setMemRefType(const ::mlir::TypeAttr &propValue) {
      this->memRefType = propValue;
    }
    using stCountTy = ::mlir::IntegerAttr;
    stCountTy stCount;

    auto getStCount() const {
      auto &propStorage = this->stCount;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setStCount(const ::mlir::IntegerAttr &propValue) {
      this->stCount = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.id == this->id &&
        rhs.ldCount == this->ldCount &&
        rhs.lsq == this->lsq &&
        rhs.memRefType == this->memRefType &&
        rhs.stCount == this->stCount &&
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
  MemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.memory", odsAttrs.getContext());
  }

  MemoryOpGenericAdaptorBase(MemoryOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLdCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().ldCount);
    return attr;
  }

  uint32_t getLdCount();
  ::mlir::IntegerAttr getStCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().stCount);
    return attr;
  }

  uint32_t getStCount();
  ::mlir::IntegerAttr getIdAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().id);
    return attr;
  }

  uint32_t getId();
  ::mlir::TypeAttr getMemRefTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().memRefType);
    return attr;
  }

  MemRefType getMemRefType();
  ::mlir::IntegerAttr getLsqAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().lsq);
    return attr;
  }

  bool getLsq();
};

} // namespace detail
template <typename RangeT>
class MemoryOpGenericAdaptor : public detail::MemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryOpGenericAdaptor(RangeT values, const MemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryOp>>>
  MemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MemoryOpAdaptor : public MemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryOpGenericAdaptor::MemoryOpGenericAdaptor;
  MemoryOpAdaptor(MemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryOp : public ::mlir::Op<MemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::MemoryOpInterface::Trait, ::mlir::OpTrait::HasClock, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<MemoryOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<MemoryOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<MemoryOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("id"), ::llvm::StringRef("ldCount"), ::llvm::StringRef("lsq"), ::llvm::StringRef("memRefType"), ::llvm::StringRef("stCount")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLdCountAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLdCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getLsqAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getLsqAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getMemRefTypeAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMemRefTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getStCountAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getStCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.memory");
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getLdCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().ldCount);
  }

  uint32_t getLdCount();
  ::mlir::IntegerAttr getStCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().stCount);
  }

  uint32_t getStCount();
  ::mlir::IntegerAttr getIdAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().id);
  }

  uint32_t getId();
  ::mlir::TypeAttr getMemRefTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().memRefType);
  }

  MemRefType getMemRefType();
  ::mlir::IntegerAttr getLsqAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().lsq);
  }

  bool getLsq();
  void setLdCountAttr(::mlir::IntegerAttr attr) {
    getProperties().ldCount = attr;
  }

  void setLdCount(uint32_t attrValue);
  void setStCountAttr(::mlir::IntegerAttr attr) {
    getProperties().stCount = attr;
  }

  void setStCount(uint32_t attrValue);
  void setIdAttr(::mlir::IntegerAttr attr) {
    getProperties().id = attr;
  }

  void setId(uint32_t attrValue);
  void setMemRefTypeAttr(::mlir::TypeAttr attr) {
    getProperties().memRefType = attr;
  }

  void setLsqAttr(::mlir::IntegerAttr attr) {
    getProperties().lsq = attr;
  }

  void setLsq(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange operands, int outputs, int control_outputs, bool lsq, int id, Value memref);
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange operands, int outputs, int control_outputs, bool lsq, int id, Value memref);
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange operands, int outputs, int control_outputs, bool lsq, int id, Value memref);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  bool allocateMemory(llvm::DenseMap<unsigned, unsigned> &memoryMap, std::vector<std::vector<llvm::Any>> &store, std::vector<double> &storeTimes);
  std::string getOperandName(unsigned idx);
  std::string getResultName(unsigned idx);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  llvm::SmallVector<handshake::MemLoadInterface> getLoadPorts();
  llvm::SmallVector<handshake::MemStoreInterface> getStorePorts();
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::MemoryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::detail::MemoryOpGenericAdaptorBase::Properties)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::MergeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MergeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MergeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.merge", odsAttrs.getContext());
  }

  MergeOpGenericAdaptorBase(MergeOp op);

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
class MergeOpGenericAdaptor : public detail::MergeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MergeOpGenericAdaptorBase;
  static constexpr int odsIndex_dataOperands = 0;
public:
  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MergeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MergeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MergeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MergeOpGenericAdaptor(RangeT values, const MergeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MergeOp, typename = std::enable_if_t<std::is_same_v<LateInst, MergeOp>>>
  MergeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getDataOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MergeOpAdaptor : public MergeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MergeOpGenericAdaptor::MergeOpGenericAdaptor;
  MergeOpAdaptor(MergeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MergeOp : public ::mlir::Op<MergeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::MergeLikeOpInterface::Trait, ::circt::handshake::SOSTInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MergeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MergeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dataOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<MergeOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<MergeOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<MergeOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.merge");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getDataOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getDataOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange dataOperands);
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange dataOperands);
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange dataOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MergeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::MergeOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::MuxOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MuxOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MuxOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.mux", odsAttrs.getContext());
  }

  MuxOpGenericAdaptorBase(MuxOp op);

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
class MuxOpGenericAdaptor : public detail::MuxOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MuxOpGenericAdaptorBase;
  static constexpr int odsIndex_selectOperand = 0;
  static constexpr int odsIndex_dataOperands = 1;
public:
  MuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MuxOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MuxOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MuxOpGenericAdaptor(RangeT values, const MuxOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MuxOp, typename = std::enable_if_t<std::is_same_v<LateInst, MuxOp>>>
  MuxOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSelectOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getDataOperands() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MuxOpAdaptor : public MuxOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MuxOpGenericAdaptor::MuxOpGenericAdaptor;
  MuxOpAdaptor(MuxOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MuxOp : public ::mlir::Op<MuxOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::MergeLikeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MuxOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MuxOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_selectOperand = 0;
  static constexpr int odsIndex_dataOperands = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<MuxOp>::refineReturnTypes;
  using ::circt::handshake::NamedIOInterface::Trait<MuxOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<MuxOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<MuxOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.mux");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getSelectOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getDataOperands() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getSelectOperandMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getDataOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value selectOperand, ::mlir::ValueRange dataOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  bool isControl();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  std::string getOperandName(unsigned idx);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::MuxOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::NeverOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NeverOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NeverOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.never", odsAttrs.getContext());
  }

  NeverOpGenericAdaptorBase(NeverOp op);

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
class NeverOpGenericAdaptor : public detail::NeverOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NeverOpGenericAdaptorBase;
public:
  NeverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NeverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : NeverOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NeverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NeverOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NeverOpGenericAdaptor(RangeT values, const NeverOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NeverOp, typename = std::enable_if_t<std::is_same_v<LateInst, NeverOp>>>
  NeverOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NeverOpAdaptor : public NeverOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NeverOpGenericAdaptor::NeverOpGenericAdaptor;
  NeverOpAdaptor(NeverOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NeverOp : public ::mlir::Op<NeverOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NeverOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NeverOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<NeverOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<NeverOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<NeverOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.never");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static NeverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static NeverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static NeverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static NeverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NeverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NeverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::NeverOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::PackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PackOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.pack", odsAttrs.getContext());
  }

  PackOpGenericAdaptorBase(PackOp op);

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
class PackOpGenericAdaptor : public detail::PackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PackOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PackOpGenericAdaptor(RangeT values, const PackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PackOp, typename = std::enable_if_t<std::is_same_v<LateInst, PackOp>>>
  PackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PackOpAdaptor : public PackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PackOpGenericAdaptor::PackOpGenericAdaptor;
  PackOpAdaptor(PackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PackOp : public ::mlir::Op<PackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::TupleType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<PackOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<PackOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<PackOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.pack");
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

  ::mlir::TypedValue<::mlir::TupleType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TupleType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange operands);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange operands);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::PackOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::ReturnOp declarations
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
      odsOpName.emplace("handshake.return", odsAttrs.getContext());
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
  static constexpr int odsIndex_opOperands = 0;
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

  RangeT getOpOperands() {
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_opOperands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<ReturnOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<ReturnOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<ReturnOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOpOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOpOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange opOperands);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange opOperands);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange opOperands);
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

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::ReturnOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::SinkOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SinkOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SinkOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.sink", odsAttrs.getContext());
  }

  SinkOpGenericAdaptorBase(SinkOp op);

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
class SinkOpGenericAdaptor : public detail::SinkOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SinkOpGenericAdaptorBase;
  static constexpr int odsIndex_operand = 0;
public:
  SinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SinkOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SinkOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SinkOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SinkOpGenericAdaptor(RangeT values, const SinkOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SinkOp, typename = std::enable_if_t<std::is_same_v<LateInst, SinkOp>>>
  SinkOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOperand() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SinkOpAdaptor : public SinkOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SinkOpGenericAdaptor::SinkOpGenericAdaptor;
  SinkOpAdaptor(SinkOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SinkOp : public ::mlir::Op<SinkOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SinkOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SinkOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operand = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<SinkOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<SinkOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<SinkOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.sink");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOperand() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOperandMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value operand);
  static SinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value operand);
  static SinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value operand);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value operand);
  static SinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value operand);
  static SinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value operand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SinkOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SinkOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::SinkOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::SourceOp declarations
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
      odsOpName.emplace("handshake.source", odsAttrs.getContext());
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
class SourceOp : public ::mlir::Op<SourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::handshake::SOSTInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::SOSTInterface::Trait<SourceOp>::sostIsControl;
  using ::circt::handshake::SOSTInterface::Trait<SourceOp>::sostPrint;
  using ::circt::handshake::NamedIOInterface::Trait<SourceOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<SourceOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<SourceOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.source");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  mlir::Type getDataType();
  unsigned getSize();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::SourceOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::StoreOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StoreOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StoreOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.store", odsAttrs.getContext());
  }

  StoreOpGenericAdaptorBase(StoreOp op);

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
class StoreOpGenericAdaptor : public detail::StoreOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StoreOpGenericAdaptorBase;
  static constexpr int odsIndex_addresses = 0;
  static constexpr int odsIndex_data = 1;
  static constexpr int odsIndex_ctrl = 2;
public:
  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StoreOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StoreOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StoreOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StoreOpGenericAdaptor(RangeT values, const StoreOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StoreOp, typename = std::enable_if_t<std::is_same_v<LateInst, StoreOp>>>
  StoreOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAddresses() {
    return getODSOperands(0);
  }

  ValueT getData() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCtrl() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StoreOpAdaptor : public StoreOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StoreOpGenericAdaptor::StoreOpGenericAdaptor;
  StoreOpAdaptor(StoreOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StoreOp : public ::mlir::Op<StoreOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StoreOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StoreOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_addresses = 0;
  static constexpr int odsIndex_data = 1;
  static constexpr int odsIndex_ctrl = 2;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<StoreOp>::getResultName;
  using ::circt::handshake::NamedIOInterface::Trait<StoreOp>::getOperandName;
  using ::circt::handshake::ControlInterface::Trait<StoreOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.store");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getAddresses() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::NoneType> getCtrl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::NoneType>>(*getODSOperands(2).begin());
  }

  ::mlir::MutableOperandRange getAddressesMutable();
  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getCtrlMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDataResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::Operation::result_range getAddressResult() {
    return getODSResults(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value valueToStore, ValueRange indices);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value valueToStore, ValueRange indices);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, Value valueToStore, ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dataResult, ::mlir::TypeRange addressResult, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataResult, ::mlir::TypeRange addressResult, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataResult, ::mlir::TypeRange addressResult, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange addresses, ::mlir::Value data, ::mlir::Value ctrl);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  std::string getOperandName(unsigned idx);
  std::string getResultName(unsigned idx);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::StoreOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::SyncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SyncOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SyncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.sync", odsAttrs.getContext());
  }

  SyncOpGenericAdaptorBase(SyncOp op);

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
class SyncOpGenericAdaptor : public detail::SyncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SyncOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  SyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SyncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SyncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SyncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SyncOpGenericAdaptor(RangeT values, const SyncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SyncOp, typename = std::enable_if_t<std::is_same_v<LateInst, SyncOp>>>
  SyncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SyncOpAdaptor : public SyncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SyncOpGenericAdaptor::SyncOpGenericAdaptor;
  SyncOpAdaptor(SyncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SyncOp : public ::mlir::Op<SyncOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::HasClock, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SyncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SyncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<SyncOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<SyncOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<SyncOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.sync");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange operands);
  static SyncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange operands);
  static SyncOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange operands);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::SyncOp)

namespace circt::handshake {


//===----------------------------------------------------------------------===//
// ::circt::handshake::UnpackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnpackOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnpackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("handshake.unpack", odsAttrs.getContext());
  }

  UnpackOpGenericAdaptorBase(UnpackOp op);

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
class UnpackOpGenericAdaptor : public detail::UnpackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnpackOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  UnpackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnpackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnpackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnpackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnpackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnpackOpGenericAdaptor(RangeT values, const UnpackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnpackOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnpackOp>>>
  UnpackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class UnpackOpAdaptor : public UnpackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnpackOpGenericAdaptor::UnpackOpGenericAdaptor;
  UnpackOpAdaptor(UnpackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnpackOp : public ::mlir::Op<UnpackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParentInterface<FineGrainedDataflowRegionOpInterface>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::HasClock, ::circt::handshake::ExecutableOpInterface::Trait, ::circt::handshake::GeneralOpInterface::Trait, ::circt::handshake::NamedIOInterface::Trait, ::circt::handshake::ControlInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnpackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnpackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::handshake::NamedIOInterface::Trait<UnpackOp>::getOperandName;
  using ::circt::handshake::NamedIOInterface::Trait<UnpackOp>::getResultName;
  using ::circt::handshake::ControlInterface::Trait<UnpackOp>::isControl;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("handshake.unpack");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::TupleType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::TupleType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input);
  static UnpackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input);
  static UnpackOp create(::mlir::ImplicitLocOpBuilder &builder, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value input);
  static UnpackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value input);
  static UnpackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnpackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnpackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnpackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnpackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> &valueMap, llvm::DenseMap<unsigned, unsigned> &memoryMap, llvm::DenseMap<mlir::Value, double> &timeMap, std::vector<std::vector<llvm::Any>> &store, std::vector<mlir::Value> &scheduleList);
  void execute(std::vector<llvm::Any> &ins, std::vector<llvm::Any> &outs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::UnpackOp)


#endif // GET_OP_CLASSES

