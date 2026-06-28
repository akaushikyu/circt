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
namespace circt::rtgtest {

/// handle to a specific CPU
/// This type implements a specific context resource to test RTG operations
/// taking context resources as operands (such as `on_context`) and other things
/// requiring a concrete instance of a `ContextResourceTypeInterface`.
class CPUType;
/// represents an integer register
class IntegerRegisterType;
/// represents a floating-point register
class FloatRegisterType;
class CPUType : public ::mlir::Type::TypeBase<CPUType, ::mlir::Type, ::mlir::TypeStorage, ::circt::rtg::ContextResourceTypeInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtgtest.cpu";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cpu"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};
class IntegerRegisterType : public ::mlir::Type::TypeBase<IntegerRegisterType, ::mlir::Type, ::mlir::TypeStorage, ::circt::rtg::RegisterTypeInterface::Trait, ::circt::rtg::ValidationTypeInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtgtest.ireg";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ireg"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  static unsigned getRegisterClassSize();
  static ::circt::rtg::RegisterAttrInterface getRegisterAttrForClassIndex(::mlir::MLIRContext *ctx, unsigned index);
  bool isValidContentType(mlir::Type contentType) const;
  mlir::TypedAttr parseContentValue(mlir::StringRef valueString, mlir::Type contentType) const;
  std::string getIntrinsicLabel(mlir::Attribute value, mlir::StringRef id) const;
};
class FloatRegisterType : public ::mlir::Type::TypeBase<FloatRegisterType, ::mlir::Type, ::mlir::TypeStorage, ::circt::rtg::RegisterTypeInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtgtest.freg";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"freg"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  static unsigned getRegisterClassSize();
  static ::circt::rtg::RegisterAttrInterface getRegisterAttrForClassIndex(::mlir::MLIRContext *ctx, unsigned index);
};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::CPUType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::IntegerRegisterType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::FloatRegisterType)

#endif // GET_TYPEDEF_CLASSES

