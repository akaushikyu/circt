/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Datapath.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::datapath {

/// Datapath Optimization
/// This dialect defines the `datapath` dialect, which is about the efficient 
/// construction of arithmetic circuits via low-level datapath optimizations.
class DatapathDialect : public ::mlir::Dialect {
  explicit DatapathDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~DatapathDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("datapath");
  }
};

} // namespace circt::datapath
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::datapath::DatapathDialect)
