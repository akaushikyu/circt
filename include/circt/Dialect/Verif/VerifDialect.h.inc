/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Verif.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::verif {

/// Verification constructs and utilities.
class VerifDialect : public ::mlir::Dialect {
  explicit VerifDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~VerifDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("verif");
  }

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::VerifDialect)
