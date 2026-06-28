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
namespace circt::sv {

/// Macro identifier
/// Represents a reference to a macro identifier.
class MacroIdentAttr;
/// a Verilog Attribute
/// This attribute is used to encode a Verilog _attribute_.  A Verilog attribute
/// (not to be confused with an LLVM or MLIR attribute) is a syntactic mechanism
/// for adding metadata to specific declarations, statements, and expressions in
/// the Verilog language.  _There are no "standard" attributes_.  Specific tools
/// define and handle their own attributes.
/// 
/// Verilog attributes have a mandatory name and an optional constant
/// expression.  This is encoded as a key (name) value (expression) pair.
/// Multiple attributes may be specified, either with multiple separate
/// attributes or by comman-separating name--expression pairs.
/// 
/// Currently, SV attributes don't block most optimizations; therefore, users should
/// not expect that sv attributes always appear in the output verilog.
/// However, we must block optimizations that updating ops in-place
/// since it is mostly invalid to transfer SV attributes one to another.
/// 
/// For more information, refer to Section 5.12 of the SystemVerilog (1800-2017)
/// specification.
class SVAttributeAttr;
/// Represents a case expression pattern
class CaseExprPatternAttr;
/// validation qualifier type
class ValidationQualifierTypeEnumAttr;
/// Double-quoted local include, or angle bracketed system include
class IncludeStyleAttr;
/// Defines direction in a modport
class ModportDirectionAttr;
class ModportStructAttr;
namespace detail {

struct MacroIdentAttrStorage;

} // namespace detail
class MacroIdentAttr : public ::mlir::Attribute::AttrBase<MacroIdentAttr, ::mlir::Attribute, detail::MacroIdentAttrStorage> {
public:
  using Base::Base;
  ::llvm::StringRef getName() { return getIdent().getValue(); }
  static constexpr ::llvm::StringLiteral name = "sv.macro.ident";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static MacroIdentAttr get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr ident);
  static MacroIdentAttr get(::mlir::MLIRContext *context, ::llvm::StringRef ident);
  static MacroIdentAttr get(::mlir::StringAttr ident);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"macro.ident"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FlatSymbolRefAttr getIdent() const;
};
namespace detail {

struct SVAttributeAttrStorage;

} // namespace detail
class SVAttributeAttr : public ::mlir::Attribute::AttrBase<SVAttributeAttr, ::mlir::Attribute, detail::SVAttributeAttrStorage> {
public:
  using Base::Base;
  static inline llvm::StringRef
      getSVAttributesAttrName() { return "sv.attributes"; }
  static constexpr ::llvm::StringLiteral name = "sv.attribute";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static SVAttributeAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::StringAttr expression, mlir::BoolAttr emitAsComment);
  static SVAttributeAttr get(::mlir::MLIRContext *context, ::llvm::StringRef name, bool emitAsComment = false);
  static SVAttributeAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, bool emitAsComment = false);
  static SVAttributeAttr get(::mlir::MLIRContext *context, ::llvm::StringRef name, ::llvm::StringRef expression, bool emitAsComment = false);
  static SVAttributeAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::StringAttr expression, bool emitAsComment = false);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"attribute"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getName() const;
  ::mlir::StringAttr getExpression() const;
  mlir::BoolAttr getEmitAsComment() const;
};
class CaseExprPatternAttr : public ::mlir::Attribute::AttrBase<CaseExprPatternAttr, ::mlir::Attribute, ::mlir::AttributeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.expr";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"expr"};
  }

};
namespace detail {

struct ValidationQualifierTypeEnumAttrStorage;

} // namespace detail
class ValidationQualifierTypeEnumAttr : public ::mlir::Attribute::AttrBase<ValidationQualifierTypeEnumAttr, ::mlir::Attribute, detail::ValidationQualifierTypeEnumAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.validation_qualifier";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static ValidationQualifierTypeEnumAttr get(::mlir::MLIRContext *context, ::circt::sv::ValidationQualifierTypeEnum value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"validation_qualifier"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::sv::ValidationQualifierTypeEnum getValue() const;
};
namespace detail {

struct IncludeStyleAttrStorage;

} // namespace detail
class IncludeStyleAttr : public ::mlir::Attribute::AttrBase<IncludeStyleAttr, ::mlir::Attribute, detail::IncludeStyleAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.include_style";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static IncludeStyleAttr get(::mlir::MLIRContext *context, ::IncludeStyle value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"include_style"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::IncludeStyle getValue() const;
};
namespace detail {

struct ModportDirectionAttrStorage;

} // namespace detail
class ModportDirectionAttr : public ::mlir::Attribute::AttrBase<ModportDirectionAttr, ::mlir::Attribute, detail::ModportDirectionAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.modport_direction";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static ModportDirectionAttr get(::mlir::MLIRContext *context, ::circt::sv::ModportDirection value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"modport_direction"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::sv::ModportDirection getValue() const;
};
namespace detail {

struct ModportStructAttrStorage;

} // namespace detail
class ModportStructAttr : public ::mlir::Attribute::AttrBase<ModportStructAttr, ::mlir::Attribute, detail::ModportStructAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "sv.mod_port";
  static constexpr ::llvm::StringLiteral dialectName = "sv";
  static ModportStructAttr get(::mlir::MLIRContext *context, ::circt::sv::ModportDirectionAttr direction, mlir::FlatSymbolRefAttr signal);
  static ModportStructAttr get(::mlir::MLIRContext *context, ModportDirection dir, mlir::FlatSymbolRefAttr sig);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mod_port"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::circt::sv::ModportDirectionAttr getDirection() const;
  mlir::FlatSymbolRefAttr getSignal() const;
};

} // namespace circt::sv
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::MacroIdentAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::SVAttributeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::CaseExprPatternAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::ValidationQualifierTypeEnumAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::IncludeStyleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::ModportDirectionAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::sv::ModportStructAttr)

#endif // GET_ATTRDEF_CLASSES

