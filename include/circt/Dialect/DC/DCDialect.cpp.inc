/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: DC.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::dc::DCDialect)
namespace circt::dc {


DCDialect::DCDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<DCDialect>())
    
     {
  getContext()->loadDialect<circt::esi::ESIDialect>();
  initialize();
}

DCDialect::~DCDialect() = default;


} // namespace circt::dc
