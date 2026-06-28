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
namespace circt::sv {

/// SystemVerilog unpacked 'open' array
/// This type represents unpacked 'open' array. Open array is a special type that can be
/// used as formal arguments of DPI import statements.
/// 
/// See SystemVerilog Spec 35.5.6.1.
class UnpackedOpenArrayType;
/// SystemVerilog interface type pointing to an InterfaceOp
/// A MLIR type for the SV dialect's `InterfaceOp` to allow instances in any
/// dialect with an open type system. Points at the InterfaceOp which defines
/// the SystemVerilog interface.
class InterfaceType;
/// SystemVerilog type pointing to an InterfaceModportOp
/// A MLIR type for the SV dialect's `InterfaceModportOp` to allow
/// interactions with any open type system dialect. Points at the
/// InterfaceModportOp which defines the SystemVerilog interface's modport.
class ModportType;
namespace detail {

struct UnpackedOpenArrayTypeStorage;

} // namespace detail
class UnpackedOpenArrayType : public ::mlir::Type::TypeBase<UnpackedOpenArrayType, ::mlir::Type, detail::UnpackedOpenArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.open_uarray";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static UnpackedOpenArrayType get(::mlir::MLIRContext *context, ::mlir::Type elementType);
  static UnpackedOpenArrayType get(Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"open_uarray"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
};
namespace detail {

struct InterfaceTypeStorage;

} // namespace detail
class InterfaceType : public ::mlir::Type::TypeBase<InterfaceType, ::mlir::Type, detail::InterfaceTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.interface";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static InterfaceType get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr interface);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"interface"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FlatSymbolRefAttr getInterface() const;
};
namespace detail {

struct ModportTypeStorage;

} // namespace detail
class ModportType : public ::mlir::Type::TypeBase<ModportType, ::mlir::Type, detail::ModportTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.modport";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static ModportType get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr modport);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"modport"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::SymbolRefAttr getModport() const;
};

} // namespace circt::sv
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::UnpackedOpenArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::InterfaceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::ModportType)

#endif // GET_TYPEDEF_CLASSES

