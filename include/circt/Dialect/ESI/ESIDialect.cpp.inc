/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ESI.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ESIDialect)
namespace circt::esi {


ESIDialect::ESIDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<ESIDialect>())
    
     {
  getContext()->loadDialect<circt::seq::SeqDialect>();
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::sv::SVDialect>();
  getContext()->loadDialect<circt::comb::CombDialect>();
  initialize();
}

ESIDialect::~ESIDialect() = default;


} // namespace circt::esi
