/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::hw::OutputFileAttr,
::circt::hw::ParamDeclAttr,
::circt::hw::ParamDeclRefAttr,
::circt::hw::ParamVerbatimAttr,
::circt::hw::ParamExprAttr,
::circt::hw::EnumFieldAttr,
::circt::hw::InnerRefAttr,
::circt::hw::InnerSymPropertiesAttr,
::circt::hw::InnerSymAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::hw::OutputFileAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::OutputFileAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ParamDeclAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ParamDeclAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ParamDeclRefAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ParamDeclRefAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ParamVerbatimAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ParamVerbatimAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ParamExprAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ParamExprAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::EnumFieldAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::EnumFieldAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::InnerRefAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::InnerRefAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::InnerSymPropertiesAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::InnerSymPropertiesAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::InnerSymAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::InnerSymAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::hw::OutputFileAttr>([&](auto t) {
      printer << ::circt::hw::OutputFileAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ParamDeclAttr>([&](auto t) {
      printer << ::circt::hw::ParamDeclAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ParamDeclRefAttr>([&](auto t) {
      printer << ::circt::hw::ParamDeclRefAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ParamVerbatimAttr>([&](auto t) {
      printer << ::circt::hw::ParamVerbatimAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ParamExprAttr>([&](auto t) {
      printer << ::circt::hw::ParamExprAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::EnumFieldAttr>([&](auto t) {
      printer << ::circt::hw::EnumFieldAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::InnerRefAttr>([&](auto t) {
      printer << ::circt::hw::InnerRefAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::InnerSymPropertiesAttr>([&](auto t) {
      printer << ::circt::hw::InnerSymPropertiesAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::InnerSymAttr>([&](auto t) {
      printer << ::circt::hw::InnerSymAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::hw {

namespace detail {

struct OutputFileAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::BoolAttr, ::mlir::BoolAttr>;
  OutputFileAttrStorage(::mlir::StringAttr filename, ::mlir::BoolAttr excludeFromFilelist, ::mlir::BoolAttr includeReplicatedOps) : filename(std::move(filename)), excludeFromFilelist(std::move(excludeFromFilelist)), includeReplicatedOps(std::move(includeReplicatedOps)) {}

  KeyTy getAsKey() const {
    return KeyTy(filename, excludeFromFilelist, includeReplicatedOps);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (filename == std::get<0>(tblgenKey)) && (excludeFromFilelist == std::get<1>(tblgenKey)) && (includeReplicatedOps == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static OutputFileAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto filename = std::move(std::get<0>(tblgenKey));
    auto excludeFromFilelist = std::move(std::get<1>(tblgenKey));
    auto includeReplicatedOps = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<OutputFileAttrStorage>()) OutputFileAttrStorage(std::move(filename), std::move(excludeFromFilelist), std::move(includeReplicatedOps));
  }

  ::mlir::StringAttr filename;
  ::mlir::BoolAttr excludeFromFilelist;
  ::mlir::BoolAttr includeReplicatedOps;
};

} // namespace detail
OutputFileAttr OutputFileAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr filename, ::mlir::BoolAttr excludeFromFilelist, ::mlir::BoolAttr includeReplicatedOps) {
  return Base::get(context, std::move(filename), std::move(excludeFromFilelist), std::move(includeReplicatedOps));
}

OutputFileAttr OutputFileAttr::get(::mlir::StringAttr filename, ::mlir::BoolAttr excludeFromFileList, ::mlir::BoolAttr includeReplicatedOps) {
  return get(filename.getContext(), filename, excludeFromFileList,
             includeReplicatedOps);
}

::mlir::StringAttr OutputFileAttr::getFilename() const {
  return getImpl()->filename;
}

::mlir::BoolAttr OutputFileAttr::getExcludeFromFilelist() const {
  return getImpl()->excludeFromFilelist;
}

::mlir::BoolAttr OutputFileAttr::getIncludeReplicatedOps() const {
  return getImpl()->includeReplicatedOps;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::OutputFileAttr)
namespace circt::hw {

namespace detail {

struct ParamDeclAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::Type, ::mlir::Attribute>;
  ParamDeclAttrStorage(::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value) : name(std::move(name)), type(std::move(type)), value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, type, value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey)) && (value == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static ParamDeclAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    auto value = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<ParamDeclAttrStorage>()) ParamDeclAttrStorage(std::move(name), std::move(type), std::move(value));
  }

  ::mlir::StringAttr name;
  ::mlir::Type type;
  ::mlir::Attribute value;
};

} // namespace detail
ParamDeclAttr ParamDeclAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value) {
  return Base::get(context, std::move(name), std::move(type), std::move(value));
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringAttr name, ::mlir::Type type) {
  auto *context = type.getContext();
  return Base::get(context, name, type, Attribute());
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringRef name, ::mlir::Type type) {
  return get(StringAttr::get(type.getContext(), name), type);
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringAttr name, ::mlir::TypedAttr value) {
  auto *context = value.getContext();
  return Base::get(context, name, value.getType(), value);
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringRef name, ::mlir::TypedAttr value) {
  return get(StringAttr::get(value.getContext(), name), value);
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringRef name, ::mlir::Type type, ::mlir::TypedAttr value) {
  return get(value.getContext(),
                    StringAttr::get(value.getContext(), name),
                    type,
                    value);
}

::mlir::StringAttr ParamDeclAttr::getName() const {
  return getImpl()->name;
}

::mlir::Type ParamDeclAttr::getType() const {
  return getImpl()->type;
}

::mlir::Attribute ParamDeclAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ParamDeclAttr)
namespace circt::hw {

namespace detail {

struct ParamDeclRefAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::Type>;
  ParamDeclRefAttrStorage(::mlir::StringAttr name, ::mlir::Type type) : name(std::move(name)), type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ParamDeclRefAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ParamDeclRefAttrStorage>()) ParamDeclRefAttrStorage(std::move(name), std::move(type));
  }

  ::mlir::StringAttr name;
  ::mlir::Type type;
};

} // namespace detail
ParamDeclRefAttr ParamDeclRefAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type) {
  return Base::get(context, std::move(name), std::move(type));
}

ParamDeclRefAttr ParamDeclRefAttr::get(::mlir::StringAttr name, ::mlir::Type type) {
  return get(name.getContext(), name, type);
}

::mlir::StringAttr ParamDeclRefAttr::getName() const {
  return getImpl()->name;
}

::mlir::Type ParamDeclRefAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ParamDeclRefAttr)
namespace circt::hw {

namespace detail {

struct ParamVerbatimAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::Type>;
  ParamVerbatimAttrStorage(::mlir::StringAttr value, ::mlir::Type type) : value(std::move(value)), type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(value, type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ParamVerbatimAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ParamVerbatimAttrStorage>()) ParamVerbatimAttrStorage(std::move(value), std::move(type));
  }

  ::mlir::StringAttr value;
  ::mlir::Type type;
};

} // namespace detail
ParamVerbatimAttr ParamVerbatimAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr value, ::mlir::Type type) {
  return Base::get(context, std::move(value), std::move(type));
}

ParamVerbatimAttr ParamVerbatimAttr::get(::mlir::StringAttr value) {
  return get(value, NoneType::get(value.getContext()));
}

ParamVerbatimAttr ParamVerbatimAttr::get(::mlir::StringAttr value, ::mlir::Type type) {
  return get(value.getContext(), value, type);
}

::mlir::StringAttr ParamVerbatimAttr::getValue() const {
  return getImpl()->value;
}

::mlir::Type ParamVerbatimAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ParamVerbatimAttr)
namespace circt::hw {

namespace detail {

struct ParamExprAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PEO, ::llvm::ArrayRef<::mlir::TypedAttr>, ::mlir::Type>;
  ParamExprAttrStorage(PEO opcode, ::llvm::ArrayRef<::mlir::TypedAttr> operands, ::mlir::Type type) : opcode(std::move(opcode)), operands(std::move(operands)), type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(opcode, operands, type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (opcode == std::get<0>(tblgenKey)) && (operands == std::get<1>(tblgenKey)) && (type == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static ParamExprAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto opcode = std::move(std::get<0>(tblgenKey));
    auto operands = std::move(std::get<1>(tblgenKey));
    auto type = std::move(std::get<2>(tblgenKey));
    operands = allocator.copyInto(operands);
    return new (allocator.allocate<ParamExprAttrStorage>()) ParamExprAttrStorage(std::move(opcode), std::move(operands), std::move(type));
  }

  PEO opcode;
  ::llvm::ArrayRef<::mlir::TypedAttr> operands;
  ::mlir::Type type;
};

} // namespace detail
PEO ParamExprAttr::getOpcode() const {
  return getImpl()->opcode;
}

::llvm::ArrayRef<::mlir::TypedAttr> ParamExprAttr::getOperands() const {
  return getImpl()->operands;
}

::mlir::Type ParamExprAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ParamExprAttr)
namespace circt::hw {

namespace detail {

struct EnumFieldAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::TypeAttr>;
  EnumFieldAttrStorage(::mlir::StringAttr field, ::mlir::TypeAttr type) : field(std::move(field)), type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(field, type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (field == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static EnumFieldAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto field = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<EnumFieldAttrStorage>()) EnumFieldAttrStorage(std::move(field), std::move(type));
  }

  ::mlir::StringAttr field;
  ::mlir::TypeAttr type;
};

} // namespace detail
::mlir::StringAttr EnumFieldAttr::getField() const {
  return getImpl()->field;
}

::mlir::TypeAttr EnumFieldAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::EnumFieldAttr)
namespace circt::hw {

namespace detail {

struct InnerRefAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::FlatSymbolRefAttr, ::mlir::StringAttr>;
  InnerRefAttrStorage(::mlir::FlatSymbolRefAttr moduleRef, ::mlir::StringAttr name) : moduleRef(std::move(moduleRef)), name(std::move(name)) {}

  KeyTy getAsKey() const {
    return KeyTy(moduleRef, name);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (moduleRef == std::get<0>(tblgenKey)) && (name == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static InnerRefAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto moduleRef = std::move(std::get<0>(tblgenKey));
    auto name = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<InnerRefAttrStorage>()) InnerRefAttrStorage(std::move(moduleRef), std::move(name));
  }

  ::mlir::FlatSymbolRefAttr moduleRef;
  ::mlir::StringAttr name;
};

} // namespace detail
InnerRefAttr InnerRefAttr::get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr moduleRef, ::mlir::StringAttr name) {
  return Base::get(context, std::move(moduleRef), std::move(name));
}

InnerRefAttr InnerRefAttr::get(::mlir::StringAttr module, ::mlir::StringAttr name) {
  return Base::get(
      module.getContext(), mlir::FlatSymbolRefAttr::get(module), name);
}

::mlir::FlatSymbolRefAttr InnerRefAttr::getModuleRef() const {
  return getImpl()->moduleRef;
}

::mlir::StringAttr InnerRefAttr::getName() const {
  return getImpl()->name;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::InnerRefAttr)
namespace circt::hw {

namespace detail {

struct InnerSymPropertiesAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, uint64_t, ::mlir::StringAttr>;
  InnerSymPropertiesAttrStorage(::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility) : name(std::move(name)), fieldID(std::move(fieldID)), sym_visibility(std::move(sym_visibility)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, fieldID, sym_visibility);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (fieldID == std::get<1>(tblgenKey)) && (sym_visibility == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static InnerSymPropertiesAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto fieldID = std::move(std::get<1>(tblgenKey));
    auto sym_visibility = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<InnerSymPropertiesAttrStorage>()) InnerSymPropertiesAttrStorage(std::move(name), std::move(fieldID), std::move(sym_visibility));
  }

  ::mlir::StringAttr name;
  uint64_t fieldID;
  ::mlir::StringAttr sym_visibility;
};

} // namespace detail
InnerSymPropertiesAttr InnerSymPropertiesAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility) {
  return Base::get(context, std::move(name), std::move(fieldID), std::move(sym_visibility));
}

InnerSymPropertiesAttr InnerSymPropertiesAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility) {
  return Base::getChecked(emitError, context, std::move(name), std::move(fieldID), std::move(sym_visibility));
}

InnerSymPropertiesAttr InnerSymPropertiesAttr::get(::mlir::StringAttr sym) {
  return get(sym.getContext(), sym, 0,
                    mlir::StringAttr::get(sym.getContext(), "public") );
}

InnerSymPropertiesAttr InnerSymPropertiesAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::StringAttr sym) {
  return get(sym.getContext(), sym, 0,
                    mlir::StringAttr::get(sym.getContext(), "public") );
}

::llvm::LogicalResult InnerSymPropertiesAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::StringAttr name, uint64_t fieldID, ::mlir::StringAttr sym_visibility) {
  if (::mlir::failed(verify(emitError, name, fieldID, sym_visibility)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::StringAttr InnerSymPropertiesAttr::getName() const {
  return getImpl()->name;
}

uint64_t InnerSymPropertiesAttr::getFieldID() const {
  return getImpl()->fieldID;
}

::mlir::StringAttr InnerSymPropertiesAttr::getSymVisibility() const {
  return getImpl()->sym_visibility;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::InnerSymPropertiesAttr)
namespace circt::hw {

namespace detail {

struct InnerSymAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<InnerSymPropertiesAttr>>;
  InnerSymAttrStorage(::llvm::ArrayRef<InnerSymPropertiesAttr> props) : props(std::move(props)) {}

  KeyTy getAsKey() const {
    return KeyTy(props);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (props == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InnerSymAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto props = std::move(std::get<0>(tblgenKey));
    props = allocator.copyInto(props);
    return new (allocator.allocate<InnerSymAttrStorage>()) InnerSymAttrStorage(std::move(props));
  }

  ::llvm::ArrayRef<InnerSymPropertiesAttr> props;
};

} // namespace detail
InnerSymAttr InnerSymAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<InnerSymPropertiesAttr> props) {
  return Base::get(context, std::move(props));
}

InnerSymAttr InnerSymAttr::get(::mlir::StringAttr sym) {
  return get(sym.getContext(),
  {InnerSymPropertiesAttr::get(sym.getContext(), sym, 0,
                    mlir::StringAttr::get(sym.getContext(), "public"))});
}

InnerSymAttr InnerSymAttr::get(::mlir::MLIRContext *context) {
  return get(context, {});
}

::llvm::ArrayRef<InnerSymPropertiesAttr> InnerSymAttr::getProps() const {
  return getImpl()->props;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::InnerSymAttr)

#endif // GET_ATTRDEF_CLASSES

