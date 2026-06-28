/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LLHD.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::llhd::LLHDDialect)
namespace circt::llhd {


LLHDDialect::LLHDDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<LLHDDialect>())
    
     {
  getContext()->loadDialect<circt::hw::HWDialect>();
  initialize();
}

LLHDDialect::~LLHDDialect() = default;


} // namespace circt::llhd
