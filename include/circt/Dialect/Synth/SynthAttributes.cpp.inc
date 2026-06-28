/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::synth::NLDMTableAttr,
::circt::synth::NLDMTimingArcAttr,
::circt::synth::PolarityAttr,
::circt::synth::LinearTimingArcAttr,
::circt::synth::MappingCostAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::synth::NLDMTableAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::synth::NLDMTableAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::synth::NLDMTimingArcAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::synth::NLDMTimingArcAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::synth::PolarityAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::synth::PolarityAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::synth::LinearTimingArcAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::synth::LinearTimingArcAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::synth::MappingCostAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::synth::MappingCostAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::synth::NLDMTableAttr>([&](auto t) {
      printer << ::circt::synth::NLDMTableAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::synth::NLDMTimingArcAttr>([&](auto t) {
      printer << ::circt::synth::NLDMTimingArcAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::synth::PolarityAttr>([&](auto t) {
      printer << ::circt::synth::PolarityAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::synth::LinearTimingArcAttr>([&](auto t) {
      printer << ::circt::synth::LinearTimingArcAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::synth::MappingCostAttr>([&](auto t) {
      printer << ::circt::synth::MappingCostAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::synth {

namespace detail {

struct NLDMTableAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::DenseF64ArrayAttr, ::mlir::DenseF64ArrayAttr, ::mlir::DenseF64ArrayAttr>;
  NLDMTableAttrStorage(::mlir::DenseF64ArrayAttr index1, ::mlir::DenseF64ArrayAttr index2, ::mlir::DenseF64ArrayAttr values) : index1(std::move(index1)), index2(std::move(index2)), values(std::move(values)) {}

  KeyTy getAsKey() const {
    return KeyTy(index1, index2, values);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (index1 == std::get<0>(tblgenKey)) && (index2 == std::get<1>(tblgenKey)) && (values == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static NLDMTableAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto index1 = std::move(std::get<0>(tblgenKey));
    auto index2 = std::move(std::get<1>(tblgenKey));
    auto values = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<NLDMTableAttrStorage>()) NLDMTableAttrStorage(std::move(index1), std::move(index2), std::move(values));
  }

  ::mlir::DenseF64ArrayAttr index1;
  ::mlir::DenseF64ArrayAttr index2;
  ::mlir::DenseF64ArrayAttr values;
};

} // namespace detail
NLDMTableAttr NLDMTableAttr::get(::mlir::MLIRContext *context, ::mlir::DenseF64ArrayAttr index1, ::mlir::DenseF64ArrayAttr index2, ::mlir::DenseF64ArrayAttr values) {
  return Base::get(context, std::move(index1), std::move(index2), std::move(values));
}

::mlir::Attribute NLDMTableAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::DenseF64ArrayAttr> _result_index1;
  ::mlir::FailureOr<::mlir::DenseF64ArrayAttr> _result_index2;
  ::mlir::FailureOr<::mlir::DenseF64ArrayAttr> _result_values;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'index1'
  _result_index1 = ::mlir::FieldParser<::mlir::DenseF64ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_index1)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTableAttr parameter 'index1' which is to be a `::mlir::DenseF64ArrayAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'index2'
  _result_index2 = ::mlir::FieldParser<::mlir::DenseF64ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_index2)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTableAttr parameter 'index2' which is to be a `::mlir::DenseF64ArrayAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'values'
  _result_values = ::mlir::FieldParser<::mlir::DenseF64ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_values)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTableAttr parameter 'values' which is to be a `::mlir::DenseF64ArrayAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_index1));
  assert(::mlir::succeeded(_result_index2));
  assert(::mlir::succeeded(_result_values));
  return NLDMTableAttr::get(odsParser.getContext(),
      ::mlir::DenseF64ArrayAttr((*_result_index1)),
      ::mlir::DenseF64ArrayAttr((*_result_index2)),
      ::mlir::DenseF64ArrayAttr((*_result_values)));
}

void NLDMTableAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getIndex1());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIndex2());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getValues());
  odsPrinter << ">";
}

::mlir::DenseF64ArrayAttr NLDMTableAttr::getIndex1() const {
  return getImpl()->index1;
}

::mlir::DenseF64ArrayAttr NLDMTableAttr::getIndex2() const {
  return getImpl()->index2;
}

::mlir::DenseF64ArrayAttr NLDMTableAttr::getValues() const {
  return getImpl()->values;
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::NLDMTableAttr)
namespace circt::synth {

namespace detail {

struct NLDMTimingArcAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::StringAttr, ::mlir::StringAttr, NLDMTableAttr, NLDMTableAttr, NLDMTableAttr, NLDMTableAttr>;
  NLDMTimingArcAttrStorage(::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, ::mlir::StringAttr timingSense, NLDMTableAttr cellRise, NLDMTableAttr cellFall, NLDMTableAttr riseTransition, NLDMTableAttr fallTransition) : pin(std::move(pin)), relatedPin(std::move(relatedPin)), timingSense(std::move(timingSense)), cellRise(std::move(cellRise)), cellFall(std::move(cellFall)), riseTransition(std::move(riseTransition)), fallTransition(std::move(fallTransition)) {}

  KeyTy getAsKey() const {
    return KeyTy(pin, relatedPin, timingSense, cellRise, cellFall, riseTransition, fallTransition);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (pin == std::get<0>(tblgenKey)) && (relatedPin == std::get<1>(tblgenKey)) && (timingSense == std::get<2>(tblgenKey)) && (cellRise == std::get<3>(tblgenKey)) && (cellFall == std::get<4>(tblgenKey)) && (riseTransition == std::get<5>(tblgenKey)) && (fallTransition == std::get<6>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey), std::get<4>(tblgenKey), std::get<5>(tblgenKey), std::get<6>(tblgenKey));
  }

  static NLDMTimingArcAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto pin = std::move(std::get<0>(tblgenKey));
    auto relatedPin = std::move(std::get<1>(tblgenKey));
    auto timingSense = std::move(std::get<2>(tblgenKey));
    auto cellRise = std::move(std::get<3>(tblgenKey));
    auto cellFall = std::move(std::get<4>(tblgenKey));
    auto riseTransition = std::move(std::get<5>(tblgenKey));
    auto fallTransition = std::move(std::get<6>(tblgenKey));
    return new (allocator.allocate<NLDMTimingArcAttrStorage>()) NLDMTimingArcAttrStorage(std::move(pin), std::move(relatedPin), std::move(timingSense), std::move(cellRise), std::move(cellFall), std::move(riseTransition), std::move(fallTransition));
  }

  ::mlir::StringAttr pin;
  ::mlir::StringAttr relatedPin;
  ::mlir::StringAttr timingSense;
  NLDMTableAttr cellRise;
  NLDMTableAttr cellFall;
  NLDMTableAttr riseTransition;
  NLDMTableAttr fallTransition;
};

} // namespace detail
NLDMTimingArcAttr NLDMTimingArcAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, ::mlir::StringAttr timingSense, NLDMTableAttr cellRise, NLDMTableAttr cellFall, NLDMTableAttr riseTransition, NLDMTableAttr fallTransition) {
  return Base::get(context, std::move(pin), std::move(relatedPin), std::move(timingSense), std::move(cellRise), std::move(cellFall), std::move(riseTransition), std::move(fallTransition));
}

::mlir::Attribute NLDMTimingArcAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::StringAttr> _result_pin;
  ::mlir::FailureOr<::mlir::StringAttr> _result_relatedPin;
  ::mlir::FailureOr<::mlir::StringAttr> _result_timingSense;
  ::mlir::FailureOr<NLDMTableAttr> _result_cellRise;
  ::mlir::FailureOr<NLDMTableAttr> _result_cellFall;
  ::mlir::FailureOr<NLDMTableAttr> _result_riseTransition;
  ::mlir::FailureOr<NLDMTableAttr> _result_fallTransition;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'pin'
  _result_pin = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_pin)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'pin' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'relatedPin'
  _result_relatedPin = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_relatedPin)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'relatedPin' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'timingSense'
  _result_timingSense = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_timingSense)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'timingSense' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'cellRise'
  _result_cellRise = ::mlir::FieldParser<NLDMTableAttr>::parse(odsParser);
  if (::mlir::failed(_result_cellRise)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'cellRise' which is to be a `NLDMTableAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'cellFall'
  _result_cellFall = ::mlir::FieldParser<NLDMTableAttr>::parse(odsParser);
  if (::mlir::failed(_result_cellFall)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'cellFall' which is to be a `NLDMTableAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'riseTransition'
  _result_riseTransition = ::mlir::FieldParser<NLDMTableAttr>::parse(odsParser);
  if (::mlir::failed(_result_riseTransition)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'riseTransition' which is to be a `NLDMTableAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'fallTransition'
  _result_fallTransition = ::mlir::FieldParser<NLDMTableAttr>::parse(odsParser);
  if (::mlir::failed(_result_fallTransition)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NLDMTimingArcAttr parameter 'fallTransition' which is to be a `NLDMTableAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_pin));
  assert(::mlir::succeeded(_result_relatedPin));
  assert(::mlir::succeeded(_result_timingSense));
  assert(::mlir::succeeded(_result_cellRise));
  assert(::mlir::succeeded(_result_cellFall));
  assert(::mlir::succeeded(_result_riseTransition));
  assert(::mlir::succeeded(_result_fallTransition));
  return NLDMTimingArcAttr::get(odsParser.getContext(),
      ::mlir::StringAttr((*_result_pin)),
      ::mlir::StringAttr((*_result_relatedPin)),
      ::mlir::StringAttr((*_result_timingSense)),
      NLDMTableAttr((*_result_cellRise)),
      NLDMTableAttr((*_result_cellFall)),
      NLDMTableAttr((*_result_riseTransition)),
      NLDMTableAttr((*_result_fallTransition)));
}

void NLDMTimingArcAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getPin());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getRelatedPin());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getTimingSense());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getCellRise());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getCellFall());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getRiseTransition());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getFallTransition());
  odsPrinter << ">";
}

::mlir::StringAttr NLDMTimingArcAttr::getPin() const {
  return getImpl()->pin;
}

::mlir::StringAttr NLDMTimingArcAttr::getRelatedPin() const {
  return getImpl()->relatedPin;
}

::mlir::StringAttr NLDMTimingArcAttr::getTimingSense() const {
  return getImpl()->timingSense;
}

NLDMTableAttr NLDMTimingArcAttr::getCellRise() const {
  return getImpl()->cellRise;
}

NLDMTableAttr NLDMTimingArcAttr::getCellFall() const {
  return getImpl()->cellFall;
}

NLDMTableAttr NLDMTimingArcAttr::getRiseTransition() const {
  return getImpl()->riseTransition;
}

NLDMTableAttr NLDMTimingArcAttr::getFallTransition() const {
  return getImpl()->fallTransition;
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::NLDMTimingArcAttr)
namespace circt::synth {

namespace detail {

struct PolarityAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PolarityKind>;
  PolarityAttrStorage(PolarityKind value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static PolarityAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<PolarityAttrStorage>()) PolarityAttrStorage(std::move(value));
  }

  PolarityKind value;
};

} // namespace detail
PolarityAttr PolarityAttr::get(::mlir::MLIRContext *context, PolarityKind value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute PolarityAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<PolarityKind> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<PolarityKind>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PolarityAttr parameter 'value' which is to be a `PolarityKind`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return PolarityAttr::get(odsParser.getContext(),
      PolarityKind((*_result_value)));
}

void PolarityAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

PolarityKind PolarityAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::PolarityAttr)
namespace circt::synth {

namespace detail {

struct LinearTimingArcAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::StringAttr, int64_t, int64_t, PolarityAttr>;
  LinearTimingArcAttrStorage(::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, int64_t intrinsic, int64_t sensitivity, PolarityAttr polarity) : pin(std::move(pin)), relatedPin(std::move(relatedPin)), intrinsic(std::move(intrinsic)), sensitivity(std::move(sensitivity)), polarity(std::move(polarity)) {}

  KeyTy getAsKey() const {
    return KeyTy(pin, relatedPin, intrinsic, sensitivity, polarity);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (pin == std::get<0>(tblgenKey)) && (relatedPin == std::get<1>(tblgenKey)) && (intrinsic == std::get<2>(tblgenKey)) && (sensitivity == std::get<3>(tblgenKey)) && (polarity == std::get<4>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey), std::get<4>(tblgenKey));
  }

  static LinearTimingArcAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto pin = std::move(std::get<0>(tblgenKey));
    auto relatedPin = std::move(std::get<1>(tblgenKey));
    auto intrinsic = std::move(std::get<2>(tblgenKey));
    auto sensitivity = std::move(std::get<3>(tblgenKey));
    auto polarity = std::move(std::get<4>(tblgenKey));
    return new (allocator.allocate<LinearTimingArcAttrStorage>()) LinearTimingArcAttrStorage(std::move(pin), std::move(relatedPin), std::move(intrinsic), std::move(sensitivity), std::move(polarity));
  }

  ::mlir::StringAttr pin;
  ::mlir::StringAttr relatedPin;
  int64_t intrinsic;
  int64_t sensitivity;
  PolarityAttr polarity;
};

} // namespace detail
LinearTimingArcAttr LinearTimingArcAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr pin, ::mlir::StringAttr relatedPin, int64_t intrinsic, int64_t sensitivity, PolarityAttr polarity) {
  return Base::get(context, std::move(pin), std::move(relatedPin), std::move(intrinsic), std::move(sensitivity), std::move(polarity));
}

::mlir::Attribute LinearTimingArcAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::StringAttr> _result_pin;
  ::mlir::FailureOr<::mlir::StringAttr> _result_relatedPin;
  ::mlir::FailureOr<int64_t> _result_intrinsic;
  ::mlir::FailureOr<int64_t> _result_sensitivity;
  ::mlir::FailureOr<PolarityAttr> _result_polarity;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'pin'
  _result_pin = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_pin)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinearTimingArcAttr parameter 'pin' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'relatedPin'
  _result_relatedPin = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_relatedPin)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinearTimingArcAttr parameter 'relatedPin' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'intrinsic'
  _result_intrinsic = ::mlir::FieldParser<int64_t>::parse(odsParser);
  if (::mlir::failed(_result_intrinsic)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinearTimingArcAttr parameter 'intrinsic' which is to be a `int64_t`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'sensitivity'
  _result_sensitivity = ::mlir::FieldParser<int64_t>::parse(odsParser);
  if (::mlir::failed(_result_sensitivity)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinearTimingArcAttr parameter 'sensitivity' which is to be a `int64_t`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'polarity'
  _result_polarity = ::mlir::FieldParser<PolarityAttr>::parse(odsParser);
  if (::mlir::failed(_result_polarity)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinearTimingArcAttr parameter 'polarity' which is to be a `PolarityAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_pin));
  assert(::mlir::succeeded(_result_relatedPin));
  assert(::mlir::succeeded(_result_intrinsic));
  assert(::mlir::succeeded(_result_sensitivity));
  assert(::mlir::succeeded(_result_polarity));
  return LinearTimingArcAttr::get(odsParser.getContext(),
      ::mlir::StringAttr((*_result_pin)),
      ::mlir::StringAttr((*_result_relatedPin)),
      int64_t((*_result_intrinsic)),
      int64_t((*_result_sensitivity)),
      PolarityAttr((*_result_polarity)));
}

void LinearTimingArcAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getPin());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getRelatedPin());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIntrinsic());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getSensitivity());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getPolarity());
  odsPrinter << ">";
}

::mlir::StringAttr LinearTimingArcAttr::getPin() const {
  return getImpl()->pin;
}

::mlir::StringAttr LinearTimingArcAttr::getRelatedPin() const {
  return getImpl()->relatedPin;
}

int64_t LinearTimingArcAttr::getIntrinsic() const {
  return getImpl()->intrinsic;
}

int64_t LinearTimingArcAttr::getSensitivity() const {
  return getImpl()->sensitivity;
}

PolarityAttr LinearTimingArcAttr::getPolarity() const {
  return getImpl()->polarity;
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::LinearTimingArcAttr)
namespace circt::synth {

namespace detail {

struct MappingCostAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FloatAttr, ::mlir::ArrayAttr, ::mlir::DictionaryAttr>;
  MappingCostAttrStorage(::mlir::FloatAttr area, ::mlir::ArrayAttr arcs, ::mlir::DictionaryAttr inputCaps) : area(std::move(area)), arcs(std::move(arcs)), inputCaps(std::move(inputCaps)) {}

  KeyTy getAsKey() const {
    return KeyTy(area, arcs, inputCaps);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (area == std::get<0>(tblgenKey)) && (arcs == std::get<1>(tblgenKey)) && (inputCaps == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static MappingCostAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto area = std::move(std::get<0>(tblgenKey));
    auto arcs = std::move(std::get<1>(tblgenKey));
    auto inputCaps = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<MappingCostAttrStorage>()) MappingCostAttrStorage(std::move(area), std::move(arcs), std::move(inputCaps));
  }

  ::mlir::FloatAttr area;
  ::mlir::ArrayAttr arcs;
  ::mlir::DictionaryAttr inputCaps;
};

} // namespace detail
MappingCostAttr MappingCostAttr::get(::mlir::MLIRContext *context, ::mlir::FloatAttr area, ::mlir::ArrayAttr arcs, ::mlir::DictionaryAttr inputCaps) {
  return Base::get(context, std::move(area), std::move(arcs), std::move(inputCaps));
}

::mlir::Attribute MappingCostAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FloatAttr> _result_area;
  ::mlir::FailureOr<::mlir::ArrayAttr> _result_arcs;
  ::mlir::FailureOr<::mlir::DictionaryAttr> _result_inputCaps;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  // Parse literal 'area'
  if (odsParser.parseKeyword("area")) return {};
  // Parse literal '='
  if (odsParser.parseEqual()) return {};

  // Parse variable 'area'
  _result_area = ::mlir::FieldParser<::mlir::FloatAttr>::parse(odsParser);
  if (::mlir::failed(_result_area)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MappingCostAttr parameter 'area' which is to be a `::mlir::FloatAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};
  // Parse literal 'arcs'
  if (odsParser.parseKeyword("arcs")) return {};
  // Parse literal '='
  if (odsParser.parseEqual()) return {};

  // Parse variable 'arcs'
  _result_arcs = ::mlir::FieldParser<::mlir::ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_arcs)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MappingCostAttr parameter 'arcs' which is to be a `::mlir::ArrayAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};
  // Parse literal 'input_caps'
  if (odsParser.parseKeyword("input_caps")) return {};
  // Parse literal '='
  if (odsParser.parseEqual()) return {};

  // Parse variable 'inputCaps'
  _result_inputCaps = ::mlir::FieldParser<::mlir::DictionaryAttr>::parse(odsParser);
  if (::mlir::failed(_result_inputCaps)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MappingCostAttr parameter 'inputCaps' which is to be a `::mlir::DictionaryAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_area));
  assert(::mlir::succeeded(_result_arcs));
  assert(::mlir::succeeded(_result_inputCaps));
  return MappingCostAttr::get(odsParser.getContext(),
      ::mlir::FloatAttr((*_result_area)),
      ::mlir::ArrayAttr((*_result_arcs)),
      ::mlir::DictionaryAttr((*_result_inputCaps)));
}

void MappingCostAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter << "area";
  odsPrinter << ' ' << "=";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getArea());
  odsPrinter << ",";
  odsPrinter << ' ' << "arcs";
  odsPrinter << ' ' << "=";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getArcs());
  odsPrinter << ",";
  odsPrinter << ' ' << "input_caps";
  odsPrinter << ' ' << "=";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getInputCaps());
  odsPrinter << ">";
}

::mlir::FloatAttr MappingCostAttr::getArea() const {
  return getImpl()->area;
}

::mlir::ArrayAttr MappingCostAttr::getArcs() const {
  return getImpl()->arcs;
}

::mlir::DictionaryAttr MappingCostAttr::getInputCaps() const {
  return getImpl()->inputCaps;
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::MappingCostAttr)
namespace circt::synth {


/// Parse an attribute registered to this dialect.
::mlir::Attribute SynthDialect::parseAttribute(::mlir::DialectAsmParser &parser,
                                      ::mlir::Type type) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef attrTag;
  {
    ::mlir::Attribute attr;
    auto parseResult = generatedAttributeParser(parser, &attrTag, type, attr);
    if (parseResult.has_value())
      return attr;
  }
  
  parser.emitError(typeLoc) << "unknown attribute `"
      << attrTag << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print an attribute registered to this dialect.
void SynthDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::synth

#endif // GET_ATTRDEF_CLASSES

