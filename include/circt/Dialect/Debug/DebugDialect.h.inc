/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Debug.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::debug {

/// Facilities to represent debug information
class DebugDialect : public ::mlir::Dialect {
  explicit DebugDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~DebugDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("dbg");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

    void registerOps();
    void registerTypes();
  };

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::DebugDialect)
