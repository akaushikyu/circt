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
namespace circt::seq {

/// Multi-dimensional memory type
/// Syntax:
/// ```
/// hlmem-type ::== `hlmem` `<` dim-list element-type `>`
/// ```
/// 
/// The HLMemType represents the type of an addressable memory structure. The
/// type is inherently multidimensional. Dimensions must be known integer values.
/// 
/// Note: unidimensional memories are represented as <1x{element type}> -
/// <{element type}> is illegal.
class HLMemType;
/// A FIRRTL-flavored memory
/// The `!seq.firmem` type represents a FIRRTL-flavored memory declared by a
/// `seq.firmem` operation. It captures the parameters of the memory that are
/// relevant to the read, write, and read-write ports, such as width and depth.
class FirMemType;
/// A type for clock-carrying wires
/// The `!seq.clock` type represents signals which can be used to drive the
/// clock input of sequential operations.
class ClockType;
/// Value type that is immutable after initialization
class ImmutableType;
namespace detail {

struct HLMemTypeStorage;

} // namespace detail
class HLMemType : public ::mlir::Type::TypeBase<HLMemType, ::mlir::Type, detail::HLMemTypeStorage, ::mlir::ShapedType::Trait> {
public:
  using Base::Base;
  using ShapedType::Trait<HLMemType>::clone;
  using ShapedType::Trait<HLMemType>::getElementTypeBitWidth;
  using ShapedType::Trait<HLMemType>::getRank;
  using ShapedType::Trait<HLMemType>::getNumElements;
  using ShapedType::Trait<HLMemType>::isDynamicDim;
  using ShapedType::Trait<HLMemType>::hasStaticShape;
  using ShapedType::Trait<HLMemType>::getNumDynamicDims;
  using ShapedType::Trait<HLMemType>::getDimSize;
  using ShapedType::Trait<HLMemType>::getDynamicDimIndex;

  // Returns the set of types required to access this memory type.
  llvm::SmallVector<Type> getAddressTypes() const;

  /// Returns if this type is ranked (always true).
  bool hasRank() const { return true; }

  /// Clone this vector type with the given shape and element type. If the
  /// provided shape is `None`, the current shape of the type is used.
  HLMemType cloneWith(std::optional<ArrayRef<int64_t>> shape,
                       Type elementType) const;
  static constexpr ::llvm::StringLiteral name = "seq.hlmem";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  using Base::getChecked;
  static HLMemType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> shape, Type elementType);
  static HLMemType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> shape, Type elementType);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"hlmem"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<int64_t> getShape() const;
  Type getElementType() const;
};
namespace detail {

struct FirMemTypeStorage;

} // namespace detail
class FirMemType : public ::mlir::Type::TypeBase<FirMemType, ::mlir::Type, detail::FirMemTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "seq.firmem";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  static FirMemType get(::mlir::MLIRContext *context, uint64_t depth, uint32_t width, std::optional<uint32_t> maskWidth);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"firmem"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint64_t getDepth() const;
  uint32_t getWidth() const;
  std::optional<uint32_t> getMaskWidth() const;
};
class ClockType : public ::mlir::Type::TypeBase<ClockType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "seq.clock";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"clock"};
  }

};
namespace detail {

struct ImmutableTypeStorage;

} // namespace detail
class ImmutableType : public ::mlir::Type::TypeBase<ImmutableType, ::mlir::Type, detail::ImmutableTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "seq.immutable";
  static constexpr ::llvm::StringLiteral dialectName = "seq";
  static ImmutableType get(::mlir::MLIRContext *context, ::mlir::Type innerType);
  static ImmutableType get(Type innerType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"immutable"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getInnerType() const;
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::HLMemType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ImmutableType)

#endif // GET_TYPEDEF_CLASSES

