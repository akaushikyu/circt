/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTG.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// types and operations for random test generation
/// This dialect defines the `rtg` dialect, which is intended to encode
/// constraints and randomization constructs for random test generation. Such a
/// test can, for example, be a sequence of ISA instructions to test a CPU core.
class RTGDialect : public ::mlir::Dialect {
  explicit RTGDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~RTGDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("rtg");
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

  /// Materialize a single constant operation from a given attribute value with
  /// the desired resultant type.
  ::mlir::Operation *materializeConstant(::mlir::OpBuilder &builder,
                                         ::mlir::Attribute value,
                                         ::mlir::Type type,
                                         ::mlir::Location loc) override;

    void registerAttributes();
    void registerTypes();
  };

} // namespace circt::rtg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::RTGDialect)
