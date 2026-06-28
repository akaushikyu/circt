/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ArcPasses.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

// Lowering Mode
enum class LowerVectorizationsModeEnum : uint32_t {
  Boundary = 0,
  Body = 1,
  InlineBody = 2,
  Full = 3,
};

::std::optional<LowerVectorizationsModeEnum> symbolizeLowerVectorizationsModeEnum(uint32_t);
::llvm::StringRef stringifyLowerVectorizationsModeEnum(LowerVectorizationsModeEnum);
::std::optional<LowerVectorizationsModeEnum> symbolizeLowerVectorizationsModeEnum(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForLowerVectorizationsModeEnum() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(LowerVectorizationsModeEnum enumValue) {
  return stringifyLowerVectorizationsModeEnum(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<LowerVectorizationsModeEnum> symbolizeEnum<LowerVectorizationsModeEnum>(::llvm::StringRef str) {
  return symbolizeLowerVectorizationsModeEnum(str);
}

class LowerVectorizationsModeEnumAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = LowerVectorizationsModeEnum;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static LowerVectorizationsModeEnumAttr get(::mlir::MLIRContext *context, LowerVectorizationsModeEnum val);
  LowerVectorizationsModeEnum getValue() const;
};

} // namespace circt::arc

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::arc::LowerVectorizationsModeEnum, circt::arc::LowerVectorizationsModeEnum> {
  template <typename ParserT>
  static FailureOr<circt::arc::LowerVectorizationsModeEnum> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Lowering Mode");

    // Symbolize the keyword.
    if (::std::optional<circt::arc::LowerVectorizationsModeEnum> attr = circt::arc::symbolizeEnum<circt::arc::LowerVectorizationsModeEnum>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [boundary, body, \"inline-body\"inline-body, Full] for Lowering Mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::arc::LowerVectorizationsModeEnum>, std::optional<circt::arc::LowerVectorizationsModeEnum>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::arc::LowerVectorizationsModeEnum>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"boundary", "body", "inline-body", "Full"})))
      return std::optional<circt::arc::LowerVectorizationsModeEnum>{};

    // Symbolize the keyword.
    if (::std::optional<circt::arc::LowerVectorizationsModeEnum> attr = circt::arc::symbolizeEnum<circt::arc::LowerVectorizationsModeEnum>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [boundary, body, \"inline-body\"inline-body, Full] for Lowering Mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::arc::LowerVectorizationsModeEnum value) {
  auto valueStr = stringifyEnum(value);
  switch (value) {
  case circt::arc::LowerVectorizationsModeEnum::Boundary:
  case circt::arc::LowerVectorizationsModeEnum::Body:
  case circt::arc::LowerVectorizationsModeEnum::Full:
    break;
  default:
    return p << '"' << valueStr << '"';
  }
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::arc::LowerVectorizationsModeEnum> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::arc::LowerVectorizationsModeEnum getEmptyKey() {
    return static_cast<circt::arc::LowerVectorizationsModeEnum>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::arc::LowerVectorizationsModeEnum &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::arc::LowerVectorizationsModeEnum &lhs, const circt::arc::LowerVectorizationsModeEnum &rhs) {
    return lhs == rhs;
  }
};
}

