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
namespace circt::handshake {

/// BufferOp seq or fifo
class BufferTypeEnumAttr;
namespace detail {

struct BufferTypeEnumAttrStorage;

} // namespace detail
class BufferTypeEnumAttr : public ::mlir::Attribute::AttrBase<BufferTypeEnumAttr, ::mlir::Attribute, detail::BufferTypeEnumAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "handshake.buffer_type_enum";
  static constexpr ::llvm::StringLiteral dialectName = "handshake";
  static BufferTypeEnumAttr get(::mlir::MLIRContext *context, ::BufferTypeEnum value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"buffer_type_enum"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::BufferTypeEnum getValue() const;
};

} // namespace circt::handshake
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::handshake::BufferTypeEnumAttr)

#endif // GET_ATTRDEF_CLASSES

