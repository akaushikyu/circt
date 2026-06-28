/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SystemCDialect)
namespace circt::systemc {


SystemCDialect::SystemCDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<SystemCDialect>())
    
     {
  
  initialize();
}

SystemCDialect::~SystemCDialect() = default;


} // namespace circt::systemc
