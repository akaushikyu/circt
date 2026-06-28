/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Calyx.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::calyx {

/// Types and operations for the Calyx dialect
/// Calyx is an intermediate language and infrastructure for building
/// compilers that generate custom hardware accelerators. For more
/// information, visit the
/// [documentation](https://capra.cs.cornell.edu/calyx/).
class CalyxDialect : public ::mlir::Dialect {
  explicit CalyxDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~CalyxDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("calyx");
  }

    /// Register all Calyx types.
    void registerTypes();
    /// Register all Calyx attributes.
    void registerAttributes();
  };

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::CalyxDialect)
