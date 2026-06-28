/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Comb.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::CombDialect)
namespace circt::comb {


CombDialect::CombDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<CombDialect>())
    
     {
  getContext()->loadDialect<hw::HWDialect>();
  initialize();
}

CombDialect::~CombDialect() = default;


} // namespace circt::comb
