/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FIRRTL.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::firrtl {

/// Types and operations for firrtl dialect
/// This dialect defines the `firrtl` dialect, which is used to lower from Chisel
/// code to Verilog.  For more information, see the [FIRRTL Spec
/// page](https://github.com/chipsalliance/firrtl-spec).
class FIRRTLDialect : public ::mlir::Dialect {
  explicit FIRRTLDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~FIRRTLDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("firrtl");
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

     ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;
     void printType(::mlir::Type type, ::mlir::DialectAsmPrinter &printer) const override;

    /// Register all FIRRTL types.
    void registerTypes();
    /// Register all attributes.
    void registerAttributes();
  };

} // namespace circt::firrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::FIRRTLDialect)
