/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SSP.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::ssp {

/// Static scheduling problem instances and solutions.
/// A dialect to abstractly represent instances and solutions of [static
/// scheduling problems](https://circt.llvm.org/docs/Scheduling/), intended as
/// an import/export format for testing, benchmarking, and rapid prototyping of
/// problem definitions and algorithm implementations. See the
/// [rationale](https://circt.llvm.org/docs/Dialects/SSP/RationaleSSP/) for more
/// information.
class SSPDialect : public ::mlir::Dialect {
  explicit SSPDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~SSPDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("ssp");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

    /// Register all SSP attributes.
    void registerAttributes();
  };

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::SSPDialect)
