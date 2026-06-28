/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ESI.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::esi {

// Direction of channel (see ChannelBundleImpl for details)
enum class ChannelDirection : uint32_t {
  to = 1,
  from = 2,
};

::std::optional<ChannelDirection> symbolizeChannelDirection(uint32_t);
::llvm::StringRef stringifyChannelDirection(ChannelDirection);
::std::optional<ChannelDirection> symbolizeChannelDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForChannelDirection() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ChannelDirection enumValue) {
  return stringifyChannelDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ChannelDirection> symbolizeEnum<ChannelDirection>(::llvm::StringRef str) {
  return symbolizeChannelDirection(str);
}

class ChannelDirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ChannelDirection;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ChannelDirectionAttr get(::mlir::MLIRContext *context, ChannelDirection val);
  ChannelDirection getValue() const;
};

} // namespace circt::esi

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::esi::ChannelDirection, ::circt::esi::ChannelDirection> {
  template <typename ParserT>
  static FailureOr<::circt::esi::ChannelDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Direction of channel (see ChannelBundleImpl for details)");

    // Symbolize the keyword.
    if (::std::optional<::circt::esi::ChannelDirection> attr = ::circt::esi::symbolizeEnum<::circt::esi::ChannelDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [to, from] for Direction of channel (see ChannelBundleImpl for details), got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::esi::ChannelDirection>, std::optional<::circt::esi::ChannelDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::esi::ChannelDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"to", "from"})))
      return std::optional<::circt::esi::ChannelDirection>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::esi::ChannelDirection> attr = ::circt::esi::symbolizeEnum<::circt::esi::ChannelDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [to, from] for Direction of channel (see ChannelBundleImpl for details), got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::esi::ChannelDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::esi::ChannelDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::esi::ChannelDirection getEmptyKey() {
    return static_cast<::circt::esi::ChannelDirection>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::esi::ChannelDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::esi::ChannelDirection &lhs, const ::circt::esi::ChannelDirection &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::esi {

// ESI channel wire signaling standard
enum class ChannelSignaling : uint32_t {
  ValidReady = 0,
  FIFO = 1,
  ValidOnly = 2,
};

::std::optional<ChannelSignaling> symbolizeChannelSignaling(uint32_t);
::llvm::StringRef stringifyChannelSignaling(ChannelSignaling);
::std::optional<ChannelSignaling> symbolizeChannelSignaling(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForChannelSignaling() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ChannelSignaling enumValue) {
  return stringifyChannelSignaling(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ChannelSignaling> symbolizeEnum<ChannelSignaling>(::llvm::StringRef str) {
  return symbolizeChannelSignaling(str);
}

class ChannelSignalingAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ChannelSignaling;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ChannelSignalingAttr get(::mlir::MLIRContext *context, ChannelSignaling val);
  ChannelSignaling getValue() const;
};

} // namespace circt::esi

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::esi::ChannelSignaling, ::circt::esi::ChannelSignaling> {
  template <typename ParserT>
  static FailureOr<::circt::esi::ChannelSignaling> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for ESI channel wire signaling standard");

    // Symbolize the keyword.
    if (::std::optional<::circt::esi::ChannelSignaling> attr = ::circt::esi::symbolizeEnum<::circt::esi::ChannelSignaling>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [ValidReady, FIFO, ValidOnly] for ESI channel wire signaling standard, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::esi::ChannelSignaling>, std::optional<::circt::esi::ChannelSignaling>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::esi::ChannelSignaling>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"ValidReady", "FIFO", "ValidOnly"})))
      return std::optional<::circt::esi::ChannelSignaling>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::esi::ChannelSignaling> attr = ::circt::esi::symbolizeEnum<::circt::esi::ChannelSignaling>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [ValidReady, FIFO, ValidOnly] for ESI channel wire signaling standard, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::esi::ChannelSignaling value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::esi::ChannelSignaling> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::esi::ChannelSignaling getEmptyKey() {
    return static_cast<::circt::esi::ChannelSignaling>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::esi::ChannelSignaling &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::esi::ChannelSignaling &lhs, const ::circt::esi::ChannelSignaling &rhs) {
    return lhs == rhs;
  }
};
}

