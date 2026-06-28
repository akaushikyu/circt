/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWArith.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hwarith::HWArithDialect)
namespace circt::hwarith {


HWArithDialect::HWArithDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<HWArithDialect>())
    
     {
  
  initialize();
}

HWArithDialect::~HWArithDialect() = default;


} // namespace circt::hwarith
