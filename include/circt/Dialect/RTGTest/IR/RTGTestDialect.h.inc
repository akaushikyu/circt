/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTGTest.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtgtest {

/// types and operations for random test generation testing
/// This dialect defines the `rtgtest` dialect, which provides a set of 
/// operation definitions to test the RTG dialect.
class RTGTestDialect : public ::mlir::Dialect {
  explicit RTGTestDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~RTGTestDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("rtgtest");
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

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RTGTestDialect)
