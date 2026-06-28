/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Emit.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::emit {

/// Represents a file list
/// This operation emits a file list referencing a set of files.
/// 
/// File lists can be references from other ops (including other file lists)
/// through an optional symbol.
class FileListOp;

} // namespace circt::emit
namespace circt::emit {

/// Represents the contents of an emitted file
/// This operation groups a set of nested operations to be emitted to a file.
/// 
/// Other operations (such as file lists)can reference a file to access its
/// filename through an optional symbol.
class FileOp;

} // namespace circt::emit
namespace circt::emit {

/// Emittable fragment which can be replicated before modules
/// The fragment operation is a container for other operations that can
/// be emitted before other operations. It carries a symbol that can be
/// referenced by an `emit.fragments` attribute placed on operations before
/// which the fragments should be inserted.
/// 
/// In single-file mode, each fragment is emitted once. In split file emission
/// mode, fragments precede all operations that reference them, but are still
/// emitted at most once per file.
class FragmentOp;

} // namespace circt::emit
namespace circt::emit {

/// Print a referenced SV operation inline into the file
/// The `emit.ref` operation targets an op via a symbol, emitting its
/// contents into the file it is part of. The set of targetable
/// operations and the emission rules are defined in ExportVerilog.
class RefOp;

} // namespace circt::emit
namespace circt::emit {

/// Verbatim opaque text emitted inline.
/// This operation produces opaque text inline in the file.
/// 
/// `emit.verbatim` allows symbol reference substitutions with {{0}} syntax.
class VerbatimOp;

} // namespace circt::emit
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FileListOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FileListOpGenericAdaptorBase {
public:
  struct Properties {
    using file_nameTy = ::mlir::StringAttr;
    file_nameTy file_name;

    auto getFileName() const {
      auto &propStorage = this->file_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setFileName(const ::mlir::StringAttr &propValue) {
      this->file_name = propValue;
    }
    using filesTy = ::mlir::ArrayAttr;
    filesTy files;

    auto getFiles() const {
      auto &propStorage = this->files;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setFiles(const ::mlir::ArrayAttr &propValue) {
      this->files = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.file_name == this->file_name &&
        rhs.files == this->files &&
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FileListOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("emit.file_list", odsAttrs.getContext());
  }

  FileListOpGenericAdaptorBase(FileListOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getFileNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().file_name);
    return attr;
  }

  ::llvm::StringRef getFileName();
  ::mlir::ArrayAttr getFilesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().files);
    return attr;
  }

  ::mlir::ArrayAttr getFiles();
  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
};

} // namespace detail
template <typename RangeT>
class FileListOpGenericAdaptor : public detail::FileListOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FileListOpGenericAdaptorBase;
public:
  FileListOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FileListOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FileListOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FileListOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FileListOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FileListOpGenericAdaptor(RangeT values, const FileListOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FileListOp, typename = std::enable_if_t<std::is_same_v<LateInst, FileListOp>>>
  FileListOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FileListOpAdaptor : public FileListOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FileListOpGenericAdaptor::FileListOpGenericAdaptor;
  FileListOpAdaptor(FileListOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FileListOp : public ::mlir::Op<FileListOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FileListOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FileListOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("file_name"), ::llvm::StringRef("files"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFileNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFileNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFilesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFilesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("emit.file_list");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getFileNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().file_name);
  }

  ::llvm::StringRef getFileName();
  ::mlir::ArrayAttr getFilesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().files);
  }

  ::mlir::ArrayAttr getFiles();
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  void setFileNameAttr(::mlir::StringAttr attr) {
    getProperties().file_name = attr;
  }

  void setFileName(::llvm::StringRef attrValue);
  void setFilesAttr(::mlir::ArrayAttr attr) {
    getProperties().files = attr;
  }

  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FileListOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FileListOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // SymbolOpInterface
  static bool isOptionalSymbol() { return true; }
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::FileListOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::detail::FileListOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FileOpGenericAdaptorBase {
public:
  struct Properties {
    using file_nameTy = ::mlir::StringAttr;
    file_nameTy file_name;

    auto getFileName() const {
      auto &propStorage = this->file_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setFileName(const ::mlir::StringAttr &propValue) {
      this->file_name = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.file_name == this->file_name &&
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("emit.file", odsAttrs.getContext());
  }

  FileOpGenericAdaptorBase(FileOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getFileNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().file_name);
    return attr;
  }

  ::llvm::StringRef getFileName();
  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class FileOpGenericAdaptor : public detail::FileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FileOpGenericAdaptorBase;
public:
  FileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FileOpGenericAdaptor(RangeT values, const FileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FileOp, typename = std::enable_if_t<std::is_same_v<LateInst, FileOp>>>
  FileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FileOpAdaptor : public FileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FileOpGenericAdaptor::FileOpGenericAdaptor;
  FileOpAdaptor(FileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FileOp : public ::mlir::Op<FileOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("file_name"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFileNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFileNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("emit.file");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getBodyRegion() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getFileNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().file_name);
  }

  ::llvm::StringRef getFileName();
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  void setFileNameAttr(::mlir::StringAttr attr) {
    getProperties().file_name = attr;
  }

  void setFileName(::llvm::StringRef attrValue);
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef fileName, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef fileName, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef fileName, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr fileName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr fileName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr fileName, llvm::function_ref<void()> bodyCtor = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const Twine &fileName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const Twine &fileName, llvm::function_ref<void()> bodyCtor = {});
  static FileOp create(::mlir::ImplicitLocOpBuilder &builder, const Twine &fileName, llvm::function_ref<void()> bodyCtor = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // SymbolOpInterface
  static bool isOptionalSymbol() { return true; }
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::FileOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::detail::FileOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FragmentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FragmentOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FragmentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("emit.fragment", odsAttrs.getContext());
  }

  FragmentOpGenericAdaptorBase(FragmentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::Region &getBodyRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class FragmentOpGenericAdaptor : public detail::FragmentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FragmentOpGenericAdaptorBase;
public:
  FragmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FragmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FragmentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FragmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FragmentOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FragmentOpGenericAdaptor(RangeT values, const FragmentOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FragmentOp, typename = std::enable_if_t<std::is_same_v<LateInst, FragmentOp>>>
  FragmentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FragmentOpAdaptor : public FragmentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FragmentOpGenericAdaptor::FragmentOpGenericAdaptor;
  FragmentOpAdaptor(FragmentOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FragmentOp : public ::mlir::Op<FragmentOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FragmentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FragmentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("emit.fragment");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getBodyRegion() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static FragmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static FragmentOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef symName, llvm::function_ref<void()> bodyCtor = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr symName, llvm::function_ref<void()> bodyCtor = {});
  static FragmentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr symName, llvm::function_ref<void()> bodyCtor = {});
  static FragmentOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr symName, llvm::function_ref<void()> bodyCtor = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::FragmentOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::detail::FragmentOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::RefOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RefOpGenericAdaptorBase {
public:
  struct Properties {
    using targetTy = ::mlir::FlatSymbolRefAttr;
    targetTy target;

    auto getTarget() const {
      auto &propStorage = this->target;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setTarget(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->target = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.target == this->target &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RefOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("emit.ref", odsAttrs.getContext());
  }

  RefOpGenericAdaptorBase(RefOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getTargetAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().target);
    return attr;
  }

  ::llvm::StringRef getTarget();
};

} // namespace detail
template <typename RangeT>
class RefOpGenericAdaptor : public detail::RefOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RefOpGenericAdaptorBase;
public:
  RefOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RefOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RefOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RefOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RefOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RefOpGenericAdaptor(RangeT values, const RefOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RefOp, typename = std::enable_if_t<std::is_same_v<LateInst, RefOp>>>
  RefOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RefOpAdaptor : public RefOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RefOpGenericAdaptor::RefOpGenericAdaptor;
  RefOpAdaptor(RefOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RefOp : public ::mlir::Op<RefOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<circt::emit::FileOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RefOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RefOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("target")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTargetAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTargetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("emit.ref");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getTargetAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().target);
  }

  ::llvm::StringRef getTarget();
  void setTargetAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().target = attr;
  }

  void setTarget(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr target);
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr target);
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target);
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target);
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef target);
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef target);
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef target);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef target);
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef target);
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef target);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RefOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RefOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::RefOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::detail::RefOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::VerbatimOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VerbatimOpGenericAdaptorBase {
public:
  struct Properties {
    using textTy = ::mlir::StringAttr;
    textTy text;

    auto getText() const {
      auto &propStorage = this->text;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setText(const ::mlir::StringAttr &propValue) {
      this->text = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.text == this->text &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  VerbatimOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("emit.verbatim", odsAttrs.getContext());
  }

  VerbatimOpGenericAdaptorBase(VerbatimOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getTextAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().text);
    return attr;
  }

  ::llvm::StringRef getText();
};

} // namespace detail
template <typename RangeT>
class VerbatimOpGenericAdaptor : public detail::VerbatimOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VerbatimOpGenericAdaptorBase;
public:
  VerbatimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VerbatimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : VerbatimOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VerbatimOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VerbatimOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VerbatimOpGenericAdaptor(RangeT values, const VerbatimOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VerbatimOp, typename = std::enable_if_t<std::is_same_v<LateInst, VerbatimOp>>>
  VerbatimOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class VerbatimOpAdaptor : public VerbatimOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VerbatimOpGenericAdaptor::VerbatimOpGenericAdaptor;
  VerbatimOpAdaptor(VerbatimOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VerbatimOp : public ::mlir::Op<VerbatimOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<circt::emit::FileOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VerbatimOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VerbatimOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("text")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTextAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTextAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("emit.verbatim");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getTextAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().text);
  }

  ::llvm::StringRef getText();
  void setTextAttr(::mlir::StringAttr attr) {
    getProperties().text = attr;
  }

  void setText(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr text);
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr text);
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr text);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text);
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text);
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef text);
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef text);
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef text);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef text);
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef text);
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef text);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VerbatimOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VerbatimOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::emit
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::VerbatimOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::emit::detail::VerbatimOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

