/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OM.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::OMDialect)
namespace circt::om {


OMDialect::OMDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<OMDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  initialize();
}

OMDialect::~OMDialect() = default;


} // namespace circt::om
