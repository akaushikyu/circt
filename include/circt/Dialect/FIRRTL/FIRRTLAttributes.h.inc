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
namespace circt::firrtl {

/// GrandCentral AugmentedBundleType
/// Used in the GrandCentralPass.
class AugmentedBundleTypeAttr;
/// GrandCentral AugmentedVectorType
/// Used in the GrandCentralPass.
class AugmentedVectorTypeAttr;
/// GrandCentral AugmentedGroundType
/// Used in the GrandCentralPass.
class AugmentedGroundTypeAttr;
/// Module or instance parameter definition
/// An attribute describing a module parameter, or instance parameter
/// specification.
class ParamDeclAttr;
/// Information about the initial state of a memory
/// This attribute captures information about the external initialization of a
/// memory.  This is the FIRRTL Dialect representation of both
/// "firrtl.annotations.LoadMemoryFromFile" and
/// "firrtl.annotations.MemoryFileInlineAnnotation".
class MemoryInitAttr;
/// A single field of a domain
class DomainFieldAttr;
/// name kind
class NameKindEnumAttr;
/// lowering convention
class ConventionAttr;
/// layer convention
class LayerConventionAttr;
/// layer specialization
class LayerSpecializationAttr;
/// read under write behavior
class RUWBehaviorAttr;
namespace detail {

struct AugmentedBundleTypeAttrStorage;

} // namespace detail
class AugmentedBundleTypeAttr : public ::mlir::Attribute::AttrBase<AugmentedBundleTypeAttr, ::mlir::Attribute, detail::AugmentedBundleTypeAttrStorage> {
public:
  using Base::Base;
  StringAttr getClass() { return getUnderlying().getAs<StringAttr>("class"); }

  IntegerAttr getID() { return getUnderlying().getAs<IntegerAttr>("id"); }

  ArrayAttr getElements() { return getUnderlying().getAs<ArrayAttr>("elements"); }

  StringAttr getDefName() { return getUnderlying().getAs<StringAttr>("defName"); }

    bool isRoot() { return getID() != nullptr; }
  static constexpr ::llvm::StringLiteral name = "firrtl.augmentedBundle";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static AugmentedBundleTypeAttr get(::mlir::MLIRContext *context, DictionaryAttr underlying);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"augmentedBundle"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  DictionaryAttr getUnderlying() const;
};
namespace detail {

struct AugmentedVectorTypeAttrStorage;

} // namespace detail
class AugmentedVectorTypeAttr : public ::mlir::Attribute::AttrBase<AugmentedVectorTypeAttr, ::mlir::Attribute, detail::AugmentedVectorTypeAttrStorage> {
public:
  using Base::Base;
  StringAttr getClass() { return getUnderlying().getAs<StringAttr>("class"); }

  ArrayAttr getElements() { return getUnderlying().getAs<ArrayAttr>("elements"); }
  static constexpr ::llvm::StringLiteral name = "firrtl.augmentedVector";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static AugmentedVectorTypeAttr get(::mlir::MLIRContext *context, DictionaryAttr underlying);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"augmentedVector"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  DictionaryAttr getUnderlying() const;
};
namespace detail {

struct AugmentedGroundTypeAttrStorage;

} // namespace detail
class AugmentedGroundTypeAttr : public ::mlir::Attribute::AttrBase<AugmentedGroundTypeAttr, ::mlir::Attribute, detail::AugmentedGroundTypeAttrStorage> {
public:
  using Base::Base;
  IntegerAttr getID() { return getUnderlying().getAs<IntegerAttr>("id"); }

  StringAttr getName() { return getUnderlying().getAs<StringAttr>("name"); }
  static constexpr ::llvm::StringLiteral name = "firrtl.augmentedGround";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static AugmentedGroundTypeAttr get(::mlir::MLIRContext *context, DictionaryAttr underlying);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"augmentedGround"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  DictionaryAttr getUnderlying() const;
};
namespace detail {

struct ParamDeclAttrStorage;

} // namespace detail
class ParamDeclAttr : public ::mlir::Attribute::AttrBase<ParamDeclAttr, ::mlir::Attribute, detail::ParamDeclAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static ParamDeclAttr getWithName(ParamDeclAttr param,
                                   ::mlir::StringAttr name) {
    return get(param.getContext(), name, param.getType(), param.getValue());
  }
  static constexpr ::llvm::StringLiteral name = "firrtl.param.decl";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ParamDeclAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value);
  static ParamDeclAttr get(::mlir::StringAttr name, ::mlir::Type type);
  static ParamDeclAttr get(::mlir::StringRef name, ::mlir::Type type);
  static ParamDeclAttr get(::mlir::StringAttr name, ::mlir::TypedAttr value);
  static ParamDeclAttr get(::mlir::StringRef name, ::mlir::TypedAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"param.decl"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getName() const;
  ::mlir::Type getType() const;
  ::mlir::Attribute getValue() const;
};
namespace detail {

struct MemoryInitAttrStorage;

} // namespace detail
class MemoryInitAttr : public ::mlir::Attribute::AttrBase<MemoryInitAttr, ::mlir::Attribute, detail::MemoryInitAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.meminit";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static MemoryInitAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr filename, bool isBinary, bool isInline);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"meminit"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getFilename() const;
  bool getIsBinary() const;
  bool getIsInline() const;
};
namespace detail {

struct DomainFieldAttrStorage;

} // namespace detail
class DomainFieldAttr : public ::mlir::Attribute::AttrBase<DomainFieldAttr, ::mlir::Attribute, detail::DomainFieldAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.domain.field";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static DomainFieldAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::circt::firrtl::PropertyType type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"domain.field"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getName() const;
  ::circt::firrtl::PropertyType getType() const;
};
namespace detail {

struct NameKindEnumAttrStorage;

} // namespace detail
class NameKindEnumAttr : public ::mlir::Attribute::AttrBase<NameKindEnumAttr, ::mlir::Attribute, detail::NameKindEnumAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.name_kind";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static NameKindEnumAttr get(::mlir::MLIRContext *context, ::circt::firrtl::NameKindEnum value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"name_kind"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::firrtl::NameKindEnum getValue() const;
};
namespace detail {

struct ConventionAttrStorage;

} // namespace detail
class ConventionAttr : public ::mlir::Attribute::AttrBase<ConventionAttr, ::mlir::Attribute, detail::ConventionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.convention";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ConventionAttr get(::mlir::MLIRContext *context, ::circt::firrtl::Convention value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"convention"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::firrtl::Convention getValue() const;
};
namespace detail {

struct LayerConventionAttrStorage;

} // namespace detail
class LayerConventionAttr : public ::mlir::Attribute::AttrBase<LayerConventionAttr, ::mlir::Attribute, detail::LayerConventionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.layerconvention";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static LayerConventionAttr get(::mlir::MLIRContext *context, ::circt::firrtl::LayerConvention value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"layerconvention"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::firrtl::LayerConvention getValue() const;
};
namespace detail {

struct LayerSpecializationAttrStorage;

} // namespace detail
class LayerSpecializationAttr : public ::mlir::Attribute::AttrBase<LayerSpecializationAttr, ::mlir::Attribute, detail::LayerSpecializationAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.layerspecialization";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static LayerSpecializationAttr get(::mlir::MLIRContext *context, ::circt::firrtl::LayerSpecialization value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"layerspecialization"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::firrtl::LayerSpecialization getValue() const;
};
namespace detail {

struct RUWBehaviorAttrStorage;

} // namespace detail
class RUWBehaviorAttr : public ::mlir::Attribute::AttrBase<RUWBehaviorAttr, ::mlir::Attribute, detail::RUWBehaviorAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.ruwbehavior";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static RUWBehaviorAttr get(::mlir::MLIRContext *context, ::circt::firrtl::RUWBehavior value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ruwbehavior"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::firrtl::RUWBehavior getValue() const;
};

} // namespace circt::firrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedBundleTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedVectorTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedGroundTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ParamDeclAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::MemoryInitAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::DomainFieldAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::NameKindEnumAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ConventionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::LayerConventionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::LayerSpecializationAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::RUWBehaviorAttr)

#endif // GET_ATTRDEF_CLASSES

