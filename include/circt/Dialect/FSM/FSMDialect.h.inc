/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FSM.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::fsm {

/// Types and operations for FSM dialect
/// This dialect defines the `fsm` dialect, which is intended to represent
/// finite-state machines.
class FSMDialect : public ::mlir::Dialect {
  explicit FSMDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~FSMDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("fsm");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;
};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::FSMDialect)
