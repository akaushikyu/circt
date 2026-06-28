/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::esi {

/// a runtime-variably sized list
/// In software, a chunk of memory with runtime-specified length. In hardware, a
/// stream of runtime-specified amount of data transmitted over many cycles in
/// compile-time specified specified windows (chunks).
class ListType;
/// An ESI-compatible channel port
/// An ESI port kind which models a latency-insensitive, unidirectional,
/// point-to-point data stream. Channels are typed (like all of ESI). Said
/// type can be any MLIR type, but must be lowered to something a backend
/// knows how to output (i.e. something emitVerilog knows about).
/// 
/// Parameters:
///   signaling: the style of the control signals (valid/ready vs FIFO).
///   dataDelay: the number of cycles data takes to arrive after the control
///   indicates a transaction has occured. For instance, on a FIFO without read
///   ahead, this would be 1. Defaults to 0.
/// 
/// Example:
/// 
/// ```mlir
/// hw.module.extern @Sender() -> (%x: !esi.channel<i1>)
/// hw.module @Reciever(%a: !esi.channel<hw.array<5xi16>>) { }
/// ```
class ChannelType;
/// a bundle of channels
/// A channel bundle (sometimes referred to as just "bundle") is a set of
/// channels of associated signals, along with per-channel names and directions.
/// The prototypical example for a bundle is a request-response channel pair.
/// 
/// The direction terminology is a bit confusing. Let us designate the module
/// which is outputting the bundle as the "sender" module and a module which has
/// a bundle as an input as the "receiver". The directions "from" and "to" are
/// from the senders perspective. So, the "to" direction means that channel is
/// transmitting messages from the sender to the receiver. Then, "from" means
/// that the sender is getting messages from the receiver (typically responses).
/// 
/// When requesting a bundle from a service, the service is always considered
/// the sender; so, "to" means the service is sending messages to the client and
/// "from" means the service is receiving messages from the client.
class ChannelBundleType;
/// a data window
/// A 'data window' allows designers to break up large messages into multiple
/// frames (aka flits) spread across multiple cycles. Windows are specified in
/// terms of a mapping of struct fields to frames. The width of a window is the
/// maximum frame size + the union tag (log2(#frames)).
/// 
/// A data window does NOT imply an ESI channel.
/// 
/// Current restrictions:
/// - A field may only appear once.
/// - Fields may only be re-ordered (wrt the original message) within a frame.
/// - Array fields whose array length is not evenly divisible by 'numItems' will
/// have an implicit frame inserted directly after containing the leftover array
/// items.
/// - A frame which contains an array with a 'numItems' specification CANNOT
/// contain another array with 'numItems' specified or a list field.
/// - Likewise, a frame which contains a list field CANNOT contain another list
/// field or an array with 'numItems' specified.
/// 
/// When either a list or an array with 'numItems' is specified in a frame, all
/// the other fields in the frame are assumed to be constant over the length of
/// the list/array transmission. This allows for efficient hardware
/// implementations where the constant fields can be held in registers while the
/// list/array segments stream through. In general, when a struct field appears
/// in multiple frames, it must be constant throughout the message transmission.
/// 
/// Typically lowered to a union of structs. There is a special case of one
/// frame with no name. In this case, it is lowered to just the struct itself.
class WindowType;
/// Declare a data window frame
/// A named list of fields which should appear in a given frame.
class WindowFrameType;
/// a field-in-frame specifier
/// Specify that a field should appear within the enclosing frame.
/// 
/// 'numItems' indicates how many items of the field should appear in the frame.
/// Only applicable to array or list fields. If not specified:
/// - For arrays, the entire array will appear in the frame.
/// - For lists, it is assumed to be 1.
/// 
/// For lists, there are two possible encodings:
///   - Parallel (default): a 'last' field to the struct to indicate that the
///   end of the list is this frame.  If 'numItems' is specified for a list, a
///   '<fieldName>_size' (representing the number of valid items in the array)
///   field will be added to the struct.  When `<fieldName>_size` is less than
///   'numItems', `last` MUST be true meaning that all frames must be full
///   except for the last one. This format matches typical on-chip hardware
///   streaming interfaces but is terribly inefficient for serial links.
///   - Serial (bulk transfer): in this encoding, there must be a 'header' frame
///   immediately preceding the frame which contains the list field. That frame
///   must include a special 'count' field which indicates how many items of the
///   list will be transmitted next. Once the number of items are transmitted
///   (transmitted frames == ceil(count/numItems)), the header is re-transmitted
///   to set up the next bulk transfer _for the same list_. If the transfer was
///   the last transfer, the header should set the count to zero. This method
///   allows for efficient transfers over serial links (no 'last' or '_size'
///   fields) without requiring knowledge of the total list size up front.
/// 
/// Note: list types with zero bitwidth are supported merely so one does not
/// have to special case elsewhere. It is not recommended to actually use them
/// as there is no special casing here either: in the serial encoding, N data
/// frames will still be transmitted!
class WindowFieldType;
/// any type
/// Used to state that any type is accepted in a service port declaration. The
/// specific type will be determined later in compilation.
class AnyType;
namespace detail {

struct ListTypeStorage;

} // namespace detail
class ListType : public ::mlir::Type::TypeBase<ListType, ::mlir::Type, detail::ListTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "esi.list";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static ListType get(::mlir::MLIRContext *context, Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"list"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getElementType() const;
};
namespace detail {

struct ChannelTypeStorage;

} // namespace detail
class ChannelType : public ::mlir::Type::TypeBase<ChannelType, ::mlir::Type, detail::ChannelTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  /// Consumers are ones which actually absorb tokens. Non-consumer ops
  /// include any snooping operations.
  static SmallVector<std::reference_wrapper<OpOperand>, 4> getConsumers(
    mlir::TypedValue<ChannelType>);
  static bool hasOneConsumer(mlir::TypedValue<ChannelType>);
  static bool hasNoConsumers(mlir::TypedValue<ChannelType>);
  static LogicalResult verifyChannel(mlir::TypedValue<ChannelType>);

  /// Get the single consumer of a channel. Returns nullptr if there are zero
  /// or more than one.
  static OpOperand* getSingleConsumer(mlir::TypedValue<ChannelType>);
  static constexpr ::llvm::StringLiteral name = "esi.channel";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static ChannelType get(::mlir::MLIRContext *context, Type inner, ::circt::esi::ChannelSignaling signaling, uint64_t dataDelay);
  static ChannelType get(::mlir::MLIRContext *context, Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"channel"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getInner() const;
  ::circt::esi::ChannelSignaling getSignaling() const;
  uint64_t getDataDelay() const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct ChannelBundleTypeStorage;

} // namespace detail
class ChannelBundleType : public ::mlir::Type::TypeBase<ChannelBundleType, ::mlir::Type, detail::ChannelBundleTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  // Get a channel bundle with the same types and names but the directions
  // reversed.
  ChannelBundleType getReversed() const;

  // Return the opposite direction.
  static ChannelDirection flip(ChannelDirection dir) {
    return dir == ChannelDirection::from
                             ? ChannelDirection::to
                             : ChannelDirection::from;
  }
  static constexpr ::llvm::StringLiteral name = "esi.bundle";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static ChannelBundleType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<BundledChannel> channels, ::mlir::UnitAttr resettable);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"bundle"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<BundledChannel> getChannels() const;
  ::mlir::UnitAttr getResettable() const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct WindowTypeStorage;

} // namespace detail
class WindowType : public ::mlir::Type::TypeBase<WindowType, ::mlir::Type, detail::WindowTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  /// Get the union which realizes this window during lowering.
  Type getLoweredType() const;
  static constexpr ::llvm::StringLiteral name = "esi.window";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  using Base::getChecked;
  static WindowType get(::mlir::MLIRContext *context, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames);
  static WindowType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"window"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  StringAttr getName() const;
  mlir::Type getInto() const;
  ::llvm::ArrayRef<WindowFrameType> getFrames() const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct WindowFrameTypeStorage;

} // namespace detail
class WindowFrameType : public ::mlir::Type::TypeBase<WindowFrameType, ::mlir::Type, detail::WindowFrameTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "esi.window.frame";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static WindowFrameType get(::mlir::MLIRContext *context, StringAttr name, ::llvm::ArrayRef<WindowFieldType> members);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"window.frame"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  StringAttr getName() const;
  ::llvm::ArrayRef<WindowFieldType> getMembers() const;
};
namespace detail {

struct WindowFieldTypeStorage;

} // namespace detail
class WindowFieldType : public ::mlir::Type::TypeBase<WindowFieldType, ::mlir::Type, detail::WindowFieldTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "esi.window.field";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  using Base::getChecked;
  static WindowFieldType get(::mlir::MLIRContext *context, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth);
  static WindowFieldType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"window.field"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  StringAttr getFieldName() const;
  uint64_t getNumItems() const;
  uint64_t getBulkCountWidth() const;
};
class AnyType : public ::mlir::Type::TypeBase<AnyType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static AnyType get(MLIRContext *context);
  static constexpr ::llvm::StringLiteral name = "esi.any";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"any"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ListType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ChannelType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ChannelBundleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WindowType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WindowFrameType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WindowFieldType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::AnyType)

#endif // GET_TYPEDEF_CLASSES

