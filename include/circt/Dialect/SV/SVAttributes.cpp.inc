/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::sv::MacroIdentAttr,
::circt::sv::SVAttributeAttr,
::circt::sv::CaseExprPatternAttr,
::circt::sv::ValidationQualifierTypeEnumAttr,
::circt::sv::IncludeStyleAttr,
::circt::sv::ModportDirectionAttr,
::circt::sv::ModportStructAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::sv::MacroIdentAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::MacroIdentAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::SVAttributeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::SVAttributeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::CaseExprPatternAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::CaseExprPatternAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::ValidationQualifierTypeEnumAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::ValidationQualifierTypeEnumAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::IncludeStyleAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::IncludeStyleAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::ModportDirectionAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::ModportDirectionAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::ModportStructAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::ModportStructAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::sv::MacroIdentAttr>([&](auto t) {
      printer << ::circt::sv::MacroIdentAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::SVAttributeAttr>([&](auto t) {
      printer << ::circt::sv::SVAttributeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::CaseExprPatternAttr>([&](auto t) {
      printer << ::circt::sv::CaseExprPatternAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::sv::ValidationQualifierTypeEnumAttr>([&](auto t) {
      printer << ::circt::sv::ValidationQualifierTypeEnumAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::IncludeStyleAttr>([&](auto t) {
      printer << ::circt::sv::IncludeStyleAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::ModportDirectionAttr>([&](auto t) {
      printer << ::circt::sv::ModportDirectionAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::ModportStructAttr>([&](auto t) {
      printer << ::circt::sv::ModportStructAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::sv {

namespace detail {

struct MacroIdentAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FlatSymbolRefAttr>;
  MacroIdentAttrStorage(::mlir::FlatSymbolRefAttr ident) : ident(std::move(ident)) {}

  KeyTy getAsKey() const {
    return KeyTy(ident);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (ident == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static MacroIdentAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto ident = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<MacroIdentAttrStorage>()) MacroIdentAttrStorage(std::move(ident));
  }

  ::mlir::FlatSymbolRefAttr ident;
};

} // namespace detail
MacroIdentAttr MacroIdentAttr::get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr ident) {
  return Base::get(context, std::move(ident));
}

MacroIdentAttr MacroIdentAttr::get(::mlir::MLIRContext *context, ::llvm::StringRef ident) {
  return get(::mlir::StringAttr::get(context, ident));
}

MacroIdentAttr MacroIdentAttr::get(::mlir::StringAttr ident) {
  return Base::get(ident.getContext(), ::mlir::FlatSymbolRefAttr::get(ident));
}

::mlir::Attribute MacroIdentAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FlatSymbolRefAttr> _result_ident;

  // Parse variable 'ident'
  _result_ident = ::mlir::FieldParser<::mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_ident)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MacroIdentAttr parameter 'ident' which is to be a `::mlir::FlatSymbolRefAttr`");
    return {};
  }
  assert(::mlir::succeeded(_result_ident));
  return MacroIdentAttr::get(odsParser.getContext(),
      ::mlir::FlatSymbolRefAttr((*_result_ident)));
}

void MacroIdentAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter.printStrippedAttrOrType(getIdent());
}

::mlir::FlatSymbolRefAttr MacroIdentAttr::getIdent() const {
  return getImpl()->ident;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::MacroIdentAttr)
namespace circt::sv {

namespace detail {

struct SVAttributeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::StringAttr, mlir::BoolAttr>;
  SVAttributeAttrStorage(::mlir::StringAttr name, ::mlir::StringAttr expression, mlir::BoolAttr emitAsComment) : name(std::move(name)), expression(std::move(expression)), emitAsComment(std::move(emitAsComment)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, expression, emitAsComment);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (expression == std::get<1>(tblgenKey)) && (emitAsComment == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static SVAttributeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto expression = std::move(std::get<1>(tblgenKey));
    auto emitAsComment = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<SVAttributeAttrStorage>()) SVAttributeAttrStorage(std::move(name), std::move(expression), std::move(emitAsComment));
  }

  ::mlir::StringAttr name;
  ::mlir::StringAttr expression;
  mlir::BoolAttr emitAsComment;
};

} // namespace detail
SVAttributeAttr SVAttributeAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::StringAttr expression, mlir::BoolAttr emitAsComment) {
  return Base::get(context, std::move(name), std::move(expression), std::move(emitAsComment));
}

SVAttributeAttr SVAttributeAttr::get(::mlir::MLIRContext *context, ::llvm::StringRef name, bool emitAsComment) {
  return get(context, StringAttr::get(context, name), StringAttr(),
             BoolAttr::get(context, emitAsComment));
}

SVAttributeAttr SVAttributeAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, bool emitAsComment) {
  return get(context, name, StringAttr(),
             BoolAttr::get(context, emitAsComment));
}

SVAttributeAttr SVAttributeAttr::get(::mlir::MLIRContext *context, ::llvm::StringRef name, ::llvm::StringRef expression, bool emitAsComment) {
  return get(context, StringAttr::get(context, name),
             StringAttr::get(context, expression),
             BoolAttr::get(context, emitAsComment));
}

SVAttributeAttr SVAttributeAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::StringAttr expression, bool emitAsComment) {
  return get(context, name, expression,
             BoolAttr::get(context, emitAsComment));
}

::mlir::StringAttr SVAttributeAttr::getName() const {
  return getImpl()->name;
}

::mlir::StringAttr SVAttributeAttr::getExpression() const {
  return getImpl()->expression;
}

mlir::BoolAttr SVAttributeAttr::getEmitAsComment() const {
  return getImpl()->emitAsComment;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::SVAttributeAttr)
namespace circt::sv {


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::CaseExprPatternAttr)
namespace circt::sv {

namespace detail {

struct ValidationQualifierTypeEnumAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::sv::ValidationQualifierTypeEnum>;
  ValidationQualifierTypeEnumAttrStorage(::circt::sv::ValidationQualifierTypeEnum value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ValidationQualifierTypeEnumAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ValidationQualifierTypeEnumAttrStorage>()) ValidationQualifierTypeEnumAttrStorage(std::move(value));
  }

  ::circt::sv::ValidationQualifierTypeEnum value;
};

} // namespace detail
ValidationQualifierTypeEnumAttr ValidationQualifierTypeEnumAttr::get(::mlir::MLIRContext *context, ::circt::sv::ValidationQualifierTypeEnum value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute ValidationQualifierTypeEnumAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::sv::ValidationQualifierTypeEnum> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::sv::ValidationQualifierTypeEnum> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::sv::symbolizeValidationQualifierTypeEnum(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::sv::ValidationQualifierTypeEnum" << " to be one of: " << "plain" << ", " << "unique" << ", " << "unique0" << ", " << "priority")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ValidationQualifierTypeAttr parameter 'value' which is to be a `::circt::sv::ValidationQualifierTypeEnum`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return ValidationQualifierTypeEnumAttr::get(odsParser.getContext(),
      ::circt::sv::ValidationQualifierTypeEnum((*_result_value)));
}

void ValidationQualifierTypeEnumAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyValidationQualifierTypeEnum(getValue());
}

::circt::sv::ValidationQualifierTypeEnum ValidationQualifierTypeEnumAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::ValidationQualifierTypeEnumAttr)
namespace circt::sv {

namespace detail {

struct IncludeStyleAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::IncludeStyle>;
  IncludeStyleAttrStorage(::IncludeStyle value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static IncludeStyleAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<IncludeStyleAttrStorage>()) IncludeStyleAttrStorage(std::move(value));
  }

  ::IncludeStyle value;
};

} // namespace detail
IncludeStyleAttr IncludeStyleAttr::get(::mlir::MLIRContext *context, ::IncludeStyle value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute IncludeStyleAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::IncludeStyle> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::IncludeStyle> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::symbolizeIncludeStyle(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::IncludeStyle" << " to be one of: " << "local" << ", " << "system")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse IncludeStyleAttr parameter 'value' which is to be a `::IncludeStyle`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return IncludeStyleAttr::get(odsParser.getContext(),
      ::IncludeStyle((*_result_value)));
}

void IncludeStyleAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyIncludeStyle(getValue());
}

::IncludeStyle IncludeStyleAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::IncludeStyleAttr)
namespace circt::sv {

namespace detail {

struct ModportDirectionAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::sv::ModportDirection>;
  ModportDirectionAttrStorage(::circt::sv::ModportDirection value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ModportDirectionAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ModportDirectionAttrStorage>()) ModportDirectionAttrStorage(std::move(value));
  }

  ::circt::sv::ModportDirection value;
};

} // namespace detail
ModportDirectionAttr ModportDirectionAttr::get(::mlir::MLIRContext *context, ::circt::sv::ModportDirection value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute ModportDirectionAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::sv::ModportDirection> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::sv::ModportDirection> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::sv::symbolizeModportDirection(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::sv::ModportDirection" << " to be one of: " << "input" << ", " << "output" << ", " << "inout")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ModportDirectionAttr parameter 'value' which is to be a `::circt::sv::ModportDirection`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return ModportDirectionAttr::get(odsParser.getContext(),
      ::circt::sv::ModportDirection((*_result_value)));
}

void ModportDirectionAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyModportDirection(getValue());
}

::circt::sv::ModportDirection ModportDirectionAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::ModportDirectionAttr)
namespace circt::sv {

namespace detail {

struct ModportStructAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::sv::ModportDirectionAttr, mlir::FlatSymbolRefAttr>;
  ModportStructAttrStorage(::circt::sv::ModportDirectionAttr direction, mlir::FlatSymbolRefAttr signal) : direction(std::move(direction)), signal(std::move(signal)) {}

  KeyTy getAsKey() const {
    return KeyTy(direction, signal);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (direction == std::get<0>(tblgenKey)) && (signal == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ModportStructAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto direction = std::move(std::get<0>(tblgenKey));
    auto signal = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ModportStructAttrStorage>()) ModportStructAttrStorage(std::move(direction), std::move(signal));
  }

  ::circt::sv::ModportDirectionAttr direction;
  mlir::FlatSymbolRefAttr signal;
};

} // namespace detail
ModportStructAttr ModportStructAttr::get(::mlir::MLIRContext *context, ::circt::sv::ModportDirectionAttr direction, mlir::FlatSymbolRefAttr signal) {
  return Base::get(context, std::move(direction), std::move(signal));
}

::mlir::Attribute ModportStructAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::sv::ModportDirectionAttr> _result_direction;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_signal;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  // Parse parameter struct
  bool _seen_direction = false;
  bool _seen_signal = false;
  {
    const auto _loop_body = [&](::llvm::StringRef _paramKey) -> bool {
      // Parse literal '='
      if (odsParser.parseEqual()) return {};
      if (!_seen_direction && _paramKey == "direction") {
        _seen_direction = true;

        // Parse variable 'direction'
        _result_direction = ::mlir::FieldParser<::circt::sv::ModportDirectionAttr>::parse(odsParser);
        if (::mlir::failed(_result_direction)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ModportStruct parameter 'direction' which is to be a `::circt::sv::ModportDirectionAttr`");
          return {};
        }
      } else if (!_seen_signal && _paramKey == "signal") {
        _seen_signal = true;

        // Parse variable 'signal'
        _result_signal = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
        if (::mlir::failed(_result_signal)) {
          odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ModportStruct parameter 'signal' which is to be a `mlir::FlatSymbolRefAttr`");
          return {};
        }
      } else {
        odsParser.emitError(odsParser.getCurrentLocation(), "duplicate or unknown struct parameter name: ") << _paramKey;
        return {};
      }
      return true;
    };
    for (unsigned odsStructIndex = 0; odsStructIndex < 2; ++odsStructIndex) {
      ::llvm::StringRef _paramKey;
      if (odsParser.parseKeyword(&_paramKey)) {
        odsParser.emitError(odsParser.getCurrentLocation(),
                           "expected a parameter name in struct");
        return {};
      }
      if (!_loop_body(_paramKey)) return {};
      if ((odsStructIndex != 2 - 1) && odsParser.parseComma())
        return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_direction));
  assert(::mlir::succeeded(_result_signal));
  return ModportStructAttr::get(odsParser.getContext(),
      ::circt::sv::ModportDirectionAttr((*_result_direction)),
      mlir::FlatSymbolRefAttr((*_result_signal)));
}

void ModportStructAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  {
    bool _firstPrinted = true;
    if (!_firstPrinted) odsPrinter << ", ";
    _firstPrinted = false;
    odsPrinter << "direction = ";
    odsPrinter.printStrippedAttrOrType(getDirection());
    if (!_firstPrinted) odsPrinter << ", ";
    _firstPrinted = false;
    odsPrinter << "signal = ";
    odsPrinter.printStrippedAttrOrType(getSignal());
  }
  odsPrinter << ">";
}

::circt::sv::ModportDirectionAttr ModportStructAttr::getDirection() const {
  return getImpl()->direction;
}

mlir::FlatSymbolRefAttr ModportStructAttr::getSignal() const {
  return getImpl()->signal;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::ModportStructAttr)
namespace circt::sv {


/// Parse an attribute registered to this dialect.
::mlir::Attribute SVDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void SVDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::sv

#endif // GET_ATTRDEF_CLASSES

