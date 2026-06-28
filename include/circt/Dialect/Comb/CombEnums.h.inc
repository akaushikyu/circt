/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Comb.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::comb {

// hw.icmp comparison predicate
enum class ICmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
  slt = 2,
  sle = 3,
  sgt = 4,
  sge = 5,
  ult = 6,
  ule = 7,
  ugt = 8,
  uge = 9,
  ceq = 10,
  cne = 11,
  weq = 12,
  wne = 13,
};

::std::optional<ICmpPredicate> symbolizeICmpPredicate(uint64_t);
::llvm::StringRef stringifyICmpPredicate(ICmpPredicate);
::std::optional<ICmpPredicate> symbolizeICmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForICmpPredicate() {
  return 13;
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

} // namespace circt::comb

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::comb::ICmpPredicate, circt::comb::ICmpPredicate> {
  template <typename ParserT>
  static FailureOr<circt::comb::ICmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for hw.icmp comparison predicate");

    // Symbolize the keyword.
    if (::std::optional<circt::comb::ICmpPredicate> attr = circt::comb::symbolizeEnum<circt::comb::ICmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne, slt, sle, sgt, sge, ult, ule, ugt, uge, ceq, cne, weq, wne] for hw.icmp comparison predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::comb::ICmpPredicate>, std::optional<circt::comb::ICmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::comb::ICmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"eq", "ne", "slt", "sle", "sgt", "sge", "ult", "ule", "ugt", "uge", "ceq", "cne", "weq", "wne"})))
      return std::optional<circt::comb::ICmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::comb::ICmpPredicate> attr = circt::comb::symbolizeEnum<circt::comb::ICmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne, slt, sle, sgt, sge, ult, ule, ugt, uge, ceq, cne, weq, wne] for hw.icmp comparison predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::comb::ICmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::comb::ICmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline circt::comb::ICmpPredicate getEmptyKey() {
    return static_cast<circt::comb::ICmpPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::comb::ICmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const circt::comb::ICmpPredicate &lhs, const circt::comb::ICmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

