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
namespace circt::synth {

/// Resolved 2D NLDM lookup table
class NLDMTableAttr;
/// NLDM timing arc with delay and transition lookup tables
class NLDMTimingArcAttr;
/// Timing arc polarity
class PolarityAttr;
/// A single simplified linear timing arc
class LinearTimingArcAttr;
/// Simplified timing and area cost for tech mapping
class MappingCostAttr;
namespace detail {

struct NLDMTableAttrStorage;

} // namespace detail
class NLDMTableAttr : public ::mlir::Attribute::AttrBase<NLDMTableAttr, ::mlir::Attribute, detail::NLDMTableAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "synth.nldm_table";
  static constexpr ::llvm::StringLiteral dialectName = "synth";
  static NLDMTableAttr get(::mlir::MLIRContext *context, ::mlir::DenseF64ArrayAttr index1, ::mlir::DenseF64ArrayAttr index2, ::mlir::DenseF64ArrayAttr values);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"nldm_table"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::DenseF64ArrayAttr getIndex1() const;
  ::mlir::DenseF64ArrayAttr getIndex2() const;
  ::mlir::DenseF64ArrayAttr getValues() const;
};
namespace detail {

struct NLDMTimingArcAttrStorage;

} // namespace detail
class NLDMTimingArcAttr : public ::mlir::Attribute::AttrBase<NLDMTimingArcAttr, ::mlir::Attribute, detail::NLDMTimingArcAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "synth.nldm_timing_arc";
  static constexpr ::llvm::StringLiteral dialectName = "synth";
  static NLDMTimingArcAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, ::mlir::StringAttr timingSense, NLDMTableAttr cellRise, NLDMTableAttr cellFall, NLDMTableAttr riseTransition, NLDMTableAttr fallTransition);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"nldm_timing_arc"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getPin() const;
  ::mlir::StringAttr getRelatedPin() const;
  ::mlir::StringAttr getTimingSense() const;
  NLDMTableAttr getCellRise() const;
  NLDMTableAttr getCellFall() const;
  NLDMTableAttr getRiseTransition() const;
  NLDMTableAttr getFallTransition() const;
};
namespace detail {

struct PolarityAttrStorage;

} // namespace detail
class PolarityAttr : public ::mlir::Attribute::AttrBase<PolarityAttr, ::mlir::Attribute, detail::PolarityAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "synth.polarity";
  static constexpr ::llvm::StringLiteral dialectName = "synth";
  static PolarityAttr get(::mlir::MLIRContext *context, PolarityKind value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"polarity"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PolarityKind getValue() const;
};
namespace detail {

struct LinearTimingArcAttrStorage;

} // namespace detail
class LinearTimingArcAttr : public ::mlir::Attribute::AttrBase<LinearTimingArcAttr, ::mlir::Attribute, detail::LinearTimingArcAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "synth.linear_timing_arc";
  static constexpr ::llvm::StringLiteral dialectName = "synth";
  static LinearTimingArcAttr get(::mlir::MLIRContext *context, ::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, int64_t intrinsic, int64_t sensitivity, PolarityAttr polarity);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"linear_timing_arc"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::StringAttr getPin() const;
  ::mlir::StringAttr getRelatedPin() const;
  int64_t getIntrinsic() const;
  int64_t getSensitivity() const;
  PolarityAttr getPolarity() const;
};
namespace detail {

struct MappingCostAttrStorage;

} // namespace detail
class MappingCostAttr : public ::mlir::Attribute::AttrBase<MappingCostAttr, ::mlir::Attribute, detail::MappingCostAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "synth.mapping_cost";
  static constexpr ::llvm::StringLiteral dialectName = "synth";
  static MappingCostAttr get(::mlir::MLIRContext *context, ::mlir::FloatAttr area, ::mlir::ArrayAttr arcs, ::mlir::DictionaryAttr inputCaps);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"mapping_cost"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FloatAttr getArea() const;
  ::mlir::ArrayAttr getArcs() const;
  ::mlir::DictionaryAttr getInputCaps() const;
};

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::NLDMTableAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::NLDMTimingArcAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::PolarityAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::LinearTimingArcAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::MappingCostAttr)

#endif // GET_ATTRDEF_CLASSES

