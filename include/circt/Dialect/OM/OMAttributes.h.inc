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
namespace circt::om {

/// An attribute that wraps a #hw.innerNameRef with !om.ref type
class ReferenceAttr;
/// An attribute that wraps a FlatSymbolRefAttr type
class SymbolRefAttr;
/// An attribute that represents a list
class ListAttr;
/// An attribute that represents an instance path
class PathAttr;
/// An attribute that represents an arbitrary integer
class IntegerAttr;
namespace detail {

struct ReferenceAttrStorage;

} // namespace detail
class ReferenceAttr : public ::mlir::Attribute::AttrBase<ReferenceAttr, ::mlir::Attribute, detail::ReferenceAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  mlir::Type getType();
  static constexpr ::llvm::StringLiteral name = "om.ref";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static ReferenceAttr get(::mlir::MLIRContext *context, circt::hw::InnerRefAttr innerRef);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ref"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  circt::hw::InnerRefAttr getInnerRef() const;
};
namespace detail {

struct SymbolRefAttrStorage;

} // namespace detail
class SymbolRefAttr : public ::mlir::Attribute::AttrBase<SymbolRefAttr, ::mlir::Attribute, detail::SymbolRefAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  mlir::Type getType();
  static constexpr ::llvm::StringLiteral name = "om.sym_ref";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  static SymbolRefAttr get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr ref);
  static SymbolRefAttr get(::mlir::Operation *op);
  static SymbolRefAttr get(::mlir::StringAttr symName);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sym_ref"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::FlatSymbolRefAttr getRef() const;
};
namespace detail {

struct ListAttrStorage;

} // namespace detail
class ListAttr : public ::mlir::Attribute::AttrBase<ListAttr, ::mlir::Attribute, detail::ListAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  mlir::Type getType();
  static constexpr ::llvm::StringLiteral name = "om.list";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  using Base::getChecked;
  static ListAttr get(::mlir::MLIRContext *context, mlir::Type elementType, mlir::ArrayAttr elements);
  static ListAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::Type elementType, mlir::ArrayAttr elements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::Type elementType, mlir::ArrayAttr elements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::Type elementType, mlir::ArrayAttr elements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"list"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::Type getElementType() const;
  mlir::ArrayAttr getElements() const;
};
namespace detail {

struct PathAttrStorage;

} // namespace detail
class PathAttr : public ::mlir::Attribute::AttrBase<PathAttr, ::mlir::Attribute, detail::PathAttrStorage> {
public:
  using Base::Base;
  auto begin() const { return getPath().begin(); }
  auto end() const { return getPath().end(); }
  static constexpr ::llvm::StringLiteral name = "om.path";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  using Base::getChecked;
  static PathAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::om::PathElement> path);
  static PathAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::om::PathElement> path);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::om::PathElement> path);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::om::PathElement> path);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"path"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::om::PathElement> getPath() const;
};
namespace detail {

struct IntegerAttrStorage;

} // namespace detail
class IntegerAttr : public ::mlir::Attribute::AttrBase<IntegerAttr, ::mlir::Attribute, detail::IntegerAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  mlir::Type getType();
  static constexpr ::llvm::StringLiteral name = "om.integer";
  static constexpr ::llvm::StringLiteral dialectName = "om";
  using Base::getChecked;
  static IntegerAttr get(::mlir::MLIRContext *context, mlir::IntegerAttr value);
  static IntegerAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::IntegerAttr value);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::IntegerAttr value);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::IntegerAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"integer"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::IntegerAttr getValue() const;
};

} // namespace circt::om
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::ReferenceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::SymbolRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::ListAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::PathAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::om::IntegerAttr)

#endif // GET_ATTRDEF_CLASSES

