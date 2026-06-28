/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LTL.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::ltl::LTLDialect)
namespace circt::ltl {


LTLDialect::LTLDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<LTLDialect>())
    
     {
  getContext()->loadDialect<hw::HWDialect>();
  getContext()->loadDialect<comb::CombDialect>();
  initialize();
}

LTLDialect::~LTLDialect() = default;


} // namespace circt::ltl
