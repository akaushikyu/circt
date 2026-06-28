/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTGTest.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::rtgtest::ADD,
::circt::rtgtest::ADDI,
::circt::rtgtest::AND,
::circt::rtgtest::ANDI,
::circt::rtgtest::AUIPC,
::circt::rtgtest::BEQ,
::circt::rtgtest::BGE,
::circt::rtgtest::BGEU,
::circt::rtgtest::BLT,
::circt::rtgtest::BLTU,
::circt::rtgtest::BNE,
::circt::rtgtest::ConstantTestOp,
::circt::rtgtest::EBREAKOp,
::circt::rtgtest::ECALLOp,
::circt::rtgtest::GetHartIdOp,
::circt::rtgtest::ImplicitConstraintTestOp,
::circt::rtgtest::JAL,
::circt::rtgtest::JALROp,
::circt::rtgtest::LA,
::circt::rtgtest::LBOp,
::circt::rtgtest::LBUOp,
::circt::rtgtest::LHOp,
::circt::rtgtest::LHUOp,
::circt::rtgtest::LUI,
::circt::rtgtest::LWOp,
::circt::rtgtest::OR,
::circt::rtgtest::ORI,
::circt::rtgtest::SB,
::circt::rtgtest::SH,
::circt::rtgtest::SLL,
::circt::rtgtest::SLLI,
::circt::rtgtest::SLT,
::circt::rtgtest::SLTI,
::circt::rtgtest::SLTIU,
::circt::rtgtest::SLTU,
::circt::rtgtest::SRA,
::circt::rtgtest::SRAI,
::circt::rtgtest::SRL,
::circt::rtgtest::SRLI,
::circt::rtgtest::SUB,
::circt::rtgtest::SW,
::circt::rtgtest::XOR,
::circt::rtgtest::XORI
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::rtgtest::IntegerRegisterType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be represents an integer register, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 12)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 12-bit immediate, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 32))) || ((::llvm::isa<::circt::rtg::LabelType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 32-bit immediate or a reference to a label, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 13))) || ((::llvm::isa<::circt::rtg::LabelType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 13-bit immediate or a reference to a label, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::rtgtest::CPUType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be handle to a specific CPU, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::IndexType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be index, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 21))) || ((::llvm::isa<::circt::rtg::LabelType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 21-bit immediate or a reference to a label, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::circt::rtg::MemoryType>(type))) && ((llvm::cast<::circt::rtg::MemoryType>(type).getAddressWidth() == 32))) || (((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 32))) || ((::llvm::isa<::circt::rtg::LabelType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 32-bit addressable memory or a 32-bit immediate or a reference to a label, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_RTGTest10(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::rtg::ImmediateType>(type))) && ((llvm::cast<::circt::rtg::ImmediateType>(type).getWidth() == 5)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a 5-bit immediate, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_RTGTest1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((true)))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_RTGTest1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_RTGTest1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_RTGTest2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_RTGTest2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_RTGTest2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ADD definitions
//===----------------------------------------------------------------------===//

namespace detail {

ADDGenericAdaptorBase::ADDGenericAdaptorBase(ADD op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ADDAdaptor::ADDAdaptor(ADD op) : ADDGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ADDAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ADD::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ADD::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ADD::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ADD::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ADD::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ADD::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ADD::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ADD::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

ADD ADD::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<ADD>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADD ADD::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void ADD::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ADD ADD::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<ADD>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADD ADD::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void ADD::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ADD ADD::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ADD>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADD ADD::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ADD::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ADD ADD::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ADD>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADD ADD::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ADD::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ADD::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ADD::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ADD::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ADD::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void ADD::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ADD)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ADDI definitions
//===----------------------------------------------------------------------===//

namespace detail {

ADDIGenericAdaptorBase::ADDIGenericAdaptorBase(ADDI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ADDIAdaptor::ADDIAdaptor(ADDI op) : ADDIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ADDIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ADDI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ADDI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ADDI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ADDI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ADDI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ADDI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ADDI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ADDI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

ADDI ADDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ADDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADDI ADDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ADDI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ADDI ADDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ADDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADDI ADDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ADDI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ADDI ADDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ADDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADDI ADDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ADDI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ADDI ADDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ADDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ADDI ADDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ADDI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ADDI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ADDI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ADDI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ADDI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void ADDI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ADDI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::AND definitions
//===----------------------------------------------------------------------===//

namespace detail {

ANDGenericAdaptorBase::ANDGenericAdaptorBase(AND op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ANDAdaptor::ANDAdaptor(AND op) : ANDGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ANDAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult AND::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute AND::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AND::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> AND::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void AND::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void AND::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult AND::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void AND::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

AND AND::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<AND>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AND AND::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void AND::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AND AND::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<AND>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AND AND::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void AND::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AND AND::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AND>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AND AND::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AND::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AND AND::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AND>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AND AND::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AND::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AND::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AND::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AND::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void AND::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void AND::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::AND)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ANDI definitions
//===----------------------------------------------------------------------===//

namespace detail {

ANDIGenericAdaptorBase::ANDIGenericAdaptorBase(ANDI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ANDIAdaptor::ANDIAdaptor(ANDI op) : ANDIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ANDIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ANDI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ANDI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ANDI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ANDI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ANDI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ANDI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ANDI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ANDI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

ANDI ANDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ANDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ANDI ANDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ANDI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ANDI ANDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ANDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ANDI ANDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ANDI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ANDI ANDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ANDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ANDI ANDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ANDI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ANDI ANDI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ANDI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ANDI ANDI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ANDI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ANDI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ANDI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ANDI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ANDI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void ANDI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ANDI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::AUIPC definitions
//===----------------------------------------------------------------------===//

namespace detail {

AUIPCGenericAdaptorBase::AUIPCGenericAdaptorBase(AUIPC op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
AUIPCAdaptor::AUIPCAdaptor(AUIPC op) : AUIPCGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AUIPCAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult AUIPC::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute AUIPC::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AUIPC::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> AUIPC::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void AUIPC::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void AUIPC::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult AUIPC::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void AUIPC::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
}

AUIPC AUIPC::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<AUIPC>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AUIPC AUIPC::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void AUIPC::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AUIPC AUIPC::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<AUIPC>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AUIPC AUIPC::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void AUIPC::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AUIPC AUIPC::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AUIPC>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AUIPC AUIPC::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AUIPC::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AUIPC AUIPC::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AUIPC>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AUIPC AUIPC::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AUIPC::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AUIPC::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AUIPC::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    immRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AUIPC::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getImm().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void AUIPC::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void AUIPC::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::AUIPC)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BEQ definitions
//===----------------------------------------------------------------------===//

namespace detail {

BEQGenericAdaptorBase::BEQGenericAdaptorBase(BEQ op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BEQAdaptor::BEQAdaptor(BEQ op) : BEQGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BEQAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BEQ::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BEQ::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BEQ::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BEQ::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BEQ::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BEQ::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BEQ::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BEQ::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BEQ BEQ::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BEQ>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BEQ BEQ::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BEQ::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BEQ BEQ::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BEQ>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BEQ BEQ::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BEQ::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BEQ BEQ::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BEQ>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BEQ BEQ::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BEQ::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BEQ BEQ::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BEQ>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BEQ BEQ::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BEQ::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BEQ::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BEQ::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BEQ::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BEQ::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BEQ::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BEQ)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BGE definitions
//===----------------------------------------------------------------------===//

namespace detail {

BGEGenericAdaptorBase::BGEGenericAdaptorBase(BGE op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BGEAdaptor::BGEAdaptor(BGE op) : BGEGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BGEAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BGE::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BGE::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BGE::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BGE::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BGE::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BGE::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BGE::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BGE::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BGE BGE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BGE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGE BGE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BGE::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BGE BGE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BGE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGE BGE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BGE::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BGE BGE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BGE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGE BGE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BGE::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BGE BGE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BGE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGE BGE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BGE::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BGE::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BGE::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BGE::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BGE::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BGE::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BGE)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BGEU definitions
//===----------------------------------------------------------------------===//

namespace detail {

BGEUGenericAdaptorBase::BGEUGenericAdaptorBase(BGEU op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BGEUAdaptor::BGEUAdaptor(BGEU op) : BGEUGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BGEUAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BGEU::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BGEU::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BGEU::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BGEU::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BGEU::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BGEU::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BGEU::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BGEU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BGEU BGEU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BGEU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGEU BGEU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BGEU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BGEU BGEU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BGEU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGEU BGEU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BGEU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BGEU BGEU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BGEU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGEU BGEU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BGEU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BGEU BGEU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BGEU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BGEU BGEU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BGEU::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BGEU::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BGEU::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BGEU::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BGEU::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BGEU::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BGEU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BLT definitions
//===----------------------------------------------------------------------===//

namespace detail {

BLTGenericAdaptorBase::BLTGenericAdaptorBase(BLT op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BLTAdaptor::BLTAdaptor(BLT op) : BLTGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BLTAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BLT::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BLT::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BLT::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BLT::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BLT::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BLT::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BLT::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BLT::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BLT BLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLT BLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BLT::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BLT BLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLT BLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BLT::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BLT BLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLT BLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BLT::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BLT BLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLT BLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BLT::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BLT::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BLT::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BLT::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BLT::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BLT::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BLT)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BLTU definitions
//===----------------------------------------------------------------------===//

namespace detail {

BLTUGenericAdaptorBase::BLTUGenericAdaptorBase(BLTU op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BLTUAdaptor::BLTUAdaptor(BLTU op) : BLTUGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BLTUAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BLTU::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BLTU::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BLTU::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BLTU::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BLTU::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BLTU::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BLTU::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BLTU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BLTU BLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLTU BLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BLTU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BLTU BLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLTU BLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BLTU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BLTU BLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLTU BLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BLTU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BLTU BLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BLTU BLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BLTU::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BLTU::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BLTU::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BLTU::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BLTU::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BLTU::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BLTU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::BNE definitions
//===----------------------------------------------------------------------===//

namespace detail {

BNEGenericAdaptorBase::BNEGenericAdaptorBase(BNE op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BNEAdaptor::BNEAdaptor(BNE op) : BNEGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BNEAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BNE::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BNE::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BNE::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BNE::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BNE::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BNE::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BNE::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BNE::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

BNE BNE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BNE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BNE BNE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BNE::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BNE BNE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<BNE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BNE BNE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void BNE::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BNE BNE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BNE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BNE BNE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BNE::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BNE BNE::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BNE>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BNE BNE::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BNE::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BNE::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult BNE::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(immRawType))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BNE::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getImm().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void BNE::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void BNE::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::BNE)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ConstantTestOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConstantTestOpGenericAdaptorBase::ConstantTestOpGenericAdaptorBase(ConstantTestOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::Attribute ConstantTestOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr;
}


} // namespace detail
ConstantTestOpAdaptor::ConstantTestOpAdaptor(ConstantTestOp op) : ConstantTestOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConstantTestOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'rtgtest.constant_test' op requires attribute 'value'");

  if (tblgen_value && !((true)))
    return emitError(loc, "'rtgtest.constant_test' op attribute 'value' failed to satisfy constraint: any attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ConstantTestOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.value;
       auto attr = dict.get("value");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ConstantTestOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.value;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("value",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConstantTestOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ConstantTestOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ConstantTestOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ConstantTestOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ConstantTestOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_RTGTest1(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ConstantTestOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ConstantTestOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.value);
}

::mlir::Attribute ConstantTestOp::getValue() {
  auto attr = getValueAttr();
  return attr;
}

void ConstantTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute value) {
  odsState.getOrAddProperties<Properties>().value = value;
  odsState.addTypes(result);
}

ConstantTestOp ConstantTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantTestOp ConstantTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ConstantTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  odsState.getOrAddProperties<Properties>().value = value;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConstantTestOp ConstantTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantTestOp ConstantTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ConstantTestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ConstantTestOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ConstantTestOp ConstantTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstantTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantTestOp ConstantTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstantTestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConstantTestOp ConstantTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstantTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantTestOp ConstantTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConstantTestOp::verifyInvariantsImpl() {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_RTGTest1(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConstantTestOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ConstantTestOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void ConstantTestOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ConstantTestOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ConstantTestOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::detail::ConstantTestOpGenericAdaptorBase::Properties)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::EBREAKOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EBREAKOpGenericAdaptorBase::EBREAKOpGenericAdaptorBase(EBREAKOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
EBREAKOpAdaptor::EBREAKOpAdaptor(EBREAKOp op) : EBREAKOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EBREAKOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult EBREAKOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute EBREAKOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EBREAKOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> EBREAKOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void EBREAKOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void EBREAKOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult EBREAKOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void EBREAKOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
}

EBREAKOp EBREAKOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<EBREAKOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EBREAKOp EBREAKOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void EBREAKOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EBREAKOp EBREAKOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<EBREAKOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EBREAKOp EBREAKOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void EBREAKOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EBREAKOp EBREAKOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EBREAKOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EBREAKOp EBREAKOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EBREAKOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EBREAKOp EBREAKOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EBREAKOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EBREAKOp EBREAKOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EBREAKOp::verifyInvariantsImpl() {
  return ::mlir::success();
}

::llvm::LogicalResult EBREAKOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult EBREAKOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void EBREAKOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void EBREAKOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void EBREAKOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::EBREAKOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ECALLOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ECALLOpGenericAdaptorBase::ECALLOpGenericAdaptorBase(ECALLOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ECALLOpAdaptor::ECALLOpAdaptor(ECALLOp op) : ECALLOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ECALLOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ECALLOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ECALLOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ECALLOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ECALLOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ECALLOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ECALLOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ECALLOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ECALLOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
}

ECALLOp ECALLOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<ECALLOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ECALLOp ECALLOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void ECALLOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ECALLOp ECALLOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<ECALLOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ECALLOp ECALLOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void ECALLOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ECALLOp ECALLOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ECALLOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ECALLOp ECALLOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ECALLOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ECALLOp ECALLOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ECALLOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ECALLOp ECALLOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ECALLOp::verifyInvariantsImpl() {
  return ::mlir::success();
}

::llvm::LogicalResult ECALLOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ECALLOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ECALLOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ECALLOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void ECALLOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ECALLOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::GetHartIdOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GetHartIdOpGenericAdaptorBase::GetHartIdOpGenericAdaptorBase(GetHartIdOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
GetHartIdOpAdaptor::GetHartIdOpAdaptor(GetHartIdOp op) : GetHartIdOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GetHartIdOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult GetHartIdOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute GetHartIdOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GetHartIdOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> GetHartIdOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GetHartIdOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GetHartIdOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GetHartIdOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void GetHartIdOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type hartid, ::mlir::Value cpu) {
  odsState.addOperands(cpu);
  odsState.addTypes(hartid);
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type hartid, ::mlir::Value cpu) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(hartid)>(hartid), std::forward<decltype(cpu)>(cpu));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type hartid, ::mlir::Value cpu) {
  return create(builder, builder.getLoc(), std::forward<decltype(hartid)>(hartid), std::forward<decltype(cpu)>(cpu));
}

void GetHartIdOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cpu) {
  odsState.addOperands(cpu);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(GetHartIdOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cpu) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cpu)>(cpu));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cpu) {
  return create(builder, builder.getLoc(), std::forward<decltype(cpu)>(cpu));
}

void GetHartIdOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cpu) {
  odsState.addOperands(cpu);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cpu) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cpu)>(cpu));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cpu) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cpu)>(cpu));
}

void GetHartIdOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetHartIdOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetHartIdOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetHartIdOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GetHartIdOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(GetHartIdOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

GetHartIdOp GetHartIdOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetHartIdOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetHartIdOp GetHartIdOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GetHartIdOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GetHartIdOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult GetHartIdOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIndexType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult GetHartIdOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand cpuRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> cpuOperands(&cpuRawOperand, 1);  ::llvm::SMLoc cpuOperandsLoc;
  (void)cpuOperandsLoc;

  cpuOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(cpuRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIndexType();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getType<::circt::rtgtest::CPUType>();
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(cpuOperands, odsBuildableType1, cpuOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetHartIdOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCpu();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void GetHartIdOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::GetHartIdOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ImplicitConstraintTestOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ImplicitConstraintTestOpGenericAdaptorBase::ImplicitConstraintTestOpGenericAdaptorBase(ImplicitConstraintTestOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ImplicitConstraintTestOpGenericAdaptorBase::getImplicitConstraintAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().implicitConstraint);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ImplicitConstraintTestOpGenericAdaptorBase::getImplicitConstraint() {
  auto attr = getImplicitConstraintAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ImplicitConstraintTestOpAdaptor::ImplicitConstraintTestOpAdaptor(ImplicitConstraintTestOp op) : ImplicitConstraintTestOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ImplicitConstraintTestOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_implicitConstraint = getProperties().implicitConstraint; (void)tblgen_implicitConstraint;

  if (tblgen_implicitConstraint && !((::llvm::isa<::mlir::UnitAttr>(tblgen_implicitConstraint))))
    return emitError(loc, "'rtgtest.implicit_constraint_op' op attribute 'implicitConstraint' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ImplicitConstraintTestOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.implicitConstraint;
       auto attr = dict.get("implicitConstraint");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `implicitConstraint` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ImplicitConstraintTestOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.implicitConstraint;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("implicitConstraint",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ImplicitConstraintTestOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.implicitConstraint.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ImplicitConstraintTestOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "implicitConstraint")
      return prop.implicitConstraint;
  return std::nullopt;
}

void ImplicitConstraintTestOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "implicitConstraint") {
       prop.implicitConstraint = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.implicitConstraint)>>(value);
       return;
    }
}

void ImplicitConstraintTestOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.implicitConstraint) attrs.append("implicitConstraint", prop.implicitConstraint);
}

::llvm::LogicalResult ImplicitConstraintTestOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getImplicitConstraintAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_RTGTest2(attr, "implicitConstraint", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ImplicitConstraintTestOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.implicitConstraint)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ImplicitConstraintTestOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.implicitConstraint);
}

bool ImplicitConstraintTestOp::getImplicitConstraint() {
  auto attr = getImplicitConstraintAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ImplicitConstraintTestOp::setImplicitConstraint(bool attrValue) {
    auto &odsProp = getProperties().implicitConstraint;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::UnitAttr implicitConstraint) {
  if (implicitConstraint) {
    odsState.getOrAddProperties<Properties>().implicitConstraint = implicitConstraint;
  }
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::UnitAttr implicitConstraint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(implicitConstraint)>(implicitConstraint));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::UnitAttr implicitConstraint) {
  return create(builder, builder.getLoc(), std::forward<decltype(implicitConstraint)>(implicitConstraint));
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint) {
  if (implicitConstraint) {
    odsState.getOrAddProperties<Properties>().implicitConstraint = implicitConstraint;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(implicitConstraint)>(implicitConstraint));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::UnitAttr implicitConstraint) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(implicitConstraint)>(implicitConstraint));
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/bool implicitConstraint) {
  if (implicitConstraint) {
    odsState.getOrAddProperties<Properties>().implicitConstraint = ((implicitConstraint) ? odsBuilder.getUnitAttr() : nullptr);
  }
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/bool implicitConstraint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(implicitConstraint)>(implicitConstraint));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/bool implicitConstraint) {
  return create(builder, builder.getLoc(), std::forward<decltype(implicitConstraint)>(implicitConstraint));
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint) {
  if (implicitConstraint) {
    odsState.getOrAddProperties<Properties>().implicitConstraint = ((implicitConstraint) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(implicitConstraint)>(implicitConstraint));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/bool implicitConstraint) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(implicitConstraint)>(implicitConstraint));
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ImplicitConstraintTestOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ImplicitConstraintTestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ImplicitConstraintTestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ImplicitConstraintTestOp ImplicitConstraintTestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ImplicitConstraintTestOp::verifyInvariantsImpl() {
  auto tblgen_implicitConstraint = getProperties().implicitConstraint; (void)tblgen_implicitConstraint;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_RTGTest2(*this, tblgen_implicitConstraint, "implicitConstraint")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ImplicitConstraintTestOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ImplicitConstraintTestOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  if (::mlir::succeeded(parser.parseOptionalKeyword("implicit_constraint"))) {
    result.getOrAddProperties<ImplicitConstraintTestOp::Properties>().implicitConstraint = parser.getBuilder().getUnitAttr();  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ImplicitConstraintTestOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getImplicitConstraintAttr() && getImplicitConstraintAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "implicit_constraint";
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("implicitConstraint");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getImplicitConstraintAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("implicitConstraint");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ImplicitConstraintTestOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::detail::ImplicitConstraintTestOpGenericAdaptorBase::Properties)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::JAL definitions
//===----------------------------------------------------------------------===//

namespace detail {

JALGenericAdaptorBase::JALGenericAdaptorBase(JAL op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
JALAdaptor::JALAdaptor(JAL op) : JALGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult JALAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult JAL::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute JAL::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code JAL::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> JAL::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void JAL::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void JAL::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult JAL::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void JAL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
}

JAL JAL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<JAL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JAL JAL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void JAL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

JAL JAL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<JAL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JAL JAL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void JAL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

JAL JAL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<JAL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JAL JAL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void JAL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

JAL JAL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<JAL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JAL JAL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult JAL::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult JAL::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult JAL::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    immRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void JAL::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getImm().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void JAL::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void JAL::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::JAL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::JALROp definitions
//===----------------------------------------------------------------------===//

namespace detail {

JALROpGenericAdaptorBase::JALROpGenericAdaptorBase(JALROp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
JALROpAdaptor::JALROpAdaptor(JALROp op) : JALROpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult JALROpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult JALROp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute JALROp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code JALROp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> JALROp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void JALROp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void JALROp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult JALROp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void JALROp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

JALROp JALROp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<JALROp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JALROp JALROp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void JALROp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

JALROp JALROp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<JALROp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JALROp JALROp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void JALROp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

JALROp JALROp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<JALROp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JALROp JALROp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void JALROp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

JALROp JALROp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<JALROp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

JALROp JALROp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult JALROp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult JALROp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult JALROp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void JALROp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void JALROp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void JALROp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::JALROp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LA definitions
//===----------------------------------------------------------------------===//

namespace detail {

LAGenericAdaptorBase::LAGenericAdaptorBase(LA op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LAAdaptor::LAAdaptor(LA op) : LAGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LAAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LA::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LA::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LA::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LA::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LA::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LA::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LA::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LA::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value mem) {
  odsState.addOperands(rd);
  odsState.addOperands(mem);
}

LA LA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value mem) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(mem)>(mem));
  auto __res__ = ::llvm::dyn_cast<LA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LA LA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value mem) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(mem)>(mem));
}

void LA::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem) {
  odsState.addOperands(rd);
  odsState.addOperands(mem);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LA LA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(mem)>(mem));
  auto __res__ = ::llvm::dyn_cast<LA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LA LA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value mem) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(mem)>(mem));
}

void LA::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LA LA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LA LA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LA::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LA LA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LA LA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LA::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LA::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LA::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand memRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memOperands(&memRawOperand, 1);  ::llvm::SMLoc memOperandsLoc;
  (void)memOperandsLoc;
  ::mlir::Type memRawType{};
  ::llvm::ArrayRef<::mlir::Type> memTypes(&memRawType, 1);

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  memOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    memRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(memOperands, memTypes, memOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LA::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getMem();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getMem().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LA::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LA::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LA)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LBOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LBOpGenericAdaptorBase::LBOpGenericAdaptorBase(LBOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LBOpAdaptor::LBOpAdaptor(LBOp op) : LBOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LBOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LBOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LBOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LBOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LBOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LBOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LBOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LBOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LBOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

LBOp LBOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LBOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBOp LBOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LBOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LBOp LBOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LBOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBOp LBOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LBOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LBOp LBOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LBOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBOp LBOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LBOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LBOp LBOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LBOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBOp LBOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LBOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LBOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LBOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LBOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LBOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LBOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LBOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LBUOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LBUOpGenericAdaptorBase::LBUOpGenericAdaptorBase(LBUOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LBUOpAdaptor::LBUOpAdaptor(LBUOp op) : LBUOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LBUOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LBUOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LBUOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LBUOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LBUOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LBUOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LBUOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LBUOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LBUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

LBUOp LBUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LBUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBUOp LBUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LBUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LBUOp LBUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LBUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBUOp LBUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LBUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LBUOp LBUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LBUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBUOp LBUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LBUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LBUOp LBUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LBUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LBUOp LBUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LBUOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LBUOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LBUOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LBUOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LBUOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LBUOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LBUOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LHOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LHOpGenericAdaptorBase::LHOpGenericAdaptorBase(LHOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LHOpAdaptor::LHOpAdaptor(LHOp op) : LHOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LHOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LHOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LHOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LHOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LHOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LHOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LHOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LHOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LHOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

LHOp LHOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LHOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHOp LHOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LHOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LHOp LHOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LHOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHOp LHOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LHOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LHOp LHOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LHOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHOp LHOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LHOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LHOp LHOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LHOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHOp LHOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LHOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LHOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LHOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LHOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LHOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LHOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LHOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LHUOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LHUOpGenericAdaptorBase::LHUOpGenericAdaptorBase(LHUOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LHUOpAdaptor::LHUOpAdaptor(LHUOp op) : LHUOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LHUOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LHUOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LHUOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LHUOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LHUOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LHUOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LHUOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LHUOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LHUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

LHUOp LHUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LHUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHUOp LHUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LHUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LHUOp LHUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LHUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHUOp LHUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LHUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LHUOp LHUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LHUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHUOp LHUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LHUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LHUOp LHUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LHUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LHUOp LHUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LHUOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LHUOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LHUOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LHUOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LHUOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LHUOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LHUOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LUI definitions
//===----------------------------------------------------------------------===//

namespace detail {

LUIGenericAdaptorBase::LUIGenericAdaptorBase(LUI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LUIAdaptor::LUIAdaptor(LUI op) : LUIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LUIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LUI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LUI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LUI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LUI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LUI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LUI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LUI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LUI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
}

LUI LUI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LUI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LUI LUI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void LUI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LUI LUI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LUI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LUI LUI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(imm)>(imm));
}

void LUI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LUI LUI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LUI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LUI LUI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LUI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LUI LUI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LUI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LUI LUI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LUI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LUI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LUI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;
  ::mlir::Type immRawType{};
  ::llvm::ArrayRef<::mlir::Type> immTypes(&immRawType, 1);

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    immRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, immTypes, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LUI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getImm().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LUI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LUI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LUI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::LWOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LWOpGenericAdaptorBase::LWOpGenericAdaptorBase(LWOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LWOpAdaptor::LWOpAdaptor(LWOp op) : LWOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LWOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult LWOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LWOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LWOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LWOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LWOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LWOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LWOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LWOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

LWOp LWOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LWOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LWOp LWOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LWOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LWOp LWOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<LWOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LWOp LWOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void LWOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LWOp LWOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LWOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LWOp LWOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LWOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LWOp LWOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LWOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LWOp LWOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LWOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LWOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LWOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LWOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void LWOp::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void LWOp::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::LWOp)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::OR definitions
//===----------------------------------------------------------------------===//

namespace detail {

ORGenericAdaptorBase::ORGenericAdaptorBase(OR op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ORAdaptor::ORAdaptor(OR op) : ORGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ORAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult OR::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute OR::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OR::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> OR::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void OR::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void OR::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult OR::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void OR::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

OR OR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<OR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OR OR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void OR::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OR OR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<OR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OR OR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void OR::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OR OR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OR OR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OR::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OR OR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OR OR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OR::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OR::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OR::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void OR::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void OR::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void OR::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::OR)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::ORI definitions
//===----------------------------------------------------------------------===//

namespace detail {

ORIGenericAdaptorBase::ORIGenericAdaptorBase(ORI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ORIAdaptor::ORIAdaptor(ORI op) : ORIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ORIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ORI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ORI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ORI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ORI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ORI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ORI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ORI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ORI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

ORI ORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ORI ORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ORI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ORI ORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<ORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ORI ORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void ORI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ORI ORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ORI ORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ORI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ORI ORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ORI ORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ORI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ORI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ORI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ORI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ORI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void ORI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::ORI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SB definitions
//===----------------------------------------------------------------------===//

namespace detail {

SBGenericAdaptorBase::SBGenericAdaptorBase(SB op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SBAdaptor::SBAdaptor(SB op) : SBGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SBAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SB::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SB::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SB::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SB::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SB::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SB::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SB::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SB::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

SB SB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SB SB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SB::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SB SB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SB SB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SB::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SB SB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SB SB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SB::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SB SB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SB SB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SB::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SB::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SB::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SB::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SB::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SB::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SB)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SH definitions
//===----------------------------------------------------------------------===//

namespace detail {

SHGenericAdaptorBase::SHGenericAdaptorBase(SH op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SHAdaptor::SHAdaptor(SH op) : SHGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SHAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SH::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SH::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SH::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SH::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SH::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SH::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SH::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SH::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

SH SH::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SH>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SH SH::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SH::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SH SH::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SH>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SH SH::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SH::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SH SH::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SH>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SH SH::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SH::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SH SH::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SH>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SH SH::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SH::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SH::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SH::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SH::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SH::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SH::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SH)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLL definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLLGenericAdaptorBase::SLLGenericAdaptorBase(SLL op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLLAdaptor::SLLAdaptor(SLL op) : SLLGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLLAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLL::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLL::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLL::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLL::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLL::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLL::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLL::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SLL SLL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLL SLL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLL SLL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLL SLL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLL SLL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLL SLL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLL SLL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLL SLL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLL::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLL::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLL::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLL::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLL::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLL::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLLI definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLLIGenericAdaptorBase::SLLIGenericAdaptorBase(SLLI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLLIAdaptor::SLLIAdaptor(SLLI op) : SLLIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLLIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLLI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLLI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLLI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLLI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLLI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLLI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLLI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLLI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

SLLI SLLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLLI SLLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLLI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLLI SLLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLLI SLLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLLI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLLI SLLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLLI SLLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLLI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLLI SLLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLLI SLLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLLI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest10(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLLI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLLI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 5);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLLI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLLI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLLI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLLI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLT definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLTGenericAdaptorBase::SLTGenericAdaptorBase(SLT op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLTAdaptor::SLTAdaptor(SLT op) : SLTGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLTAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLT::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLT::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLT::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLT::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLT::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLT::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLT::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLT::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SLT SLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLT SLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLT::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLT SLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLT SLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLT::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLT SLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLT SLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLT::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLT SLT::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLT>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLT SLT::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLT::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLT::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLT::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLT::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLT::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLT::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLT)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTI definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLTIGenericAdaptorBase::SLTIGenericAdaptorBase(SLTI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLTIAdaptor::SLTIAdaptor(SLTI op) : SLTIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLTIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLTI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLTI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLTI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLTI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLTI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLTI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLTI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLTI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

SLTI SLTI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLTI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTI SLTI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLTI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLTI SLTI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLTI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTI SLTI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLTI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTI SLTI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLTI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTI SLTI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLTI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTI SLTI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLTI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTI SLTI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLTI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLTI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLTI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLTI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLTI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLTI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTIU definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLTIUGenericAdaptorBase::SLTIUGenericAdaptorBase(SLTIU op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLTIUAdaptor::SLTIUAdaptor(SLTIU op) : SLTIUGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLTIUAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLTIU::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLTIU::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLTIU::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLTIU::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLTIU::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLTIU::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLTIU::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLTIU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

SLTIU SLTIU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLTIU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTIU SLTIU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLTIU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLTIU SLTIU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SLTIU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTIU SLTIU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SLTIU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTIU SLTIU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLTIU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTIU SLTIU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLTIU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTIU SLTIU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLTIU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTIU SLTIU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLTIU::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLTIU::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLTIU::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLTIU::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLTIU::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLTIU::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTIU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SLTU definitions
//===----------------------------------------------------------------------===//

namespace detail {

SLTUGenericAdaptorBase::SLTUGenericAdaptorBase(SLTU op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SLTUAdaptor::SLTUAdaptor(SLTU op) : SLTUGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SLTUAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SLTU::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SLTU::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SLTU::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SLTU::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SLTU::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SLTU::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SLTU::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SLTU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SLTU SLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTU SLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLTU::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SLTU SLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTU SLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SLTU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTU SLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTU SLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SLTU::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SLTU SLTU::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SLTU>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SLTU SLTU::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SLTU::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SLTU::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SLTU::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SLTU::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SLTU::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SLTU::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SLTU)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRA definitions
//===----------------------------------------------------------------------===//

namespace detail {

SRAGenericAdaptorBase::SRAGenericAdaptorBase(SRA op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SRAAdaptor::SRAAdaptor(SRA op) : SRAGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SRAAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SRA::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SRA::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SRA::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SRA::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SRA::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SRA::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SRA::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SRA::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SRA SRA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SRA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRA SRA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SRA::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SRA SRA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SRA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRA SRA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SRA::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRA SRA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SRA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRA SRA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SRA::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRA SRA::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SRA>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRA SRA::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SRA::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SRA::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SRA::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SRA::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SRA::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SRA::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRA)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRAI definitions
//===----------------------------------------------------------------------===//

namespace detail {

SRAIGenericAdaptorBase::SRAIGenericAdaptorBase(SRAI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SRAIAdaptor::SRAIAdaptor(SRAI op) : SRAIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SRAIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SRAI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SRAI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SRAI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SRAI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SRAI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SRAI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SRAI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SRAI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

SRAI SRAI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SRAI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRAI SRAI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SRAI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SRAI SRAI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SRAI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRAI SRAI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SRAI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRAI SRAI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SRAI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRAI SRAI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SRAI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRAI SRAI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SRAI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRAI SRAI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SRAI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest10(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SRAI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SRAI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 5);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SRAI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SRAI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SRAI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRAI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRL definitions
//===----------------------------------------------------------------------===//

namespace detail {

SRLGenericAdaptorBase::SRLGenericAdaptorBase(SRL op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SRLAdaptor::SRLAdaptor(SRL op) : SRLGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SRLAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SRL::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SRL::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SRL::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SRL::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SRL::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SRL::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SRL::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SRL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SRL SRL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SRL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRL SRL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SRL::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SRL SRL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SRL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRL SRL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SRL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRL SRL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SRL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRL SRL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SRL::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRL SRL::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SRL>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRL SRL::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SRL::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SRL::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SRL::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SRL::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SRL::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SRL::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRL)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SRLI definitions
//===----------------------------------------------------------------------===//

namespace detail {

SRLIGenericAdaptorBase::SRLIGenericAdaptorBase(SRLI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SRLIAdaptor::SRLIAdaptor(SRLI op) : SRLIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SRLIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SRLI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SRLI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SRLI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SRLI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SRLI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SRLI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SRLI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SRLI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

SRLI SRLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SRLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRLI SRLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SRLI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SRLI SRLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SRLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRLI SRLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void SRLI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRLI SRLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SRLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRLI SRLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SRLI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SRLI SRLI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SRLI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SRLI SRLI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SRLI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest10(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SRLI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SRLI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 5);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SRLI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SRLI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SRLI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SRLI)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SUB definitions
//===----------------------------------------------------------------------===//

namespace detail {

SUBGenericAdaptorBase::SUBGenericAdaptorBase(SUB op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SUBAdaptor::SUBAdaptor(SUB op) : SUBGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SUBAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SUB::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SUB::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SUB::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SUB::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SUB::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SUB::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SUB::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SUB::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

SUB SUB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SUB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SUB SUB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SUB::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SUB SUB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<SUB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SUB SUB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void SUB::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SUB SUB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SUB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SUB SUB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SUB::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SUB SUB::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SUB>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SUB SUB::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SUB::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SUB::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SUB::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SUB::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SUB::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SUB::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SUB)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::SW definitions
//===----------------------------------------------------------------------===//

namespace detail {

SWGenericAdaptorBase::SWGenericAdaptorBase(SW op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SWAdaptor::SWAdaptor(SW op) : SWGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SWAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SW::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SW::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SW::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SW::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SW::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SW::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SW::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SW::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
}

SW SW::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SW>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SW SW::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SW::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SW SW::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<SW>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SW SW::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rs1, ::mlir::Value rs2, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2), std::forward<decltype(imm)>(imm));
}

void SW::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SW SW::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SW>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SW SW::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SW::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SW SW::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SW>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SW SW::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SW::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SW::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SW::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SW::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SW::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void SW::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::SW)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::XOR definitions
//===----------------------------------------------------------------------===//

namespace detail {

XORGenericAdaptorBase::XORGenericAdaptorBase(XOR op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
XORAdaptor::XORAdaptor(XOR op) : XORGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult XORAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult XOR::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute XOR::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code XOR::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> XOR::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void XOR::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void XOR::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult XOR::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void XOR::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
}

XOR XOR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<XOR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XOR XOR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void XOR::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  odsState.addOperands(rd);
  odsState.addOperands(rs1);
  odsState.addOperands(rs2);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XOR XOR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
  auto __res__ = ::llvm::dyn_cast<XOR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XOR XOR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs1, ::mlir::Value rs2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs1)>(rs1), std::forward<decltype(rs2)>(rs2));
}

void XOR::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XOR XOR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XOR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XOR XOR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XOR::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XOR XOR::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XOR>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XOR XOR::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult XOR::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult XOR::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult XOR::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs1RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs1Operands(&rs1RawOperand, 1);  ::llvm::SMLoc rs1OperandsLoc;
  (void)rs1OperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rs2RawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rs2Operands(&rs2RawOperand, 1);  ::llvm::SMLoc rs2OperandsLoc;
  (void)rs2OperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs1OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs1RawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rs2OperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rs2RawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs1Operands, odsBuildableType0, rs1OperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rs2Operands, odsBuildableType0, rs2OperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void XOR::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs1();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs2();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void XOR::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void XOR::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::XOR)

namespace circt::rtgtest {


//===----------------------------------------------------------------------===//
// ::circt::rtgtest::XORI definitions
//===----------------------------------------------------------------------===//

namespace detail {

XORIGenericAdaptorBase::XORIGenericAdaptorBase(XORI op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
XORIAdaptor::XORIAdaptor(XORI op) : XORIGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult XORIAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult XORI::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute XORI::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code XORI::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> XORI::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void XORI::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void XORI::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult XORI::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void XORI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
}

XORI XORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<XORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XORI XORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void XORI::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  odsState.addOperands(rd);
  odsState.addOperands(rs);
  odsState.addOperands(imm);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XORI XORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
  auto __res__ = ::llvm::dyn_cast<XORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XORI XORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rd, ::mlir::Value rs, ::mlir::Value imm) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rd)>(rd), std::forward<decltype(rs)>(rs), std::forward<decltype(imm)>(imm));
}

void XORI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XORI XORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XORI XORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XORI::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XORI XORI::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XORI>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XORI XORI::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult XORI::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_RTGTest2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult XORI::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult XORI::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rdRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdOperands(&rdRawOperand, 1);  ::llvm::SMLoc rdOperandsLoc;
  (void)rdOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rsOperands(&rsRawOperand, 1);  ::llvm::SMLoc rsOperandsLoc;
  (void)rsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand immRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> immOperands(&immRawOperand, 1);  ::llvm::SMLoc immOperandsLoc;
  (void)immOperandsLoc;

  rdOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  immOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(immRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::rtgtest::IntegerRegisterType>();
  ::mlir::Type odsBuildableType1 = ::circt::rtg::ImmediateType::get(parser.getBuilder().getContext(), 12);
  if (parser.resolveOperands(rdOperands, odsBuildableType0, rdOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rsOperands, odsBuildableType0, rsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(immOperands, odsBuildableType1, immOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void XORI::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRd();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getImm();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void XORI::printInstructionBinary(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionBinary(os, FoldAdaptor(operands));
}

void XORI::printInstructionAssembly(
    llvm::raw_ostream &os, llvm::ArrayRef<mlir::Attribute> operands) {
  printInstructionAssembly(os, FoldAdaptor(operands));
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::XORI)


#endif // GET_OP_CLASSES

