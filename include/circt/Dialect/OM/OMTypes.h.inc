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
namespace circt::om {

/// A type that represents a reference to a Class.
class ClassType;
/// A type that represents a reference to a hardware entity.
class ReferenceType;
/// A type that represents a list.
class ListType;
/// A type that represents a reference to a flat symbol reference.
class SymbolRefType;
/// A type that represents an arbitrary width integer.
class OMIntegerType;
/// A type that represents a string.
class StringType;
/// A fragment of a path to a hardware component
class BasePathType;
/// A path to a hardware component
class PathType;
/// A frozen fragment of a path to a hardware component
class FrozenBasePathType;
/// A frozen path to a hardware component
class FrozenPathType;
/// A type that represents any valid OM type.
class AnyType;
namespace detail {

struct ClassTypeStorage;

} // namespace detail
class ClassType : public ::mlir::Type::TypeBase<ClassType, ::mlir::Type, detail::ClassTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.class.type";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static ClassType get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr className);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"class.type"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::FlatSymbolRefAttr getClassName() const;
};
class ReferenceType : public ::mlir::Type::TypeBase<ReferenceType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.ref";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ref"};
  }

};
namespace detail {

struct ListTypeStorage;

} // namespace detail
class ListType : public ::mlir::Type::TypeBase<ListType, ::mlir::Type, detail::ListTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.list";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static ListType get(::mlir::MLIRContext *context, mlir::Type elementType);
  static ListType get(::mlir::Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"list"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::Type getElementType() const;
};
class SymbolRefType : public ::mlir::Type::TypeBase<SymbolRefType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.sym_ref";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sym_ref"};
  }

};
class OMIntegerType : public ::mlir::Type::TypeBase<OMIntegerType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.integer";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"integer"};
  }

};
class StringType : public ::mlir::Type::TypeBase<StringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.string";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"string"};
  }

};
class BasePathType : public ::mlir::Type::TypeBase<BasePathType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.basepath";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"basepath"};
  }

};
class PathType : public ::mlir::Type::TypeBase<PathType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.path";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"path"};
  }

};
class FrozenBasePathType : public ::mlir::Type::TypeBase<FrozenBasePathType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.frozenbasepath";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"frozenbasepath"};
  }

};
class FrozenPathType : public ::mlir::Type::TypeBase<FrozenPathType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.frozenpath";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"frozenpath"};
  }

};
class AnyType : public ::mlir::Type::TypeBase<AnyType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "om.any";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"any"};
  }

};

} // namespace circt::om
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::ClassType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::ReferenceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::ListType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::SymbolRefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::OMIntegerType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::StringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::BasePathType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::PathType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::FrozenBasePathType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::FrozenPathType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::AnyType)

#endif // GET_TYPEDEF_CLASSES

