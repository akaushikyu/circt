/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWArith.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hwarith {

/// Types and operations for the HWArith dialect
/// This dialect defines the `HWArith` dialect, modeling bit-width aware
/// arithmetic operations.
class HWArithDialect : public ::mlir::Dialect {
  explicit HWArithDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~HWArithDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("hwarith");
  }
};

} // namespace circt::hwarith
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hwarith::HWArithDialect)
