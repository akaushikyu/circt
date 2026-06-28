/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Emit.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::EmitDialect)
namespace circt::emit {


EmitDialect::EmitDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<EmitDialect>())
    
     {
  
  initialize();
}

EmitDialect::~EmitDialect() = default;


} // namespace circt::emit
