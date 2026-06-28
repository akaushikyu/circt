/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: CHIRRTL.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::chirrtl {

/// Types and operations for the chirrtl dialect
/// This dialect defines the `chirrtl` dialect, which contains high-level
/// memory defintions which can be lowered to FIRRTL.
class CHIRRTLDialect : public ::mlir::Dialect {
  explicit CHIRRTLDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~CHIRRTLDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("chirrtl");
  }

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;


    /// Register all FIRRTL types.
    void registerTypes();
  };

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::CHIRRTLDialect)
