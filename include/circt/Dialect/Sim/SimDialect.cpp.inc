/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Sim.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::SimDialect)
namespace circt::sim {


SimDialect::SimDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<SimDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  getContext()->loadDialect<circt::seq::SeqDialect>();
  initialize();
}

SimDialect::~SimDialect() = default;


} // namespace circt::sim
