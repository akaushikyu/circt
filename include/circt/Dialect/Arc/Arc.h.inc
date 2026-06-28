/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Arc.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

/// Allocate a memory
class AllocMemoryOp;

} // namespace circt::arc
namespace circt::arc {

/// Allocate internal state
class AllocStateOp;

} // namespace circt::arc
namespace circt::arc {

/// Allocate contiguous storage space from a larger storage space
class AllocStorageOp;

} // namespace circt::arc
namespace circt::arc {

/// array allocation
/// Allocates an array on the stack. If `init` is set, the array is initialized
/// to this value. Otherwise the array's contents are undefined.
class ArrayRefAllocOp;

} // namespace circt::arc
namespace circt::arc {

/// array copy
/// Copies the content of one array into another array. Returns the input array.
class ArrayRefCopyOp;

} // namespace circt::arc
namespace circt::arc {

/// array create
/// Creates an array from a list of values. The values are ordered from
/// most significant to least significant (the same as `hw.array_create`).
/// 
/// The `input` array is populated with `elements` and is returned.
class ArrayRefCreateOp;

} // namespace circt::arc
namespace circt::arc {

/// arrayref from array
/// Populates an arrayref with the elements of an array.
class ArrayRefFromArrayOp;

} // namespace circt::arc
namespace circt::arc {

/// array get
/// Loads a single value from an arrayref.
class ArrayRefGetOp;

} // namespace circt::arc
namespace circt::arc {

/// array inject
/// Stores a single value into an arrayref.
class ArrayRefInjectOp;

} // namespace circt::arc
namespace circt::arc {

/// array slice
/// Slices an array into a sub-array, returning a view into the original array.
class ArrayRefSliceOp;

} // namespace circt::arc
namespace circt::arc {

/// arrayref to array
/// Creates an array from an arrayref.
class ArrayRefToArrayOp;

} // namespace circt::arc
namespace circt::arc {

/// calls an arc
class CallOp;

} // namespace circt::arc
namespace circt::arc {

/// Call a coroutine
/// Call an `arc.coroutine.define`. The coroutine is resumed at the point
/// indicated by the `pc` operand, and local state is restored from the `state`
/// operand. The `args` are passed into the coroutine and may differ between
/// subsequent re-entries. When the coroutine suspends or finishes, control is
/// transferred back to the caller and the call op returns the coroutine's
/// resume program counter, resume state, and the values yielded back from the
/// coroutine as results.
/// 
/// Passing a `return` or `halt` program counter to the callee results in
/// undefined behavior. These program counter values indicate that the coroutine
/// has finished or suspended forever, respectively, and the coroutine must not
/// be re-entered in either case.
/// 
/// The caller is responsible for interpreting the program counter returned from
/// the coroutine. A `return` indicates that the coroutine is finished and
/// control shall continue in the parent. A `halt` indicates that the coroutine
/// suspends forever, and the parent should also return `halt` if it is a
/// coroutine itself. Any other value indicates that the callee has suspended
/// and expects to be re-entered at a later point, and the caller must suspend
/// itself and re-enter the callee if it is a coroutine itself.
class CoroutineCallOp;

} // namespace circt::arc
namespace circt::arc {

/// Coroutine definition
/// Define a coroutine. Coroutines are suspendable functions that are entered at
/// their entry block or re-entered at a resume block. Local state and values
/// are persisted by an opaque state held by the caller, alongside an opaque
/// program counter value indicating at which point the coroutine should be
/// resumed.
/// 
/// Coroutines can be suspended by the `arc.coroutine.yield` terminator, which
/// returns control and local state back to the caller. The caller can then
/// re-enter the coroutine by passing that control and local state back into the
/// coroutine. Coroutines can be finished by the `arc.coroutine.return` and
/// `arc.coroutine.halt` terminators, which return control back to the caller
/// with a corresponding program counter indicating return or halt.
/// 
/// Arguments are passed to the coroutine upon each entry. The entry block's
/// arguments hold the values supplied by the caller on the first call. Each
/// block targeted by a suspension op must have its first arguments match the
/// coroutine's function type. On resumption, those arguments are bound to the
/// values supplied by the caller and may differ from the values passed on prior
/// entries.
/// 
/// Results are returned from the coroutine upon each suspension. Each of the
/// terminators must provide a set of values to be yielded back to the caller
/// upon suspension.
/// 
/// The local state of a coroutine is represented by `!arc.coroutine_state<@A>`,
/// and the program counter for resuming by `!arc.coroutine_pc<@A>`. These types
/// are opaque and are expanded to a concrete union/struct of local state and a
/// concrete integer PC via a lowering. These types are only used on coroutine
/// calls; coroutine definitions define them implicitly by values carried across
/// resume points.
/// 
/// To nest coroutines, a coroutine definition can call another coroutine and
/// carry the `!arc.coroutine_state` and `!arc.coroutine_pc` of that call as
/// local state across its own suspension points.
class CoroutineDefineOp;

} // namespace circt::arc
namespace circt::arc {

/// Halt a coroutine permanently
/// Halts execution of a coroutine forever. Control effectively gets stuck
/// indefinitely at the halt operation, also preventing all callers from making
/// progress. Yields back a special sentinel program counter value to the caller
/// which the caller must translate into either halting itself if it is a
/// coroutine, or arranging for the coroutine to never be re-entered again.
class CoroutineHaltOp;

} // namespace circt::arc
namespace circt::arc {

/// Continuously run a coroutine in an hw.module
/// Execute a coroutine concurrently in an `hw.module`. The program counter and
/// state of the coroutine are held implicitly by the instance and passed into
/// the coroutine when executed next. The values yielded by the coroutine are
/// produced as results of the instance. The callee must produce a wakeup time
/// as its last result value. This wakeup time is not exposed as a result of
/// the instance op and is instead used to schedule the next execution.
class CoroutineInstanceOp;

} // namespace circt::arc
namespace circt::arc {

/// Check whether a coroutine PC is a sentinel value
class CoroutinePCIsHaltOp;

} // namespace circt::arc
namespace circt::arc {

/// Check whether a coroutine PC is a sentinel value
class CoroutinePCIsReturnOp;

} // namespace circt::arc
namespace circt::arc {

/// Return from a coroutine
/// Returns control from a coroutine to the caller, yielding back a special
/// sentinel program counter value indicating that the coroutine has run to
/// completion. Additionally, the yield operands are returned to the caller and
/// must match the result types of the coroutine.
class CoroutineReturnOp;

} // namespace circt::arc
namespace circt::arc {

/// Create the start sentinel coroutine program counter
/// Produces the special `start` sentinel `!arc.coroutine_pc` value. Passing
/// this program counter to an `arc.coroutine.call` enters the coroutine for the
/// first time, executing its body from the entry block. This op provides such a
/// value to seed the very first call into a coroutine.
class CoroutineStartPCOp;

} // namespace circt::arc
namespace circt::arc {

/// Create an undefined initial coroutine state
/// Produces an undefined `!arc.coroutine_state` value. A coroutine establishes
/// its local state on first entry and never reads the state passed on that
/// first call, such that any initial state value will do. This op provides such
/// a value to seed the very first call into a coroutine.
class CoroutineUndefinedStateOp;

} // namespace circt::arc
namespace circt::arc {

/// Suspend a coroutine and request resumption at a block
/// Suspend a coroutine. Control is transferred back to the caller, alongside
/// a program counter value indicating the destination block, and the local
/// state needed to restore the values live across the yield op. Additionally,
/// the yield operands are returned to the caller and must match the result
/// types of the coroutine.
/// 
/// The destination block's first arguments must match the coroutine's function
/// type. On resumption, those arguments are bound to the values supplied by the
/// caller. The remaining arguments of the destination block are bound to the
/// destination operands of the yield op.
class CoroutineYieldOp;

} // namespace circt::arc
namespace circt::arc {

/// Read the current simulation time
/// Reads the current simulation time from the model's storage. The time is
/// represented as an `i64` value in femtoseconds.
class CurrentTimeOp;

} // namespace circt::arc
namespace circt::arc {

/// State transfer arc definition
class DefineOp;

} // namespace circt::arc
namespace circt::arc {

/// Execute an SSACFG region
/// The `arc.execute` op allows an SSACFG region to be embedded in a parent
/// graph region, or another SSACFG region. Whenever execution reaches this op,
/// its body region is executed and the results yielded from the body are
/// produced as the `arc.execute` op's results. The op is isolated from above.
/// Any SSA values defined outside the op that are used inside the body have to
/// be captured as operands and then referred to as entry block arguments in the
/// body.
class ExecuteOp;

} // namespace circt::arc
namespace circt::arc {

/// Region to be executed at the end of simulation
class FinalOp;

} // namespace circt::arc
namespace circt::arc {

/// Read the model's next wakeup time
/// Reads the next wakeup time from the model's storage. The time is
/// represented as an `i64` value in femtoseconds. A value of `0` indicates
/// "wake up immediately"; a value of `UINT64_MAX` indicates that no wakeup
/// is pending.
class GetNextWakeupOp;

} // namespace circt::arc
namespace circt::arc {

/// Region to be executed at the start of simulation
class InitialOp;

} // namespace circt::arc
namespace circt::arc {

/// A lookup-table.
/// Represents a lookup-table as one operation. The operations that map the
/// lookup/input values to the corresponding table-entry are collected inside
/// the body of this operation.
/// Note that the operation is marked to be isolated from above to guarantee
/// that all input values have to be passed as an operand. This allows for
/// simpler analyses and canonicalizations of the LUT as well as lowering.
/// Only combinational operations are allowed inside the LUT, i.e., no
/// side-effects, state, time delays, etc.
class LutOp;

} // namespace circt::arc
namespace circt::arc {

/// Memory
class MemoryOp;

} // namespace circt::arc
namespace circt::arc {

/// Read a word from a memory
class MemoryReadOp;

} // namespace circt::arc
namespace circt::arc {

/// Read port from a memory
/// Represents a combinatorial memory read port. No memory read side-effect
/// trait is necessary because at the stage of the Arc lowering where this
/// operation is legal to be present, it is guaranteed that all reads from the
/// same address produce the same output. This is because all writes are
/// reordered to happen at the end of the cycle in LegalizeStateUpdates (or
/// alternatively produce the necessary temporaries).
class MemoryReadPortOp;

} // namespace circt::arc
namespace circt::arc {

/// Write a word to a memory
class MemoryWriteOp;

} // namespace circt::arc
namespace circt::arc {

/// Write port to a memory
class MemoryWritePortOp;

} // namespace circt::arc
namespace circt::arc {

/// A model with stratified clocks
/// A model with stratified clocks. The `io` optional attribute
/// specifies the I/O of the module associated to this model.
class ModelOp;

} // namespace circt::arc
namespace circt::arc {

/// Arc terminator
class OutputOp;

} // namespace circt::arc
namespace circt::arc {

/// A root input
class RootInputOp;

} // namespace circt::arc
namespace circt::arc {

/// A root output
class RootOutputOp;

} // namespace circt::arc
namespace circt::arc {

/// Provides static metadata of an Arc model used by the runtime
/// Collection of static metadata for a specific Arc model accessed by the
/// arcilator runtime library:
/// - name: Name of the model
/// - numStateBytes: Number of bytes required to store the model's internal
///     state
/// - traceTaps: Traced signal metadata
class RuntimeModelOp;

} // namespace circt::arc
namespace circt::arc {

/// Set the model's next wakeup time
/// Writes the next wakeup time into the model's storage. The time is
/// represented as an `i64` value in femtoseconds. The model's eval body
/// establishes the slot at `UINT64_MAX` ("no wakeup pending") on entry, and
/// process suspension code lowers the value to the earliest scheduled
/// wakeup over the course of an evaluation.
class SetNextWakeupOp;

} // namespace circt::arc
namespace circt::arc {

/// Sends a value to the simulation driver
/// Sends a named value to the simulation driver. This is notably useful
/// for printing values during simulation.
class SimEmitValueOp;

} // namespace circt::arc
namespace circt::arc {

/// Gets the next wakeup time of the model instance
/// Gets the next wakeup time of the given model instance. The time is
/// represented as an `i64` value in femtoseconds. A value of `0` indicates
/// "wake up immediately"; a value of `UINT64_MAX` indicates that no wakeup
/// is pending. The slot is recomputed on every evaluation, so a driver
/// typically reads it after each `arc.sim.step` to decide how far to
/// advance simulation time before the next step.
class SimGetNextWakeupOp;

} // namespace circt::arc
namespace circt::arc {

/// Gets the value of a port of the model instance
/// Gets the value of the given port in a specific instance of a model. The
/// provided port must be of the type of the expected value.
class SimGetPortOp;

} // namespace circt::arc
namespace circt::arc {

/// Gets the current simulation time of the model instance
/// Gets the current simulation time of the given model instance. The time is
/// represented as an `i64` value in femtoseconds.
class SimGetTimeOp;

} // namespace circt::arc
namespace circt::arc {

/// Instantiates an Arc model for simulation
/// Creates an instance of an Arc model in scope, in order to simulate it.
/// The model can be used from within the associated region, modelling its
/// lifetime.
class SimInstantiateOp;

} // namespace circt::arc
namespace circt::arc {

/// Sets the value of an input of the model instance
/// Sets the value of an input port in a specific instance of a model. The
/// provided input port must be of input type on the model and its type must
/// match the type of the value operand.
class SimSetInputOp;

} // namespace circt::arc
namespace circt::arc {

/// Sets the simulation time of the model instance
/// Sets the simulation time of the given model instance. The time is
/// represented as an `i64` value in femtoseconds.
class SimSetTimeOp;

} // namespace circt::arc
namespace circt::arc {

/// Evaluates one step of the simulation for the provided model instance
/// Evaluates one step of the simulation for the provided model instance,
/// updating ports accordingly.
/// 
/// If `timePostIncrement` is provided, the instance's simulation time will be
/// incremented by the given number in femtoseconds _after_ the step has been
/// evaluated.
/// 
/// Example:
/// 
/// ```mlir
/// %cst5  = arith.constant 5  : i64
/// %cst10 = arith.constant 10 : i64
/// arc.sim.set_time %instance, %cst10 [...]
/// arc.sim.step %instance by %cst5 [...]       // Step at t = 10 fs
/// arc.sim.step %instance [...]                // Step at t = 15 fs
/// arc.sim.step %instance by %cst5 [...]       // Step at t = 15 fs
/// arc.sim.step %instance by %cst5 [...]       // Step at t = 20 fs
/// ```
class SimStepOp;

} // namespace circt::arc
namespace circt::arc {

/// Instantiates a state element with input from a transfer arc
class StateOp;

} // namespace circt::arc
namespace circt::arc {

/// Read a state's value
class StateReadOp;

} // namespace circt::arc
namespace circt::arc {

/// Update a state's value
class StateWriteOp;

} // namespace circt::arc
namespace circt::arc {

/// Access an allocated state, memory, or storage slice
class StorageGetOp;

} // namespace circt::arc
namespace circt::arc {

/// A tracker op to observe a value under one or more given names
class TapOp;

} // namespace circt::arc
namespace circt::arc {

/// Request simulation termination
/// Sets a termination flag in the model's storage.
/// It unconditionally writes 1 for success or 2 for failure.
/// This allows the simulation to exit gracefully after the current
/// evaluation cycle.
class TerminateOp;

} // namespace circt::arc
namespace circt::arc {

/// isolated subgraph of operations to be vectorized
/// This operation represents a vectorized computation DAG. It places a
/// convenient boundary between the subgraph to be vectorized and the
/// surrounding non-vectorizable parts of the original graph.
/// 
/// This allows us to split the vectorization transformations into multiple
/// parts/passes:
///   * Finding an initial set of operations to be vectorized
///   * Optimizing this set by pulling in more operations into the nested block,
///     splitting it such that the vector width does not exceed a given limit,
///     applying a cost model and potentially reverting the decision to
///     vectorize this subgraph (e.g., because not enough ops could be pulled
///     in)
///   * Performing the actual vectorization by lowering this operation. This
///     operation allows to perform the lowering of the boundary and the body
///     separately and either via 1D `vector` types for SIMD vectorization or
///     plain integers for manual vectorization within a scalar register.
/// 
/// For each block argument of the nested block, there is a list of operands
/// that represent the elements of the vector. If the boundary is already
/// vectorized each list will only contain a single SSA value of either vector
/// type or an integer representing the concatenation of all original operands
/// of that vector.
/// 
/// Example:
/// 
/// Given the following two AND operations in the IR
/// ```mlir
/// %0 = arith.and %in0, %in1 : i1
/// %1 = arith.and %in2, %in2 : i1
/// ```
/// they could be vectorized by putting one such AND operation in the body block
/// of the `arc.vectorize` operation and forwarding the operands accordingly.
/// ```mlir
/// %0:2 = arc.vectorize (%in0, %in1), (%in2, %in2) :
///   (i1, i1, i1, i1) -> (i1, i1) {
/// ^bb0(%arg0: i1, %arg1: i1):
///   %1 = arith.and %arg0, %arg1 : i1
///   arc.output %1 : i1
/// }
/// ```
/// In a next step, the boundary could be lowered/vectorized. This can happen
/// in terms of integers for vectorization within scalar registers:
/// ```mlir
/// %0 = comb.concat %in0, %in1 : i1, i1
/// %1 = comb.replicate %in2 : (i1) -> i2
/// %2 = arc.vectorize (%0), (%1) : (i2, i2) -> (i2) {
/// ^bb0(%arg0: i1, %arg1: i1):
///   %1 = arith.and %arg0, %arg1 : i1
///   arc.output %1 : i1
/// }
/// %3 = comb.extract %2 from 1 : (i2) -> i1
/// %4 = comb.extract %2 from 0 : (i2) -> i1
/// ```
/// Or via `vector` types for SIMD vectorization:
/// ```mlir
/// %cst = arith.constant dense<0> : vector<2xi1>
/// %0 = vector.insert %in0, %cst[0] : i1 into vector<2xi1>
/// %1 = vector.insert %in1, %0[1] : i1 into vector<2xi1>
/// %2 = vector.broadcast %in2 : i1 to vector<2xi1>
/// %3 = arc.vectorize (%1), (%2) :
///   (vector<2xi1>, vector<2xi1>) -> (vector<2xi1>) {
/// ^bb0(%arg0: i1, %arg1: i1):
///   %1 = arith.and %arg0, %arg1 : i1
///   arc.output %1 : i1
/// }
/// %4 = vector.extract %2[0] : vector<2xi1>
/// %5 = vector.extract %2[1] : vector<2xi1>
/// ```
/// Alternatively, the body could be vectorized first. Again, as integers
/// ```mlir
/// %0:2 = arc.vectorize (%in0, %in1), (%in2, %in2) :
///   (i1, i1, i1, i1) -> (i1, i1) {
/// ^bb0(%arg0: i2, %arg1: i2):
///   %1 = arith.and %arg0, %arg1 : i2
///   arc.output %1 : i2
/// }
/// ```
/// or SIMD vectors.
/// ```mlir
/// %0:2 = arc.vectorize (%in0, %in1), (%in2, %in3) :
///   (i1, i1, i1, i1) -> (i1, i1) {
/// ^bb0(%arg0: vector<2xi1>, %arg1: vector<2xi1>):
///   %1 = arith.and %arg0, %arg1 : vector<2xi1>
///   arc.output %1 : vector<2xi1>
/// }
/// ```
/// Once both sides are lowered, the `arc.vectorize` op simply becomes a
/// passthrough for the operands and can be removed by inlining the nested
/// block. The integer based vectorization would then look like the following:
/// ```mlir
/// %0 = comb.concat %in0, %in1 : i1, i1
/// %1 = comb.replicate %in2 : (i1) -> i2
/// %2 = arith.and %0, %1 : i2
/// %3 = comb.extract %2 from 1 : (i2) -> i1
/// %4 = comb.extract %2 from 0 : (i2) -> i1
/// ```
/// The SIMD vector based lowering would result in the following IR:
/// ```mlir
/// %cst = arith.constant dense<0> : vector<2xi1>
/// %0 = vector.insert %in0, %cst[0] : i1 into vector<2xi1>
/// %1 = vector.insert %in1, %0[1] : i1 into vector<2xi1>
/// %2 = vector.broadcast %in2 : i1 to vector<2xi1>
/// %3 = arith.and %1, %2 : vector<2xi1>
/// %4 = vector.extract %3[0] : vector<2xi1>
/// %5 = vector.extract %3[1] : vector<2xi1>
/// ```
class VectorizeOp;

} // namespace circt::arc
namespace circt::arc {

/// arc.vectorized terminator
class VectorizeReturnOp;

} // namespace circt::arc
namespace circt::arc {

/// leading/trailing zero count operation
class ZeroCountOp;

} // namespace circt::arc
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::AllocMemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocMemoryOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AllocMemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.alloc_memory", odsAttrs.getContext());
  }

  AllocMemoryOpGenericAdaptorBase(AllocMemoryOp op);

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
class AllocMemoryOpGenericAdaptor : public detail::AllocMemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocMemoryOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  AllocMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AllocMemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllocMemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocMemoryOpGenericAdaptor(RangeT values, const AllocMemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocMemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocMemoryOp>>>
  AllocMemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocMemoryOpAdaptor : public AllocMemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocMemoryOpGenericAdaptor::AllocMemoryOpGenericAdaptor;
  AllocMemoryOpAdaptor(AllocMemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocMemoryOp : public ::mlir::Op<AllocMemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::MemoryType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocMemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocMemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.alloc_memory");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory, ::mlir::Value storage);
  static AllocMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory, ::mlir::Value storage);
  static AllocMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static AllocMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static AllocMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::AllocMemoryOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::AllocStateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocStateOpGenericAdaptorBase {
public:
  struct Properties {
    using tapTy = ::mlir::UnitAttr;
    tapTy tap;

    auto getTap() const {
      auto &propStorage = this->tap;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setTap(const ::mlir::UnitAttr &propValue) {
      this->tap = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.tap == this->tap &&
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
  AllocStateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.alloc_state", odsAttrs.getContext());
  }

  AllocStateOpGenericAdaptorBase(AllocStateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getTapAttr();
  bool getTap();
};

} // namespace detail
template <typename RangeT>
class AllocStateOpGenericAdaptor : public detail::AllocStateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocStateOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  AllocStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AllocStateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllocStateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocStateOpGenericAdaptor(RangeT values, const AllocStateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocStateOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocStateOp>>>
  AllocStateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllocStateOpAdaptor : public AllocStateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocStateOpGenericAdaptor::AllocStateOpGenericAdaptor;
  AllocStateOpAdaptor(AllocStateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocStateOp : public ::mlir::Op<AllocStateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::StateType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocStateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocStateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("tap")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTapAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.alloc_state");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<circt::arc::StateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StateType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getTapAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().tap);
  }

  bool getTap();
  void setTapAttr(::mlir::UnitAttr attr) {
    getProperties().tap = attr;
  }

  void setTap(bool attrValue);
  ::mlir::Attribute removeTapAttr() {
      auto attr = getProperties().tap;
      getProperties().tap = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/::mlir::UnitAttr tap);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::mlir::Value storage, /*optional*/bool tap = false);
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::mlir::Value storage, /*optional*/bool tap = false);
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::mlir::Value storage, /*optional*/bool tap = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/bool tap = false);
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/bool tap = false);
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, /*optional*/bool tap = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::AllocStateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::AllocStateOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::AllocStorageOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AllocStorageOpGenericAdaptorBase {
public:
  struct Properties {
    using offsetTy = ::mlir::IntegerAttr;
    offsetTy offset;

    auto getOffset() const {
      auto &propStorage = this->offset;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setOffset(const ::mlir::IntegerAttr &propValue) {
      this->offset = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offset == this->offset &&
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
  AllocStorageOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.alloc_storage", odsAttrs.getContext());
  }

  AllocStorageOpGenericAdaptorBase(AllocStorageOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getOffsetAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().offset);
    return attr;
  }

  ::std::optional<uint32_t> getOffset();
};

} // namespace detail
template <typename RangeT>
class AllocStorageOpGenericAdaptor : public detail::AllocStorageOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllocStorageOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  AllocStorageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllocStorageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AllocStorageOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AllocStorageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AllocStorageOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AllocStorageOpGenericAdaptor(RangeT values, const AllocStorageOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AllocStorageOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllocStorageOp>>>
  AllocStorageOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AllocStorageOpAdaptor : public AllocStorageOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllocStorageOpGenericAdaptor::AllocStorageOpGenericAdaptor;
  AllocStorageOpAdaptor(AllocStorageOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AllocStorageOp : public ::mlir::Op<AllocStorageOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::StorageType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllocStorageOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllocStorageOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offset")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffsetAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffsetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.alloc_storage");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<circt::arc::StorageType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getOffsetAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().offset);
  }

  ::std::optional<uint32_t> getOffset();
  void setOffsetAttr(::mlir::IntegerAttr attr) {
    getProperties().offset = attr;
  }

  void setOffset(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeOffsetAttr() {
      auto attr = getProperties().offset;
      getProperties().offset = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static AllocStorageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static AllocStorageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static AllocStorageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static AllocStorageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::IntegerAttr offset);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocStorageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AllocStorageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocStorageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AllocStorageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::AllocStorageOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::AllocStorageOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefAllocOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefAllocOpGenericAdaptorBase {
public:
  struct Properties {
    using initTy = ::mlir::ArrayAttr;
    initTy init;

    auto getInit() const {
      auto &propStorage = this->init;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setInit(const ::mlir::ArrayAttr &propValue) {
      this->init = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.init == this->init &&
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
  ArrayRefAllocOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.alloc", odsAttrs.getContext());
  }

  ArrayRefAllocOpGenericAdaptorBase(ArrayRefAllocOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getInitAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().init);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getInit();
};

} // namespace detail
template <typename RangeT>
class ArrayRefAllocOpGenericAdaptor : public detail::ArrayRefAllocOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefAllocOpGenericAdaptorBase;
public:
  ArrayRefAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefAllocOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefAllocOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefAllocOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefAllocOpGenericAdaptor(RangeT values, const ArrayRefAllocOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefAllocOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefAllocOp>>>
  ArrayRefAllocOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayRefAllocOpAdaptor : public ArrayRefAllocOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefAllocOpGenericAdaptor::ArrayRefAllocOpGenericAdaptor;
  ArrayRefAllocOpAdaptor(ArrayRefAllocOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefAllocOp : public ::mlir::Op<ArrayRefAllocOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefAllocOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefAllocOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("init")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.alloc");
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getInitAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().init);
  }

  ::std::optional< ::mlir::ArrayAttr > getInit();
  void setInitAttr(::mlir::ArrayAttr attr) {
    getProperties().init = attr;
  }

  ::mlir::Attribute removeInitAttr() {
      auto attr = getProperties().init;
      getProperties().init = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, /*optional*/::mlir::ArrayAttr init);
  static ArrayRefAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, /*optional*/::mlir::ArrayAttr init);
  static ArrayRefAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, /*optional*/::mlir::ArrayAttr init);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr init);
  static ArrayRefAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr init);
  static ArrayRefAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::ArrayAttr init);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefAllocOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefAllocOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefAllocOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::ArrayRefAllocOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefCopyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefCopyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefCopyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.copy", odsAttrs.getContext());
  }

  ArrayRefCopyOpGenericAdaptorBase(ArrayRefCopyOp op);

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
class ArrayRefCopyOpGenericAdaptor : public detail::ArrayRefCopyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefCopyOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_source = 1;
public:
  ArrayRefCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefCopyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefCopyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefCopyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefCopyOpGenericAdaptor(RangeT values, const ArrayRefCopyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefCopyOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefCopyOp>>>
  ArrayRefCopyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getSource() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayRefCopyOpAdaptor : public ArrayRefCopyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefCopyOpGenericAdaptor::ArrayRefCopyOpGenericAdaptor;
  ArrayRefCopyOpAdaptor(ArrayRefCopyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefCopyOp : public ::mlir::Op<ArrayRefCopyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefCopyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefCopyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_source = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.copy");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getSource() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value source);
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCopyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCopyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefCopyOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefCreateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefCreateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefCreateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.create", odsAttrs.getContext());
  }

  ArrayRefCreateOpGenericAdaptorBase(ArrayRefCreateOp op);

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
class ArrayRefCreateOpGenericAdaptor : public detail::ArrayRefCreateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefCreateOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_elements = 1;
public:
  ArrayRefCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefCreateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefCreateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefCreateOpGenericAdaptor(RangeT values, const ArrayRefCreateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefCreateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefCreateOp>>>
  ArrayRefCreateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getElements() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayRefCreateOpAdaptor : public ArrayRefCreateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefCreateOpGenericAdaptor::ArrayRefCreateOpGenericAdaptor;
  ArrayRefCreateOpAdaptor(ArrayRefCreateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefCreateOp : public ::mlir::Op<ArrayRefCreateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefCreateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefCreateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_elements = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.create");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getElements() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::ValueRange elements);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::ValueRange elements);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange elements);
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::ValueRange elements);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefCreateOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefFromArrayOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefFromArrayOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefFromArrayOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.from_array", odsAttrs.getContext());
  }

  ArrayRefFromArrayOpGenericAdaptorBase(ArrayRefFromArrayOp op);

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
class ArrayRefFromArrayOpGenericAdaptor : public detail::ArrayRefFromArrayOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefFromArrayOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_array = 1;
public:
  ArrayRefFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefFromArrayOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefFromArrayOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefFromArrayOpGenericAdaptor(RangeT values, const ArrayRefFromArrayOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefFromArrayOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefFromArrayOp>>>
  ArrayRefFromArrayOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getArray() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayRefFromArrayOpAdaptor : public ArrayRefFromArrayOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefFromArrayOpGenericAdaptor::ArrayRefFromArrayOpGenericAdaptor;
  ArrayRefFromArrayOpAdaptor(ArrayRefFromArrayOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefFromArrayOp : public ::mlir::Op<ArrayRefFromArrayOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefFromArrayOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefFromArrayOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_array = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.from_array");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getArray() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getArrayMutable() {
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value array);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value array);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value array);
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value array);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefFromArrayOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefGetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.get", odsAttrs.getContext());
  }

  ArrayRefGetOpGenericAdaptorBase(ArrayRefGetOp op);

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
class ArrayRefGetOpGenericAdaptor : public detail::ArrayRefGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefGetOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
public:
  ArrayRefGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefGetOpGenericAdaptor(RangeT values, const ArrayRefGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefGetOp>>>
  ArrayRefGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayRefGetOpAdaptor : public ArrayRefGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefGetOpGenericAdaptor::ArrayRefGetOpGenericAdaptor;
  ArrayRefGetOpAdaptor(ArrayRefGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefGetOp : public ::mlir::Op<ArrayRefGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
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

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefGetOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefInjectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefInjectOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefInjectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.inject", odsAttrs.getContext());
  }

  ArrayRefInjectOpGenericAdaptorBase(ArrayRefInjectOp op);

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
class ArrayRefInjectOpGenericAdaptor : public detail::ArrayRefInjectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefInjectOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_element = 2;
public:
  ArrayRefInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefInjectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefInjectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefInjectOpGenericAdaptor(RangeT values, const ArrayRefInjectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefInjectOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefInjectOp>>>
  ArrayRefInjectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayRefInjectOpAdaptor : public ArrayRefInjectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefInjectOpGenericAdaptor::ArrayRefInjectOpGenericAdaptor;
  ArrayRefInjectOpAdaptor(ArrayRefInjectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefInjectOp : public ::mlir::Op<ArrayRefInjectOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefInjectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefInjectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_element = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.inject");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefInjectOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefSliceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.slice", odsAttrs.getContext());
  }

  ArrayRefSliceOpGenericAdaptorBase(ArrayRefSliceOp op);

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
class ArrayRefSliceOpGenericAdaptor : public detail::ArrayRefSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_lowIndex = 1;
public:
  ArrayRefSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefSliceOpGenericAdaptor(RangeT values, const ArrayRefSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefSliceOp>>>
  ArrayRefSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayRefSliceOpAdaptor : public ArrayRefSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefSliceOpGenericAdaptor::ArrayRefSliceOpGenericAdaptor;
  ArrayRefSliceOpAdaptor(ArrayRefSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefSliceOp : public ::mlir::Op<ArrayRefSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::ArrayRefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_lowIndex = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IndexType> getLowIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSOperands(1).begin());
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

  ::mlir::TypedValue<circt::arc::ArrayRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArrayRefSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArrayRefSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value lowIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArrayRefSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArrayRefSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefSliceOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ArrayRefToArrayOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayRefToArrayOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayRefToArrayOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.arrayref.to_array", odsAttrs.getContext());
  }

  ArrayRefToArrayOpGenericAdaptorBase(ArrayRefToArrayOp op);

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
class ArrayRefToArrayOpGenericAdaptor : public detail::ArrayRefToArrayOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayRefToArrayOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ArrayRefToArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayRefToArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayRefToArrayOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayRefToArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayRefToArrayOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayRefToArrayOpGenericAdaptor(RangeT values, const ArrayRefToArrayOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayRefToArrayOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayRefToArrayOp>>>
  ArrayRefToArrayOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayRefToArrayOpAdaptor : public ArrayRefToArrayOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayRefToArrayOpGenericAdaptor::ArrayRefToArrayOpGenericAdaptor;
  ArrayRefToArrayOpAdaptor(ArrayRefToArrayOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayRefToArrayOp : public ::mlir::Op<ArrayRefToArrayOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayRefToArrayOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayRefToArrayOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.arrayref.to_array");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::ArrayRefType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::ArrayRefType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefToArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayRefToArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefToArrayOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CallOpGenericAdaptorBase {
public:
  struct Properties {
    using arcTy = ::mlir::FlatSymbolRefAttr;
    arcTy arc;

    auto getArc() const {
      auto &propStorage = this->arc;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setArc(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->arc = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arc == this->arc &&
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
      odsOpName.emplace("arc.call", odsAttrs.getContext());
  }

  CallOpGenericAdaptorBase(CallOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getArcAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
    return attr;
  }

  ::llvm::StringRef getArc();
};

} // namespace detail
template <typename RangeT>
class CallOpGenericAdaptor : public detail::CallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CallOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
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

  RangeT getInputs() {
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
class CallOp : public ::mlir::Op<CallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::circt::arc::ClockedOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arc")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArcAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArcAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.call");
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
  ::mlir::FlatSymbolRefAttr getArcAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
  }

  ::llvm::StringRef getArc();
  void setArcAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().arc = attr;
  }

  void setArc(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, DefineOp arc, mlir::ValueRange inputs = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, DefineOp arc, mlir::ValueRange inputs = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, DefineOp arc, mlir::ValueRange inputs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs);
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs);
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::llvm::StringRef arc, ::mlir::ValueRange inputs);
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::llvm::StringRef arc, ::mlir::ValueRange inputs);
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::llvm::StringRef arc, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static bool isClocked();
  ::mlir::Value getClock();
  void eraseClock();
  uint32_t getLatency();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
  operand_range getArgOperands() {
    return {operand_begin(), operand_end()};
  }
  MutableOperandRange getArgOperandsMutable() {
    return getInputsMutable();
  }

  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("arc");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getArcAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CallOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::CallOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineCallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineCallOpGenericAdaptorBase {
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
  CoroutineCallOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.call", odsAttrs.getContext());
  }

  CoroutineCallOpGenericAdaptorBase(CoroutineCallOp op);

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
class CoroutineCallOpGenericAdaptor : public detail::CoroutineCallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineCallOpGenericAdaptorBase;
  static constexpr int odsIndex_state = 0;
  static constexpr int odsIndex_pc = 1;
  static constexpr int odsIndex_args = 2;
public:
  CoroutineCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineCallOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineCallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineCallOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineCallOpGenericAdaptor(RangeT values, const CoroutineCallOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineCallOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineCallOp>>>
  CoroutineCallOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getState() {
    return (*getODSOperands(0).begin());
  }

  ValueT getPc() {
    return (*getODSOperands(1).begin());
  }

  RangeT getArgs() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutineCallOpAdaptor : public CoroutineCallOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineCallOpGenericAdaptor::CoroutineCallOpGenericAdaptor;
  CoroutineCallOpAdaptor(CoroutineCallOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineCallOp : public ::mlir::Op<CoroutineCallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineCallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineCallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_state = 0;
  static constexpr int odsIndex_pc = 1;
  static constexpr int odsIndex_args = 2;
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

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.call");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::CoroutineStateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutineStateType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<circt::arc::CoroutinePCType> getPc() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutinePCType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(2);
  }

  ::mlir::OpOperand &getStateMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getPcMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::CoroutineStateType> getResumeState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutineStateType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<circt::arc::CoroutinePCType> getResumePC() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutinePCType>>(*getODSResults(1).begin());
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(2);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resumeState, ::mlir::Type resumePC, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::Value state, ::mlir::Value pc, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineCallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineCallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  operand_range getArgOperands() {
    return getArgs();
  }
  MutableOperandRange getArgOperandsMutable() {
    return getArgsMutable();
  }

  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("callee");
  }

  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getCalleeAttrName(),
                     llvm::cast<mlir::SymbolRefAttr>(callee));
  }

  /// CallOpInterface requires ArgAndResultAttrsOpInterface. Call sites
  /// don't carry these attributes, so stub them out as no-ops.
  mlir::ArrayAttr getArgAttrsAttr() { return nullptr; }
  mlir::ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(mlir::ArrayAttr args) {}
  void setResAttrsAttr(mlir::ArrayAttr args) {}
  mlir::Attribute removeArgAttrsAttr() { return nullptr; }
  mlir::Attribute removeResAttrsAttr() { return nullptr; }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineCallOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::CoroutineCallOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineDefineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineDefineOpGenericAdaptorBase {
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
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
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
  CoroutineDefineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.define", odsAttrs.getContext());
  }

  CoroutineDefineOpGenericAdaptorBase(CoroutineDefineOp op);

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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class CoroutineDefineOpGenericAdaptor : public detail::CoroutineDefineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineDefineOpGenericAdaptorBase;
public:
  CoroutineDefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineDefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineDefineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineDefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineDefineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineDefineOpGenericAdaptor(RangeT values, const CoroutineDefineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineDefineOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineDefineOp>>>
  CoroutineDefineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CoroutineDefineOpAdaptor : public CoroutineDefineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineDefineOpGenericAdaptor::CoroutineDefineOpGenericAdaptor;
  CoroutineDefineOpAdaptor(CoroutineDefineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineDefineOp : public ::mlir::Op<CoroutineDefineOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineDefineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineDefineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name")};
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

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.define");
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineDefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineDefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Returns the argument types of this coroutine.
  mlir::ArrayRef<mlir::Type> getArgumentTypes() {
    return getFunctionType().getInputs();
  }

  /// Returns the result types of this coroutine.
  mlir::ArrayRef<mlir::Type> getResultTypes() {
    return getFunctionType().getResults();
  }

  mlir::Region *getCallableRegion() { return &getBody(); }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineDefineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::CoroutineDefineOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineHaltOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineHaltOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutineHaltOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.halt", odsAttrs.getContext());
  }

  CoroutineHaltOpGenericAdaptorBase(CoroutineHaltOp op);

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
class CoroutineHaltOpGenericAdaptor : public detail::CoroutineHaltOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineHaltOpGenericAdaptorBase;
  static constexpr int odsIndex_yieldOperands = 0;
public:
  CoroutineHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineHaltOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineHaltOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineHaltOpGenericAdaptor(RangeT values, const CoroutineHaltOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineHaltOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineHaltOp>>>
  CoroutineHaltOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getYieldOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutineHaltOpAdaptor : public CoroutineHaltOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineHaltOpGenericAdaptor::CoroutineHaltOpGenericAdaptor;
  CoroutineHaltOpAdaptor(CoroutineHaltOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineHaltOp : public ::mlir::Op<CoroutineHaltOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<CoroutineDefineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineHaltOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineHaltOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_yieldOperands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.halt");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getYieldOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getYieldOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange yieldOperands);
  static CoroutineHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange yieldOperands);
  static CoroutineHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange yieldOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineHaltOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineInstanceOpGenericAdaptorBase {
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
  CoroutineInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.instance", odsAttrs.getContext());
  }

  CoroutineInstanceOpGenericAdaptorBase(CoroutineInstanceOp op);

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
class CoroutineInstanceOpGenericAdaptor : public detail::CoroutineInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineInstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  CoroutineInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineInstanceOpGenericAdaptor(RangeT values, const CoroutineInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineInstanceOp>>>
  CoroutineInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CoroutineInstanceOpAdaptor : public CoroutineInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineInstanceOpGenericAdaptor::CoroutineInstanceOpGenericAdaptor;
  CoroutineInstanceOpAdaptor(CoroutineInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineInstanceOp : public ::mlir::Op<CoroutineInstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<hw::HWModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
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
    return ::llvm::StringLiteral("arc.coroutine.instance");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange args);
  static CoroutineInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange args);
  static CoroutineInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange args);
  static CoroutineInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange args);
  static CoroutineInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  operand_range getArgOperands() {
    return getArgs();
  }
  MutableOperandRange getArgOperandsMutable() {
    return getArgsMutable();
  }

  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("callee");
  }

  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getCalleeAttrName(),
                     llvm::cast<mlir::SymbolRefAttr>(callee));
  }

  mlir::ArrayAttr getArgAttrsAttr() { return nullptr; }
  mlir::ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(mlir::ArrayAttr args) {}
  void setResAttrsAttr(mlir::ArrayAttr args) {}
  mlir::Attribute removeArgAttrsAttr() { return nullptr; }
  mlir::Attribute removeResAttrsAttr() { return nullptr; }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::CoroutineInstanceOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutinePCIsHaltOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutinePCIsHaltOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutinePCIsHaltOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.pc_is_halt", odsAttrs.getContext());
  }

  CoroutinePCIsHaltOpGenericAdaptorBase(CoroutinePCIsHaltOp op);

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
class CoroutinePCIsHaltOpGenericAdaptor : public detail::CoroutinePCIsHaltOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutinePCIsHaltOpGenericAdaptorBase;
  static constexpr int odsIndex_pc = 0;
public:
  CoroutinePCIsHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutinePCIsHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutinePCIsHaltOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutinePCIsHaltOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutinePCIsHaltOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutinePCIsHaltOpGenericAdaptor(RangeT values, const CoroutinePCIsHaltOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutinePCIsHaltOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutinePCIsHaltOp>>>
  CoroutinePCIsHaltOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPc() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutinePCIsHaltOpAdaptor : public CoroutinePCIsHaltOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutinePCIsHaltOpGenericAdaptor::CoroutinePCIsHaltOpGenericAdaptor;
  CoroutinePCIsHaltOpAdaptor(CoroutinePCIsHaltOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutinePCIsHaltOp : public ::mlir::Op<CoroutinePCIsHaltOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutinePCIsHaltOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutinePCIsHaltOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_pc = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.pc_is_halt");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::CoroutinePCType> getPc() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutinePCType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPcMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsHaltOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsHaltOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutinePCIsHaltOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutinePCIsReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutinePCIsReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutinePCIsReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.pc_is_return", odsAttrs.getContext());
  }

  CoroutinePCIsReturnOpGenericAdaptorBase(CoroutinePCIsReturnOp op);

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
class CoroutinePCIsReturnOpGenericAdaptor : public detail::CoroutinePCIsReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutinePCIsReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_pc = 0;
public:
  CoroutinePCIsReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutinePCIsReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutinePCIsReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutinePCIsReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutinePCIsReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutinePCIsReturnOpGenericAdaptor(RangeT values, const CoroutinePCIsReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutinePCIsReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutinePCIsReturnOp>>>
  CoroutinePCIsReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPc() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutinePCIsReturnOpAdaptor : public CoroutinePCIsReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutinePCIsReturnOpGenericAdaptor::CoroutinePCIsReturnOpGenericAdaptor;
  CoroutinePCIsReturnOpAdaptor(CoroutinePCIsReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutinePCIsReturnOp : public ::mlir::Op<CoroutinePCIsReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutinePCIsReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutinePCIsReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_pc = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.pc_is_return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::CoroutinePCType> getPc() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutinePCType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPcMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value pc);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutinePCIsReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutinePCIsReturnOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutineReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.return", odsAttrs.getContext());
  }

  CoroutineReturnOpGenericAdaptorBase(CoroutineReturnOp op);

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
class CoroutineReturnOpGenericAdaptor : public detail::CoroutineReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_yieldOperands = 0;
public:
  CoroutineReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineReturnOpGenericAdaptor(RangeT values, const CoroutineReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineReturnOp>>>
  CoroutineReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getYieldOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutineReturnOpAdaptor : public CoroutineReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineReturnOpGenericAdaptor::CoroutineReturnOpGenericAdaptor;
  CoroutineReturnOpAdaptor(CoroutineReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineReturnOp : public ::mlir::Op<CoroutineReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<CoroutineDefineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_yieldOperands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getYieldOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getYieldOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange yieldOperands);
  static CoroutineReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange yieldOperands);
  static CoroutineReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange yieldOperands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineReturnOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineStartPCOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineStartPCOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutineStartPCOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.start_pc", odsAttrs.getContext());
  }

  CoroutineStartPCOpGenericAdaptorBase(CoroutineStartPCOp op);

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
class CoroutineStartPCOpGenericAdaptor : public detail::CoroutineStartPCOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineStartPCOpGenericAdaptorBase;
public:
  CoroutineStartPCOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineStartPCOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineStartPCOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineStartPCOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineStartPCOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineStartPCOpGenericAdaptor(RangeT values, const CoroutineStartPCOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineStartPCOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineStartPCOp>>>
  CoroutineStartPCOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CoroutineStartPCOpAdaptor : public CoroutineStartPCOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineStartPCOpGenericAdaptor::CoroutineStartPCOpGenericAdaptor;
  CoroutineStartPCOpAdaptor(CoroutineStartPCOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineStartPCOp : public ::mlir::Op<CoroutineStartPCOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::CoroutinePCType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineStartPCOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineStartPCOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.start_pc");
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

  ::mlir::TypedValue<circt::arc::CoroutinePCType> getPc() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutinePCType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type pc);
  static CoroutineStartPCOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type pc);
  static CoroutineStartPCOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type pc);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static CoroutineStartPCOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static CoroutineStartPCOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineStartPCOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineStartPCOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineStartPCOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineStartPCOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineStartPCOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineUndefinedStateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineUndefinedStateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CoroutineUndefinedStateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.undefined_state", odsAttrs.getContext());
  }

  CoroutineUndefinedStateOpGenericAdaptorBase(CoroutineUndefinedStateOp op);

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
class CoroutineUndefinedStateOpGenericAdaptor : public detail::CoroutineUndefinedStateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineUndefinedStateOpGenericAdaptorBase;
public:
  CoroutineUndefinedStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineUndefinedStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineUndefinedStateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineUndefinedStateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoroutineUndefinedStateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineUndefinedStateOpGenericAdaptor(RangeT values, const CoroutineUndefinedStateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineUndefinedStateOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineUndefinedStateOp>>>
  CoroutineUndefinedStateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CoroutineUndefinedStateOpAdaptor : public CoroutineUndefinedStateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineUndefinedStateOpGenericAdaptor::CoroutineUndefinedStateOpGenericAdaptor;
  CoroutineUndefinedStateOpAdaptor(CoroutineUndefinedStateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineUndefinedStateOp : public ::mlir::Op<CoroutineUndefinedStateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::CoroutineStateType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineUndefinedStateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineUndefinedStateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.coroutine.undefined_state");
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

  ::mlir::TypedValue<circt::arc::CoroutineStateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::CoroutineStateType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state);
  static CoroutineUndefinedStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state);
  static CoroutineUndefinedStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static CoroutineUndefinedStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static CoroutineUndefinedStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineUndefinedStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineUndefinedStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineUndefinedStateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineUndefinedStateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineUndefinedStateOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CoroutineYieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoroutineYieldOpGenericAdaptorBase {
public:
  struct Properties {
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
  CoroutineYieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.coroutine.yield", odsAttrs.getContext());
  }

  CoroutineYieldOpGenericAdaptorBase(CoroutineYieldOp op);

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
class CoroutineYieldOpGenericAdaptor : public detail::CoroutineYieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoroutineYieldOpGenericAdaptorBase;
  static constexpr int odsIndex_yieldOperands = 0;
  static constexpr int odsIndex_destOperands = 1;
public:
  CoroutineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoroutineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoroutineYieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoroutineYieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CoroutineYieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoroutineYieldOpGenericAdaptor(RangeT values, const CoroutineYieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoroutineYieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoroutineYieldOp>>>
  CoroutineYieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getYieldOperands() {
    return getODSOperands(0);
  }

  RangeT getDestOperands() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoroutineYieldOpAdaptor : public CoroutineYieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoroutineYieldOpGenericAdaptor::CoroutineYieldOpGenericAdaptor;
  CoroutineYieldOpAdaptor(CoroutineYieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoroutineYieldOp : public ::mlir::Op<CoroutineYieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::HasParent<CoroutineDefineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::BranchOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoroutineYieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoroutineYieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_yieldOperands = 0;
  static constexpr int odsIndex_destOperands = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::BranchOpInterface::Trait<CoroutineYieldOp>::getSuccessorForOperands;
  using ::mlir::BranchOpInterface::Trait<CoroutineYieldOp>::areTypesCompatible;
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
    return ::llvm::StringLiteral("arc.coroutine.yield");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getYieldOperands() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getDestOperands() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getYieldOperandsMutable();
  ::mlir::MutableOperandRange getDestOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Block *getDest() {
    return (*this)->getSuccessor(0);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static CoroutineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static CoroutineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static CoroutineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static CoroutineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange yieldOperands, ::mlir::ValueRange destOperands, ::mlir::Block *dest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoroutineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineYieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoroutineYieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::SuccessorOperands getSuccessorOperands(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineYieldOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::CoroutineYieldOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::CurrentTimeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CurrentTimeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CurrentTimeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.current_time", odsAttrs.getContext());
  }

  CurrentTimeOpGenericAdaptorBase(CurrentTimeOp op);

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
class CurrentTimeOpGenericAdaptor : public detail::CurrentTimeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CurrentTimeOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  CurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CurrentTimeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CurrentTimeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CurrentTimeOpGenericAdaptor(RangeT values, const CurrentTimeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CurrentTimeOp, typename = std::enable_if_t<std::is_same_v<LateInst, CurrentTimeOp>>>
  CurrentTimeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CurrentTimeOpAdaptor : public CurrentTimeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CurrentTimeOpGenericAdaptor::CurrentTimeOpGenericAdaptor;
  CurrentTimeOpAdaptor(CurrentTimeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CurrentTimeOp : public ::mlir::Op<CurrentTimeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CurrentTimeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CurrentTimeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.current_time");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type time, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type time, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type time, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CurrentTimeOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::DefineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DefineOpGenericAdaptorBase {
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
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
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
  DefineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.define", odsAttrs.getContext());
  }

  DefineOpGenericAdaptorBase(DefineOp op);

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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DefineOpGenericAdaptor : public detail::DefineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DefineOpGenericAdaptorBase;
public:
  DefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DefineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DefineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DefineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DefineOpGenericAdaptor(RangeT values, const DefineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DefineOp, typename = std::enable_if_t<std::is_same_v<LateInst, DefineOp>>>
  DefineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DefineOpAdaptor : public DefineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DefineOpGenericAdaptor::DefineOpGenericAdaptor;
  DefineOpAdaptor(DefineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DefineOp : public ::mlir::Op<DefineOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<arc::OutputOp>::Impl, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::RegionKindInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DefineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DefineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name")};
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

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.define");
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringAttr sym_name, mlir::TypeAttr function_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringRef sym_name, mlir::FunctionType function_type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DefineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DefineOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
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
  static mlir::RegionKind getRegionKind(unsigned index) {
    return mlir::RegionKind::SSACFG;
  }

  mlir::Block &getBodyBlock() { return getBody().front(); }

  // Get the arc's symbolic name.
  mlir::StringAttr getNameAttr() {
    return (*this)->getAttrOfType<mlir::StringAttr>(
      ::mlir::SymbolTable::getSymbolAttrName());
  }

  // Get the arc's symbolic name.
  mlir::StringRef getName() {
    return getNameAttr().getValue();
  }

  /// Returns the argument types of this function.
  mlir::ArrayRef<mlir::Type> getArgumentTypes() {
    return getFunctionType().getInputs();
  }

  /// Returns the result types of this function.
  mlir::ArrayRef<mlir::Type> getResultTypes() {
    return getFunctionType().getResults();
  }

  /// Verify the type attribute of this function. Returns failure and emits
  /// an error if the attribute is invalid.
  mlir::LogicalResult verifyType() {
    auto type = getFunctionTypeAttr().getValue();
    if (!llvm::isa<mlir::FunctionType>(type))
      return emitOpError("requires '") << getFunctionTypeAttrName() <<
                         "' attribute of function type";
    return mlir::success();
  }

  /// Returns true if the arc returns the inputs directly and in the same
  /// order, otherwise false.
  bool isPassthrough();

  //===------------------------------------------------------------------===//
  // CallableOpInterface
  //===------------------------------------------------------------------===//

  mlir::Region *getCallableRegion() { return &getBody(); }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::DefineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::DefineOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ExecuteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExecuteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ExecuteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.execute", odsAttrs.getContext());
  }

  ExecuteOpGenericAdaptorBase(ExecuteOp op);

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
class ExecuteOpGenericAdaptor : public detail::ExecuteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExecuteOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ExecuteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExecuteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExecuteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExecuteOpGenericAdaptor(RangeT values, const ExecuteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExecuteOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExecuteOp>>>
  ExecuteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExecuteOpAdaptor : public ExecuteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExecuteOpGenericAdaptor::ExecuteOpGenericAdaptor;
  ExecuteOpAdaptor(ExecuteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExecuteOp : public ::mlir::Op<ExecuteOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExecuteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExecuteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.execute");
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
  static ExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExecuteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ExecuteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ExecuteOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::FinalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FinalOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FinalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.final", odsAttrs.getContext());
  }

  FinalOpGenericAdaptorBase(FinalOp op);

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
class FinalOpGenericAdaptor : public detail::FinalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FinalOpGenericAdaptorBase;
public:
  FinalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FinalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FinalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FinalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FinalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FinalOpGenericAdaptor(RangeT values, const FinalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FinalOp, typename = std::enable_if_t<std::is_same_v<LateInst, FinalOp>>>
  FinalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FinalOpAdaptor : public FinalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FinalOpGenericAdaptor::FinalOpGenericAdaptor;
  FinalOpAdaptor(FinalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FinalOp : public ::mlir::Op<FinalOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::HasParent<ModelOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FinalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FinalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.final");
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
  static FinalOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static FinalOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static FinalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static FinalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FinalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FinalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FinalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FinalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::FinalOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::GetNextWakeupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetNextWakeupOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetNextWakeupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.get_next_wakeup", odsAttrs.getContext());
  }

  GetNextWakeupOpGenericAdaptorBase(GetNextWakeupOp op);

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
class GetNextWakeupOpGenericAdaptor : public detail::GetNextWakeupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetNextWakeupOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  GetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GetNextWakeupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetNextWakeupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetNextWakeupOpGenericAdaptor(RangeT values, const GetNextWakeupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetNextWakeupOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetNextWakeupOp>>>
  GetNextWakeupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetNextWakeupOpAdaptor : public GetNextWakeupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetNextWakeupOpGenericAdaptor::GetNextWakeupOpGenericAdaptor;
  GetNextWakeupOpAdaptor(GetNextWakeupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetNextWakeupOp : public ::mlir::Op<GetNextWakeupOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetNextWakeupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetNextWakeupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.get_next_wakeup");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type time, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type time, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type time, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::GetNextWakeupOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::InitialOp declarations
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
      odsOpName.emplace("arc.initial", odsAttrs.getContext());
  }

  InitialOpGenericAdaptorBase(InitialOp op);

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
class InitialOpGenericAdaptor : public detail::InitialOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InitialOpGenericAdaptorBase;
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
class InitialOp : public ::mlir::Op<InitialOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::HasParent<ModelOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InitialOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InitialOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.initial");
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
  static InitialOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static InitialOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static InitialOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static InitialOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InitialOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InitialOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InitialOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InitialOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::InitialOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::LutOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LutOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LutOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.lut", odsAttrs.getContext());
  }

  LutOpGenericAdaptorBase(LutOp op);

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
class LutOpGenericAdaptor : public detail::LutOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LutOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  LutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LutOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LutOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LutOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LutOpGenericAdaptor(RangeT values, const LutOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LutOp, typename = std::enable_if_t<std::is_same_v<LateInst, LutOp>>>
  LutOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LutOpAdaptor : public LutOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LutOpGenericAdaptor::LutOpGenericAdaptor;
  LutOpAdaptor(LutOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LutOp : public ::mlir::Op<LutOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<arc::OutputOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LutOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LutOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.lut");
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

  ::mlir::TypedValue<::mlir::IntegerType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ValueRange inputs);
  static LutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::ValueRange inputs);
  static LutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LutOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LutOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  mlir::Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::LutOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::MemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.memory", odsAttrs.getContext());
  }

  MemoryOpGenericAdaptorBase(MemoryOp op);

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
class MemoryOpGenericAdaptor : public detail::MemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryOpGenericAdaptorBase;
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
class MemoryOp : public ::mlir::Op<MemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::MemoryType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.memory");
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

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory);
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory);
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::MemoryReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryReadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemoryReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.memory_read", odsAttrs.getContext());
  }

  MemoryReadOpGenericAdaptorBase(MemoryReadOp op);

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
class MemoryReadOpGenericAdaptor : public detail::MemoryReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryReadOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
public:
  MemoryReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryReadOpGenericAdaptor(RangeT values, const MemoryReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryReadOp>>>
  MemoryReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryReadOpAdaptor : public MemoryReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryReadOpGenericAdaptor::MemoryReadOpGenericAdaptor;
  MemoryReadOpAdaptor(MemoryReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryReadOp : public ::mlir::Op<MemoryReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.memory_read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryReadOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::MemoryReadPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryReadPortOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemoryReadPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.memory_read_port", odsAttrs.getContext());
  }

  MemoryReadPortOpGenericAdaptorBase(MemoryReadPortOp op);

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
class MemoryReadPortOpGenericAdaptor : public detail::MemoryReadPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryReadPortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
public:
  MemoryReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryReadPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryReadPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryReadPortOpGenericAdaptor(RangeT values, const MemoryReadPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryReadPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryReadPortOp>>>
  MemoryReadPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryReadPortOpAdaptor : public MemoryReadPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryReadPortOpGenericAdaptor::MemoryReadPortOpGenericAdaptor;
  MemoryReadPortOpAdaptor(MemoryReadPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryReadPortOp : public ::mlir::Op<MemoryReadPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryReadPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryReadPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.memory_read_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryReadPortOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::MemoryWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryWriteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemoryWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.memory_write", odsAttrs.getContext());
  }

  MemoryWriteOpGenericAdaptorBase(MemoryWriteOp op);

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
class MemoryWriteOpGenericAdaptor : public detail::MemoryWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_data = 2;
public:
  MemoryWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryWriteOpGenericAdaptor(RangeT values, const MemoryWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryWriteOp>>>
  MemoryWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getData() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryWriteOpAdaptor : public MemoryWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryWriteOpGenericAdaptor::MemoryWriteOpGenericAdaptor;
  MemoryWriteOpAdaptor(MemoryWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryWriteOp : public ::mlir::Op<MemoryWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_data = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.memory_write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getDataMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static MemoryWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static MemoryWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static MemoryWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static MemoryWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value data);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryWriteOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::MemoryWritePortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryWritePortOpGenericAdaptorBase {
public:
  struct Properties {
    using arcTy = ::mlir::FlatSymbolRefAttr;
    arcTy arc;

    auto getArc() const {
      auto &propStorage = this->arc;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setArc(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->arc = propValue;
    }
    using enableTy = ::mlir::UnitAttr;
    enableTy enable;

    auto getEnable() const {
      auto &propStorage = this->enable;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setEnable(const ::mlir::UnitAttr &propValue) {
      this->enable = propValue;
    }
    using latencyTy = ::mlir::IntegerAttr;
    latencyTy latency;

    auto getLatency() const {
      auto &propStorage = this->latency;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setLatency(const ::mlir::IntegerAttr &propValue) {
      this->latency = propValue;
    }
    using maskTy = ::mlir::UnitAttr;
    maskTy mask;

    auto getMask() const {
      auto &propStorage = this->mask;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setMask(const ::mlir::UnitAttr &propValue) {
      this->mask = propValue;
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
        rhs.arc == this->arc &&
        rhs.enable == this->enable &&
        rhs.latency == this->latency &&
        rhs.mask == this->mask &&
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
  MemoryWritePortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.memory_write_port", odsAttrs.getContext());
  }

  MemoryWritePortOpGenericAdaptorBase(MemoryWritePortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getArcAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
    return attr;
  }

  ::llvm::StringRef getArc();
  ::mlir::UnitAttr getEnableAttr();
  bool getEnable();
  ::mlir::UnitAttr getMaskAttr();
  bool getMask();
  ::mlir::IntegerAttr getLatencyAttr();
  uint32_t getLatency();
};

} // namespace detail
template <typename RangeT>
class MemoryWritePortOpGenericAdaptor : public detail::MemoryWritePortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryWritePortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_inputs = 1;
  static constexpr int odsIndex_clock = 2;
public:
  MemoryWritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryWritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryWritePortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryWritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : MemoryWritePortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryWritePortOpGenericAdaptor(RangeT values, const MemoryWritePortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryWritePortOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryWritePortOp>>>
  MemoryWritePortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getInputs() {
    return getODSOperands(1);
  }

  ValueT getClock() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryWritePortOpAdaptor : public MemoryWritePortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryWritePortOpGenericAdaptor::MemoryWritePortOpGenericAdaptor;
  MemoryWritePortOpAdaptor(MemoryWritePortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryWritePortOp : public ::mlir::Op<MemoryWritePortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::circt::arc::ClockedOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryWritePortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryWritePortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_inputs = 1;
  static constexpr int odsIndex_clock = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arc"), ::llvm::StringRef("enable"), ::llvm::StringRef("latency"), ::llvm::StringRef("mask"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArcAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArcAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getEnableAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getEnableAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getLatencyAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getMaskAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getMaskAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.memory_write_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::MemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::MemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::circt::seq::ClockType>{} : ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*operands.begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::MutableOperandRange getClockMutable();
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
  ::mlir::FlatSymbolRefAttr getArcAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
  }

  ::llvm::StringRef getArc();
  ::mlir::UnitAttr getEnableAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().enable);
  }

  bool getEnable();
  ::mlir::UnitAttr getMaskAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().mask);
  }

  bool getMask();
  ::mlir::IntegerAttr getLatencyAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().latency);
  }

  uint32_t getLatency();
  void setArcAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().arc = attr;
  }

  void setArc(::llvm::StringRef attrValue);
  void setEnableAttr(::mlir::UnitAttr attr) {
    getProperties().enable = attr;
  }

  void setEnable(bool attrValue);
  void setMaskAttr(::mlir::UnitAttr attr) {
    getProperties().mask = attr;
  }

  void setMask(bool attrValue);
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint32_t attrValue);
  ::mlir::Attribute removeEnableAttr() {
      auto attr = getProperties().enable;
      getProperties().enable = {};
      return attr;
  }

  ::mlir::Attribute removeMaskAttr() {
      auto attr = getProperties().mask;
      getProperties().mask = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::FlatSymbolRefAttr arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/::mlir::UnitAttr enable = nullptr, /*optional*/::mlir::UnitAttr mask = nullptr, ::mlir::IntegerAttr latency = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef arc, ::mlir::ValueRange inputs, /*optional*/::mlir::Value clock, /*optional*/bool enable = false, /*optional*/bool mask = false, uint32_t latency = 1);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryWritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryWritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  SmallVector<Type> getArcResultTypes();
  static unsigned getAddressIdx() { return 0; }
  static unsigned getDataIdx() { return 1; }
  static unsigned getEnableIdx() { return 2; }
  static unsigned getMaskIdx(bool hasEnable) { return hasEnable ? 3 : 2; }

  operand_range getArgOperands() {
    return getInputs();
  }
  MutableOperandRange getArgOperandsMutable() {
    return getInputsMutable();
  }

  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("arc");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getArcAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryWritePortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::MemoryWritePortOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ModelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ModelOpGenericAdaptorBase {
public:
  struct Properties {
    using finalFnTy = ::mlir::FlatSymbolRefAttr;
    finalFnTy finalFn;

    auto getFinalFn() const {
      auto &propStorage = this->finalFn;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setFinalFn(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->finalFn = propValue;
    }
    using initialFnTy = ::mlir::FlatSymbolRefAttr;
    initialFnTy initialFn;

    auto getInitialFn() const {
      auto &propStorage = this->initialFn;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setInitialFn(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->initialFn = propValue;
    }
    using ioTy = ::mlir::TypeAttr;
    ioTy io;

    auto getIo() const {
      auto &propStorage = this->io;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setIo(const ::mlir::TypeAttr &propValue) {
      this->io = propValue;
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
    using traceTapsTy = ::mlir::ArrayAttr;
    traceTapsTy traceTaps;

    auto getTraceTaps() const {
      auto &propStorage = this->traceTaps;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setTraceTaps(const ::mlir::ArrayAttr &propValue) {
      this->traceTaps = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.finalFn == this->finalFn &&
        rhs.initialFn == this->initialFn &&
        rhs.io == this->io &&
        rhs.sym_name == this->sym_name &&
        rhs.traceTaps == this->traceTaps &&
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
  ModelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.model", odsAttrs.getContext());
  }

  ModelOpGenericAdaptorBase(ModelOp op);

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
  ::mlir::TypeAttr getIoAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().io);
    return attr;
  }

  ::circt::hw::ModuleType getIo();
  ::mlir::FlatSymbolRefAttr getInitialFnAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().initialFn);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getInitialFn();
  ::mlir::FlatSymbolRefAttr getFinalFnAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().finalFn);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getFinalFn();
  ::mlir::ArrayAttr getTraceTapsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().traceTaps);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getTraceTaps();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ModelOpGenericAdaptor : public detail::ModelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ModelOpGenericAdaptorBase;
public:
  ModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ModelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ModelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ModelOpGenericAdaptor(RangeT values, const ModelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ModelOp, typename = std::enable_if_t<std::is_same_v<LateInst, ModelOp>>>
  ModelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ModelOpAdaptor : public ModelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ModelOpGenericAdaptor::ModelOpGenericAdaptor;
  ModelOpAdaptor(ModelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ModelOp : public ::mlir::Op<ModelOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ModelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ModelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("finalFn"), ::llvm::StringRef("initialFn"), ::llvm::StringRef("io"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("traceTaps")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFinalFnAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFinalFnAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInitialFnAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInitialFnAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIoAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIoAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getTraceTapsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getTraceTapsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.model");
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
  ::mlir::TypeAttr getIoAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().io);
  }

  ::circt::hw::ModuleType getIo();
  ::mlir::FlatSymbolRefAttr getInitialFnAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().initialFn);
  }

  ::std::optional< ::llvm::StringRef > getInitialFn();
  ::mlir::FlatSymbolRefAttr getFinalFnAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().finalFn);
  }

  ::std::optional< ::llvm::StringRef > getFinalFn();
  ::mlir::ArrayAttr getTraceTapsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().traceTaps);
  }

  ::std::optional< ::mlir::ArrayAttr > getTraceTaps();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setIoAttr(::mlir::TypeAttr attr) {
    getProperties().io = attr;
  }

  void setIo(::circt::hw::ModuleType attrValue);
  void setInitialFnAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().initialFn = attr;
  }

  void setInitialFn(::std::optional<::llvm::StringRef> attrValue);
  void setFinalFnAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().finalFn = attr;
  }

  void setFinalFn(::std::optional<::llvm::StringRef> attrValue);
  void setTraceTapsAttr(::mlir::ArrayAttr attr) {
    getProperties().traceTaps = attr;
  }

  ::mlir::Attribute removeInitialFnAttr() {
      auto attr = getProperties().initialFn;
      getProperties().initialFn = {};
      return attr;
  }

  ::mlir::Attribute removeFinalFnAttr() {
      auto attr = getProperties().finalFn;
      getProperties().finalFn = {};
      return attr;
  }

  ::mlir::Attribute removeTraceTapsAttr() {
      auto attr = getProperties().traceTaps;
      getProperties().traceTaps = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::hw::ModuleType io, /*optional*/::mlir::FlatSymbolRefAttr initialFn, /*optional*/::mlir::FlatSymbolRefAttr finalFn, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  mlir::Block &getBodyBlock() { return getBody().front(); }
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ModelOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::ModelOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::OutputOp declarations
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
      odsOpName.emplace("arc.output", odsAttrs.getContext());
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
class OutputOp : public ::mlir::Op<OutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<DefineOp, LutOp, ExecuteOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike> {
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
    return ::llvm::StringLiteral("arc.output");
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::OutputOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::RootInputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RootInputOpGenericAdaptorBase {
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
  RootInputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.root_input", odsAttrs.getContext());
  }

  RootInputOpGenericAdaptorBase(RootInputOp op);

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
class RootInputOpGenericAdaptor : public detail::RootInputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RootInputOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  RootInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RootInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RootInputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RootInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RootInputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RootInputOpGenericAdaptor(RangeT values, const RootInputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RootInputOp, typename = std::enable_if_t<std::is_same_v<LateInst, RootInputOp>>>
  RootInputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RootInputOpAdaptor : public RootInputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RootInputOpGenericAdaptor::RootInputOpGenericAdaptor;
  RootInputOpAdaptor(RootInputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RootInputOp : public ::mlir::Op<RootInputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::StateType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RootInputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RootInputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<RootInputOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RootInputOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RootInputOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("arc.root_input");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<circt::arc::StateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StateType>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RootInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RootInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::RootInputOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::RootInputOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::RootOutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RootOutputOpGenericAdaptorBase {
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
  RootOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.root_output", odsAttrs.getContext());
  }

  RootOutputOpGenericAdaptorBase(RootOutputOp op);

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
class RootOutputOpGenericAdaptor : public detail::RootOutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RootOutputOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  RootOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RootOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RootOutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RootOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RootOutputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RootOutputOpGenericAdaptor(RangeT values, const RootOutputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RootOutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, RootOutputOp>>>
  RootOutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RootOutputOpAdaptor : public RootOutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RootOutputOpGenericAdaptor::RootOutputOpGenericAdaptor;
  RootOutputOpAdaptor(RootOutputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RootOutputOp : public ::mlir::Op<RootOutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::arc::StateType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RootOutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RootOutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<RootOutputOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RootOutputOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RootOutputOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("arc.root_output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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

  ::mlir::TypedValue<circt::arc::StateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StateType>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::mlir::StringAttr name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type state, ::llvm::StringRef name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value storage);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RootOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RootOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::RootOutputOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::RootOutputOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::RuntimeModelOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RuntimeModelOpGenericAdaptorBase {
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
    using numStateBytesTy = ::mlir::IntegerAttr;
    numStateBytesTy numStateBytes;

    auto getNumStateBytes() const {
      auto &propStorage = this->numStateBytes;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setNumStateBytes(const ::mlir::IntegerAttr &propValue) {
      this->numStateBytes = propValue;
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
    using traceTapsTy = ::mlir::ArrayAttr;
    traceTapsTy traceTaps;

    auto getTraceTaps() const {
      auto &propStorage = this->traceTaps;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setTraceTaps(const ::mlir::ArrayAttr &propValue) {
      this->traceTaps = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        rhs.numStateBytes == this->numStateBytes &&
        rhs.sym_name == this->sym_name &&
        rhs.traceTaps == this->traceTaps &&
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
  RuntimeModelOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.runtime.model", odsAttrs.getContext());
  }

  RuntimeModelOpGenericAdaptorBase(RuntimeModelOp op);

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
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::IntegerAttr getNumStateBytesAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().numStateBytes);
    return attr;
  }

  uint64_t getNumStateBytes();
  ::mlir::ArrayAttr getTraceTapsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().traceTaps);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getTraceTaps();
};

} // namespace detail
template <typename RangeT>
class RuntimeModelOpGenericAdaptor : public detail::RuntimeModelOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RuntimeModelOpGenericAdaptorBase;
public:
  RuntimeModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RuntimeModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RuntimeModelOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RuntimeModelOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RuntimeModelOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RuntimeModelOpGenericAdaptor(RangeT values, const RuntimeModelOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RuntimeModelOp, typename = std::enable_if_t<std::is_same_v<LateInst, RuntimeModelOp>>>
  RuntimeModelOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RuntimeModelOpAdaptor : public RuntimeModelOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RuntimeModelOpGenericAdaptor::RuntimeModelOpGenericAdaptor;
  RuntimeModelOpAdaptor(RuntimeModelOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RuntimeModelOp : public ::mlir::Op<RuntimeModelOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RuntimeModelOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RuntimeModelOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("numStateBytes"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("traceTaps")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNumStateBytesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNumStateBytesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getTraceTapsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getTraceTapsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.runtime.model");
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::IntegerAttr getNumStateBytesAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().numStateBytes);
  }

  uint64_t getNumStateBytes();
  ::mlir::ArrayAttr getTraceTapsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().traceTaps);
  }

  ::std::optional< ::mlir::ArrayAttr > getTraceTaps();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setNumStateBytesAttr(::mlir::IntegerAttr attr) {
    getProperties().numStateBytes = attr;
  }

  void setNumStateBytes(uint64_t attrValue);
  void setTraceTapsAttr(::mlir::ArrayAttr attr) {
    getProperties().traceTaps = attr;
  }

  ::mlir::Attribute removeTraceTapsAttr() {
      auto attr = getProperties().traceTaps;
      getProperties().traceTaps = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr name, ::mlir::IntegerAttr numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef name, uint64_t numStateBytes, /*optional*/::mlir::ArrayAttr traceTaps);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RuntimeModelOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RuntimeModelOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::RuntimeModelOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::RuntimeModelOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SetNextWakeupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SetNextWakeupOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SetNextWakeupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.set_next_wakeup", odsAttrs.getContext());
  }

  SetNextWakeupOpGenericAdaptorBase(SetNextWakeupOp op);

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
class SetNextWakeupOpGenericAdaptor : public detail::SetNextWakeupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SetNextWakeupOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
  static constexpr int odsIndex_time = 1;
public:
  SetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SetNextWakeupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SetNextWakeupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SetNextWakeupOpGenericAdaptor(RangeT values, const SetNextWakeupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SetNextWakeupOp, typename = std::enable_if_t<std::is_same_v<LateInst, SetNextWakeupOp>>>
  SetNextWakeupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTime() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SetNextWakeupOpAdaptor : public SetNextWakeupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SetNextWakeupOpGenericAdaptor::SetNextWakeupOpGenericAdaptor;
  SetNextWakeupOpAdaptor(SetNextWakeupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SetNextWakeupOp : public ::mlir::Op<SetNextWakeupOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SetNextWakeupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SetNextWakeupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  static constexpr int odsIndex_time = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.set_next_wakeup");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTimeMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value storage, ::mlir::Value time);
  static SetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value storage, ::mlir::Value time);
  static SetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value storage, ::mlir::Value time);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::Value time);
  static SetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::Value time);
  static SetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::Value time);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SetNextWakeupOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimEmitValueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimEmitValueOpGenericAdaptorBase {
public:
  struct Properties {
    using valueNameTy = ::mlir::StringAttr;
    valueNameTy valueName;

    auto getValueName() const {
      auto &propStorage = this->valueName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setValueName(const ::mlir::StringAttr &propValue) {
      this->valueName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.valueName == this->valueName &&
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
  SimEmitValueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.emit", odsAttrs.getContext());
  }

  SimEmitValueOpGenericAdaptorBase(SimEmitValueOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getValueNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().valueName);
    return attr;
  }

  ::llvm::StringRef getValueName();
};

} // namespace detail
template <typename RangeT>
class SimEmitValueOpGenericAdaptor : public detail::SimEmitValueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimEmitValueOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  SimEmitValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimEmitValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimEmitValueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimEmitValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimEmitValueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimEmitValueOpGenericAdaptor(RangeT values, const SimEmitValueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimEmitValueOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimEmitValueOp>>>
  SimEmitValueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimEmitValueOpAdaptor : public SimEmitValueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimEmitValueOpGenericAdaptor::SimEmitValueOpGenericAdaptor;
  SimEmitValueOpAdaptor(SimEmitValueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimEmitValueOp : public ::mlir::Op<SimEmitValueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimEmitValueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimEmitValueOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("valueName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getValueNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getValueNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.emit");
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getValueNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().valueName);
  }

  ::llvm::StringRef getValueName();
  void setValueNameAttr(::mlir::StringAttr attr) {
    getProperties().valueName = attr;
  }

  void setValueName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr valueName, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr valueName, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef valueName, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef valueName, ::mlir::Value value);
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef valueName, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimEmitValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimEmitValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimEmitValueOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::SimEmitValueOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimGetNextWakeupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimGetNextWakeupOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SimGetNextWakeupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.get_next_wakeup", odsAttrs.getContext());
  }

  SimGetNextWakeupOpGenericAdaptorBase(SimGetNextWakeupOp op);

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
class SimGetNextWakeupOpGenericAdaptor : public detail::SimGetNextWakeupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimGetNextWakeupOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
public:
  SimGetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimGetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimGetNextWakeupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimGetNextWakeupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimGetNextWakeupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimGetNextWakeupOpGenericAdaptor(RangeT values, const SimGetNextWakeupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimGetNextWakeupOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimGetNextWakeupOp>>>
  SimGetNextWakeupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimGetNextWakeupOpAdaptor : public SimGetNextWakeupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimGetNextWakeupOpGenericAdaptor::SimGetNextWakeupOpGenericAdaptor;
  SimGetNextWakeupOpAdaptor(SimGetNextWakeupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimGetNextWakeupOp : public ::mlir::Op<SimGetNextWakeupOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimGetNextWakeupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimGetNextWakeupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.get_next_wakeup");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type time, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type time, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type time, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetNextWakeupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetNextWakeupOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimGetNextWakeupOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimGetPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimGetPortOpGenericAdaptorBase {
public:
  struct Properties {
    using portTy = ::mlir::StringAttr;
    portTy port;

    auto getPort() const {
      auto &propStorage = this->port;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setPort(const ::mlir::StringAttr &propValue) {
      this->port = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.port == this->port &&
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
  SimGetPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.get_port", odsAttrs.getContext());
  }

  SimGetPortOpGenericAdaptorBase(SimGetPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getPortAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().port);
    return attr;
  }

  ::llvm::StringRef getPort();
};

} // namespace detail
template <typename RangeT>
class SimGetPortOpGenericAdaptor : public detail::SimGetPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimGetPortOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
public:
  SimGetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimGetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimGetPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimGetPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimGetPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimGetPortOpGenericAdaptor(RangeT values, const SimGetPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimGetPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimGetPortOp>>>
  SimGetPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimGetPortOpAdaptor : public SimGetPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimGetPortOpGenericAdaptor::SimGetPortOpGenericAdaptor;
  SimGetPortOpAdaptor(SimGetPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimGetPortOp : public ::mlir::Op<SimGetPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimGetPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimGetPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("port")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPortAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPortAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.get_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::Type> getValue() {
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
  ::mlir::StringAttr getPortAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().port);
  }

  ::llvm::StringRef getPort();
  void setPortAttr(::mlir::StringAttr attr) {
    getProperties().port = attr;
  }

  void setPort(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value instance, ::mlir::StringAttr port);
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value instance, ::mlir::StringAttr port);
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value instance, ::mlir::StringAttr port);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr port);
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr port);
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr port);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value instance, ::llvm::StringRef port);
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value instance, ::llvm::StringRef port);
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value instance, ::llvm::StringRef port);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef port);
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef port);
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef port);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimGetPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::SimGetPortOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimGetTimeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimGetTimeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SimGetTimeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.get_time", odsAttrs.getContext());
  }

  SimGetTimeOpGenericAdaptorBase(SimGetTimeOp op);

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
class SimGetTimeOpGenericAdaptor : public detail::SimGetTimeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimGetTimeOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
public:
  SimGetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimGetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimGetTimeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimGetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimGetTimeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimGetTimeOpGenericAdaptor(RangeT values, const SimGetTimeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimGetTimeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimGetTimeOp>>>
  SimGetTimeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimGetTimeOpAdaptor : public SimGetTimeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimGetTimeOpGenericAdaptor::SimGetTimeOpGenericAdaptor;
  SimGetTimeOpAdaptor(SimGetTimeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimGetTimeOp : public ::mlir::Op<SimGetTimeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimGetTimeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimGetTimeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.get_time");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type time, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type time, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type time, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimGetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimGetTimeOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimInstantiateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimInstantiateOpGenericAdaptorBase {
public:
  struct Properties {
    using runtimeArgsTy = ::mlir::StringAttr;
    runtimeArgsTy runtimeArgs;

    auto getRuntimeArgs() const {
      auto &propStorage = this->runtimeArgs;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setRuntimeArgs(const ::mlir::StringAttr &propValue) {
      this->runtimeArgs = propValue;
    }
    using runtimeModelTy = ::mlir::FlatSymbolRefAttr;
    runtimeModelTy runtimeModel;

    auto getRuntimeModel() const {
      auto &propStorage = this->runtimeModel;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setRuntimeModel(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->runtimeModel = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.runtimeArgs == this->runtimeArgs &&
        rhs.runtimeModel == this->runtimeModel &&
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
  SimInstantiateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.instantiate", odsAttrs.getContext());
  }

  SimInstantiateOpGenericAdaptorBase(SimInstantiateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getRuntimeModelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().runtimeModel);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRuntimeModel();
  ::mlir::StringAttr getRuntimeArgsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().runtimeArgs);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRuntimeArgs();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SimInstantiateOpGenericAdaptor : public detail::SimInstantiateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimInstantiateOpGenericAdaptorBase;
public:
  SimInstantiateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimInstantiateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimInstantiateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimInstantiateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimInstantiateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimInstantiateOpGenericAdaptor(RangeT values, const SimInstantiateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimInstantiateOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimInstantiateOp>>>
  SimInstantiateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimInstantiateOpAdaptor : public SimInstantiateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimInstantiateOpGenericAdaptor::SimInstantiateOpGenericAdaptor;
  SimInstantiateOpAdaptor(SimInstantiateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimInstantiateOp : public ::mlir::Op<SimInstantiateOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimInstantiateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimInstantiateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("runtimeArgs"), ::llvm::StringRef("runtimeModel")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRuntimeArgsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRuntimeArgsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRuntimeModelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRuntimeModelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.instantiate");
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
  ::mlir::FlatSymbolRefAttr getRuntimeModelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().runtimeModel);
  }

  ::std::optional< ::llvm::StringRef > getRuntimeModel();
  ::mlir::StringAttr getRuntimeArgsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().runtimeArgs);
  }

  ::std::optional< ::llvm::StringRef > getRuntimeArgs();
  void setRuntimeModelAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().runtimeModel = attr;
  }

  void setRuntimeModel(::std::optional<::llvm::StringRef> attrValue);
  void setRuntimeArgsAttr(::mlir::StringAttr attr) {
    getProperties().runtimeArgs = attr;
  }

  void setRuntimeArgs(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeRuntimeModelAttr() {
      auto attr = getProperties().runtimeModel;
      getProperties().runtimeModel = {};
      return attr;
  }

  ::mlir::Attribute removeRuntimeArgsAttr() {
      auto attr = getProperties().runtimeArgs;
      getProperties().runtimeArgs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static SimInstantiateOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static SimInstantiateOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static SimInstantiateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static SimInstantiateOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static SimInstantiateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static SimInstantiateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::FlatSymbolRefAttr runtimeModel, /*optional*/::mlir::StringAttr runtimeArgs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimInstantiateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimInstantiateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimInstantiateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimInstantiateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimInstantiateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::SimInstantiateOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimSetInputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimSetInputOpGenericAdaptorBase {
public:
  struct Properties {
    using inputTy = ::mlir::StringAttr;
    inputTy input;

    auto getInput() const {
      auto &propStorage = this->input;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInput(const ::mlir::StringAttr &propValue) {
      this->input = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.input == this->input &&
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
  SimSetInputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.set_input", odsAttrs.getContext());
  }

  SimSetInputOpGenericAdaptorBase(SimSetInputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getInputAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().input);
    return attr;
  }

  ::llvm::StringRef getInput();
};

} // namespace detail
template <typename RangeT>
class SimSetInputOpGenericAdaptor : public detail::SimSetInputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimSetInputOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_value = 1;
public:
  SimSetInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimSetInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimSetInputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimSetInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimSetInputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimSetInputOpGenericAdaptor(RangeT values, const SimSetInputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimSetInputOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimSetInputOp>>>
  SimSetInputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SimSetInputOpAdaptor : public SimSetInputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimSetInputOpGenericAdaptor::SimSetInputOpGenericAdaptor;
  SimSetInputOpAdaptor(SimSetInputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimSetInputOp : public ::mlir::Op<SimSetInputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimSetInputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimSetInputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("input")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInputAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInputAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.set_input");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getInputAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().input);
  }

  ::llvm::StringRef getInput();
  void setInputAttr(::mlir::StringAttr attr) {
    getProperties().input = attr;
  }

  void setInput(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::StringAttr input, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef input, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimSetInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimSetInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimSetInputOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::SimSetInputOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimSetTimeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimSetTimeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SimSetTimeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.set_time", odsAttrs.getContext());
  }

  SimSetTimeOpGenericAdaptorBase(SimSetTimeOp op);

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
class SimSetTimeOpGenericAdaptor : public detail::SimSetTimeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimSetTimeOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_time = 1;
public:
  SimSetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimSetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimSetTimeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimSetTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimSetTimeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimSetTimeOpGenericAdaptor(RangeT values, const SimSetTimeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimSetTimeOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimSetTimeOp>>>
  SimSetTimeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getTime() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SimSetTimeOpAdaptor : public SimSetTimeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimSetTimeOpGenericAdaptor::SimSetTimeOpGenericAdaptor;
  SimSetTimeOpAdaptor(SimSetTimeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimSetTimeOp : public ::mlir::Op<SimSetTimeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimSetTimeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimSetTimeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_time = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.set_time");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTime() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTimeMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::mlir::Value time);
  static SimSetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::mlir::Value time);
  static SimSetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::mlir::Value time);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::Value time);
  static SimSetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::Value time);
  static SimSetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::Value time);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimSetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimSetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimSetTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimSetTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimSetTimeOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::SimStepOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimStepOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SimStepOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.sim.step", odsAttrs.getContext());
  }

  SimStepOpGenericAdaptorBase(SimStepOp op);

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
class SimStepOpGenericAdaptor : public detail::SimStepOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimStepOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_timePostIncrement = 1;
public:
  SimStepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimStepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimStepOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimStepOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimStepOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimStepOpGenericAdaptor(RangeT values, const SimStepOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimStepOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimStepOp>>>
  SimStepOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getTimePostIncrement() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SimStepOpAdaptor : public SimStepOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimStepOpGenericAdaptor::SimStepOpGenericAdaptor;
  SimStepOpAdaptor(SimStepOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimStepOp : public ::mlir::Op<SimStepOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimStepOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimStepOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_timePostIncrement = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.sim.step");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::SimModelInstanceType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::SimModelInstanceType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTimePostIncrement() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getTimePostIncrementMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value instance);
  static SimStepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value instance);
  static SimStepOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value instance);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static SimStepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static SimStepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static SimStepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static SimStepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, /*optional*/::mlir::Value timePostIncrement);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimStepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimStepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimStepOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimStepOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimStepOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::StateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StateOpGenericAdaptorBase {
public:
  struct Properties {
    using arcTy = ::mlir::FlatSymbolRefAttr;
    arcTy arc;

    auto getArc() const {
      auto &propStorage = this->arc;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setArc(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->arc = propValue;
    }
    using latencyTy = ::mlir::IntegerAttr;
    latencyTy latency;

    auto getLatency() const {
      auto &propStorage = this->latency;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLatency(const ::mlir::IntegerAttr &propValue) {
      this->latency = propValue;
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
        rhs.arc == this->arc &&
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
  StateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.state", odsAttrs.getContext());
  }

  StateOpGenericAdaptorBase(StateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getArcAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
    return attr;
  }

  ::llvm::StringRef getArc();
  ::mlir::IntegerAttr getLatencyAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
    return attr;
  }

  uint32_t getLatency();
};

} // namespace detail
template <typename RangeT>
class StateOpGenericAdaptor : public detail::StateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StateOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_inputs = 3;
  static constexpr int odsIndex_initials = 4;
public:
  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : StateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

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

  ValueT getClock() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getInputs() {
    return getODSOperands(3);
  }

  RangeT getInitials() {
    return getODSOperands(4);
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
class StateOp : public ::mlir::Op<StateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::MemRefsNormalizable, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::circt::arc::ClockedOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_inputs = 3;
  static constexpr int odsIndex_initials = 4;
  using Properties = FoldAdaptor::Properties;
  using ::circt::arc::ClockedOpInterface::Trait<StateOp>::isClocked;
  using ::circt::arc::ClockedOpInterface::Trait<StateOp>::eraseClock;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arc"), ::llvm::StringRef("latency"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArcAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArcAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLatencyAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.state");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::circt::seq::ClockType>{} : ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(3);
  }

  ::mlir::Operation::operand_range getInitials() {
    return getODSOperands(4);
  }

  ::mlir::MutableOperandRange getClockMutable();
  ::mlir::MutableOperandRange getEnableMutable();
  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::MutableOperandRange getInitialsMutable();
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
  ::mlir::FlatSymbolRefAttr getArcAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().arc);
  }

  ::llvm::StringRef getArc();
  ::mlir::IntegerAttr getLatencyAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
  }

  uint32_t getLatency();
  void setArcAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().arc = attr;
  }

  void setArc(::llvm::StringRef attrValue);
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, DefineOp arc, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, DefineOp arc, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, DefineOp arc, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, mlir::Value reset, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, mlir::Value reset, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::SymbolRefAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, mlir::Value reset, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringAttr arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::StringRef arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::StringRef arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  static StateOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::StringRef arc, mlir::TypeRange results, mlir::Value clock, mlir::Value enable, unsigned latency, mlir::ValueRange inputs = {}, mlir::ValueRange initials = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(StateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
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
  operand_range getArgOperands() {
    return getInputs();
  }
  MutableOperandRange getArgOperandsMutable() {
    return getInputsMutable();
  }

  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("arc");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getArcAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::StateOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::StateReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StateReadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StateReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.state_read", odsAttrs.getContext());
  }

  StateReadOpGenericAdaptorBase(StateReadOp op);

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
class StateReadOpGenericAdaptor : public detail::StateReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StateReadOpGenericAdaptorBase;
  static constexpr int odsIndex_state = 0;
public:
  StateReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StateReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StateReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StateReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StateReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StateReadOpGenericAdaptor(RangeT values, const StateReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StateReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, StateReadOp>>>
  StateReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getState() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StateReadOpAdaptor : public StateReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StateReadOpGenericAdaptor::StateReadOpGenericAdaptor;
  StateReadOpAdaptor(StateReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StateReadOp : public ::mlir::Op<StateReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StateReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StateReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_state = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.state_read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StateType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStateMutable() {
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

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::Value state);
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::Value state);
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::Value state);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value state);
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value state);
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value state);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value state);
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value state);
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value state);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StateReadOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::StateWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StateWriteOpGenericAdaptorBase {
public:
  struct Properties {
    using traceTapIndexTy = ::mlir::IntegerAttr;
    traceTapIndexTy traceTapIndex;

    auto getTraceTapIndex() const {
      auto &propStorage = this->traceTapIndex;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setTraceTapIndex(const ::mlir::IntegerAttr &propValue) {
      this->traceTapIndex = propValue;
    }
    using traceTapModelTy = ::mlir::FlatSymbolRefAttr;
    traceTapModelTy traceTapModel;

    auto getTraceTapModel() const {
      auto &propStorage = this->traceTapModel;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setTraceTapModel(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->traceTapModel = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.traceTapIndex == this->traceTapIndex &&
        rhs.traceTapModel == this->traceTapModel &&
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
  StateWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.state_write", odsAttrs.getContext());
  }

  StateWriteOpGenericAdaptorBase(StateWriteOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getTraceTapModelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().traceTapModel);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getTraceTapModel();
  ::mlir::IntegerAttr getTraceTapIndexAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().traceTapIndex);
    return attr;
  }

  ::std::optional<uint64_t> getTraceTapIndex();
};

} // namespace detail
template <typename RangeT>
class StateWriteOpGenericAdaptor : public detail::StateWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StateWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_state = 0;
  static constexpr int odsIndex_value = 1;
public:
  StateWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StateWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StateWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StateWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StateWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StateWriteOpGenericAdaptor(RangeT values, const StateWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StateWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, StateWriteOp>>>
  StateWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getState() {
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
class StateWriteOpAdaptor : public StateWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StateWriteOpGenericAdaptor::StateWriteOpGenericAdaptor;
  StateWriteOpAdaptor(StateWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StateWriteOp : public ::mlir::Op<StateWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StateWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StateWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_state = 0;
  static constexpr int odsIndex_value = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("traceTapIndex"), ::llvm::StringRef("traceTapModel")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTraceTapIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTraceTapIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTraceTapModelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTraceTapModelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.state_write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StateType> getState() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StateType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getStateMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getTraceTapModelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().traceTapModel);
  }

  ::std::optional< ::llvm::StringRef > getTraceTapModel();
  ::mlir::IntegerAttr getTraceTapIndexAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().traceTapIndex);
  }

  ::std::optional<uint64_t> getTraceTapIndex();
  void setTraceTapModelAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().traceTapModel = attr;
  }

  void setTraceTapModel(::std::optional<::llvm::StringRef> attrValue);
  void setTraceTapIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().traceTapIndex = attr;
  }

  void setTraceTapIndex(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeTraceTapModelAttr() {
      auto attr = getProperties().traceTapModel;
      getProperties().traceTapModel = {};
      return attr;
  }

  ::mlir::Attribute removeTraceTapIndexAttr() {
      auto attr = getProperties().traceTapIndex;
      getProperties().traceTapIndex = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value state, mlir::Value value);
  static StateWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value state, mlir::Value value);
  static StateWriteOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value state, mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static StateWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static StateWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static StateWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static StateWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value state, ::mlir::Value value, /*optional*/::mlir::FlatSymbolRefAttr traceTapModel, /*optional*/::mlir::IntegerAttr traceTapIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StateWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StateWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StateWriteOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::StateWriteOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::StorageGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StorageGetOpGenericAdaptorBase {
public:
  struct Properties {
    using offsetTy = ::mlir::IntegerAttr;
    offsetTy offset;

    auto getOffset() const {
      auto &propStorage = this->offset;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setOffset(const ::mlir::IntegerAttr &propValue) {
      this->offset = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.offset == this->offset &&
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
  StorageGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.storage.get", odsAttrs.getContext());
  }

  StorageGetOpGenericAdaptorBase(StorageGetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getOffsetAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
    return attr;
  }

  uint32_t getOffset();
};

} // namespace detail
template <typename RangeT>
class StorageGetOpGenericAdaptor : public detail::StorageGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StorageGetOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  StorageGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StorageGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StorageGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StorageGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StorageGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StorageGetOpGenericAdaptor(RangeT values, const StorageGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StorageGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, StorageGetOp>>>
  StorageGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StorageGetOpAdaptor : public StorageGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StorageGetOpGenericAdaptor::StorageGetOpGenericAdaptor;
  StorageGetOpAdaptor(StorageGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StorageGetOp : public ::mlir::Op<StorageGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StorageGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StorageGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("offset")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOffsetAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getOffsetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.storage.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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
  ::mlir::IntegerAttr getOffsetAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().offset);
  }

  uint32_t getOffset();
  void setOffsetAttr(::mlir::IntegerAttr attr) {
    getProperties().offset = attr;
  }

  void setOffset(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::IntegerAttr offset);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value storage, uint32_t offset);
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value storage, uint32_t offset);
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value storage, uint32_t offset);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, uint32_t offset);
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, uint32_t offset);
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, uint32_t offset);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StorageGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(StorageGetOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StorageGetOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::StorageGetOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::TapOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TapOpGenericAdaptorBase {
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
  TapOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.tap", odsAttrs.getContext());
  }

  TapOpGenericAdaptorBase(TapOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class TapOpGenericAdaptor : public detail::TapOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TapOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  TapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TapOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TapOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TapOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TapOpGenericAdaptor(RangeT values, const TapOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TapOp, typename = std::enable_if_t<std::is_same_v<LateInst, TapOp>>>
  TapOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TapOpAdaptor : public TapOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TapOpGenericAdaptor::TapOpGenericAdaptor;
  TapOpAdaptor(TapOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TapOp : public ::mlir::Op<TapOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TapOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TapOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
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
    return ::llvm::StringLiteral("arc.tap");
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value val, mlir::StringRef name);
  static TapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value val, mlir::StringRef name);
  static TapOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value val, mlir::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::ArrayAttr names);
  static TapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::ArrayAttr names);
  static TapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr names);
  static TapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr names);
  static TapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TapOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TapOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::TapOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::TapOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::TerminateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TerminateOpGenericAdaptorBase {
public:
  struct Properties {
    using successTy = ::mlir::BoolAttr;
    successTy success;

    auto getSuccess() const {
      auto &propStorage = this->success;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setSuccess(const ::mlir::BoolAttr &propValue) {
      this->success = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.success == this->success &&
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
  TerminateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.terminate", odsAttrs.getContext());
  }

  TerminateOpGenericAdaptorBase(TerminateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getSuccessAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().success);
    return attr;
  }

  bool getSuccess();
};

} // namespace detail
template <typename RangeT>
class TerminateOpGenericAdaptor : public detail::TerminateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TerminateOpGenericAdaptorBase;
  static constexpr int odsIndex_storage = 0;
public:
  TerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TerminateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TerminateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TerminateOpGenericAdaptor(RangeT values, const TerminateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TerminateOp, typename = std::enable_if_t<std::is_same_v<LateInst, TerminateOp>>>
  TerminateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStorage() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TerminateOpAdaptor : public TerminateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TerminateOpGenericAdaptor::TerminateOpGenericAdaptor;
  TerminateOpAdaptor(TerminateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TerminateOp : public ::mlir::Op<TerminateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TerminateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TerminateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_storage = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("success")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSuccessAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSuccessAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.terminate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::arc::StorageType> getStorage() {
    return ::llvm::cast<::mlir::TypedValue<circt::arc::StorageType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStorageMutable() {
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::BoolAttr getSuccessAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().success);
  }

  bool getSuccess();
  void setSuccessAttr(::mlir::BoolAttr attr) {
    getProperties().success = attr;
  }

  void setSuccess(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value storage, ::mlir::BoolAttr success);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value storage, ::mlir::BoolAttr success);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value storage, ::mlir::BoolAttr success);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::BoolAttr success);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::BoolAttr success);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, ::mlir::BoolAttr success);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value storage, bool success);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value storage, bool success);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value storage, bool success);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value storage, bool success);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value storage, bool success);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value storage, bool success);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::TerminateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::TerminateOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::VectorizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VectorizeOpGenericAdaptorBase {
public:
  struct Properties {
    using inputOperandSegmentsTy = ::mlir::DenseI32ArrayAttr;
    inputOperandSegmentsTy inputOperandSegments;

    auto getInputOperandSegments() const {
      auto &propStorage = this->inputOperandSegments;
      return ::llvm::cast<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setInputOperandSegments(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->inputOperandSegments = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inputOperandSegments == this->inputOperandSegments &&
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
  VectorizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.vectorize", odsAttrs.getContext());
  }

  VectorizeOpGenericAdaptorBase(VectorizeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI32ArrayAttr getInputOperandSegmentsAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI32ArrayAttr>(getProperties().inputOperandSegments);
    return attr;
  }

  ::llvm::ArrayRef<int32_t> getInputOperandSegments();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class VectorizeOpGenericAdaptor : public detail::VectorizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VectorizeOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  VectorizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VectorizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : VectorizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VectorizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VectorizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VectorizeOpGenericAdaptor(RangeT values, const VectorizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VectorizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, VectorizeOp>>>
  VectorizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ::llvm::SmallVector<RangeT> getInputs() {
    auto tblgenTmpOperands = getODSOperands(0);
    auto sizes = getInputOperandSegments();

    ::llvm::SmallVector<RangeT> tblgenTmpOperandGroups;
    for (int i = 0, e = sizes.size(); i < e; ++i) {
      tblgenTmpOperandGroups.push_back(tblgenTmpOperands.take_front(sizes[i]));
      tblgenTmpOperands = tblgenTmpOperands.drop_front(sizes[i]);
    }
    return tblgenTmpOperandGroups;
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class VectorizeOpAdaptor : public VectorizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VectorizeOpGenericAdaptor::VectorizeOpGenericAdaptor;
  VectorizeOpAdaptor(VectorizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VectorizeOp : public ::mlir::Op<VectorizeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpTrait::HasRecursiveMemoryEffects> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VectorizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VectorizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inputOperandSegments")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInputOperandSegmentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInputOperandSegmentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.vectorize");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::OperandRangeRange getInputs() {
    return getODSOperands(0).split(getInputOperandSegmentsAttr());
  }

  ::mlir::MutableOperandRangeRange getInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
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
  ::mlir::DenseI32ArrayAttr getInputOperandSegmentsAttr() {
    return ::llvm::cast<::mlir::DenseI32ArrayAttr>(getProperties().inputOperandSegments);
  }

  ::llvm::ArrayRef<int32_t> getInputOperandSegments();
  void setInputOperandSegmentsAttr(::mlir::DenseI32ArrayAttr attr) {
    getProperties().inputOperandSegments = attr;
  }

  void setInputOperandSegments(::llvm::ArrayRef<int32_t> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::ArrayRef<::mlir::ValueRange> inputs);
  static VectorizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::ArrayRef<::mlir::ValueRange> inputs);
  static VectorizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::ArrayRef<::mlir::ValueRange> inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
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
  /// Returns whether the `arc.vectorize` boundary is already vectorized.
  /// The boundary is vectorized if each input vector has only one element
  /// (either of integer or vector type), i.e., the vector itself.
  bool isBoundaryVectorized();

  /// Returns whether the body block of the `arc.vectorize` is already
  /// vectorized. The body is vectorized if the boundary is vectorized and
  /// the body's argument and result types match those of the boundary, or
  /// they are a vectorized version of the boundary types (i.e., a matching
  /// vector type or integer with summed-up bitwidth).
  bool isBodyVectorized();
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::VectorizeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::VectorizeOpGenericAdaptorBase::Properties)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::VectorizeReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VectorizeReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  VectorizeReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.vectorize.return", odsAttrs.getContext());
  }

  VectorizeReturnOpGenericAdaptorBase(VectorizeReturnOp op);

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
class VectorizeReturnOpGenericAdaptor : public detail::VectorizeReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VectorizeReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  VectorizeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VectorizeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : VectorizeReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VectorizeReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VectorizeReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VectorizeReturnOpGenericAdaptor(RangeT values, const VectorizeReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VectorizeReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, VectorizeReturnOp>>>
  VectorizeReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class VectorizeReturnOpAdaptor : public VectorizeReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VectorizeReturnOpGenericAdaptor::VectorizeReturnOpGenericAdaptor;
  VectorizeReturnOpAdaptor(VectorizeReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VectorizeReturnOp : public ::mlir::Op<VectorizeReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<VectorizeOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VectorizeReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VectorizeReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<VectorizeReturnOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<VectorizeReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.vectorize.return");
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value);
  static VectorizeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value);
  static VectorizeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static VectorizeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static VectorizeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorizeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VectorizeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorizeReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VectorizeReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::VectorizeReturnOp)

namespace circt::arc {


//===----------------------------------------------------------------------===//
// circt::arc::ZeroCountOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ZeroCountOpGenericAdaptorBase {
public:
  struct Properties {
    using predicateTy = circt::arc::ZeroCountPredicateAttr;
    predicateTy predicate;

    auto getPredicate() const {
      auto &propStorage = this->predicate;
      return ::llvm::cast<circt::arc::ZeroCountPredicateAttr>(propStorage);
    }
    void setPredicate(const circt::arc::ZeroCountPredicateAttr &propValue) {
      this->predicate = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.predicate == this->predicate &&
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
  ZeroCountOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("arc.zero_count", odsAttrs.getContext());
  }

  ZeroCountOpGenericAdaptorBase(ZeroCountOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::arc::ZeroCountPredicateAttr getPredicateAttr() {
    auto attr = ::llvm::cast<circt::arc::ZeroCountPredicateAttr>(getProperties().predicate);
    return attr;
  }

  circt::arc::ZeroCountPredicate getPredicate();
};

} // namespace detail
template <typename RangeT>
class ZeroCountOpGenericAdaptor : public detail::ZeroCountOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ZeroCountOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ZeroCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ZeroCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ZeroCountOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ZeroCountOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ZeroCountOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ZeroCountOpGenericAdaptor(RangeT values, const ZeroCountOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ZeroCountOp, typename = std::enable_if_t<std::is_same_v<LateInst, ZeroCountOp>>>
  ZeroCountOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ZeroCountOpAdaptor : public ZeroCountOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ZeroCountOpGenericAdaptor::ZeroCountOpGenericAdaptor;
  ZeroCountOpAdaptor(ZeroCountOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ZeroCountOp : public ::mlir::Op<ZeroCountOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ZeroCountOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ZeroCountOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("predicate")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPredicateAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPredicateAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("arc.zero_count");
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  circt::arc::ZeroCountPredicateAttr getPredicateAttr() {
    return ::llvm::cast<circt::arc::ZeroCountPredicateAttr>(getProperties().predicate);
  }

  circt::arc::ZeroCountPredicate getPredicate();
  void setPredicateAttr(circt::arc::ZeroCountPredicateAttr attr) {
    getProperties().predicate = attr;
  }

  void setPredicate(circt::arc::ZeroCountPredicate attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicateAttr predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, circt::arc::ZeroCountPredicate predicate);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ZeroCountOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ZeroCountOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ZeroCountOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::detail::ZeroCountOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

