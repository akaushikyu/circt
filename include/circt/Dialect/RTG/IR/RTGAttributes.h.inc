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
namespace circt::rtg {

/// the default context of its type
/// A target must specify a default value for each context resource type it
/// uses. The tests matched against that target then start in that context
/// initially and 'on_context' operations can be used to switch to another
/// context within a test. Essentially, this attribute is used within tests to
/// refer to the default context set in the target.
class DefaultContextAttr;
/// any single context of its type
/// This attribute can be used to refer to any context of its type.
class AnyContextAttr;
/// an unordered set of elements
class SetAttr;
/// a map from keys to values
class MapAttr;
/// a tuple
class TupleAttr;
/// an ISA immediate value
/// This represents an ISA immediate of arbitrary but fixed bit-width. The type
/// of this attribute must always be an `ImmediateType` of matching bit-width.
class ImmediateAttr;
/// an allowed register configuration for a virtual register
class VirtualRegisterConfigAttr;
/// an assembly label
class LabelAttr;
namespace detail {

struct DefaultContextAttrStorage;

} // namespace detail
class DefaultContextAttr : public ::mlir::Attribute::AttrBase<DefaultContextAttr, ::mlir::Attribute, detail::DefaultContextAttrStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::ContextResourceAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.default";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static DefaultContextAttr get(::mlir::MLIRContext *context, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"default"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getType() const;
};
namespace detail {

struct AnyContextAttrStorage;

} // namespace detail
class AnyContextAttr : public ::mlir::Attribute::AttrBase<AnyContextAttr, ::mlir::Attribute, detail::AnyContextAttrStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::ContextResourceAttrInterface::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.any_context";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static AnyContextAttr get(::mlir::MLIRContext *context, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"any_context"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getType() const;
};
namespace detail {

struct SetAttrStorage;

} // namespace detail
class SetAttr : public ::mlir::Attribute::AttrBase<SetAttr, ::mlir::Attribute, detail::SetAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.set";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  using Base::getChecked;
  static SetAttr get(::mlir::MLIRContext *context, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements);
  static SetAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements);
  static SetAttr get(rtg::SetType type, const ::llvm::DenseSet<::mlir::TypedAttr> *elements);
  static SetAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::SetType type, const ::llvm::DenseSet<::mlir::TypedAttr> *elements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"set"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  rtg::SetType getType() const;
  const ::llvm::DenseSet<TypedAttr> *getElements() const;
};
namespace detail {

struct MapAttrStorage;

} // namespace detail
class MapAttr : public ::mlir::Attribute::AttrBase<MapAttr, ::mlir::Attribute, detail::MapAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.map";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  using Base::getChecked;
  static MapAttr get(::mlir::MLIRContext *context, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries);
  static MapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries);
  static MapAttr get(rtg::MapType type, const ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> *entries);
  static MapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type, const ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> *entries);
  static MapAttr get(rtg::MapType type);
  static MapAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"map"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  rtg::MapType getType() const;
  const ::llvm::DenseMap<TypedAttr, TypedAttr> *getEntries() const;
};
namespace detail {

struct TupleAttrStorage;

} // namespace detail
class TupleAttr : public ::mlir::Attribute::AttrBase<TupleAttr, ::mlir::Attribute, detail::TupleAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.tuple";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static TupleAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::mlir::TypedAttr> elements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tuple"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::mlir::TypedAttr> getElements() const;
  ::mlir::Type getType() const;
};
class ImmediateAttr : public ::mlir::Attribute::AttrBase<ImmediateAttr, ::mlir::Attribute, detail::ImmediateAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.immediate";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static ImmediateAttr get(::mlir::MLIRContext *context, llvm::APInt value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.immediate"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  llvm::APInt getValue() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct VirtualRegisterConfigAttrStorage;

} // namespace detail
class VirtualRegisterConfigAttr : public ::mlir::Attribute::AttrBase<VirtualRegisterConfigAttr, ::mlir::Attribute, detail::VirtualRegisterConfigAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.virtual_register_config";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  using Base::getChecked;
  static VirtualRegisterConfigAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs);
  static VirtualRegisterConfigAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"virtual_register_config"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<rtg::RegisterAttrInterface> getAllowedRegs() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct LabelAttrStorage;

} // namespace detail
class LabelAttr : public ::mlir::Attribute::AttrBase<LabelAttr, ::mlir::Attribute, detail::LabelAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.label";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static LabelAttr get(::mlir::MLIRContext *context, ::llvm::StringRef name);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.label"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::StringRef getName() const;
  ::mlir::Type getType() const;
};

} // namespace circt::rtg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::DefaultContextAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::AnyContextAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::SetAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::MapAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::TupleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::ImmediateAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::VirtualRegisterConfigAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::LabelAttr)

#endif // GET_ATTRDEF_CLASSES

