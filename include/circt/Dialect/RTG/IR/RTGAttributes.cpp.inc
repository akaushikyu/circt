/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::rtg::DefaultContextAttr,
::circt::rtg::AnyContextAttr,
::circt::rtg::SetAttr,
::circt::rtg::MapAttr,
::circt::rtg::TupleAttr,
::circt::rtg::ImmediateAttr,
::circt::rtg::VirtualRegisterConfigAttr,
::circt::rtg::LabelAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::rtg::DefaultContextAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::DefaultContextAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::AnyContextAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::AnyContextAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::SetAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::SetAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::MapAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::MapAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::TupleAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::TupleAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::ImmediateAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::ImmediateAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::VirtualRegisterConfigAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::VirtualRegisterConfigAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::LabelAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::LabelAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::rtg::DefaultContextAttr>([&](auto t) {
      printer << ::circt::rtg::DefaultContextAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::AnyContextAttr>([&](auto t) {
      printer << ::circt::rtg::AnyContextAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::SetAttr>([&](auto t) {
      printer << ::circt::rtg::SetAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::MapAttr>([&](auto t) {
      printer << ::circt::rtg::MapAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::TupleAttr>([&](auto t) {
      printer << ::circt::rtg::TupleAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::ImmediateAttr>([&](auto t) {
      printer << ::circt::rtg::ImmediateAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::VirtualRegisterConfigAttr>([&](auto t) {
      printer << ::circt::rtg::VirtualRegisterConfigAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::LabelAttr>([&](auto t) {
      printer << ::circt::rtg::LabelAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::rtg {

namespace detail {

struct DefaultContextAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  DefaultContextAttrStorage(::mlir::Type type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static DefaultContextAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<DefaultContextAttrStorage>()) DefaultContextAttrStorage(std::move(type));
  }

  ::mlir::Type type;
};

} // namespace detail
DefaultContextAttr DefaultContextAttr::get(::mlir::MLIRContext *context, ::mlir::Type type) {
  return Base::get(context, std::move(type));
}

::mlir::Attribute DefaultContextAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_type;

  if (odsType) {
    if (auto reqType = ::llvm::dyn_cast<::mlir::Type>(odsType)) {
      _result_type = reqType;
    } else {
      odsParser.emitError(odsLoc, "invalid kind of type specified");
      return {};
    }
  }
  return DefaultContextAttr::get(odsParser.getContext(),
      ::mlir::Type((_result_type.value_or(::mlir::NoneType::get(odsParser.getContext())))));
}

void DefaultContextAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}

::mlir::Type DefaultContextAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::DefaultContextAttr)
namespace circt::rtg {

namespace detail {

struct AnyContextAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  AnyContextAttrStorage(::mlir::Type type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static AnyContextAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<AnyContextAttrStorage>()) AnyContextAttrStorage(std::move(type));
  }

  ::mlir::Type type;
};

} // namespace detail
AnyContextAttr AnyContextAttr::get(::mlir::MLIRContext *context, ::mlir::Type type) {
  return Base::get(context, std::move(type));
}

::mlir::Attribute AnyContextAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_type;

  if (odsType) {
    if (auto reqType = ::llvm::dyn_cast<::mlir::Type>(odsType)) {
      _result_type = reqType;
    } else {
      odsParser.emitError(odsLoc, "invalid kind of type specified");
      return {};
    }
  }
  return AnyContextAttr::get(odsParser.getContext(),
      ::mlir::Type((_result_type.value_or(::mlir::NoneType::get(odsParser.getContext())))));
}

void AnyContextAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}

::mlir::Type AnyContextAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::AnyContextAttr)
namespace circt::rtg {

namespace detail {

struct SetAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<rtg::SetType, const ::llvm::DenseSet<TypedAttr> *>;
  SetAttrStorage(rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements) : type(std::move(type)), elements(std::move(elements)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, elements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (elements == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static SetAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto elements = std::move(std::get<1>(tblgenKey));

        elements = new (allocator.allocate<DenseSet<TypedAttr>>())
          DenseSet<TypedAttr>(elements->begin(), elements->end());

    return new (allocator.allocate<SetAttrStorage>()) SetAttrStorage(std::move(type), std::move(elements));
  }

  rtg::SetType type;
  const ::llvm::DenseSet<TypedAttr> * elements;
};

} // namespace detail
SetAttr SetAttr::get(::mlir::MLIRContext *context, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements) {
  return Base::get(context, std::move(type), std::move(elements));
}

SetAttr SetAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements) {
  return Base::getChecked(emitError, context, std::move(type), std::move(elements));
}

SetAttr SetAttr::get(rtg::SetType type, const ::llvm::DenseSet<::mlir::TypedAttr> *elements) {
  return Base::get(type.getContext(), type, elements);
}

SetAttr SetAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::SetType type, const ::llvm::DenseSet<::mlir::TypedAttr> *elements) {
  return Base::getChecked(emitError, type.getContext(), type, elements);
}

::llvm::LogicalResult SetAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::SetType type, const ::llvm::DenseSet<TypedAttr> *elements) {
  if (::mlir::failed(verify(emitError, type, elements)))
    return ::mlir::failure();
  return ::mlir::success();
}

rtg::SetType SetAttr::getType() const {
  return getImpl()->type;
}

const ::llvm::DenseSet<TypedAttr> *SetAttr::getElements() const {
  return getImpl()->elements;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::SetAttr)
namespace circt::rtg {

namespace detail {

struct MapAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<rtg::MapType, const ::llvm::DenseMap<TypedAttr, TypedAttr> *>;
  MapAttrStorage(rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries) : type(std::move(type)), entries(std::move(entries)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, entries);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (entries == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static MapAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto entries = std::move(std::get<1>(tblgenKey));
    entries = new (allocator.allocate<DenseMap<TypedAttr, TypedAttr>>()) DenseMap<TypedAttr, TypedAttr>(entries->begin(), entries->end());
    return new (allocator.allocate<MapAttrStorage>()) MapAttrStorage(std::move(type), std::move(entries));
  }

  rtg::MapType type;
  const ::llvm::DenseMap<TypedAttr, TypedAttr> * entries;
};

} // namespace detail
MapAttr MapAttr::get(::mlir::MLIRContext *context, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries) {
  return Base::get(context, std::move(type), std::move(entries));
}

MapAttr MapAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries) {
  return Base::getChecked(emitError, context, std::move(type), std::move(entries));
}

MapAttr MapAttr::get(rtg::MapType type, const ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> *entries) {
  return Base::get(type.getContext(), type, entries);
}

MapAttr MapAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type, const ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> *entries) {
  return Base::getChecked(emitError, type.getContext(), type, entries);
}

MapAttr MapAttr::get(rtg::MapType type) {
  ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> entries;
  return Base::get(type.getContext(), type, &entries);
}

MapAttr MapAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type) {
  ::llvm::DenseMap<::mlir::TypedAttr, ::mlir::TypedAttr> entries;
  return Base::getChecked(emitError, type.getContext(), type, &entries);
}

::llvm::LogicalResult MapAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, rtg::MapType type, const ::llvm::DenseMap<TypedAttr, TypedAttr> *entries) {
  if (::mlir::failed(verify(emitError, type, entries)))
    return ::mlir::failure();
  return ::mlir::success();
}

rtg::MapType MapAttr::getType() const {
  return getImpl()->type;
}

const ::llvm::DenseMap<TypedAttr, TypedAttr> *MapAttr::getEntries() const {
  return getImpl()->entries;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::MapAttr)
namespace circt::rtg {

namespace detail {

struct TupleAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::mlir::TypedAttr>>;
  TupleAttrStorage(::llvm::ArrayRef<::mlir::TypedAttr> elements) : elements(std::move(elements)) {}

  KeyTy getAsKey() const {
    return KeyTy(elements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elements == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static TupleAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elements = std::move(std::get<0>(tblgenKey));
    elements = allocator.copyInto(elements);
    return new (allocator.allocate<TupleAttrStorage>()) TupleAttrStorage(std::move(elements));
  }

  ::llvm::ArrayRef<::mlir::TypedAttr> elements;
};

} // namespace detail
TupleAttr TupleAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::mlir::TypedAttr> elements) {
  return Base::get(context, std::move(elements));
}

::mlir::Attribute TupleAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<::mlir::TypedAttr>> _result_elements;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elements'
  _result_elements = ::mlir::FieldParser<::llvm::SmallVector<::mlir::TypedAttr>>::parse(odsParser);
  if (::mlir::failed(_result_elements)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse TupleAttr parameter 'elements' which is to be a `::llvm::ArrayRef<::mlir::TypedAttr>`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elements));
  return TupleAttr::get(odsParser.getContext(),
      ::llvm::ArrayRef<::mlir::TypedAttr>((*_result_elements)));
}

void TupleAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElements());
  odsPrinter << ">";
}

::llvm::ArrayRef<::mlir::TypedAttr> TupleAttr::getElements() const {
  return getImpl()->elements;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::TupleAttr)
namespace circt::rtg {

ImmediateAttr ImmediateAttr::get(::mlir::MLIRContext *context, llvm::APInt value) {
  return Base::get(context, std::move(value));
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::ImmediateAttr)
namespace circt::rtg {

namespace detail {

struct VirtualRegisterConfigAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<rtg::RegisterAttrInterface>>;
  VirtualRegisterConfigAttrStorage(::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs) : allowedRegs(std::move(allowedRegs)) {}

  KeyTy getAsKey() const {
    return KeyTy(allowedRegs);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (allowedRegs == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static VirtualRegisterConfigAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto allowedRegs = std::move(std::get<0>(tblgenKey));
    allowedRegs = allocator.copyInto(allowedRegs);
    return new (allocator.allocate<VirtualRegisterConfigAttrStorage>()) VirtualRegisterConfigAttrStorage(std::move(allowedRegs));
  }

  ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs;
};

} // namespace detail
VirtualRegisterConfigAttr VirtualRegisterConfigAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs) {
  return Base::get(context, std::move(allowedRegs));
}

VirtualRegisterConfigAttr VirtualRegisterConfigAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs) {
  return Base::getChecked(emitError, context, std::move(allowedRegs));
}

::llvm::LogicalResult VirtualRegisterConfigAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<rtg::RegisterAttrInterface> allowedRegs) {
  if (::mlir::failed(verify(emitError, allowedRegs)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Attribute VirtualRegisterConfigAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<rtg::RegisterAttrInterface>> _result_allowedRegs;
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'allowedRegs'
  _result_allowedRegs = ::mlir::FieldParser<::llvm::SmallVector<rtg::RegisterAttrInterface>>::parse(odsParser);
  if (::mlir::failed(_result_allowedRegs)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse VirtualRegisterConfigAttr parameter 'allowedRegs' which is to be a `::llvm::ArrayRef<rtg::RegisterAttrInterface>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  assert(::mlir::succeeded(_result_allowedRegs));
  return odsParser.getChecked<VirtualRegisterConfigAttr>(odsLoc, odsParser.getContext(),
      ::llvm::ArrayRef<rtg::RegisterAttrInterface>((*_result_allowedRegs)));
}

void VirtualRegisterConfigAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "[";
  odsPrinter.printStrippedAttrOrType(getAllowedRegs());
  odsPrinter << "]";
}

::llvm::ArrayRef<rtg::RegisterAttrInterface> VirtualRegisterConfigAttr::getAllowedRegs() const {
  return getImpl()->allowedRegs;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::VirtualRegisterConfigAttr)
namespace circt::rtg {

namespace detail {

struct LabelAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::StringRef>;
  LabelAttrStorage(::llvm::StringRef name) : name(std::move(name)) {}

  KeyTy getAsKey() const {
    return KeyTy(name);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LabelAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    name = allocator.copyInto(name);
    return new (allocator.allocate<LabelAttrStorage>()) LabelAttrStorage(std::move(name));
  }

  ::llvm::StringRef name;
};

} // namespace detail
LabelAttr LabelAttr::get(::mlir::MLIRContext *context, ::llvm::StringRef name) {
  return Base::get(context, std::move(name));
}

::mlir::Attribute LabelAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<std::string> _result_name;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'name'
  _result_name = ::mlir::FieldParser<std::string>::parse(odsParser);
  if (::mlir::failed(_result_name)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LabelAttr parameter 'name' which is to be a `::llvm::StringRef`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_name));
  return LabelAttr::get(odsParser.getContext(),
      ::llvm::StringRef((*_result_name)));
}

void LabelAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printString(getName());;
  odsPrinter << ">";
}

::llvm::StringRef LabelAttr::getName() const {
  return getImpl()->name;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::LabelAttr)
namespace circt::rtg {


/// Parse an attribute registered to this dialect.
::mlir::Attribute RTGDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void RTGDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::rtg

#endif // GET_ATTRDEF_CLASSES

