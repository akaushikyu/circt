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
namespace circt::arc {

/// Metadata of a signal with trace instrumentation
class TraceTapAttr;
namespace detail {

struct TraceTapAttrStorage;

} // namespace detail
class TraceTapAttr : public ::mlir::Attribute::AttrBase<TraceTapAttr, ::mlir::Attribute, detail::TraceTapAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "arc.trace_tap";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static TraceTapAttr get(::mlir::MLIRContext *context, mlir::TypeAttr sigType, uint64_t stateOffset, mlir::ArrayAttr names);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"trace_tap"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::TypeAttr getSigType() const;
  uint64_t getStateOffset() const;
  mlir::ArrayAttr getNames() const;
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::TraceTapAttr)

#endif // GET_ATTRDEF_CLASSES

