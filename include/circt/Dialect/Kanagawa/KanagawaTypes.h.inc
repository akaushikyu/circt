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
namespace circt::kanagawa {

/// A reference to an Kanagawa scope. May be either a reference to a specific
/// scope (given a `$scopeName` argument) or an opaque reference.
class ScopeRefType;
/// A reference to an Kanagawa port.
class PortRefType;
namespace detail {

struct ScopeRefTypeStorage;

} // namespace detail
class ScopeRefType : public ::mlir::Type::TypeBase<ScopeRefType, ::mlir::Type, detail::ScopeRefTypeStorage> {
public:
  using Base::Base;
  bool isOpaque() {
    return !getScopeRef();
  }
  static constexpr ::llvm::StringLiteral name = "kanagawa.scoperef";
  static constexpr ::llvm::StringLiteral dialectName = "kanagawa";
  static ScopeRefType get(::mlir::MLIRContext *context, ::circt::hw::InnerRefAttr scopeRef);
  static ScopeRefType get(::mlir::MLIRContext *context);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"scoperef"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::hw::InnerRefAttr getScopeRef() const;
};
namespace detail {

struct PortRefTypeStorage;

} // namespace detail
class PortRefType : public ::mlir::Type::TypeBase<PortRefType, ::mlir::Type, detail::PortRefTypeStorage> {
public:
  using Base::Base;
  Type getPortType() {
    return getPortTypeAttr().getValue();
  }
  static constexpr ::llvm::StringLiteral name = "kanagawa.portref";
  static constexpr ::llvm::StringLiteral dialectName = "kanagawa";
  static PortRefType get(::mlir::MLIRContext *context, TypeAttr portTypeAttr, kanagawa::Direction direction);
  static PortRefType get(::mlir::MLIRContext *context, Type t, kanagawa::Direction d);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"portref"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  TypeAttr getPortTypeAttr() const;
  kanagawa::Direction getDirection() const;
};

} // namespace circt::kanagawa
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::ScopeRefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortRefType)

#endif // GET_TYPEDEF_CLASSES

