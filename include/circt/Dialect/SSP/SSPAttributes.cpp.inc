/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::ssp::DependenceAttr,
::circt::ssp::LinkedOperatorTypeAttr,
::circt::ssp::LinkedResourceTypesAttr,
::circt::ssp::StartTimeAttr,
::circt::ssp::LatencyAttr,
::circt::ssp::DistanceAttr,
::circt::ssp::InitiationIntervalAttr,
::circt::ssp::StartTimeInCycleAttr,
::circt::ssp::IncomingDelayAttr,
::circt::ssp::OutgoingDelayAttr,
::circt::ssp::LimitAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::ssp::DependenceAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::DependenceAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::LinkedOperatorTypeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::LinkedOperatorTypeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::LinkedResourceTypesAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::LinkedResourceTypesAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::StartTimeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::StartTimeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::LatencyAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::LatencyAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::DistanceAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::DistanceAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::InitiationIntervalAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::InitiationIntervalAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::StartTimeInCycleAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::StartTimeInCycleAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::IncomingDelayAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::IncomingDelayAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::OutgoingDelayAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::OutgoingDelayAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::ssp::LimitAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::ssp::LimitAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::ssp::DependenceAttr>([&](auto t) {
      printer << ::circt::ssp::DependenceAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::LinkedOperatorTypeAttr>([&](auto t) {
      printer << ::circt::ssp::LinkedOperatorTypeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::LinkedResourceTypesAttr>([&](auto t) {
      printer << ::circt::ssp::LinkedResourceTypesAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::StartTimeAttr>([&](auto t) {
      printer << ::circt::ssp::StartTimeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::LatencyAttr>([&](auto t) {
      printer << ::circt::ssp::LatencyAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::DistanceAttr>([&](auto t) {
      printer << ::circt::ssp::DistanceAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::InitiationIntervalAttr>([&](auto t) {
      printer << ::circt::ssp::InitiationIntervalAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::StartTimeInCycleAttr>([&](auto t) {
      printer << ::circt::ssp::StartTimeInCycleAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::IncomingDelayAttr>([&](auto t) {
      printer << ::circt::ssp::IncomingDelayAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::OutgoingDelayAttr>([&](auto t) {
      printer << ::circt::ssp::OutgoingDelayAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::ssp::LimitAttr>([&](auto t) {
      printer << ::circt::ssp::LimitAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::ssp {

namespace detail {

struct DependenceAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned, ::mlir::FlatSymbolRefAttr, ::mlir::ArrayAttr>;
  DependenceAttrStorage(unsigned operandIdx, ::mlir::FlatSymbolRefAttr sourceRef, ::mlir::ArrayAttr properties) : operandIdx(std::move(operandIdx)), sourceRef(std::move(sourceRef)), properties(std::move(properties)) {}

  KeyTy getAsKey() const {
    return KeyTy(operandIdx, sourceRef, properties);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (operandIdx == std::get<0>(tblgenKey)) && (sourceRef == std::get<1>(tblgenKey)) && (properties == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static DependenceAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto operandIdx = std::move(std::get<0>(tblgenKey));
    auto sourceRef = std::move(std::get<1>(tblgenKey));
    auto properties = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<DependenceAttrStorage>()) DependenceAttrStorage(std::move(operandIdx), std::move(sourceRef), std::move(properties));
  }

  unsigned operandIdx;
  ::mlir::FlatSymbolRefAttr sourceRef;
  ::mlir::ArrayAttr properties;
};

} // namespace detail
DependenceAttr DependenceAttr::get(::mlir::MLIRContext *context, unsigned operandIdx, ::mlir::FlatSymbolRefAttr sourceRef, ::mlir::ArrayAttr properties) {
  return Base::get(context, std::move(operandIdx), std::move(sourceRef), std::move(properties));
}

::mlir::Attribute DependenceAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_operandIdx;
  ::mlir::FailureOr<::mlir::FlatSymbolRefAttr> _result_sourceRef;
  ::mlir::FailureOr<::mlir::ArrayAttr> _result_properties;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'operandIdx'
  _result_operandIdx = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_operandIdx)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DependenceAttr parameter 'operandIdx' which is to be a `unsigned`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseOptionalComma()) {
  } else {

    // Parse variable 'sourceRef'
    _result_sourceRef = ::mlir::FieldParser<::mlir::FlatSymbolRefAttr>::parse(odsParser);
    if (::mlir::failed(_result_sourceRef)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DependenceAttr parameter 'sourceRef' which is to be a `::mlir::FlatSymbolRefAttr`");
      return {};
    }
  }
  // Parse literal ':'
  if (odsParser.parseOptionalColon()) {
  } else {

    // Parse variable 'properties'
    _result_properties = ::mlir::FieldParser<::mlir::ArrayAttr>::parse(odsParser);
    if (::mlir::failed(_result_properties)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DependenceAttr parameter 'properties' which is to be a `::mlir::ArrayAttr`");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_operandIdx));
  return DependenceAttr::get(odsParser.getContext(),
      unsigned((*_result_operandIdx)),
      ::mlir::FlatSymbolRefAttr((_result_sourceRef.value_or(::mlir::FlatSymbolRefAttr()))),
      ::mlir::ArrayAttr((_result_properties.value_or(::mlir::ArrayAttr()))));
}

void DependenceAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getOperandIdx());
  if (!(getSourceRef() == ::mlir::FlatSymbolRefAttr())) {
    odsPrinter << ",";
    if (!(getSourceRef() == ::mlir::FlatSymbolRefAttr())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getSourceRef());
    }
  } else {
  }
  if (!(getProperties() == ::mlir::ArrayAttr())) {
    odsPrinter << ' ' << ":";
    if (!(getProperties() == ::mlir::ArrayAttr())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getProperties());
    }
  } else {
  }
  odsPrinter << ">";
}

unsigned DependenceAttr::getOperandIdx() const {
  return getImpl()->operandIdx;
}

::mlir::FlatSymbolRefAttr DependenceAttr::getSourceRef() const {
  return getImpl()->sourceRef;
}

::mlir::ArrayAttr DependenceAttr::getProperties() const {
  return getImpl()->properties;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::DependenceAttr)
namespace circt::ssp {

namespace detail {

struct LinkedOperatorTypeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::SymbolRefAttr>;
  LinkedOperatorTypeAttrStorage(::mlir::SymbolRefAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LinkedOperatorTypeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LinkedOperatorTypeAttrStorage>()) LinkedOperatorTypeAttrStorage(std::move(value));
  }

  ::mlir::SymbolRefAttr value;
};

} // namespace detail
LinkedOperatorTypeAttr LinkedOperatorTypeAttr::get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LinkedOperatorTypeAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::SymbolRefAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::mlir::SymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinkedOperatorTypeProp parameter 'value' which is to be a `::mlir::SymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return LinkedOperatorTypeAttr::get(odsParser.getContext(),
      ::mlir::SymbolRefAttr((*_result_value)));
}

void LinkedOperatorTypeAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

::mlir::SymbolRefAttr LinkedOperatorTypeAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::LinkedOperatorTypeAttr)
namespace circt::ssp {

namespace detail {

struct LinkedResourceTypesAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::ArrayAttr>;
  LinkedResourceTypesAttrStorage(::mlir::ArrayAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LinkedResourceTypesAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LinkedResourceTypesAttrStorage>()) LinkedResourceTypesAttrStorage(std::move(value));
  }

  ::mlir::ArrayAttr value;
};

} // namespace detail
LinkedResourceTypesAttr LinkedResourceTypesAttr::get(::mlir::MLIRContext *context, ::mlir::ArrayAttr value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LinkedResourceTypesAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::ArrayAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::mlir::ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LinkedResourceTypesProp parameter 'value' which is to be a `::mlir::ArrayAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return LinkedResourceTypesAttr::get(odsParser.getContext(),
      ::mlir::ArrayAttr((*_result_value)));
}

void LinkedResourceTypesAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

::mlir::ArrayAttr LinkedResourceTypesAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::LinkedResourceTypesAttr)
namespace circt::ssp {

namespace detail {

struct StartTimeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned>;
  StartTimeAttrStorage(unsigned value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StartTimeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<StartTimeAttrStorage>()) StartTimeAttrStorage(std::move(value));
  }

  unsigned value;
};

} // namespace detail
StartTimeAttr StartTimeAttr::get(::mlir::MLIRContext *context, unsigned value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute StartTimeAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse StartTimeProp parameter 'value' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return StartTimeAttr::get(odsParser.getContext(),
      unsigned((*_result_value)));
}

void StartTimeAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

unsigned StartTimeAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::StartTimeAttr)
namespace circt::ssp {

namespace detail {

struct LatencyAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned>;
  LatencyAttrStorage(unsigned value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LatencyAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LatencyAttrStorage>()) LatencyAttrStorage(std::move(value));
  }

  unsigned value;
};

} // namespace detail
LatencyAttr LatencyAttr::get(::mlir::MLIRContext *context, unsigned value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LatencyAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LatencyProp parameter 'value' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return LatencyAttr::get(odsParser.getContext(),
      unsigned((*_result_value)));
}

void LatencyAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

unsigned LatencyAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::LatencyAttr)
namespace circt::ssp {

namespace detail {

struct DistanceAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned>;
  DistanceAttrStorage(unsigned value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static DistanceAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<DistanceAttrStorage>()) DistanceAttrStorage(std::move(value));
  }

  unsigned value;
};

} // namespace detail
DistanceAttr DistanceAttr::get(::mlir::MLIRContext *context, unsigned value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute DistanceAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DistanceProp parameter 'value' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return DistanceAttr::get(odsParser.getContext(),
      unsigned((*_result_value)));
}

void DistanceAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

unsigned DistanceAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::DistanceAttr)
namespace circt::ssp {

namespace detail {

struct InitiationIntervalAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned>;
  InitiationIntervalAttrStorage(unsigned value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InitiationIntervalAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<InitiationIntervalAttrStorage>()) InitiationIntervalAttrStorage(std::move(value));
  }

  unsigned value;
};

} // namespace detail
InitiationIntervalAttr InitiationIntervalAttr::get(::mlir::MLIRContext *context, unsigned value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute InitiationIntervalAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse InitiationIntervalProp parameter 'value' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return InitiationIntervalAttr::get(odsParser.getContext(),
      unsigned((*_result_value)));
}

void InitiationIntervalAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

unsigned InitiationIntervalAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::InitiationIntervalAttr)
namespace circt::ssp {

namespace detail {

struct StartTimeInCycleAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FloatAttr>;
  StartTimeInCycleAttrStorage(::mlir::FloatAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StartTimeInCycleAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<StartTimeInCycleAttrStorage>()) StartTimeInCycleAttrStorage(std::move(value));
  }

  ::mlir::FloatAttr value;
};

} // namespace detail
StartTimeInCycleAttr StartTimeInCycleAttr::get(::mlir::MLIRContext *context, ::mlir::FloatAttr value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute StartTimeInCycleAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FloatAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::mlir::FloatAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse StartTimeInCycleProp parameter 'value' which is to be a `::mlir::FloatAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return StartTimeInCycleAttr::get(odsParser.getContext(),
      ::mlir::FloatAttr((*_result_value)));
}

void StartTimeInCycleAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

::mlir::FloatAttr StartTimeInCycleAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::StartTimeInCycleAttr)
namespace circt::ssp {

namespace detail {

struct IncomingDelayAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FloatAttr>;
  IncomingDelayAttrStorage(::mlir::FloatAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static IncomingDelayAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<IncomingDelayAttrStorage>()) IncomingDelayAttrStorage(std::move(value));
  }

  ::mlir::FloatAttr value;
};

} // namespace detail
IncomingDelayAttr IncomingDelayAttr::get(::mlir::MLIRContext *context, ::mlir::FloatAttr value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute IncomingDelayAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FloatAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::mlir::FloatAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse IncomingDelayProp parameter 'value' which is to be a `::mlir::FloatAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return IncomingDelayAttr::get(odsParser.getContext(),
      ::mlir::FloatAttr((*_result_value)));
}

void IncomingDelayAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

::mlir::FloatAttr IncomingDelayAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::IncomingDelayAttr)
namespace circt::ssp {

namespace detail {

struct OutgoingDelayAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FloatAttr>;
  OutgoingDelayAttrStorage(::mlir::FloatAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static OutgoingDelayAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<OutgoingDelayAttrStorage>()) OutgoingDelayAttrStorage(std::move(value));
  }

  ::mlir::FloatAttr value;
};

} // namespace detail
OutgoingDelayAttr OutgoingDelayAttr::get(::mlir::MLIRContext *context, ::mlir::FloatAttr value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute OutgoingDelayAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FloatAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<::mlir::FloatAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OutgoingDelayProp parameter 'value' which is to be a `::mlir::FloatAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return OutgoingDelayAttr::get(odsParser.getContext(),
      ::mlir::FloatAttr((*_result_value)));
}

void OutgoingDelayAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

::mlir::FloatAttr OutgoingDelayAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::OutgoingDelayAttr)
namespace circt::ssp {

namespace detail {

struct LimitAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<unsigned>;
  LimitAttrStorage(unsigned value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LimitAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LimitAttrStorage>()) LimitAttrStorage(std::move(value));
  }

  unsigned value;
};

} // namespace detail
LimitAttr LimitAttr::get(::mlir::MLIRContext *context, unsigned value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LimitAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LimitProp parameter 'value' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return LimitAttr::get(odsParser.getContext(),
      unsigned((*_result_value)));
}

void LimitAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

unsigned LimitAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::LimitAttr)
namespace circt::ssp {


/// Parse an attribute registered to this dialect.
::mlir::Attribute SSPDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void SSPDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::ssp

#endif // GET_ATTRDEF_CLASSES

