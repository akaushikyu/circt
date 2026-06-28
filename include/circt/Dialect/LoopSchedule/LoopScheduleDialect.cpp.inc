/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LoopSchedule.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleDialect)
namespace circt::loopschedule {


LoopScheduleDialect::LoopScheduleDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<LoopScheduleDialect>())
    
     {
  
  initialize();
}

LoopScheduleDialect::~LoopScheduleDialect() = default;


} // namespace circt::loopschedule
