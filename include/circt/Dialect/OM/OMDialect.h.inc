/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OM.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::om {

/// The Object Model dialect captures design intent from various domains in an
/// object model.
/// For more information about the Object Model dialect, see the
/// [Object Model Dialect Rationale](./RationaleOM.md).
class OMDialect : public ::mlir::Dialect {
  explicit OMDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~OMDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("om");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

    /// Register all OM types.
    void registerTypes();

    /// Register all OM types.
    void registerAttributes();

    /// Materialize a constant value into an om.constant op.
    ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                           ::mlir::Attribute value,
                                           ::mlir::Type type,
                                           ::mlir::Location loc) override;
  };

} // namespace circt::om
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::OMDialect)
