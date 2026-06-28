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
namespace circt::chirrtl {

/// a behavioral memory
/// Syntax:
/// ```
/// cmemory-type ::= `cmemory` `<` element-type, element-count `>`
/// ```
/// 
/// The value of a `cmemory` type represents a behavioral memory with unknown
/// ports.  This is produced by `combmem` and `seqmem` declarations and used by
/// `memoryport` declarations to define memories and their ports. A CMemory is
/// similar to a vector of passive element types.
/// 
/// Examples:
/// 
/// ```mlir
/// !chirrtl.cmemory<uint<32>, 16>
/// !chirrtl.cmemory<bundle<a : uint<1>>, 16>
/// ```
class CMemoryType;
/// a behavioral memory port
/// Syntax:
/// ```
/// cmemoryport-type ::= `cmemoryport`
/// ```
/// 
/// The value of a `cmemoryport` type represents a port which has been
/// declared on a `cmemory`.  This value is used to set the memory port access
/// conditions.
class CMemoryPortType;
namespace detail {

struct CMemoryTypeStorage;

} // namespace detail
class CMemoryType : public ::mlir::Type::TypeBase<CMemoryType, ::mlir::Type, detail::CMemoryTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "chirrtl.cmemory";
  static constexpr ::llvm::StringLiteral dialectName = "chirrtl";
  using Base::getChecked;
  static CMemoryType get(::mlir::MLIRContext *context, firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static CMemoryType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static CMemoryType get(firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static CMemoryType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, firrtl::FIRRTLBaseType elementType, uint64_t numElements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cmemory"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  firrtl::FIRRTLBaseType getElementType() const;
  uint64_t getNumElements() const;
};
class CMemoryPortType : public ::mlir::Type::TypeBase<CMemoryPortType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "chirrtl.cmemoryport";
  static constexpr ::llvm::StringLiteral dialectName = "chirrtl";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cmemoryport"};
  }

};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::CMemoryType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::CMemoryPortType)

#endif // GET_TYPEDEF_CLASSES

