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
namespace circt::msft {

/// Descibes a physical location on a device
/// Annotate a particular entity within an op with the location of the device
/// on an FPGA to which it should mapped. The coordinates in this attribute
/// are absolute locations on the device, so if there are two instances of a
/// module with this annotation incorrect results will be generated. How to
/// solve this is a more general, open problem.
class PhysLocationAttr;
/// Describes a rectangle bounding a physical region on a device
/// Describes a rectangular bound within a device. The lower and upper bounds
/// must be specified for both the X and Y axis. The bounds are inclusive.
class PhysicalBoundsAttr;
/// Vector of optional locations corresponding to bits in a type
class LocationVectorAttr;
namespace detail {

struct PhysLocationAttrStorage;

} // namespace detail
class PhysLocationAttr : public ::mlir::Attribute::AttrBase<PhysLocationAttr, ::mlir::Attribute, detail::PhysLocationAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "msft.physloc";
  static constexpr ::llvm::StringLiteral dialectName = "msft";
  static PhysLocationAttr get(::mlir::MLIRContext *context, PrimitiveTypeAttr primitiveType, uint64_t x, uint64_t y, uint64_t num);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"physloc"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PrimitiveTypeAttr getPrimitiveType() const;
  uint64_t getX() const;
  uint64_t getY() const;
  uint64_t getNum() const;
};
namespace detail {

struct PhysicalBoundsAttrStorage;

} // namespace detail
class PhysicalBoundsAttr : public ::mlir::Attribute::AttrBase<PhysicalBoundsAttr, ::mlir::Attribute, detail::PhysicalBoundsAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "msft.physical_bounds";
  static constexpr ::llvm::StringLiteral dialectName = "msft";
  static PhysicalBoundsAttr get(::mlir::MLIRContext *context, uint64_t xMin, uint64_t xMax, uint64_t yMin, uint64_t yMax);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"physical_bounds"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint64_t getXMin() const;
  uint64_t getXMax() const;
  uint64_t getYMin() const;
  uint64_t getYMax() const;
};
namespace detail {

struct LocationVectorAttrStorage;

} // namespace detail
class LocationVectorAttr : public ::mlir::Attribute::AttrBase<LocationVectorAttr, ::mlir::Attribute, detail::LocationVectorAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "msft.location_vec";
  static constexpr ::llvm::StringLiteral dialectName = "msft";
  using Base::getChecked;
  static LocationVectorAttr get(::mlir::MLIRContext *context, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs);
  static LocationVectorAttr getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"location_vec"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::TypeAttr getType() const;
  ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> getLocs() const;
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PhysLocationAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PhysicalBoundsAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::LocationVectorAttr)

#endif // GET_ATTRDEF_CLASSES

