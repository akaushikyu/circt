/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HW.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

/// Types and operations for the hardware dialect
/// This dialect defines the `hw` dialect, which is intended to be a generic
/// representation of HW outside of a particular use-case.
class HWDialect : public ::mlir::Dialect {
  explicit HWDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~HWDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("hw");
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

    /// Register all HW types.
    void registerTypes();
    /// Register all HW attributes.
    void registerAttributes();

    Attribute parseAttribute(DialectAsmParser &p, Type type) const override;
    void printAttribute(Attribute attr, DialectAsmPrinter &p) const override;
  };

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HWDialect)
