/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Arc.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::ArcDialect)
namespace circt::arc {


ArcDialect::ArcDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<ArcDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

ArcDialect::~ArcDialect() = default;


} // namespace circt::arc
