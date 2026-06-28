/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FSM.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::fsm::FSMDialect)
namespace circt::fsm {


FSMDialect::FSMDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<FSMDialect>())
    
     {
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

FSMDialect::~FSMDialect() = default;


} // namespace circt::fsm
