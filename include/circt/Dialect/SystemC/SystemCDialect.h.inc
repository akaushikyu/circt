/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::systemc {

/// Types and operations for the SystemC dialect
/// This dialect defines the `systemc` dialect, which represents various
/// constructs of the SystemC library (IEEE 1666-2011) useful for emission.
class SystemCDialect : public ::mlir::Dialect {
  explicit SystemCDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SystemCDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("systemc");
  }

    /// Register all SystemC attributes.
    void registerAttributes();
    /// Register all SystemC types.
    void registerTypes();

    /// Type parsing and printing.
    mlir::Type parseType(mlir::DialectAsmParser &parser) const override;
    void printType(mlir::Type, mlir::DialectAsmPrinter &) const override;
  };

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SystemCDialect)
