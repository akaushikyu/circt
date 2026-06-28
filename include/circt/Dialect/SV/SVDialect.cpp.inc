/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SV.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::SVDialect)
namespace circt::sv {


SVDialect::SVDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<SVDialect>())
    
     {
  getContext()->loadDialect<circt::comb::CombDialect>();
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::ltl::LTLDialect>();
  initialize();
}

SVDialect::~SVDialect() = default;


} // namespace circt::sv
