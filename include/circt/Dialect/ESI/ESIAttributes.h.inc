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
namespace circt::esi {

/// An attribute which indicates a channel is unconnected.
class NullChannelAttr;
/// An application relevant instance identifier
/// Identifies an instance which is visible through multiple hierarchy levels.
/// Indended to make locating an instance easier in the instance hierarchy.
class AppIDAttr;
/// An application-specific hierarchical path through a design
/// A list of AppID components which specifies a specific dynamic instance
/// in the design.
class AppIDPathAttr;
/// A binary blob
class BlobAttr;
namespace detail {

struct NullChannelAttrStorage;

} // namespace detail
class NullChannelAttr : public ::mlir::Attribute::AttrBase<NullChannelAttr, ::mlir::Attribute, detail::NullChannelAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "esi.null";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static NullChannelAttr get(::mlir::MLIRContext *context, TypeAttr type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"null"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  TypeAttr getType() const;
};
namespace detail {

struct AppIDAttrStorage;

} // namespace detail
class AppIDAttr : public ::mlir::Attribute::AttrBase<AppIDAttr, ::mlir::Attribute, detail::AppIDAttrStorage> {
public:
  using Base::Base;
  static constexpr StringRef AppIDAttrName = "esi.appid";
  static constexpr ::llvm::StringLiteral name = "esi.appid";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static AppIDAttr get(::mlir::MLIRContext *context, StringAttr name, std::optional<uint64_t> index);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"appid"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  StringAttr getName() const;
  std::optional<uint64_t> getIndex() const;
};
namespace detail {

struct AppIDPathAttrStorage;

} // namespace detail
class AppIDPathAttr : public ::mlir::Attribute::AttrBase<AppIDPathAttr, ::mlir::Attribute, detail::AppIDPathAttrStorage> {
public:
  using Base::Base;
  // Get an AppIDPathAttr without the last component. Returns None if the path
  // is simply the root.
  AppIDPathAttr getParent();
  static constexpr ::llvm::StringLiteral name = "esi.appid_path";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static AppIDPathAttr get(::mlir::MLIRContext *context, FlatSymbolRefAttr root, ::llvm::ArrayRef<AppIDAttr> path);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"appid_path"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  FlatSymbolRefAttr getRoot() const;
  ::llvm::ArrayRef<AppIDAttr> getPath() const;
};
namespace detail {

struct BlobAttrStorage;

} // namespace detail
class BlobAttr : public ::mlir::Attribute::AttrBase<BlobAttr, ::mlir::Attribute, detail::BlobAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "esi.blob";
  static constexpr ::llvm::StringLiteral dialectName = "esi";
  static BlobAttr get(::mlir::MLIRContext *context, ::llvm::ArrayRef<uint8_t> data);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"blob"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<uint8_t> getData() const;
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::NullChannelAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::AppIDAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::AppIDPathAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::BlobAttr)

#endif // GET_ATTRDEF_CLASSES

