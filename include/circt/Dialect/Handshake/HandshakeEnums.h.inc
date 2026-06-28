/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Handshake.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// BufferOp seq or fifo
enum class BufferTypeEnum : uint32_t {
  seq = 0,
  fifo = 1,
};

::std::optional<BufferTypeEnum> symbolizeBufferTypeEnum(uint32_t);
::llvm::StringRef stringifyBufferTypeEnum(BufferTypeEnum);
::std::optional<BufferTypeEnum> symbolizeBufferTypeEnum(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForBufferTypeEnum() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(BufferTypeEnum enumValue) {
  return stringifyBufferTypeEnum(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<BufferTypeEnum> symbolizeEnum<BufferTypeEnum>(::llvm::StringRef str) {
  return symbolizeBufferTypeEnum(str);
}

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::BufferTypeEnum, ::BufferTypeEnum> {
  template <typename ParserT>
  static FailureOr<::BufferTypeEnum> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for BufferOp seq or fifo");

    // Symbolize the keyword.
    if (::std::optional<::BufferTypeEnum> attr = ::symbolizeEnum<::BufferTypeEnum>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [seq, fifo] for BufferOp seq or fifo, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::BufferTypeEnum>, std::optional<::BufferTypeEnum>> {
  template <typename ParserT>
  static FailureOr<std::optional<::BufferTypeEnum>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"seq", "fifo"})))
      return std::optional<::BufferTypeEnum>{};

    // Symbolize the keyword.
    if (::std::optional<::BufferTypeEnum> attr = ::symbolizeEnum<::BufferTypeEnum>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [seq, fifo] for BufferOp seq or fifo, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::BufferTypeEnum value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::BufferTypeEnum> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::BufferTypeEnum getEmptyKey() {
    return static_cast<::BufferTypeEnum>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::BufferTypeEnum &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::BufferTypeEnum &lhs, const ::BufferTypeEnum &rhs) {
    return lhs == rhs;
  }
};
}

