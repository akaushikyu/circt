/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Synth.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::synth {

// timing arc polarity
enum class PolarityKind : uint32_t {
  Positive = 0,
  Negative = 1,
};

::std::optional<PolarityKind> symbolizePolarityKind(uint32_t);
::llvm::StringRef stringifyPolarityKind(PolarityKind);
::std::optional<PolarityKind> symbolizePolarityKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPolarityKind() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(PolarityKind enumValue) {
  return stringifyPolarityKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PolarityKind> symbolizeEnum<PolarityKind>(::llvm::StringRef str) {
  return symbolizePolarityKind(str);
}

class PolarityKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = PolarityKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static PolarityKindAttr get(::mlir::MLIRContext *context, PolarityKind val);
  PolarityKind getValue() const;
};

} // namespace circt::synth

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::synth::PolarityKind, circt::synth::PolarityKind> {
  template <typename ParserT>
  static FailureOr<circt::synth::PolarityKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for timing arc polarity");

    // Symbolize the keyword.
    if (::std::optional<circt::synth::PolarityKind> attr = circt::synth::symbolizeEnum<circt::synth::PolarityKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [positive, negative] for timing arc polarity, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::synth::PolarityKind>, std::optional<circt::synth::PolarityKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::synth::PolarityKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"positive", "negative"})))
      return std::optional<circt::synth::PolarityKind>{};

    // Symbolize the keyword.
    if (::std::optional<circt::synth::PolarityKind> attr = circt::synth::symbolizeEnum<circt::synth::PolarityKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [positive, negative] for timing arc polarity, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::synth::PolarityKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::synth::PolarityKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::synth::PolarityKind getEmptyKey() {
    return static_cast<circt::synth::PolarityKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::synth::PolarityKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::synth::PolarityKind &lhs, const circt::synth::PolarityKind &rhs) {
    return lhs == rhs;
  }
};
}

