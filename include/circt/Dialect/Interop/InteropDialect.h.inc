/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Interop.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::interop {

/// Provides interoperability between backends and tools
/// This dialect defines the `interop` dialect which defines operations and
/// interfaces necessary to provide interoperability between backends and
/// and external tools without the need of writing custom pairwise interop
/// solutions.
class InteropDialect : public ::mlir::Dialect {
  explicit InteropDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~InteropDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("interop");
  }
};

} // namespace circt::interop
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::interop::InteropDialect)
