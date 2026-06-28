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
namespace circt::ltl {

/// LTL sequence type
/// The `ltl.sequence` type represents a sequence of linear temporal logic, for
/// example, *"A is true two cycles after B is true"*.
/// 
/// Note that this type explicitly identifies a *sequence*. However, a boolean
/// value (`i1`) is also a valid sequence. Operations that accept a sequence as
/// an operand will use the `AnySequence` constraint, which also accepts `i1`.
class SequenceType;
/// LTL property type
/// The `ltl.property` type represents a verifiable property built from linear
/// temporal logic sequences and quantifiers, for example, *"if you see sequence
/// A, eventually you will see sequence B"*.
/// 
/// Note that this type explicitly identifies a *property*. However, a boolean
/// value (`i1`) or a sequence (`ltl.sequence`) is also a valid property.
/// Operations that accept a property as an operand will use the `AnyProperty`
/// constraint, which also accepts `ltl.sequence` and `i1`.
class PropertyType;
class SequenceType : public ::mlir::Type::TypeBase<SequenceType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ltl.sequence";
  static constexpr ::llvm::StringLiteral dialectName = "ltl";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sequence"};
  }

};
class PropertyType : public ::mlir::Type::TypeBase<PropertyType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ltl.property";
  static constexpr ::llvm::StringLiteral dialectName = "ltl";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"property"};
  }

};

} // namespace circt::ltl
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::ltl::SequenceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::ltl::PropertyType)

#endif // GET_TYPEDEF_CLASSES

