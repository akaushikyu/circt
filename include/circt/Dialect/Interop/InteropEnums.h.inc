/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Interop.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// interface through which interoperability is achieved
enum class InteropMechanism : uint32_t {
  CFFI = 0,
  CPP = 1,
};

::std::optional<InteropMechanism> symbolizeInteropMechanism(uint32_t);
::llvm::StringRef stringifyInteropMechanism(InteropMechanism);
::std::optional<InteropMechanism> symbolizeInteropMechanism(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForInteropMechanism() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(InteropMechanism enumValue) {
  return stringifyInteropMechanism(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<InteropMechanism> symbolizeEnum<InteropMechanism>(::llvm::StringRef str) {
  return symbolizeInteropMechanism(str);
}

class InteropMechanismAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = InteropMechanism;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static InteropMechanismAttr get(::mlir::MLIRContext *context, InteropMechanism val);
  InteropMechanism getValue() const;
};

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::InteropMechanism, ::InteropMechanism> {
  template <typename ParserT>
  static FailureOr<::InteropMechanism> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for interface through which interoperability is achieved");

    // Symbolize the keyword.
    if (::std::optional<::InteropMechanism> attr = ::symbolizeEnum<::InteropMechanism>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [cffi, cpp] for interface through which interoperability is achieved, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::InteropMechanism>, std::optional<::InteropMechanism>> {
  template <typename ParserT>
  static FailureOr<std::optional<::InteropMechanism>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"cffi", "cpp"})))
      return std::optional<::InteropMechanism>{};

    // Symbolize the keyword.
    if (::std::optional<::InteropMechanism> attr = ::symbolizeEnum<::InteropMechanism>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [cffi, cpp] for interface through which interoperability is achieved, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::InteropMechanism value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::InteropMechanism> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::InteropMechanism getEmptyKey() {
    return static_cast<::InteropMechanism>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::InteropMechanism &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::InteropMechanism &lhs, const ::InteropMechanism &rhs) {
    return lhs == rhs;
  }
};
}

