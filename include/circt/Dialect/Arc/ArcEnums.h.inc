/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Arc.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

// arc.zero_count predicate
enum class ZeroCountPredicate : uint32_t {
  leading = 0,
  trailing = 1,
};

::std::optional<ZeroCountPredicate> symbolizeZeroCountPredicate(uint32_t);
::llvm::StringRef stringifyZeroCountPredicate(ZeroCountPredicate);
::std::optional<ZeroCountPredicate> symbolizeZeroCountPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForZeroCountPredicate() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(ZeroCountPredicate enumValue) {
  return stringifyZeroCountPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ZeroCountPredicate> symbolizeEnum<ZeroCountPredicate>(::llvm::StringRef str) {
  return symbolizeZeroCountPredicate(str);
}

class ZeroCountPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ZeroCountPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ZeroCountPredicateAttr get(::mlir::MLIRContext *context, ZeroCountPredicate val);
  ZeroCountPredicate getValue() const;
};

} // namespace circt::arc

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::arc::ZeroCountPredicate, circt::arc::ZeroCountPredicate> {
  template <typename ParserT>
  static FailureOr<circt::arc::ZeroCountPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for arc.zero_count predicate");

    // Symbolize the keyword.
    if (::std::optional<circt::arc::ZeroCountPredicate> attr = circt::arc::symbolizeEnum<circt::arc::ZeroCountPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [leading, trailing] for arc.zero_count predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::arc::ZeroCountPredicate>, std::optional<circt::arc::ZeroCountPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::arc::ZeroCountPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"leading", "trailing"})))
      return std::optional<circt::arc::ZeroCountPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::arc::ZeroCountPredicate> attr = circt::arc::symbolizeEnum<circt::arc::ZeroCountPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [leading, trailing] for arc.zero_count predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::arc::ZeroCountPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::arc::ZeroCountPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::arc::ZeroCountPredicate getEmptyKey() {
    return static_cast<circt::arc::ZeroCountPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::arc::ZeroCountPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::arc::ZeroCountPredicate &lhs, const circt::arc::ZeroCountPredicate &rhs) {
    return lhs == rhs;
  }
};
}

