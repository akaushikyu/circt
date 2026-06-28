/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SSP.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::ssp {

/// Container for (scheduling) operations.
/// The dependence graph is spanned by `OperationOp`s (vertices) and a
/// combination of MLIR value uses and symbol references (edges).
class DependenceGraphOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Instance of a static scheduling problem.
/// This operation represents an instance of a static scheduling problem,
/// comprised of an operator library (`OperatorLibraryOp`, a container for
/// `OperatorTypeOp`s), an resource library (`ResourceLibraryOp`, a container
/// for `ResourceTypeOp`s), and the dependence graph (`DependenceGraphOp`, a
/// container for `OperationOp`s). The instance and its components (operations,
/// operator types, resource types and dependences) can carry properties,
/// i.e. special MLIR attributes inheriting from the TableGen classes in
/// `PropertyBase.td`. The `ssp` dialect provides attribute definitions (and
/// short-form pretty-printing) for CIRCT's built-in scheduling problems.
/// 
/// **Example**
/// ```mlir
/// ssp.instance @canis14_fig2 of "ModuloProblem" [II<3>] {
///   library {
///     operator_type @Memory [latency<1>]
///     operator_type @Add [latency<1>]
///   }
///   resource {
///     resource_type @ReadPort [limit<1>]
///     resource_type @WritePort [limit<1>]
///   }
///   graph {
///     %0 = operation<@Memory> @load_A(@store_A [dist<1>]) uses[@ReadPort] [t<2>]
///     %1 = operation<@Memory> @load_B() uses[@ReadPort] [t<0>]
///     %2 = operation<@Add> @add(%0, %1) [t<3>]  // no `resource_type` needed
///     operation<@Memory> @store_A(%2) uses[@WritePort] [t<4>]
///   }
/// }
/// ```
class InstanceOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Vertex and incoming edges in the dependence graph.
/// This MLIR operation represents an operation (in the terminology of CIRCT's
/// scheduling infra) in a scheduling problem, or in other words, a vertex in
/// the surrounding instance's dependence graph. In addition, it also encodes
/// the operation's incoming dependences. In order to faithfully reproduce the
/// internal modeling in the scheduling infrastructure, these dependence edges
/// are either encoded as MLIR operands (def-use dependences) or symbol
/// references (auxiliary dependences). To that end, `OperationOp`s can
/// optionally be named, and accept/produce an arbitrary number of
/// operands/results. The operation and the incoming dependences can carry
/// properties.
/// 
/// The `linkedOperatorType` and `linkedResourceType` property in the root
/// `Problem` class are central to the problem models, because it links operations
/// to their properties in the target IR. Therefore, the referenced operator/resource
/// type symbol is parsed/printed right after the operation keyword in the custom
/// assembly syntax. Flat symbol references are resolved by name in the surrounding
/// instance's operator/resource library. Nested references can point to arbitrary
/// operator/resource libraries.
/// 
/// **Examples**
/// ```mlir
/// // unnamed, only def-use dependences
/// %2 = operation<@Add>(%0, %1)
/// 
/// // unnamed, multiple results
/// %5:2 = operation<@Div>(%3, %4) // multiple results
/// 
/// // named, mix of def-use and auxiliary dependences
/// operation<@MemAccess> @store_A(%2, @store_B, @load_A) uses[@MemPort]
/// 
/// // dependence properties
/// operation<@Barrier>(%2 [dist<1>], %5#1, @store_A [dist<3>])
/// 
/// // operator type in stand-alone library
/// %7 = operation<@MathLib::@Sqrt>(%6)
/// ```
class OperationOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Container for operator types.
/// The operator library abstracts the characteristics of the target
/// architecture/IR (onto which the source graph is scheduled), represented by
/// the individual `OperatorTypeOp`s. This operation may be used outside of an
/// `InstanceOp`.
class OperatorLibraryOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Element of the target architecture/IR.
/// This operation represents an operator type, which can be augmented with a
/// set of problem-specific properties, and is identified through a unique name.
/// 
/// **Example**
/// ```mlir
/// operator_type @MemPort [latency<1>]
/// ```
class OperatorTypeOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Container for resource types.
/// The resource library represents different kinds of resource of desired
/// usage on the target architecture/IR. Each resource will be represented by
/// the individual `ResourceTypeOp`s. An `OperationOp` can be associated with
/// zero, one, or multiple resources. This operation may be used outside of
/// an `InstanceOp` so different problems can share the same resource constraints.
class ResourceLibraryOp;

} // namespace circt::ssp
namespace circt::ssp {

/// Resource of desired usage on the target architecture/IR.
/// This resource represents a resource type, which can be augmented with a
/// set of problem-specific properties, and is identified through a unique name.
/// 
/// **Example**
/// ```mlir
/// resource_type @MemPort [limit<1>]
/// ```
class ResourceTypeOp;

} // namespace circt::ssp
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::DependenceGraphOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DependenceGraphOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DependenceGraphOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.graph", odsAttrs.getContext());
  }

  DependenceGraphOpGenericAdaptorBase(DependenceGraphOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class DependenceGraphOpGenericAdaptor : public detail::DependenceGraphOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DependenceGraphOpGenericAdaptorBase;
public:
  DependenceGraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DependenceGraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DependenceGraphOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DependenceGraphOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DependenceGraphOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DependenceGraphOpGenericAdaptor(RangeT values, const DependenceGraphOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DependenceGraphOp, typename = std::enable_if_t<std::is_same_v<LateInst, DependenceGraphOp>>>
  DependenceGraphOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DependenceGraphOpAdaptor : public DependenceGraphOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DependenceGraphOpGenericAdaptor::DependenceGraphOpGenericAdaptor;
  DependenceGraphOpAdaptor(DependenceGraphOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DependenceGraphOp : public ::mlir::Op<DependenceGraphOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<InstanceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::HasOnlyGraphRegion, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DependenceGraphOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DependenceGraphOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ssp.graph");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static DependenceGraphOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static DependenceGraphOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  // OpAsmOpInterface
  static ::llvm::StringRef getDefaultDialect() { return "ssp"; }

  // Convenience
  ::mlir::Block *getBodyBlock() {
    return &getBody().getBlocks().front();
  }
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::DependenceGraphOp)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using problemNameTy = ::mlir::StringAttr;
    problemNameTy problemName;

    auto getProblemName() const {
      auto &propStorage = this->problemName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setProblemName(const ::mlir::StringAttr &propValue) {
      this->problemName = propValue;
    }
    using sspPropertiesTy = ::mlir::ArrayAttr;
    sspPropertiesTy sspProperties;

    auto getSspProperties() const {
      auto &propStorage = this->sspProperties;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setSspProperties(const ::mlir::ArrayAttr &propValue) {
      this->sspProperties = propValue;
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
        rhs.problemName == this->problemName &&
        rhs.sspProperties == this->sspProperties &&
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
  InstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.instance", odsAttrs.getContext());
  }

  InstanceOpGenericAdaptorBase(InstanceOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::StringAttr getProblemNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().problemName);
    return attr;
  }

  ::llvm::StringRef getProblemName();
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class InstanceOpGenericAdaptor : public detail::InstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceOpGenericAdaptorBase;
public:
  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InstanceOpGenericAdaptor(RangeT values, const InstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, InstanceOp>>>
  InstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InstanceOpAdaptor : public InstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InstanceOpGenericAdaptor::InstanceOpGenericAdaptor;
  InstanceOpAdaptor(InstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("problemName"), ::llvm::StringRef("sspProperties"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getProblemNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getProblemNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSspPropertiesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSspPropertiesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ssp.instance");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::StringAttr getProblemNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().problemName);
  }

  ::llvm::StringRef getProblemName();
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  void setProblemNameAttr(::mlir::StringAttr attr) {
    getProperties().problemName = attr;
  }

  void setProblemName(::llvm::StringRef attrValue);
  void setSspPropertiesAttr(::mlir::ArrayAttr attr) {
    getProperties().sspProperties = attr;
  }

  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  ::mlir::Attribute removeSspPropertiesAttr() {
      auto attr = getProperties().sspProperties;
      getProperties().sspProperties = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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
  // OpAsmOpInterface
  static ::llvm::StringRef getDefaultDialect() { return "ssp"; }

  // SymbolOpInterface
  static bool isOptionalSymbol() { return true; }

  // Convenience
  ::mlir::Block *getBodyBlock() {
    return &getBody().getBlocks().front();
  }

  // Access to container ops
  ::circt::ssp::OperatorLibraryOp getOperatorLibrary();
  ::circt::ssp::ResourceLibraryOp getResourceLibrary();
  ::circt::ssp::DependenceGraphOp getDependenceGraph();
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperationOpGenericAdaptorBase {
public:
  struct Properties {
    using dependencesTy = ::mlir::ArrayAttr;
    dependencesTy dependences;

    auto getDependences() const {
      auto &propStorage = this->dependences;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setDependences(const ::mlir::ArrayAttr &propValue) {
      this->dependences = propValue;
    }
    using sspPropertiesTy = ::mlir::ArrayAttr;
    sspPropertiesTy sspProperties;

    auto getSspProperties() const {
      auto &propStorage = this->sspProperties;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setSspProperties(const ::mlir::ArrayAttr &propValue) {
      this->sspProperties = propValue;
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
        rhs.dependences == this->dependences &&
        rhs.sspProperties == this->sspProperties &&
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
  OperationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.operation", odsAttrs.getContext());
  }

  OperationOpGenericAdaptorBase(OperationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::ArrayAttr getDependencesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().dependences);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getDependences();
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
};

} // namespace detail
template <typename RangeT>
class OperationOpGenericAdaptor : public detail::OperationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperationOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OperationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OperationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperationOpGenericAdaptor(RangeT values, const OperationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperationOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperationOp>>>
  OperationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OperationOpAdaptor : public OperationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperationOpGenericAdaptor::OperationOpGenericAdaptor;
  OperationOpAdaptor(OperationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperationOp : public ::mlir::Op<OperationOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<DependenceGraphOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("dependences"), ::llvm::StringRef("sspProperties"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDependencesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDependencesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSspPropertiesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSspPropertiesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ssp.operation");
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
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::ArrayAttr getDependencesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().dependences);
  }

  ::std::optional< ::mlir::ArrayAttr > getDependences();
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  void setDependencesAttr(::mlir::ArrayAttr attr) {
    getProperties().dependences = attr;
  }

  void setSspPropertiesAttr(::mlir::ArrayAttr attr) {
    getProperties().sspProperties = attr;
  }

  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  ::mlir::Attribute removeDependencesAttr() {
      auto attr = getProperties().dependences;
      getProperties().dependences = {};
      return attr;
  }

  ::mlir::Attribute removeSspPropertiesAttr() {
      auto attr = getProperties().sspProperties;
      getProperties().sspProperties = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name = ::mlir::StringAttr(), ::mlir::ArrayAttr dependences = ::mlir::ArrayAttr(), ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  static OperationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name = ::mlir::StringAttr(), ::mlir::ArrayAttr dependences = ::mlir::ArrayAttr(), ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  static OperationOp create(::mlir::ImplicitLocOpBuilder &builder, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name = ::mlir::StringAttr(), ::mlir::ArrayAttr dependences = ::mlir::ArrayAttr(), ::mlir::ArrayAttr sspProperties = ::mlir::ArrayAttr());
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

  // Find the attribute modeling the `linkedOperatorType` property
  ::circt::ssp::LinkedOperatorTypeAttr getLinkedOperatorTypeAttr();

  // Find the attribute modeling the `linkedResourceTypes` property
  ::circt::ssp::LinkedResourceTypesAttr getLinkedResourceTypesAttr();
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::OperationOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperationOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperatorLibraryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperatorLibraryOpGenericAdaptorBase {
public:
  struct Properties {
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
  OperatorLibraryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.library", odsAttrs.getContext());
  }

  OperatorLibraryOpGenericAdaptorBase(OperatorLibraryOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class OperatorLibraryOpGenericAdaptor : public detail::OperatorLibraryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperatorLibraryOpGenericAdaptorBase;
public:
  OperatorLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperatorLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OperatorLibraryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperatorLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OperatorLibraryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperatorLibraryOpGenericAdaptor(RangeT values, const OperatorLibraryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperatorLibraryOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperatorLibraryOp>>>
  OperatorLibraryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OperatorLibraryOpAdaptor : public OperatorLibraryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperatorLibraryOpGenericAdaptor::OperatorLibraryOpGenericAdaptor;
  OperatorLibraryOpAdaptor(OperatorLibraryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperatorLibraryOp : public ::mlir::Op<OperatorLibraryOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperatorLibraryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperatorLibraryOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("ssp.library");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static OperatorLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OperatorLibraryOp create(::mlir::ImplicitLocOpBuilder &builder);
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
  // OpAsmOpInterface
  static ::llvm::StringRef getDefaultDialect() { return "ssp"; }

  // SymbolOpInterface
  static bool isOptionalSymbol() { return true; }

  // Convenience
  ::mlir::Block *getBodyBlock() {
    return &getBody().getBlocks().front();
  }
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::OperatorLibraryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperatorLibraryOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperatorTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OperatorTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using sspPropertiesTy = ::mlir::ArrayAttr;
    sspPropertiesTy sspProperties;

    auto getSspProperties() const {
      auto &propStorage = this->sspProperties;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setSspProperties(const ::mlir::ArrayAttr &propValue) {
      this->sspProperties = propValue;
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
        rhs.sspProperties == this->sspProperties &&
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
  OperatorTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.operator_type", odsAttrs.getContext());
  }

  OperatorTypeOpGenericAdaptorBase(OperatorTypeOp op);

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
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
};

} // namespace detail
template <typename RangeT>
class OperatorTypeOpGenericAdaptor : public detail::OperatorTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperatorTypeOpGenericAdaptorBase;
public:
  OperatorTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperatorTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OperatorTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OperatorTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OperatorTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OperatorTypeOpGenericAdaptor(RangeT values, const OperatorTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OperatorTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperatorTypeOp>>>
  OperatorTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OperatorTypeOpAdaptor : public OperatorTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperatorTypeOpGenericAdaptor::OperatorTypeOpGenericAdaptor;
  OperatorTypeOpAdaptor(OperatorTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OperatorTypeOp : public ::mlir::Op<OperatorTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<OperatorLibraryOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperatorTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperatorTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sspProperties"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSspPropertiesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSspPropertiesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ssp.operator_type");
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
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setSspPropertiesAttr(::mlir::ArrayAttr attr) {
    getProperties().sspProperties = attr;
  }

  ::mlir::Attribute removeSspPropertiesAttr() {
      auto attr = getProperties().sspProperties;
      getProperties().sspProperties = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperatorTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OperatorTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::OperatorTypeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperatorTypeOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::ResourceLibraryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ResourceLibraryOpGenericAdaptorBase {
public:
  struct Properties {
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
  ResourceLibraryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.resource", odsAttrs.getContext());
  }

  ResourceLibraryOpGenericAdaptorBase(ResourceLibraryOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ResourceLibraryOpGenericAdaptor : public detail::ResourceLibraryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ResourceLibraryOpGenericAdaptorBase;
public:
  ResourceLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ResourceLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ResourceLibraryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ResourceLibraryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ResourceLibraryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ResourceLibraryOpGenericAdaptor(RangeT values, const ResourceLibraryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ResourceLibraryOp, typename = std::enable_if_t<std::is_same_v<LateInst, ResourceLibraryOp>>>
  ResourceLibraryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ResourceLibraryOpAdaptor : public ResourceLibraryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ResourceLibraryOpGenericAdaptor::ResourceLibraryOpGenericAdaptor;
  ResourceLibraryOpAdaptor(ResourceLibraryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ResourceLibraryOp : public ::mlir::Op<ResourceLibraryOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ResourceLibraryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ResourceLibraryOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("ssp.resource");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::std::optional< ::llvm::StringRef > getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeSymNameAttr() {
      auto attr = getProperties().sym_name;
      getProperties().sym_name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ResourceLibraryOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ResourceLibraryOp create(::mlir::ImplicitLocOpBuilder &builder);
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
  // OpAsmOpInterface
  static ::llvm::StringRef getDefaultDialect() { return "ssp"; }

  // SymbolOpInterface
  static bool isOptionalSymbol() { return true; }

  // Convenience
  ::mlir::Block *getBodyBlock() {
    return &getBody().getBlocks().front();
  }
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::ResourceLibraryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::ResourceLibraryOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::ResourceTypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ResourceTypeOpGenericAdaptorBase {
public:
  struct Properties {
    using sspPropertiesTy = ::mlir::ArrayAttr;
    sspPropertiesTy sspProperties;

    auto getSspProperties() const {
      auto &propStorage = this->sspProperties;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setSspProperties(const ::mlir::ArrayAttr &propValue) {
      this->sspProperties = propValue;
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
        rhs.sspProperties == this->sspProperties &&
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
  ResourceTypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("ssp.resource_type", odsAttrs.getContext());
  }

  ResourceTypeOpGenericAdaptorBase(ResourceTypeOp op);

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
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
};

} // namespace detail
template <typename RangeT>
class ResourceTypeOpGenericAdaptor : public detail::ResourceTypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ResourceTypeOpGenericAdaptorBase;
public:
  ResourceTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ResourceTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ResourceTypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ResourceTypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ResourceTypeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ResourceTypeOpGenericAdaptor(RangeT values, const ResourceTypeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ResourceTypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ResourceTypeOp>>>
  ResourceTypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ResourceTypeOpAdaptor : public ResourceTypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ResourceTypeOpGenericAdaptor::ResourceTypeOpGenericAdaptor;
  ResourceTypeOpAdaptor(ResourceTypeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ResourceTypeOp : public ::mlir::Op<ResourceTypeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ResourceLibraryOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ResourceTypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ResourceTypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sspProperties"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSspPropertiesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSspPropertiesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("ssp.resource_type");
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
  ::mlir::ArrayAttr getSspPropertiesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().sspProperties);
  }

  ::std::optional< ::mlir::ArrayAttr > getSspProperties();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setSspPropertiesAttr(::mlir::ArrayAttr attr) {
    getProperties().sspProperties = attr;
  }

  ::mlir::Attribute removeSspPropertiesAttr() {
      auto attr = getProperties().sspProperties;
      getProperties().sspProperties = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResourceTypeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ResourceTypeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::ResourceTypeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::detail::ResourceTypeOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

