/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Pipeline.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::PipelineDialect)
namespace circt::pipeline {


PipelineDialect::PipelineDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<PipelineDialect>())
    
     {
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

PipelineDialect::~PipelineDialect() = default;


} // namespace circt::pipeline
