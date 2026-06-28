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
namespace circt::debug {

/// debug scope
/// The result of a `dbg.scope` operation.
class ScopeType;
/// debug struct aggregate
/// The result of a `dbg.struct` operation.
class StructType;
/// debug array aggregate
/// The result of a `dbg.array` operation.
class ArrayType;
/// debug value annotated with source-language metadata
/// The result of a `dbg.value` operation.
class ValueType;
/// debug enum value
/// The result of a `dbg.enum` operation.
class EnumType;
class ScopeType : public ::mlir::Type::TypeBase<ScopeType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dbg.scope";
  static constexpr ::llvm::StringLiteral dialectName = "dbg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"scope"};
  }

};
class StructType : public ::mlir::Type::TypeBase<StructType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dbg.struct";
  static constexpr ::llvm::StringLiteral dialectName = "dbg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"struct"};
  }

};
class ArrayType : public ::mlir::Type::TypeBase<ArrayType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dbg.array";
  static constexpr ::llvm::StringLiteral dialectName = "dbg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"array"};
  }

};
class ValueType : public ::mlir::Type::TypeBase<ValueType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dbg.value";
  static constexpr ::llvm::StringLiteral dialectName = "dbg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"value"};
  }

};
class EnumType : public ::mlir::Type::TypeBase<EnumType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "dbg.enum";
  static constexpr ::llvm::StringLiteral dialectName = "dbg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"enum"};
  }

};

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ScopeType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::StructType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ValueType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::EnumType)

#endif // GET_TYPEDEF_CLASSES

