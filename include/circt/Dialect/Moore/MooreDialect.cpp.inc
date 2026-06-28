/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Moore.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::MooreDialect)
namespace circt::moore {


MooreDialect::MooreDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<MooreDialect>())
    
     {
  getContext()->loadDialect<hw::HWDialect>();
  initialize();
}

MooreDialect::~MooreDialect() = default;


} // namespace circt::moore
