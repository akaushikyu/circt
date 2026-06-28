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
namespace circt::dc {

/// A `!dc.token`-typed value represents a control value with handshake semantics.
class TokenType;
/// A `!dc.value`-typed value represents a value which is wrapped with
/// `!dc.token` semantics. This type is used to attach control semantics to
/// values. The inner value may be of any type.
class ValueType;
class TokenType : public ::mlir::Type::TypeBase<TokenType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dc.token";
  static constexpr ::llvm::StringLiteral dialectName = "dc";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"token"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};
namespace detail {

struct ValueTypeStorage;

} // namespace detail
class ValueType : public ::mlir::Type::TypeBase<ValueType, ::mlir::Type, detail::ValueTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dc.value";
  static constexpr ::llvm::StringLiteral dialectName = "dc";
  static ValueType get(::mlir::MLIRContext *context, Type innerType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"value"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  Type getInnerType() const;
};

} // namespace circt::dc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::dc::TokenType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::dc::ValueType)

#endif // GET_TYPEDEF_CLASSES

