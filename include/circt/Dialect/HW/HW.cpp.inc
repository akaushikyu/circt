/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HW.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::hw::AggregateConstantOp,
::circt::hw::ArrayConcatOp,
::circt::hw::ArrayCreateOp,
::circt::hw::ArrayGetOp,
::circt::hw::ArrayInjectOp,
::circt::hw::ArraySliceOp,
::circt::hw::BitcastOp,
::circt::hw::ConstantOp,
::circt::hw::EnumCmpOp,
::circt::hw::EnumConstantOp,
::circt::hw::HWGeneratorSchemaOp,
::circt::hw::HWModuleExternOp,
::circt::hw::HWModuleGeneratedOp,
::circt::hw::HWModuleOp,
::circt::hw::HierPathOp,
::circt::hw::InstanceOp,
::circt::hw::OutputOp,
::circt::hw::ParamValueOp,
::circt::hw::StructCreateOp,
::circt::hw::StructExplodeOp,
::circt::hw::StructExtractOp,
::circt::hw::StructInjectOp,
::circt::hw::TriggeredOp,
::circt::hw::TypeScopeOp,
::circt::hw::TypedeclOp,
::circt::hw::UnionCreateOp,
::circt::hw::UnionExtractOp,
::circt::hw::WireOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<
      circt::hw::ArrayType,
      circt::hw::UnpackedArrayType,
      circt::hw::StructType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an ArrayType or StructType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::ArrayType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of an ArrayType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::ArrayType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an ArrayType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((!circt::hw::hasHWInOutType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of a type without inout, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::isHWIntegerType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a signless integer bitvector, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((!circt::hw::hasHWInOutType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a type without inout, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((getBitWidth(type) != -1))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be Type wherein the bitwidth in hardware is known, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::EnumType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a EnumType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW10(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW11(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW12(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::isHWValueType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a known primitive element, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW13(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::StructType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a StructType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_HW14(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::UnionType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a UnionType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::IntegerAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: arbitrary integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::EnumFieldAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Enumeration field attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((isa<circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of a module";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of dictionary attributes";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::LocationAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: location array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::hw::ParamDeclAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: parameter array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW10(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW10(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW10(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW11(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((llvm::isa<::mlir::FlatSymbolRefAttr, ::circt::hw::InnerRefAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: name reference array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW11(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW11(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW12(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerSymAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Inner symbol definition";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW12(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW12(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW13(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW13(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW13(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW14(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((true)))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW14(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW14(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW15(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW15(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW15(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW16(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<circt::hw::EventControlAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: edge control trigger";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW16(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW16(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW17(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((true))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any type attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_HW17(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_HW17(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_HW1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_HW2(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::AggregateConstantOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AggregateConstantOpGenericAdaptorBase::AggregateConstantOpGenericAdaptorBase(AggregateConstantOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::ArrayAttr AggregateConstantOpGenericAdaptorBase::getFields() {
  auto attr = getFieldsAttr();
  return attr;
}


} // namespace detail
AggregateConstantOpAdaptor::AggregateConstantOpAdaptor(AggregateConstantOp op) : AggregateConstantOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AggregateConstantOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_fields = getProperties().fields; (void)tblgen_fields;
  if (!tblgen_fields) return emitError(loc, "'hw.aggregate_constant' op requires attribute 'fields'");

  if (tblgen_fields && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_fields))))
    return emitError(loc, "'hw.aggregate_constant' op attribute 'fields' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AggregateConstantOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.fields;
       auto attr = dict.get("fields");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fields` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AggregateConstantOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.fields;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fields",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AggregateConstantOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.fields.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AggregateConstantOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "fields")
      return prop.fields;
  return std::nullopt;
}

void AggregateConstantOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "fields") {
       prop.fields = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fields)>>(value);
       return;
    }
}

void AggregateConstantOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.fields) attrs.append("fields", prop.fields);
}

::llvm::LogicalResult AggregateConstantOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW1(attr, "fields", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AggregateConstantOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.fields)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AggregateConstantOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.fields);
}

::mlir::ArrayAttr AggregateConstantOp::getFields() {
  auto attr = getFieldsAttr();
  return attr;
}

void AggregateConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ArrayAttr fields) {
  odsState.getOrAddProperties<Properties>().fields = fields;
  odsState.addTypes(result);
}

AggregateConstantOp AggregateConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ArrayAttr fields) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(fields)>(fields));
  auto __res__ = ::llvm::dyn_cast<AggregateConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AggregateConstantOp AggregateConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ArrayAttr fields) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(fields)>(fields));
}

void AggregateConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields) {
  odsState.getOrAddProperties<Properties>().fields = fields;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AggregateConstantOp AggregateConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fields)>(fields));
  auto __res__ = ::llvm::dyn_cast<AggregateConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AggregateConstantOp AggregateConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fields)>(fields));
}

void AggregateConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AggregateConstantOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AggregateConstantOp AggregateConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AggregateConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AggregateConstantOp AggregateConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AggregateConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AggregateConstantOp AggregateConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AggregateConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AggregateConstantOp AggregateConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AggregateConstantOp::verifyInvariantsImpl() {
  auto tblgen_fields = getProperties().fields; (void)tblgen_fields;
  if (!tblgen_fields) return emitOpError("requires attribute 'fields'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW1(*this, tblgen_fields, "fields")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AggregateConstantOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult AggregateConstantOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::ArrayAttr fieldsAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  if (parser.parseCustomAttributeWithFallback(fieldsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (fieldsAttr) result.getOrAddProperties<AggregateConstantOp::Properties>().fields = fieldsAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::circt::hw::TypeVariant<
      ::circt::hw::ArrayType,
      ::circt::hw::UnpackedArrayType,
      ::circt::hw::StructType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void AggregateConstantOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getFieldsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("fields");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeVariant<
      ::circt::hw::ArrayType,
      ::circt::hw::UnpackedArrayType,
      ::circt::hw::StructType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void AggregateConstantOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::AggregateConstantOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::AggregateConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayConcatOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArrayConcatOpGenericAdaptorBase::ArrayConcatOpGenericAdaptorBase(ArrayConcatOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ArrayConcatOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
ArrayConcatOpAdaptor::ArrayConcatOpAdaptor(ArrayConcatOp op) : ArrayConcatOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArrayConcatOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ArrayConcatOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ArrayConcatOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ArrayConcatOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArrayConcatOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArrayConcatOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArrayConcatOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArrayConcatOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArrayConcatOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArrayConcatOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

ArrayConcatOp ArrayConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ArrayConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayConcatOp ArrayConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs));
}

void ArrayConcatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.addTypes(result);
}

ArrayConcatOp ArrayConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ArrayConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayConcatOp ArrayConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
}

void ArrayConcatOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayConcatOp ArrayConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayConcatOp ArrayConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayConcatOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayConcatOp ArrayConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayConcatOp ArrayConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArrayConcatOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ArrayConcatOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ArrayConcatOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult ArrayConcatOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();
  {
    auto odsResult = parseArrayConcatTypes(parser, inputsTypes, resultRawType);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ArrayConcatOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  printArrayConcatTypes(_odsPrinter, *this, getInputs().getTypes(), getResult().getType());
}

void ArrayConcatOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArrayConcatOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayCreateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArrayCreateOpGenericAdaptorBase::ArrayCreateOpGenericAdaptorBase(ArrayCreateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ArrayCreateOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
ArrayCreateOpAdaptor::ArrayCreateOpAdaptor(ArrayCreateOp op) : ArrayCreateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArrayCreateOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ArrayCreateOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ArrayCreateOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ArrayCreateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArrayCreateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArrayCreateOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArrayCreateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArrayCreateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArrayCreateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArrayCreateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

ArrayCreateOp ArrayCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ArrayCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayCreateOp ArrayCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ValueRange input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void ArrayCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.addTypes(result);
}

ArrayCreateOp ArrayCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ArrayCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayCreateOp ArrayCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
}

void ArrayCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayCreateOp ArrayCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayCreateOp ArrayCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayCreateOp ArrayCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayCreateOp ArrayCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArrayCreateOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ArrayCreateOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void ArrayCreateOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ArrayCreateOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void ArrayCreateOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArrayCreateOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayGetOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArrayGetOpGenericAdaptorBase::ArrayGetOpGenericAdaptorBase(ArrayGetOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ArrayGetOpAdaptor::ArrayGetOpAdaptor(ArrayGetOp op) : ArrayGetOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArrayGetOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ArrayGetOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArrayGetOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArrayGetOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArrayGetOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArrayGetOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArrayGetOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArrayGetOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ArrayGetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index) {
  odsState.addOperands(input);
  odsState.addOperands(index);
  odsState.addTypes(result);
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
}

void ArrayGetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index) {
  odsState.addOperands(input);
  odsState.addOperands(index);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ArrayGetOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
}

void ArrayGetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index) {
  odsState.addOperands(input);
  odsState.addOperands(index);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index));
}

void ArrayGetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayGetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayGetOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayGetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ArrayGetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayGetOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ArrayGetOp ArrayGetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayGetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayGetOp ArrayGetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArrayGetOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(type_cast<ArrayType>((*this->getODSOperands(0).begin()).getType()).getElementType(), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that must match array element type");
  if (!((isValidIndexBitWidth((*this->getODSOperands(1).begin()), (*this->getODSOperands(0).begin())))))
    return emitOpError("failed to verify that index bit width equals ceil(log2(length(input))), or 0 or 1 if input contains only one element");
  return ::mlir::success();
}

::llvm::LogicalResult ArrayGetOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ArrayGetOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ArrayGetOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = type_cast<ArrayType>(operands[0].getType()).getElementType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ArrayGetOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand indexRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> indexOperands(&indexRawOperand, 1);  ::llvm::SMLoc indexOperandsLoc;
  (void)indexOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type indexRawType{};
  ::llvm::ArrayRef<::mlir::Type> indexTypes(&indexRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  indexOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(indexRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::circt::hw::TypeAliasOr<circt::hw::ArrayType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    indexRawType = type;
  }
  for (::mlir::Type type : inputTypes) {
    (void)type;
    if (!((::circt::hw::type_isa<circt::hw::ArrayType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'input' must be an ArrayType, but got " << type;
    }
  }
  result.addTypes(type_cast<ArrayType>(inputTypes[0]).getElementType());
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(indexOperands, indexTypes, indexOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ArrayGetOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << "[";
  _odsPrinter << getIndex();
  _odsPrinter << "]";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getIndex().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ArrayGetOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArrayGetOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayInjectOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArrayInjectOpGenericAdaptorBase::ArrayInjectOpGenericAdaptorBase(ArrayInjectOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ArrayInjectOpAdaptor::ArrayInjectOpAdaptor(ArrayInjectOp op) : ArrayInjectOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArrayInjectOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ArrayInjectOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArrayInjectOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArrayInjectOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArrayInjectOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArrayInjectOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArrayInjectOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArrayInjectOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ArrayInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  odsState.addOperands(input);
  odsState.addOperands(index);
  odsState.addOperands(element);
  odsState.addTypes(result);
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
}

void ArrayInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  odsState.addOperands(input);
  odsState.addOperands(index);
  odsState.addOperands(element);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ArrayInjectOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
}

void ArrayInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  odsState.addOperands(input);
  odsState.addOperands(index);
  odsState.addOperands(element);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(index)>(index), std::forward<decltype(element)>(element));
}

void ArrayInjectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayInjectOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayInjectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ArrayInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayInjectOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

ArrayInjectOp ArrayInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayInjectOp ArrayInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArrayInjectOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, result} have same type");
  if (!((std::equal_to<>()(type_cast<ArrayType>((*this->getODSOperands(0).begin()).getType()).getElementType(), (*this->getODSOperands(2).begin()).getType()))))
    return emitOpError("failed to verify that must match array element type");
  if (!((isValidIndexBitWidth((*this->getODSOperands(1).begin()), (*this->getODSOperands(0).begin())))))
    return emitOpError("failed to verify that index bit width equals ceil(log2(length(input))), or 0 or 1 if input contains only one element");
  return ::mlir::success();
}

::llvm::LogicalResult ArrayInjectOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ArrayInjectOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ArrayInjectOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand indexRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> indexOperands(&indexRawOperand, 1);  ::llvm::SMLoc indexOperandsLoc;
  (void)indexOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand elementRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> elementOperands(&elementRawOperand, 1);  ::llvm::SMLoc elementOperandsLoc;
  (void)elementOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type indexRawType{};
  ::llvm::ArrayRef<::mlir::Type> indexTypes(&indexRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  indexOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(indexRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  elementOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(elementRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::circt::hw::TypeAliasOr<circt::hw::ArrayType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    indexRawType = type;
  }
  for (::mlir::Type type : inputTypes) {
    (void)type;
    if (!((::circt::hw::type_isa<circt::hw::ArrayType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'input' must be an ArrayType, but got " << type;
    }
  }
  result.addTypes(inputTypes[0]);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(indexOperands, indexTypes, indexOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(elementOperands, type_cast<ArrayType>(inputTypes[0]).getElementType(), elementOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ArrayInjectOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << "[";
  _odsPrinter << getIndex();
  _odsPrinter << "]";
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getElement();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getIndex().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ArrayInjectOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArrayInjectOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArraySliceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArraySliceOpGenericAdaptorBase::ArraySliceOpGenericAdaptorBase(ArraySliceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ArraySliceOpAdaptor::ArraySliceOpAdaptor(ArraySliceOp op) : ArraySliceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArraySliceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ArraySliceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArraySliceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArraySliceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArraySliceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArraySliceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArraySliceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArraySliceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ArraySliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex) {
  odsState.addOperands(input);
  odsState.addOperands(lowIndex);
  odsState.addTypes(dst);
}

ArraySliceOp ArraySliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dst)>(dst), std::forward<decltype(input)>(input), std::forward<decltype(lowIndex)>(lowIndex));
  auto __res__ = ::llvm::dyn_cast<ArraySliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArraySliceOp ArraySliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(dst)>(dst), std::forward<decltype(input)>(input), std::forward<decltype(lowIndex)>(lowIndex));
}

void ArraySliceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex) {
  odsState.addOperands(input);
  odsState.addOperands(lowIndex);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ArraySliceOp ArraySliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowIndex)>(lowIndex));
  auto __res__ = ::llvm::dyn_cast<ArraySliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArraySliceOp ArraySliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowIndex)>(lowIndex));
}

void ArraySliceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArraySliceOp ArraySliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArraySliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArraySliceOp ArraySliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArraySliceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArraySliceOp ArraySliceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArraySliceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArraySliceOp ArraySliceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArraySliceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ArraySliceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void ArraySliceOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult ArraySliceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand lowIndexRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lowIndexOperands(&lowIndexRawOperand, 1);  ::llvm::SMLoc lowIndexOperandsLoc;
  (void)lowIndexOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type lowIndexRawType{};
  ::llvm::ArrayRef<::mlir::Type> lowIndexTypes(&lowIndexRawType, 1);
  ::mlir::Type dstRawType{};
  ::llvm::ArrayRef<::mlir::Type> dstTypes(&dstRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  lowIndexOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lowIndexRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();
  if (parser.parseLParen())
    return ::mlir::failure();
  {
    auto odsResult = parseSliceTypes(parser, inputRawType, lowIndexRawType);
    if (odsResult) return ::mlir::failure();
  }
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseType(dstRawType))
    return ::mlir::failure();
  result.addTypes(dstTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(lowIndexOperands, lowIndexTypes, lowIndexOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ArraySliceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << "[";
  _odsPrinter << getLowIndex();
  _odsPrinter << "]";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ' << "(";
  printSliceTypes(_odsPrinter, *this, getInput().getType(), getLowIndex().getType());
  _odsPrinter << ")";
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
   _odsPrinter << getDst().getType();
}

void ArraySliceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArraySliceOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::BitcastOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

BitcastOpGenericAdaptorBase::BitcastOpGenericAdaptorBase(BitcastOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
BitcastOpAdaptor::BitcastOpAdaptor(BitcastOp op) : BitcastOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BitcastOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult BitcastOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BitcastOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BitcastOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BitcastOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BitcastOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BitcastOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BitcastOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BitcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

BitcastOp BitcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<BitcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BitcastOp BitcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void BitcastOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BitcastOp BitcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<BitcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BitcastOp BitcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void BitcastOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BitcastOp BitcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BitcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BitcastOp BitcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BitcastOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BitcastOp BitcastOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BitcastOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BitcastOp BitcastOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BitcastOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BitcastOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void BitcastOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult BitcastOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> inputTypes;
  ::llvm::ArrayRef<::mlir::Type> resultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType input__result_functionType;
  if (parser.parseType(input__result_functionType))
    return ::mlir::failure();
  inputTypes = input__result_functionType.getInputs();
  resultTypes = input__result_functionType.getResults();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BitcastOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(::llvm::ArrayRef<::mlir::Type>(getInput().getType()), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void BitcastOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::BitcastOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ConstantOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConstantOpGenericAdaptorBase::ConstantOpGenericAdaptorBase(ConstantOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::APInt ConstantOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}


} // namespace detail
ConstantOpAdaptor::ConstantOpAdaptor(ConstantOp op) : ConstantOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConstantOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'hw.constant' op requires attribute 'value'");

  if (tblgen_value && !((::llvm::isa<::mlir::IntegerAttr>(tblgen_value))))
    return emitError(loc, "'hw.constant' op attribute 'value' failed to satisfy constraint: arbitrary integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.value;
       auto attr = dict.get("value");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ConstantOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.value;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("value",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConstantOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ConstantOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ConstantOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ConstantOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ConstantOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW2(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ConstantOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.value);
}

::mlir::APInt ConstantOp::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, const APInt &value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, const APInt &value) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value));
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type type, int64_t value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(type)>(type), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, Type type, int64_t value) {
  return create(builder, builder.getLoc(), std::forward<decltype(type)>(type), std::forward<decltype(value)>(value));
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, IntegerAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, IntegerAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  odsState.addTypes(result);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ConstantOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::Attribute typeAttr;
  auto attrName = getValueAttrName(odsState.name);
  for (auto attr : attributes) {
    if (attr.getName() == attrName) {
      typeAttr = attr.getValue();
      break;
    }
  }
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
    odsState.addTypes({::llvm::cast<::mlir::TypedAttr>(typeAttr).getType()});
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::Attribute typeAttr = properties.getValue();
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
    odsState.addTypes({::llvm::cast<::mlir::TypedAttr>(typeAttr).getType()});
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConstantOp::verifyInvariantsImpl() {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW2(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ConstantOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.value;
    auto valueAttrName = ::mlir::StringAttr::get(ctx, "value");
    auto attr = dict.get(valueAttrName);
    usedKeys.insert(valueAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for value in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void ConstantOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ConstantOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::ConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::EnumCmpOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EnumCmpOpGenericAdaptorBase::EnumCmpOpGenericAdaptorBase(EnumCmpOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
EnumCmpOpAdaptor::EnumCmpOpAdaptor(EnumCmpOp op) : EnumCmpOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EnumCmpOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult EnumCmpOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute EnumCmpOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EnumCmpOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> EnumCmpOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void EnumCmpOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void EnumCmpOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult EnumCmpOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void EnumCmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addTypes(result);
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

void EnumCmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(EnumCmpOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

void EnumCmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

void EnumCmpOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnumCmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(EnumCmpOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnumCmpOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void EnumCmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(EnumCmpOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

EnumCmpOp EnumCmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnumCmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumCmpOp EnumCmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EnumCmpOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW10(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult EnumCmpOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult EnumCmpOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult EnumCmpOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type lhsRawType{};
  ::llvm::ArrayRef<::mlir::Type> lhsTypes(&lhsRawType, 1);
  ::mlir::Type rhsRawType{};
  ::llvm::ArrayRef<::mlir::Type> rhsTypes(&rhsRawType, 1);

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(lhsRawType))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseType(rhsRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(lhsOperands, lhsTypes, lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, rhsTypes, rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnumCmpOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getLhs().getType();
  _odsPrinter << ",";
  _odsPrinter << ' ';
   _odsPrinter << getRhs().getType();
}

void EnumCmpOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::EnumCmpOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::EnumConstantOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EnumConstantOpGenericAdaptorBase::EnumConstantOpGenericAdaptorBase(EnumConstantOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::EnumFieldAttr EnumConstantOpGenericAdaptorBase::getField() {
  auto attr = getFieldAttr();
  return ::llvm::cast<::circt::hw::EnumFieldAttr>(attr);
}


} // namespace detail
EnumConstantOpAdaptor::EnumConstantOpAdaptor(EnumConstantOp op) : EnumConstantOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EnumConstantOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_field = getProperties().field; (void)tblgen_field;
  if (!tblgen_field) return emitError(loc, "'hw.enum.constant' op requires attribute 'field'");

  if (tblgen_field && !((::llvm::isa<::circt::hw::EnumFieldAttr>(tblgen_field))))
    return emitError(loc, "'hw.enum.constant' op attribute 'field' failed to satisfy constraint: Enumeration field attribute");
  return ::mlir::success();
}

::llvm::LogicalResult EnumConstantOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.field;
       auto attr = dict.get("field");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `field` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute EnumConstantOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.field;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("field",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EnumConstantOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.field.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> EnumConstantOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "field")
      return prop.field;
  return std::nullopt;
}

void EnumConstantOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "field") {
       prop.field = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.field)>>(value);
       return;
    }
}

void EnumConstantOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.field) attrs.append("field", prop.field);
}

::llvm::LogicalResult EnumConstantOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW3(attr, "field", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult EnumConstantOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.field)))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnumConstantOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.field);
}

::circt::hw::EnumFieldAttr EnumConstantOp::getField() {
  auto attr = getFieldAttr();
  return ::llvm::cast<::circt::hw::EnumFieldAttr>(attr);
}

EnumConstantOp EnumConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::EnumFieldAttr field) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(field)>(field));
  auto __res__ = ::llvm::dyn_cast<EnumConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumConstantOp EnumConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, hw::EnumFieldAttr field) {
  return create(builder, builder.getLoc(), std::forward<decltype(field)>(field));
}

void EnumConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::hw::EnumFieldAttr field) {
  odsState.getOrAddProperties<Properties>().field = field;
  odsState.addTypes(result);
}

EnumConstantOp EnumConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::hw::EnumFieldAttr field) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(field)>(field));
  auto __res__ = ::llvm::dyn_cast<EnumConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumConstantOp EnumConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::hw::EnumFieldAttr field) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(field)>(field));
}

void EnumConstantOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field) {
  odsState.getOrAddProperties<Properties>().field = field;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnumConstantOp EnumConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(field)>(field));
  auto __res__ = ::llvm::dyn_cast<EnumConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumConstantOp EnumConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(field)>(field));
}

void EnumConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<EnumConstantOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

EnumConstantOp EnumConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnumConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumConstantOp EnumConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnumConstantOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnumConstantOp EnumConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnumConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumConstantOp EnumConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EnumConstantOp::verifyInvariantsImpl() {
  auto tblgen_field = getProperties().field; (void)tblgen_field;
  if (!tblgen_field) return emitOpError("requires attribute 'field'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW3(*this, tblgen_field, "field")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW9(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult EnumConstantOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult EnumConstantOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.field;
    auto fieldAttrName = ::mlir::StringAttr::get(ctx, "field");
    auto attr = dict.get(fieldAttrName);
    usedKeys.insert(fieldAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for field in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `field` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void EnumConstantOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::EnumConstantOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::EnumConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWGeneratorSchemaOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HWGeneratorSchemaOpGenericAdaptorBase::HWGeneratorSchemaOpGenericAdaptorBase(HWGeneratorSchemaOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HWGeneratorSchemaOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef HWGeneratorSchemaOpGenericAdaptorBase::getDescriptor() {
  auto attr = getDescriptorAttr();
  return attr.getValue();
}

::mlir::ArrayAttr HWGeneratorSchemaOpGenericAdaptorBase::getRequiredAttrs() {
  auto attr = getRequiredAttrsAttr();
  return attr;
}


} // namespace detail
HWGeneratorSchemaOpAdaptor::HWGeneratorSchemaOpAdaptor(HWGeneratorSchemaOp op) : HWGeneratorSchemaOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HWGeneratorSchemaOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_descriptor = getProperties().descriptor; (void)tblgen_descriptor;
  if (!tblgen_descriptor) return emitError(loc, "'hw.generator.schema' op requires attribute 'descriptor'");
  auto tblgen_requiredAttrs = getProperties().requiredAttrs; (void)tblgen_requiredAttrs;
  if (!tblgen_requiredAttrs) return emitError(loc, "'hw.generator.schema' op requires attribute 'requiredAttrs'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.generator.schema' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.generator.schema' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_descriptor && !((::llvm::isa<::mlir::StringAttr>(tblgen_descriptor))))
    return emitError(loc, "'hw.generator.schema' op attribute 'descriptor' failed to satisfy constraint: string attribute");

  if (tblgen_requiredAttrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_requiredAttrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_requiredAttrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'hw.generator.schema' op attribute 'requiredAttrs' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HWGeneratorSchemaOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.descriptor;
       auto attr = dict.get("descriptor");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `descriptor` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.requiredAttrs;
       auto attr = dict.get("requiredAttrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `requiredAttrs` in property conversion: " << attr;
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

::mlir::Attribute HWGeneratorSchemaOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.descriptor;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("descriptor",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.requiredAttrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("requiredAttrs",
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

llvm::hash_code HWGeneratorSchemaOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.descriptor.getAsOpaquePointer()), 
    llvm::hash_value(prop.requiredAttrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HWGeneratorSchemaOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "descriptor")
      return prop.descriptor;

    if (name == "requiredAttrs")
      return prop.requiredAttrs;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void HWGeneratorSchemaOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "descriptor") {
       prop.descriptor = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.descriptor)>>(value);
       return;
    }

    if (name == "requiredAttrs") {
       prop.requiredAttrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.requiredAttrs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void HWGeneratorSchemaOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.descriptor) attrs.append("descriptor", prop.descriptor);

    if (prop.requiredAttrs) attrs.append("requiredAttrs", prop.requiredAttrs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult HWGeneratorSchemaOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDescriptorAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "descriptor", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRequiredAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW5(attr, "requiredAttrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HWGeneratorSchemaOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.descriptor)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.requiredAttrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HWGeneratorSchemaOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.descriptor);
  writer.writeAttribute(prop.requiredAttrs);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef HWGeneratorSchemaOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef HWGeneratorSchemaOp::getDescriptor() {
  auto attr = getDescriptorAttr();
  return attr.getValue();
}

::mlir::ArrayAttr HWGeneratorSchemaOp::getRequiredAttrs() {
  auto attr = getRequiredAttrsAttr();
  return attr;
}

void HWGeneratorSchemaOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HWGeneratorSchemaOp::setDescriptor(::llvm::StringRef attrValue) {
  getProperties().descriptor = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().descriptor = descriptor;
  odsState.getOrAddProperties<Properties>().requiredAttrs = requiredAttrs;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().descriptor = descriptor;
  odsState.getOrAddProperties<Properties>().requiredAttrs = requiredAttrs;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().descriptor = odsBuilder.getStringAttr(descriptor);
  odsState.getOrAddProperties<Properties>().requiredAttrs = requiredAttrs;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().descriptor = odsBuilder.getStringAttr(descriptor);
  odsState.getOrAddProperties<Properties>().requiredAttrs = requiredAttrs;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(descriptor)>(descriptor), std::forward<decltype(requiredAttrs)>(requiredAttrs));
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HWGeneratorSchemaOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HWGeneratorSchemaOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HWGeneratorSchemaOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWGeneratorSchemaOp HWGeneratorSchemaOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult HWGeneratorSchemaOp::verifyInvariantsImpl() {
  auto tblgen_descriptor = getProperties().descriptor; (void)tblgen_descriptor;
  if (!tblgen_descriptor) return emitOpError("requires attribute 'descriptor'");
  auto tblgen_requiredAttrs = getProperties().requiredAttrs; (void)tblgen_requiredAttrs;
  if (!tblgen_requiredAttrs) return emitOpError("requires attribute 'requiredAttrs'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_descriptor, "descriptor")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW5(*this, tblgen_requiredAttrs, "requiredAttrs")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult HWGeneratorSchemaOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult HWGeneratorSchemaOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::StringAttr descriptorAttr;
  ::mlir::ArrayAttr requiredAttrsAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<HWGeneratorSchemaOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(descriptorAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (descriptorAttr) result.getOrAddProperties<HWGeneratorSchemaOp::Properties>().descriptor = descriptorAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(requiredAttrsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (requiredAttrsAttr) result.getOrAddProperties<HWGeneratorSchemaOp::Properties>().requiredAttrs = requiredAttrsAttr;
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

void HWGeneratorSchemaOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getDescriptorAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getRequiredAttrsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("descriptor");
  elidedAttrs.push_back("requiredAttrs");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::HWGeneratorSchemaOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWGeneratorSchemaOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleExternOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HWModuleExternOpGenericAdaptorBase::HWModuleExternOpGenericAdaptorBase(HWModuleExternOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HWModuleExternOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleExternOpGenericAdaptorBase::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleExternOpGenericAdaptorBase::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleExternOpGenericAdaptorBase::getPortLocs() {
  auto attr = getPortLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleExternOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleExternOpGenericAdaptorBase::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
HWModuleExternOpAdaptor::HWModuleExternOpAdaptor(HWModuleExternOp op) : HWModuleExternOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HWModuleExternOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitError(loc, "'hw.module.extern' op requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'hw.module.extern' op requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_port_locs = getProperties().port_locs; (void)tblgen_port_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.module.extern' op requires attribute 'sym_name'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.module.extern' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_module_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_module_type))) && ((::llvm::isa<::circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue()))) && ((isa<circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue())))))
    return emitError(loc, "'hw.module.extern' op attribute 'module_type' failed to satisfy constraint: type attribute of a module");

  if (tblgen_per_port_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_per_port_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_per_port_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'hw.module.extern' op attribute 'per_port_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_port_locs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_port_locs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_port_locs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::LocationAttr>(attr))); }))))
    return emitError(loc, "'hw.module.extern' op attribute 'port_locs' failed to satisfy constraint: location array attribute");

  if (tblgen_parameters && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_parameters))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_parameters), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::hw::ParamDeclAttr>(attr))); }))))
    return emitError(loc, "'hw.module.extern' op attribute 'parameters' failed to satisfy constraint: parameter array attribute");

  if (tblgen_verilogName && !((::llvm::isa<::mlir::StringAttr>(tblgen_verilogName))))
    return emitError(loc, "'hw.module.extern' op attribute 'verilogName' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleExternOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.module_type;
       auto attr = dict.get("module_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.per_port_attrs;
       auto attr = dict.get("per_port_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.port_locs;
       auto attr = dict.get("port_locs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `port_locs` in property conversion: " << attr;
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

  {
    auto &propStorage = prop.verilogName;
       auto attr = dict.get("verilogName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `verilogName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute HWModuleExternOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.module_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("module_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.per_port_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("per_port_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.port_locs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("port_locs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.verilogName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("verilogName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code HWModuleExternOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.module_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.per_port_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.port_locs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.verilogName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HWModuleExternOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "module_type")
      return prop.module_type;

    if (name == "parameters")
      return prop.parameters;

    if (name == "per_port_attrs")
      return prop.per_port_attrs;

    if (name == "port_locs")
      return prop.port_locs;

    if (name == "sym_name")
      return prop.sym_name;

    if (name == "verilogName")
      return prop.verilogName;
  return std::nullopt;
}

void HWModuleExternOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "module_type") {
       prop.module_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.module_type)>>(value);
       return;
    }

    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "per_port_attrs") {
       prop.per_port_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.per_port_attrs)>>(value);
       return;
    }

    if (name == "port_locs") {
       prop.port_locs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.port_locs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "verilogName") {
       prop.verilogName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.verilogName)>>(value);
       return;
    }
}

void HWModuleExternOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.module_type) attrs.append("module_type", prop.module_type);

    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.per_port_attrs) attrs.append("per_port_attrs", prop.per_port_attrs);

    if (prop.port_locs) attrs.append("port_locs", prop.port_locs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.verilogName) attrs.append("verilogName", prop.verilogName);
}

::llvm::LogicalResult HWModuleExternOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getModuleTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW6(attr, "module_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW9(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPerPortAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW7(attr, "per_port_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortLocsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW8(attr, "port_locs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getVerilogNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "verilogName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HWModuleExternOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.module_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.per_port_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.port_locs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.verilogName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HWModuleExternOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.module_type);
  writer.writeAttribute(prop.parameters);

  writer.writeOptionalAttribute(prop.per_port_attrs);

  writer.writeOptionalAttribute(prop.port_locs);
  writer.writeAttribute(prop.sym_name);

  writer.writeOptionalAttribute(prop.verilogName);
}

::llvm::StringRef HWModuleExternOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleExternOp::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleExternOp::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleExternOp::getPortLocs() {
  auto attr = getPortLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleExternOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleExternOp::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void HWModuleExternOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HWModuleExternOp::setModuleType(::circt::hw::ModuleType attrValue) {
  getProperties().module_type = ::mlir::TypeAttr::get(attrValue);
}

void HWModuleExternOp::setVerilogName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().verilogName;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

HWModuleExternOp HWModuleExternOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HWModuleExternOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleExternOp HWModuleExternOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
}

HWModuleExternOp HWModuleExternOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HWModuleExternOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleExternOp HWModuleExternOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
}

::llvm::LogicalResult HWModuleExternOp::verifyInvariantsImpl() {
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitOpError("requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_port_locs = getProperties().port_locs; (void)tblgen_port_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW6(*this, tblgen_module_type, "module_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW7(*this, tblgen_per_port_attrs, "per_port_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW8(*this, tblgen_port_locs, "port_locs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW9(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_verilogName, "verilogName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_HW1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleExternOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult HWModuleExternOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.sym_name;
    auto sym_nameAttrName = ::mlir::StringAttr::get(ctx, "sym_name");
    auto attr = dict.get(sym_nameAttrName);
    usedKeys.insert(sym_nameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.module_type;
    auto module_typeAttrName = ::mlir::StringAttr::get(ctx, "module_type");
    auto attr = dict.get(module_typeAttrName);
    usedKeys.insert(module_typeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for module_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.per_port_attrs;
    auto per_port_attrsAttrName = ::mlir::StringAttr::get(ctx, "per_port_attrs");
    auto attr = dict.get(per_port_attrsAttrName);
    usedKeys.insert(per_port_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for per_port_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.port_locs;
    auto port_locsAttrName = ::mlir::StringAttr::get(ctx, "port_locs");
    auto attr = dict.get(port_locsAttrName);
    usedKeys.insert(port_locsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for port_locs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `port_locs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.parameters;
    auto parametersAttrName = ::mlir::StringAttr::get(ctx, "parameters");
    auto attr = dict.get(parametersAttrName);
    usedKeys.insert(parametersAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for parameters in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.verilogName;
    auto verilogNameAttrName = ::mlir::StringAttr::get(ctx, "verilogName");
    auto attr = dict.get(verilogNameAttrName);
    usedKeys.insert(verilogNameAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for verilogName in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `verilogName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

ModuleType HWModuleExternOp::getHWModuleType() {
  return getModuleType();
}

void HWModuleExternOp::setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym) {
  auto portSymAttr = StringAttr::get(getContext(), getPortSymbolAttrName());
  setPortAttr(portIndex, portSymAttr, sym);
}

size_t HWModuleExternOp::getNumPorts() {
  auto modty = getHWModuleType();
  return modty.getNumPorts();
}

size_t HWModuleExternOp::getNumInputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumInputs();
}

size_t HWModuleExternOp::getNumOutputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumOutputs();
}

size_t HWModuleExternOp::getPortIdForInputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForInputId(idx);
}

size_t HWModuleExternOp::getPortIdForOutputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForOutputId(idx);
}

SmallVector<::circt::hw::PortInfo> HWModuleExternOp::getPortList() {
  return ::getPortList(*this);
}

::circt::hw::PortInfo HWModuleExternOp::getPort(size_t idx) {
  return ::getPort(*this, idx);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleExternOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleExternOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleGeneratedOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HWModuleGeneratedOpGenericAdaptorBase::HWModuleGeneratedOpGenericAdaptorBase(HWModuleGeneratedOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HWModuleGeneratedOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef HWModuleGeneratedOpGenericAdaptorBase::getGeneratorKind() {
  auto attr = getGeneratorKindAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleGeneratedOpGenericAdaptorBase::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleGeneratedOpGenericAdaptorBase::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleGeneratedOpGenericAdaptorBase::getPortLocs() {
  auto attr = getPortLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleGeneratedOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleGeneratedOpGenericAdaptorBase::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
HWModuleGeneratedOpAdaptor::HWModuleGeneratedOpAdaptor(HWModuleGeneratedOp op) : HWModuleGeneratedOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HWModuleGeneratedOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_generatorKind = getProperties().generatorKind; (void)tblgen_generatorKind;
  if (!tblgen_generatorKind) return emitError(loc, "'hw.module.generated' op requires attribute 'generatorKind'");
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitError(loc, "'hw.module.generated' op requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'hw.module.generated' op requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_port_locs = getProperties().port_locs; (void)tblgen_port_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.module.generated' op requires attribute 'sym_name'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.module.generated' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_generatorKind && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_generatorKind))))
    return emitError(loc, "'hw.module.generated' op attribute 'generatorKind' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_module_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_module_type))) && ((::llvm::isa<::circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue()))) && ((isa<circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue())))))
    return emitError(loc, "'hw.module.generated' op attribute 'module_type' failed to satisfy constraint: type attribute of a module");

  if (tblgen_per_port_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_per_port_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_per_port_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'hw.module.generated' op attribute 'per_port_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_port_locs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_port_locs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_port_locs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::LocationAttr>(attr))); }))))
    return emitError(loc, "'hw.module.generated' op attribute 'port_locs' failed to satisfy constraint: location array attribute");

  if (tblgen_parameters && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_parameters))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_parameters), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::hw::ParamDeclAttr>(attr))); }))))
    return emitError(loc, "'hw.module.generated' op attribute 'parameters' failed to satisfy constraint: parameter array attribute");

  if (tblgen_verilogName && !((::llvm::isa<::mlir::StringAttr>(tblgen_verilogName))))
    return emitError(loc, "'hw.module.generated' op attribute 'verilogName' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleGeneratedOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.generatorKind;
       auto attr = dict.get("generatorKind");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `generatorKind` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.module_type;
       auto attr = dict.get("module_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.per_port_attrs;
       auto attr = dict.get("per_port_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.port_locs;
       auto attr = dict.get("port_locs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `port_locs` in property conversion: " << attr;
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

  {
    auto &propStorage = prop.verilogName;
       auto attr = dict.get("verilogName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `verilogName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute HWModuleGeneratedOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.generatorKind;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("generatorKind",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.module_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("module_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.per_port_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("per_port_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.port_locs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("port_locs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.verilogName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("verilogName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code HWModuleGeneratedOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.generatorKind.getAsOpaquePointer()), 
    llvm::hash_value(prop.module_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.per_port_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.port_locs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.verilogName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HWModuleGeneratedOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "generatorKind")
      return prop.generatorKind;

    if (name == "module_type")
      return prop.module_type;

    if (name == "parameters")
      return prop.parameters;

    if (name == "per_port_attrs")
      return prop.per_port_attrs;

    if (name == "port_locs")
      return prop.port_locs;

    if (name == "sym_name")
      return prop.sym_name;

    if (name == "verilogName")
      return prop.verilogName;
  return std::nullopt;
}

void HWModuleGeneratedOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "generatorKind") {
       prop.generatorKind = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.generatorKind)>>(value);
       return;
    }

    if (name == "module_type") {
       prop.module_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.module_type)>>(value);
       return;
    }

    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "per_port_attrs") {
       prop.per_port_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.per_port_attrs)>>(value);
       return;
    }

    if (name == "port_locs") {
       prop.port_locs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.port_locs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "verilogName") {
       prop.verilogName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.verilogName)>>(value);
       return;
    }
}

void HWModuleGeneratedOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.generatorKind) attrs.append("generatorKind", prop.generatorKind);

    if (prop.module_type) attrs.append("module_type", prop.module_type);

    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.per_port_attrs) attrs.append("per_port_attrs", prop.per_port_attrs);

    if (prop.port_locs) attrs.append("port_locs", prop.port_locs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.verilogName) attrs.append("verilogName", prop.verilogName);
}

::llvm::LogicalResult HWModuleGeneratedOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGeneratorKindAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW10(attr, "generatorKind", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW6(attr, "module_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW9(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPerPortAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW7(attr, "per_port_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortLocsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW8(attr, "port_locs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getVerilogNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "verilogName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HWModuleGeneratedOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.generatorKind)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.module_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.per_port_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.port_locs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.verilogName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HWModuleGeneratedOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.generatorKind);
  writer.writeAttribute(prop.module_type);
  writer.writeAttribute(prop.parameters);

  writer.writeOptionalAttribute(prop.per_port_attrs);

  writer.writeOptionalAttribute(prop.port_locs);
  writer.writeAttribute(prop.sym_name);

  writer.writeOptionalAttribute(prop.verilogName);
}

::llvm::StringRef HWModuleGeneratedOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef HWModuleGeneratedOp::getGeneratorKind() {
  auto attr = getGeneratorKindAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleGeneratedOp::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleGeneratedOp::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleGeneratedOp::getPortLocs() {
  auto attr = getPortLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleGeneratedOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleGeneratedOp::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void HWModuleGeneratedOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HWModuleGeneratedOp::setGeneratorKind(::llvm::StringRef attrValue) {
  getProperties().generatorKind = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void HWModuleGeneratedOp::setModuleType(::circt::hw::ModuleType attrValue) {
  getProperties().module_type = ::mlir::TypeAttr::get(attrValue);
}

void HWModuleGeneratedOp::setVerilogName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().verilogName;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

HWModuleGeneratedOp HWModuleGeneratedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr genKind, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(genKind)>(genKind), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HWModuleGeneratedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleGeneratedOp HWModuleGeneratedOp::create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr genKind, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(genKind)>(genKind), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
}

HWModuleGeneratedOp HWModuleGeneratedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr genKind, StringAttr name, const ModulePortInfo &ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(genKind)>(genKind), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HWModuleGeneratedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleGeneratedOp HWModuleGeneratedOp::create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr genKind, StringAttr name, const ModulePortInfo &ports, StringRef verilogName, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(genKind)>(genKind), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(verilogName)>(verilogName), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes));
}

::llvm::LogicalResult HWModuleGeneratedOp::verifyInvariantsImpl() {
  auto tblgen_generatorKind = getProperties().generatorKind; (void)tblgen_generatorKind;
  if (!tblgen_generatorKind) return emitOpError("requires attribute 'generatorKind'");
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitOpError("requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_port_locs = getProperties().port_locs; (void)tblgen_port_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW10(*this, tblgen_generatorKind, "generatorKind")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW6(*this, tblgen_module_type, "module_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW7(*this, tblgen_per_port_attrs, "per_port_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW8(*this, tblgen_port_locs, "port_locs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW9(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_verilogName, "verilogName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_HW1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleGeneratedOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult HWModuleGeneratedOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.sym_name;
    auto sym_nameAttrName = ::mlir::StringAttr::get(ctx, "sym_name");
    auto attr = dict.get(sym_nameAttrName);
    usedKeys.insert(sym_nameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.generatorKind;
    auto generatorKindAttrName = ::mlir::StringAttr::get(ctx, "generatorKind");
    auto attr = dict.get(generatorKindAttrName);
    usedKeys.insert(generatorKindAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for generatorKind in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `generatorKind` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.module_type;
    auto module_typeAttrName = ::mlir::StringAttr::get(ctx, "module_type");
    auto attr = dict.get(module_typeAttrName);
    usedKeys.insert(module_typeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for module_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.per_port_attrs;
    auto per_port_attrsAttrName = ::mlir::StringAttr::get(ctx, "per_port_attrs");
    auto attr = dict.get(per_port_attrsAttrName);
    usedKeys.insert(per_port_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for per_port_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.port_locs;
    auto port_locsAttrName = ::mlir::StringAttr::get(ctx, "port_locs");
    auto attr = dict.get(port_locsAttrName);
    usedKeys.insert(port_locsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for port_locs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `port_locs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.parameters;
    auto parametersAttrName = ::mlir::StringAttr::get(ctx, "parameters");
    auto attr = dict.get(parametersAttrName);
    usedKeys.insert(parametersAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for parameters in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.verilogName;
    auto verilogNameAttrName = ::mlir::StringAttr::get(ctx, "verilogName");
    auto attr = dict.get(verilogNameAttrName);
    usedKeys.insert(verilogNameAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for verilogName in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `verilogName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

ModuleType HWModuleGeneratedOp::getHWModuleType() {
  return getModuleType();
}

void HWModuleGeneratedOp::setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym) {
  auto portSymAttr = StringAttr::get(getContext(), getPortSymbolAttrName());
  setPortAttr(portIndex, portSymAttr, sym);
}

size_t HWModuleGeneratedOp::getNumPorts() {
  auto modty = getHWModuleType();
  return modty.getNumPorts();
}

size_t HWModuleGeneratedOp::getNumInputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumInputs();
}

size_t HWModuleGeneratedOp::getNumOutputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumOutputs();
}

size_t HWModuleGeneratedOp::getPortIdForInputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForInputId(idx);
}

size_t HWModuleGeneratedOp::getPortIdForOutputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForOutputId(idx);
}

SmallVector<::circt::hw::PortInfo> HWModuleGeneratedOp::getPortList() {
  return ::getPortList(*this);
}

::circt::hw::PortInfo HWModuleGeneratedOp::getPort(size_t idx) {
  return ::getPort(*this, idx);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleGeneratedOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleGeneratedOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HWModuleOpGenericAdaptorBase::HWModuleOpGenericAdaptorBase(HWModuleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HWModuleOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleOpGenericAdaptorBase::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleOpGenericAdaptorBase::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleOpGenericAdaptorBase::getResultLocs() {
  auto attr = getResultLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleOpGenericAdaptorBase::getComment() {
  auto attr = getCommentAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
HWModuleOpAdaptor::HWModuleOpAdaptor(HWModuleOp op) : HWModuleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HWModuleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_comment = getProperties().comment; (void)tblgen_comment;
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitError(loc, "'hw.module' op requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'hw.module' op requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_result_locs = getProperties().result_locs; (void)tblgen_result_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.module' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.module' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_module_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_module_type))) && ((::llvm::isa<::circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue()))) && ((isa<circt::hw::ModuleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_module_type).getValue())))))
    return emitError(loc, "'hw.module' op attribute 'module_type' failed to satisfy constraint: type attribute of a module");

  if (tblgen_per_port_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_per_port_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_per_port_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'hw.module' op attribute 'per_port_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_result_locs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_result_locs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_result_locs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::LocationAttr>(attr))); }))))
    return emitError(loc, "'hw.module' op attribute 'result_locs' failed to satisfy constraint: location array attribute");

  if (tblgen_parameters && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_parameters))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_parameters), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::hw::ParamDeclAttr>(attr))); }))))
    return emitError(loc, "'hw.module' op attribute 'parameters' failed to satisfy constraint: parameter array attribute");

  if (tblgen_comment && !((::llvm::isa<::mlir::StringAttr>(tblgen_comment))))
    return emitError(loc, "'hw.module' op attribute 'comment' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.comment;
       auto attr = dict.get("comment");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `comment` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.module_type;
       auto attr = dict.get("module_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.per_port_attrs;
       auto attr = dict.get("per_port_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.result_locs;
       auto attr = dict.get("result_locs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `result_locs` in property conversion: " << attr;
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

::mlir::Attribute HWModuleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.comment;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("comment",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.module_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("module_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.per_port_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("per_port_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.result_locs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("result_locs",
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

llvm::hash_code HWModuleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.comment.getAsOpaquePointer()), 
    llvm::hash_value(prop.module_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.per_port_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.result_locs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HWModuleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "comment")
      return prop.comment;

    if (name == "module_type")
      return prop.module_type;

    if (name == "parameters")
      return prop.parameters;

    if (name == "per_port_attrs")
      return prop.per_port_attrs;

    if (name == "result_locs")
      return prop.result_locs;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void HWModuleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "comment") {
       prop.comment = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.comment)>>(value);
       return;
    }

    if (name == "module_type") {
       prop.module_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.module_type)>>(value);
       return;
    }

    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "per_port_attrs") {
       prop.per_port_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.per_port_attrs)>>(value);
       return;
    }

    if (name == "result_locs") {
       prop.result_locs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.result_locs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void HWModuleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.comment) attrs.append("comment", prop.comment);

    if (prop.module_type) attrs.append("module_type", prop.module_type);

    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.per_port_attrs) attrs.append("per_port_attrs", prop.per_port_attrs);

    if (prop.result_locs) attrs.append("result_locs", prop.result_locs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult HWModuleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCommentAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "comment", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW6(attr, "module_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW9(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPerPortAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW7(attr, "per_port_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResultLocsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW8(attr, "result_locs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HWModuleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.comment)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.module_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.per_port_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.result_locs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HWModuleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.comment);
  writer.writeAttribute(prop.module_type);
  writer.writeAttribute(prop.parameters);

  writer.writeOptionalAttribute(prop.per_port_attrs);

  writer.writeOptionalAttribute(prop.result_locs);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef HWModuleOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::circt::hw::ModuleType HWModuleOp::getModuleType() {
  auto attr = getModuleTypeAttr();
  return ::llvm::cast<::circt::hw::ModuleType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > HWModuleOp::getPerPortAttrs() {
  auto attr = getPerPortAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > HWModuleOp::getResultLocs() {
  auto attr = getResultLocsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr HWModuleOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > HWModuleOp::getComment() {
  auto attr = getCommentAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void HWModuleOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HWModuleOp::setModuleType(::circt::hw::ModuleType attrValue) {
  getProperties().module_type = ::mlir::TypeAttr::get(attrValue);
}

void HWModuleOp::setComment(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().comment;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

HWModuleOp HWModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment));
  auto __res__ = ::llvm::dyn_cast<HWModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleOp HWModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment));
}

HWModuleOp HWModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment, bool shouldEnsureTerminator) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment), std::forward<decltype(shouldEnsureTerminator)>(shouldEnsureTerminator));
  auto __res__ = ::llvm::dyn_cast<HWModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleOp HWModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment, bool shouldEnsureTerminator) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment), std::forward<decltype(shouldEnsureTerminator)>(shouldEnsureTerminator));
}

HWModuleOp HWModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, HWModuleBuilder modBuilder, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(modBuilder)>(modBuilder), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment));
  auto __res__ = ::llvm::dyn_cast<HWModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HWModuleOp HWModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, HWModuleBuilder modBuilder, ArrayAttr parameters, ArrayRef<NamedAttribute> attributes, StringAttr comment) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(modBuilder)>(modBuilder), std::forward<decltype(parameters)>(parameters), std::forward<decltype(attributes)>(attributes), std::forward<decltype(comment)>(comment));
}

::llvm::LogicalResult HWModuleOp::verifyInvariantsImpl() {
  auto tblgen_comment = getProperties().comment; (void)tblgen_comment;
  auto tblgen_module_type = getProperties().module_type; (void)tblgen_module_type;
  if (!tblgen_module_type) return emitOpError("requires attribute 'module_type'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_per_port_attrs = getProperties().per_port_attrs; (void)tblgen_per_port_attrs;
  auto tblgen_result_locs = getProperties().result_locs; (void)tblgen_result_locs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW6(*this, tblgen_module_type, "module_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW7(*this, tblgen_per_port_attrs, "per_port_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW8(*this, tblgen_result_locs, "result_locs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW9(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_comment, "comment")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_HW2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult HWModuleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult HWModuleOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.sym_name;
    auto sym_nameAttrName = ::mlir::StringAttr::get(ctx, "sym_name");
    auto attr = dict.get(sym_nameAttrName);
    usedKeys.insert(sym_nameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.module_type;
    auto module_typeAttrName = ::mlir::StringAttr::get(ctx, "module_type");
    auto attr = dict.get(module_typeAttrName);
    usedKeys.insert(module_typeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for module_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `module_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.per_port_attrs;
    auto per_port_attrsAttrName = ::mlir::StringAttr::get(ctx, "per_port_attrs");
    auto attr = dict.get(per_port_attrsAttrName);
    usedKeys.insert(per_port_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for per_port_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `per_port_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.result_locs;
    auto result_locsAttrName = ::mlir::StringAttr::get(ctx, "result_locs");
    auto attr = dict.get(result_locsAttrName);
    usedKeys.insert(result_locsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for result_locs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `result_locs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.parameters;
    auto parametersAttrName = ::mlir::StringAttr::get(ctx, "parameters");
    auto attr = dict.get(parametersAttrName);
    usedKeys.insert(parametersAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for parameters in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.comment;
    auto commentAttrName = ::mlir::StringAttr::get(ctx, "comment");
    auto attr = dict.get(commentAttrName);
    usedKeys.insert(commentAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for comment in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `comment` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

ModuleType HWModuleOp::getHWModuleType() {
  return getModuleType();
}

void HWModuleOp::setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym) {
  auto portSymAttr = StringAttr::get(getContext(), getPortSymbolAttrName());
  setPortAttr(portIndex, portSymAttr, sym);
}

size_t HWModuleOp::getNumPorts() {
  auto modty = getHWModuleType();
  return modty.getNumPorts();
}

size_t HWModuleOp::getNumInputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumInputs();
}

size_t HWModuleOp::getNumOutputPorts() {
  auto modty = getHWModuleType();
  return modty.getNumOutputs();
}

size_t HWModuleOp::getPortIdForInputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForInputId(idx);
}

size_t HWModuleOp::getPortIdForOutputId(size_t idx) {
  auto modty = getHWModuleType();
  return modty.getPortIdForOutputId(idx);
}

SmallVector<::circt::hw::PortInfo> HWModuleOp::getPortList() {
  return ::getPortList(*this);
}

::circt::hw::PortInfo HWModuleOp::getPort(size_t idx) {
  return ::getPort(*this, idx);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HierPathOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HierPathOpGenericAdaptorBase::HierPathOpGenericAdaptorBase(HierPathOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HierPathOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr HierPathOpGenericAdaptorBase::getNamepath() {
  auto attr = getNamepathAttr();
  return attr;
}


} // namespace detail
HierPathOpAdaptor::HierPathOpAdaptor(HierPathOp op) : HierPathOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HierPathOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_namepath = getProperties().namepath; (void)tblgen_namepath;
  if (!tblgen_namepath) return emitError(loc, "'hw.hierpath' op requires attribute 'namepath'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.hierpath' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.hierpath' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_namepath && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_namepath))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_namepath), [&](::mlir::Attribute attr) { return attr && ((llvm::isa<::mlir::FlatSymbolRefAttr, ::circt::hw::InnerRefAttr>(attr))); }))))
    return emitError(loc, "'hw.hierpath' op attribute 'namepath' failed to satisfy constraint: name reference array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HierPathOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.namepath;
       auto attr = dict.get("namepath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `namepath` in property conversion: " << attr;
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

::mlir::Attribute HierPathOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.namepath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("namepath",
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

llvm::hash_code HierPathOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.namepath.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HierPathOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "namepath")
      return prop.namepath;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void HierPathOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "namepath") {
       prop.namepath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.namepath)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void HierPathOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.namepath) attrs.append("namepath", prop.namepath);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult HierPathOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNamepathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW11(attr, "namepath", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HierPathOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.namepath)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HierPathOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.namepath);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef HierPathOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr HierPathOp::getNamepath() {
  auto attr = getNamepathAttr();
  return attr;
}

void HierPathOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HierPathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().namepath = namepath;
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
}

void HierPathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().namepath = namepath;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
}

void HierPathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().namepath = namepath;
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
}

void HierPathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().namepath = namepath;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(namepath)>(namepath));
}

void HierPathOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HierPathOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HierPathOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

HierPathOp HierPathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HierPathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HierPathOp HierPathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult HierPathOp::verifyInvariantsImpl() {
  auto tblgen_namepath = getProperties().namepath; (void)tblgen_namepath;
  if (!tblgen_namepath) return emitOpError("requires attribute 'namepath'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW11(*this, tblgen_namepath, "namepath")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult HierPathOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult HierPathOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.sym_name;
    auto sym_nameAttrName = ::mlir::StringAttr::get(ctx, "sym_name");
    auto attr = dict.get(sym_nameAttrName);
    usedKeys.insert(sym_nameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.namepath;
    auto namepathAttrName = ::mlir::StringAttr::get(ctx, "namepath");
    auto attr = dict.get(namepathAttrName);
    usedKeys.insert(namepathAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for namepath in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `namepath` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::HierPathOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::HierPathOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::InstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceOpGenericAdaptorBase::InstanceOpGenericAdaptorBase(InstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> InstanceOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef InstanceOpGenericAdaptorBase::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceOpGenericAdaptorBase::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InstanceOpGenericAdaptorBase::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::mlir::ArrayAttr InstanceOpGenericAdaptorBase::getResultNames() {
  auto attr = getResultNamesAttr();
  return attr;
}

::mlir::ArrayAttr InstanceOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> InstanceOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::mlir::UnitAttr InstanceOpGenericAdaptorBase::getDoNotPrintAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().doNotPrint);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool InstanceOpGenericAdaptorBase::getDoNotPrint() {
  auto attr = getDoNotPrintAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
InstanceOpAdaptor::InstanceOpAdaptor(InstanceOp op) : InstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitError(loc, "'hw.instance' op requires attribute 'argNames'");
  auto tblgen_doNotPrint = getProperties().doNotPrint; (void)tblgen_doNotPrint;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitError(loc, "'hw.instance' op requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitError(loc, "'hw.instance' op requires attribute 'moduleName'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'hw.instance' op requires attribute 'parameters'");
  auto tblgen_resultNames = getProperties().resultNames; (void)tblgen_resultNames;
  if (!tblgen_resultNames) return emitError(loc, "'hw.instance' op requires attribute 'resultNames'");

  if (tblgen_instanceName && !((::llvm::isa<::mlir::StringAttr>(tblgen_instanceName))))
    return emitError(loc, "'hw.instance' op attribute 'instanceName' failed to satisfy constraint: string attribute");

  if (tblgen_moduleName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_moduleName))))
    return emitError(loc, "'hw.instance' op attribute 'moduleName' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_argNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_argNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_argNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'hw.instance' op attribute 'argNames' failed to satisfy constraint: string array attribute");

  if (tblgen_resultNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_resultNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_resultNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'hw.instance' op attribute 'resultNames' failed to satisfy constraint: string array attribute");

  if (tblgen_parameters && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_parameters))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_parameters), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::hw::ParamDeclAttr>(attr))); }))))
    return emitError(loc, "'hw.instance' op attribute 'parameters' failed to satisfy constraint: parameter array attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'hw.instance' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_doNotPrint && !((::llvm::isa<::mlir::UnitAttr>(tblgen_doNotPrint))))
    return emitError(loc, "'hw.instance' op attribute 'doNotPrint' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> InstanceOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange InstanceOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> InstanceOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult InstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.argNames;
       auto attr = dict.get("argNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.doNotPrint;
       auto attr = dict.get("doNotPrint");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `doNotPrint` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.instanceName;
       auto attr = dict.get("instanceName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `instanceName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.moduleName;
       auto attr = dict.get("moduleName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `moduleName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.resultNames;
       auto attr = dict.get("resultNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `resultNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.argNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("argNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.doNotPrint;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("doNotPrint",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.instanceName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("instanceName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.moduleName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("moduleName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.resultNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("resultNames",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.argNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.doNotPrint.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.instanceName.getAsOpaquePointer()), 
    llvm::hash_value(prop.moduleName.getAsOpaquePointer()), 
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.resultNames.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "argNames")
      return prop.argNames;

    if (name == "doNotPrint")
      return prop.doNotPrint;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "instanceName")
      return prop.instanceName;

    if (name == "moduleName")
      return prop.moduleName;

    if (name == "parameters")
      return prop.parameters;

    if (name == "resultNames")
      return prop.resultNames;
  return std::nullopt;
}

void InstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "argNames") {
       prop.argNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.argNames)>>(value);
       return;
    }

    if (name == "doNotPrint") {
       prop.doNotPrint = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.doNotPrint)>>(value);
       return;
    }

    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "instanceName") {
       prop.instanceName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.instanceName)>>(value);
       return;
    }

    if (name == "moduleName") {
       prop.moduleName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.moduleName)>>(value);
       return;
    }

    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "resultNames") {
       prop.resultNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.resultNames)>>(value);
       return;
    }
}

void InstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.argNames) attrs.append("argNames", prop.argNames);

    if (prop.doNotPrint) attrs.append("doNotPrint", prop.doNotPrint);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.instanceName) attrs.append("instanceName", prop.instanceName);

    if (prop.moduleName) attrs.append("moduleName", prop.moduleName);

    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.resultNames) attrs.append("resultNames", prop.resultNames);
}

::llvm::LogicalResult InstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW5(attr, "argNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getDoNotPrintAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW13(attr, "doNotPrint", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW12(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInstanceNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "instanceName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW10(attr, "moduleName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW9(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResultNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW5(attr, "resultNames", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.argNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.doNotPrint)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.instanceName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.moduleName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.resultNames)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.argNames);

  writer.writeOptionalAttribute(prop.doNotPrint);

  writer.writeOptionalAttribute(prop.inner_sym);
  writer.writeAttribute(prop.instanceName);
  writer.writeAttribute(prop.moduleName);
  writer.writeAttribute(prop.parameters);
  writer.writeAttribute(prop.resultNames);
}

::llvm::StringRef InstanceOp::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceOp::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InstanceOp::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::mlir::ArrayAttr InstanceOp::getResultNames() {
  auto attr = getResultNamesAttr();
  return attr;
}

::mlir::ArrayAttr InstanceOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> InstanceOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

bool InstanceOp::getDoNotPrint() {
  auto attr = getDoNotPrintAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void InstanceOp::setInstanceName(::llvm::StringRef attrValue) {
  getProperties().instanceName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void InstanceOp::setModuleName(::llvm::StringRef attrValue) {
  getProperties().moduleName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void InstanceOp::setDoNotPrint(bool attrValue) {
    auto &odsProp = getProperties().doNotPrint;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringAttr name, ArrayRef<Value> inputs, ArrayAttr parameters, InnerSymAttr innerSym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs), std::forward<decltype(parameters)>(parameters), std::forward<decltype(innerSym)>(innerSym));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringAttr name, ArrayRef<Value> inputs, ArrayAttr parameters, InnerSymAttr innerSym) {
  return create(builder, builder.getLoc(), std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs), std::forward<decltype(parameters)>(parameters), std::forward<decltype(innerSym)>(innerSym));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters, InnerSymAttr innerSym) {
      build(odsBuilder, odsState, module, odsBuilder.getStringAttr(name), inputs,
            parameters, innerSym);
    
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters, InnerSymAttr innerSym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs), std::forward<decltype(parameters)>(parameters), std::forward<decltype(innerSym)>(innerSym));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters, InnerSymAttr innerSym) {
  return create(builder, builder.getLoc(), std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs), std::forward<decltype(parameters)>(parameters), std::forward<decltype(innerSym)>(innerSym));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().instanceName = instanceName;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  odsState.getOrAddProperties<Properties>().resultNames = resultNames;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (doNotPrint) {
    odsState.getOrAddProperties<Properties>().doNotPrint = doNotPrint;
  }
  odsState.addTypes(results);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputs)>(inputs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(parameters)>(parameters), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(doNotPrint)>(doNotPrint));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputs)>(inputs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(parameters)>(parameters), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(doNotPrint)>(doNotPrint));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().instanceName = odsBuilder.getStringAttr(instanceName);
  odsState.getOrAddProperties<Properties>().moduleName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleName);
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  odsState.getOrAddProperties<Properties>().resultNames = resultNames;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (doNotPrint) {
    odsState.getOrAddProperties<Properties>().doNotPrint = ((doNotPrint) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(results);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputs)>(inputs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(parameters)>(parameters), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(doNotPrint)>(doNotPrint));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputs)>(inputs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(parameters)>(parameters), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(doNotPrint)>(doNotPrint));
}

void InstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InstanceOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InstanceOp::verifyInvariantsImpl() {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitOpError("requires attribute 'argNames'");
  auto tblgen_doNotPrint = getProperties().doNotPrint; (void)tblgen_doNotPrint;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitOpError("requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitOpError("requires attribute 'moduleName'");
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_resultNames = getProperties().resultNames; (void)tblgen_resultNames;
  if (!tblgen_resultNames) return emitOpError("requires attribute 'resultNames'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_instanceName, "instanceName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW10(*this, tblgen_moduleName, "moduleName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW5(*this, tblgen_argNames, "argNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW5(*this, tblgen_resultNames, "resultNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW9(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW12(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW13(*this, tblgen_doNotPrint, "doNotPrint")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW11(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW11(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult InstanceOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.instanceName;
    auto instanceNameAttrName = ::mlir::StringAttr::get(ctx, "instanceName");
    auto attr = dict.get(instanceNameAttrName);
    usedKeys.insert(instanceNameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for instanceName in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `instanceName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.moduleName;
    auto moduleNameAttrName = ::mlir::StringAttr::get(ctx, "moduleName");
    auto attr = dict.get(moduleNameAttrName);
    usedKeys.insert(moduleNameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for moduleName in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `moduleName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.argNames;
    auto argNamesAttrName = ::mlir::StringAttr::get(ctx, "argNames");
    auto attr = dict.get(argNamesAttrName);
    usedKeys.insert(argNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for argNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.resultNames;
    auto resultNamesAttrName = ::mlir::StringAttr::get(ctx, "resultNames");
    auto attr = dict.get(resultNamesAttrName);
    usedKeys.insert(resultNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for resultNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `resultNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.parameters;
    auto parametersAttrName = ::mlir::StringAttr::get(ctx, "parameters");
    auto attr = dict.get(parametersAttrName);
    usedKeys.insert(parametersAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for parameters in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.inner_sym;
    auto inner_symAttrName = ::mlir::StringAttr::get(ctx, "inner_sym");
    auto attr = dict.get(inner_symAttrName);
    usedKeys.insert(inner_symAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for inner_sym in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.doNotPrint;
    auto doNotPrintAttrName = ::mlir::StringAttr::get(ctx, "doNotPrint");
    auto attr = dict.get(doNotPrintAttrName);
    usedKeys.insert(doNotPrintAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for doNotPrint in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `doNotPrint` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

::llvm::SmallVector<::circt::hw::PortInfo> InstanceOp::getPortList() {
  return instance_like_impl::getPortList(getOperation());
}

::circt::hw::PortInfo InstanceOp::getPort(size_t idx) {
  return getPortList()[idx];
}

size_t InstanceOp::getNumPorts() {
  return getNumInputPorts() + getNumOutputPorts();
}

size_t InstanceOp::getNumInputPorts() { return getNumOperands(); }

size_t InstanceOp::getNumOutputPorts() { return getNumResults(); }

size_t InstanceOp::getPortIdForInputId(size_t idx) { return idx; }

size_t InstanceOp::getPortIdForOutputId(size_t idx) {
  return idx + getNumInputPorts();
}

/// Suggest a name for each result value based on the saved result names
/// attribute.
void InstanceOp::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  ::circt::hw::instance_like_impl::getAsmResultNames(
      setNameFn, getInstanceName(), getOutputNames(), getResults());
}

void InstanceOp::getValues(SmallVectorImpl<Value> &values,
                          const ModulePortInfo &mpi) {
  size_t inputPort = 0, resultPort = 0;
  values.resize(mpi.size());
  auto results = getResults();
  auto inputs = getInputs();
  for (auto [idx, port] : llvm::enumerate(mpi))
    if (mpi.at(idx).isOutput())
      values[idx] = results[resultPort++];
    else
      values[idx] = inputs[inputPort++];
}

} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::InstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::OutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OutputOpGenericAdaptorBase::OutputOpGenericAdaptorBase(OutputOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> OutputOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
OutputOpAdaptor::OutputOpAdaptor(OutputOp op) : OutputOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OutputOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> OutputOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange OutputOp::getOutputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult OutputOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute OutputOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OutputOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> OutputOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void OutputOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void OutputOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult OutputOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void OutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
build(odsBuilder, odsState, mlir::ValueRange());
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void OutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange outputs) {
  odsState.addOperands(outputs);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange outputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange outputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs));
}

void OutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OutputOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW11(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OutputOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult OutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> outputsOperands;
  ::llvm::SMLoc outputsOperandsLoc;
  (void)outputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> outputsTypes;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  outputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(outputsOperands))
    return ::mlir::failure();
  if (!outputsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(outputsTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(outputsOperands, outputsTypes, outputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void OutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getOutputs().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getOutputs();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getOutputs().getTypes();
  }
}

void OutputOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::OutputOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ParamValueOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ParamValueOpGenericAdaptorBase::ParamValueOpGenericAdaptorBase(ParamValueOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::Attribute ParamValueOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr;
}


} // namespace detail
ParamValueOpAdaptor::ParamValueOpAdaptor(ParamValueOp op) : ParamValueOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ParamValueOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'hw.param.value' op requires attribute 'value'");

  if (tblgen_value && !((true)))
    return emitError(loc, "'hw.param.value' op attribute 'value' failed to satisfy constraint: any attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ParamValueOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.value;
       auto attr = dict.get("value");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ParamValueOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.value;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("value",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ParamValueOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ParamValueOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ParamValueOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ParamValueOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ParamValueOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW14(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ParamValueOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ParamValueOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.value);
}

::mlir::Attribute ParamValueOp::getValue() {
  auto attr = getValueAttr();
  return attr;
}

void ParamValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute value) {
  odsState.getOrAddProperties<Properties>().value = value;
  odsState.addTypes(result);
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ParamValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  odsState.getOrAddProperties<Properties>().value = value;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ParamValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ParamValueOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ParamValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ParamValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::Attribute typeAttr;
  auto attrName = getValueAttrName(odsState.name);
  for (auto attr : attributes) {
    if (attr.getName() == attrName) {
      typeAttr = attr.getValue();
      break;
    }
  }
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
    odsState.addTypes({::llvm::cast<::mlir::TypedAttr>(typeAttr).getType()});
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ParamValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::Attribute typeAttr = properties.getValue();
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
    odsState.addTypes({::llvm::cast<::mlir::TypedAttr>(typeAttr).getType()});
}

ParamValueOp ParamValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ParamValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParamValueOp ParamValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ParamValueOp::verifyInvariantsImpl() {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW14(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW12(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ParamValueOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ParamValueOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::Attribute valueAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  {
    auto odsResult = parseParamValue(parser, valueAttr, resultRawType);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<ParamValueOp::Properties>().value = valueAttr;
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
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void ParamValueOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printParamValue(_odsPrinter, *this, getValueAttr(), getResult().getType());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("value");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ParamValueOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ParamValueOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::ParamValueOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructCreateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StructCreateOpGenericAdaptorBase::StructCreateOpGenericAdaptorBase(StructCreateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> StructCreateOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
StructCreateOpAdaptor::StructCreateOpAdaptor(StructCreateOp op) : StructCreateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StructCreateOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> StructCreateOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange StructCreateOp::getInputMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult StructCreateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute StructCreateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StructCreateOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> StructCreateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void StructCreateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void StructCreateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult StructCreateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void StructCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

StructCreateOp StructCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<StructCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructCreateOp StructCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void StructCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StructCreateOp StructCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructCreateOp StructCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StructCreateOp StructCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructCreateOp StructCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StructCreateOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW13(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult StructCreateOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void StructCreateOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult StructCreateOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void StructCreateOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StructCreateOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructExplodeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StructExplodeOpGenericAdaptorBase::StructExplodeOpGenericAdaptorBase(StructExplodeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
StructExplodeOpAdaptor::StructExplodeOpAdaptor(StructExplodeOp op) : StructExplodeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StructExplodeOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> StructExplodeOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult StructExplodeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute StructExplodeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StructExplodeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> StructExplodeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void StructExplodeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void StructExplodeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult StructExplodeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

StructExplodeOp StructExplodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<StructExplodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExplodeOp StructExplodeOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void StructExplodeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

StructExplodeOp StructExplodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<StructExplodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExplodeOp StructExplodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void StructExplodeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);
}

StructExplodeOp StructExplodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructExplodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExplodeOp StructExplodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructExplodeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

StructExplodeOp StructExplodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructExplodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExplodeOp StructExplodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StructExplodeOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW13(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult StructExplodeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void StructExplodeOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult StructExplodeOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void StructExplodeOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StructExplodeOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructExtractOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StructExtractOpGenericAdaptorBase::StructExtractOpGenericAdaptorBase(StructExtractOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t StructExtractOpGenericAdaptorBase::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
StructExtractOpAdaptor::StructExtractOpAdaptor(StructExtractOp op) : StructExtractOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StructExtractOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitError(loc, "'hw.struct_extract' op requires attribute 'fieldIndex'");

  if (tblgen_fieldIndex && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_fieldIndex))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_fieldIndex).getType().isSignlessInteger(32)))))
    return emitError(loc, "'hw.struct_extract' op attribute 'fieldIndex' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult StructExtractOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.fieldIndex;
       auto attr = dict.get("fieldIndex");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute StructExtractOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.fieldIndex;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fieldIndex",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StructExtractOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.fieldIndex.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StructExtractOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "fieldIndex")
      return prop.fieldIndex;
  return std::nullopt;
}

void StructExtractOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "fieldIndex") {
       prop.fieldIndex = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fieldIndex)>>(value);
       return;
    }
}

void StructExtractOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.fieldIndex) attrs.append("fieldIndex", prop.fieldIndex);
}

::llvm::LogicalResult StructExtractOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldIndexAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW15(attr, "fieldIndex", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StructExtractOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.fieldIndex)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StructExtractOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.fieldIndex);
}

uint32_t StructExtractOp::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}

void StructExtractOp::setFieldIndex(uint32_t attrValue) {
  getProperties().fieldIndex = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StructType::FieldInfo field) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(field)>(field));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StructType::FieldInfo field) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(field)>(field));
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
}

void StructExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName) {
      build(odsBuilder, odsState, input, odsBuilder.getStringAttr(fieldName));
    
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
}

void StructExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  odsState.addTypes(result);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void StructExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void StructExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  odsState.addTypes(result);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void StructExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void StructExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<StructExtractOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StructExtractOp StructExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructExtractOp StructExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StructExtractOp::verifyInvariantsImpl() {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitOpError("requires attribute 'fieldIndex'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW15(*this, tblgen_fieldIndex, "fieldIndex")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW13(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult StructExtractOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void StructExtractOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult StructExtractOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.fieldIndex;
    auto fieldIndexAttrName = ::mlir::StringAttr::get(ctx, "fieldIndex");
    auto attr = dict.get(fieldIndexAttrName);
    usedKeys.insert(fieldIndexAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for fieldIndex in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void StructExtractOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StructExtractOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::StructExtractOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructInjectOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StructInjectOpGenericAdaptorBase::StructInjectOpGenericAdaptorBase(StructInjectOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t StructInjectOpGenericAdaptorBase::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
StructInjectOpAdaptor::StructInjectOpAdaptor(StructInjectOp op) : StructInjectOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StructInjectOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitError(loc, "'hw.struct_inject' op requires attribute 'fieldIndex'");

  if (tblgen_fieldIndex && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_fieldIndex))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_fieldIndex).getType().isSignlessInteger(32)))))
    return emitError(loc, "'hw.struct_inject' op attribute 'fieldIndex' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult StructInjectOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.fieldIndex;
       auto attr = dict.get("fieldIndex");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute StructInjectOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.fieldIndex;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fieldIndex",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StructInjectOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.fieldIndex.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StructInjectOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "fieldIndex")
      return prop.fieldIndex;
  return std::nullopt;
}

void StructInjectOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "fieldIndex") {
       prop.fieldIndex = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fieldIndex)>>(value);
       return;
    }
}

void StructInjectOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.fieldIndex) attrs.append("fieldIndex", prop.fieldIndex);
}

::llvm::LogicalResult StructInjectOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldIndexAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW15(attr, "fieldIndex", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StructInjectOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.fieldIndex)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StructInjectOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.fieldIndex);
}

uint32_t StructInjectOp::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}

void StructInjectOp::setFieldIndex(uint32_t attrValue) {
  getProperties().fieldIndex = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName, Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName, Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName, Value newValue) {
      build(odsBuilder, odsState, input, odsBuilder.getStringAttr(fieldName), newValue);
    
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName, Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName, Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  odsState.addTypes(result);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(StructInjectOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  odsState.addTypes(result);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(StructInjectOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  odsState.addOperands(input);
  odsState.addOperands(newValue);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(newValue)>(newValue));
}

void StructInjectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<StructInjectOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<StructInjectOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(StructInjectOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructInjectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void StructInjectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(StructInjectOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

StructInjectOp StructInjectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructInjectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructInjectOp StructInjectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StructInjectOp::verifyInvariantsImpl() {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitOpError("requires attribute 'fieldIndex'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW15(*this, tblgen_fieldIndex, "fieldIndex")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW13(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW13(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, result} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult StructInjectOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void StructInjectOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult StructInjectOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::llvm::LogicalResult StructInjectOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.fieldIndex;
    auto fieldIndexAttrName = ::mlir::StringAttr::get(ctx, "fieldIndex");
    auto attr = dict.get(fieldIndexAttrName);
    usedKeys.insert(fieldIndexAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for fieldIndex in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void StructInjectOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StructInjectOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::StructInjectOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TriggeredOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TriggeredOpGenericAdaptorBase::TriggeredOpGenericAdaptorBase(TriggeredOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> TriggeredOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

circt::hw::EventControl TriggeredOpGenericAdaptorBase::getEvent() {
  auto attr = getEventAttr();
  return attr.getValue();
}


} // namespace detail
TriggeredOpAdaptor::TriggeredOpAdaptor(TriggeredOp op) : TriggeredOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TriggeredOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_event = getProperties().event; (void)tblgen_event;
  if (!tblgen_event) return emitError(loc, "'hw.triggered' op requires attribute 'event'");

  if (tblgen_event && !((::llvm::isa<circt::hw::EventControlAttr>(tblgen_event))))
    return emitError(loc, "'hw.triggered' op attribute 'event' failed to satisfy constraint: edge control trigger");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> TriggeredOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange TriggeredOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult TriggeredOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.event;
       auto attr = dict.get("event");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `event` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute TriggeredOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.event;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("event",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code TriggeredOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.event.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TriggeredOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "event")
      return prop.event;
  return std::nullopt;
}

void TriggeredOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "event") {
       prop.event = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.event)>>(value);
       return;
    }
}

void TriggeredOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.event) attrs.append("event", prop.event);
}

::llvm::LogicalResult TriggeredOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEventAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW16(attr, "event", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TriggeredOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.event)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TriggeredOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.event);
}

circt::hw::EventControl TriggeredOp::getEvent() {
  auto attr = getEventAttr();
  return attr.getValue();
}

void TriggeredOp::setEvent(circt::hw::EventControl attrValue) {
  getProperties().event = circt::hw::EventControlAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

TriggeredOp TriggeredOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, EventControlAttr event, Value trigger, ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(event)>(event), std::forward<decltype(trigger)>(trigger), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<TriggeredOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TriggeredOp TriggeredOp::create(::mlir::ImplicitLocOpBuilder &builder, EventControlAttr event, Value trigger, ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(event)>(event), std::forward<decltype(trigger)>(trigger), std::forward<decltype(inputs)>(inputs));
}

::llvm::LogicalResult TriggeredOp::verifyInvariantsImpl() {
  auto tblgen_event = getProperties().event; (void)tblgen_event;
  if (!tblgen_event) return emitOpError("requires attribute 'event'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW16(*this, tblgen_event, "event")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW10(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW11(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_HW2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult TriggeredOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TriggeredOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  circt::hw::EventControlAttr eventAttr;
  ::mlir::OpAsmParser::UnresolvedOperand triggerRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> triggerOperands(&triggerRawOperand, 1);  ::llvm::SMLoc triggerOperandsLoc;
  (void)triggerOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"posedge","negedge","edge"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "event", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'event' [posedge, negedge, edge]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::hw::symbolizeEventControl(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "event attribute specification: \"" << attrStr << '"';;

      eventAttr = circt::hw::EventControlAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<TriggeredOp::Properties>().event = eventAttr;
    }
  }

  triggerOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(triggerRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalLParen())) {

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(inputsTypes))
    return ::mlir::failure();
  }

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(bodyRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(triggerOperands, odsBuildableType0, triggerOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void TriggeredOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getEvent();
    auto caseValueStr = stringifyEventControl(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getTrigger();
  if (!getInputs().empty()) {
    _odsPrinter << "(";
    _odsPrinter << getInputs();
    _odsPrinter << ")";
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getInputs().getTypes();
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("event");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::TriggeredOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::TriggeredOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TypeScopeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TypeScopeOpGenericAdaptorBase::TypeScopeOpGenericAdaptorBase(TypeScopeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef TypeScopeOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
TypeScopeOpAdaptor::TypeScopeOpAdaptor(TypeScopeOp op) : TypeScopeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TypeScopeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.type_scope' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.type_scope' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult TypeScopeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute TypeScopeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code TypeScopeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TypeScopeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void TypeScopeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void TypeScopeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult TypeScopeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TypeScopeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TypeScopeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef TypeScopeOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void TypeScopeOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void TypeScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void TypeScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void TypeScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void TypeScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void TypeScopeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<TypeScopeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TypeScopeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TypeScopeOp TypeScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TypeScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypeScopeOp TypeScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult TypeScopeOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_HW2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult TypeScopeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TypeScopeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<TypeScopeOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(bodyRegion));
  return ::mlir::success();
}

void TypeScopeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::TypeScopeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::TypeScopeOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TypedeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TypedeclOpGenericAdaptorBase::TypedeclOpGenericAdaptorBase(TypedeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef TypedeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::Type TypedeclOpGenericAdaptorBase::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > TypedeclOpGenericAdaptorBase::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
TypedeclOpAdaptor::TypedeclOpAdaptor(TypedeclOp op) : TypedeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TypedeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'hw.typedecl' op requires attribute 'sym_name'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitError(loc, "'hw.typedecl' op requires attribute 'type'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'hw.typedecl' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_type))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))) && ((true))))
    return emitError(loc, "'hw.typedecl' op attribute 'type' failed to satisfy constraint: any type attribute");

  if (tblgen_verilogName && !((::llvm::isa<::mlir::StringAttr>(tblgen_verilogName))))
    return emitError(loc, "'hw.typedecl' op attribute 'verilogName' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult TypedeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

  {
    auto &propStorage = prop.type;
       auto attr = dict.get("type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.verilogName;
       auto attr = dict.get("verilogName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `verilogName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute TypedeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.verilogName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("verilogName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code TypedeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.type.getAsOpaquePointer()), 
    llvm::hash_value(prop.verilogName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TypedeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;

    if (name == "type")
      return prop.type;

    if (name == "verilogName")
      return prop.verilogName;
  return std::nullopt;
}

void TypedeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "type") {
       prop.type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.type)>>(value);
       return;
    }

    if (name == "verilogName") {
       prop.verilogName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.verilogName)>>(value);
       return;
    }
}

void TypedeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.type) attrs.append("type", prop.type);

    if (prop.verilogName) attrs.append("verilogName", prop.verilogName);
}

::llvm::LogicalResult TypedeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW17(attr, "type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getVerilogNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "verilogName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TypedeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.verilogName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TypedeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
  writer.writeAttribute(prop.type);

  writer.writeOptionalAttribute(prop.verilogName);
}

::llvm::StringRef TypedeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::Type TypedeclOp::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > TypedeclOp::getVerilogName() {
  auto attr = getVerilogNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void TypedeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void TypedeclOp::setType(::mlir::Type attrValue) {
  getProperties().type = ::mlir::TypeAttr::get(attrValue);
}

void TypedeclOp::setVerilogName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().verilogName;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void TypedeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().type = type;
  if (verilogName) {
    odsState.getOrAddProperties<Properties>().verilogName = verilogName;
  }
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
}

void TypedeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().type = type;
  if (verilogName) {
    odsState.getOrAddProperties<Properties>().verilogName = verilogName;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
}

void TypedeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (verilogName) {
    odsState.getOrAddProperties<Properties>().verilogName = verilogName;
  }
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
}

void TypedeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (verilogName) {
    odsState.getOrAddProperties<Properties>().verilogName = verilogName;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type), std::forward<decltype(verilogName)>(verilogName));
}

void TypedeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<TypedeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TypedeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TypedeclOp TypedeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TypedeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TypedeclOp TypedeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult TypedeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitOpError("requires attribute 'type'");
  auto tblgen_verilogName = getProperties().verilogName; (void)tblgen_verilogName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW17(*this, tblgen_type, "type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_verilogName, "verilogName")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult TypedeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TypedeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::StringAttr verilogNameAttr;
  ::mlir::TypeAttr typeAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<TypedeclOp::Properties>().sym_name = sym_nameAttr;
  if (::mlir::succeeded(parser.parseOptionalComma())) {

  if (parser.parseCustomAttributeWithFallback(verilogNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (verilogNameAttr) result.getOrAddProperties<TypedeclOp::Properties>().verilogName = verilogNameAttr;
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeAttr) result.getOrAddProperties<TypedeclOp::Properties>().type = typeAttr;
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

void TypedeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  if (getVerilogNameAttr()) {
    _odsPrinter << ",";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getVerilogNameAttr());
  }
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("verilogName");
  elidedAttrs.push_back("type");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::TypedeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::TypedeclOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::UnionCreateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnionCreateOpGenericAdaptorBase::UnionCreateOpGenericAdaptorBase(UnionCreateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t UnionCreateOpGenericAdaptorBase::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
UnionCreateOpAdaptor::UnionCreateOpAdaptor(UnionCreateOp op) : UnionCreateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnionCreateOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitError(loc, "'hw.union_create' op requires attribute 'fieldIndex'");

  if (tblgen_fieldIndex && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_fieldIndex))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_fieldIndex).getType().isSignlessInteger(32)))))
    return emitError(loc, "'hw.union_create' op attribute 'fieldIndex' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult UnionCreateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.fieldIndex;
       auto attr = dict.get("fieldIndex");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute UnionCreateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.fieldIndex;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fieldIndex",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnionCreateOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.fieldIndex.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> UnionCreateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "fieldIndex")
      return prop.fieldIndex;
  return std::nullopt;
}

void UnionCreateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "fieldIndex") {
       prop.fieldIndex = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fieldIndex)>>(value);
       return;
    }
}

void UnionCreateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.fieldIndex) attrs.append("fieldIndex", prop.fieldIndex);
}

::llvm::LogicalResult UnionCreateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldIndexAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW15(attr, "fieldIndex", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UnionCreateOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.fieldIndex)))
    return ::mlir::failure();
  return ::mlir::success();
}

void UnionCreateOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.fieldIndex);
}

uint32_t UnionCreateOp::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}

void UnionCreateOp::setFieldIndex(uint32_t attrValue) {
  getProperties().fieldIndex = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type unionType, StringAttr fieldName, Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(unionType)>(unionType), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, Type unionType, StringAttr fieldName, Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(unionType)>(unionType), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type unionType, StringRef fieldName, Value input) {
      build(odsBuilder, odsState, unionType, odsBuilder.getStringAttr(fieldName), input);
    
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Type unionType, StringRef fieldName, Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(unionType)>(unionType), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, Type unionType, StringRef fieldName, Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(unionType)>(unionType), std::forward<decltype(fieldName)>(fieldName), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  odsState.addTypes(result);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  odsState.addTypes(result);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fieldIndex)>(fieldIndex), std::forward<decltype(input)>(input));
}

void UnionCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<UnionCreateOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnionCreateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnionCreateOp UnionCreateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnionCreateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionCreateOp UnionCreateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnionCreateOp::verifyInvariantsImpl() {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitOpError("requires attribute 'fieldIndex'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW15(*this, tblgen_fieldIndex, "fieldIndex")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW14(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnionCreateOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult UnionCreateOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.fieldIndex;
    auto fieldIndexAttrName = ::mlir::StringAttr::get(ctx, "fieldIndex");
    auto attr = dict.get(fieldIndexAttrName);
    usedKeys.insert(fieldIndexAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for fieldIndex in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void UnionCreateOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::UnionCreateOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::UnionCreateOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::UnionExtractOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnionExtractOpGenericAdaptorBase::UnionExtractOpGenericAdaptorBase(UnionExtractOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t UnionExtractOpGenericAdaptorBase::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
UnionExtractOpAdaptor::UnionExtractOpAdaptor(UnionExtractOp op) : UnionExtractOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnionExtractOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitError(loc, "'hw.union_extract' op requires attribute 'fieldIndex'");

  if (tblgen_fieldIndex && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_fieldIndex))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_fieldIndex).getType().isSignlessInteger(32)))))
    return emitError(loc, "'hw.union_extract' op attribute 'fieldIndex' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult UnionExtractOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.fieldIndex;
       auto attr = dict.get("fieldIndex");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute UnionExtractOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.fieldIndex;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fieldIndex",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnionExtractOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.fieldIndex.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> UnionExtractOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "fieldIndex")
      return prop.fieldIndex;
  return std::nullopt;
}

void UnionExtractOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "fieldIndex") {
       prop.fieldIndex = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fieldIndex)>>(value);
       return;
    }
}

void UnionExtractOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.fieldIndex) attrs.append("fieldIndex", prop.fieldIndex);
}

::llvm::LogicalResult UnionExtractOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFieldIndexAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW15(attr, "fieldIndex", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UnionExtractOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.fieldIndex)))
    return ::mlir::failure();
  return ::mlir::success();
}

void UnionExtractOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.fieldIndex);
}

uint32_t UnionExtractOp::getFieldIndex() {
  auto attr = getFieldIndexAttr();
  return attr.getValue().getZExtValue();
}

void UnionExtractOp::setFieldIndex(uint32_t attrValue) {
  getProperties().fieldIndex = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName) {
      build(odsBuilder, odsState, input, odsBuilder.getStringAttr(fieldName));
    
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldName)>(fieldName));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  odsState.addTypes(result);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(UnionExtractOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = fieldIndex;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  odsState.addTypes(result);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint32_t fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(UnionExtractOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint32_t fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint32_t fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().fieldIndex = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), fieldIndex);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(fieldIndex)>(fieldIndex));
}

void UnionExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<UnionExtractOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<UnionExtractOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnionExtractOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnionExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void UnionExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnionExtractOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnionExtractOp UnionExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnionExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnionExtractOp UnionExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnionExtractOp::verifyInvariantsImpl() {
  auto tblgen_fieldIndex = getProperties().fieldIndex; (void)tblgen_fieldIndex;
  if (!tblgen_fieldIndex) return emitOpError("requires attribute 'fieldIndex'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW15(*this, tblgen_fieldIndex, "fieldIndex")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW14(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnionExtractOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void UnionExtractOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult UnionExtractOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.fieldIndex;
    auto fieldIndexAttrName = ::mlir::StringAttr::get(ctx, "fieldIndex");
    auto attr = dict.get(fieldIndexAttrName);
    usedKeys.insert(fieldIndexAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for fieldIndex in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fieldIndex` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void UnionExtractOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::UnionExtractOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::UnionExtractOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::WireOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WireOpGenericAdaptorBase::WireOpGenericAdaptorBase(WireOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > WireOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> WireOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}


} // namespace detail
WireOpAdaptor::WireOpAdaptor(WireOp op) : WireOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WireOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'hw.wire' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'hw.wire' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");
  return ::mlir::success();
}

::llvm::LogicalResult WireOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.name;
       auto attr = dict.get("name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute WireOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WireOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> WireOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void WireOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void WireOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult WireOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW12(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_HW4(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult WireOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void WireOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
}

::std::optional< ::llvm::StringRef > WireOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> WireOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

void WireOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value input, const StringAttrOrRef &name, hw::InnerSymAttr innerSym) {
      auto *context = odsBuilder.getContext();
      odsState.addOperands(input);
      if (auto attr = name.get(context))
        odsState.addAttribute(getNameAttrName(odsState.name), attr);
      if (innerSym)
        odsState.addAttribute(getInnerSymAttrName(odsState.name), innerSym);
      odsState.addTypes(input.getType());
    
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value input, const StringAttrOrRef &name, hw::InnerSymAttr innerSym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(innerSym)>(innerSym));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value input, const StringAttrOrRef &name, hw::InnerSymAttr innerSym) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(innerSym)>(innerSym));
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(result);
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(WireOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym));
}

void WireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<WireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<WireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(WireOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void WireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(WireOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

WireOp WireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireOp WireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WireOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW4(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_HW12(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_HW7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WireOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void WireOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult WireOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult WireOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<WireOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<WireOp::Properties>().name = nameAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(inputRawType))
    return ::mlir::failure();
  result.addTypes(inputTypes[0]);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void WireOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  _odsPrinter << ' ';
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::WireOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::detail::WireOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

