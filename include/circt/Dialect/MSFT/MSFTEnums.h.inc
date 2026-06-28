/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// Type of device at physical location
enum class PrimitiveType : uint32_t {
  M20K = 1,
  DSP = 2,
  FF = 3,
};

::std::optional<PrimitiveType> symbolizePrimitiveType(uint32_t);
::llvm::StringRef stringifyPrimitiveType(PrimitiveType);
::std::optional<PrimitiveType> symbolizePrimitiveType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPrimitiveType() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(PrimitiveType enumValue) {
  return stringifyPrimitiveType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PrimitiveType> symbolizeEnum<PrimitiveType>(::llvm::StringRef str) {
  return symbolizePrimitiveType(str);
}

class PrimitiveTypeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = PrimitiveType;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static PrimitiveTypeAttr get(::mlir::MLIRContext *context, PrimitiveType val);
  PrimitiveType getValue() const;
};

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::PrimitiveType, ::PrimitiveType> {
  template <typename ParserT>
  static FailureOr<::PrimitiveType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Type of device at physical location");

    // Symbolize the keyword.
    if (::std::optional<::PrimitiveType> attr = ::symbolizeEnum<::PrimitiveType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [M20K, DSP, FF] for Type of device at physical location, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::PrimitiveType>, std::optional<::PrimitiveType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::PrimitiveType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"M20K", "DSP", "FF"})))
      return std::optional<::PrimitiveType>{};

    // Symbolize the keyword.
    if (::std::optional<::PrimitiveType> attr = ::symbolizeEnum<::PrimitiveType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [M20K, DSP, FF] for Type of device at physical location, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::PrimitiveType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::PrimitiveType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::PrimitiveType getEmptyKey() {
    return static_cast<::PrimitiveType>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::PrimitiveType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::PrimitiveType &lhs, const ::PrimitiveType &rhs) {
    return lhs == rhs;
  }
};
}

