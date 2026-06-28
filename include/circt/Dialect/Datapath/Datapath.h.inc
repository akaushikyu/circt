/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Datapath.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::datapath {

/// Reduce a set of bitvectors to a carry-save representation
/// Reduce an array of bitvectors to a smaller set of bitvectors (at least 2).
/// A compressor tree sums multiple bitvectors (often partial products in
/// multipliers or adders). Instead of adding all bitvectors sequentially, a 
/// compressor tree reduces the number of operands in parallel stages. The 
/// result is stored in a redundant (carry-save) representation, deferring the 
/// compressor tree implementation to a later stage.
/// 
/// Example:
/// ```mlir
/// %0:2 = datapath.compress %a, %b, %c : i16 [3 -> 2]
/// ```
class CompressOp;

} // namespace circt::datapath
namespace circt::datapath {

/// Generate partial products from multiplying the operands
/// The first step in a multiplication is to generate partial products, which 
/// when summed, yield the product of the two operands. The partial
/// product operator does not specify an implementation, only that summing the 
/// results will yield the product of the two operands. The number of results 
/// corresponds to the rows of a partial product array, which by default is
/// equal to the width of the inputs. 
/// 
/// Verilog Example 4-bit multiplication:
/// ```verilog
/// partial_product[0][3:0] = {4{a[0]}} & b
/// ...
/// partial_product[3][3:0] = {4{a[3]}} & b
/// ab[3:0] = partial_product[0] + ... + partial_product[3] // = a*b
/// ```
/// 
/// Example using `datapath` dialect:
/// ```mlir
/// %0:4 = datapath.partial_product %a, %b : (i4, i4) -> (i4, i4, i4, i4)
/// ```
class PartialProductOp;

} // namespace circt::datapath
namespace circt::datapath {

/// Generate partial products for (a+b)*c
/// A partial product array which when summed produces the result (a+b)*c. 
/// An efficient circuit can be constructed that encodes a carry-save input
/// without performing a full carry-propagation. The number of results 
/// corresponds to the rows of a partial product array, which by default is 
/// equal to the width of the inputs. 
/// 
/// Example using `datapath` dialect:
/// ```mlir
/// %0:3 = datapath.pos_partial_product %a, %b, %c : (i3, i3, i3) 
///                                               -> (i3, i3, i3)
/// ```
class PosPartialProductOp;

} // namespace circt::datapath
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::datapath {


//===----------------------------------------------------------------------===//
// ::circt::datapath::CompressOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompressOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CompressOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("datapath.compress", odsAttrs.getContext());
  }

  CompressOpGenericAdaptorBase(CompressOp op);

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
class CompressOpGenericAdaptor : public detail::CompressOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompressOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CompressOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompressOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CompressOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompressOpGenericAdaptor(RangeT values, const CompressOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompressOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompressOp>>>
  CompressOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompressOpAdaptor : public CompressOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompressOpGenericAdaptor::CompressOpGenericAdaptor;
  CompressOpAdaptor(CompressOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompressOp : public ::mlir::Op<CompressOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::OpTrait::IsCommutative> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompressOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompressOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("datapath.compress");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lhs, int32_t targetRows);
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lhs, int32_t targetRows);
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lhs, int32_t targetRows);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::datapath
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::datapath::CompressOp)

namespace circt::datapath {


//===----------------------------------------------------------------------===//
// ::circt::datapath::PartialProductOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PartialProductOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PartialProductOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("datapath.partial_product", odsAttrs.getContext());
  }

  PartialProductOpGenericAdaptorBase(PartialProductOp op);

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
class PartialProductOpGenericAdaptor : public detail::PartialProductOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PartialProductOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  PartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PartialProductOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PartialProductOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PartialProductOpGenericAdaptor(RangeT values, const PartialProductOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PartialProductOp, typename = std::enable_if_t<std::is_same_v<LateInst, PartialProductOp>>>
  PartialProductOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PartialProductOpAdaptor : public PartialProductOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PartialProductOpGenericAdaptor::PartialProductOpGenericAdaptor;
  PartialProductOpAdaptor(PartialProductOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PartialProductOp : public ::mlir::Op<PartialProductOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::OpTrait::IsCommutative> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PartialProductOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PartialProductOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("datapath.partial_product");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lhs, int32_t targetRows);
  static PartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lhs, int32_t targetRows);
  static PartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lhs, int32_t targetRows);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value lhs, ::mlir::Value rhs);
  static PartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value lhs, ::mlir::Value rhs);
  static PartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::datapath
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::datapath::PartialProductOp)

namespace circt::datapath {


//===----------------------------------------------------------------------===//
// ::circt::datapath::PosPartialProductOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PosPartialProductOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PosPartialProductOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("datapath.pos_partial_product", odsAttrs.getContext());
  }

  PosPartialProductOpGenericAdaptorBase(PosPartialProductOp op);

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
class PosPartialProductOpGenericAdaptor : public detail::PosPartialProductOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PosPartialProductOpGenericAdaptorBase;
  static constexpr int odsIndex_addend0 = 0;
  static constexpr int odsIndex_addend1 = 1;
  static constexpr int odsIndex_multiplicand = 2;
public:
  PosPartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PosPartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PosPartialProductOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PosPartialProductOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PosPartialProductOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PosPartialProductOpGenericAdaptor(RangeT values, const PosPartialProductOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PosPartialProductOp, typename = std::enable_if_t<std::is_same_v<LateInst, PosPartialProductOp>>>
  PosPartialProductOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getAddend0() {
    return (*getODSOperands(0).begin());
  }

  ValueT getAddend1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getMultiplicand() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PosPartialProductOpAdaptor : public PosPartialProductOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PosPartialProductOpGenericAdaptor::PosPartialProductOpGenericAdaptor;
  PosPartialProductOpAdaptor(PosPartialProductOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PosPartialProductOp : public ::mlir::Op<PosPartialProductOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands, ::mlir::OpTrait::SameOperandsAndResultType> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PosPartialProductOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PosPartialProductOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_addend0 = 0;
  static constexpr int odsIndex_addend1 = 1;
  static constexpr int odsIndex_multiplicand = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("datapath.pos_partial_product");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getAddend0() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getAddend1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getMultiplicand() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getAddend0Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddend1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMultiplicandMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange lhs, int32_t targetRows);
  static PosPartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange lhs, int32_t targetRows);
  static PosPartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange lhs, int32_t targetRows);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value addend0, ::mlir::Value addend1, ::mlir::Value multiplicand);
  static PosPartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value addend0, ::mlir::Value addend1, ::mlir::Value multiplicand);
  static PosPartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value addend0, ::mlir::Value addend1, ::mlir::Value multiplicand);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PosPartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PosPartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PosPartialProductOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PosPartialProductOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::datapath
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::datapath::PosPartialProductOp)


#endif // GET_OP_CLASSES

