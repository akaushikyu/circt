/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Datapath.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::datapath::DatapathDialect)
namespace circt::datapath {


DatapathDialect::DatapathDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<DatapathDialect>())
    
     {
  getContext()->loadDialect<circt::comb::CombDialect>();
  initialize();
}

DatapathDialect::~DatapathDialect() = default;


} // namespace circt::datapath
