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
namespace circt::seq {

/// clock constant
class ClockConstAttr;
/// Memory initialization information
/// This attribute captures what the initial contents of a memory should be.
/// At the moment this is modeled primarily with simulation in mind, where the
/// memory contents are pre-loaded from a file at simulation startup.
/// 
/// The `filename` specifies a file on disk that contains the initial contents
/// for this memory. If `isBinary` is set, the file is interpreted as a binary
/// file, otherwise it is treated as hexadecimal. This is modeled after the
/// `$readmemh` and `$readmemb` SystemVerilog functions. If `isInline` is set,
/// the initialization is emitted directly in the memory model; otherwise it is
/// split out into a separate module that can be bound in.
class FirMemInitAttr;
namespace detail {

struct ClockConstAttrStorage;

} // namespace detail
class ClockConstAttr : public ::mlir::Attribute::AttrBase<ClockConstAttr, ::mlir::Attribute, detail::ClockConstAttrStorage, ::mlir::TypedAttr::Trait> {
public:
  using Base::Base;
  mlir::Type getType();
  static constexpr ::llvm::StringLiteral name = "seq.clock_constant";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  static ClockConstAttr get(::mlir::MLIRContext *context, circt::seq::ClockConst value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"clock_constant"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  circt::seq::ClockConst getValue() const;
};
namespace detail {

struct FirMemInitAttrStorage;

} // namespace detail
class FirMemInitAttr : public ::mlir::Attribute::AttrBase<FirMemInitAttr, ::mlir::Attribute, detail::FirMemInitAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "seq.firmem.init";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  static FirMemInitAttr get(::mlir::MLIRContext *context, mlir::StringAttr filename, bool isBinary, bool isInline);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"firmem.init"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::StringAttr getFilename() const;
  bool getIsBinary() const;
  bool getIsInline() const;
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockConstAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemInitAttr)

#endif // GET_ATTRDEF_CLASSES

