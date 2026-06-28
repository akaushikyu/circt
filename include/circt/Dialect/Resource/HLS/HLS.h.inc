/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HLS.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hls_analysis {

/// Affine-level predicated store; commits iff $condition holds.
/// Writes $value to $memref at affine $map applied to $mapOperands, but only
/// when the integer set $condition (applied to $setOperands) is satisfied.
/// The predicate is an affine_set, so the guard stays in the affine domain
/// and MemoryDependenceAnalysis treats this as a real affine write -- giving
/// it dependence edges automatically (no manual anchoring), and exposing
/// loop-carried dependences for predicated accumulation.
/// 
/// Lowers to hls.store_enable: $condition is materialized to i1, $map is
/// expanded to index SSA values.
class AffineStoreEnableOp;

} // namespace circt::hls_analysis
namespace circt::hls_analysis {

/// Predicated memref store; commits only when $enable is true.
/// A flat, region-free conditional store. Writes $value to
/// $memref[$indices] iff $enable holds at runtime. Models a BRAM write port
/// whose write-enable line is driven by $enable
/// 
/// Carries an *unconditional* Write memory effect: the predicate is an
/// operand, not an effect. This is deliberate and conservative --
///   * the scheduler reserves the write port in every cycle the op could
///     fire (correct for an enable that may be true any iteration), and
///   * the BRAM estimator, walking memory effects, sees exactly one write
///     and zero reads, so a bank written only through store_enable infers
///     RAM_1P instead of the RAM_2P that the RMW demux wrongly forced.
/// 
/// Example:
///   hls.store_enable %v, %en, %bank[%i] : memref<256xi32>
class StoreEnableOp;

} // namespace circt::hls_analysis
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::hls_analysis {


//===----------------------------------------------------------------------===//
// circt::hls_analysis::AffineStoreEnableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AffineStoreEnableOpGenericAdaptorBase {
public:
  struct Properties {
    using conditionTy = ::mlir::IntegerSetAttr;
    conditionTy condition;

    auto getCondition() const {
      auto &propStorage = this->condition;
      return ::llvm::cast<::mlir::IntegerSetAttr>(propStorage);
    }
    void setCondition(const ::mlir::IntegerSetAttr &propValue) {
      this->condition = propValue;
    }
    using mapTy = ::mlir::AffineMapAttr;
    mapTy map;

    auto getMap() const {
      auto &propStorage = this->map;
      return ::llvm::cast<::mlir::AffineMapAttr>(propStorage);
    }
    void setMap(const ::mlir::AffineMapAttr &propValue) {
      this->map = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 4>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.condition == this->condition &&
        rhs.map == this->map &&
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
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
  AffineStoreEnableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hls.affine.store_enable", odsAttrs.getContext());
  }

  AffineStoreEnableOpGenericAdaptorBase(AffineStoreEnableOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::AffineMapAttr getMapAttr() {
    auto attr = ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
    return attr;
  }

  ::mlir::AffineMap getMap();
  ::mlir::IntegerSetAttr getConditionAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerSetAttr>(getProperties().condition);
    return attr;
  }

  ::mlir::IntegerSet getCondition();
};

} // namespace detail
template <typename RangeT>
class AffineStoreEnableOpGenericAdaptor : public detail::AffineStoreEnableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AffineStoreEnableOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_mapOperands = 2;
  static constexpr int odsIndex_setOperands = 3;
public:
  AffineStoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AffineStoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AffineStoreEnableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AffineStoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : AffineStoreEnableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AffineStoreEnableOpGenericAdaptor(RangeT values, const AffineStoreEnableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AffineStoreEnableOp, typename = std::enable_if_t<std::is_same_v<LateInst, AffineStoreEnableOp>>>
  AffineStoreEnableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMemref() {
    return (*getODSOperands(1).begin());
  }

  RangeT getMapOperands() {
    return getODSOperands(2);
  }

  RangeT getSetOperands() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AffineStoreEnableOpAdaptor : public AffineStoreEnableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AffineStoreEnableOpGenericAdaptor::AffineStoreEnableOpGenericAdaptor;
  AffineStoreEnableOpAdaptor(AffineStoreEnableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AffineStoreEnableOp : public ::mlir::Op<AffineStoreEnableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::affine::AffineWriteOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AffineStoreEnableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AffineStoreEnableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_memref = 1;
  static constexpr int odsIndex_mapOperands = 2;
  static constexpr int odsIndex_setOperands = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreEnableOp>::getMemRef;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreEnableOp>::getMemRefType;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreEnableOp>::getAffineMap;
  using ::mlir::affine::AffineWriteOpInterface::Trait<AffineStoreEnableOp>::getValueToStore;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("condition"), ::llvm::StringRef("map"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConditionAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConditionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMapAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hls.affine.store_enable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::Operation::operand_range getMapOperands() {
    return getODSOperands(2);
  }

  ::mlir::Operation::operand_range getSetOperands() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMapOperandsMutable();
  ::mlir::MutableOperandRange getSetOperandsMutable();
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
  ::mlir::AffineMapAttr getMapAttr() {
    return ::llvm::cast<::mlir::AffineMapAttr>(getProperties().map);
  }

  ::mlir::AffineMap getMap();
  ::mlir::IntegerSetAttr getConditionAttr() {
    return ::llvm::cast<::mlir::IntegerSetAttr>(getProperties().condition);
  }

  ::mlir::IntegerSet getCondition();
  void setMapAttr(::mlir::AffineMapAttr attr) {
    getProperties().map = attr;
  }

  void setMap(::mlir::AffineMap attrValue);
  void setConditionAttr(::mlir::IntegerSetAttr attr) {
    getProperties().condition = attr;
  }

  void setCondition(::mlir::IntegerSet attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMapAttr map, ::mlir::IntegerSetAttr condition);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value memref, ::mlir::ValueRange mapOperands, ::mlir::ValueRange setOperands, ::mlir::AffineMap map, ::mlir::IntegerSet condition);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineStoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AffineStoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  // Primitives the AffineWriteOpInterface defaults invoke.
  unsigned getMemRefOperandIndex()    { return 1; } // operand 1 = memref
  unsigned getStoredValOperandIndex() { return 0; } // operand 0 = value
  ::mlir::AffineMapAttr getAffineMapAttr() { return getMapAttr(); }
};

} // namespace circt::hls_analysis
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::AffineStoreEnableOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::detail::AffineStoreEnableOpGenericAdaptorBase::Properties)

namespace circt::hls_analysis {


//===----------------------------------------------------------------------===//
// circt::hls_analysis::StoreEnableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StoreEnableOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StoreEnableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hls.store_enable", odsAttrs.getContext());
  }

  StoreEnableOpGenericAdaptorBase(StoreEnableOp op);

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
class StoreEnableOpGenericAdaptor : public detail::StoreEnableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StoreEnableOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_memref = 2;
  static constexpr int odsIndex_indices = 3;
public:
  StoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StoreEnableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StoreEnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StoreEnableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StoreEnableOpGenericAdaptor(RangeT values, const StoreEnableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StoreEnableOp, typename = std::enable_if_t<std::is_same_v<LateInst, StoreEnableOp>>>
  StoreEnableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMemref() {
    return (*getODSOperands(2).begin());
  }

  RangeT getIndices() {
    return getODSOperands(3);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StoreEnableOpAdaptor : public StoreEnableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StoreEnableOpGenericAdaptor::StoreEnableOpGenericAdaptor;
  StoreEnableOpAdaptor(StoreEnableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StoreEnableOp : public ::mlir::Op<StoreEnableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StoreEnableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StoreEnableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_memref = 2;
  static constexpr int odsIndex_indices = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hls.store_enable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getMemref() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::Operation::operand_range getIndices() {
    return getODSOperands(3);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getEnableMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemrefMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getIndicesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static StoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static StoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static StoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static StoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::Value enable, ::mlir::Value memref, ::mlir::ValueRange indices);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreEnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StoreEnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::hls_analysis
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::StoreEnableOp)


#endif // GET_OP_CLASSES

