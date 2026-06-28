/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::fsm {

/// An FSM instance type
/// Represents an FSM instance.
class InstanceType;
class InstanceType : public ::mlir::Type::TypeBase<InstanceType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "fsm.instance";
  static constexpr ::llvm::StringLiteral dialectName = "fsm";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"instance"};
  }

};

} // namespace circt::fsm
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::fsm::InstanceType)

#endif // GET_TYPEDEF_CLASSES

