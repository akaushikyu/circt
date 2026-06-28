/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Comb.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::comb {

/// Types and operations for comb dialect
/// This dialect defines the `comb` dialect, which is intended to be a generic
/// representation of combinational logic outside of a particular use-case.
class CombDialect : public ::mlir::Dialect {
  explicit CombDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~CombDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("comb");
  }

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;
};

} // namespace circt::comb
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::comb::CombDialect)
