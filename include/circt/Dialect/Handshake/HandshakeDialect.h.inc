/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Handshake.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::handshake {

/// Types and operations for the handshake dialect
/// This dialect defined the `handshake` dialect, modeling dataflow circuits.
/// Handshake/dataflow IR is describes independent, unsynchronized processes
/// communicating data through First-in First-out (FIFO) communication channels.
class HandshakeDialect : public ::mlir::Dialect {
  explicit HandshakeDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~HandshakeDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("handshake");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::HandshakeDialect)
