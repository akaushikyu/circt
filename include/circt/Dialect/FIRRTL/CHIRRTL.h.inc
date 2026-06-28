/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: CHIRRTL.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::chirrtl {

/// Define a new combinational memory
/// Define a new behavioral combinational memory. Combinational memories have a
/// write latency of 1 and a read latency of 0.
class CombMemOp;

} // namespace circt::chirrtl
namespace circt::chirrtl {

/// Defines a debug memory port on CHIRRTL memory
/// This operation defines a new debug memory port on a `combmem`CHISEL.
/// `data` is the data returned from the memory port.
class MemoryDebugPortOp;

} // namespace circt::chirrtl
namespace circt::chirrtl {

/// Enables a memory port
/// This operation is used to conditionally enable a memory port, and associate
/// it with a `clock` and `index`.  The memory port will be actuve on the
/// positive edge of the clock. The index is the address of the memory
/// accessed. See the FIRRTL rational for more information about why this
/// operation exists.
class MemoryPortAccessOp;

} // namespace circt::chirrtl
namespace circt::chirrtl {

/// Defines a memory port on CHIRRTL memory
/// This operation defines a new memory port on a `seqmem` or `combmem`CHISEL.
/// `data` is the data returned from the memory port.
/// 
/// The memory port requires an access point, which sets the enable condition
/// of the port, the clock, and the address.  This is done by passing the the
/// `port` argument to a `chirrtl.memoryport.access operation`.
class MemoryPortOp;

} // namespace circt::chirrtl
namespace circt::chirrtl {

/// Define a new sequential memory
/// Define a new behavioral sequential memory.  Sequential memories have a
/// write latency and a read latency of 1.
class SeqMemOp;

} // namespace circt::chirrtl
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::CombMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CombMemOpGenericAdaptorBase {
public:
  struct Properties {
    using annotationsTy = ::mlir::ArrayAttr;
    annotationsTy annotations;

    auto getAnnotations() const {
      auto &propStorage = this->annotations;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAnnotations(const ::mlir::ArrayAttr &propValue) {
      this->annotations = propValue;
    }
    using initTy = ::circt::firrtl::MemoryInitAttr;
    initTy init;

    auto getInit() const {
      auto &propStorage = this->init;
      return ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(propStorage);
    }
    void setInit(const ::circt::firrtl::MemoryInitAttr &propValue) {
      this->init = propValue;
    }
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using nameKindTy = ::circt::firrtl::NameKindEnumAttr;
    nameKindTy nameKind;

    auto getNameKind() const {
      auto &propStorage = this->nameKind;
      return ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(propStorage);
    }
    void setNameKind(const ::circt::firrtl::NameKindEnumAttr &propValue) {
      this->nameKind = propValue;
    }
    using prefixTy = ::mlir::StringAttr;
    prefixTy prefix;

    auto getPrefix() const {
      auto &propStorage = this->prefix;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setPrefix(const ::mlir::StringAttr &propValue) {
      this->prefix = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.annotations == this->annotations &&
        rhs.init == this->init &&
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.nameKind == this->nameKind &&
        rhs.prefix == this->prefix &&
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
  CombMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("chirrtl.combmem", odsAttrs.getContext());
  }

  CombMemOpGenericAdaptorBase(CombMemOp op);

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
  ::circt::firrtl::NameKindEnumAttr getNameKindAttr() {
    auto attr = ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(getProperties().nameKind);
    return attr;
  }

  ::circt::firrtl::NameKindEnum getNameKind();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
    return attr;
  }

  ::mlir::ArrayAttr getAnnotations();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::firrtl::MemoryInitAttr getInitAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(getProperties().init);
    return attr;
  }

  ::std::optional<::circt::firrtl::MemoryInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
};

} // namespace detail
template <typename RangeT>
class CombMemOpGenericAdaptor : public detail::CombMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CombMemOpGenericAdaptorBase;
public:
  CombMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CombMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CombMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CombMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CombMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CombMemOpGenericAdaptor(RangeT values, const CombMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CombMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, CombMemOp>>>
  CombMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CombMemOpAdaptor : public CombMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CombMemOpGenericAdaptor::CombMemOpGenericAdaptor;
  CombMemOpAdaptor(CombMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CombMemOp : public ::mlir::Op<CombMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::chirrtl::CMemoryType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::circt::firrtl::FNamableOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CombMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CombMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<CombMemOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CombMemOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CombMemOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CombMemOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("annotations"), ::llvm::StringRef("init"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("nameKind"), ::llvm::StringRef("prefix")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAnnotationsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAnnotationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getNameKindAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getNameKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrefixAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrefixAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("chirrtl.combmem");
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

  ::mlir::TypedValue<::circt::chirrtl::CMemoryType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryType>>(*getODSResults(0).begin());
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
  ::circt::firrtl::NameKindEnumAttr getNameKindAttr() {
    return ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(getProperties().nameKind);
  }

  ::circt::firrtl::NameKindEnum getNameKind();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
  }

  ::mlir::ArrayAttr getAnnotations();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::firrtl::MemoryInitAttr getInitAttr() {
    return ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(getProperties().init);
  }

  ::std::optional<::circt::firrtl::MemoryInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setNameKindAttr(::circt::firrtl::NameKindEnumAttr attr) {
    getProperties().nameKind = attr;
  }

  void setNameKind(::circt::firrtl::NameKindEnum attrValue);
  void setAnnotationsAttr(::mlir::ArrayAttr attr) {
    getProperties().annotations = attr;
  }

  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setInitAttr(::circt::firrtl::MemoryInitAttr attr) {
    getProperties().init = attr;
  }

  void setPrefixAttr(::mlir::StringAttr attr) {
    getProperties().prefix = attr;
  }

  void setPrefix(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  ::mlir::Attribute removeInitAttr() {
      auto attr = getProperties().init;
      getProperties().init = {};
      return attr;
  }

  ::mlir::Attribute removePrefixAttr() {
      auto attr = getProperties().prefix;
      getProperties().prefix = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, firrtl::FIRRTLBaseType elementType, uint64_t numElements, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, firrtl::FIRRTLBaseType elementType, uint64_t numElements, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, firrtl::FIRRTLBaseType elementType, uint64_t numElements, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CombMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CombMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::CombMemOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::CombMemOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryDebugPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryDebugPortOpGenericAdaptorBase {
public:
  struct Properties {
    using annotationsTy = ::mlir::ArrayAttr;
    annotationsTy annotations;

    auto getAnnotations() const {
      auto &propStorage = this->annotations;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAnnotations(const ::mlir::ArrayAttr &propValue) {
      this->annotations = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.annotations == this->annotations &&
        rhs.name == this->name &&
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
  MemoryDebugPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("chirrtl.debugport", odsAttrs.getContext());
  }

  MemoryDebugPortOpGenericAdaptorBase(MemoryDebugPortOp op);

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
  ::mlir::ArrayAttr getAnnotationsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
    return attr;
  }

  ::mlir::ArrayAttr getAnnotations();
};

} // namespace detail
template <typename RangeT>
class MemoryDebugPortOpGenericAdaptor : public detail::MemoryDebugPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryDebugPortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
public:
  MemoryDebugPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryDebugPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryDebugPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryDebugPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryDebugPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryDebugPortOpGenericAdaptor(RangeT values, const MemoryDebugPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryDebugPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryDebugPortOp>>>
  MemoryDebugPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryDebugPortOpAdaptor : public MemoryDebugPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryDebugPortOpGenericAdaptor::MemoryDebugPortOpGenericAdaptor;
  MemoryDebugPortOpAdaptor(MemoryDebugPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryDebugPortOp : public ::mlir::Op<MemoryDebugPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::firrtl::RefType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryDebugPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryDebugPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<MemoryDebugPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryDebugPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryDebugPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("annotations"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAnnotationsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAnnotationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("chirrtl.debugport");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::chirrtl::CMemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
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

  ::mlir::TypedValue<::circt::firrtl::RefType> getData() {
    return ::llvm::cast<::mlir::TypedValue<::circt::firrtl::RefType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getAnnotationsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
  }

  ::mlir::ArrayAttr getAnnotations();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setAnnotationsAttr(::mlir::ArrayAttr attr) {
    getProperties().annotations = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dataType, ::mlir::Value memory, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataType, ::mlir::Value memory, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataType, ::mlir::Value memory, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryDebugPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryDebugPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results);
};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryDebugPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::MemoryDebugPortOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryPortAccessOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryPortAccessOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MemoryPortAccessOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("chirrtl.memoryport.access", odsAttrs.getContext());
  }

  MemoryPortAccessOpGenericAdaptorBase(MemoryPortAccessOp op);

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
class MemoryPortAccessOpGenericAdaptor : public detail::MemoryPortAccessOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryPortAccessOpGenericAdaptorBase;
  static constexpr int odsIndex_port = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_clock = 2;
public:
  MemoryPortAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryPortAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryPortAccessOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryPortAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryPortAccessOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryPortAccessOpGenericAdaptor(RangeT values, const MemoryPortAccessOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryPortAccessOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryPortAccessOp>>>
  MemoryPortAccessOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPort() {
    return (*getODSOperands(0).begin());
  }

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClock() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryPortAccessOpAdaptor : public MemoryPortAccessOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryPortAccessOpGenericAdaptor::MemoryPortAccessOpGenericAdaptor;
  MemoryPortAccessOpAdaptor(MemoryPortAccessOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryPortAccessOp : public ::mlir::Op<MemoryPortAccessOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryPortAccessOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryPortAccessOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_port = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_clock = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("chirrtl.memoryport.access");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::chirrtl::CMemoryPortType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryPortType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::firrtl::BaseTypeAliasOr<::circt::firrtl::IntType>> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::circt::firrtl::BaseTypeAliasOr<::circt::firrtl::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::firrtl::BaseTypeAliasOr<::circt::firrtl::ClockType>> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::firrtl::BaseTypeAliasOr<::circt::firrtl::ClockType>>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getPortMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(2);
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static MemoryPortAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static MemoryPortAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static MemoryPortAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static MemoryPortAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryPortAccessOp)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryPortOpGenericAdaptorBase {
public:
  struct Properties {
    using annotationsTy = ::mlir::ArrayAttr;
    annotationsTy annotations;

    auto getAnnotations() const {
      auto &propStorage = this->annotations;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAnnotations(const ::mlir::ArrayAttr &propValue) {
      this->annotations = propValue;
    }
    using directionTy = ::circt::firrtl::MemDirAttrAttr;
    directionTy direction;

    auto getDirection() const {
      auto &propStorage = this->direction;
      return ::llvm::cast<::circt::firrtl::MemDirAttrAttr>(propStorage);
    }
    void setDirection(const ::circt::firrtl::MemDirAttrAttr &propValue) {
      this->direction = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.annotations == this->annotations &&
        rhs.direction == this->direction &&
        rhs.name == this->name &&
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
  MemoryPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("chirrtl.memoryport", odsAttrs.getContext());
  }

  MemoryPortOpGenericAdaptorBase(MemoryPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::firrtl::MemDirAttrAttr getDirectionAttr() {
    auto attr = ::llvm::cast<::circt::firrtl::MemDirAttrAttr>(getProperties().direction);
    return attr;
  }

  ::circt::firrtl::MemDirAttr getDirection();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
    return attr;
  }

  ::mlir::ArrayAttr getAnnotations();
};

} // namespace detail
template <typename RangeT>
class MemoryPortOpGenericAdaptor : public detail::MemoryPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryPortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
public:
  MemoryPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryPortOpGenericAdaptor(RangeT values, const MemoryPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryPortOp>>>
  MemoryPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemoryPortOpAdaptor : public MemoryPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryPortOpGenericAdaptor::MemoryPortOpGenericAdaptor;
  MemoryPortOpAdaptor(MemoryPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryPortOp : public ::mlir::Op<MemoryPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<MemoryPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("annotations"), ::llvm::StringRef("direction"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAnnotationsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAnnotationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDirectionAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDirectionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("chirrtl.memoryport");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::chirrtl::CMemoryType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
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

  ::mlir::TypedValue<::circt::firrtl::FIRRTLBaseType> getData() {
    return ::llvm::cast<::mlir::TypedValue<::circt::firrtl::FIRRTLBaseType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::circt::chirrtl::CMemoryPortType> getPort() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryPortType>>(*getODSResults(1).begin());
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
  ::circt::firrtl::MemDirAttrAttr getDirectionAttr() {
    return ::llvm::cast<::circt::firrtl::MemDirAttrAttr>(getProperties().direction);
  }

  ::circt::firrtl::MemDirAttr getDirection();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
  }

  ::mlir::ArrayAttr getAnnotations();
  void setDirectionAttr(::circt::firrtl::MemDirAttrAttr attr) {
    getProperties().direction = attr;
  }

  void setDirection(::circt::firrtl::MemDirAttr attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setAnnotationsAttr(::mlir::ArrayAttr attr) {
    getProperties().annotations = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dataType, ::mlir::Value memory, firrtl::MemDirAttr direction, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataType, ::mlir::Value memory, firrtl::MemDirAttr direction, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataType, ::mlir::Value memory, firrtl::MemDirAttr direction, StringRef name = {}, ArrayRef<Attribute> annotations = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemoryPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  /// Get the assocated access op.
  MemoryPortAccessOp getAccess();

  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results);
};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::MemoryPortOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::SeqMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SeqMemOpGenericAdaptorBase {
public:
  struct Properties {
    using annotationsTy = ::mlir::ArrayAttr;
    annotationsTy annotations;

    auto getAnnotations() const {
      auto &propStorage = this->annotations;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAnnotations(const ::mlir::ArrayAttr &propValue) {
      this->annotations = propValue;
    }
    using initTy = ::circt::firrtl::MemoryInitAttr;
    initTy init;

    auto getInit() const {
      auto &propStorage = this->init;
      return ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(propStorage);
    }
    void setInit(const ::circt::firrtl::MemoryInitAttr &propValue) {
      this->init = propValue;
    }
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using nameKindTy = ::circt::firrtl::NameKindEnumAttr;
    nameKindTy nameKind;

    auto getNameKind() const {
      auto &propStorage = this->nameKind;
      return ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(propStorage);
    }
    void setNameKind(const ::circt::firrtl::NameKindEnumAttr &propValue) {
      this->nameKind = propValue;
    }
    using prefixTy = ::mlir::StringAttr;
    prefixTy prefix;

    auto getPrefix() const {
      auto &propStorage = this->prefix;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setPrefix(const ::mlir::StringAttr &propValue) {
      this->prefix = propValue;
    }
    using ruwTy = ::circt::firrtl::RUWBehaviorAttr;
    ruwTy ruw;

    auto getRuw() const {
      auto &propStorage = this->ruw;
      return ::llvm::cast<::circt::firrtl::RUWBehaviorAttr>(propStorage);
    }
    void setRuw(const ::circt::firrtl::RUWBehaviorAttr &propValue) {
      this->ruw = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.annotations == this->annotations &&
        rhs.init == this->init &&
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.nameKind == this->nameKind &&
        rhs.prefix == this->prefix &&
        rhs.ruw == this->ruw &&
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
  SeqMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("chirrtl.seqmem", odsAttrs.getContext());
  }

  SeqMemOpGenericAdaptorBase(SeqMemOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::firrtl::RUWBehaviorAttr getRuwAttr() {
    auto attr = ::llvm::cast<::circt::firrtl::RUWBehaviorAttr>(getProperties().ruw);
    return attr;
  }

  ::circt::firrtl::RUWBehavior getRuw();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::circt::firrtl::NameKindEnumAttr getNameKindAttr() {
    auto attr = ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(getProperties().nameKind);
    return attr;
  }

  ::circt::firrtl::NameKindEnum getNameKind();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
    return attr;
  }

  ::mlir::ArrayAttr getAnnotations();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::firrtl::MemoryInitAttr getInitAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(getProperties().init);
    return attr;
  }

  ::std::optional<::circt::firrtl::MemoryInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
};

} // namespace detail
template <typename RangeT>
class SeqMemOpGenericAdaptor : public detail::SeqMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SeqMemOpGenericAdaptorBase;
public:
  SeqMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SeqMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SeqMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SeqMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SeqMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SeqMemOpGenericAdaptor(RangeT values, const SeqMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SeqMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, SeqMemOp>>>
  SeqMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SeqMemOpAdaptor : public SeqMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SeqMemOpGenericAdaptor::SeqMemOpGenericAdaptor;
  SeqMemOpAdaptor(SeqMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SeqMemOp : public ::mlir::Op<SeqMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::chirrtl::CMemoryType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::circt::firrtl::FNamableOp::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SeqMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SeqMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<SeqMemOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("annotations"), ::llvm::StringRef("init"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("nameKind"), ::llvm::StringRef("prefix"), ::llvm::StringRef("ruw")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAnnotationsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAnnotationsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInitAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getNameKindAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getNameKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getPrefixAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getPrefixAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getRuwAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getRuwAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("chirrtl.seqmem");
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

  ::mlir::TypedValue<::circt::chirrtl::CMemoryType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::chirrtl::CMemoryType>>(*getODSResults(0).begin());
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
  ::circt::firrtl::RUWBehaviorAttr getRuwAttr() {
    return ::llvm::cast<::circt::firrtl::RUWBehaviorAttr>(getProperties().ruw);
  }

  ::circt::firrtl::RUWBehavior getRuw();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::circt::firrtl::NameKindEnumAttr getNameKindAttr() {
    return ::llvm::cast<::circt::firrtl::NameKindEnumAttr>(getProperties().nameKind);
  }

  ::circt::firrtl::NameKindEnum getNameKind();
  ::mlir::ArrayAttr getAnnotationsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().annotations);
  }

  ::mlir::ArrayAttr getAnnotations();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::firrtl::MemoryInitAttr getInitAttr() {
    return ::llvm::dyn_cast_or_null<::circt::firrtl::MemoryInitAttr>(getProperties().init);
  }

  ::std::optional<::circt::firrtl::MemoryInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
  void setRuwAttr(::circt::firrtl::RUWBehaviorAttr attr) {
    getProperties().ruw = attr;
  }

  void setRuw(::circt::firrtl::RUWBehavior attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setNameKindAttr(::circt::firrtl::NameKindEnumAttr attr) {
    getProperties().nameKind = attr;
  }

  void setNameKind(::circt::firrtl::NameKindEnum attrValue);
  void setAnnotationsAttr(::mlir::ArrayAttr attr) {
    getProperties().annotations = attr;
  }

  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setInitAttr(::circt::firrtl::MemoryInitAttr attr) {
    getProperties().init = attr;
  }

  void setPrefixAttr(::mlir::StringAttr attr) {
    getProperties().prefix = attr;
  }

  void setPrefix(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  ::mlir::Attribute removeInitAttr() {
      auto attr = getProperties().init;
      getProperties().init = {};
      return attr;
  }

  ::mlir::Attribute removePrefixAttr() {
      auto attr = getProperties().prefix;
      getProperties().prefix = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, firrtl::FIRRTLBaseType elementType, uint64_t numElements, firrtl::RUWBehavior ruw, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, firrtl::FIRRTLBaseType elementType, uint64_t numElements, firrtl::RUWBehavior ruw, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, firrtl::FIRRTLBaseType elementType, uint64_t numElements, firrtl::RUWBehavior ruw, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym = StringAttr(), firrtl::MemoryInitAttr init = firrtl::MemoryInitAttr{});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SeqMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SeqMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::chirrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::SeqMemOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::SeqMemOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

