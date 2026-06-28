/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Emit.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::emit {

/// Types and operations for the `emit` dialect
/// The `emit` dialect is intended to model the structure of the emitted RTL.
/// 
/// It organizes the files, file lists, directories and collateral.
class EmitDialect : public ::mlir::Dialect {
  explicit EmitDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~EmitDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("emit");
  }
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::EmitDialect)
