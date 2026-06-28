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
namespace circt::moore {

/// An attribute containing a four-valued integer
class FVIntegerAttr;
namespace detail {

struct FVIntegerAttrStorage;

} // namespace detail
class FVIntegerAttr : public ::mlir::Attribute::AttrBase<FVIntegerAttr, ::mlir::Attribute, detail::FVIntegerAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.fvint";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static FVIntegerAttr get(::mlir::MLIRContext *context, FVInt value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"fvint"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  FVInt getValue() const;
};

} // namespace circt::moore
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::FVIntegerAttr)

#endif // GET_ATTRDEF_CLASSES

