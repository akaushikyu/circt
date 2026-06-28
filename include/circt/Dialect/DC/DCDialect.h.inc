/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: DC.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::dc {

/// Dynamic Control
/// This is the `dc` dialect, used to represent dynamic control constructs with
/// handshaking semantics.
class DCDialect : public ::mlir::Dialect {
  explicit DCDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~DCDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("dc");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

    void registerTypes();
  };

} // namespace circt::dc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::dc::DCDialect)
