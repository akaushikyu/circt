/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// C++ member access kind
enum class MemberAccessKind : uint32_t {
  Dot = 0,
  Arrow = 1,
};

::std::optional<MemberAccessKind> symbolizeMemberAccessKind(uint32_t);
::llvm::StringRef stringifyMemberAccessKind(MemberAccessKind);
::std::optional<MemberAccessKind> symbolizeMemberAccessKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForMemberAccessKind() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(MemberAccessKind enumValue) {
  return stringifyMemberAccessKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<MemberAccessKind> symbolizeEnum<MemberAccessKind>(::llvm::StringRef str) {
  return symbolizeMemberAccessKind(str);
}

class MemberAccessKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = MemberAccessKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static MemberAccessKindAttr get(::mlir::MLIRContext *context, MemberAccessKind val);
  MemberAccessKind getValue() const;
};

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::MemberAccessKind, ::MemberAccessKind> {
  template <typename ParserT>
  static FailureOr<::MemberAccessKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for C++ member access kind");

    // Symbolize the keyword.
    if (::std::optional<::MemberAccessKind> attr = ::symbolizeEnum<::MemberAccessKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [dot, arrow] for C++ member access kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::MemberAccessKind>, std::optional<::MemberAccessKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::MemberAccessKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"dot", "arrow"})))
      return std::optional<::MemberAccessKind>{};

    // Symbolize the keyword.
    if (::std::optional<::MemberAccessKind> attr = ::symbolizeEnum<::MemberAccessKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [dot, arrow] for C++ member access kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::MemberAccessKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::MemberAccessKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::MemberAccessKind getEmptyKey() {
    return static_cast<::MemberAccessKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::MemberAccessKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::MemberAccessKind &lhs, const ::MemberAccessKind &rhs) {
    return lhs == rhs;
  }
};
}

