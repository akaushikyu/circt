/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SV.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sv {

/// Types and operations for SV dialect
/// This dialect defines the `sv` dialect, which represents various
/// SystemVerilog-specific constructs in an AST-like representation.
class SVDialect : public ::mlir::Dialect {
  explicit SVDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SVDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("sv");
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

    /// Register all SV types.
    void registerTypes();
    /// Register all attributes.
    void registerAttributes();
  };

} // namespace circt::sv
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::SVDialect)
