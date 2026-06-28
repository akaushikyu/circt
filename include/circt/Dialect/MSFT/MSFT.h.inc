/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::msft {

class DeclPhysicalRegionOp;

} // namespace circt::msft
namespace circt::msft {

/// A module instance in the instance hierarchy
/// Represents an instance (as in instance in the instance hierarchy) referred
/// to henceforth as a dynamic instance. Specified with a path through the
/// instance hierarchy (which in the future will be replaced with an AppID).
/// Lowers to a `hw.hierpath` but unlike a global ref, does not require all of
/// the ops participating in the hierpath to contain a back pointer attribute.
/// Allows users to efficiently add placements to a large number of dynamic
/// instances which happen to map to a small number of static instances by
/// bulk-adding the necessary `hw.hierpath` attributes.
/// 
/// During the lowering, moves the operations in the body to the top level and
/// gives them the symbol of the hierpath which was created to replace the
/// dynamic instance.
class DynamicInstanceOp;

} // namespace circt::msft
namespace circt::msft {

/// Specify an arbitrary attribute attached to a dynamic instance
/// Allows a user to specify a custom attribute name and value which is attached
/// to a dynamic instance.
/// 
/// For Quartus tcl, translates to:
///   set_instance_assignment -name $name $value -to $parent|<instance_path>
class DynamicInstanceVerbatimAttrOp;

} // namespace circt::msft
namespace circt::msft {

/// The root of an instance hierarchy
/// Models the "root" / "top" of an instance hierarchy. `DynamicInstanceOp`s
/// must be contained by this op. Specifies the top module and (optionally) an
/// "instance" name in the case where there are multiple instances of a
/// particular module in a design. (As is often the case where one isn't
/// producing the design's "top" module but a subdesign.)
class InstanceHierarchyOp;

} // namespace circt::msft
namespace circt::msft {

/// Model of a linear datapath which can be arbitrarily pipelined
/// Defines a feed-forward datapath which can be scheduled into a pipeline.
/// Due to the feed-forwardness, the inner region is NOT a graph region.
/// Internally, only combinational operations (`comb`, `msft`, `hw`) are allowed.
/// 
/// Example:
/// ```mlir
/// msft.module @foo(%in0 : i32, %in1 : i32, %in2 : i32, %clk : i1) -> (out: i32) -> {
///   %0 = msft.hlc.linear(%a = %in0, %b = %in1, %c = %in2) clock %clk (i32, i32, i32) -> (i32) {
///     %0 = comb.mul %a, %b : i32
///     %1 = comb.add %0, %c : i32
///     msft.output %1 : i32
///   }
/// }
/// ```
class LinearOp;

} // namespace circt::msft
namespace circt::msft {

/// termination operation
class OutputOp;

} // namespace circt::msft
namespace circt::msft {

/// Specify a multicycle constraint
/// Specifies a multicycle constraint in between two registers.
/// `source` and `dest` symbols reference `HierPathOp` symbols denoting the
/// exact registers in the instance hierarchy to which the constraint applies.
class PDMulticycleOp;

} // namespace circt::msft
namespace circt::msft {

/// Specify a location for an instance
/// Used to specify a specific location on an FPGA to place a dynamic instance.
/// Supports specifying the location of a subpath for extern modules and device
/// primitives. Intended to live as a child of `instance.dynamic` initially
/// without the `ref` field. The dynamic instance lowering will fill in `ref`
/// with the symol of the `hw.hierpath` op corresponding to the lowered dynamic
/// instance.
class PDPhysLocationOp;

} // namespace circt::msft
namespace circt::msft {

/// Specify a physical region for an instance
/// Annotate a particular entity within an op with the region of the devices
/// on an FPGA to which it should mapped. The physRegionRef must refer to a
/// DeclPhysicalRegion operation.
class PDPhysRegionOp;

} // namespace circt::msft
namespace circt::msft {

/// Specify register locations
/// A version of "PDPhysLocationOp" specialized for registers, which have one
/// location per bit.
class PDRegPhysLocationOp;

} // namespace circt::msft
namespace circt::msft {

/// Set the outputs from a PE block
class PEOutputOp;

} // namespace circt::msft
namespace circt::msft {

/// Model of a row/column broadcast systolic array
/// Note: the PE region is NOT a graph region. This was intentional since
/// systolic arrays are entirely feed-forward.
class SystolicArrayOp;

} // namespace circt::msft
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DeclPhysicalRegionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeclPhysicalRegionOpGenericAdaptorBase {
public:
  struct Properties {
    using boundsTy = ::mlir::ArrayAttr;
    boundsTy bounds;

    auto getBounds() const {
      auto &propStorage = this->bounds;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setBounds(const ::mlir::ArrayAttr &propValue) {
      this->bounds = propValue;
    }
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
        rhs.bounds == this->bounds &&
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
  DeclPhysicalRegionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.physical_region", odsAttrs.getContext());
  }

  DeclPhysicalRegionOpGenericAdaptorBase(DeclPhysicalRegionOp op);

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
  ::mlir::ArrayAttr getBoundsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().bounds);
    return attr;
  }

  ::mlir::ArrayAttr getBounds();
};

} // namespace detail
template <typename RangeT>
class DeclPhysicalRegionOpGenericAdaptor : public detail::DeclPhysicalRegionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeclPhysicalRegionOpGenericAdaptorBase;
public:
  DeclPhysicalRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeclPhysicalRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DeclPhysicalRegionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeclPhysicalRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeclPhysicalRegionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeclPhysicalRegionOpGenericAdaptor(RangeT values, const DeclPhysicalRegionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeclPhysicalRegionOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeclPhysicalRegionOp>>>
  DeclPhysicalRegionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DeclPhysicalRegionOpAdaptor : public DeclPhysicalRegionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeclPhysicalRegionOpGenericAdaptor::DeclPhysicalRegionOpGenericAdaptor;
  DeclPhysicalRegionOpAdaptor(DeclPhysicalRegionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeclPhysicalRegionOp : public ::mlir::Op<DeclPhysicalRegionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeclPhysicalRegionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeclPhysicalRegionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bounds"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBoundsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBoundsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.physical_region");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::ArrayAttr getBoundsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().bounds);
  }

  ::mlir::ArrayAttr getBounds();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setBoundsAttr(::mlir::ArrayAttr attr) {
    getProperties().bounds = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclPhysicalRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeclPhysicalRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::DeclPhysicalRegionOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::DeclPhysicalRegionOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DynamicInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DynamicInstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using instanceRefTy = ::circt::hw::InnerRefAttr;
    instanceRefTy instanceRef;

    auto getInstanceRef() const {
      auto &propStorage = this->instanceRef;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setInstanceRef(const ::circt::hw::InnerRefAttr &propValue) {
      this->instanceRef = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.instanceRef == this->instanceRef &&
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
  DynamicInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.instance.dynamic", odsAttrs.getContext());
  }

  DynamicInstanceOpGenericAdaptorBase(DynamicInstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerRefAttr getInstanceRefAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().instanceRef);
    return attr;
  }

  ::circt::hw::InnerRefAttr getInstanceRef();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DynamicInstanceOpGenericAdaptor : public detail::DynamicInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DynamicInstanceOpGenericAdaptorBase;
public:
  DynamicInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DynamicInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DynamicInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DynamicInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DynamicInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DynamicInstanceOpGenericAdaptor(RangeT values, const DynamicInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DynamicInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, DynamicInstanceOp>>>
  DynamicInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DynamicInstanceOpAdaptor : public DynamicInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DynamicInstanceOpGenericAdaptor::DynamicInstanceOpGenericAdaptor;
  DynamicInstanceOpAdaptor(DynamicInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DynamicInstanceOp : public ::mlir::Op<DynamicInstanceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<circt::msft::InstanceHierarchyOp, circt::msft::DynamicInstanceOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DynamicInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DynamicInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("instanceRef")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInstanceRefAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInstanceRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.instance.dynamic");
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

  ::mlir::Region &getBody() {
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
  ::circt::hw::InnerRefAttr getInstanceRefAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().instanceRef);
  }

  ::circt::hw::InnerRefAttr getInstanceRef();
  void setInstanceRefAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().instanceRef = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerRefAttr instanceRef);
  static DynamicInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerRefAttr instanceRef);
  static DynamicInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerRefAttr instanceRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef);
  static DynamicInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef);
  static DynamicInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  ::mlir::ArrayAttr getPath();
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::DynamicInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::DynamicInstanceOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DynamicInstanceVerbatimAttrOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DynamicInstanceVerbatimAttrOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using refTy = ::mlir::FlatSymbolRefAttr;
    refTy ref;

    auto getRef() const {
      auto &propStorage = this->ref;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->ref = propValue;
    }
    using subPathTy = ::mlir::StringAttr;
    subPathTy subPath;

    auto getSubPath() const {
      auto &propStorage = this->subPath;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSubPath(const ::mlir::StringAttr &propValue) {
      this->subPath = propValue;
    }
    using valueTy = ::mlir::StringAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setValue(const ::mlir::StringAttr &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        rhs.ref == this->ref &&
        rhs.subPath == this->subPath &&
        rhs.value == this->value &&
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
  DynamicInstanceVerbatimAttrOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.instance.verb_attr", odsAttrs.getContext());
  }

  DynamicInstanceVerbatimAttrOpGenericAdaptorBase(DynamicInstanceVerbatimAttrOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::StringAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().value);
    return attr;
  }

  ::llvm::StringRef getValue();
  ::mlir::StringAttr getSubPathAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRef();
};

} // namespace detail
template <typename RangeT>
class DynamicInstanceVerbatimAttrOpGenericAdaptor : public detail::DynamicInstanceVerbatimAttrOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DynamicInstanceVerbatimAttrOpGenericAdaptorBase;
public:
  DynamicInstanceVerbatimAttrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DynamicInstanceVerbatimAttrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DynamicInstanceVerbatimAttrOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DynamicInstanceVerbatimAttrOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DynamicInstanceVerbatimAttrOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DynamicInstanceVerbatimAttrOpGenericAdaptor(RangeT values, const DynamicInstanceVerbatimAttrOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DynamicInstanceVerbatimAttrOp, typename = std::enable_if_t<std::is_same_v<LateInst, DynamicInstanceVerbatimAttrOp>>>
  DynamicInstanceVerbatimAttrOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DynamicInstanceVerbatimAttrOpAdaptor : public DynamicInstanceVerbatimAttrOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DynamicInstanceVerbatimAttrOpGenericAdaptor::DynamicInstanceVerbatimAttrOpGenericAdaptor;
  DynamicInstanceVerbatimAttrOpAdaptor(DynamicInstanceVerbatimAttrOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DynamicInstanceVerbatimAttrOp : public ::mlir::Op<DynamicInstanceVerbatimAttrOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::msft::DynInstDataOpInterface::Trait, ::circt::msft::UnaryDynInstDataOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DynamicInstanceVerbatimAttrOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DynamicInstanceVerbatimAttrOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<DynamicInstanceVerbatimAttrOp>::setPathOp;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<DynamicInstanceVerbatimAttrOp>::getPathSym;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("ref"), ::llvm::StringRef("subPath"), ::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSubPathAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSubPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.instance.verb_attr");
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::StringAttr getValueAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().value);
  }

  ::llvm::StringRef getValue();
  ::mlir::StringAttr getSubPathAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
  }

  ::std::optional< ::llvm::StringRef > getRef();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setValueAttr(::mlir::StringAttr attr) {
    getProperties().value = attr;
  }

  void setValue(::llvm::StringRef attrValue);
  void setSubPathAttr(::mlir::StringAttr attr) {
    getProperties().subPath = attr;
  }

  void setSubPath(::std::optional<::llvm::StringRef> attrValue);
  void setRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().ref = attr;
  }

  void setRef(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSubPathAttr() {
      auto attr = getProperties().subPath;
      getProperties().subPath = {};
      return attr;
  }

  ::mlir::Attribute removeRefAttr() {
      auto attr = getProperties().ref;
      getProperties().ref = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicInstanceVerbatimAttrOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DynamicInstanceVerbatimAttrOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Operation* getTopModule(circt::hw::HWSymbolCache &symCache) {
    return getHierPathTopModule(getOperation()->getLoc(), symCache, getPathSym());
  }
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::DynamicInstanceVerbatimAttrOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::DynamicInstanceVerbatimAttrOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::InstanceHierarchyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceHierarchyOpGenericAdaptorBase {
public:
  struct Properties {
    using instNameTy = ::mlir::StringAttr;
    instNameTy instName;

    auto getInstName() const {
      auto &propStorage = this->instName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setInstName(const ::mlir::StringAttr &propValue) {
      this->instName = propValue;
    }
    using topModuleRefTy = ::mlir::FlatSymbolRefAttr;
    topModuleRefTy topModuleRef;

    auto getTopModuleRef() const {
      auto &propStorage = this->topModuleRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setTopModuleRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->topModuleRef = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.instName == this->instName &&
        rhs.topModuleRef == this->topModuleRef &&
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
  InstanceHierarchyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.instance.hierarchy", odsAttrs.getContext());
  }

  InstanceHierarchyOpGenericAdaptorBase(InstanceHierarchyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getTopModuleRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().topModuleRef);
    return attr;
  }

  ::llvm::StringRef getTopModuleRef();
  ::mlir::StringAttr getInstNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().instName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getInstName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class InstanceHierarchyOpGenericAdaptor : public detail::InstanceHierarchyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceHierarchyOpGenericAdaptorBase;
public:
  InstanceHierarchyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InstanceHierarchyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InstanceHierarchyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InstanceHierarchyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InstanceHierarchyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InstanceHierarchyOpGenericAdaptor(RangeT values, const InstanceHierarchyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InstanceHierarchyOp, typename = std::enable_if_t<std::is_same_v<LateInst, InstanceHierarchyOp>>>
  InstanceHierarchyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InstanceHierarchyOpAdaptor : public InstanceHierarchyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InstanceHierarchyOpGenericAdaptor::InstanceHierarchyOpGenericAdaptor;
  InstanceHierarchyOpAdaptor(InstanceHierarchyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InstanceHierarchyOp : public ::mlir::Op<InstanceHierarchyOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceHierarchyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceHierarchyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("instName"), ::llvm::StringRef("topModuleRef")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInstNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInstNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTopModuleRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTopModuleRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.instance.hierarchy");
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

  ::mlir::Region &getBody() {
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
  ::mlir::FlatSymbolRefAttr getTopModuleRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().topModuleRef);
  }

  ::llvm::StringRef getTopModuleRef();
  ::mlir::StringAttr getInstNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().instName);
  }

  ::std::optional< ::llvm::StringRef > getInstName();
  void setTopModuleRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().topModuleRef = attr;
  }

  void setTopModuleRef(::llvm::StringRef attrValue);
  void setInstNameAttr(::mlir::StringAttr attr) {
    getProperties().instName = attr;
  }

  void setInstName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeInstNameAttr() {
      auto attr = getProperties().instName;
      getProperties().instName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceHierarchyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceHierarchyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::InstanceHierarchyOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::InstanceHierarchyOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::LinearOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LinearOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LinearOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.hlc.linear", odsAttrs.getContext());
  }

  LinearOpGenericAdaptorBase(LinearOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getDatapath() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LinearOpGenericAdaptor : public detail::LinearOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LinearOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
public:
  LinearOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LinearOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LinearOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LinearOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LinearOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LinearOpGenericAdaptor(RangeT values, const LinearOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LinearOp, typename = std::enable_if_t<std::is_same_v<LateInst, LinearOp>>>
  LinearOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClock() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LinearOpAdaptor : public LinearOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LinearOpGenericAdaptor::LinearOpGenericAdaptor;
  LinearOpAdaptor(LinearOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LinearOp : public ::mlir::Op<LinearOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<OutputOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LinearOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LinearOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.hlc.linear");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOuts() {
    return getODSResults(0);
  }

  ::mlir::Region &getDatapath() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outs, ::mlir::Value clock);
  static LinearOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outs, ::mlir::Value clock);
  static LinearOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outs, ::mlir::Value clock);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LinearOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LinearOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LinearOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LinearOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  Block *getBodyBlock() { return &getDatapath().front(); }
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::LinearOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::OutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OutputOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.output", odsAttrs.getContext());
  }

  OutputOpGenericAdaptorBase(OutputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class OutputOpGenericAdaptor : public detail::OutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OutputOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OutputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OutputOpGenericAdaptor(RangeT values, const OutputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, OutputOp>>>
  OutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class OutputOpAdaptor : public OutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OutputOpGenericAdaptor::OutputOpGenericAdaptor;
  OutputOpAdaptor(OutputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OutputOp : public ::mlir::Op<OutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::OutputOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDMulticycleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PDMulticycleOpGenericAdaptorBase {
public:
  struct Properties {
    using cyclesTy = ::mlir::IntegerAttr;
    cyclesTy cycles;

    auto getCycles() const {
      auto &propStorage = this->cycles;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCycles(const ::mlir::IntegerAttr &propValue) {
      this->cycles = propValue;
    }
    using destTy = ::mlir::FlatSymbolRefAttr;
    destTy dest;

    auto getDest() const {
      auto &propStorage = this->dest;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setDest(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->dest = propValue;
    }
    using sourceTy = ::mlir::FlatSymbolRefAttr;
    sourceTy source;

    auto getSource() const {
      auto &propStorage = this->source;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setSource(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->source = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.cycles == this->cycles &&
        rhs.dest == this->dest &&
        rhs.source == this->source &&
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
  PDMulticycleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.pd.multicycle", odsAttrs.getContext());
  }

  PDMulticycleOpGenericAdaptorBase(PDMulticycleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getSourceAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().source);
    return attr;
  }

  ::llvm::StringRef getSource();
  ::mlir::FlatSymbolRefAttr getDestAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().dest);
    return attr;
  }

  ::llvm::StringRef getDest();
  ::mlir::IntegerAttr getCyclesAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().cycles);
    return attr;
  }

  uint32_t getCycles();
};

} // namespace detail
template <typename RangeT>
class PDMulticycleOpGenericAdaptor : public detail::PDMulticycleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PDMulticycleOpGenericAdaptorBase;
public:
  PDMulticycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PDMulticycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PDMulticycleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PDMulticycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PDMulticycleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PDMulticycleOpGenericAdaptor(RangeT values, const PDMulticycleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PDMulticycleOp, typename = std::enable_if_t<std::is_same_v<LateInst, PDMulticycleOp>>>
  PDMulticycleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PDMulticycleOpAdaptor : public PDMulticycleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PDMulticycleOpGenericAdaptor::PDMulticycleOpGenericAdaptor;
  PDMulticycleOpAdaptor(PDMulticycleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PDMulticycleOp : public ::mlir::Op<PDMulticycleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::msft::DynInstDataOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PDMulticycleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PDMulticycleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("cycles"), ::llvm::StringRef("dest"), ::llvm::StringRef("source")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCyclesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCyclesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDestAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDestAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSourceAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSourceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.pd.multicycle");
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
  ::mlir::FlatSymbolRefAttr getSourceAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().source);
  }

  ::llvm::StringRef getSource();
  ::mlir::FlatSymbolRefAttr getDestAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().dest);
  }

  ::llvm::StringRef getDest();
  ::mlir::IntegerAttr getCyclesAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().cycles);
  }

  uint32_t getCycles();
  void setSourceAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().source = attr;
  }

  void setSource(::llvm::StringRef attrValue);
  void setDestAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().dest = attr;
  }

  void setDest(::llvm::StringRef attrValue);
  void setCyclesAttr(::mlir::IntegerAttr attr) {
    getProperties().cycles = attr;
  }

  void setCycles(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDMulticycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDMulticycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  Operation *getTopModule(circt::hw::HWSymbolCache &symCache);
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
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PDMulticycleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDMulticycleOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDPhysLocationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PDPhysLocationOpGenericAdaptorBase {
public:
  struct Properties {
    using locTy = ::circt::msft::PhysLocationAttr;
    locTy loc;

    auto getLoc() const {
      auto &propStorage = this->loc;
      return ::llvm::cast<::circt::msft::PhysLocationAttr>(propStorage);
    }
    void setLoc(const ::circt::msft::PhysLocationAttr &propValue) {
      this->loc = propValue;
    }
    using refTy = ::mlir::FlatSymbolRefAttr;
    refTy ref;

    auto getRef() const {
      auto &propStorage = this->ref;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->ref = propValue;
    }
    using subPathTy = ::mlir::StringAttr;
    subPathTy subPath;

    auto getSubPath() const {
      auto &propStorage = this->subPath;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSubPath(const ::mlir::StringAttr &propValue) {
      this->subPath = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.loc == this->loc &&
        rhs.ref == this->ref &&
        rhs.subPath == this->subPath &&
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
  PDPhysLocationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.pd.location", odsAttrs.getContext());
  }

  PDPhysLocationOpGenericAdaptorBase(PDPhysLocationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::msft::PhysLocationAttr getLocAttr() {
    auto attr = ::llvm::cast<::circt::msft::PhysLocationAttr>(getProperties().loc);
    return attr;
  }

  ::circt::msft::PhysLocationAttr getLoc();
  ::mlir::StringAttr getSubPathAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRef();
};

} // namespace detail
template <typename RangeT>
class PDPhysLocationOpGenericAdaptor : public detail::PDPhysLocationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PDPhysLocationOpGenericAdaptorBase;
public:
  PDPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PDPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PDPhysLocationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PDPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PDPhysLocationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PDPhysLocationOpGenericAdaptor(RangeT values, const PDPhysLocationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PDPhysLocationOp, typename = std::enable_if_t<std::is_same_v<LateInst, PDPhysLocationOp>>>
  PDPhysLocationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PDPhysLocationOpAdaptor : public PDPhysLocationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PDPhysLocationOpGenericAdaptor::PDPhysLocationOpGenericAdaptor;
  PDPhysLocationOpAdaptor(PDPhysLocationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PDPhysLocationOp : public ::mlir::Op<PDPhysLocationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::msft::DynInstDataOpInterface::Trait, ::circt::msft::UnaryDynInstDataOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PDPhysLocationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PDPhysLocationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDPhysLocationOp>::setPathOp;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDPhysLocationOp>::getPathSym;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("loc"), ::llvm::StringRef("ref"), ::llvm::StringRef("subPath")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLocAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLocAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSubPathAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSubPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.pd.location");
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
  ::circt::msft::PhysLocationAttr getLocAttr() {
    return ::llvm::cast<::circt::msft::PhysLocationAttr>(getProperties().loc);
  }

  ::circt::msft::PhysLocationAttr getLoc();
  ::mlir::StringAttr getSubPathAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
  }

  ::std::optional< ::llvm::StringRef > getRef();
  void setLocAttr(::circt::msft::PhysLocationAttr attr) {
    getProperties().loc = attr;
  }

  void setSubPathAttr(::mlir::StringAttr attr) {
    getProperties().subPath = attr;
  }

  void setSubPath(::std::optional<::llvm::StringRef> attrValue);
  void setRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().ref = attr;
  }

  void setRef(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSubPathAttr() {
      auto attr = getProperties().subPath;
      getProperties().subPath = {};
      return attr;
  }

  ::mlir::Attribute removeRefAttr() {
      auto attr = getProperties().ref;
      getProperties().ref = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  Operation* getTopModule(circt::hw::HWSymbolCache &symCache) {
    return getHierPathTopModule(getOperation()->getLoc(), symCache, getPathSym());
  }
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PDPhysLocationOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDPhysLocationOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDPhysRegionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PDPhysRegionOpGenericAdaptorBase {
public:
  struct Properties {
    using physRegionRefTy = ::mlir::FlatSymbolRefAttr;
    physRegionRefTy physRegionRef;

    auto getPhysRegionRef() const {
      auto &propStorage = this->physRegionRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setPhysRegionRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->physRegionRef = propValue;
    }
    using refTy = ::mlir::FlatSymbolRefAttr;
    refTy ref;

    auto getRef() const {
      auto &propStorage = this->ref;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->ref = propValue;
    }
    using subPathTy = ::mlir::StringAttr;
    subPathTy subPath;

    auto getSubPath() const {
      auto &propStorage = this->subPath;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSubPath(const ::mlir::StringAttr &propValue) {
      this->subPath = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.physRegionRef == this->physRegionRef &&
        rhs.ref == this->ref &&
        rhs.subPath == this->subPath &&
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
  PDPhysRegionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.pd.physregion", odsAttrs.getContext());
  }

  PDPhysRegionOpGenericAdaptorBase(PDPhysRegionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getPhysRegionRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().physRegionRef);
    return attr;
  }

  ::llvm::StringRef getPhysRegionRef();
  ::mlir::StringAttr getSubPathAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRef();
};

} // namespace detail
template <typename RangeT>
class PDPhysRegionOpGenericAdaptor : public detail::PDPhysRegionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PDPhysRegionOpGenericAdaptorBase;
public:
  PDPhysRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PDPhysRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PDPhysRegionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PDPhysRegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PDPhysRegionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PDPhysRegionOpGenericAdaptor(RangeT values, const PDPhysRegionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PDPhysRegionOp, typename = std::enable_if_t<std::is_same_v<LateInst, PDPhysRegionOp>>>
  PDPhysRegionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PDPhysRegionOpAdaptor : public PDPhysRegionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PDPhysRegionOpGenericAdaptor::PDPhysRegionOpGenericAdaptor;
  PDPhysRegionOpAdaptor(PDPhysRegionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PDPhysRegionOp : public ::mlir::Op<PDPhysRegionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::msft::DynInstDataOpInterface::Trait, ::circt::msft::UnaryDynInstDataOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PDPhysRegionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PDPhysRegionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDPhysRegionOp>::setPathOp;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDPhysRegionOp>::getPathSym;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("physRegionRef"), ::llvm::StringRef("ref"), ::llvm::StringRef("subPath")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPhysRegionRefAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPhysRegionRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSubPathAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSubPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.pd.physregion");
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
  ::mlir::FlatSymbolRefAttr getPhysRegionRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().physRegionRef);
  }

  ::llvm::StringRef getPhysRegionRef();
  ::mlir::StringAttr getSubPathAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().subPath);
  }

  ::std::optional< ::llvm::StringRef > getSubPath();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
  }

  ::std::optional< ::llvm::StringRef > getRef();
  void setPhysRegionRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().physRegionRef = attr;
  }

  void setPhysRegionRef(::llvm::StringRef attrValue);
  void setSubPathAttr(::mlir::StringAttr attr) {
    getProperties().subPath = attr;
  }

  void setSubPath(::std::optional<::llvm::StringRef> attrValue);
  void setRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().ref = attr;
  }

  void setRef(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSubPathAttr() {
      auto attr = getProperties().subPath;
      getProperties().subPath = {};
      return attr;
  }

  ::mlir::Attribute removeRefAttr() {
      auto attr = getProperties().ref;
      getProperties().ref = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDPhysRegionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDPhysRegionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  Operation* getTopModule(circt::hw::HWSymbolCache &symCache) {
    return getHierPathTopModule(getOperation()->getLoc(), symCache, getPathSym());
  }
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PDPhysRegionOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDPhysRegionOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDRegPhysLocationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PDRegPhysLocationOpGenericAdaptorBase {
public:
  struct Properties {
    using locsTy = ::circt::msft::LocationVectorAttr;
    locsTy locs;

    auto getLocs() const {
      auto &propStorage = this->locs;
      return ::llvm::cast<::circt::msft::LocationVectorAttr>(propStorage);
    }
    void setLocs(const ::circt::msft::LocationVectorAttr &propValue) {
      this->locs = propValue;
    }
    using refTy = ::mlir::FlatSymbolRefAttr;
    refTy ref;

    auto getRef() const {
      auto &propStorage = this->ref;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->ref = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.locs == this->locs &&
        rhs.ref == this->ref &&
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
  PDRegPhysLocationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.pd.reg_location", odsAttrs.getContext());
  }

  PDRegPhysLocationOpGenericAdaptorBase(PDRegPhysLocationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::msft::LocationVectorAttr getLocsAttr() {
    auto attr = ::llvm::cast<::circt::msft::LocationVectorAttr>(getProperties().locs);
    return attr;
  }

  ::circt::msft::LocationVectorAttr getLocs();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRef();
};

} // namespace detail
template <typename RangeT>
class PDRegPhysLocationOpGenericAdaptor : public detail::PDRegPhysLocationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PDRegPhysLocationOpGenericAdaptorBase;
public:
  PDRegPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PDRegPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PDRegPhysLocationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PDRegPhysLocationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PDRegPhysLocationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PDRegPhysLocationOpGenericAdaptor(RangeT values, const PDRegPhysLocationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PDRegPhysLocationOp, typename = std::enable_if_t<std::is_same_v<LateInst, PDRegPhysLocationOp>>>
  PDRegPhysLocationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PDRegPhysLocationOpAdaptor : public PDRegPhysLocationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PDRegPhysLocationOpGenericAdaptor::PDRegPhysLocationOpGenericAdaptor;
  PDRegPhysLocationOpAdaptor(PDRegPhysLocationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PDRegPhysLocationOp : public ::mlir::Op<PDRegPhysLocationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::msft::DynInstDataOpInterface::Trait, ::circt::msft::UnaryDynInstDataOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PDRegPhysLocationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PDRegPhysLocationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDRegPhysLocationOp>::setPathOp;
  using ::circt::msft::UnaryDynInstDataOpInterface::Trait<PDRegPhysLocationOp>::getPathSym;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("locs"), ::llvm::StringRef("ref")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLocsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLocsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.pd.reg_location");
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
  ::circt::msft::LocationVectorAttr getLocsAttr() {
    return ::llvm::cast<::circt::msft::LocationVectorAttr>(getProperties().locs);
  }

  ::circt::msft::LocationVectorAttr getLocs();
  ::mlir::FlatSymbolRefAttr getRefAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().ref);
  }

  ::std::optional< ::llvm::StringRef > getRef();
  void setLocsAttr(::circt::msft::LocationVectorAttr attr) {
    getProperties().locs = attr;
  }

  void setRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().ref = attr;
  }

  void setRef(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeRefAttr() {
      auto attr = getProperties().ref;
      getProperties().ref = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDRegPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDRegPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDRegPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static PDRegPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDRegPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PDRegPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDRegPhysLocationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PDRegPhysLocationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  Operation* getTopModule(circt::hw::HWSymbolCache &symCache) {
    return getHierPathTopModule(getOperation()->getLoc(), symCache, getPathSym());
  }
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PDRegPhysLocationOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDRegPhysLocationOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PEOutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PEOutputOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PEOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.pe.output", odsAttrs.getContext());
  }

  PEOutputOpGenericAdaptorBase(PEOutputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class PEOutputOpGenericAdaptor : public detail::PEOutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PEOutputOpGenericAdaptorBase;
  static constexpr int odsIndex_output = 0;
public:
  PEOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PEOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PEOutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PEOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PEOutputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PEOutputOpGenericAdaptor(RangeT values, const PEOutputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PEOutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, PEOutputOp>>>
  PEOutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getOutput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PEOutputOpAdaptor : public PEOutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PEOutputOpGenericAdaptor::PEOutputOpGenericAdaptor;
  PEOutputOpAdaptor(PEOutputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PEOutputOp : public ::mlir::Op<PEOutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PEOutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PEOutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_output = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.pe.output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getOutputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value output);
  static PEOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value output);
  static PEOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value output);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value output);
  static PEOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value output);
  static PEOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value output);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PEOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PEOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PEOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PEOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::PEOutputOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::SystolicArrayOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SystolicArrayOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SystolicArrayOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("msft.systolic.array", odsAttrs.getContext());
  }

  SystolicArrayOpGenericAdaptorBase(SystolicArrayOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getPe() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SystolicArrayOpGenericAdaptor : public detail::SystolicArrayOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SystolicArrayOpGenericAdaptorBase;
  static constexpr int odsIndex_rowInputs = 0;
  static constexpr int odsIndex_colInputs = 1;
public:
  SystolicArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SystolicArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SystolicArrayOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SystolicArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SystolicArrayOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SystolicArrayOpGenericAdaptor(RangeT values, const SystolicArrayOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SystolicArrayOp, typename = std::enable_if_t<std::is_same_v<LateInst, SystolicArrayOp>>>
  SystolicArrayOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRowInputs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getColInputs() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SystolicArrayOpAdaptor : public SystolicArrayOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SystolicArrayOpGenericAdaptor::SystolicArrayOpGenericAdaptor;
  SystolicArrayOpAdaptor(SystolicArrayOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SystolicArrayOp : public ::mlir::Op<SystolicArrayOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<hw::TypeAliasOr<hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<PEOutputOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SystolicArrayOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SystolicArrayOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rowInputs = 0;
  static constexpr int odsIndex_colInputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("msft.systolic.array");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getRowInputs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getColInputs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRowInputsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getColInputsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<hw::TypeAliasOr<hw::ArrayType>> getPeOutputs() {
    return ::llvm::cast<::mlir::TypedValue<hw::TypeAliasOr<hw::ArrayType>>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getPe() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static SystolicArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static SystolicArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static SystolicArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static SystolicArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SystolicArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SystolicArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SystolicArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SystolicArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::msft
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::msft::SystolicArrayOp)


#endif // GET_OP_CLASSES

