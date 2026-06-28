/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Verif.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::VerifDialect)
namespace circt::verif {


VerifDialect::VerifDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<VerifDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::ltl::LTLDialect>();
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

VerifDialect::~VerifDialect() = default;


} // namespace circt::verif
