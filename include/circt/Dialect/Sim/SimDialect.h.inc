/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Sim.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sim {

/// Types and operations for the `sim` dialect
/// The `sim` dialect is intented to model simulator-specific operations.
class SimDialect : public ::mlir::Dialect {
  explicit SimDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SimDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("sim");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;

    /// Register all Sim types.
    void registerTypes();
  };

} // namespace circt::sim
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sim::SimDialect)
