/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OMEnums.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::om {

// object model target kind
enum class TargetKind : uint32_t {
  DontTouch = 0,
  Instance = 1,
  MemberInstance = 2,
  MemberReference = 3,
  Reference = 4,
};

::std::optional<TargetKind> symbolizeTargetKind(uint32_t);
::llvm::StringRef stringifyTargetKind(TargetKind);
::std::optional<TargetKind> symbolizeTargetKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForTargetKind() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(TargetKind enumValue) {
  return stringifyTargetKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TargetKind> symbolizeEnum<TargetKind>(::llvm::StringRef str) {
  return symbolizeTargetKind(str);
}

class TargetKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = TargetKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static TargetKindAttr get(::mlir::MLIRContext *context, TargetKind val);
  TargetKind getValue() const;
};

} // namespace circt::om

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::om::TargetKind, ::circt::om::TargetKind> {
  template <typename ParserT>
  static FailureOr<::circt::om::TargetKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for object model target kind");

    // Symbolize the keyword.
    if (::std::optional<::circt::om::TargetKind> attr = ::circt::om::symbolizeEnum<::circt::om::TargetKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [dont_touch, instance, member_instance, member_reference, reference] for object model target kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::om::TargetKind>, std::optional<::circt::om::TargetKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::om::TargetKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"dont_touch", "instance", "member_instance", "member_reference", "reference"})))
      return std::optional<::circt::om::TargetKind>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::om::TargetKind> attr = ::circt::om::symbolizeEnum<::circt::om::TargetKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [dont_touch, instance, member_instance, member_reference, reference] for object model target kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::om::TargetKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::om::TargetKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::om::TargetKind getEmptyKey() {
    return static_cast<::circt::om::TargetKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::om::TargetKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::om::TargetKind &lhs, const ::circt::om::TargetKind &rhs) {
    return lhs == rhs;
  }
};
}

