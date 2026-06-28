/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HLS.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::HLSDialect)
namespace circt::hls_analysis {


HLSDialect::HLSDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<HLSDialect>())
    
     {
  
  initialize();
}

HLSDialect::~HLSDialect() = default;


} // namespace circt::hls_analysis
