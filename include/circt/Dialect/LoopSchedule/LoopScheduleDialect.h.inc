/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LoopSchedule.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::loopschedule {

/// Representation of scheduled loops
class LoopScheduleDialect : public ::mlir::Dialect {
  explicit LoopScheduleDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~LoopScheduleDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("loopschedule");
  }
};

} // namespace circt::loopschedule
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleDialect)
