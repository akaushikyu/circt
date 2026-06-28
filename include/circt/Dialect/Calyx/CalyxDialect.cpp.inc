/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Calyx.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::CalyxDialect)
namespace circt::calyx {


CalyxDialect::CalyxDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<CalyxDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  initialize();
}

CalyxDialect::~CalyxDialect() = default;


} // namespace circt::calyx
