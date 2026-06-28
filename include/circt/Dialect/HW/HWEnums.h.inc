/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWEnums.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

// edge control trigger
enum class EventControl : uint32_t {
  AtPosEdge = 0,
  AtNegEdge = 1,
  AtEdge = 2,
};

::std::optional<EventControl> symbolizeEventControl(uint32_t);
::llvm::StringRef stringifyEventControl(EventControl);
::std::optional<EventControl> symbolizeEventControl(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForEventControl() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(EventControl enumValue) {
  return stringifyEventControl(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<EventControl> symbolizeEnum<EventControl>(::llvm::StringRef str) {
  return symbolizeEventControl(str);
}

class EventControlAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = EventControl;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static EventControlAttr get(::mlir::MLIRContext *context, EventControl val);
  EventControl getValue() const;
};

} // namespace circt::hw

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::hw::EventControl, circt::hw::EventControl> {
  template <typename ParserT>
  static FailureOr<circt::hw::EventControl> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for edge control trigger");

    // Symbolize the keyword.
    if (::std::optional<circt::hw::EventControl> attr = circt::hw::symbolizeEnum<circt::hw::EventControl>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::hw::EventControl>, std::optional<circt::hw::EventControl>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::hw::EventControl>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"posedge", "negedge", "edge"})))
      return std::optional<circt::hw::EventControl>{};

    // Symbolize the keyword.
    if (::std::optional<circt::hw::EventControl> attr = circt::hw::symbolizeEnum<circt::hw::EventControl>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::hw::EventControl value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::hw::EventControl> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::hw::EventControl getEmptyKey() {
    return static_cast<circt::hw::EventControl>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::hw::EventControl &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::hw::EventControl &lhs, const circt::hw::EventControl &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::hw {

// Parameter Expression Opcode
enum class PEO : uint32_t {
  Add = 0,
  Mul = 1,
  And = 2,
  Or = 3,
  Xor = 4,
  Shl = 5,
  ShrU = 6,
  ShrS = 7,
  DivU = 8,
  DivS = 9,
  ModU = 10,
  ModS = 11,
  CLog2 = 12,
  StrConcat = 13,
};

::std::optional<PEO> symbolizePEO(uint32_t);
::llvm::StringRef stringifyPEO(PEO);
::std::optional<PEO> symbolizePEO(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForPEO() {
  return 13;
}


inline ::llvm::StringRef stringifyEnum(PEO enumValue) {
  return stringifyPEO(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<PEO> symbolizeEnum<PEO>(::llvm::StringRef str) {
  return symbolizePEO(str);
}

class PEOAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = PEO;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static PEOAttr get(::mlir::MLIRContext *context, PEO val);
  PEO getValue() const;
};

} // namespace circt::hw

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::hw::PEO, circt::hw::PEO> {
  template <typename ParserT>
  static FailureOr<circt::hw::PEO> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Parameter Expression Opcode");

    // Symbolize the keyword.
    if (::std::optional<circt::hw::PEO> attr = circt::hw::symbolizeEnum<circt::hw::PEO>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [add, mul, and, or, xor, shl, shru, shrs, divu, divs, modu, mods, clog2, str.concat] for Parameter Expression Opcode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::hw::PEO>, std::optional<circt::hw::PEO>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::hw::PEO>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"add", "mul", "and", "or", "xor", "shl", "shru", "shrs", "divu", "divs", "modu", "mods", "clog2", "str.concat"})))
      return std::optional<circt::hw::PEO>{};

    // Symbolize the keyword.
    if (::std::optional<circt::hw::PEO> attr = circt::hw::symbolizeEnum<circt::hw::PEO>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [add, mul, and, or, xor, shl, shru, shrs, divu, divs, modu, mods, clog2, str.concat] for Parameter Expression Opcode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::hw::PEO value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::hw::PEO> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::hw::PEO getEmptyKey() {
    return static_cast<circt::hw::PEO>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::hw::PEO &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::hw::PEO &lhs, const circt::hw::PEO &rhs) {
    return lhs == rhs;
  }
};
}

