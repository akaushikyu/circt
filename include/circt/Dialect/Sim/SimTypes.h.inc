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
namespace circt::sim {

/// Format string type
/// A format string type represents either a single formatting fragment or the
/// concatenation of an arbitrary but finite number of fragments.
/// A formatting fragment is either a static string literal or the association
/// of a dynamic hardware value with a format specifier.
class FormatStringType;
/// String type with variable length
/// The dynamic string type represents a string with a variable length that is
/// only known at runtime. The contents of the string are held as an array of
/// `i8` bytes. The interpretation of these bytes as a concrete character
/// encoding is undefined, but treating the bytes as a UTF-8 string is
/// recommended. A string's length must fit into an `i64`.
/// 
/// Even though practical lowerings of this type likely have to hold the string
/// contents in dynamically-allocated heap memory, *this type has value
/// semantics*. If the same string SSA value is passed to multiple users, any
/// mutation performed by one user is not visible to other users.
class DynamicStringType;
/// a queue type
/// An ordered container of elements with an optional upper bound
/// on the number of elements that it can hold. If this bound is 0, then the
/// queue has unrestricted capacity.
/// 
/// Even though practical lowerings of this type likely have to hold the queue
/// contents in dynamically-allocated heap memory, *this type has value
/// semantics*.
class QueueType;
/// DPI function type with first-class argument directions
/// Represents the full argument signature of a DPI-C function declaration.
/// Each argument has a name, type, and direction (`input`, `output`, `inout`,
/// `return`, or `ref`). Unlike `hw.modty`, this type preserves DPI-specific
/// semantics such as explicit return values and by-reference arguments.
class DPIFunctionType;
/// a type representing an output stream
/// Represents a simulation output stream resource.
/// This type models the existence of a stream resource at the Sim dialect level,
/// while leaving its concrete representation to the lowering backend. Backends may
/// realize this as a file descriptor, object handle, pointer, or any other target-
/// specific resource representation.
class OutputStreamType;
class FormatStringType : public ::mlir::Type::TypeBase<FormatStringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sim.fstring";
  static constexpr ::llvm::StringLiteral dialectName = "sim";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"fstring"};
  }

};
class DynamicStringType : public ::mlir::Type::TypeBase<DynamicStringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sim.dstring";
  static constexpr ::llvm::StringLiteral dialectName = "sim";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dstring"};
  }

};
namespace detail {

struct QueueTypeStorage;

} // namespace detail
class QueueType : public ::mlir::Type::TypeBase<QueueType, ::mlir::Type, detail::QueueTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sim.queue";
  static constexpr ::llvm::StringLiteral dialectName = "sim";
  static QueueType get(::mlir::MLIRContext *context, ::mlir::Type elementType, unsigned bound);
  static QueueType get(Type elementType, unsigned bound);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"queue"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
  unsigned getBound() const;
};
class DPIFunctionType : public ::mlir::Type::TypeBase<DPIFunctionType, ::mlir::Type, detail::DPIFunctionTypeStorage> {
public:
  using Base::Base;
  /// Get the number of arguments.
  size_t getNumArguments() const;

  /// Get the input arguments (input, inout, ref — call operands).
  llvm::SmallVector<DPIArgument> getInputArguments() const;

  /// Get the result arguments (output, inout, return — call results).
  llvm::SmallVector<DPIArgument> getResultArguments() const;

  /// Get the return argument, if any. Returns nullptr if none.
  const DPIArgument *getReturnArgument() const;

  /// Derive the MLIR FunctionType for the call shape.
  mlir::FunctionType getFunctionType() const;

  /// Verify structural constraints (return-is-last, at-most-one-return).
  /// On failure, emits diagnostics on the given op and returns failure.
  mlir::LogicalResult verify(llvm::function_ref<mlir::InFlightDiagnostic()> emitError) const;
  static constexpr ::llvm::StringLiteral name = "sim.dpi_functy";
  static constexpr ::llvm::StringLiteral dialectName = "sim";
  static DPIFunctionType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::sim::DPIArgument> arguments);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dpi_functy"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::sim::DPIArgument> getArguments() const;
};
class OutputStreamType : public ::mlir::Type::TypeBase<OutputStreamType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sim.output_stream";
  static constexpr ::llvm::StringLiteral dialectName = "sim";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"output_stream"};
  }

};

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::FormatStringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::DynamicStringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::QueueType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::DPIFunctionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::OutputStreamType)

#endif // GET_TYPEDEF_CLASSES

