/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::msft {

/// Microsoft internal support dialect
/// Umbrella dialect for everything needed to support Microsoft development
/// but not thoroughly discussed. Most (if not everything) in this dialect is
/// a candidate for generalization and re-homing.
class MSFTDialect : public ::mlir::Dialect {
  explicit MSFTDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~MSFTDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("msft");
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

    /// Register all MSFT attributes.
    void registerAttributes();
  };

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::MSFTDialect)
