/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::esi::ListType,
::circt::esi::ChannelType,
::circt::esi::ChannelBundleType,
::circt::esi::WindowType,
::circt::esi::WindowFrameType,
::circt::esi::WindowFieldType,
::circt::esi::AnyType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::esi::ListType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::ListType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::ChannelType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::ChannelType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::ChannelBundleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::ChannelBundleType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::WindowType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::WindowType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::WindowFrameType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::WindowFrameType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::WindowFieldType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::WindowFieldType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::AnyType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::AnyType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::esi::ListType>([&](auto t) {
      printer << ::circt::esi::ListType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::ChannelType>([&](auto t) {
      printer << ::circt::esi::ChannelType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::ChannelBundleType>([&](auto t) {
      printer << ::circt::esi::ChannelBundleType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::WindowType>([&](auto t) {
      printer << ::circt::esi::WindowType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::WindowFrameType>([&](auto t) {
      printer << ::circt::esi::WindowFrameType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::WindowFieldType>([&](auto t) {
      printer << ::circt::esi::WindowFieldType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::AnyType>([&](auto t) {
      printer << ::circt::esi::AnyType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::esi {

namespace detail {

struct ListTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<Type>;
  ListTypeStorage(Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ListTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ListTypeStorage>()) ListTypeStorage(std::move(elementType));
  }

  Type elementType;
};

} // namespace detail
ListType ListType::get(::mlir::MLIRContext *context, Type elementType) {
  return Base::get(context, std::move(elementType));
}

::mlir::Type ListType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ESIListType parameter 'elementType' which is to be a `Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return ListType::get(odsParser.getContext(),
      Type((*_result_elementType)));
}

void ListType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

Type ListType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ListType)
namespace circt::esi {

namespace detail {

struct ChannelTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<Type, ::circt::esi::ChannelSignaling, uint64_t>;
  ChannelTypeStorage(Type inner, ::circt::esi::ChannelSignaling signaling, uint64_t dataDelay) : inner(std::move(inner)), signaling(std::move(signaling)), dataDelay(std::move(dataDelay)) {}

  KeyTy getAsKey() const {
    return KeyTy(inner, signaling, dataDelay);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (inner == std::get<0>(tblgenKey)) && (signaling == std::get<1>(tblgenKey)) && (dataDelay == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static ChannelTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto inner = std::move(std::get<0>(tblgenKey));
    auto signaling = std::move(std::get<1>(tblgenKey));
    auto dataDelay = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<ChannelTypeStorage>()) ChannelTypeStorage(std::move(inner), std::move(signaling), std::move(dataDelay));
  }

  Type inner;
  ::circt::esi::ChannelSignaling signaling;
  uint64_t dataDelay;
};

} // namespace detail
ChannelType ChannelType::get(::mlir::MLIRContext *context, Type inner, ::circt::esi::ChannelSignaling signaling, uint64_t dataDelay) {
  return Base::get(context, std::move(inner), std::move(signaling), std::move(dataDelay));
}

ChannelType ChannelType::get(::mlir::MLIRContext *context, Type type) {
  return Base::get(type.getContext(), type,
                   ::circt::esi::ChannelSignaling::ValidReady, 0);
}

::mlir::Type ChannelType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<Type> _result_inner;
  ::mlir::FailureOr<::circt::esi::ChannelSignaling> _result_signaling;
  ::mlir::FailureOr<uint64_t> _result_dataDelay;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'inner'
  _result_inner = ::mlir::FieldParser<Type>::parse(odsParser);
  if (::mlir::failed(_result_inner)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ChannelTypeImpl parameter 'inner' which is to be a `Type`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseOptionalComma()) {
  } else {

    // Parse variable 'signaling'
    _result_signaling = ::mlir::FieldParser<::circt::esi::ChannelSignaling>::parse(odsParser);
    if (::mlir::failed(_result_signaling)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ChannelTypeImpl parameter 'signaling' which is to be a `::circt::esi::ChannelSignaling`");
      return {};
    }
    // Parse literal '('
    if (odsParser.parseOptionalLParen()) {
    } else {

      // Parse variable 'dataDelay'
      _result_dataDelay = ::mlir::FieldParser<uint64_t>::parse(odsParser);
      if (::mlir::failed(_result_dataDelay)) {
        odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ChannelTypeImpl parameter 'dataDelay' which is to be a `uint64_t`");
        return {};
      }
      // Parse literal ')'
      if (odsParser.parseRParen()) return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_inner));
  return ChannelType::get(odsParser.getContext(),
      Type((*_result_inner)),
      ::circt::esi::ChannelSignaling((_result_signaling.value_or(::circt::esi::ChannelSignaling::ValidReady))),
      uint64_t((_result_dataDelay.value_or(0))));
}

void ChannelType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getInner());
  if (!(getSignaling() == ::circt::esi::ChannelSignaling::ValidReady)) {
    odsPrinter << ",";
    if (!(getSignaling() == ::circt::esi::ChannelSignaling::ValidReady)) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getSignaling());
    }
    if (!(getDataDelay() == 0)) {
      odsPrinter << "(";
      if (!(getDataDelay() == 0)) {
        odsPrinter.printStrippedAttrOrType(getDataDelay());
      }
      odsPrinter << ")";
    } else {
    }
  } else {
  }
  odsPrinter << ">";
}

Type ChannelType::getInner() const {
  return getImpl()->inner;
}

::circt::esi::ChannelSignaling ChannelType::getSignaling() const {
  return getImpl()->signaling;
}

uint64_t ChannelType::getDataDelay() const {
  return getImpl()->dataDelay;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ChannelType)
namespace circt::esi {

namespace detail {

struct ChannelBundleTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<BundledChannel>, ::mlir::UnitAttr>;
  ChannelBundleTypeStorage(::llvm::ArrayRef<BundledChannel> channels, ::mlir::UnitAttr resettable) : channels(std::move(channels)), resettable(std::move(resettable)) {}

  KeyTy getAsKey() const {
    return KeyTy(channels, resettable);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (channels == std::get<0>(tblgenKey)) && (resettable == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ChannelBundleTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto channels = std::move(std::get<0>(tblgenKey));
    auto resettable = std::move(std::get<1>(tblgenKey));
    channels = allocator.copyInto(channels);
    return new (allocator.allocate<ChannelBundleTypeStorage>()) ChannelBundleTypeStorage(std::move(channels), std::move(resettable));
  }

  ::llvm::ArrayRef<BundledChannel> channels;
  ::mlir::UnitAttr resettable;
};

} // namespace detail
ChannelBundleType ChannelBundleType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<BundledChannel> channels, ::mlir::UnitAttr resettable) {
  return Base::get(context, std::move(channels), std::move(resettable));
}

::mlir::Type ChannelBundleType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<BundledChannel>> _result_channels;
  ::mlir::FailureOr<::mlir::UnitAttr> _result_resettable;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'channels'
  _result_channels = ::mlir::FieldParser<::llvm::SmallVector<BundledChannel>>::parse(odsParser);
  if (::mlir::failed(_result_channels)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ChannelBundleType parameter 'channels' which is to be a `::llvm::ArrayRef<BundledChannel>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  // Parse literal 'reset'
  if (odsParser.parseOptionalKeyword("reset")) {
  } else {

    // Parse variable 'resettable'
    _result_resettable = ::mlir::UnitAttr::get(odsParser.getContext());
    if (::mlir::failed(_result_resettable)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ChannelBundleType parameter 'resettable' which is to be a `::mlir::UnitAttr`");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_channels));
  return ChannelBundleType::get(odsParser.getContext(),
      ::llvm::ArrayRef<BundledChannel>((*_result_channels)),
      ::mlir::UnitAttr((_result_resettable.value_or(::mlir::UnitAttr()))));
}

void ChannelBundleType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter << "[";
  odsPrinter.printStrippedAttrOrType(getChannels());
  odsPrinter << "]";
  if (!(getResettable() == ::mlir::UnitAttr())) {
    odsPrinter << ' ' << "reset";
    if (!(getResettable() == ::mlir::UnitAttr())) {
      odsPrinter << ' ';
      ;
    }
  } else {
  }
  odsPrinter << ">";
}

::llvm::ArrayRef<BundledChannel> ChannelBundleType::getChannels() const {
  return getImpl()->channels;
}

::mlir::UnitAttr ChannelBundleType::getResettable() const {
  return getImpl()->resettable;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ChannelBundleType)
namespace circt::esi {

namespace detail {

struct WindowTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<StringAttr, mlir::Type, ::llvm::ArrayRef<WindowFrameType>>;
  WindowTypeStorage(StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames) : name(std::move(name)), into(std::move(into)), frames(std::move(frames)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, into, frames);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (into == std::get<1>(tblgenKey)) && (frames == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static WindowTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto into = std::move(std::get<1>(tblgenKey));
    auto frames = std::move(std::get<2>(tblgenKey));
    frames = allocator.copyInto(frames);
    return new (allocator.allocate<WindowTypeStorage>()) WindowTypeStorage(std::move(name), std::move(into), std::move(frames));
  }

  StringAttr name;
  mlir::Type into;
  ::llvm::ArrayRef<WindowFrameType> frames;
};

} // namespace detail
WindowType WindowType::get(::mlir::MLIRContext *context, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames) {
  return Base::get(context, std::move(name), std::move(into), std::move(frames));
}

WindowType WindowType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames) {
  return Base::getChecked(emitError, context, std::move(name), std::move(into), std::move(frames));
}

::llvm::LogicalResult WindowType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr name, mlir::Type into, ::llvm::ArrayRef<WindowFrameType> frames) {
  if (::mlir::failed(verify(emitError, name, into, frames)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type WindowType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<StringAttr> _result_name;
  ::mlir::FailureOr<mlir::Type> _result_into;
  ::mlir::FailureOr<::llvm::SmallVector<WindowFrameType>> _result_frames;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'name'
  _result_name = ::mlir::FieldParser<StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_name)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ESIWindowType parameter 'name' which is to be a `StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'into'
  _result_into = ::mlir::FieldParser<mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_into)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ESIWindowType parameter 'into' which is to be a `mlir::Type`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'frames'
  _result_frames = ::mlir::FieldParser<::llvm::SmallVector<WindowFrameType>>::parse(odsParser);
  if (::mlir::failed(_result_frames)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ESIWindowType parameter 'frames' which is to be a `::llvm::ArrayRef<WindowFrameType>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_name));
  assert(::mlir::succeeded(_result_into));
  assert(::mlir::succeeded(_result_frames));
  return odsParser.getChecked<WindowType>(odsLoc, odsParser.getContext(),
      StringAttr((*_result_name)),
      mlir::Type((*_result_into)),
      ::llvm::ArrayRef<WindowFrameType>((*_result_frames)));
}

void WindowType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getName());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getInto());
  odsPrinter << ",";
  odsPrinter << ' ' << "[";
  odsPrinter.printStrippedAttrOrType(getFrames());
  odsPrinter << "]";
  odsPrinter << ">";
}

StringAttr WindowType::getName() const {
  return getImpl()->name;
}

mlir::Type WindowType::getInto() const {
  return getImpl()->into;
}

::llvm::ArrayRef<WindowFrameType> WindowType::getFrames() const {
  return getImpl()->frames;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WindowType)
namespace circt::esi {

namespace detail {

struct WindowFrameTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<StringAttr, ::llvm::ArrayRef<WindowFieldType>>;
  WindowFrameTypeStorage(StringAttr name, ::llvm::ArrayRef<WindowFieldType> members) : name(std::move(name)), members(std::move(members)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, members);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (members == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static WindowFrameTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto members = std::move(std::get<1>(tblgenKey));
    members = allocator.copyInto(members);
    return new (allocator.allocate<WindowFrameTypeStorage>()) WindowFrameTypeStorage(std::move(name), std::move(members));
  }

  StringAttr name;
  ::llvm::ArrayRef<WindowFieldType> members;
};

} // namespace detail
WindowFrameType WindowFrameType::get(::mlir::MLIRContext *context, StringAttr name, ::llvm::ArrayRef<WindowFieldType> members) {
  return Base::get(context, std::move(name), std::move(members));
}

::mlir::Type WindowFrameType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<StringAttr> _result_name;
  ::mlir::FailureOr<::llvm::SmallVector<WindowFieldType>> _result_members;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'name'
  _result_name = ::mlir::FieldParser<StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_name)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse WindowFrameType parameter 'name' which is to be a `StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'members'
  _result_members = ::mlir::FieldParser<::llvm::SmallVector<WindowFieldType>>::parse(odsParser);
  if (::mlir::failed(_result_members)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse WindowFrameType parameter 'members' which is to be a `::llvm::ArrayRef<WindowFieldType>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_name));
  assert(::mlir::succeeded(_result_members));
  return WindowFrameType::get(odsParser.getContext(),
      StringAttr((*_result_name)),
      ::llvm::ArrayRef<WindowFieldType>((*_result_members)));
}

void WindowFrameType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getName());
  odsPrinter << ",";
  odsPrinter << ' ' << "[";
  odsPrinter.printStrippedAttrOrType(getMembers());
  odsPrinter << "]";
  odsPrinter << ">";
}

StringAttr WindowFrameType::getName() const {
  return getImpl()->name;
}

::llvm::ArrayRef<WindowFieldType> WindowFrameType::getMembers() const {
  return getImpl()->members;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WindowFrameType)
namespace circt::esi {

namespace detail {

struct WindowFieldTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<StringAttr, uint64_t, uint64_t>;
  WindowFieldTypeStorage(StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth) : fieldName(std::move(fieldName)), numItems(std::move(numItems)), bulkCountWidth(std::move(bulkCountWidth)) {}

  KeyTy getAsKey() const {
    return KeyTy(fieldName, numItems, bulkCountWidth);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (fieldName == std::get<0>(tblgenKey)) && (numItems == std::get<1>(tblgenKey)) && (bulkCountWidth == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static WindowFieldTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto fieldName = std::move(std::get<0>(tblgenKey));
    auto numItems = std::move(std::get<1>(tblgenKey));
    auto bulkCountWidth = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<WindowFieldTypeStorage>()) WindowFieldTypeStorage(std::move(fieldName), std::move(numItems), std::move(bulkCountWidth));
  }

  StringAttr fieldName;
  uint64_t numItems;
  uint64_t bulkCountWidth;
};

} // namespace detail
WindowFieldType WindowFieldType::get(::mlir::MLIRContext *context, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth) {
  return Base::get(context, std::move(fieldName), std::move(numItems), std::move(bulkCountWidth));
}

WindowFieldType WindowFieldType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth) {
  return Base::getChecked(emitError, context, std::move(fieldName), std::move(numItems), std::move(bulkCountWidth));
}

::llvm::LogicalResult WindowFieldType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, StringAttr fieldName, uint64_t numItems, uint64_t bulkCountWidth) {
  if (::mlir::failed(verify(emitError, fieldName, numItems, bulkCountWidth)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type WindowFieldType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<StringAttr> _result_fieldName;
  ::mlir::FailureOr<uint64_t> _result_numItems;
  ::mlir::FailureOr<uint64_t> _result_bulkCountWidth;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'fieldName'
  _result_fieldName = ::mlir::FieldParser<StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_fieldName)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse WindowFieldType parameter 'fieldName' which is to be a `StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseOptionalComma()) {
  } else {

    // Parse variable 'numItems'
    _result_numItems = ::mlir::FieldParser<uint64_t>::parse(odsParser);
    if (::mlir::failed(_result_numItems)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse WindowFieldType parameter 'numItems' which is to be a `uint64_t`");
      return {};
    }
  }
  // Parse literal 'countWidth'
  if (odsParser.parseOptionalKeyword("countWidth")) {
  } else {

    // Parse variable 'bulkCountWidth'
    _result_bulkCountWidth = ::mlir::FieldParser<uint64_t>::parse(odsParser);
    if (::mlir::failed(_result_bulkCountWidth)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse WindowFieldType parameter 'bulkCountWidth' which is to be a `uint64_t`");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_fieldName));
  return odsParser.getChecked<WindowFieldType>(odsLoc, odsParser.getContext(),
      StringAttr((*_result_fieldName)),
      uint64_t((_result_numItems.value_or(uint64_t()))),
      uint64_t((_result_bulkCountWidth.value_or(uint64_t()))));
}

void WindowFieldType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getFieldName());
  if (!(getNumItems() == uint64_t())) {
    odsPrinter << ",";
    if (!(getNumItems() == uint64_t())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getNumItems());
    }
  } else {
  }
  if (!(getBulkCountWidth() == uint64_t())) {
    odsPrinter << ' ' << "countWidth";
    if (!(getBulkCountWidth() == uint64_t())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getBulkCountWidth());
    }
  } else {
  }
  odsPrinter << ">";
}

StringAttr WindowFieldType::getFieldName() const {
  return getImpl()->fieldName;
}

uint64_t WindowFieldType::getNumItems() const {
  return getImpl()->numItems;
}

uint64_t WindowFieldType::getBulkCountWidth() const {
  return getImpl()->bulkCountWidth;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WindowFieldType)
namespace circt::esi {

::mlir::Type AnyType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return AnyType::get(odsParser.getContext());
}

void AnyType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::AnyType)
namespace circt::esi {


/// Parse a type registered to this dialect.
::mlir::Type ESIDialect::parseType(::mlir::DialectAsmParser &parser) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef mnemonic;
  ::mlir::Type genType;
  auto parseResult = generatedTypeParser(parser, &mnemonic, genType);
  if (parseResult.has_value())
    return genType;
  
  parser.emitError(typeLoc) << "unknown  type `"
      << mnemonic << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print a type registered to this dialect.
void ESIDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::esi

#endif // GET_TYPEDEF_CLASSES

