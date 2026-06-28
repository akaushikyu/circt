/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTGTest.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtgtest {

class ADD;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ADDI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class AND;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ANDI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class AUIPC;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BEQ;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BGE;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BGEU;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BLT;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BLTU;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class BNE;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ConstantTestOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class EBREAKOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ECALLOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class GetHartIdOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ImplicitConstraintTestOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class JAL;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class JALROp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LA;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LBOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LBUOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LHOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LHUOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LUI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class LWOp;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class OR;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class ORI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SB;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SH;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLL;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLLI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLT;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLTI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLTIU;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SLTU;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SRA;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SRAI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SRL;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SRLI;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SUB;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class SW;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class XOR;

} // namespace circt::rtgtest
namespace circt::rtgtest {

class XORI;

} // namespace circt::rtgtest
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ADD declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ADDGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ADDGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.add", odsAttrs.getContext());
  }

  ADDGenericAdaptorBase(ADD op);

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
class ADDGenericAdaptor : public detail::ADDGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ADDGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  ADDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ADDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ADDGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ADDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ADDGenericAdaptor(values, attrs, Properties{}, {}) {}

  ADDGenericAdaptor(RangeT values, const ADDGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ADD, typename = std::enable_if_t<std::is_same_v<LateInst, ADD>>>
  ADDGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ADDAdaptor : public ADDGenericAdaptor<::mlir::ValueRange> {
public:
  using ADDGenericAdaptor::ADDGenericAdaptor;
  ADDAdaptor(ADD op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ADD : public ::mlir::Op<ADD, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ADDAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ADDGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.add");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static ADD create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static ADD create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static ADD create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static ADD create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ADD create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ADD create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ADD create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ADD create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ADD)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ADDI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ADDIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ADDIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.addi", odsAttrs.getContext());
  }

  ADDIGenericAdaptorBase(ADDI op);

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
class ADDIGenericAdaptor : public detail::ADDIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ADDIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  ADDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ADDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ADDIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ADDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ADDIGenericAdaptor(values, attrs, Properties{}, {}) {}

  ADDIGenericAdaptor(RangeT values, const ADDIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ADDI, typename = std::enable_if_t<std::is_same_v<LateInst, ADDI>>>
  ADDIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ADDIAdaptor : public ADDIGenericAdaptor<::mlir::ValueRange> {
public:
  using ADDIGenericAdaptor::ADDIGenericAdaptor;
  ADDIAdaptor(ADDI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ADDI : public ::mlir::Op<ADDI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ADDIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ADDIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.addi");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ADDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ADDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ADDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ADDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ADDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ADDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ADDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ADDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ADDI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::AND declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ANDGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ANDGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.and", odsAttrs.getContext());
  }

  ANDGenericAdaptorBase(AND op);

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
class ANDGenericAdaptor : public detail::ANDGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ANDGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  ANDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ANDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ANDGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ANDGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ANDGenericAdaptor(values, attrs, Properties{}, {}) {}

  ANDGenericAdaptor(RangeT values, const ANDGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AND, typename = std::enable_if_t<std::is_same_v<LateInst, AND>>>
  ANDGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ANDAdaptor : public ANDGenericAdaptor<::mlir::ValueRange> {
public:
  using ANDGenericAdaptor::ANDGenericAdaptor;
  ANDAdaptor(AND op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AND : public ::mlir::Op<AND, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ANDAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ANDGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.and");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static AND create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static AND create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static AND create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static AND create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AND create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AND create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AND create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AND create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::AND)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ANDI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ANDIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ANDIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.andi", odsAttrs.getContext());
  }

  ANDIGenericAdaptorBase(ANDI op);

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
class ANDIGenericAdaptor : public detail::ANDIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ANDIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  ANDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ANDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ANDIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ANDIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ANDIGenericAdaptor(values, attrs, Properties{}, {}) {}

  ANDIGenericAdaptor(RangeT values, const ANDIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ANDI, typename = std::enable_if_t<std::is_same_v<LateInst, ANDI>>>
  ANDIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ANDIAdaptor : public ANDIGenericAdaptor<::mlir::ValueRange> {
public:
  using ANDIGenericAdaptor::ANDIGenericAdaptor;
  ANDIAdaptor(ANDI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ANDI : public ::mlir::Op<ANDI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ANDIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ANDIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.andi");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ANDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ANDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ANDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ANDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ANDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ANDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ANDI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ANDI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ANDI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::AUIPC declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AUIPCGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AUIPCGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.auipc", odsAttrs.getContext());
  }

  AUIPCGenericAdaptorBase(AUIPC op);

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
class AUIPCGenericAdaptor : public detail::AUIPCGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AUIPCGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
public:
  AUIPCGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AUIPCGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AUIPCGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AUIPCGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AUIPCGenericAdaptor(values, attrs, Properties{}, {}) {}

  AUIPCGenericAdaptor(RangeT values, const AUIPCGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AUIPC, typename = std::enable_if_t<std::is_same_v<LateInst, AUIPC>>>
  AUIPCGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AUIPCAdaptor : public AUIPCGenericAdaptor<::mlir::ValueRange> {
public:
  using AUIPCGenericAdaptor::AUIPCGenericAdaptor;
  AUIPCAdaptor(AUIPC op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AUIPC : public ::mlir::Op<AUIPC, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AUIPCAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AUIPCGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.auipc");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm);
  static AUIPC create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm);
  static AUIPC create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static AUIPC create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static AUIPC create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AUIPC create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AUIPC create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AUIPC create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AUIPC create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::AUIPC)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BEQ declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BEQGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BEQGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.beq", odsAttrs.getContext());
  }

  BEQGenericAdaptorBase(BEQ op);

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
class BEQGenericAdaptor : public detail::BEQGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BEQGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BEQGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BEQGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BEQGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BEQGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BEQGenericAdaptor(values, attrs, Properties{}, {}) {}

  BEQGenericAdaptor(RangeT values, const BEQGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BEQ, typename = std::enable_if_t<std::is_same_v<LateInst, BEQ>>>
  BEQGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BEQAdaptor : public BEQGenericAdaptor<::mlir::ValueRange> {
public:
  using BEQGenericAdaptor::BEQGenericAdaptor;
  BEQAdaptor(BEQ op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BEQ : public ::mlir::Op<BEQ, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BEQAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BEQGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.beq");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BEQ create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BEQ create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BEQ create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BEQ create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BEQ create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BEQ create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BEQ create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BEQ create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BEQ)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BGE declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BGEGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BGEGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.bge", odsAttrs.getContext());
  }

  BGEGenericAdaptorBase(BGE op);

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
class BGEGenericAdaptor : public detail::BGEGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BGEGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BGEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BGEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BGEGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BGEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BGEGenericAdaptor(values, attrs, Properties{}, {}) {}

  BGEGenericAdaptor(RangeT values, const BGEGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BGE, typename = std::enable_if_t<std::is_same_v<LateInst, BGE>>>
  BGEGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BGEAdaptor : public BGEGenericAdaptor<::mlir::ValueRange> {
public:
  using BGEGenericAdaptor::BGEGenericAdaptor;
  BGEAdaptor(BGE op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BGE : public ::mlir::Op<BGE, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BGEAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BGEGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.bge");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BGE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BGE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BGE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BGE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BGE)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BGEU declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BGEUGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BGEUGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.bgeu", odsAttrs.getContext());
  }

  BGEUGenericAdaptorBase(BGEU op);

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
class BGEUGenericAdaptor : public detail::BGEUGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BGEUGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BGEUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BGEUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BGEUGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BGEUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BGEUGenericAdaptor(values, attrs, Properties{}, {}) {}

  BGEUGenericAdaptor(RangeT values, const BGEUGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BGEU, typename = std::enable_if_t<std::is_same_v<LateInst, BGEU>>>
  BGEUGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BGEUAdaptor : public BGEUGenericAdaptor<::mlir::ValueRange> {
public:
  using BGEUGenericAdaptor::BGEUGenericAdaptor;
  BGEUAdaptor(BGEU op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BGEU : public ::mlir::Op<BGEU, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BGEUAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BGEUGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.bgeu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGEU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGEU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGEU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BGEU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BGEU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BGEU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BGEU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BGEU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BGEU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BLT declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BLTGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BLTGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.blt", odsAttrs.getContext());
  }

  BLTGenericAdaptorBase(BLT op);

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
class BLTGenericAdaptor : public detail::BLTGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BLTGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BLTGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BLTGenericAdaptor(values, attrs, Properties{}, {}) {}

  BLTGenericAdaptor(RangeT values, const BLTGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BLT, typename = std::enable_if_t<std::is_same_v<LateInst, BLT>>>
  BLTGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BLTAdaptor : public BLTGenericAdaptor<::mlir::ValueRange> {
public:
  using BLTGenericAdaptor::BLTGenericAdaptor;
  BLTAdaptor(BLT op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BLT : public ::mlir::Op<BLT, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BLTAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BLTGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.blt");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BLT)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BLTU declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BLTUGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BLTUGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.bltu", odsAttrs.getContext());
  }

  BLTUGenericAdaptorBase(BLTU op);

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
class BLTUGenericAdaptor : public detail::BLTUGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BLTUGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BLTUGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BLTUGenericAdaptor(values, attrs, Properties{}, {}) {}

  BLTUGenericAdaptor(RangeT values, const BLTUGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BLTU, typename = std::enable_if_t<std::is_same_v<LateInst, BLTU>>>
  BLTUGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BLTUAdaptor : public BLTUGenericAdaptor<::mlir::ValueRange> {
public:
  using BLTUGenericAdaptor::BLTUGenericAdaptor;
  BLTUAdaptor(BLTU op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BLTU : public ::mlir::Op<BLTU, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BLTUAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BLTUGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.bltu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BLTU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BNE declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BNEGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BNEGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.bne", odsAttrs.getContext());
  }

  BNEGenericAdaptorBase(BNE op);

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
class BNEGenericAdaptor : public detail::BNEGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BNEGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  BNEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BNEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BNEGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BNEGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BNEGenericAdaptor(values, attrs, Properties{}, {}) {}

  BNEGenericAdaptor(RangeT values, const BNEGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BNE, typename = std::enable_if_t<std::is_same_v<LateInst, BNE>>>
  BNEGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BNEAdaptor : public BNEGenericAdaptor<::mlir::ValueRange> {
public:
  using BNEGenericAdaptor::BNEGenericAdaptor;
  BNEAdaptor(BNE op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BNE : public ::mlir::Op<BNE, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BNEAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BNEGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.bne");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BNE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BNE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BNE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static BNE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BNE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BNE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BNE create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BNE create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::BNE)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ConstantTestOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantTestOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::Attribute;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
    }
    void setValue(const ::mlir::Attribute &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
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
  ConstantTestOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.constant_test", odsAttrs.getContext());
  }

  ConstantTestOpGenericAdaptorBase(ConstantTestOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getValueAttr() {
    auto attr = ::llvm::cast<::mlir::Attribute>(getProperties().value);
    return attr;
  }

  ::mlir::Attribute getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantTestOpGenericAdaptor : public detail::ConstantTestOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantTestOpGenericAdaptorBase;
public:
  ConstantTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConstantTestOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantTestOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantTestOpGenericAdaptor(RangeT values, const ConstantTestOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantTestOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantTestOp>>>
  ConstantTestOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstantTestOpAdaptor : public ConstantTestOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantTestOpGenericAdaptor::ConstantTestOpGenericAdaptor;
  ConstantTestOpAdaptor(ConstantTestOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantTestOp : public ::mlir::Op<ConstantTestOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantTestOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantTestOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.constant_test");
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::Attribute getValueAttr() {
    return ::llvm::cast<::mlir::Attribute>(getProperties().value);
  }

  ::mlir::Attribute getValue();
  void setValueAttr(::mlir::Attribute attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute value);
  static ConstantTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute value);
  static ConstantTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ConstantTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ConstantTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ConstantTestOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::detail::ConstantTestOpGenericAdaptorBase::Properties)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::EBREAKOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EBREAKOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  EBREAKOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.ebreak", odsAttrs.getContext());
  }

  EBREAKOpGenericAdaptorBase(EBREAKOp op);

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
class EBREAKOpGenericAdaptor : public detail::EBREAKOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EBREAKOpGenericAdaptorBase;
public:
  EBREAKOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EBREAKOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EBREAKOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EBREAKOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EBREAKOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EBREAKOpGenericAdaptor(RangeT values, const EBREAKOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EBREAKOp, typename = std::enable_if_t<std::is_same_v<LateInst, EBREAKOp>>>
  EBREAKOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EBREAKOpAdaptor : public EBREAKOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EBREAKOpGenericAdaptor::EBREAKOpGenericAdaptor;
  EBREAKOpAdaptor(EBREAKOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EBREAKOp : public ::mlir::Op<EBREAKOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EBREAKOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EBREAKOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.ebreak");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static EBREAKOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static EBREAKOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static EBREAKOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static EBREAKOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EBREAKOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EBREAKOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EBREAKOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EBREAKOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::EBREAKOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ECALLOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ECALLOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ECALLOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.ecall", odsAttrs.getContext());
  }

  ECALLOpGenericAdaptorBase(ECALLOp op);

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
class ECALLOpGenericAdaptor : public detail::ECALLOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ECALLOpGenericAdaptorBase;
public:
  ECALLOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ECALLOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ECALLOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ECALLOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ECALLOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ECALLOpGenericAdaptor(RangeT values, const ECALLOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ECALLOp, typename = std::enable_if_t<std::is_same_v<LateInst, ECALLOp>>>
  ECALLOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ECALLOpAdaptor : public ECALLOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ECALLOpGenericAdaptor::ECALLOpGenericAdaptor;
  ECALLOpAdaptor(ECALLOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ECALLOp : public ::mlir::Op<ECALLOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ECALLOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ECALLOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.ecall");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ECALLOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ECALLOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static ECALLOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static ECALLOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ECALLOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ECALLOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ECALLOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ECALLOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ECALLOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::GetHartIdOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GetHartIdOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GetHartIdOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.get_hartid", odsAttrs.getContext());
  }

  GetHartIdOpGenericAdaptorBase(GetHartIdOp op);

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
class GetHartIdOpGenericAdaptor : public detail::GetHartIdOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GetHartIdOpGenericAdaptorBase;
  static constexpr int odsIndex_cpu = 0;
public:
  GetHartIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GetHartIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GetHartIdOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GetHartIdOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GetHartIdOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GetHartIdOpGenericAdaptor(RangeT values, const GetHartIdOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GetHartIdOp, typename = std::enable_if_t<std::is_same_v<LateInst, GetHartIdOp>>>
  GetHartIdOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCpu() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GetHartIdOpAdaptor : public GetHartIdOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GetHartIdOpGenericAdaptor::GetHartIdOpGenericAdaptor;
  GetHartIdOpAdaptor(GetHartIdOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GetHartIdOp : public ::mlir::Op<GetHartIdOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IndexType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GetHartIdOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GetHartIdOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_cpu = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.get_hartid");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::CPUType> getCpu() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::CPUType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getCpuMutable() {
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

  ::mlir::TypedValue<::mlir::IndexType> getHartid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IndexType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type hartid, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type hartid, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type hartid, ::mlir::Value cpu);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cpu);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cpu);
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cpu);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetHartIdOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GetHartIdOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::GetHartIdOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ImplicitConstraintTestOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ImplicitConstraintTestOpGenericAdaptorBase {
public:
  struct Properties {
    using implicitConstraintTy = ::mlir::UnitAttr;
    implicitConstraintTy implicitConstraint;

    auto getImplicitConstraint() const {
      auto &propStorage = this->implicitConstraint;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setImplicitConstraint(const ::mlir::UnitAttr &propValue) {
      this->implicitConstraint = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.implicitConstraint == this->implicitConstraint &&
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
  ImplicitConstraintTestOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.implicit_constraint_op", odsAttrs.getContext());
  }

  ImplicitConstraintTestOpGenericAdaptorBase(ImplicitConstraintTestOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::UnitAttr getImplicitConstraintAttr();
  bool getImplicitConstraint();
};

} // namespace detail
template <typename RangeT>
class ImplicitConstraintTestOpGenericAdaptor : public detail::ImplicitConstraintTestOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ImplicitConstraintTestOpGenericAdaptorBase;
public:
  ImplicitConstraintTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ImplicitConstraintTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ImplicitConstraintTestOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ImplicitConstraintTestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ImplicitConstraintTestOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ImplicitConstraintTestOpGenericAdaptor(RangeT values, const ImplicitConstraintTestOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ImplicitConstraintTestOp, typename = std::enable_if_t<std::is_same_v<LateInst, ImplicitConstraintTestOp>>>
  ImplicitConstraintTestOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ImplicitConstraintTestOpAdaptor : public ImplicitConstraintTestOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ImplicitConstraintTestOpGenericAdaptor::ImplicitConstraintTestOpGenericAdaptor;
  ImplicitConstraintTestOpAdaptor(ImplicitConstraintTestOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ImplicitConstraintTestOp : public ::mlir::Op<ImplicitConstraintTestOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::rtg::ImplicitConstraintOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ImplicitConstraintTestOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ImplicitConstraintTestOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("implicitConstraint")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getImplicitConstraintAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getImplicitConstraintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.implicit_constraint_op");
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
  ::mlir::UnitAttr getImplicitConstraintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().implicitConstraint);
  }

  bool getImplicitConstraint();
  void setImplicitConstraintAttr(::mlir::UnitAttr attr) {
    getProperties().implicitConstraint = attr;
  }

  void setImplicitConstraint(bool attrValue);
  ::mlir::Attribute removeImplicitConstraintAttr() {
      auto attr = getProperties().implicitConstraint;
      getProperties().implicitConstraint = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::UnitAttr implicitConstraint);
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::UnitAttr implicitConstraint);
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::UnitAttr implicitConstraint);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint);
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint);
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/bool implicitConstraint = false);
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/bool implicitConstraint = false);
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/bool implicitConstraint = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint = false);
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint = false);
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ImplicitConstraintTestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ImplicitConstraintTestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  bool isConstraintMaterialized();
  mlir::Operation *materializeConstraint(mlir::OpBuilder &builder);
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
};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ImplicitConstraintTestOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::detail::ImplicitConstraintTestOpGenericAdaptorBase::Properties)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::JAL declarations
//===----------------------------------------------------------------------===//

namespace detail {

class JALGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  JALGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.jal", odsAttrs.getContext());
  }

  JALGenericAdaptorBase(JAL op);

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
class JALGenericAdaptor : public detail::JALGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::JALGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
public:
  JALGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  JALGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : JALGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  JALGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : JALGenericAdaptor(values, attrs, Properties{}, {}) {}

  JALGenericAdaptor(RangeT values, const JALGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = JAL, typename = std::enable_if_t<std::is_same_v<LateInst, JAL>>>
  JALGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class JALAdaptor : public JALGenericAdaptor<::mlir::ValueRange> {
public:
  using JALGenericAdaptor::JALGenericAdaptor;
  JALAdaptor(JAL op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class JAL : public ::mlir::Op<JAL, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = JALAdaptor;
  template <typename RangeT>
  using GenericAdaptor = JALGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.jal");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm);
  static JAL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm);
  static JAL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static JAL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static JAL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JAL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JAL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JAL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JAL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::JAL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::JALROp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class JALROpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  JALROpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.jalr", odsAttrs.getContext());
  }

  JALROpGenericAdaptorBase(JALROp op);

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
class JALROpGenericAdaptor : public detail::JALROpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::JALROpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  JALROpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  JALROpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : JALROpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  JALROpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : JALROpGenericAdaptor(values, attrs, Properties{}, {}) {}

  JALROpGenericAdaptor(RangeT values, const JALROpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = JALROp, typename = std::enable_if_t<std::is_same_v<LateInst, JALROp>>>
  JALROpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class JALROpAdaptor : public JALROpGenericAdaptor<::mlir::ValueRange> {
public:
  using JALROpGenericAdaptor::JALROpGenericAdaptor;
  JALROpAdaptor(JALROp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class JALROp : public ::mlir::Op<JALROp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = JALROpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = JALROpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.jalr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static JALROp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static JALROp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static JALROp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static JALROp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JALROp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static JALROp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JALROp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static JALROp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::JALROp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LA declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LAGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LAGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.la", odsAttrs.getContext());
  }

  LAGenericAdaptorBase(LA op);

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
class LAGenericAdaptor : public detail::LAGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LAGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_mem = 1;
public:
  LAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LAGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LAGenericAdaptor(values, attrs, Properties{}, {}) {}

  LAGenericAdaptor(RangeT values, const LAGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LA, typename = std::enable_if_t<std::is_same_v<LateInst, LA>>>
  LAGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getMem() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LAAdaptor : public LAGenericAdaptor<::mlir::ValueRange> {
public:
  using LAGenericAdaptor::LAGenericAdaptor;
  LAAdaptor(LA op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LA : public ::mlir::Op<LA, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LAAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LAGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_mem = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.la");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getMem() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getMemMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value mem);
  static LA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value mem);
  static LA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value mem);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem);
  static LA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem);
  static LA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LA)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LBOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LBOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LBOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lb", odsAttrs.getContext());
  }

  LBOpGenericAdaptorBase(LBOp op);

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
class LBOpGenericAdaptor : public detail::LBOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LBOpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  LBOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LBOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LBOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LBOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LBOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LBOpGenericAdaptor(RangeT values, const LBOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LBOp, typename = std::enable_if_t<std::is_same_v<LateInst, LBOp>>>
  LBOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LBOpAdaptor : public LBOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LBOpGenericAdaptor::LBOpGenericAdaptor;
  LBOpAdaptor(LBOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LBOp : public ::mlir::Op<LBOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LBOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LBOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lb");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LBOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LBOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LBOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LBOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LBOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LBUOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LBUOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LBUOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lbu", odsAttrs.getContext());
  }

  LBUOpGenericAdaptorBase(LBUOp op);

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
class LBUOpGenericAdaptor : public detail::LBUOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LBUOpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  LBUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LBUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LBUOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LBUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LBUOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LBUOpGenericAdaptor(RangeT values, const LBUOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LBUOp, typename = std::enable_if_t<std::is_same_v<LateInst, LBUOp>>>
  LBUOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LBUOpAdaptor : public LBUOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LBUOpGenericAdaptor::LBUOpGenericAdaptor;
  LBUOpAdaptor(LBUOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LBUOp : public ::mlir::Op<LBUOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LBUOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LBUOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lbu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LBUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LBUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LBUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LBUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LBUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LBUOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LHOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LHOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LHOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lh", odsAttrs.getContext());
  }

  LHOpGenericAdaptorBase(LHOp op);

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
class LHOpGenericAdaptor : public detail::LHOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LHOpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  LHOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LHOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LHOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LHOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LHOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LHOpGenericAdaptor(RangeT values, const LHOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LHOp, typename = std::enable_if_t<std::is_same_v<LateInst, LHOp>>>
  LHOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LHOpAdaptor : public LHOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LHOpGenericAdaptor::LHOpGenericAdaptor;
  LHOpAdaptor(LHOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LHOp : public ::mlir::Op<LHOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LHOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LHOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lh");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LHOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LHOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LHOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LHOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LHOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LHUOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LHUOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LHUOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lhu", odsAttrs.getContext());
  }

  LHUOpGenericAdaptorBase(LHUOp op);

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
class LHUOpGenericAdaptor : public detail::LHUOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LHUOpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  LHUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LHUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LHUOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LHUOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LHUOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LHUOpGenericAdaptor(RangeT values, const LHUOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LHUOp, typename = std::enable_if_t<std::is_same_v<LateInst, LHUOp>>>
  LHUOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LHUOpAdaptor : public LHUOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LHUOpGenericAdaptor::LHUOpGenericAdaptor;
  LHUOpAdaptor(LHUOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LHUOp : public ::mlir::Op<LHUOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LHUOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LHUOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lhu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LHUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LHUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LHUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LHUOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LHUOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LHUOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LUI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LUIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LUIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lui", odsAttrs.getContext());
  }

  LUIGenericAdaptorBase(LUI op);

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
class LUIGenericAdaptor : public detail::LUIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LUIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
public:
  LUIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LUIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LUIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LUIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LUIGenericAdaptor(values, attrs, Properties{}, {}) {}

  LUIGenericAdaptor(RangeT values, const LUIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LUI, typename = std::enable_if_t<std::is_same_v<LateInst, LUI>>>
  LUIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LUIAdaptor : public LUIGenericAdaptor<::mlir::ValueRange> {
public:
  using LUIGenericAdaptor::LUIGenericAdaptor;
  LUIAdaptor(LUI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LUI : public ::mlir::Op<LUI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LUIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LUIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_imm = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lui");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm);
  static LUI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm);
  static LUI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static LUI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static LUI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LUI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LUI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LUI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LUI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LUI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LWOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LWOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LWOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.lw", odsAttrs.getContext());
  }

  LWOpGenericAdaptorBase(LWOp op);

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
class LWOpGenericAdaptor : public detail::LWOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LWOpGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  LWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LWOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LWOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LWOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LWOpGenericAdaptor(RangeT values, const LWOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LWOp, typename = std::enable_if_t<std::is_same_v<LateInst, LWOp>>>
  LWOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LWOpAdaptor : public LWOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LWOpGenericAdaptor::LWOpGenericAdaptor;
  LWOpAdaptor(LWOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LWOp : public ::mlir::Op<LWOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LWOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LWOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.lw");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static LWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LWOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LWOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::LWOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::OR declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ORGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ORGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.or", odsAttrs.getContext());
  }

  ORGenericAdaptorBase(OR op);

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
class ORGenericAdaptor : public detail::ORGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ORGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  ORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ORGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ORGenericAdaptor(values, attrs, Properties{}, {}) {}

  ORGenericAdaptor(RangeT values, const ORGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OR, typename = std::enable_if_t<std::is_same_v<LateInst, OR>>>
  ORGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ORAdaptor : public ORGenericAdaptor<::mlir::ValueRange> {
public:
  using ORGenericAdaptor::ORGenericAdaptor;
  ORAdaptor(OR op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OR : public ::mlir::Op<OR, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ORAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ORGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.or");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static OR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static OR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static OR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static OR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::OR)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ORI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ORIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ORIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.ori", odsAttrs.getContext());
  }

  ORIGenericAdaptorBase(ORI op);

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
class ORIGenericAdaptor : public detail::ORIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ORIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  ORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ORIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ORIGenericAdaptor(values, attrs, Properties{}, {}) {}

  ORIGenericAdaptor(RangeT values, const ORIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ORI, typename = std::enable_if_t<std::is_same_v<LateInst, ORI>>>
  ORIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ORIAdaptor : public ORIGenericAdaptor<::mlir::ValueRange> {
public:
  using ORIGenericAdaptor::ORIGenericAdaptor;
  ORIAdaptor(ORI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ORI : public ::mlir::Op<ORI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ORIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ORIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.ori");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static ORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::ORI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SB declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SBGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SBGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sb", odsAttrs.getContext());
  }

  SBGenericAdaptorBase(SB op);

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
class SBGenericAdaptor : public detail::SBGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SBGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SBGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SBGenericAdaptor(values, attrs, Properties{}, {}) {}

  SBGenericAdaptor(RangeT values, const SBGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SB, typename = std::enable_if_t<std::is_same_v<LateInst, SB>>>
  SBGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SBAdaptor : public SBGenericAdaptor<::mlir::ValueRange> {
public:
  using SBGenericAdaptor::SBGenericAdaptor;
  SBAdaptor(SB op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SB : public ::mlir::Op<SB, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SBAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SBGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sb");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SB)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SH declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SHGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SHGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sh", odsAttrs.getContext());
  }

  SHGenericAdaptorBase(SH op);

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
class SHGenericAdaptor : public detail::SHGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SHGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SHGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SHGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SHGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SHGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SHGenericAdaptor(values, attrs, Properties{}, {}) {}

  SHGenericAdaptor(RangeT values, const SHGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SH, typename = std::enable_if_t<std::is_same_v<LateInst, SH>>>
  SHGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SHAdaptor : public SHGenericAdaptor<::mlir::ValueRange> {
public:
  using SHGenericAdaptor::SHGenericAdaptor;
  SHAdaptor(SH op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SH : public ::mlir::Op<SH, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SHAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SHGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sh");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SH create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SH create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SH create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SH create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SH create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SH create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SH create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SH create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SH)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLL declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLLGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLLGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sll", odsAttrs.getContext());
  }

  SLLGenericAdaptorBase(SLL op);

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
class SLLGenericAdaptor : public detail::SLLGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLLGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SLLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLLGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLLGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLLGenericAdaptor(RangeT values, const SLLGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLL, typename = std::enable_if_t<std::is_same_v<LateInst, SLL>>>
  SLLGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLLAdaptor : public SLLGenericAdaptor<::mlir::ValueRange> {
public:
  using SLLGenericAdaptor::SLLGenericAdaptor;
  SLLAdaptor(SLL op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLL : public ::mlir::Op<SLL, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLLAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLLGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sll");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLLI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLLIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLLIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.slli", odsAttrs.getContext());
  }

  SLLIGenericAdaptorBase(SLLI op);

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
class SLLIGenericAdaptor : public detail::SLLIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLLIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SLLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLLIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLLIGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLLIGenericAdaptor(RangeT values, const SLLIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLLI, typename = std::enable_if_t<std::is_same_v<LateInst, SLLI>>>
  SLLIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLLIAdaptor : public SLLIGenericAdaptor<::mlir::ValueRange> {
public:
  using SLLIGenericAdaptor::SLLIGenericAdaptor;
  SLLIAdaptor(SLLI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLLI : public ::mlir::Op<SLLI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLLIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLLIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.slli");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLLI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLT declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLTGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLTGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.slt", odsAttrs.getContext());
  }

  SLTGenericAdaptorBase(SLT op);

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
class SLTGenericAdaptor : public detail::SLTGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLTGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLTGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLTGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLTGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLTGenericAdaptor(RangeT values, const SLTGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLT, typename = std::enable_if_t<std::is_same_v<LateInst, SLT>>>
  SLTGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLTAdaptor : public SLTGenericAdaptor<::mlir::ValueRange> {
public:
  using SLTGenericAdaptor::SLTGenericAdaptor;
  SLTAdaptor(SLT op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLT : public ::mlir::Op<SLT, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLTAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLTGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.slt");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLT create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLT create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLT)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLTIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLTIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.slti", odsAttrs.getContext());
  }

  SLTIGenericAdaptorBase(SLTI op);

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
class SLTIGenericAdaptor : public detail::SLTIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLTIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SLTIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLTIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLTIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLTIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLTIGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLTIGenericAdaptor(RangeT values, const SLTIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLTI, typename = std::enable_if_t<std::is_same_v<LateInst, SLTI>>>
  SLTIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLTIAdaptor : public SLTIGenericAdaptor<::mlir::ValueRange> {
public:
  using SLTIGenericAdaptor::SLTIGenericAdaptor;
  SLTIAdaptor(SLTI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLTI : public ::mlir::Op<SLTI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLTIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLTIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.slti");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTIU declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLTIUGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLTIUGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sltiu", odsAttrs.getContext());
  }

  SLTIUGenericAdaptorBase(SLTIU op);

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
class SLTIUGenericAdaptor : public detail::SLTIUGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLTIUGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SLTIUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLTIUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLTIUGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLTIUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLTIUGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLTIUGenericAdaptor(RangeT values, const SLTIUGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLTIU, typename = std::enable_if_t<std::is_same_v<LateInst, SLTIU>>>
  SLTIUGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLTIUAdaptor : public SLTIUGenericAdaptor<::mlir::ValueRange> {
public:
  using SLTIUGenericAdaptor::SLTIUGenericAdaptor;
  SLTIUAdaptor(SLTIU op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLTIU : public ::mlir::Op<SLTIU, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLTIUAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLTIUGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sltiu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTIU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTIU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTIU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SLTIU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTIU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTIU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTIU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTIU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTIU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTU declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SLTUGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SLTUGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sltu", odsAttrs.getContext());
  }

  SLTUGenericAdaptorBase(SLTU op);

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
class SLTUGenericAdaptor : public detail::SLTUGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SLTUGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SLTUGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SLTUGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SLTUGenericAdaptor(values, attrs, Properties{}, {}) {}

  SLTUGenericAdaptor(RangeT values, const SLTUGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SLTU, typename = std::enable_if_t<std::is_same_v<LateInst, SLTU>>>
  SLTUGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SLTUAdaptor : public SLTUGenericAdaptor<::mlir::ValueRange> {
public:
  using SLTUGenericAdaptor::SLTUGenericAdaptor;
  SLTUAdaptor(SLTU op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SLTU : public ::mlir::Op<SLTU, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SLTUAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SLTUGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sltu");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTU create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SLTU create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRA declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SRAGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SRAGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sra", odsAttrs.getContext());
  }

  SRAGenericAdaptorBase(SRA op);

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
class SRAGenericAdaptor : public detail::SRAGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SRAGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SRAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SRAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SRAGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SRAGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SRAGenericAdaptor(values, attrs, Properties{}, {}) {}

  SRAGenericAdaptor(RangeT values, const SRAGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SRA, typename = std::enable_if_t<std::is_same_v<LateInst, SRA>>>
  SRAGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SRAAdaptor : public SRAGenericAdaptor<::mlir::ValueRange> {
public:
  using SRAGenericAdaptor::SRAGenericAdaptor;
  SRAAdaptor(SRA op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SRA : public ::mlir::Op<SRA, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SRAAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SRAGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sra");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRA create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRA create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRA)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRAI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SRAIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SRAIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.srai", odsAttrs.getContext());
  }

  SRAIGenericAdaptorBase(SRAI op);

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
class SRAIGenericAdaptor : public detail::SRAIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SRAIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SRAIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SRAIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SRAIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SRAIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SRAIGenericAdaptor(values, attrs, Properties{}, {}) {}

  SRAIGenericAdaptor(RangeT values, const SRAIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SRAI, typename = std::enable_if_t<std::is_same_v<LateInst, SRAI>>>
  SRAIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SRAIAdaptor : public SRAIGenericAdaptor<::mlir::ValueRange> {
public:
  using SRAIGenericAdaptor::SRAIGenericAdaptor;
  SRAIAdaptor(SRAI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SRAI : public ::mlir::Op<SRAI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SRAIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SRAIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.srai");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRAI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRAI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRAI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRAI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRAI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRAI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRAI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRAI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRAI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRL declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SRLGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SRLGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.srl", odsAttrs.getContext());
  }

  SRLGenericAdaptorBase(SRL op);

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
class SRLGenericAdaptor : public detail::SRLGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SRLGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SRLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SRLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SRLGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SRLGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SRLGenericAdaptor(values, attrs, Properties{}, {}) {}

  SRLGenericAdaptor(RangeT values, const SRLGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SRL, typename = std::enable_if_t<std::is_same_v<LateInst, SRL>>>
  SRLGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SRLAdaptor : public SRLGenericAdaptor<::mlir::ValueRange> {
public:
  using SRLGenericAdaptor::SRLGenericAdaptor;
  SRLAdaptor(SRL op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SRL : public ::mlir::Op<SRL, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SRLAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SRLGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.srl");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SRL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRL create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRL create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRLI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SRLIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SRLIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.srli", odsAttrs.getContext());
  }

  SRLIGenericAdaptorBase(SRLI op);

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
class SRLIGenericAdaptor : public detail::SRLIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SRLIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SRLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SRLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SRLIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SRLIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SRLIGenericAdaptor(values, attrs, Properties{}, {}) {}

  SRLIGenericAdaptor(RangeT values, const SRLIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SRLI, typename = std::enable_if_t<std::is_same_v<LateInst, SRLI>>>
  SRLIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SRLIAdaptor : public SRLIGenericAdaptor<::mlir::ValueRange> {
public:
  using SRLIGenericAdaptor::SRLIGenericAdaptor;
  SRLIAdaptor(SRLI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SRLI : public ::mlir::Op<SRLI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SRLIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SRLIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.srli");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static SRLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SRLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRLI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SRLI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRLI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SUB declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SUBGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SUBGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sub", odsAttrs.getContext());
  }

  SUBGenericAdaptorBase(SUB op);

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
class SUBGenericAdaptor : public detail::SUBGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SUBGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  SUBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SUBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SUBGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SUBGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SUBGenericAdaptor(values, attrs, Properties{}, {}) {}

  SUBGenericAdaptor(RangeT values, const SUBGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SUB, typename = std::enable_if_t<std::is_same_v<LateInst, SUB>>>
  SUBGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SUBAdaptor : public SUBGenericAdaptor<::mlir::ValueRange> {
public:
  using SUBGenericAdaptor::SUBGenericAdaptor;
  SUBAdaptor(SUB op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SUB : public ::mlir::Op<SUB, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SUBAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SUBGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sub");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SUB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SUB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SUB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static SUB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SUB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SUB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SUB create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SUB create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SUB)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SW declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SWGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SWGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.sw", odsAttrs.getContext());
  }

  SWGenericAdaptorBase(SW op);

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
class SWGenericAdaptor : public detail::SWGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SWGenericAdaptorBase;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
public:
  SWGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SWGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SWGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SWGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SWGenericAdaptor(values, attrs, Properties{}, {}) {}

  SWGenericAdaptor(RangeT values, const SWGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SW, typename = std::enable_if_t<std::is_same_v<LateInst, SW>>>
  SWGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRs1() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SWAdaptor : public SWGenericAdaptor<::mlir::ValueRange> {
public:
  using SWGenericAdaptor::SWGenericAdaptor;
  SWAdaptor(SW op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SW : public ::mlir::Op<SW, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SWAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SWGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rs1 = 0;
  static constexpr int odsIndex_rs2 = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.sw");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SW create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SW create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SW create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static SW create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SW create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SW create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SW create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SW create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::SW)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::XOR declarations
//===----------------------------------------------------------------------===//

namespace detail {

class XORGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  XORGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.xor", odsAttrs.getContext());
  }

  XORGenericAdaptorBase(XOR op);

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
class XORGenericAdaptor : public detail::XORGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::XORGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
public:
  XORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  XORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : XORGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  XORGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : XORGenericAdaptor(values, attrs, Properties{}, {}) {}

  XORGenericAdaptor(RangeT values, const XORGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = XOR, typename = std::enable_if_t<std::is_same_v<LateInst, XOR>>>
  XORGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs1() {
    return (*getODSOperands(1).begin());
  }

  ValueT getRs2() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class XORAdaptor : public XORGenericAdaptor<::mlir::ValueRange> {
public:
  using XORGenericAdaptor::XORGenericAdaptor;
  XORAdaptor(XOR op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class XOR : public ::mlir::Op<XOR, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = XORAdaptor;
  template <typename RangeT>
  using GenericAdaptor = XORGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs1 = 1;
  static constexpr int odsIndex_rs2 = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.xor");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs1() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs2() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs1Mutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRs2Mutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static XOR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static XOR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static XOR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static XOR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XOR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XOR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XOR create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XOR create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::XOR)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::XORI declarations
//===----------------------------------------------------------------------===//

namespace detail {

class XORIGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  XORIGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("rtgtest.xori", odsAttrs.getContext());
  }

  XORIGenericAdaptorBase(XORI op);

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
class XORIGenericAdaptor : public detail::XORIGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::XORIGenericAdaptorBase;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
public:
  XORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  XORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : XORIGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  XORIGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : XORIGenericAdaptor(values, attrs, Properties{}, {}) {}

  XORIGenericAdaptor(RangeT values, const XORIGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = XORI, typename = std::enable_if_t<std::is_same_v<LateInst, XORI>>>
  XORIGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRd() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getImm() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class XORIAdaptor : public XORIGenericAdaptor<::mlir::ValueRange> {
public:
  using XORIGenericAdaptor::XORIGenericAdaptor;
  XORIAdaptor(XORI op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class XORI : public ::mlir::Op<XORI, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::circt::rtg::RegisterAllocationOpInterface::Trait, ::circt::rtg::InstructionOpInterface::Trait, ::circt::rtg::InstructionOpAdaptorTrait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = XORIAdaptor;
  template <typename RangeT>
  using GenericAdaptor = XORIGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rd = 0;
  static constexpr int odsIndex_rs = 1;
  static constexpr int odsIndex_imm = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("rtgtest.xori");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRd() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType> getRs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::rtgtest::IntegerRegisterType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getImm() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getRdMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getImmMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static XORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static XORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static XORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static XORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XORI create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XORI create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void printInstructionBinary(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  static void printInstructionAssembly(llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands);
  bool isSourceRegister(unsigned index);
  bool isDestinationRegister(unsigned index);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static void printInstructionBinary(llvm::raw_ostream &os,
                                     FoldAdaptor adaptor);

  static void printInstructionAssembly(llvm::raw_ostream &os,
                                       FoldAdaptor adaptor);

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::XORI)


#endif // GET_OP_CLASSES

