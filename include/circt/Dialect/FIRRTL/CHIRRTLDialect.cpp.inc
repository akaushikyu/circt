/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: CHIRRTL.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::CHIRRTLDialect)
namespace circt::chirrtl {


CHIRRTLDialect::CHIRRTLDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<CHIRRTLDialect>())
    
     {
  getContext()->loadDialect<circt::firrtl::FIRRTLDialect>();
  initialize();
}

CHIRRTLDialect::~CHIRRTLDialect() = default;


} // namespace circt::chirrtl
