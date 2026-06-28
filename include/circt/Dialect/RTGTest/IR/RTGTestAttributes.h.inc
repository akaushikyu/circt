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
namespace circt::rtgtest {

/// this attribute represents a CPU referred to by the core ID
class CPUAttr;
class RegZeroAttr;
class RegRaAttr;
class RegSpAttr;
class RegGpAttr;
class RegTpAttr;
class RegT0Attr;
class RegT1Attr;
class RegT2Attr;
class RegS0Attr;
class RegS1Attr;
class RegA0Attr;
class RegA1Attr;
class RegA2Attr;
class RegA3Attr;
class RegA4Attr;
class RegA5Attr;
class RegA6Attr;
class RegA7Attr;
class RegS2Attr;
class RegS3Attr;
class RegS4Attr;
class RegS5Attr;
class RegS6Attr;
class RegS7Attr;
class RegS8Attr;
class RegS9Attr;
class RegS10Attr;
class RegS11Attr;
class RegT3Attr;
class RegT4Attr;
class RegT5Attr;
class RegT6Attr;
class RegF0Attr;
namespace detail {

struct CPUAttrStorage;

} // namespace detail
class CPUAttr : public ::mlir::Attribute::AttrBase<CPUAttr, ::mlir::Attribute, detail::CPUAttrStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::ContextResourceAttrInterface::Trait> {
public:
  using Base::Base;
  // TypedAttrInterface
  Type getType() const;
  static constexpr ::llvm::StringLiteral name = "rtgtest.cpu";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static CPUAttr get(::mlir::MLIRContext *context, size_t id);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"cpu"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  size_t getId() const;
};
class RegZeroAttr : public ::mlir::Attribute::AttrBase<RegZeroAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 0;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "zero";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.zero";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"zero"};
  }

};
class RegRaAttr : public ::mlir::Attribute::AttrBase<RegRaAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 1;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "ra";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.ra";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ra"};
  }

};
class RegSpAttr : public ::mlir::Attribute::AttrBase<RegSpAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 2;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "sp";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.sp";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sp"};
  }

};
class RegGpAttr : public ::mlir::Attribute::AttrBase<RegGpAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 3;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "gp";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.gp";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"gp"};
  }

};
class RegTpAttr : public ::mlir::Attribute::AttrBase<RegTpAttr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 4;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "tp";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.tp";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tp"};
  }

};
class RegT0Attr : public ::mlir::Attribute::AttrBase<RegT0Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 5;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t0";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t0";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t0"};
  }

};
class RegT1Attr : public ::mlir::Attribute::AttrBase<RegT1Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 6;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t1";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t1";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t1"};
  }

};
class RegT2Attr : public ::mlir::Attribute::AttrBase<RegT2Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 7;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t2";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t2";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t2"};
  }

};
class RegS0Attr : public ::mlir::Attribute::AttrBase<RegS0Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 8;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s0";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s0";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s0"};
  }

};
class RegS1Attr : public ::mlir::Attribute::AttrBase<RegS1Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 9;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s1";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s1";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s1"};
  }

};
class RegA0Attr : public ::mlir::Attribute::AttrBase<RegA0Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 10;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a0";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a0";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a0"};
  }

};
class RegA1Attr : public ::mlir::Attribute::AttrBase<RegA1Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 11;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a1";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a1";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a1"};
  }

};
class RegA2Attr : public ::mlir::Attribute::AttrBase<RegA2Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 12;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a2";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a2";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a2"};
  }

};
class RegA3Attr : public ::mlir::Attribute::AttrBase<RegA3Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 13;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a3";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a3";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a3"};
  }

};
class RegA4Attr : public ::mlir::Attribute::AttrBase<RegA4Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 14;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a4";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a4";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a4"};
  }

};
class RegA5Attr : public ::mlir::Attribute::AttrBase<RegA5Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 15;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a5";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a5";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a5"};
  }

};
class RegA6Attr : public ::mlir::Attribute::AttrBase<RegA6Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 16;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a6";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a6";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a6"};
  }

};
class RegA7Attr : public ::mlir::Attribute::AttrBase<RegA7Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 17;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "a7";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.a7";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"a7"};
  }

};
class RegS2Attr : public ::mlir::Attribute::AttrBase<RegS2Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 18;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s2";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s2";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s2"};
  }

};
class RegS3Attr : public ::mlir::Attribute::AttrBase<RegS3Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 19;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s3";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s3";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s3"};
  }

};
class RegS4Attr : public ::mlir::Attribute::AttrBase<RegS4Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 20;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s4";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s4";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s4"};
  }

};
class RegS5Attr : public ::mlir::Attribute::AttrBase<RegS5Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 21;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s5";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s5";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s5"};
  }

};
class RegS6Attr : public ::mlir::Attribute::AttrBase<RegS6Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 22;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s6";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s6";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s6"};
  }

};
class RegS7Attr : public ::mlir::Attribute::AttrBase<RegS7Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 23;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s7";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s7";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s7"};
  }

};
class RegS8Attr : public ::mlir::Attribute::AttrBase<RegS8Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 24;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s8";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s8";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s8"};
  }

};
class RegS9Attr : public ::mlir::Attribute::AttrBase<RegS9Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 25;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s9";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s9";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s9"};
  }

};
class RegS10Attr : public ::mlir::Attribute::AttrBase<RegS10Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 26;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s10";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s10";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s10"};
  }

};
class RegS11Attr : public ::mlir::Attribute::AttrBase<RegS11Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 27;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "s11";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.s11";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"s11"};
  }

};
class RegT3Attr : public ::mlir::Attribute::AttrBase<RegT3Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 28;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t3";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t3";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t3"};
  }

};
class RegT4Attr : public ::mlir::Attribute::AttrBase<RegT4Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 29;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t4";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t4";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t4"};
  }

};
class RegT5Attr : public ::mlir::Attribute::AttrBase<RegT5Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 30;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t5";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t5";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t5"};
  }

};
class RegT6Attr : public ::mlir::Attribute::AttrBase<RegT6Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 31;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "t6";
  }

  Type getType() const {
    return IntegerRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.t6";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t6"};
  }

};
class RegF0Attr : public ::mlir::Attribute::AttrBase<RegF0Attr, ::mlir::Attribute, ::mlir::AttributeStorage, ::mlir::TypedAttr::Trait, ::circt::rtg::RegisterAttrInterface::Trait> {
public:
  using Base::Base;
  unsigned getClassIndex() const {
    return 0;
  }

  llvm::StringLiteral getRegisterAssembly() const {
    return "f0";
  }

  Type getType() const {
    return FloatRegisterType::get(getContext());
  }
  static constexpr ::llvm::StringLiteral name = "rtgtest.f0";
  static constexpr ::llvm::StringLiteral dialectName = "rtgtest";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"f0"};
  }

};

} // namespace circt::rtgtest
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::CPUAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegZeroAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegRaAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegSpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegGpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegTpAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT0Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT1Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT2Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS0Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS1Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA0Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA1Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA2Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA3Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA4Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA5Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA6Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA7Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS2Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS3Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS4Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS5Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS6Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS7Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS8Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS9Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS10Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS11Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT3Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT4Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT5Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT6Attr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegF0Attr)

#endif // GET_ATTRDEF_CLASSES

