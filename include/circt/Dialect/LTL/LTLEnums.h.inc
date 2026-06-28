/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LTL.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::ltl {

// clock edge
enum class ClockEdge : uint32_t {
  Pos = 0,
  Neg = 1,
  Both = 2,
};

::std::optional<ClockEdge> symbolizeClockEdge(uint32_t);
::llvm::StringRef stringifyClockEdge(ClockEdge);
::std::optional<ClockEdge> symbolizeClockEdge(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClockEdge() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ClockEdge enumValue) {
  return stringifyClockEdge(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClockEdge> symbolizeEnum<ClockEdge>(::llvm::StringRef str) {
  return symbolizeClockEdge(str);
}

class ClockEdgeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ClockEdge;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ClockEdgeAttr get(::mlir::MLIRContext *context, ClockEdge val);
  ClockEdge getValue() const;
};

} // namespace circt::ltl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::ltl::ClockEdge, circt::ltl::ClockEdge> {
  template <typename ParserT>
  static FailureOr<circt::ltl::ClockEdge> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for clock edge");

    // Symbolize the keyword.
    if (::std::optional<circt::ltl::ClockEdge> attr = circt::ltl::symbolizeEnum<circt::ltl::ClockEdge>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for clock edge, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::ltl::ClockEdge>, std::optional<circt::ltl::ClockEdge>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::ltl::ClockEdge>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"posedge", "negedge", "edge"})))
      return std::optional<circt::ltl::ClockEdge>{};

    // Symbolize the keyword.
    if (::std::optional<circt::ltl::ClockEdge> attr = circt::ltl::symbolizeEnum<circt::ltl::ClockEdge>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for clock edge, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::ltl::ClockEdge value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::ltl::ClockEdge> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::ltl::ClockEdge getEmptyKey() {
    return static_cast<circt::ltl::ClockEdge>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::ltl::ClockEdge &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::ltl::ClockEdge &lhs, const circt::ltl::ClockEdge &rhs) {
    return lhs == rhs;
  }
};
}

