/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::kanagawa {

// Kanagawa port direction
enum class Direction : uint32_t {
  Input = 0,
  Output = 1,
};

::std::optional<Direction> symbolizeDirection(uint32_t);
::llvm::StringRef stringifyDirection(Direction);
::std::optional<Direction> symbolizeDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDirection() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(Direction enumValue) {
  return stringifyDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Direction> symbolizeEnum<Direction>(::llvm::StringRef str) {
  return symbolizeDirection(str);
}

class DirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Direction;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DirectionAttr get(::mlir::MLIRContext *context, Direction val);
  Direction getValue() const;
};

} // namespace circt::kanagawa

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::kanagawa::Direction, ::circt::kanagawa::Direction> {
  template <typename ParserT>
  static FailureOr<::circt::kanagawa::Direction> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Kanagawa port direction");

    // Symbolize the keyword.
    if (::std::optional<::circt::kanagawa::Direction> attr = ::circt::kanagawa::symbolizeEnum<::circt::kanagawa::Direction>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [in, out] for Kanagawa port direction, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::kanagawa::Direction>, std::optional<::circt::kanagawa::Direction>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::kanagawa::Direction>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"in", "out"})))
      return std::optional<::circt::kanagawa::Direction>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::kanagawa::Direction> attr = ::circt::kanagawa::symbolizeEnum<::circt::kanagawa::Direction>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [in, out] for Kanagawa port direction, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::kanagawa::Direction value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::kanagawa::Direction> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::kanagawa::Direction getEmptyKey() {
    return static_cast<::circt::kanagawa::Direction>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::kanagawa::Direction &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::kanagawa::Direction &lhs, const ::circt::kanagawa::Direction &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::kanagawa {

// path direction
enum class PathDirection : uint32_t {
  Parent = 0,
  Child = 1,
};

::std::optional<PathDirection> symbolizePathDirection(uint32_t);
::llvm::StringRef stringifyPathDirection(PathDirection);
::std::optional<PathDirection> symbolizePathDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPathDirection() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(PathDirection enumValue) {
  return stringifyPathDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PathDirection> symbolizeEnum<PathDirection>(::llvm::StringRef str) {
  return symbolizePathDirection(str);
}

class PathDirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = PathDirection;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static PathDirectionAttr get(::mlir::MLIRContext *context, PathDirection val);
  PathDirection getValue() const;
};

} // namespace circt::kanagawa

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::kanagawa::PathDirection, ::circt::kanagawa::PathDirection> {
  template <typename ParserT>
  static FailureOr<::circt::kanagawa::PathDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for path direction");

    // Symbolize the keyword.
    if (::std::optional<::circt::kanagawa::PathDirection> attr = ::circt::kanagawa::symbolizeEnum<::circt::kanagawa::PathDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [parent, child] for path direction, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::kanagawa::PathDirection>, std::optional<::circt::kanagawa::PathDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::kanagawa::PathDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"parent", "child"})))
      return std::optional<::circt::kanagawa::PathDirection>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::kanagawa::PathDirection> attr = ::circt::kanagawa::symbolizeEnum<::circt::kanagawa::PathDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [parent, child] for path direction, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::kanagawa::PathDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::kanagawa::PathDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::kanagawa::PathDirection getEmptyKey() {
    return static_cast<::circt::kanagawa::PathDirection>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::kanagawa::PathDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::kanagawa::PathDirection &lhs, const ::circt::kanagawa::PathDirection &rhs) {
    return lhs == rhs;
  }
};
}

