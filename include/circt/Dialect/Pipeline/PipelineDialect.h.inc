/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Pipeline.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::pipeline {


class PipelineDialect : public ::mlir::Dialect {
  explicit PipelineDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~PipelineDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("pipeline");
  }
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::PipelineDialect)
