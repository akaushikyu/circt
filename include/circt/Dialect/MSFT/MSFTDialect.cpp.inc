/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::MSFTDialect)
namespace circt::msft {


MSFTDialect::MSFTDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<MSFTDialect>())
    
     {
  getContext()->loadDialect<::circt::hw::HWDialect>();
  initialize();
}

MSFTDialect::~MSFTDialect() = default;


} // namespace circt::msft
