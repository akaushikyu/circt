/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::KanagawaDialect)
namespace circt::kanagawa {


KanagawaDialect::KanagawaDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<KanagawaDialect>())
    
     {
  getContext()->loadDialect<seq::SeqDialect>();
  getContext()->loadDialect<hw::HWDialect>();
  initialize();
}

KanagawaDialect::~KanagawaDialect() = default;


} // namespace circt::kanagawa
