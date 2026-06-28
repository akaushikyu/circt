/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FIRRTL.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::FIRRTLDialect)
namespace circt::firrtl {


FIRRTLDialect::FIRRTLDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<FIRRTLDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::om::OMDialect>();
  getContext()->loadDialect<circt::sv::SVDialect>();
  initialize();
}

FIRRTLDialect::~FIRRTLDialect() = default;


} // namespace circt::firrtl
