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
namespace circt::kanagawa {

/// Used to describe a single step in a path
class PathStepAttr;
namespace detail {

struct PathStepAttrStorage;

} // namespace detail
class PathStepAttr : public ::mlir::Attribute::AttrBase<PathStepAttr, ::mlir::Attribute, detail::PathStepAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "kanagawa.step";
  static constexpr ::llvm::StringLiteral dialectName = "kanagawa";
  using Base::getChecked;
  static PathStepAttr get(::mlir::MLIRContext *context, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child);
  static PathStepAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"step"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PathDirection getDirection() const;
  ::mlir::Type getType() const;
  mlir::FlatSymbolRefAttr getChild() const;
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PathStepAttr)

#endif // GET_ATTRDEF_CLASSES

