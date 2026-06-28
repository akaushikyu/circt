/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Seq.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::seq {

// clock constant
enum class ClockConst : uint32_t {
  Low = 0,
  High = 1,
};

::std::optional<ClockConst> symbolizeClockConst(uint32_t);
::llvm::StringRef stringifyClockConst(ClockConst);
::std::optional<ClockConst> symbolizeClockConst(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForClockConst() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(ClockConst enumValue) {
  return stringifyClockConst(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ClockConst> symbolizeEnum<ClockConst>(::llvm::StringRef str) {
  return symbolizeClockConst(str);
}

} // namespace circt::seq

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::seq::ClockConst, circt::seq::ClockConst> {
  template <typename ParserT>
  static FailureOr<circt::seq::ClockConst> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for clock constant");

    // Symbolize the keyword.
    if (::std::optional<circt::seq::ClockConst> attr = circt::seq::symbolizeEnum<circt::seq::ClockConst>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [low, high] for clock constant, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::seq::ClockConst>, std::optional<circt::seq::ClockConst>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::seq::ClockConst>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"low", "high"})))
      return std::optional<circt::seq::ClockConst>{};

    // Symbolize the keyword.
    if (::std::optional<circt::seq::ClockConst> attr = circt::seq::symbolizeEnum<circt::seq::ClockConst>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [low, high] for clock constant, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::seq::ClockConst value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::seq::ClockConst> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::seq::ClockConst getEmptyKey() {
    return static_cast<circt::seq::ClockConst>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::seq::ClockConst &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::seq::ClockConst &lhs, const circt::seq::ClockConst &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::seq {

// Read-Under-Write Behavior
enum class RUW : uint32_t {
  Undefined = 0,
  Old = 1,
  New = 2,
};

::std::optional<RUW> symbolizeRUW(uint32_t);
::llvm::StringRef stringifyRUW(RUW);
::std::optional<RUW> symbolizeRUW(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForRUW() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(RUW enumValue) {
  return stringifyRUW(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<RUW> symbolizeEnum<RUW>(::llvm::StringRef str) {
  return symbolizeRUW(str);
}

class RUWAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = RUW;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static RUWAttr get(::mlir::MLIRContext *context, RUW val);
  RUW getValue() const;
};

} // namespace circt::seq

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::seq::RUW, circt::seq::RUW> {
  template <typename ParserT>
  static FailureOr<circt::seq::RUW> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Read-Under-Write Behavior");

    // Symbolize the keyword.
    if (::std::optional<circt::seq::RUW> attr = circt::seq::symbolizeEnum<circt::seq::RUW>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [undefined, old, new] for Read-Under-Write Behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::seq::RUW>, std::optional<circt::seq::RUW>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::seq::RUW>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"undefined", "old", "new"})))
      return std::optional<circt::seq::RUW>{};

    // Symbolize the keyword.
    if (::std::optional<circt::seq::RUW> attr = circt::seq::symbolizeEnum<circt::seq::RUW>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [undefined, old, new] for Read-Under-Write Behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::seq::RUW value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::seq::RUW> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::seq::RUW getEmptyKey() {
    return static_cast<circt::seq::RUW>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::seq::RUW &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::seq::RUW &lhs, const circt::seq::RUW &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::seq {

// Write-Under-Write Behavior
enum class WUW : uint32_t {
  Undefined = 0,
  PortOrder = 1,
};

::std::optional<WUW> symbolizeWUW(uint32_t);
::llvm::StringRef stringifyWUW(WUW);
::std::optional<WUW> symbolizeWUW(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForWUW() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(WUW enumValue) {
  return stringifyWUW(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<WUW> symbolizeEnum<WUW>(::llvm::StringRef str) {
  return symbolizeWUW(str);
}

class WUWAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = WUW;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static WUWAttr get(::mlir::MLIRContext *context, WUW val);
  WUW getValue() const;
};

} // namespace circt::seq

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::seq::WUW, circt::seq::WUW> {
  template <typename ParserT>
  static FailureOr<circt::seq::WUW> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Write-Under-Write Behavior");

    // Symbolize the keyword.
    if (::std::optional<circt::seq::WUW> attr = circt::seq::symbolizeEnum<circt::seq::WUW>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [undefined, port_order] for Write-Under-Write Behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::seq::WUW>, std::optional<circt::seq::WUW>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::seq::WUW>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"undefined", "port_order"})))
      return std::optional<circt::seq::WUW>{};

    // Symbolize the keyword.
    if (::std::optional<circt::seq::WUW> attr = circt::seq::symbolizeEnum<circt::seq::WUW>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [undefined, port_order] for Write-Under-Write Behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::seq::WUW value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::seq::WUW> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::seq::WUW getEmptyKey() {
    return static_cast<circt::seq::WUW>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::seq::WUW &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::seq::WUW &lhs, const circt::seq::WUW &rhs) {
    return lhs == rhs;
  }
};
}

