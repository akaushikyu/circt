/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::kanagawa {

/// Types and operations for Kanagawa dialect
/// The `kanagawa` dialect is intended to support porting and eventual open sourcing
/// of an internal hardware development language.
class KanagawaDialect : public ::mlir::Dialect {
  explicit KanagawaDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~KanagawaDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("kanagawa");
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

    void registerTypes();
    void registerAttributes();
  };

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::KanagawaDialect)
