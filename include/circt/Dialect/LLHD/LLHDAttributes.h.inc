/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::llhd {

/// time attribute
/// Represents a value of the LLHD time type.
/// 
/// Example: `#llhd.time<0ns, 1d, 0e>`
class TimeAttr;
namespace detail {

struct TimeAttrStorage;

} // namespace detail
class TimeAttr : public ::mlir::Attribute::AttrBase<TimeAttr, ::mlir::Attribute, detail::TimeAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "llhd.time";
  static constexpr ::llvm::StringLiteral dialectName = "llhd";
  using Base::getChecked;
  static TimeAttr get(::mlir::MLIRContext *context, uint64_t time, llvm::StringRef timeUnit, unsigned delta, unsigned epsilon);
  static TimeAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, uint64_t time, llvm::StringRef timeUnit, unsigned delta, unsigned epsilon);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, llhd::TimeType type, uint64_t time, ::llvm::StringRef timeUnit, unsigned delta, unsigned epsilon);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, llhd::TimeType type, uint64_t time, ::llvm::StringRef timeUnit, unsigned delta, unsigned epsilon);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"time"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  llhd::TimeType getType() const;
  uint64_t getTime() const;
  ::llvm::StringRef getTimeUnit() const;
  unsigned getDelta() const;
  unsigned getEpsilon() const;
};

} // namespace circt::llhd
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::llhd::TimeAttr)

#endif // GET_ATTRDEF_CLASSES

