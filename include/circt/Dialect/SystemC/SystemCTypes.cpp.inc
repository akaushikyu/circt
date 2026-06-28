/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::systemc::LogicType,
::circt::systemc::InputType,
::circt::systemc::InOutType,
::circt::systemc::OutputType,
::circt::systemc::SignalType,
::circt::systemc::ModuleType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::systemc::LogicType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::LogicType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::systemc::InputType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::InputType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::systemc::InOutType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::InOutType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::systemc::OutputType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::OutputType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::systemc::SignalType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::SignalType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::systemc::ModuleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::systemc::ModuleType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::systemc::LogicType>([&](auto t) {
      printer << ::circt::systemc::LogicType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::systemc::InputType>([&](auto t) {
      printer << ::circt::systemc::InputType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::systemc::InOutType>([&](auto t) {
      printer << ::circt::systemc::InOutType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::systemc::OutputType>([&](auto t) {
      printer << ::circt::systemc::OutputType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::systemc::SignalType>([&](auto t) {
      printer << ::circt::systemc::SignalType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::systemc::ModuleType>([&](auto t) {
      printer << ::circt::systemc::ModuleType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::systemc {

::mlir::Type LogicType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return LogicType::get(odsParser.getContext());
}

void LogicType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::LogicType)
namespace circt::systemc {

namespace detail {

struct InputTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  InputTypeStorage(::mlir::Type baseType) : baseType(std::move(baseType)) {}

  KeyTy getAsKey() const {
    return KeyTy(baseType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (baseType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InputTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto baseType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<InputTypeStorage>()) InputTypeStorage(std::move(baseType));
  }

  ::mlir::Type baseType;
};

} // namespace detail
InputType InputType::get(::mlir::MLIRContext *context, ::mlir::Type baseType) {
  return Base::get(context, std::move(baseType));
}

InputType InputType::get(::mlir::Type baseType) {
  return Base::get(baseType.getContext(), baseType);
}

::mlir::Type InputType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_baseType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'baseType'
  _result_baseType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_baseType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse InputType parameter 'baseType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_baseType));
  return InputType::get(odsParser.getContext(),
      ::mlir::Type((*_result_baseType)));
}

void InputType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getBaseType());
  odsPrinter << ">";
}

::mlir::Type InputType::getBaseType() const {
  return getImpl()->baseType;
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::InputType)
namespace circt::systemc {

namespace detail {

struct InOutTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  InOutTypeStorage(::mlir::Type baseType) : baseType(std::move(baseType)) {}

  KeyTy getAsKey() const {
    return KeyTy(baseType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (baseType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InOutTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto baseType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<InOutTypeStorage>()) InOutTypeStorage(std::move(baseType));
  }

  ::mlir::Type baseType;
};

} // namespace detail
InOutType InOutType::get(::mlir::MLIRContext *context, ::mlir::Type baseType) {
  return Base::get(context, std::move(baseType));
}

InOutType InOutType::get(::mlir::Type baseType) {
  return Base::get(baseType.getContext(), baseType);
}

::mlir::Type InOutType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_baseType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'baseType'
  _result_baseType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_baseType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse InOutType parameter 'baseType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_baseType));
  return InOutType::get(odsParser.getContext(),
      ::mlir::Type((*_result_baseType)));
}

void InOutType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getBaseType());
  odsPrinter << ">";
}

::mlir::Type InOutType::getBaseType() const {
  return getImpl()->baseType;
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::InOutType)
namespace circt::systemc {

namespace detail {

struct OutputTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  OutputTypeStorage(::mlir::Type baseType) : baseType(std::move(baseType)) {}

  KeyTy getAsKey() const {
    return KeyTy(baseType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (baseType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static OutputTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto baseType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<OutputTypeStorage>()) OutputTypeStorage(std::move(baseType));
  }

  ::mlir::Type baseType;
};

} // namespace detail
OutputType OutputType::get(::mlir::MLIRContext *context, ::mlir::Type baseType) {
  return Base::get(context, std::move(baseType));
}

OutputType OutputType::get(::mlir::Type baseType) {
  return Base::get(baseType.getContext(), baseType);
}

::mlir::Type OutputType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_baseType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'baseType'
  _result_baseType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_baseType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OutputType parameter 'baseType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_baseType));
  return OutputType::get(odsParser.getContext(),
      ::mlir::Type((*_result_baseType)));
}

void OutputType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getBaseType());
  odsPrinter << ">";
}

::mlir::Type OutputType::getBaseType() const {
  return getImpl()->baseType;
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::OutputType)
namespace circt::systemc {

namespace detail {

struct SignalTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  SignalTypeStorage(::mlir::Type baseType) : baseType(std::move(baseType)) {}

  KeyTy getAsKey() const {
    return KeyTy(baseType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (baseType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static SignalTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto baseType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<SignalTypeStorage>()) SignalTypeStorage(std::move(baseType));
  }

  ::mlir::Type baseType;
};

} // namespace detail
SignalType SignalType::get(::mlir::MLIRContext *context, ::mlir::Type baseType) {
  return Base::get(context, std::move(baseType));
}

SignalType SignalType::get(::mlir::Type baseType) {
  return Base::get(baseType.getContext(), baseType);
}

::mlir::Type SignalType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_baseType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'baseType'
  _result_baseType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_baseType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse SignalType parameter 'baseType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_baseType));
  return SignalType::get(odsParser.getContext(),
      ::mlir::Type((*_result_baseType)));
}

void SignalType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getBaseType());
  odsPrinter << ">";
}

::mlir::Type SignalType::getBaseType() const {
  return getImpl()->baseType;
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SignalType)
namespace circt::systemc {

namespace detail {

struct ModuleTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::StringAttr, ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo>>;
  ModuleTypeStorage(mlir::StringAttr moduleName, ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> ports) : moduleName(std::move(moduleName)), ports(std::move(ports)) {}

  KeyTy getAsKey() const {
    return KeyTy(moduleName, ports);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (moduleName == std::get<0>(tblgenKey)) && (ports == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ModuleTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto moduleName = std::move(std::get<0>(tblgenKey));
    auto ports = std::move(std::get<1>(tblgenKey));
    ports = allocator.copyInto(ports);
    return new (allocator.allocate<ModuleTypeStorage>()) ModuleTypeStorage(std::move(moduleName), std::move(ports));
  }

  mlir::StringAttr moduleName;
  ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> ports;
};

} // namespace detail
ModuleType ModuleType::get(::mlir::MLIRContext *context, mlir::StringAttr moduleName, ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> ports) {
  return Base::get(context, std::move(moduleName), std::move(ports));
}

mlir::StringAttr ModuleType::getModuleName() const {
  return getImpl()->moduleName;
}

::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> ModuleType::getPorts() const {
  return getImpl()->ports;
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::ModuleType)

#endif // GET_TYPEDEF_CLASSES

