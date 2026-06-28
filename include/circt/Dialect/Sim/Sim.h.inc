/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Sim.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sim {

/// Pause the simulation
/// Implements the semantics of `sim.pause` if the given condition is true on
/// the rising edge of the clock operand.
class ClockedPauseOp;

} // namespace circt::sim
namespace circt::sim {

/// Terminate the simulation
/// Implements the semantics of `sim.terminate` if the given condition is true
/// on the rising edge of the clock operand.
class ClockedTerminateOp;

} // namespace circt::sim
namespace circt::sim {

/// A call option for DPI function with an optional clock and enable
/// `sim.func.dpi.call` represents SystemVerilog DPI function call. There are two
/// optional operands `clock` and `enable`.
/// 
/// If `clock` is not provided, the callee is invoked when input values are changed.
/// If provided, the DPI function is called at clock's posedge. The result values behave
/// like registers and the DPI function is used as a state transfer function of them.
/// 
/// `enable` operand is used to conditionally call the DPI since DPI call could be quite
/// more expensive than native constructs. When `enable` is low, results of unclocked
/// calls are undefined and in SV results they are lowered into `X`. Users are expected
/// to gate result values by another `enable` to model a default value of results.
/// 
/// For clocked calls, a low enable means that its register state transfer function is
/// not called. Hence their values will not be modify in that clock.
class DPICallOp;

} // namespace circt::sim
namespace circt::sim {

/// A DPI-C imported function declaration
/// `sim.func.dpi` models a DPI-C imported function with first-class argument
/// direction keywords: `in`, `out`, `inout`, `return`, and `ref`.
/// 
/// Argument directions map to call and ABI semantics as follows:
/// - `in`     — call operand, passed by value.
/// - `out`    — call result, passed by pointer in the C ABI.
/// - `inout`  — call operand and result, passed by pointer in the C ABI.
/// - `return` — call result (last), the actual C return value.
/// - `ref`    — call operand (pass-through pointer, e.g. open-array ABI).
class DPIFuncOp;

} // namespace circt::sim
namespace circt::sim {

/// Flush a output stream
/// Flushes the output buffer of an output stream.
/// This ensures that any buffered data is written to the file immediately.
class FlushOp;

} // namespace circt::sim
namespace circt::sim {

/// Binary format specifier
/// Format the given integer value as binary (base two) string.
/// 
/// The printed value will be left-padded with '0' up to the number
/// of bits of the argument's type. Zero width values will produce
/// the empty string. No further prefix will be added.
class FormatBinOp;

} // namespace circt::sim
namespace circt::sim {

/// Character format specifier
/// Format the given integer value as a single character.
/// 
/// For integer values up to 127, ASCII compatible encoding is assumed.
/// For larger values, the encoding is unspecified.
/// 
/// If the argument's type width is less than eight bits, the value is
/// zero extended.
/// If the width is greater than eight bits, the resulting formatted string
/// is undefined.
class FormatCharOp;

} // namespace circt::sim
namespace circt::sim {

/// Simulation time format specifier
/// Format string fragment that resolves to the current simulation time when
/// printed. The textual representation is implementation defined.
class FormatCurrentTimeOp;

} // namespace circt::sim
namespace circt::sim {

/// Decimal format specifier
/// Format the given integer value as signed or unsigned decimal string.
/// 
/// Leading zeros are omitted. Non-negative or unsigned values will
/// _not_ be prefixed with a '+'.
/// 
/// For unsigned formatting, the printed value will
/// be left-padded with spaces up to _at least_ the length required to print
/// the maximum unsigned value of the argument's type.
/// For signed formatting, the printed value will be
/// left-padded with spaces up to _at least_ the length required
/// to print the minimum signed value of the argument's type
/// including the '-' character.
/// E.g., a zero value of type `i1` requires no padding for unsigned
/// formatting and one leading space for signed formatting.
/// Format specifiers of same argument type and signedness must be
/// padded to the same width. Zero width values will produce
/// a single '0'.
/// 
/// Backends are recommended to not exceed the required amount of padding.
class FormatDecOp;

} // namespace circt::sim
namespace circt::sim {

/// Real format specifier
/// Format the given real value in floating point (decimal) notation
class FormatFloatOp;

} // namespace circt::sim
namespace circt::sim {

/// Real format specifier
/// Format floating-point numbers using either decimal or scientific notation
/// based on the exponent and precision parameter fracDigits (default: 6)
/// 
/// For exp ≥ 0:
/// Uses decimal notation if exp + 1 ≤ max(1, fracDigits), otherwise switches
/// to scientific notation with max(0, fracDigits - 1) fractional digits
/// 
/// For exp < 0:
/// If exp ≥ -4: Uses decimal notation with max(b - 1, 0) + |exp| fractional digits
/// If exp < -4: Uses scientific notation with max(b - 1, 0) fractional digits
class FormatGeneralOp;

} // namespace circt::sim
namespace circt::sim {

/// Hexadecimal format specifier
/// Format the given integer value as lower-case hexadecimal string.
/// 
/// The printed value will be left-padded with '0' up to the
/// length required to print the maximum value of the argument's
/// type. Zero width values will produce the empty string.
/// No further prefix will be added.
class FormatHexOp;

} // namespace circt::sim
namespace circt::sim {

/// Hierarchical path format specifier
/// Format string fragment that resolves to the hierarchical path of the module
/// instance containing this operation when printed. This corresponds to the
/// `%m` (or `%M` with escaped special characters) format specifier in
/// SystemVerilog.
/// 
/// See IEEE 1800-2017 § 21.2.1.6 "Hierarchical name format".
/// 
/// The `useEscapes` attribute distinguishes between `%m` (false) and `%M`
/// (true). When true, special characters in the path should be escaped.
class FormatHierPathOp;

} // namespace circt::sim
namespace circt::sim {

/// Literal string fragment
/// Creates a constant, raw ASCII string literal for formatted printing.
/// The given string attribute will be outputted as is,
/// including non-printable characters. The literal may be empty or contain
/// null characters ('\0') which must not be interpreted as string
/// terminators by backends.
class FormatLiteralOp;

} // namespace circt::sim
namespace circt::sim {

/// Octal format specifier
/// Format the given integer value as lower-case octal (base eight) string.
/// 
/// The printed value will be left-padded with '0' up to the
/// length required to print the maximum value of the argument's
/// type. Zero width values will produce the empty string.
/// No further prefix will be added.
class FormatOctOp;

} // namespace circt::sim
namespace circt::sim {

/// Real format specifier
/// Format the given real value in scientific (exponential) notation
class FormatScientificOp;

} // namespace circt::sim
namespace circt::sim {

/// Concatenate format strings
/// Concatenates an arbitrary number of format strings from
/// left to right. If the argument list is empty, the empty string
/// literal is produced.
/// 
/// Concatenations must not be recursive. I.e., a concatenated string should
/// not contain itself directly or indirectly.
class FormatStringConcatOp;

} // namespace circt::sim
namespace circt::sim {

/// Dynamic string format specifier
/// Format the given dynamic string value.
/// 
/// If `specifierWidth` is present and larger than the string length, the
/// result is padded to that width using `paddingChar`. By default, strings are
/// right-aligned and padded with spaces.
class FormatStringOp;

} // namespace circt::sim
namespace circt::sim {

/// Get an output stream for a formatted file name
/// Resolves a file name from a `!sim.fstring` value, immediately creates the
/// corresponding file, and returns an output stream resource that can be
/// consumed by `sim.proc.print`. The file-name format string should be
/// constructed using `sim.fmt.*` operations, just like any other Sim
/// format-string value.
/// 
/// This operation has an immediate side effect: executing it creates the file,
/// even if the returned stream is never subsequently consumed.
/// 
/// The concrete runtime representation and lifetime management of the returned
/// stream are backend-defined.
class GetFileOp;

} // namespace circt::sim
namespace circt::sim {

/// Convert an integer into a string
/// Converts an integer value to a string following Verilog semantics, where
/// string literals are represented as right-aligned bitvectors.
/// 
/// The operation reads the integer byte-by-byte, interpreting each non-zero
/// byte as an ASCII character. Zero-valued bytes are skipped and
/// not included in the output string. See Sec 6.16 of the standard saying
/// "A string variable shall not contain the special character "\0".
/// Assigning the value 0 to a string character shall be ignored"
/// 
/// Example:
///   Consider the hex value 0x00_00_00_48_00_00_6C_6F
///   Reading from MSB to LSB and filtering out null bytes:
///     - 0x48 = 'H'
///     - 0x6C = 'l'
///     - 0x6F = 'o'
///   This produces the string "Hlo", not "\0\0\0H\0\0lo".
class IntToStringOp;

} // namespace circt::sim
namespace circt::sim {

/// Pause the simulation
/// Interrupt the simulation and give control back to the user in case of an
/// interactive simulation. Non-interactive simulations may choose to terminate
/// instead. Depending on the `verbose` operand, simulators may print additional
/// information about the current simulation time and hierarchical location of
/// the op.
/// 
/// This op corresponds to the following SystemVerilog constructs:
/// 
/// | Operation           | SystemVerilog          |
/// |---------------------|------------------------|
/// | `sim.pause quiet`   | `$stop(0)`             |
/// | `sim.pause verbose` | `$stop` or `$stop(1)`  |
class PauseOp;

} // namespace circt::sim
namespace circt::sim {

/// SystemVerilog `$test$plusargs` call
class PlusArgsTestOp;

} // namespace circt::sim
namespace circt::sim {

/// SystemVerilog `$value$plusargs` call
class PlusArgsValueOp;

} // namespace circt::sim
namespace circt::sim {

/// Print a formatted string on a given clock and condition
/// Evaluate a format string and print it to the simulation console on the
/// rising edge of the given clock, if, and only if, the condition argument
/// is 'true'.
/// 
/// Multiple print operations in the same module and on the same clock edge
/// are performed according to their order of occurence in the IR. The order
/// of printing for operations in different modules, instances or on different
/// clocks is undefined.
class PrintFormattedOp;

} // namespace circt::sim
namespace circt::sim {

/// Print a formatted string within a procedural region
/// Evaluate a format string and print it to the simulation console.
/// 
/// This operation must be within a procedural region.
class PrintFormattedProcOp;

} // namespace circt::sim
namespace circt::sim {

/// Compares two queues
/// Carries out a comparison on two queues.
/// Returns 1 if the comparison is true, and 0 if it is false.
/// 
/// Comparing for equality and inequality are both supported.
class QueueCmpOp;

} // namespace circt::sim
namespace circt::sim {

/// Concatenate queues
/// Concatenates an arbitrary number of queues into one larger queue.
/// The queues are joined from left to right.
/// 
/// All queues must have the same element type, but the bounds may differ.
/// 
/// If the total length of the inputs doesn't fit into the queue bound of
/// $result, then the excess elements at the end of the queue are discarded.
class QueueConcatOp;

} // namespace circt::sim
namespace circt::sim {

/// Deletes an element from a queue
/// Deletes the queue element at the position `index`. Does nothing if `index`
/// is negative or greater than or equal to the length of the queue.
class QueueDeleteOp;

} // namespace circt::sim
namespace circt::sim {

/// Creates an empty queue
/// Creates an empty queue, which is the default value
/// for a variable holding a queue.
class QueueEmptyOp;

} // namespace circt::sim
namespace circt::sim {

/// Creates a queue containing the elements of the given array.
/// 
/// The queue and array must have the same element type.
/// 
/// If the queue type has bounds, any elements outside the bounds will be
/// discarded.
class QueueFromArrayOp;

} // namespace circt::sim
namespace circt::sim {

/// Returns an indexed element of the queue
/// Returns the element at position `index` within the queue.
/// 
/// If the index is negative or greater than or equal to the queue length,
/// this returns a value as indicated in Table 7-1 of IEEE 1800-2023 § 7.4.5
class QueueGetOp;

} // namespace circt::sim
namespace circt::sim {

/// Insert an element at an arbitrary position within the queue
/// Inserts an element at the given index within the queue. Any elements
/// at this index or later will be shifted forward one position. If this results in
/// the last item in the queue being outside the bounds, it is discarded.
/// 
/// If `index` is negative or greater than the queue length, this does nothing.
/// Note that an index equal to the queue length will simply push `item` to the
/// end of the queue.
class QueueInsertOp;

} // namespace circt::sim
namespace circt::sim {

/// Removes the last element of a queue
/// Removes an element from the back of a queue.
/// 
/// If the queue is empty, this has no effect, and the value of `popped`
/// will be the same as obtained by reading a non-existent array element
/// from an array with the same element type,
/// as described in IEEE 1800-2023 § 7.10.2.5 "Pop_back()".
class QueuePopBackOp;

} // namespace circt::sim
namespace circt::sim {

/// Removes the first element of a queue
/// Removes an element from the front of a queue.
/// 
/// If the queue is empty, this has no effect, and the value of `popped`
/// will be the same as obtained by reading a non-existent array element
/// from an array with the same element type,
/// as described in IEEE 1800-2023 § 7.10.2.4 "Pop_front()".
class QueuePopFrontOp;

} // namespace circt::sim
namespace circt::sim {

/// Push an element to the end of a queue
/// Adds an element to the end of the queue. If the queue is a bounded queue
/// which is full, then this has no effect.
class QueuePushBackOp;

} // namespace circt::sim
namespace circt::sim {

/// Push an element to the front of a queue
/// Adds an element to the front of the queue. If the queue is a bounded
/// queue which is full, then this will erase the final element of the queue,
/// as to keep the queue within-bounds.
class QueuePushFrontOp;

} // namespace circt::sim
namespace circt::sim {

/// Converts between two queues with different bounds, but the same element
/// type.
/// 
/// If $result has a smaller bound than the size of $input, elements at the end
/// of the queue will be discarded to ensure it fits within the space provided.
class QueueResizeOp;

} // namespace circt::sim
namespace circt::sim {

/// Overwrite an element at a position within a queue.
/// Overwrites the element at $index with $item, returning an updated queue.
/// 
/// 
/// If the index is equal to the length of the queue, the operation adds $item
/// to the end of the queue.
/// 
/// If the index is otherwise out of bounds for the queue, the queue returned
/// is unchanged.
class QueueSetOp;

} // namespace circt::sim
namespace circt::sim {

/// Length of a queue
/// Returns the length of a queue as an `i64` value.
class QueueSizeOp;

} // namespace circt::sim
namespace circt::sim {

/// Returns a range of elements from a queue
/// Returns the elements from index `lowIdx` of the `queue` to `highIdx` inclusive,
/// copied into a new queue.
/// 
/// If either index is out of bounds, the out of bounds elements within the selection
/// will have a special value as defined by the element type in IEEE 1800-2023 § 7.4.5, Table 7-1.
class QueueSliceOp;

} // namespace circt::sim
namespace circt::sim {

/// Cast a SV file descriptor or multichannel descriptor to an output stream
/// Casts a SystemVerilog output channel (an integer returned by `sv.fopen`,
/// or a predefined channel such as stdout (`32'h8000_0001`) or stderr
/// (`32'h8000_0002`)) to an `!sim.output_stream`.
/// The input must represent a valid SystemVerilog file descriptor or
/// multichannel descriptor, which can be used for writing. Otherwise,
/// this operation causes undefined behavior.
/// 
/// See IEEE 1800-2017 § 21.3.1 "Opening and closing files".
class SVChannelToOutputStreamOp;

} // namespace circt::sim
namespace circt::sim {

/// Close a file descriptor
/// Implements the SystemVerilog `$fclose` system function.
/// See IEEE 1800-2017 § 21.3.1 "Opening and closing files".
class SVFCloseOp;

} // namespace circt::sim
namespace circt::sim {

/// Flush all open files
/// Implements the SystemVerilog `$fflush` system tasks when called with no
/// arguments, which flushes all files opened by `sim.sv.fopen`.
/// 
/// See IEEE 1800-2017 § 21.3.6 "Flushing output".
class SVFFlushAllOp;

} // namespace circt::sim
namespace circt::sim {

/// Open a file and return a file descriptor
/// Implements the SystemVerilog `$fopen` system function.
/// See IEEE 1800-2017 § 21.3.1 "Opening and closing files".
class SVFOpenOp;

} // namespace circt::sim
namespace circt::sim {

/// The standard error stream
/// Returns a reference to the standard error stream, which can be consumed
/// by `sim.print` or `sim.proc.print`.
class StderrStreamOp;

} // namespace circt::sim
namespace circt::sim {

/// The standard output stream
/// Returns a reference to the standard output stream, which can be consumed
/// by `sim.print` or `sim.proc.print`.
class StdoutStreamOp;

} // namespace circt::sim
namespace circt::sim {

/// Concatenate strings
/// Concatenates multiple strings into a single, longer string. The first
/// operand appears first in the output string. The last character of the first
/// operand is immediately followed by the first character of the second
/// operand. If the operation has a single operand, its result is equal to that
/// operand. If the operation has zero operands, it returns an empty string.
/// The length of the result is the sum of each operand's length.
/// 
/// Example:
/// 
/// ```mlir
/// %0 = sim.string.literal "abc"
/// %1 = sim.string.literal "def"
/// %2 = sim.string.literal "ghj"
/// %3 = sim.string.concat (%0, %1, %2)  // %3 is "abcdefghj"
/// %4 = sim.string.concat (%0)          // %4 is "abc"
/// %5 = sim.string.concat ()            // %5 is ""
/// ```
class StringConcatOp;

} // namespace circt::sim
namespace circt::sim {

/// Literal string fragment
/// Creates a dynamic string from a constant string literal.
class StringConstantOp;

} // namespace circt::sim
namespace circt::sim {

/// Get a character from a string at a given index
/// Returns the character (byte) at the specified index within a dynamic string.
/// The index is zero-based, where 0 refers to the first character.
/// 
/// If the index is negative or greater than or equal to the string length,
/// the behavior follows IEEE 1800-2023 § 6.16, which specifies that accessing
/// an out-of-bounds index returns 0 (null character).
/// 
/// Example:
/// ```mlir
/// %str = sim.string.literal "Hello"
/// %idx = hw.constant 1 : i32
/// %char = sim.string.get %str[%idx] : i8  // Returns 'e' (0x65)
/// ```
class StringGetOp;

} // namespace circt::sim
namespace circt::sim {

/// Length of a string
/// Returns the length of a dynamic string as an `i64` value.
class StringLengthOp;

} // namespace circt::sim
namespace circt::sim {

/// Terminate the simulation
/// Terminate the simulation with a success or failure exit code. Depending on
/// the `verbose` operand, simulators may print additional information about the
/// current simulation time and hierarchical location of the op.
/// 
/// This op correpsonds to the following SystemVerilog constructs:
/// 
/// | Operation                        | SystemVerilog             |
/// |----------------------------------|---------------------------|
/// | `sim.terminate success, quiet`   | `$finish(0)`              |
/// | `sim.terminate success, verbose` | `$finish` or `$finish(1)` |
/// | `sim.terminate failure, quiet`   | `$fatal(0)`               |
/// | `sim.terminate failure, verbose` | `$fatal` or `$fatal(1)`   |
/// 
/// Note that this op does not match the behavior of the `$exit` system task in
/// SystemVerilog, which blocks execution of the calling process until all
/// `program` instances have terminated, and then calls `$finish`.
class TerminateOp;

} // namespace circt::sim
namespace circt::sim {

/// A procedural region triggered on a clock edge
/// A procedural region that executes on the rising edge of the given clock.
/// An optional 1-bit condition can be provided to guard execution of the
/// region on that clock edge.
class TriggeredOp;

} // namespace circt::sim
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::ClockedPauseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockedPauseOpGenericAdaptorBase {
public:
  struct Properties {
    using verboseTy = ::mlir::BoolAttr;
    verboseTy verbose;

    auto getVerbose() const {
      auto &propStorage = this->verbose;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setVerbose(const ::mlir::BoolAttr &propValue) {
      this->verbose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.verbose == this->verbose &&
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
  ClockedPauseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.clocked_pause", odsAttrs.getContext());
  }

  ClockedPauseOpGenericAdaptorBase(ClockedPauseOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getVerboseAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
    return attr;
  }

  bool getVerbose();
};

} // namespace detail
template <typename RangeT>
class ClockedPauseOpGenericAdaptor : public detail::ClockedPauseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockedPauseOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
public:
  ClockedPauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockedPauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockedPauseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockedPauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockedPauseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockedPauseOpGenericAdaptor(RangeT values, const ClockedPauseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockedPauseOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockedPauseOp>>>
  ClockedPauseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getCondition() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockedPauseOpAdaptor : public ClockedPauseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockedPauseOpGenericAdaptor::ClockedPauseOpGenericAdaptor;
  ClockedPauseOpAdaptor(ClockedPauseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockedPauseOp : public ::mlir::Op<ClockedPauseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::NonProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockedPauseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockedPauseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("verbose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getVerboseAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getVerboseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.clocked_pause");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getConditionMutable() {
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
  ::mlir::BoolAttr getVerboseAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
  }

  bool getVerbose();
  void setVerboseAttr(::mlir::BoolAttr attr) {
    getProperties().verbose = attr;
  }

  void setVerbose(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool verbose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedPauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedPauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::ClockedPauseOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::ClockedPauseOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::ClockedTerminateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockedTerminateOpGenericAdaptorBase {
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
    using verboseTy = ::mlir::BoolAttr;
    verboseTy verbose;

    auto getVerbose() const {
      auto &propStorage = this->verbose;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setVerbose(const ::mlir::BoolAttr &propValue) {
      this->verbose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.success == this->success &&
        rhs.verbose == this->verbose &&
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
  ClockedTerminateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.clocked_terminate", odsAttrs.getContext());
  }

  ClockedTerminateOpGenericAdaptorBase(ClockedTerminateOp op);

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
  ::mlir::BoolAttr getVerboseAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
    return attr;
  }

  bool getVerbose();
};

} // namespace detail
template <typename RangeT>
class ClockedTerminateOpGenericAdaptor : public detail::ClockedTerminateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockedTerminateOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
public:
  ClockedTerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockedTerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockedTerminateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockedTerminateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockedTerminateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockedTerminateOpGenericAdaptor(RangeT values, const ClockedTerminateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockedTerminateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockedTerminateOp>>>
  ClockedTerminateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getCondition() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockedTerminateOpAdaptor : public ClockedTerminateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockedTerminateOpGenericAdaptor::ClockedTerminateOpGenericAdaptor;
  ClockedTerminateOpAdaptor(ClockedTerminateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockedTerminateOp : public ::mlir::Op<ClockedTerminateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::NonProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockedTerminateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockedTerminateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("success"), ::llvm::StringRef("verbose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSuccessAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSuccessAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getVerboseAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getVerboseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.clocked_terminate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getConditionMutable() {
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
  ::mlir::BoolAttr getSuccessAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().success);
  }

  bool getSuccess();
  ::mlir::BoolAttr getVerboseAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
  }

  bool getVerbose();
  void setSuccessAttr(::mlir::BoolAttr attr) {
    getProperties().success = attr;
  }

  void setSuccess(bool attrValue);
  void setVerboseAttr(::mlir::BoolAttr attr) {
    getProperties().verbose = attr;
  }

  void setVerbose(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value condition, bool success, bool verbose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedTerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedTerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::ClockedTerminateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::ClockedTerminateOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::DPICallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DPICallOpGenericAdaptorBase {
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
        rhs.callee == this->callee &&
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
  DPICallOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.func.dpi.call", odsAttrs.getContext());
  }

  DPICallOpGenericAdaptorBase(DPICallOp op);

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
class DPICallOpGenericAdaptor : public detail::DPICallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DPICallOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_inputs = 2;
public:
  DPICallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DPICallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DPICallOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DPICallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : DPICallOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DPICallOpGenericAdaptor(RangeT values, const DPICallOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DPICallOp, typename = std::enable_if_t<std::is_same_v<LateInst, DPICallOp>>>
  DPICallOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  RangeT getInputs() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DPICallOpAdaptor : public DPICallOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DPICallOpGenericAdaptor::DPICallOpGenericAdaptor;
  DPICallOpAdaptor(DPICallOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DPICallOp : public ::mlir::Op<DPICallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DPICallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DPICallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_inputs = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("callee"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCalleeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCalleeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.func.dpi.call");
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

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getClockMutable();
  ::mlir::MutableOperandRange getEnableMutable();
  ::mlir::MutableOperandRange getInputsMutable();
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
  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
  }

  ::llvm::StringRef getCallee();
  void setCalleeAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().callee = attr;
  }

  void setCallee(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static DPICallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static DPICallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::mlir::FlatSymbolRefAttr callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::llvm::StringRef callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static DPICallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::llvm::StringRef callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static DPICallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::llvm::StringRef callee, /*optional*/::mlir::Value clock, /*optional*/::mlir::Value enable, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DPICallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DPICallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DPICallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DPICallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    return getInputs();
  }
  MutableOperandRange getArgOperandsMutable() {
    return getInputsMutable();
  }
  mlir::CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<mlir::SymbolRefAttr>("callee");
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::DPICallOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::DPICallOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::DPIFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DPIFuncOpGenericAdaptorBase {
public:
  struct Properties {
    using argument_locsTy = ::mlir::ArrayAttr;
    argument_locsTy argument_locs;

    auto getArgumentLocs() const {
      auto &propStorage = this->argument_locs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgumentLocs(const ::mlir::ArrayAttr &propValue) {
      this->argument_locs = propValue;
    }
    using dpi_function_typeTy = ::mlir::TypeAttr;
    dpi_function_typeTy dpi_function_type;

    auto getDpiFunctionType() const {
      auto &propStorage = this->dpi_function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setDpiFunctionType(const ::mlir::TypeAttr &propValue) {
      this->dpi_function_type = propValue;
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
        rhs.argument_locs == this->argument_locs &&
        rhs.dpi_function_type == this->dpi_function_type &&
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
  DPIFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.func.dpi", odsAttrs.getContext());
  }

  DPIFuncOpGenericAdaptorBase(DPIFuncOp op);

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
  ::mlir::TypeAttr getDpiFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().dpi_function_type);
    return attr;
  }

  ::circt::sim::DPIFunctionType getDpiFunctionType();
  ::mlir::ArrayAttr getArgumentLocsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().argument_locs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgumentLocs();
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
class DPIFuncOpGenericAdaptor : public detail::DPIFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DPIFuncOpGenericAdaptorBase;
public:
  DPIFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DPIFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DPIFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DPIFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DPIFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DPIFuncOpGenericAdaptor(RangeT values, const DPIFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DPIFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, DPIFuncOp>>>
  DPIFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DPIFuncOpAdaptor : public DPIFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DPIFuncOpGenericAdaptor::DPIFuncOpGenericAdaptor;
  DPIFuncOpAdaptor(DPIFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DPIFuncOp : public ::mlir::Op<DPIFuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DPIFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DPIFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::FunctionOpInterface::Trait<DPIFuncOp>::verifyBody;
  using ::mlir::FunctionOpInterface::Trait<DPIFuncOp>::verifyType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argument_locs"), ::llvm::StringRef("dpi_function_type"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("verilogName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgumentLocsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgumentLocsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDpiFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDpiFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getVerilogNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getVerilogNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.func.dpi");
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
  ::mlir::TypeAttr getDpiFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().dpi_function_type);
  }

  ::circt::sim::DPIFunctionType getDpiFunctionType();
  ::mlir::ArrayAttr getArgumentLocsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().argument_locs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgumentLocs();
  ::mlir::StringAttr getVerilogNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setDpiFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().dpi_function_type = attr;
  }

  void setDpiFunctionType(::circt::sim::DPIFunctionType attrValue);
  void setArgumentLocsAttr(::mlir::ArrayAttr attr) {
    getProperties().argument_locs = attr;
  }

  void setVerilogNameAttr(::mlir::StringAttr attr) {
    getProperties().verilogName = attr;
  }

  void setVerilogName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeArgumentLocsAttr() {
      auto attr = getProperties().argument_locs;
      getProperties().argument_locs = {};
      return attr;
  }

  ::mlir::Attribute removeVerilogNameAttr() {
      auto attr = getProperties().verilogName;
      getProperties().verilogName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name, ArrayRef<StringAttr> argNames, ArrayRef<Type> argTypes, ArrayRef<DPIDirection> argDirections, ArrayAttr argLocs, StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name, ArrayRef<StringAttr> argNames, ArrayRef<Type> argTypes, ArrayRef<DPIDirection> argDirections, ArrayAttr argLocs, StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name, ArrayRef<StringAttr> argNames, ArrayRef<Type> argTypes, ArrayRef<DPIDirection> argDirections, ArrayAttr argLocs, StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name, DPIFunctionType dpiFunctionType, ArrayAttr argLocs, StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name, DPIFunctionType dpiFunctionType, ArrayAttr argLocs, StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name, DPIFunctionType dpiFunctionType, ArrayAttr argLocs, StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::circt::sim::DPIFunctionType dpi_function_type, /*optional*/::mlir::ArrayAttr argument_locs, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DPIFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DPIFuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::Type getFunctionType();
  void setFunctionTypeAttr(::mlir::TypeAttr type);
  ::mlir::Type cloneTypeWith(::mlir::TypeRange inputs, ::mlir::TypeRange results);
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
  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() {
    return ::llvm::cast<::mlir::FunctionType>(getFunctionType()).getInputs();
  }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() {
    return ::llvm::cast<::mlir::FunctionType>(getFunctionType()).getResults();
  }

  ::mlir::Region *getCallableRegion() { return nullptr; }

  /// Provide a getFunctionTypeAttrName for FunctionOpInterface trait
  /// (buildWithEntryBlock).  DPIFuncOp does not store function_type as a
  /// separate attribute; it is derived from dpi_function_type.
  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getDpiFunctionTypeAttrName(name);
  }
  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getDpiFunctionTypeAttrName();
  }

  /// Stub implementations for ArgumentAttributesMethods.
  mlir::ArrayAttr getArgAttrsAttr() { return nullptr; }
  mlir::ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(mlir::ArrayAttr args) {}
  void setResAttrsAttr(mlir::ArrayAttr args) {}
  mlir::Attribute removeArgAttrsAttr() { return nullptr; }
  mlir::Attribute removeResAttrsAttr() { return nullptr; }
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::DPIFuncOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::DPIFuncOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FlushOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FlushOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FlushOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.flush", odsAttrs.getContext());
  }

  FlushOpGenericAdaptorBase(FlushOp op);

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
class FlushOpGenericAdaptor : public detail::FlushOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FlushOpGenericAdaptorBase;
  static constexpr int odsIndex_stream = 0;
public:
  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FlushOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FlushOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FlushOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FlushOpGenericAdaptor(RangeT values, const FlushOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FlushOp, typename = std::enable_if_t<std::is_same_v<LateInst, FlushOp>>>
  FlushOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStream() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FlushOpAdaptor : public FlushOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FlushOpGenericAdaptor::FlushOpGenericAdaptor;
  FlushOpAdaptor(FlushOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FlushOp : public ::mlir::Op<FlushOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FlushOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FlushOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_stream = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.flush");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getStream() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStreamMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value stream);
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value stream);
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value stream);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value stream);
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value stream);
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value stream);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FlushOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FlushOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FlushOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatBinOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatBinOpGenericAdaptorBase {
public:
  struct Properties {
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    using paddingCharTy = ::mlir::IntegerAttr;
    paddingCharTy paddingChar;

    auto getPaddingChar() const {
      auto &propStorage = this->paddingChar;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPaddingChar(const ::mlir::IntegerAttr &propValue) {
      this->paddingChar = propValue;
    }
    using specifierWidthTy = ::mlir::IntegerAttr;
    specifierWidthTy specifierWidth;

    auto getSpecifierWidth() const {
      auto &propStorage = this->specifierWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSpecifierWidth(const ::mlir::IntegerAttr &propValue) {
      this->specifierWidth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isLeftAligned == this->isLeftAligned &&
        rhs.paddingChar == this->paddingChar &&
        rhs.specifierWidth == this->specifierWidth &&
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
  FormatBinOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.bin", odsAttrs.getContext());
  }

  FormatBinOpGenericAdaptorBase(FormatBinOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr();
  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
    return attr;
  }

  ::std::optional<uint32_t> getSpecifierWidth();
};

} // namespace detail
template <typename RangeT>
class FormatBinOpGenericAdaptor : public detail::FormatBinOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatBinOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatBinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatBinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatBinOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatBinOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatBinOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatBinOpGenericAdaptor(RangeT values, const FormatBinOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatBinOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatBinOp>>>
  FormatBinOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatBinOpAdaptor : public FormatBinOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatBinOpGenericAdaptor::FormatBinOpGenericAdaptor;
  FormatBinOpAdaptor(FormatBinOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatBinOp : public ::mlir::Op<FormatBinOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatBinOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatBinOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isLeftAligned"), ::llvm::StringRef("paddingChar"), ::llvm::StringRef("specifierWidth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPaddingCharAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPaddingCharAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSpecifierWidthAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSpecifierWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.bin");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().paddingChar);
  }

  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setPaddingCharAttr(::mlir::IntegerAttr attr) {
    getProperties().paddingChar = attr;
  }

  void setPaddingChar(uint8_t attrValue);
  void setSpecifierWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().specifierWidth = attr;
  }

  void setSpecifierWidth(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeSpecifierWidthAttr() {
      auto attr = getProperties().specifierWidth;
      getProperties().specifierWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatBinOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatBinOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatBinOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatBinOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatCharOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatCharOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FormatCharOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.char", odsAttrs.getContext());
  }

  FormatCharOpGenericAdaptorBase(FormatCharOp op);

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
class FormatCharOpGenericAdaptor : public detail::FormatCharOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatCharOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatCharOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatCharOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatCharOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatCharOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatCharOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatCharOpGenericAdaptor(RangeT values, const FormatCharOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatCharOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatCharOp>>>
  FormatCharOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatCharOpAdaptor : public FormatCharOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatCharOpGenericAdaptor::FormatCharOpGenericAdaptor;
  FormatCharOpAdaptor(FormatCharOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatCharOp : public ::mlir::Op<FormatCharOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatCharOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatCharOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.char");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value);
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value);
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value);
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value);
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCharOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCharOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatCharOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatCurrentTimeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatCurrentTimeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FormatCurrentTimeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.current_time", odsAttrs.getContext());
  }

  FormatCurrentTimeOpGenericAdaptorBase(FormatCurrentTimeOp op);

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
class FormatCurrentTimeOpGenericAdaptor : public detail::FormatCurrentTimeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatCurrentTimeOpGenericAdaptorBase;
public:
  FormatCurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatCurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatCurrentTimeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatCurrentTimeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatCurrentTimeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatCurrentTimeOpGenericAdaptor(RangeT values, const FormatCurrentTimeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatCurrentTimeOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatCurrentTimeOp>>>
  FormatCurrentTimeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatCurrentTimeOpAdaptor : public FormatCurrentTimeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatCurrentTimeOpGenericAdaptor::FormatCurrentTimeOpGenericAdaptor;
  FormatCurrentTimeOpAdaptor(FormatCurrentTimeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatCurrentTimeOp : public ::mlir::Op<FormatCurrentTimeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatCurrentTimeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatCurrentTimeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.current_time");
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCurrentTimeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatCurrentTimeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatCurrentTimeOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatDecOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatDecOpGenericAdaptorBase {
public:
  struct Properties {
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    using isSignedTy = ::mlir::UnitAttr;
    isSignedTy isSigned;

    auto getIsSigned() const {
      auto &propStorage = this->isSigned;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsSigned(const ::mlir::UnitAttr &propValue) {
      this->isSigned = propValue;
    }
    using paddingCharTy = ::mlir::IntegerAttr;
    paddingCharTy paddingChar;

    auto getPaddingChar() const {
      auto &propStorage = this->paddingChar;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPaddingChar(const ::mlir::IntegerAttr &propValue) {
      this->paddingChar = propValue;
    }
    using specifierWidthTy = ::mlir::IntegerAttr;
    specifierWidthTy specifierWidth;

    auto getSpecifierWidth() const {
      auto &propStorage = this->specifierWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSpecifierWidth(const ::mlir::IntegerAttr &propValue) {
      this->specifierWidth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isLeftAligned == this->isLeftAligned &&
        rhs.isSigned == this->isSigned &&
        rhs.paddingChar == this->paddingChar &&
        rhs.specifierWidth == this->specifierWidth &&
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
  FormatDecOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.dec", odsAttrs.getContext());
  }

  FormatDecOpGenericAdaptorBase(FormatDecOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr();
  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
    return attr;
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  ::mlir::UnitAttr getIsSignedAttr();
  bool getIsSigned();
};

} // namespace detail
template <typename RangeT>
class FormatDecOpGenericAdaptor : public detail::FormatDecOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatDecOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatDecOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatDecOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatDecOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatDecOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatDecOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatDecOpGenericAdaptor(RangeT values, const FormatDecOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatDecOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatDecOp>>>
  FormatDecOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatDecOpAdaptor : public FormatDecOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatDecOpGenericAdaptor::FormatDecOpGenericAdaptor;
  FormatDecOpAdaptor(FormatDecOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatDecOp : public ::mlir::Op<FormatDecOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatDecOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatDecOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isLeftAligned"), ::llvm::StringRef("isSigned"), ::llvm::StringRef("paddingChar"), ::llvm::StringRef("specifierWidth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsSignedAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsSignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPaddingCharAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPaddingCharAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSpecifierWidthAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSpecifierWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.dec");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().paddingChar);
  }

  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  ::mlir::UnitAttr getIsSignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isSigned);
  }

  bool getIsSigned();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setPaddingCharAttr(::mlir::IntegerAttr attr) {
    getProperties().paddingChar = attr;
  }

  void setPaddingChar(uint8_t attrValue);
  void setSpecifierWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().specifierWidth = attr;
  }

  void setSpecifierWidth(::std::optional<uint32_t> attrValue);
  void setIsSignedAttr(::mlir::UnitAttr attr) {
    getProperties().isSigned = attr;
  }

  void setIsSigned(bool attrValue);
  ::mlir::Attribute removeSpecifierWidthAttr() {
      auto attr = getProperties().specifierWidth;
      getProperties().specifierWidth = {};
      return attr;
  }

  ::mlir::Attribute removeIsSignedAttr() {
      auto attr = getProperties().isSigned;
      getProperties().isSigned = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/::mlir::UnitAttr isSigned);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth, /*optional*/bool isSigned = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatDecOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatDecOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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
  static inline unsigned getDecimalWidth(unsigned bits, bool isSigned) {
    if (bits == 0)
      return 1;
    if (bits == 1)
      return isSigned ? 2 : 1;

    if (isSigned)
      bits--;

    // Should be precise up until bits = 13301
    // log(2) / log(10) + epsilon
    const double baseConversionFactor = 0.30103;
    unsigned digits = std::ceil(bits * baseConversionFactor);

    return isSigned ? digits + 1 : digits;
  }
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatDecOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatDecOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatFloatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatFloatOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldWidthTy = ::mlir::IntegerAttr;
    fieldWidthTy fieldWidth;

    auto getFieldWidth() const {
      auto &propStorage = this->fieldWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldWidth(const ::mlir::IntegerAttr &propValue) {
      this->fieldWidth = propValue;
    }
    using fracDigitsTy = ::mlir::IntegerAttr;
    fracDigitsTy fracDigits;

    auto getFracDigits() const {
      auto &propStorage = this->fracDigits;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFracDigits(const ::mlir::IntegerAttr &propValue) {
      this->fracDigits = propValue;
    }
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldWidth == this->fieldWidth &&
        rhs.fracDigits == this->fracDigits &&
        rhs.isLeftAligned == this->isLeftAligned &&
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
  FormatFloatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.flt", odsAttrs.getContext());
  }

  FormatFloatOpGenericAdaptorBase(FormatFloatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
    return attr;
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr();
  uint32_t getFracDigits();
};

} // namespace detail
template <typename RangeT>
class FormatFloatOpGenericAdaptor : public detail::FormatFloatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatFloatOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatFloatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatFloatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatFloatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatFloatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatFloatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatFloatOpGenericAdaptor(RangeT values, const FormatFloatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatFloatOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatFloatOp>>>
  FormatFloatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatFloatOpAdaptor : public FormatFloatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatFloatOpGenericAdaptor::FormatFloatOpGenericAdaptor;
  FormatFloatOpAdaptor(FormatFloatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatFloatOp : public ::mlir::Op<FormatFloatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatFloatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatFloatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldWidth"), ::llvm::StringRef("fracDigits"), ::llvm::StringRef("isLeftAligned")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldWidthAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFracDigitsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFracDigitsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.flt");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::FloatType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::FloatType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fracDigits);
  }

  uint32_t getFracDigits();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setFieldWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldWidth = attr;
  }

  void setFieldWidth(::std::optional<uint32_t> attrValue);
  void setFracDigitsAttr(::mlir::IntegerAttr attr) {
    getProperties().fracDigits = attr;
  }

  void setFracDigits(uint32_t attrValue);
  ::mlir::Attribute removeFieldWidthAttr() {
      auto attr = getProperties().fieldWidth;
      getProperties().fieldWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatFloatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatFloatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatFloatOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatFloatOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatGeneralOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatGeneralOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldWidthTy = ::mlir::IntegerAttr;
    fieldWidthTy fieldWidth;

    auto getFieldWidth() const {
      auto &propStorage = this->fieldWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldWidth(const ::mlir::IntegerAttr &propValue) {
      this->fieldWidth = propValue;
    }
    using fracDigitsTy = ::mlir::IntegerAttr;
    fracDigitsTy fracDigits;

    auto getFracDigits() const {
      auto &propStorage = this->fracDigits;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFracDigits(const ::mlir::IntegerAttr &propValue) {
      this->fracDigits = propValue;
    }
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldWidth == this->fieldWidth &&
        rhs.fracDigits == this->fracDigits &&
        rhs.isLeftAligned == this->isLeftAligned &&
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
  FormatGeneralOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.gen", odsAttrs.getContext());
  }

  FormatGeneralOpGenericAdaptorBase(FormatGeneralOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
    return attr;
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr();
  uint32_t getFracDigits();
};

} // namespace detail
template <typename RangeT>
class FormatGeneralOpGenericAdaptor : public detail::FormatGeneralOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatGeneralOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatGeneralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatGeneralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatGeneralOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatGeneralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatGeneralOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatGeneralOpGenericAdaptor(RangeT values, const FormatGeneralOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatGeneralOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatGeneralOp>>>
  FormatGeneralOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatGeneralOpAdaptor : public FormatGeneralOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatGeneralOpGenericAdaptor::FormatGeneralOpGenericAdaptor;
  FormatGeneralOpAdaptor(FormatGeneralOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatGeneralOp : public ::mlir::Op<FormatGeneralOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatGeneralOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatGeneralOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldWidth"), ::llvm::StringRef("fracDigits"), ::llvm::StringRef("isLeftAligned")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldWidthAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFracDigitsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFracDigitsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.gen");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::FloatType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::FloatType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fracDigits);
  }

  uint32_t getFracDigits();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setFieldWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldWidth = attr;
  }

  void setFieldWidth(::std::optional<uint32_t> attrValue);
  void setFracDigitsAttr(::mlir::IntegerAttr attr) {
    getProperties().fracDigits = attr;
  }

  void setFracDigits(uint32_t attrValue);
  ::mlir::Attribute removeFieldWidthAttr() {
      auto attr = getProperties().fieldWidth;
      getProperties().fieldWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatGeneralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatGeneralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatGeneralOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatGeneralOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatHexOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatHexOpGenericAdaptorBase {
public:
  struct Properties {
    using isHexUppercaseTy = ::mlir::BoolAttr;
    isHexUppercaseTy isHexUppercase;

    auto getIsHexUppercase() const {
      auto &propStorage = this->isHexUppercase;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setIsHexUppercase(const ::mlir::BoolAttr &propValue) {
      this->isHexUppercase = propValue;
    }
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    using paddingCharTy = ::mlir::IntegerAttr;
    paddingCharTy paddingChar;

    auto getPaddingChar() const {
      auto &propStorage = this->paddingChar;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPaddingChar(const ::mlir::IntegerAttr &propValue) {
      this->paddingChar = propValue;
    }
    using specifierWidthTy = ::mlir::IntegerAttr;
    specifierWidthTy specifierWidth;

    auto getSpecifierWidth() const {
      auto &propStorage = this->specifierWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSpecifierWidth(const ::mlir::IntegerAttr &propValue) {
      this->specifierWidth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isHexUppercase == this->isHexUppercase &&
        rhs.isLeftAligned == this->isLeftAligned &&
        rhs.paddingChar == this->paddingChar &&
        rhs.specifierWidth == this->specifierWidth &&
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
  FormatHexOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.hex", odsAttrs.getContext());
  }

  FormatHexOpGenericAdaptorBase(FormatHexOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsHexUppercaseAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().isHexUppercase);
    return attr;
  }

  bool getIsHexUppercase();
  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr();
  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
    return attr;
  }

  ::std::optional<uint32_t> getSpecifierWidth();
};

} // namespace detail
template <typename RangeT>
class FormatHexOpGenericAdaptor : public detail::FormatHexOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatHexOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatHexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatHexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatHexOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatHexOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatHexOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatHexOpGenericAdaptor(RangeT values, const FormatHexOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatHexOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatHexOp>>>
  FormatHexOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatHexOpAdaptor : public FormatHexOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatHexOpGenericAdaptor::FormatHexOpGenericAdaptor;
  FormatHexOpAdaptor(FormatHexOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatHexOp : public ::mlir::Op<FormatHexOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatHexOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatHexOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isHexUppercase"), ::llvm::StringRef("isLeftAligned"), ::llvm::StringRef("paddingChar"), ::llvm::StringRef("specifierWidth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsHexUppercaseAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsHexUppercaseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPaddingCharAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPaddingCharAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSpecifierWidthAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSpecifierWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.hex");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsHexUppercaseAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().isHexUppercase);
  }

  bool getIsHexUppercase();
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().paddingChar);
  }

  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  void setIsHexUppercaseAttr(::mlir::BoolAttr attr) {
    getProperties().isHexUppercase = attr;
  }

  void setIsHexUppercase(bool attrValue);
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setPaddingCharAttr(::mlir::IntegerAttr attr) {
    getProperties().paddingChar = attr;
  }

  void setPaddingChar(uint8_t attrValue);
  void setSpecifierWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().specifierWidth = attr;
  }

  void setSpecifierWidth(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeSpecifierWidthAttr() {
      auto attr = getProperties().specifierWidth;
      getProperties().specifierWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isHexUppercase, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isHexUppercase, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHexOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHexOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatHexOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatHexOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatHierPathOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatHierPathOpGenericAdaptorBase {
public:
  struct Properties {
    using useEscapesTy = ::mlir::UnitAttr;
    useEscapesTy useEscapes;

    auto getUseEscapes() const {
      auto &propStorage = this->useEscapes;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setUseEscapes(const ::mlir::UnitAttr &propValue) {
      this->useEscapes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.useEscapes == this->useEscapes &&
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
  FormatHierPathOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.hier_path", odsAttrs.getContext());
  }

  FormatHierPathOpGenericAdaptorBase(FormatHierPathOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getUseEscapesAttr();
  bool getUseEscapes();
};

} // namespace detail
template <typename RangeT>
class FormatHierPathOpGenericAdaptor : public detail::FormatHierPathOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatHierPathOpGenericAdaptorBase;
public:
  FormatHierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatHierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatHierPathOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatHierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatHierPathOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatHierPathOpGenericAdaptor(RangeT values, const FormatHierPathOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatHierPathOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatHierPathOp>>>
  FormatHierPathOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatHierPathOpAdaptor : public FormatHierPathOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatHierPathOpGenericAdaptor::FormatHierPathOpGenericAdaptor;
  FormatHierPathOpAdaptor(FormatHierPathOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatHierPathOp : public ::mlir::Op<FormatHierPathOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatHierPathOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatHierPathOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("useEscapes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getUseEscapesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getUseEscapesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.hier_path");
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getUseEscapesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().useEscapes);
  }

  bool getUseEscapes();
  void setUseEscapesAttr(::mlir::UnitAttr attr) {
    getProperties().useEscapes = attr;
  }

  void setUseEscapes(bool attrValue);
  ::mlir::Attribute removeUseEscapesAttr() {
      auto attr = getProperties().useEscapes;
      getProperties().useEscapes = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::UnitAttr useEscapes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::UnitAttr useEscapes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr useEscapes);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr useEscapes);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/bool useEscapes = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/bool useEscapes = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/bool useEscapes = false);
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/bool useEscapes = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatHierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatHierPathOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatHierPathOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatLiteralOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatLiteralOpGenericAdaptorBase {
public:
  struct Properties {
    using literalTy = ::mlir::StringAttr;
    literalTy literal;

    auto getLiteral() const {
      auto &propStorage = this->literal;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setLiteral(const ::mlir::StringAttr &propValue) {
      this->literal = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.literal == this->literal &&
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
  FormatLiteralOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.literal", odsAttrs.getContext());
  }

  FormatLiteralOpGenericAdaptorBase(FormatLiteralOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLiteralAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().literal);
    return attr;
  }

  ::llvm::StringRef getLiteral();
};

} // namespace detail
template <typename RangeT>
class FormatLiteralOpGenericAdaptor : public detail::FormatLiteralOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatLiteralOpGenericAdaptorBase;
public:
  FormatLiteralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatLiteralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatLiteralOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatLiteralOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatLiteralOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatLiteralOpGenericAdaptor(RangeT values, const FormatLiteralOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatLiteralOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatLiteralOp>>>
  FormatLiteralOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatLiteralOpAdaptor : public FormatLiteralOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatLiteralOpGenericAdaptor::FormatLiteralOpGenericAdaptor;
  FormatLiteralOpAdaptor(FormatLiteralOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatLiteralOp : public ::mlir::Op<FormatLiteralOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatLiteralOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatLiteralOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("literal")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLiteralAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLiteralAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.literal");
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getLiteralAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().literal);
  }

  ::llvm::StringRef getLiteral();
  void setLiteralAttr(::mlir::StringAttr attr) {
    getProperties().literal = attr;
  }

  void setLiteral(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatLiteralOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatLiteralOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatLiteralOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatLiteralOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatOctOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatOctOpGenericAdaptorBase {
public:
  struct Properties {
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    using paddingCharTy = ::mlir::IntegerAttr;
    paddingCharTy paddingChar;

    auto getPaddingChar() const {
      auto &propStorage = this->paddingChar;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPaddingChar(const ::mlir::IntegerAttr &propValue) {
      this->paddingChar = propValue;
    }
    using specifierWidthTy = ::mlir::IntegerAttr;
    specifierWidthTy specifierWidth;

    auto getSpecifierWidth() const {
      auto &propStorage = this->specifierWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSpecifierWidth(const ::mlir::IntegerAttr &propValue) {
      this->specifierWidth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isLeftAligned == this->isLeftAligned &&
        rhs.paddingChar == this->paddingChar &&
        rhs.specifierWidth == this->specifierWidth &&
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
  FormatOctOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.oct", odsAttrs.getContext());
  }

  FormatOctOpGenericAdaptorBase(FormatOctOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr();
  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
    return attr;
  }

  ::std::optional<uint32_t> getSpecifierWidth();
};

} // namespace detail
template <typename RangeT>
class FormatOctOpGenericAdaptor : public detail::FormatOctOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatOctOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatOctOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatOctOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatOctOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatOctOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatOctOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatOctOpGenericAdaptor(RangeT values, const FormatOctOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatOctOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatOctOp>>>
  FormatOctOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatOctOpAdaptor : public FormatOctOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatOctOpGenericAdaptor::FormatOctOpGenericAdaptor;
  FormatOctOpAdaptor(FormatOctOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatOctOp : public ::mlir::Op<FormatOctOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatOctOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatOctOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isLeftAligned"), ::llvm::StringRef("paddingChar"), ::llvm::StringRef("specifierWidth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPaddingCharAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPaddingCharAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSpecifierWidthAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSpecifierWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.oct");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().paddingChar);
  }

  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setPaddingCharAttr(::mlir::IntegerAttr attr) {
    getProperties().paddingChar = attr;
  }

  void setPaddingChar(uint8_t attrValue);
  void setSpecifierWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().specifierWidth = attr;
  }

  void setSpecifierWidth(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeSpecifierWidthAttr() {
      auto attr = getProperties().specifierWidth;
      getProperties().specifierWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatOctOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatOctOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatOctOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatOctOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatScientificOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatScientificOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldWidthTy = ::mlir::IntegerAttr;
    fieldWidthTy fieldWidth;

    auto getFieldWidth() const {
      auto &propStorage = this->fieldWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldWidth(const ::mlir::IntegerAttr &propValue) {
      this->fieldWidth = propValue;
    }
    using fracDigitsTy = ::mlir::IntegerAttr;
    fracDigitsTy fracDigits;

    auto getFracDigits() const {
      auto &propStorage = this->fracDigits;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setFracDigits(const ::mlir::IntegerAttr &propValue) {
      this->fracDigits = propValue;
    }
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldWidth == this->fieldWidth &&
        rhs.fracDigits == this->fracDigits &&
        rhs.isLeftAligned == this->isLeftAligned &&
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
  FormatScientificOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.exp", odsAttrs.getContext());
  }

  FormatScientificOpGenericAdaptorBase(FormatScientificOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
    return attr;
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr();
  uint32_t getFracDigits();
};

} // namespace detail
template <typename RangeT>
class FormatScientificOpGenericAdaptor : public detail::FormatScientificOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatScientificOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatScientificOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatScientificOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatScientificOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatScientificOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatScientificOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatScientificOpGenericAdaptor(RangeT values, const FormatScientificOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatScientificOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatScientificOp>>>
  FormatScientificOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatScientificOpAdaptor : public FormatScientificOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatScientificOpGenericAdaptor::FormatScientificOpGenericAdaptor;
  FormatScientificOpAdaptor(FormatScientificOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatScientificOp : public ::mlir::Op<FormatScientificOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatScientificOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatScientificOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldWidth"), ::llvm::StringRef("fracDigits"), ::llvm::StringRef("isLeftAligned")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldWidthAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFracDigitsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFracDigitsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.exp");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::FloatType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::FloatType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getFieldWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fieldWidth);
  }

  ::std::optional<uint32_t> getFieldWidth();
  ::mlir::IntegerAttr getFracDigitsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().fracDigits);
  }

  uint32_t getFracDigits();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setFieldWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldWidth = attr;
  }

  void setFieldWidth(::std::optional<uint32_t> attrValue);
  void setFracDigitsAttr(::mlir::IntegerAttr attr) {
    getProperties().fracDigits = attr;
  }

  void setFracDigits(uint32_t attrValue);
  ::mlir::Attribute removeFieldWidthAttr() {
      auto attr = getProperties().fieldWidth;
      getProperties().fieldWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, ::mlir::IntegerAttr fracDigits);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, /*optional*/::mlir::IntegerAttr fieldWidth, uint32_t fracDigits = 6);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatScientificOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatScientificOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatScientificOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatScientificOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatStringConcatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatStringConcatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FormatStringConcatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.concat", odsAttrs.getContext());
  }

  FormatStringConcatOpGenericAdaptorBase(FormatStringConcatOp op);

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
class FormatStringConcatOpGenericAdaptor : public detail::FormatStringConcatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatStringConcatOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  FormatStringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatStringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatStringConcatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatStringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatStringConcatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatStringConcatOpGenericAdaptor(RangeT values, const FormatStringConcatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatStringConcatOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatStringConcatOp>>>
  FormatStringConcatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatStringConcatOpAdaptor : public FormatStringConcatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatStringConcatOpGenericAdaptor::FormatStringConcatOpGenericAdaptor;
  FormatStringConcatOpAdaptor(FormatStringConcatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatStringConcatOp : public ::mlir::Op<FormatStringConcatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatStringConcatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatStringConcatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.concat");
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static FormatStringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static FormatStringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(FormatStringConcatOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Returns true iff all of the input strings are primitive
  /// (i.e. non-concatenated) fragments or block arguments.
  bool isFlat() {
    return llvm::none_of(getInputs(), [](Value operand) {
      return !!operand.getDefiningOp<circt::sim::FormatStringConcatOp>();
    });
  };

  /// Attempts to flatten this operation's input strings as much as possible.
  ///
  /// The flattened values are pushed into the passed vector.
  /// If the concatenation is acyclic, the function will return 'success'
  /// and all the flattened values are guaranteed to _not_ be the result of
  /// a format string concatenation.
  /// If a cycle is encountered, the function will return 'failure'.
  /// On encountering a cycle, the result of the concat operation
  /// forming the cycle is pushed into the list of flattened values
  /// and flattening continues without recursing into the cycle.
  LogicalResult getFlattenedInputs(
    llvm::SmallVectorImpl<Value> &flatOperands);
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatStringConcatOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::FormatStringOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatStringOpGenericAdaptorBase {
public:
  struct Properties {
    using isLeftAlignedTy = ::mlir::BoolAttr;
    isLeftAlignedTy isLeftAligned;

    auto getIsLeftAligned() const {
      auto &propStorage = this->isLeftAligned;
      return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(propStorage);
    }
    void setIsLeftAligned(const ::mlir::BoolAttr &propValue) {
      this->isLeftAligned = propValue;
    }
    using paddingCharTy = ::mlir::IntegerAttr;
    paddingCharTy paddingChar;

    auto getPaddingChar() const {
      auto &propStorage = this->paddingChar;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPaddingChar(const ::mlir::IntegerAttr &propValue) {
      this->paddingChar = propValue;
    }
    using specifierWidthTy = ::mlir::IntegerAttr;
    specifierWidthTy specifierWidth;

    auto getSpecifierWidth() const {
      auto &propStorage = this->specifierWidth;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setSpecifierWidth(const ::mlir::IntegerAttr &propValue) {
      this->specifierWidth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.isLeftAligned == this->isLeftAligned &&
        rhs.paddingChar == this->paddingChar &&
        rhs.specifierWidth == this->specifierWidth &&
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
  FormatStringOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.fmt.string", odsAttrs.getContext());
  }

  FormatStringOpGenericAdaptorBase(FormatStringOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getIsLeftAlignedAttr();
  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr();
  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
    return attr;
  }

  ::std::optional<uint32_t> getSpecifierWidth();
};

} // namespace detail
template <typename RangeT>
class FormatStringOpGenericAdaptor : public detail::FormatStringOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatStringOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  FormatStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatStringOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatStringOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatStringOpGenericAdaptor(RangeT values, const FormatStringOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatStringOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatStringOp>>>
  FormatStringOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormatStringOpAdaptor : public FormatStringOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatStringOpGenericAdaptor::FormatStringOpGenericAdaptor;
  FormatStringOpAdaptor(FormatStringOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatStringOp : public ::mlir::Op<FormatStringOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::FormatStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::sim::ValueFormatter::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatStringOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatStringOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("isLeftAligned"), ::llvm::StringRef("paddingChar"), ::llvm::StringRef("specifierWidth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIsLeftAlignedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIsLeftAlignedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPaddingCharAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPaddingCharAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSpecifierWidthAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSpecifierWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.fmt.string");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::FormatStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSResults(0).begin());
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
  ::mlir::BoolAttr getIsLeftAlignedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::BoolAttr>(getProperties().isLeftAligned);
  }

  bool getIsLeftAligned();
  ::mlir::IntegerAttr getPaddingCharAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().paddingChar);
  }

  uint8_t getPaddingChar();
  ::mlir::IntegerAttr getSpecifierWidthAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().specifierWidth);
  }

  ::std::optional<uint32_t> getSpecifierWidth();
  void setIsLeftAlignedAttr(::mlir::BoolAttr attr) {
    getProperties().isLeftAligned = attr;
  }

  void setIsLeftAligned(bool attrValue);
  void setPaddingCharAttr(::mlir::IntegerAttr attr) {
    getProperties().paddingChar = attr;
  }

  void setPaddingChar(uint8_t attrValue);
  void setSpecifierWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().specifierWidth = attr;
  }

  void setSpecifierWidth(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeSpecifierWidthAttr() {
      auto attr = getProperties().specifierWidth;
      getProperties().specifierWidth = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::BoolAttr isLeftAligned, ::mlir::IntegerAttr paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, bool isLeftAligned, uint8_t paddingChar, /*optional*/::mlir::IntegerAttr specifierWidth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatStringOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::FormatStringOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::GetFileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetFileOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetFileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.get_file", odsAttrs.getContext());
  }

  GetFileOpGenericAdaptorBase(GetFileOp op);

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
class GetFileOpGenericAdaptor : public detail::GetFileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetFileOpGenericAdaptorBase;
  static constexpr int odsIndex_fileName = 0;
public:
  GetFileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetFileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GetFileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetFileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetFileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetFileOpGenericAdaptor(RangeT values, const GetFileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetFileOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetFileOp>>>
  GetFileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFileName() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetFileOpAdaptor : public GetFileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetFileOpGenericAdaptor::GetFileOpGenericAdaptor;
  GetFileOpAdaptor(GetFileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetFileOp : public ::mlir::Op<GetFileOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::OutputStreamType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetFileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetFileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fileName = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.get_file");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::FormatStringType> getFileName() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFileNameMutable() {
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

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value fileName);
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value fileName);
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value fileName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value fileName);
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value fileName);
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value fileName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value fileName);
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value fileName);
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value fileName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetFileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetFileOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::GetFileOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::IntToStringOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IntToStringOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  IntToStringOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.string.int_to_string", odsAttrs.getContext());
  }

  IntToStringOpGenericAdaptorBase(IntToStringOp op);

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
class IntToStringOpGenericAdaptor : public detail::IntToStringOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IntToStringOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  IntToStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IntToStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : IntToStringOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IntToStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IntToStringOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IntToStringOpGenericAdaptor(RangeT values, const IntToStringOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IntToStringOp, typename = std::enable_if_t<std::is_same_v<LateInst, IntToStringOp>>>
  IntToStringOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class IntToStringOpAdaptor : public IntToStringOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IntToStringOpGenericAdaptor::IntToStringOpGenericAdaptor;
  IntToStringOpAdaptor(IntToStringOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IntToStringOp : public ::mlir::Op<IntToStringOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::DynamicStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IntToStringOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IntToStringOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.string.int_to_string");
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

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IntToStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static IntToStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::IntToStringOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::PauseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PauseOpGenericAdaptorBase {
public:
  struct Properties {
    using verboseTy = ::mlir::BoolAttr;
    verboseTy verbose;

    auto getVerbose() const {
      auto &propStorage = this->verbose;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setVerbose(const ::mlir::BoolAttr &propValue) {
      this->verbose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.verbose == this->verbose &&
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
  PauseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.pause", odsAttrs.getContext());
  }

  PauseOpGenericAdaptorBase(PauseOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getVerboseAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
    return attr;
  }

  bool getVerbose();
};

} // namespace detail
template <typename RangeT>
class PauseOpGenericAdaptor : public detail::PauseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PauseOpGenericAdaptorBase;
public:
  PauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PauseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PauseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PauseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PauseOpGenericAdaptor(RangeT values, const PauseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PauseOp, typename = std::enable_if_t<std::is_same_v<LateInst, PauseOp>>>
  PauseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PauseOpAdaptor : public PauseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PauseOpGenericAdaptor::PauseOpGenericAdaptor;
  PauseOpAdaptor(PauseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PauseOp : public ::mlir::Op<PauseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PauseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PauseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("verbose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getVerboseAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getVerboseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.pause");
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
  ::mlir::BoolAttr getVerboseAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
  }

  bool getVerbose();
  void setVerboseAttr(::mlir::BoolAttr attr) {
    getProperties().verbose = attr;
  }

  void setVerbose(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::BoolAttr verbose);
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::BoolAttr verbose);
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr verbose);
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr verbose);
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool verbose);
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, bool verbose);
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, bool verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, bool verbose);
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, bool verbose);
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, bool verbose);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PauseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PauseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::PauseOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::PauseOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::PlusArgsTestOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PlusArgsTestOpGenericAdaptorBase {
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
  PlusArgsTestOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.plusargs.test", odsAttrs.getContext());
  }

  PlusArgsTestOpGenericAdaptorBase(PlusArgsTestOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class PlusArgsTestOpGenericAdaptor : public detail::PlusArgsTestOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PlusArgsTestOpGenericAdaptorBase;
public:
  PlusArgsTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PlusArgsTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PlusArgsTestOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PlusArgsTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PlusArgsTestOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PlusArgsTestOpGenericAdaptor(RangeT values, const PlusArgsTestOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PlusArgsTestOp, typename = std::enable_if_t<std::is_same_v<LateInst, PlusArgsTestOp>>>
  PlusArgsTestOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PlusArgsTestOpAdaptor : public PlusArgsTestOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PlusArgsTestOpGenericAdaptor::PlusArgsTestOpGenericAdaptor;
  PlusArgsTestOpAdaptor(PlusArgsTestOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PlusArgsTestOp : public ::mlir::Op<PlusArgsTestOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PlusArgsTestOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PlusArgsTestOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
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
    return ::llvm::StringLiteral("sim.plusargs.test");
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

  ::mlir::TypedValue<::mlir::IntegerType> getFound() {
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
  ::mlir::StringAttr getFormatStringAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().formatString);
  }

  ::llvm::StringRef getFormatString();
  void setFormatStringAttr(::mlir::StringAttr attr) {
    getProperties().formatString = attr;
  }

  void setFormatString(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type found, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type found, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type found, ::mlir::StringAttr formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type found, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type found, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type found, ::llvm::StringRef formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::PlusArgsTestOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::PlusArgsTestOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::PlusArgsValueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PlusArgsValueOpGenericAdaptorBase {
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
  PlusArgsValueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.plusargs.value", odsAttrs.getContext());
  }

  PlusArgsValueOpGenericAdaptorBase(PlusArgsValueOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class PlusArgsValueOpGenericAdaptor : public detail::PlusArgsValueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PlusArgsValueOpGenericAdaptorBase;
public:
  PlusArgsValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PlusArgsValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PlusArgsValueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PlusArgsValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PlusArgsValueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PlusArgsValueOpGenericAdaptor(RangeT values, const PlusArgsValueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PlusArgsValueOp, typename = std::enable_if_t<std::is_same_v<LateInst, PlusArgsValueOp>>>
  PlusArgsValueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PlusArgsValueOpAdaptor : public PlusArgsValueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PlusArgsValueOpGenericAdaptor::PlusArgsValueOpGenericAdaptor;
  PlusArgsValueOpAdaptor(PlusArgsValueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PlusArgsValueOp : public ::mlir::Op<PlusArgsValueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PlusArgsValueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PlusArgsValueOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
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

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.plusargs.value");
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

  ::mlir::TypedValue<::mlir::IntegerType> getFound() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getResult() {
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
  ::mlir::StringAttr getFormatStringAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().formatString);
  }

  ::llvm::StringRef getFormatString();
  void setFormatStringAttr(::mlir::StringAttr attr) {
    getProperties().formatString = attr;
  }

  void setFormatString(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type found, ::mlir::Type result, ::mlir::StringAttr formatString);
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type found, ::mlir::Type result, ::mlir::StringAttr formatString);
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type found, ::mlir::Type result, ::mlir::StringAttr formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type found, ::mlir::Type result, ::llvm::StringRef formatString);
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type found, ::mlir::Type result, ::llvm::StringRef formatString);
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type found, ::mlir::Type result, ::llvm::StringRef formatString);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PlusArgsValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::PlusArgsValueOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::PlusArgsValueOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::PrintFormattedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintFormattedOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PrintFormattedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.print", odsAttrs.getContext());
  }

  PrintFormattedOpGenericAdaptorBase(PrintFormattedOp op);

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
class PrintFormattedOpGenericAdaptor : public detail::PrintFormattedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintFormattedOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_condition = 2;
  static constexpr int odsIndex_stream = 3;
public:
  PrintFormattedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintFormattedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PrintFormattedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintFormattedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintFormattedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintFormattedOpGenericAdaptor(RangeT values, const PrintFormattedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintFormattedOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintFormattedOp>>>
  PrintFormattedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getCondition() {
    return (*getODSOperands(2).begin());
  }

  ValueT getStream() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintFormattedOpAdaptor : public PrintFormattedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintFormattedOpGenericAdaptor::PrintFormattedOpGenericAdaptor;
  PrintFormattedOpAdaptor(PrintFormattedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintFormattedOp : public ::mlir::Op<PrintFormattedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::NonProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintFormattedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintFormattedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_condition = 2;
  static constexpr int odsIndex_stream = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::FormatStringType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getStream() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::circt::sim::OutputStreamType>{} : ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getConditionMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getStreamMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clock, Value condition);
  static PrintFormattedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clock, Value condition);
  static PrintFormattedOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clock, Value condition);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static PrintFormattedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static PrintFormattedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static PrintFormattedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static PrintFormattedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clock, ::mlir::Value condition, /*optional*/::mlir::Value stream);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintFormattedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintFormattedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintFormattedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintFormattedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(PrintFormattedOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::PrintFormattedOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::PrintFormattedProcOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintFormattedProcOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PrintFormattedProcOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.proc.print", odsAttrs.getContext());
  }

  PrintFormattedProcOpGenericAdaptorBase(PrintFormattedProcOp op);

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
class PrintFormattedProcOpGenericAdaptor : public detail::PrintFormattedProcOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintFormattedProcOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_stream = 1;
public:
  PrintFormattedProcOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintFormattedProcOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PrintFormattedProcOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintFormattedProcOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintFormattedProcOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintFormattedProcOpGenericAdaptor(RangeT values, const PrintFormattedProcOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintFormattedProcOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintFormattedProcOp>>>
  PrintFormattedProcOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getStream() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintFormattedProcOpAdaptor : public PrintFormattedProcOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintFormattedProcOpGenericAdaptor::PrintFormattedProcOpGenericAdaptor;
  PrintFormattedProcOpAdaptor(PrintFormattedProcOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintFormattedProcOp : public ::mlir::Op<PrintFormattedProcOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintFormattedProcOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintFormattedProcOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_stream = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.proc.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::FormatStringType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::FormatStringType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getStream() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::circt::sim::OutputStreamType>{} : ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getStreamMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input);
  static PrintFormattedProcOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input);
  static PrintFormattedProcOp create(::mlir::ImplicitLocOpBuilder &builder, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static PrintFormattedProcOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static PrintFormattedProcOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static PrintFormattedProcOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static PrintFormattedProcOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::Value stream);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintFormattedProcOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintFormattedProcOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintFormattedProcOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintFormattedProcOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(PrintFormattedProcOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::PrintFormattedProcOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueCmpOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueCmpOpGenericAdaptorBase {
public:
  struct Properties {
    using predicateTy = circt::sim::QueueCmpPredicateAttr;
    predicateTy predicate;

    auto getPredicate() const {
      auto &propStorage = this->predicate;
      return ::llvm::cast<circt::sim::QueueCmpPredicateAttr>(propStorage);
    }
    void setPredicate(const circt::sim::QueueCmpPredicateAttr &propValue) {
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
  QueueCmpOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.cmp", odsAttrs.getContext());
  }

  QueueCmpOpGenericAdaptorBase(QueueCmpOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::sim::QueueCmpPredicateAttr getPredicateAttr() {
    auto attr = ::llvm::cast<circt::sim::QueueCmpPredicateAttr>(getProperties().predicate);
    return attr;
  }

  circt::sim::QueueCmpPredicate getPredicate();
};

} // namespace detail
template <typename RangeT>
class QueueCmpOpGenericAdaptor : public detail::QueueCmpOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueCmpOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  QueueCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueCmpOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueCmpOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueCmpOpGenericAdaptor(RangeT values, const QueueCmpOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueCmpOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueCmpOp>>>
  QueueCmpOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QueueCmpOpAdaptor : public QueueCmpOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueCmpOpGenericAdaptor::QueueCmpOpGenericAdaptor;
  QueueCmpOpAdaptor(QueueCmpOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueCmpOp : public ::mlir::Op<QueueCmpOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsCommutative, ::mlir::OpTrait::SameTypeOperands, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueCmpOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueCmpOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
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
    return ::llvm::StringLiteral("sim.queue.cmp");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(1).begin());
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
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  circt::sim::QueueCmpPredicateAttr getPredicateAttr() {
    return ::llvm::cast<circt::sim::QueueCmpPredicateAttr>(getProperties().predicate);
  }

  circt::sim::QueueCmpPredicate getPredicate();
  void setPredicateAttr(circt::sim::QueueCmpPredicateAttr attr) {
    getProperties().predicate = attr;
  }

  void setPredicate(circt::sim::QueueCmpPredicate attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::sim::QueueCmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueCmpOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::QueueCmpOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueConcatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueConcatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueConcatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.concat", odsAttrs.getContext());
  }

  QueueConcatOpGenericAdaptorBase(QueueConcatOp op);

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
class QueueConcatOpGenericAdaptor : public detail::QueueConcatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueConcatOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  QueueConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueConcatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueConcatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueConcatOpGenericAdaptor(RangeT values, const QueueConcatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueConcatOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueConcatOp>>>
  QueueConcatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QueueConcatOpAdaptor : public QueueConcatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueConcatOpGenericAdaptor::QueueConcatOpGenericAdaptor;
  QueueConcatOpAdaptor(QueueConcatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueConcatOp : public ::mlir::Op<QueueConcatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueConcatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueConcatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.concat");
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

  ::mlir::TypedValue<::circt::sim::QueueType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static QueueConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static QueueConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueConcatOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueDeleteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueDeleteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueDeleteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.delete", odsAttrs.getContext());
  }

  QueueDeleteOpGenericAdaptorBase(QueueDeleteOp op);

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
class QueueDeleteOpGenericAdaptor : public detail::QueueDeleteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueDeleteOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
public:
  QueueDeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueDeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueDeleteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueDeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueDeleteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueDeleteOpGenericAdaptor(RangeT values, const QueueDeleteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueDeleteOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueDeleteOp>>>
  QueueDeleteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
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
class QueueDeleteOpAdaptor : public QueueDeleteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueDeleteOpGenericAdaptor::QueueDeleteOpGenericAdaptor;
  QueueDeleteOpAdaptor(QueueDeleteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueDeleteOp : public ::mlir::Op<QueueDeleteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueDeleteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueDeleteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.delete");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueDeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueDeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueDeleteOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueEmptyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueEmptyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueEmptyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.empty", odsAttrs.getContext());
  }

  QueueEmptyOpGenericAdaptorBase(QueueEmptyOp op);

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
class QueueEmptyOpGenericAdaptor : public detail::QueueEmptyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueEmptyOpGenericAdaptorBase;
public:
  QueueEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueEmptyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueEmptyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueEmptyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueEmptyOpGenericAdaptor(RangeT values, const QueueEmptyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueEmptyOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueEmptyOp>>>
  QueueEmptyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QueueEmptyOpAdaptor : public QueueEmptyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueEmptyOpGenericAdaptor::QueueEmptyOpGenericAdaptor;
  QueueEmptyOpAdaptor(QueueEmptyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueEmptyOp : public ::mlir::Op<QueueEmptyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueEmptyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueEmptyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.empty");
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutqueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outqueue);
  static QueueEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outqueue);
  static QueueEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outqueue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static QueueEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static QueueEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueEmptyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueEmptyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueEmptyOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueFromArrayOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueFromArrayOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueFromArrayOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.from_array", odsAttrs.getContext());
  }

  QueueFromArrayOpGenericAdaptorBase(QueueFromArrayOp op);

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
class QueueFromArrayOpGenericAdaptor : public detail::QueueFromArrayOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueFromArrayOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  QueueFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueFromArrayOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueFromArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueFromArrayOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueFromArrayOpGenericAdaptor(RangeT values, const QueueFromArrayOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueFromArrayOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueFromArrayOp>>>
  QueueFromArrayOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QueueFromArrayOpAdaptor : public QueueFromArrayOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueFromArrayOpGenericAdaptor::QueueFromArrayOpGenericAdaptor;
  QueueFromArrayOpAdaptor(QueueFromArrayOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueFromArrayOp : public ::mlir::Op<QueueFromArrayOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueFromArrayOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueFromArrayOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.from_array");
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

  ::mlir::TypedValue<::circt::sim::QueueType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static QueueFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static QueueFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QueueFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QueueFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueFromArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueFromArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueFromArrayOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueGetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.get", odsAttrs.getContext());
  }

  QueueGetOpGenericAdaptorBase(QueueGetOp op);

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
class QueueGetOpGenericAdaptor : public detail::QueueGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueGetOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
public:
  QueueGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueGetOpGenericAdaptor(RangeT values, const QueueGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueGetOp>>>
  QueueGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
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
class QueueGetOpAdaptor : public QueueGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueGetOpGenericAdaptor::QueueGetOpGenericAdaptor;
  QueueGetOpAdaptor(QueueGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueGetOp : public ::mlir::Op<QueueGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueGetOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueInsertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueInsertOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueInsertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.insert", odsAttrs.getContext());
  }

  QueueInsertOpGenericAdaptorBase(QueueInsertOp op);

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
class QueueInsertOpGenericAdaptor : public detail::QueueInsertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueInsertOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_item = 2;
public:
  QueueInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueInsertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueInsertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueInsertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueInsertOpGenericAdaptor(RangeT values, const QueueInsertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueInsertOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueInsertOp>>>
  QueueInsertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  ValueT getItem() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueueInsertOpAdaptor : public QueueInsertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueInsertOpGenericAdaptor::QueueInsertOpGenericAdaptor;
  QueueInsertOpAdaptor(QueueInsertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueInsertOp : public ::mlir::Op<QueueInsertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueInsertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueInsertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_item = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.insert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getItem() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getItemMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueInsertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueInsertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueInsertOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueuePopBackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueuePopBackOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueuePopBackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.pop_back", odsAttrs.getContext());
  }

  QueuePopBackOpGenericAdaptorBase(QueuePopBackOp op);

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
class QueuePopBackOpGenericAdaptor : public detail::QueuePopBackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueuePopBackOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
public:
  QueuePopBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueuePopBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueuePopBackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueuePopBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueuePopBackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueuePopBackOpGenericAdaptor(RangeT values, const QueuePopBackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueuePopBackOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueuePopBackOp>>>
  QueuePopBackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueuePopBackOpAdaptor : public QueuePopBackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueuePopBackOpGenericAdaptor::QueuePopBackOpGenericAdaptor;
  QueuePopBackOpAdaptor(QueuePopBackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueuePopBackOp : public ::mlir::Op<QueuePopBackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueuePopBackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueuePopBackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.pop_back");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getPopped() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueuePopBackOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueuePopFrontOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueuePopFrontOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueuePopFrontOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.pop_front", odsAttrs.getContext());
  }

  QueuePopFrontOpGenericAdaptorBase(QueuePopFrontOp op);

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
class QueuePopFrontOpGenericAdaptor : public detail::QueuePopFrontOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueuePopFrontOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
public:
  QueuePopFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueuePopFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueuePopFrontOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueuePopFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueuePopFrontOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueuePopFrontOpGenericAdaptor(RangeT values, const QueuePopFrontOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueuePopFrontOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueuePopFrontOp>>>
  QueuePopFrontOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueuePopFrontOpAdaptor : public QueuePopFrontOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueuePopFrontOpGenericAdaptor::QueuePopFrontOpGenericAdaptor;
  QueuePopFrontOpAdaptor(QueuePopFrontOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueuePopFrontOp : public ::mlir::Op<QueuePopFrontOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueuePopFrontOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueuePopFrontOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.pop_front");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getPopped() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Type popped, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePopFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueuePopFrontOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueuePushBackOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueuePushBackOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueuePushBackOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.push_back", odsAttrs.getContext());
  }

  QueuePushBackOpGenericAdaptorBase(QueuePushBackOp op);

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
class QueuePushBackOpGenericAdaptor : public detail::QueuePushBackOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueuePushBackOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_element = 1;
public:
  QueuePushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueuePushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueuePushBackOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueuePushBackOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueuePushBackOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueuePushBackOpGenericAdaptor(RangeT values, const QueuePushBackOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueuePushBackOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueuePushBackOp>>>
  QueuePushBackOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getElement() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueuePushBackOpAdaptor : public QueuePushBackOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueuePushBackOpGenericAdaptor::QueuePushBackOpGenericAdaptor;
  QueuePushBackOpAdaptor(QueuePushBackOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueuePushBackOp : public ::mlir::Op<QueuePushBackOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueuePushBackOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueuePushBackOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_element = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.push_back");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getElement() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getElementMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushBackOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushBackOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueuePushBackOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueuePushFrontOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueuePushFrontOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueuePushFrontOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.push_front", odsAttrs.getContext());
  }

  QueuePushFrontOpGenericAdaptorBase(QueuePushFrontOp op);

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
class QueuePushFrontOpGenericAdaptor : public detail::QueuePushFrontOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueuePushFrontOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_element = 1;
public:
  QueuePushFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueuePushFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueuePushFrontOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueuePushFrontOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueuePushFrontOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueuePushFrontOpGenericAdaptor(RangeT values, const QueuePushFrontOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueuePushFrontOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueuePushFrontOp>>>
  QueuePushFrontOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getElement() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueuePushFrontOpAdaptor : public QueuePushFrontOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueuePushFrontOpGenericAdaptor::QueuePushFrontOpGenericAdaptor;
  QueuePushFrontOpAdaptor(QueuePushFrontOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueuePushFrontOp : public ::mlir::Op<QueuePushFrontOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueuePushFrontOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueuePushFrontOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_element = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.push_front");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getElement() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getElementMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value element);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushFrontOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueuePushFrontOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueuePushFrontOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueResizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueResizeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueResizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.resize", odsAttrs.getContext());
  }

  QueueResizeOpGenericAdaptorBase(QueueResizeOp op);

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
class QueueResizeOpGenericAdaptor : public detail::QueueResizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueResizeOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  QueueResizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueResizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueResizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueResizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueResizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueResizeOpGenericAdaptor(RangeT values, const QueueResizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueResizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueResizeOp>>>
  QueueResizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class QueueResizeOpAdaptor : public QueueResizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueResizeOpGenericAdaptor::QueueResizeOpGenericAdaptor;
  QueueResizeOpAdaptor(QueueResizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueResizeOp : public ::mlir::Op<QueueResizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueResizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueResizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.resize");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::sim::QueueType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static QueueResizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static QueueResizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QueueResizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static QueueResizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueResizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueResizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueResizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueResizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueResizeOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueSetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueSetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueSetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.set", odsAttrs.getContext());
  }

  QueueSetOpGenericAdaptorBase(QueueSetOp op);

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
class QueueSetOpGenericAdaptor : public detail::QueueSetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueSetOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_item = 2;
public:
  QueueSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueSetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueSetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueSetOpGenericAdaptor(RangeT values, const QueueSetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueSetOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueSetOp>>>
  QueueSetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  ValueT getItem() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueueSetOpAdaptor : public QueueSetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueSetOpGenericAdaptor::QueueSetOpGenericAdaptor;
  QueueSetOpAdaptor(QueueSetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueSetOp : public ::mlir::Op<QueueSetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueSetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueSetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_item = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.set");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getItem() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getItemMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getOutQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type outQueue, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value index, ::mlir::Value item);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueSetOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueSizeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueSizeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueSizeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.size", odsAttrs.getContext());
  }

  QueueSizeOpGenericAdaptorBase(QueueSizeOp op);

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
class QueueSizeOpGenericAdaptor : public detail::QueueSizeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueSizeOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
public:
  QueueSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueSizeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueSizeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueSizeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueSizeOpGenericAdaptor(RangeT values, const QueueSizeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueSizeOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueSizeOp>>>
  QueueSizeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueueSizeOpAdaptor : public QueueSizeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueSizeOpGenericAdaptor::QueueSizeOpGenericAdaptor;
  QueueSizeOpAdaptor(QueueSizeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueSizeOp : public ::mlir::Op<QueueSizeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueSizeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueSizeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.size");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSizeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSizeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueSizeOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::QueueSliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class QueueSliceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  QueueSliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.queue.slice", odsAttrs.getContext());
  }

  QueueSliceOpGenericAdaptorBase(QueueSliceOp op);

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
class QueueSliceOpGenericAdaptor : public detail::QueueSliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::QueueSliceOpGenericAdaptorBase;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_lowIdx = 1;
  static constexpr int odsIndex_highIdx = 2;
public:
  QueueSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  QueueSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : QueueSliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  QueueSliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : QueueSliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  QueueSliceOpGenericAdaptor(RangeT values, const QueueSliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = QueueSliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, QueueSliceOp>>>
  QueueSliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getQueue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getLowIdx() {
    return (*getODSOperands(1).begin());
  }

  ValueT getHighIdx() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class QueueSliceOpAdaptor : public QueueSliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using QueueSliceOpGenericAdaptor::QueueSliceOpGenericAdaptor;
  QueueSliceOpAdaptor(QueueSliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class QueueSliceOp : public ::mlir::Op<QueueSliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::QueueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = QueueSliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = QueueSliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_queue = 0;
  static constexpr int odsIndex_lowIdx = 1;
  static constexpr int odsIndex_highIdx = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.queue.slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::QueueType> getQueue() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLowIdx() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getHighIdx() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getQueueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getLowIdxMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getHighIdxMutable() {
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

  ::mlir::TypedValue<::circt::sim::QueueType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::QueueType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value queue, ::mlir::Value lowIdx, ::mlir::Value highIdx);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static QueueSliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueSliceOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::SVChannelToOutputStreamOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SVChannelToOutputStreamOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SVChannelToOutputStreamOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.sv.channel_to_output_stream", odsAttrs.getContext());
  }

  SVChannelToOutputStreamOpGenericAdaptorBase(SVChannelToOutputStreamOp op);

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
class SVChannelToOutputStreamOpGenericAdaptor : public detail::SVChannelToOutputStreamOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SVChannelToOutputStreamOpGenericAdaptorBase;
  static constexpr int odsIndex_channel = 0;
public:
  SVChannelToOutputStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SVChannelToOutputStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SVChannelToOutputStreamOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SVChannelToOutputStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SVChannelToOutputStreamOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SVChannelToOutputStreamOpGenericAdaptor(RangeT values, const SVChannelToOutputStreamOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SVChannelToOutputStreamOp, typename = std::enable_if_t<std::is_same_v<LateInst, SVChannelToOutputStreamOp>>>
  SVChannelToOutputStreamOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getChannel() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SVChannelToOutputStreamOpAdaptor : public SVChannelToOutputStreamOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SVChannelToOutputStreamOpGenericAdaptor::SVChannelToOutputStreamOpGenericAdaptor;
  SVChannelToOutputStreamOpAdaptor(SVChannelToOutputStreamOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SVChannelToOutputStreamOp : public ::mlir::Op<SVChannelToOutputStreamOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::OutputStreamType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SVChannelToOutputStreamOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SVChannelToOutputStreamOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_channel = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.sv.channel_to_output_stream");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getChannel() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getChannelMutable() {
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

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getStream() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type stream, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type stream, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type stream, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value channel);
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVChannelToOutputStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVChannelToOutputStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::SVChannelToOutputStreamOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::SVFCloseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SVFCloseOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SVFCloseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.sv.fclose", odsAttrs.getContext());
  }

  SVFCloseOpGenericAdaptorBase(SVFCloseOp op);

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
class SVFCloseOpGenericAdaptor : public detail::SVFCloseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SVFCloseOpGenericAdaptorBase;
  static constexpr int odsIndex_fd = 0;
public:
  SVFCloseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SVFCloseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SVFCloseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SVFCloseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SVFCloseOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SVFCloseOpGenericAdaptor(RangeT values, const SVFCloseOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SVFCloseOp, typename = std::enable_if_t<std::is_same_v<LateInst, SVFCloseOp>>>
  SVFCloseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFd() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SVFCloseOpAdaptor : public SVFCloseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SVFCloseOpGenericAdaptor::SVFCloseOpGenericAdaptor;
  SVFCloseOpAdaptor(SVFCloseOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SVFCloseOp : public ::mlir::Op<SVFCloseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SVFCloseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SVFCloseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fd = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.sv.fclose");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getFd() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFdMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value fd);
  static SVFCloseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value fd);
  static SVFCloseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value fd);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value fd);
  static SVFCloseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value fd);
  static SVFCloseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value fd);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFCloseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFCloseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFCloseOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFCloseOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::SVFCloseOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::SVFFlushAllOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SVFFlushAllOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SVFFlushAllOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.sv.fflush_all", odsAttrs.getContext());
  }

  SVFFlushAllOpGenericAdaptorBase(SVFFlushAllOp op);

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
class SVFFlushAllOpGenericAdaptor : public detail::SVFFlushAllOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SVFFlushAllOpGenericAdaptorBase;
public:
  SVFFlushAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SVFFlushAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SVFFlushAllOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SVFFlushAllOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SVFFlushAllOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SVFFlushAllOpGenericAdaptor(RangeT values, const SVFFlushAllOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SVFFlushAllOp, typename = std::enable_if_t<std::is_same_v<LateInst, SVFFlushAllOp>>>
  SVFFlushAllOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SVFFlushAllOpAdaptor : public SVFFlushAllOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SVFFlushAllOpGenericAdaptor::SVFFlushAllOpGenericAdaptor;
  SVFFlushAllOpAdaptor(SVFFlushAllOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SVFFlushAllOp : public ::mlir::Op<SVFFlushAllOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SVFFlushAllOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SVFFlushAllOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.sv.fflush_all");
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
  static SVFFlushAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static SVFFlushAllOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static SVFFlushAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static SVFFlushAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFFlushAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFFlushAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFFlushAllOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFFlushAllOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::SVFFlushAllOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::SVFOpenOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SVFOpenOpGenericAdaptorBase {
public:
  struct Properties {
    using modeTy = circt::sim::SVFOpenModeAttr;
    modeTy mode;

    auto getMode() const {
      auto &propStorage = this->mode;
      return ::llvm::dyn_cast_or_null<circt::sim::SVFOpenModeAttr>(propStorage);
    }
    void setMode(const circt::sim::SVFOpenModeAttr &propValue) {
      this->mode = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.mode == this->mode &&
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
  SVFOpenOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.sv.fopen", odsAttrs.getContext());
  }

  SVFOpenOpGenericAdaptorBase(SVFOpenOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::sim::SVFOpenModeAttr getModeAttr() {
    auto attr = ::llvm::dyn_cast_or_null<circt::sim::SVFOpenModeAttr>(getProperties().mode);
    return attr;
  }

  ::std::optional<circt::sim::SVFOpenMode> getMode();
};

} // namespace detail
template <typename RangeT>
class SVFOpenOpGenericAdaptor : public detail::SVFOpenOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SVFOpenOpGenericAdaptorBase;
  static constexpr int odsIndex_fileName = 0;
public:
  SVFOpenOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SVFOpenOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SVFOpenOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SVFOpenOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SVFOpenOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SVFOpenOpGenericAdaptor(RangeT values, const SVFOpenOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SVFOpenOp, typename = std::enable_if_t<std::is_same_v<LateInst, SVFOpenOp>>>
  SVFOpenOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFileName() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SVFOpenOpAdaptor : public SVFOpenOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SVFOpenOpGenericAdaptor::SVFOpenOpGenericAdaptor;
  SVFOpenOpAdaptor(SVFOpenOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SVFOpenOp : public ::mlir::Op<SVFOpenOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::ProceduralOp, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SVFOpenOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SVFOpenOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fileName = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("mode")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getModeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getModeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.sv.fopen");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getFileName() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFileNameMutable() {
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

  ::mlir::TypedValue<::mlir::IntegerType> getFd() {
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
  circt::sim::SVFOpenModeAttr getModeAttr() {
    return ::llvm::dyn_cast_or_null<circt::sim::SVFOpenModeAttr>(getProperties().mode);
  }

  ::std::optional<circt::sim::SVFOpenMode> getMode();
  void setModeAttr(circt::sim::SVFOpenModeAttr attr) {
    getProperties().mode = attr;
  }

  void setMode(::std::optional<circt::sim::SVFOpenMode> attrValue);
  ::mlir::Attribute removeModeAttr() {
      auto attr = getProperties().mode;
      getProperties().mode = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type fd, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type fd, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type fd, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value fileName, /*optional*/circt::sim::SVFOpenModeAttr mode);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFOpenOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SVFOpenOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::SVFOpenOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::SVFOpenOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StderrStreamOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StderrStreamOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StderrStreamOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.stderr_stream", odsAttrs.getContext());
  }

  StderrStreamOpGenericAdaptorBase(StderrStreamOp op);

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
class StderrStreamOpGenericAdaptor : public detail::StderrStreamOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StderrStreamOpGenericAdaptorBase;
public:
  StderrStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StderrStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StderrStreamOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StderrStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StderrStreamOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StderrStreamOpGenericAdaptor(RangeT values, const StderrStreamOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StderrStreamOp, typename = std::enable_if_t<std::is_same_v<LateInst, StderrStreamOp>>>
  StderrStreamOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StderrStreamOpAdaptor : public StderrStreamOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StderrStreamOpGenericAdaptor::StderrStreamOpGenericAdaptor;
  StderrStreamOpAdaptor(StderrStreamOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StderrStreamOp : public ::mlir::Op<StderrStreamOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::OutputStreamType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StderrStreamOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StderrStreamOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.stderr_stream");
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

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StderrStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StderrStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StderrStreamOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StdoutStreamOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StdoutStreamOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StdoutStreamOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.stdout_stream", odsAttrs.getContext());
  }

  StdoutStreamOpGenericAdaptorBase(StdoutStreamOp op);

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
class StdoutStreamOpGenericAdaptor : public detail::StdoutStreamOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StdoutStreamOpGenericAdaptorBase;
public:
  StdoutStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StdoutStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StdoutStreamOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StdoutStreamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StdoutStreamOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StdoutStreamOpGenericAdaptor(RangeT values, const StdoutStreamOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StdoutStreamOp, typename = std::enable_if_t<std::is_same_v<LateInst, StdoutStreamOp>>>
  StdoutStreamOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StdoutStreamOpAdaptor : public StdoutStreamOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StdoutStreamOpGenericAdaptor::StdoutStreamOpGenericAdaptor;
  StdoutStreamOpAdaptor(StdoutStreamOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StdoutStreamOp : public ::mlir::Op<StdoutStreamOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::OutputStreamType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StdoutStreamOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StdoutStreamOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.stdout_stream");
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

  ::mlir::TypedValue<::circt::sim::OutputStreamType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::OutputStreamType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result);
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result);
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StdoutStreamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StdoutStreamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StdoutStreamOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StringConcatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StringConcatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StringConcatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.string.concat", odsAttrs.getContext());
  }

  StringConcatOpGenericAdaptorBase(StringConcatOp op);

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
class StringConcatOpGenericAdaptor : public detail::StringConcatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StringConcatOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  StringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StringConcatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StringConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StringConcatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StringConcatOpGenericAdaptor(RangeT values, const StringConcatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StringConcatOp, typename = std::enable_if_t<std::is_same_v<LateInst, StringConcatOp>>>
  StringConcatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StringConcatOpAdaptor : public StringConcatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StringConcatOpGenericAdaptor::StringConcatOpGenericAdaptor;
  StringConcatOpAdaptor(StringConcatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StringConcatOp : public ::mlir::Op<StringConcatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::DynamicStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StringConcatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StringConcatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.string.concat");
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

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static StringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static StringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StringConcatOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StringConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StringConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using literalTy = ::mlir::StringAttr;
    literalTy literal;

    auto getLiteral() const {
      auto &propStorage = this->literal;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setLiteral(const ::mlir::StringAttr &propValue) {
      this->literal = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.literal == this->literal &&
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
  StringConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.string.literal", odsAttrs.getContext());
  }

  StringConstantOpGenericAdaptorBase(StringConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLiteralAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().literal);
    return attr;
  }

  ::llvm::StringRef getLiteral();
};

} // namespace detail
template <typename RangeT>
class StringConstantOpGenericAdaptor : public detail::StringConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StringConstantOpGenericAdaptorBase;
public:
  StringConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StringConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StringConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StringConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StringConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StringConstantOpGenericAdaptor(RangeT values, const StringConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StringConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, StringConstantOp>>>
  StringConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StringConstantOpAdaptor : public StringConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StringConstantOpGenericAdaptor::StringConstantOpGenericAdaptor;
  StringConstantOpAdaptor(StringConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StringConstantOp : public ::mlir::Op<StringConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::sim::DynamicStringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StringConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StringConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("literal")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLiteralAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLiteralAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.string.literal");
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

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getLiteralAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().literal);
  }

  ::llvm::StringRef getLiteral();
  void setLiteralAttr(::mlir::StringAttr attr) {
    getProperties().literal = attr;
  }

  void setLiteral(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef literal);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StringConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::StringConstantOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StringGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StringGetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StringGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.string.get", odsAttrs.getContext());
  }

  StringGetOpGenericAdaptorBase(StringGetOp op);

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
class StringGetOpGenericAdaptor : public detail::StringGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StringGetOpGenericAdaptorBase;
  static constexpr int odsIndex_str = 0;
  static constexpr int odsIndex_index = 1;
public:
  StringGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StringGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StringGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StringGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StringGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StringGetOpGenericAdaptor(RangeT values, const StringGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StringGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, StringGetOp>>>
  StringGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getStr() {
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
class StringGetOpAdaptor : public StringGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StringGetOpGenericAdaptor::StringGetOpGenericAdaptor;
  StringGetOpAdaptor(StringGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StringGetOp : public ::mlir::Op<StringGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StringGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StringGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_str = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.string.get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getStr() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getStrMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value str, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value str, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value str, ::mlir::Value index);
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value str, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StringGetOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::StringLengthOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StringLengthOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StringLengthOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.string.length", odsAttrs.getContext());
  }

  StringLengthOpGenericAdaptorBase(StringLengthOp op);

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
class StringLengthOpGenericAdaptor : public detail::StringLengthOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StringLengthOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  StringLengthOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StringLengthOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StringLengthOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StringLengthOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StringLengthOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StringLengthOpGenericAdaptor(RangeT values, const StringLengthOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StringLengthOp, typename = std::enable_if_t<std::is_same_v<LateInst, StringLengthOp>>>
  StringLengthOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StringLengthOpAdaptor : public StringLengthOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StringLengthOpGenericAdaptor::StringLengthOpGenericAdaptor;
  StringLengthOpAdaptor(StringLengthOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StringLengthOp : public ::mlir::Op<StringLengthOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StringLengthOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StringLengthOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.string.length");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::sim::DynamicStringType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::sim::DynamicStringType>>(*getODSOperands(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringLengthOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StringLengthOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::StringLengthOp)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::TerminateOp declarations
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
    using verboseTy = ::mlir::BoolAttr;
    verboseTy verbose;

    auto getVerbose() const {
      auto &propStorage = this->verbose;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setVerbose(const ::mlir::BoolAttr &propValue) {
      this->verbose = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.success == this->success &&
        rhs.verbose == this->verbose &&
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
      odsOpName.emplace("sim.terminate", odsAttrs.getContext());
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
  ::mlir::BoolAttr getVerboseAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
    return attr;
  }

  bool getVerbose();
};

} // namespace detail
template <typename RangeT>
class TerminateOpGenericAdaptor : public detail::TerminateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TerminateOpGenericAdaptorBase;
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
class TerminateOp : public ::mlir::Op<TerminateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::ProceduralOp> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TerminateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TerminateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("success"), ::llvm::StringRef("verbose")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSuccessAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSuccessAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getVerboseAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getVerboseAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.terminate");
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
  ::mlir::BoolAttr getSuccessAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().success);
  }

  bool getSuccess();
  ::mlir::BoolAttr getVerboseAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().verbose);
  }

  bool getVerbose();
  void setSuccessAttr(::mlir::BoolAttr attr) {
    getProperties().success = attr;
  }

  void setSuccess(bool attrValue);
  void setVerboseAttr(::mlir::BoolAttr attr) {
    getProperties().verbose = attr;
  }

  void setVerbose(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::BoolAttr success, ::mlir::BoolAttr verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool success, bool verbose);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, bool success, bool verbose);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, bool success, bool verbose);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, bool success, bool verbose);
  static TerminateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, bool success, bool verbose);
  static TerminateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, bool success, bool verbose);
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

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::TerminateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::detail::TerminateOpGenericAdaptorBase::Properties)

namespace circt::sim {


//===----------------------------------------------------------------------===//
// ::circt::sim::TriggeredOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TriggeredOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TriggeredOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("sim.triggered", odsAttrs.getContext());
  }

  TriggeredOpGenericAdaptorBase(TriggeredOp op);

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
class TriggeredOpGenericAdaptor : public detail::TriggeredOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TriggeredOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
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

  ValueT getClock() {
    return (*getODSOperands(0).begin());
  }

  ValueT getCondition() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
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
class TriggeredOp : public ::mlir::Op<TriggeredOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::circt::NonProceduralOp, ::circt::ProceduralRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TriggeredOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TriggeredOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_condition = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("sim.triggered");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCondition() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getConditionMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clock, Value condition = mlir::Value());
  static TriggeredOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clock, Value condition = mlir::Value());
  static TriggeredOp create(::mlir::ImplicitLocOpBuilder &builder, Value clock, Value condition = mlir::Value());
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clock, Value condition, llvm::function_ref<void()> bodyCtor);
  static TriggeredOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clock, Value condition, llvm::function_ref<void()> bodyCtor);
  static TriggeredOp create(::mlir::ImplicitLocOpBuilder &builder, Value clock, Value condition, llvm::function_ref<void()> bodyCtor);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clock, llvm::function_ref<void()> bodyCtor);
  static TriggeredOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clock, llvm::function_ref<void()> bodyCtor);
  static TriggeredOp create(::mlir::ImplicitLocOpBuilder &builder, Value clock, llvm::function_ref<void()> bodyCtor);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::TriggeredOp)


#endif // GET_OP_CLASSES

