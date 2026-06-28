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
namespace circt::llhd {

/// time type
/// Represents a simulation time value as a combination of a real time value in
/// seconds (or any smaller SI time unit), a delta value representing
/// infinitesimal time steps, and an epsilon value representing an absolute time
/// slot within a delta step (used to model SystemVerilog scheduling regions).
class TimeType;
/// a reference to a signal or variable
/// Represents a reference to a value. Signals return a reference to the
/// underlying value, which allows them to be probed or driven.
class RefType;
class TimeType : public ::mlir::Type::TypeBase<TimeType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llhd.time";
  static constexpr ::llvm::StringLiteral dialectName = "llhd";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"time"};
  }

};
namespace detail {

struct RefTypeStorage;

} // namespace detail
class RefType : public ::mlir::Type::TypeBase<RefType, ::mlir::Type, detail::RefTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llhd.ref";
  static constexpr ::llvm::StringLiteral dialectName = "llhd";
  static RefType get(::mlir::MLIRContext *context, Type nestedType);
  static RefType get(Type nestedType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ref"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getNestedType() const;
};

} // namespace circt::llhd
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::llhd::TimeType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::llhd::RefType)

#endif // GET_TYPEDEF_CLASSES

