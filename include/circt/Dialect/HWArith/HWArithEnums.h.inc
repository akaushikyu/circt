/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWArith.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hwarith {

// hwarith.icmp comparison predicate
enum class ICmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
  lt = 2,
  ge = 3,
  le = 4,
  gt = 5,
};

::std::optional<ICmpPredicate> symbolizeICmpPredicate(uint64_t);
::llvm::StringRef stringifyICmpPredicate(ICmpPredicate);
::std::optional<ICmpPredicate> symbolizeICmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForICmpPredicate() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(ICmpPredicate enumValue) {
  return stringifyICmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ICmpPredicate> symbolizeEnum<ICmpPredicate>(::llvm::StringRef str) {
  return symbolizeICmpPredicate(str);
}

class ICmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ICmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ICmpPredicateAttr get(::mlir::MLIRContext *context, ICmpPredicate val);
  ICmpPredicate getValue() const;
};

} // namespace circt::hwarith

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::hwarith::ICmpPredicate, circt::hwarith::ICmpPredicate> {
  template <typename ParserT>
  static FailureOr<circt::hwarith::ICmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for hwarith.icmp comparison predicate");

    // Symbolize the keyword.
    if (::std::optional<circt::hwarith::ICmpPredicate> attr = circt::hwarith::symbolizeEnum<circt::hwarith::ICmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne, lt, ge, le, gt] for hwarith.icmp comparison predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::hwarith::ICmpPredicate>, std::optional<circt::hwarith::ICmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::hwarith::ICmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"eq", "ne", "lt", "ge", "le", "gt"})))
      return std::optional<circt::hwarith::ICmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::hwarith::ICmpPredicate> attr = circt::hwarith::symbolizeEnum<circt::hwarith::ICmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne, lt, ge, le, gt] for hwarith.icmp comparison predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::hwarith::ICmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::hwarith::ICmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline circt::hwarith::ICmpPredicate getEmptyKey() {
    return static_cast<circt::hwarith::ICmpPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::hwarith::ICmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const circt::hwarith::ICmpPredicate &lhs, const circt::hwarith::ICmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

