/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Debug.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::DebugDialect)
namespace circt::debug {


DebugDialect::DebugDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<DebugDialect>())
    
     {
  
  initialize();
}

DebugDialect::~DebugDialect() = default;


} // namespace circt::debug
