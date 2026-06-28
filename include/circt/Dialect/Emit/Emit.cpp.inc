/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Emit.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::emit::FileListOp,
::circt::emit::FileOp,
::circt::emit::FragmentOp,
::circt::emit::RefOp,
::circt::emit::VerbatimOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Emit1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol ref array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Emit2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Emit3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Emit3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Emit1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FileListOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FileListOpGenericAdaptorBase::FileListOpGenericAdaptorBase(FileListOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FileListOpGenericAdaptorBase::getFileName() {
  auto attr = getFileNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr FileListOpGenericAdaptorBase::getFiles() {
  auto attr = getFilesAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > FileListOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
FileListOpAdaptor::FileListOpAdaptor(FileListOp op) : FileListOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FileListOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_file_name = getProperties().file_name; (void)tblgen_file_name;
  if (!tblgen_file_name) return emitError(loc, "'emit.file_list' op requires attribute 'file_name'");
  auto tblgen_files = getProperties().files; (void)tblgen_files;
  if (!tblgen_files) return emitError(loc, "'emit.file_list' op requires attribute 'files'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_file_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_file_name))))
    return emitError(loc, "'emit.file_list' op attribute 'file_name' failed to satisfy constraint: string attribute");

  if (tblgen_files && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_files))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_files), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))); }))))
    return emitError(loc, "'emit.file_list' op attribute 'files' failed to satisfy constraint: flat symbol ref array attribute");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'emit.file_list' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FileListOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.file_name;
       auto attr = dict.get("file_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `file_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.files;
       auto attr = dict.get("files");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `files` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FileListOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.file_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("file_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.files;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("files",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FileListOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.file_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.files.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FileListOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "file_name")
      return prop.file_name;

    if (name == "files")
      return prop.files;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FileListOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "file_name") {
       prop.file_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.file_name)>>(value);
       return;
    }

    if (name == "files") {
       prop.files = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.files)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FileListOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.file_name) attrs.append("file_name", prop.file_name);

    if (prop.files) attrs.append("files", prop.files);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FileListOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFileNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "file_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFilesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit2(attr, "files", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FileListOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.file_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.files)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FileListOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.file_name);
  writer.writeAttribute(prop.files);

  writer.writeOptionalAttribute(prop.sym_name);
}

::llvm::StringRef FileListOp::getFileName() {
  auto attr = getFileNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr FileListOp::getFiles() {
  auto attr = getFilesAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > FileListOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void FileListOp::setFileName(::llvm::StringRef attrValue) {
  getProperties().file_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FileListOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void FileListOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().file_name = file_name;
  odsState.getOrAddProperties<Properties>().files = files;
  if (sym_name) {
    odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  }
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
}

void FileListOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().file_name = file_name;
  odsState.getOrAddProperties<Properties>().files = files;
  if (sym_name) {
    odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
}

void FileListOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().file_name = odsBuilder.getStringAttr(file_name);
  odsState.getOrAddProperties<Properties>().files = files;
  if (sym_name) {
    odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  }
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
}

void FileListOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().file_name = odsBuilder.getStringAttr(file_name);
  odsState.getOrAddProperties<Properties>().files = files;
  if (sym_name) {
    odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef file_name, ::mlir::ArrayAttr files, /*optional*/::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(file_name)>(file_name), std::forward<decltype(files)>(files), std::forward<decltype(sym_name)>(sym_name));
}

void FileListOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FileListOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FileListOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FileListOp FileListOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FileListOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileListOp FileListOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FileListOp::verifyInvariantsImpl() {
  auto tblgen_file_name = getProperties().file_name; (void)tblgen_file_name;
  if (!tblgen_file_name) return emitOpError("requires attribute 'file_name'");
  auto tblgen_files = getProperties().files; (void)tblgen_files;
  if (!tblgen_files) return emitOpError("requires attribute 'files'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_file_name, "file_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit2(*this, tblgen_files, "files")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult FileListOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FileListOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr file_nameAttr;
  ::mlir::ArrayAttr filesAttr;
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseCustomAttributeWithFallback(file_nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (file_nameAttr) result.getOrAddProperties<FileListOp::Properties>().file_name = file_nameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(filesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (filesAttr) result.getOrAddProperties<FileListOp::Properties>().files = filesAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FileListOp::Properties>().sym_name = sym_nameAttr;
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
  return ::mlir::success();
}

void FileListOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getFileNameAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getFilesAttr());
  if (getSymNameAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
    _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("file_name");
  elidedAttrs.push_back("files");
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::emit
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::FileListOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::detail::FileListOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FileOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FileOpGenericAdaptorBase::FileOpGenericAdaptorBase(FileOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FileOpGenericAdaptorBase::getFileName() {
  auto attr = getFileNameAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > FileOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
FileOpAdaptor::FileOpAdaptor(FileOp op) : FileOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FileOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_file_name = getProperties().file_name; (void)tblgen_file_name;
  if (!tblgen_file_name) return emitError(loc, "'emit.file' op requires attribute 'file_name'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_file_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_file_name))))
    return emitError(loc, "'emit.file' op attribute 'file_name' failed to satisfy constraint: string attribute");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'emit.file' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FileOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.file_name;
       auto attr = dict.get("file_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `file_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FileOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.file_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("file_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FileOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.file_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FileOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "file_name")
      return prop.file_name;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FileOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "file_name") {
       prop.file_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.file_name)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FileOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.file_name) attrs.append("file_name", prop.file_name);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FileOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFileNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "file_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FileOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.file_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FileOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.file_name);

  writer.writeOptionalAttribute(prop.sym_name);
}

::llvm::StringRef FileOp::getFileName() {
  auto attr = getFileNameAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > FileOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void FileOp::setFileName(::llvm::StringRef attrValue) {
  getProperties().file_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FileOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

FileOp FileOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef fileName, StringRef symName, llvm::function_ref<void()> bodyCtor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fileName)>(fileName), std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
  auto __res__ = ::llvm::dyn_cast<FileOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileOp FileOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef fileName, StringRef symName, llvm::function_ref<void()> bodyCtor) {
  return create(builder, builder.getLoc(), std::forward<decltype(fileName)>(fileName), std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
}

FileOp FileOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr fileName, llvm::function_ref<void()> bodyCtor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fileName)>(fileName), std::forward<decltype(bodyCtor)>(bodyCtor));
  auto __res__ = ::llvm::dyn_cast<FileOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileOp FileOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr fileName, llvm::function_ref<void()> bodyCtor) {
  return create(builder, builder.getLoc(), std::forward<decltype(fileName)>(fileName), std::forward<decltype(bodyCtor)>(bodyCtor));
}

void FileOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const Twine &fileName, llvm::function_ref<void()> bodyCtor) {
      return build(odsBuilder, odsState, odsBuilder.getStringAttr(fileName), bodyCtor);
    
}

FileOp FileOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, const Twine &fileName, llvm::function_ref<void()> bodyCtor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fileName)>(fileName), std::forward<decltype(bodyCtor)>(bodyCtor));
  auto __res__ = ::llvm::dyn_cast<FileOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FileOp FileOp::create(::mlir::ImplicitLocOpBuilder &builder, const Twine &fileName, llvm::function_ref<void()> bodyCtor) {
  return create(builder, builder.getLoc(), std::forward<decltype(fileName)>(fileName), std::forward<decltype(bodyCtor)>(bodyCtor));
}

::llvm::LogicalResult FileOp::verifyInvariantsImpl() {
  auto tblgen_file_name = getProperties().file_name; (void)tblgen_file_name;
  if (!tblgen_file_name) return emitOpError("requires attribute 'file_name'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_file_name, "file_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Emit1(*this, region, "bodyRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult FileOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FileOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr file_nameAttr;
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegionRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(file_nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (file_nameAttr) result.getOrAddProperties<FileOp::Properties>().file_name = file_nameAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FileOp::Properties>().sym_name = sym_nameAttr;
  }

  if (parser.parseRegion(*bodyRegionRegion))
    return ::mlir::failure();

  if (bodyRegionRegion->empty()) bodyRegionRegion->emplaceBlock();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(bodyRegionRegion));
  return ::mlir::success();
}

void FileOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getFileNameAttr());
  if (getSymNameAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
    _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBodyRegion());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("file_name");
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::emit
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::FileOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::detail::FileOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::FragmentOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FragmentOpGenericAdaptorBase::FragmentOpGenericAdaptorBase(FragmentOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FragmentOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
FragmentOpAdaptor::FragmentOpAdaptor(FragmentOp op) : FragmentOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FragmentOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'emit.fragment' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'emit.fragment' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FragmentOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FragmentOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FragmentOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FragmentOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FragmentOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FragmentOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FragmentOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FragmentOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FragmentOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef FragmentOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void FragmentOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FragmentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef symName, llvm::function_ref<void()> bodyCtor) {
      return build(
          odsBuilder, odsState, odsBuilder.getStringAttr(symName), bodyCtor);
    
}

FragmentOp FragmentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef symName, llvm::function_ref<void()> bodyCtor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
  auto __res__ = ::llvm::dyn_cast<FragmentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FragmentOp FragmentOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef symName, llvm::function_ref<void()> bodyCtor) {
  return create(builder, builder.getLoc(), std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
}

FragmentOp FragmentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr symName, llvm::function_ref<void()> bodyCtor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
  auto __res__ = ::llvm::dyn_cast<FragmentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FragmentOp FragmentOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr symName, llvm::function_ref<void()> bodyCtor) {
  return create(builder, builder.getLoc(), std::forward<decltype(symName)>(symName), std::forward<decltype(bodyCtor)>(bodyCtor));
}

::llvm::LogicalResult FragmentOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Emit1(*this, region, "bodyRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult FragmentOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FragmentOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegionRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FragmentOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*bodyRegionRegion))
    return ::mlir::failure();

  if (bodyRegionRegion->empty()) bodyRegionRegion->emplaceBlock();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(bodyRegionRegion));
  return ::mlir::success();
}

void FragmentOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBodyRegion());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::emit
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::FragmentOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::detail::FragmentOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::RefOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RefOpGenericAdaptorBase::RefOpGenericAdaptorBase(RefOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RefOpGenericAdaptorBase::getTarget() {
  auto attr = getTargetAttr();
  return attr.getValue();
}


} // namespace detail
RefOpAdaptor::RefOpAdaptor(RefOp op) : RefOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RefOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_target = getProperties().target; (void)tblgen_target;
  if (!tblgen_target) return emitError(loc, "'emit.ref' op requires attribute 'target'");

  if (tblgen_target && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_target))))
    return emitError(loc, "'emit.ref' op attribute 'target' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RefOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.target;
       auto attr = dict.get("target");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `target` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute RefOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.target;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("target",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RefOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.target.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RefOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "target")
      return prop.target;
  return std::nullopt;
}

void RefOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "target") {
       prop.target = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.target)>>(value);
       return;
    }
}

void RefOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.target) attrs.append("target", prop.target);
}

::llvm::LogicalResult RefOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTargetAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit3(attr, "target", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RefOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.target)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RefOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.target);
}

::llvm::StringRef RefOp::getTarget() {
  auto attr = getTargetAttr();
  return attr.getValue();
}

void RefOp::setTarget(::llvm::StringRef attrValue) {
  getProperties().target = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void RefOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr target) {
  odsState.getOrAddProperties<Properties>().target = target;
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr target) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(target)>(target));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr target) {
  return create(builder, builder.getLoc(), std::forward<decltype(target)>(target));
}

void RefOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target) {
  odsState.getOrAddProperties<Properties>().target = target;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(target)>(target));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr target) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(target)>(target));
}

void RefOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef target) {
  odsState.getOrAddProperties<Properties>().target = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), target);
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef target) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(target)>(target));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef target) {
  return create(builder, builder.getLoc(), std::forward<decltype(target)>(target));
}

void RefOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef target) {
  odsState.getOrAddProperties<Properties>().target = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), target);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef target) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(target)>(target));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef target) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(target)>(target));
}

void RefOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<RefOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RefOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

RefOp RefOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RefOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefOp RefOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult RefOp::verifyInvariantsImpl() {
  auto tblgen_target = getProperties().target; (void)tblgen_target;
  if (!tblgen_target) return emitOpError("requires attribute 'target'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit3(*this, tblgen_target, "target")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult RefOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RefOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr targetAttr;

  if (parser.parseCustomAttributeWithFallback(targetAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (targetAttr) result.getOrAddProperties<RefOp::Properties>().target = targetAttr;
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

void RefOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTargetAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("target");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::emit
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::RefOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::detail::RefOpGenericAdaptorBase::Properties)

namespace circt::emit {


//===----------------------------------------------------------------------===//
// ::circt::emit::VerbatimOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

VerbatimOpGenericAdaptorBase::VerbatimOpGenericAdaptorBase(VerbatimOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef VerbatimOpGenericAdaptorBase::getText() {
  auto attr = getTextAttr();
  return attr.getValue();
}


} // namespace detail
VerbatimOpAdaptor::VerbatimOpAdaptor(VerbatimOp op) : VerbatimOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult VerbatimOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_text = getProperties().text; (void)tblgen_text;
  if (!tblgen_text) return emitError(loc, "'emit.verbatim' op requires attribute 'text'");

  if (tblgen_text && !((::llvm::isa<::mlir::StringAttr>(tblgen_text))))
    return emitError(loc, "'emit.verbatim' op attribute 'text' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult VerbatimOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.text;
       auto attr = dict.get("text");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `text` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute VerbatimOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.text;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("text",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code VerbatimOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.text.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> VerbatimOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "text")
      return prop.text;
  return std::nullopt;
}

void VerbatimOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "text") {
       prop.text = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.text)>>(value);
       return;
    }
}

void VerbatimOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.text) attrs.append("text", prop.text);
}

::llvm::LogicalResult VerbatimOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTextAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(attr, "text", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult VerbatimOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.text)))
    return ::mlir::failure();
  return ::mlir::success();
}

void VerbatimOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.text);
}

::llvm::StringRef VerbatimOp::getText() {
  auto attr = getTextAttr();
  return attr.getValue();
}

void VerbatimOp::setText(::llvm::StringRef attrValue) {
  getProperties().text = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void VerbatimOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr text) {
  odsState.getOrAddProperties<Properties>().text = text;
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr text) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(text)>(text));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr text) {
  return create(builder, builder.getLoc(), std::forward<decltype(text)>(text));
}

void VerbatimOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text) {
  odsState.getOrAddProperties<Properties>().text = text;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(text)>(text));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr text) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(text)>(text));
}

void VerbatimOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef text) {
  odsState.getOrAddProperties<Properties>().text = odsBuilder.getStringAttr(text);
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef text) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(text)>(text));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef text) {
  return create(builder, builder.getLoc(), std::forward<decltype(text)>(text));
}

void VerbatimOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef text) {
  odsState.getOrAddProperties<Properties>().text = odsBuilder.getStringAttr(text);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef text) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(text)>(text));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef text) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(text)>(text));
}

void VerbatimOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<VerbatimOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void VerbatimOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

VerbatimOp VerbatimOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<VerbatimOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VerbatimOp VerbatimOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult VerbatimOp::verifyInvariantsImpl() {
  auto tblgen_text = getProperties().text; (void)tblgen_text;
  if (!tblgen_text) return emitOpError("requires attribute 'text'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Emit1(*this, tblgen_text, "text")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult VerbatimOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult VerbatimOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr textAttr;

  if (parser.parseCustomAttributeWithFallback(textAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (textAttr) result.getOrAddProperties<VerbatimOp::Properties>().text = textAttr;
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

void VerbatimOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTextAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("text");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::emit
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::VerbatimOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::emit::detail::VerbatimOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

