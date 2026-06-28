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
namespace circt::hw {

/// Output file attribute
/// This attribute represents an output file for something which will be
/// printed. The `filename` string is the file to be output to. If `filename`
/// ends in a `/` it is considered an output directory.
/// 
/// When ExportVerilog runs, one of the files produced is a list of all other
/// files which are produced. The flag `excludeFromFileList` controls if this
/// file should be included in this list. If any `OutputFileAttr` referring to
/// the same file sets this to `true`, it will be included in the file list.
/// This option defaults to `false`.
/// 
/// For each file emitted by the verilog emitter, certain prelude output will
/// be included before the main content. The flag `includeReplicatedOps` can
/// be used to disable the addition of the prelude text. All `OutputFileAttr`s
/// referring to the same file must use a consistent setting for this value.
/// This option defaults to `true`.
/// 
/// Examples:
/// ```mlir
///   #hw.ouput_file<"/home/tester/t.sv">
///   #hw.ouput_file<"t.sv", excludeFromFileList, includeReplicatedOps>
/// ```
class OutputFileAttr;
/// Module or instance parameter definition
/// An attribute describing a module parameter, or instance parameter
/// specification.
class ParamDeclAttr;
/// Is a reference to a parameter value.
class ParamDeclRefAttr;
/// Represents text to emit directly to SystemVerilog for a parameter
class ParamVerbatimAttr;
/// Parameter expression combining operands
class ParamExprAttr;
/// Enumeration field attribute
/// This attribute represents a field of an enumeration.
/// 
/// Examples:
/// ```mlir
///   #hw.enum.value<A, !hw.enum<A, B, C>>
/// ```
class EnumFieldAttr;
/// Refer to a name inside a module
/// This works like a symbol reference, but to a name inside a module.
class InnerRefAttr;
class InnerSymPropertiesAttr;
/// Inner symbol definition
/// Defines the properties of an inner_sym attribute. It specifies the symbol
/// name and symbol visibility for each field ID. For any ground types,
/// there are no subfields and the field ID is 0. For aggregate types, a
/// unique field ID is assigned to each field by visiting them in a
/// depth-first pre-order. The custom assembly format ensures that for ground
/// types, only `@<sym_name>` is printed.
class InnerSymAttr;
namespace detail {

struct OutputFileAttrStorage;

} // namespace detail
class OutputFileAttr : public ::mlir::Attribute::AttrBase<OutputFileAttr, ::mlir::Attribute, detail::OutputFileAttrStorage> {
public:
  using Base::Base;
  /// Get an OutputFileAttr from a string filename, canonicalizing the
  /// filename.
  static OutputFileAttr getFromFilename(::mlir::MLIRContext *context,
                                        const ::mlir::Twine &filename,
                                        bool excludeFromFileList = false,
                                        bool includeReplicatedOps = false);

  /// Get an OutputFileAttr from a string filename, resolving it relative to
  /// `directory`. If `filename` is an absolute path, the given `directory`
  /// will not be used.
  static OutputFileAttr getFromDirectoryAndFilename(
                                        ::mlir::MLIRContext *context,
                                        const ::mlir::Twine &directory,
                                        const ::mlir::Twine &filename,
                                        bool excludeFromFileList = false,
                                        bool includeReplicatedOps = false);

  /// Get an OutputFileAttr from a string directory name. The name will have
  /// a trailing `/` added if it is not there, ensuring that this will be
  /// an output directory.
  static OutputFileAttr getAsDirectory(::mlir::MLIRContext *context,
                                       const ::mlir::Twine &directory,
                                       bool excludeFromFileList = false,
                                       bool includeReplicatedOps = false);

  /// Returns true if this a directory.
  bool isDirectory();

  /// Get the directory of this output file, or null if there is none.
  ::mlir::StringRef getDirectory();
  static constexpr ::llvm::StringLiteral name = "hw.output_file";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static OutputFileAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr filename, ::mlir::BoolAttr excludeFromFilelist, ::mlir::BoolAttr includeReplicatedOps);
  static OutputFileAttr get(::mlir::StringAttr filename, ::mlir::BoolAttr excludeFromFileList, ::mlir::BoolAttr includeReplicatedOps);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"output_file"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getFilename() const;
  ::mlir::BoolAttr getExcludeFromFilelist() const;
  ::mlir::BoolAttr getIncludeReplicatedOps() const;
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
  static constexpr ::llvm::StringLiteral name = "hw.param.decl";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static ParamDeclAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value);
  static ParamDeclAttr get(::mlir::StringAttr name, ::mlir::Type type);
  static ParamDeclAttr get(::mlir::StringRef name, ::mlir::Type type);
  static ParamDeclAttr get(::mlir::StringAttr name, ::mlir::TypedAttr value);
  static ParamDeclAttr get(::mlir::StringRef name, ::mlir::TypedAttr value);
  static ParamDeclAttr get(::mlir::StringRef name, ::mlir::Type type, ::mlir::TypedAttr value);
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

struct ParamDeclRefAttrStorage;

} // namespace detail
class ParamDeclRefAttr : public ::mlir::Attribute::AttrBase<ParamDeclRefAttr, ::mlir::Attribute, detail::ParamDeclRefAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.param.decl.ref";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static ParamDeclRefAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type);
  static ParamDeclRefAttr get(::mlir::StringAttr name, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"param.decl.ref"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getName() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct ParamVerbatimAttrStorage;

} // namespace detail
class ParamVerbatimAttr : public ::mlir::Attribute::AttrBase<ParamVerbatimAttr, ::mlir::Attribute, detail::ParamVerbatimAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.param.verbatim";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static ParamVerbatimAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr value, ::mlir::Type type);
  static ParamVerbatimAttr get(::mlir::StringAttr value);
  static ParamVerbatimAttr get(::mlir::StringAttr value, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"param.verbatim"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getValue() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct ParamExprAttrStorage;

} // namespace detail
class ParamExprAttr : public ::mlir::Attribute::AttrBase<ParamExprAttr, ::mlir::Attribute, detail::ParamExprAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  /// Build a parameter expression.  This automatically canonicalizes and
  /// folds, so it may not necessarily return a ParamExprAttr.
  static mlir::TypedAttr get(PEO opcode,
                             mlir::ArrayRef<mlir::TypedAttr> operands);

  /// Build a binary parameter expression for convenience.
  static mlir::TypedAttr get(PEO opcode, mlir::TypedAttr lhs,
                                         mlir::TypedAttr rhs) {
    mlir::TypedAttr operands[] = { lhs, rhs };
    return get(opcode, operands);
  }
  static constexpr ::llvm::StringLiteral name = "hw.param.expr";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"param.expr"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PEO getOpcode() const;
  ::llvm::ArrayRef<::mlir::TypedAttr> getOperands() const;
  ::mlir::Type getType() const;
};
namespace detail {

struct EnumFieldAttrStorage;

} // namespace detail
class EnumFieldAttr : public ::mlir::Attribute::AttrBase<EnumFieldAttr, ::mlir::Attribute, detail::EnumFieldAttrStorage> {
public:
  using Base::Base;
  /// Builds a new EnumFieldAttr of the provided value.
  /// This will fail if the value is not a member of the provided enum type.
  static EnumFieldAttr get(::mlir::Location loc, ::mlir::StringAttr value, mlir::Type type);
  static constexpr ::llvm::StringLiteral name = "hw.enum.field";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"enum.field"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getField() const;
  ::mlir::TypeAttr getType() const;
};
namespace detail {

struct InnerRefAttrStorage;

} // namespace detail
class InnerRefAttr : public ::mlir::Attribute::AttrBase<InnerRefAttr, ::mlir::Attribute, detail::InnerRefAttrStorage> {
public:
  using Base::Base;
  /// Get the InnerRefAttr for an operation and add the sym on it.
  static InnerRefAttr getFromOperation(mlir::Operation *op,
                                       mlir::StringAttr symName,
                                       mlir::StringAttr moduleName);

  /// Return the name of the referenced module.
  mlir::StringAttr getModule() const { return getModuleRef().getAttr(); }
  static constexpr ::llvm::StringLiteral name = "hw.innerNameRef";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static InnerRefAttr get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr moduleRef, ::mlir::StringAttr name);
  static InnerRefAttr get(::mlir::StringAttr module, ::mlir::StringAttr name);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"innerNameRef"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FlatSymbolRefAttr getModuleRef() const;
  ::mlir::StringAttr getName() const;
};
namespace detail {

struct InnerSymPropertiesAttrStorage;

} // namespace detail
class InnerSymPropertiesAttr : public ::mlir::Attribute::AttrBase<InnerSymPropertiesAttr, ::mlir::Attribute, detail::InnerSymPropertiesAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.innerSymProps";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static InnerSymPropertiesAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility);
  static InnerSymPropertiesAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility);
  static InnerSymPropertiesAttr get(::mlir::StringAttr sym);
  static InnerSymPropertiesAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::StringAttr sym);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"innerSymProps"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getName() const;
  uint64_t getFieldID() const;
  ::mlir::StringAttr getSymVisibility() const;
};
namespace detail {

struct InnerSymAttrStorage;

} // namespace detail
class InnerSymAttr : public ::mlir::Attribute::AttrBase<InnerSymAttr, ::mlir::Attribute, detail::InnerSymAttrStorage> {
public:
  using Base::Base;
  using ElementType = InnerSymPropertiesAttr;

  /// Get the inner sym name for fieldID, if it exists.
  mlir::StringAttr getSymIfExists(uint64_t fieldID) const;

  /// Get the inner sym name for fieldID=0, if it exists.
  mlir::StringAttr getSymName() const { return getSymIfExists(0); }

  /// Get the number of inner symbols defined.
  size_t size() const { return getProps().size(); }

  /// Check if this is an empty array, no sym names stored.
  bool empty() const { return getProps().empty(); }

  /// Return an InnerSymAttr with the inner symbol for the specified fieldID removed.
  InnerSymAttr erase(uint64_t fieldID) const;

  using iterator = mlir::ArrayRef<InnerSymPropertiesAttr>::iterator;
  /// Iterator begin for all the InnerSymProperties.
  iterator begin() const { return getProps().begin(); }

  /// Iterator end for all the InnerSymProperties.
  iterator end() const { return getProps().end(); }

  /// Invoke the func, for all sym names. Return success(),
  /// if the callback function never returns failure().
  mlir::LogicalResult walkSymbols(llvm::function_ref<
                            mlir::LogicalResult (::mlir::StringAttr)>) const;
  static constexpr ::llvm::StringLiteral name = "hw.innerSym";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static InnerSymAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<InnerSymPropertiesAttr> props);
  static InnerSymAttr get(::mlir::StringAttr sym);
  static InnerSymAttr get(::mlir::MLIRContext *context);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"innerSym"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<InnerSymPropertiesAttr> getProps() const;
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::OutputFileAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ParamDeclAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ParamDeclRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ParamVerbatimAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ParamExprAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::EnumFieldAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::InnerRefAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::InnerSymPropertiesAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::InnerSymAttr)

#endif // GET_ATTRDEF_CLASSES

