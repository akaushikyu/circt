/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTGTest.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RTGTestDialect)
namespace circt::rtgtest {


RTGTestDialect::RTGTestDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<RTGTestDialect>())
    
     {
  getContext()->loadDialect<::circt::rtg::RTGDialect>();
  initialize();
}

RTGTestDialect::~RTGTestDialect() = default;


} // namespace circt::rtgtest
