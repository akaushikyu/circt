/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Handshake.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::handshake::HandshakeDialect)
namespace circt::handshake {


HandshakeDialect::HandshakeDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<HandshakeDialect>())
    
     {
  getContext()->loadDialect<circt::esi::ESIDialect>();
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

HandshakeDialect::~HandshakeDialect() = default;


} // namespace circt::handshake
