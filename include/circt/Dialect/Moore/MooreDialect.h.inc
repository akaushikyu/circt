/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Moore.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::moore {

/// Types and operations for the Moore dialect
/// This dialect defines the `moore` dialect, which represents various
/// SystemVerilog-specific constructs without ambiguities and all types
/// resolved.
class MooreDialect : public ::mlir::Dialect {
  explicit MooreDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~MooreDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("moore");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;

    /// Register all Moore types.
    void registerTypes();
    /// Register all Moore attributes.
    void registerAttributes();

    /// Type parsing and printing.
    Type parseType(DialectAsmParser &parser) const override;
    void printType(Type, DialectAsmPrinter &) const override;
  };

} // namespace circt::moore
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::MooreDialect)
