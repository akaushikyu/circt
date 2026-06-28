/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Moore.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::moore {

// DPI argument direction
enum class DPIArgDirection : uint32_t {
  In = 0,
  Out = 1,
  InOut = 2,
  Return = 3,
};

::std::optional<DPIArgDirection> symbolizeDPIArgDirection(uint32_t);
::llvm::StringRef stringifyDPIArgDirection(DPIArgDirection);
::std::optional<DPIArgDirection> symbolizeDPIArgDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDPIArgDirection() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(DPIArgDirection enumValue) {
  return stringifyDPIArgDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DPIArgDirection> symbolizeEnum<DPIArgDirection>(::llvm::StringRef str) {
  return symbolizeDPIArgDirection(str);
}

class DPIArgDirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DPIArgDirection;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DPIArgDirectionAttr get(::mlir::MLIRContext *context, DPIArgDirection val);
  DPIArgDirection getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::DPIArgDirection, circt::moore::DPIArgDirection> {
  template <typename ParserT>
  static FailureOr<circt::moore::DPIArgDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for DPI argument direction");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::DPIArgDirection> attr = circt::moore::symbolizeEnum<circt::moore::DPIArgDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [in, out, inout, return] for DPI argument direction, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::DPIArgDirection>, std::optional<circt::moore::DPIArgDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::DPIArgDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"in", "out", "inout", "return"})))
      return std::optional<circt::moore::DPIArgDirection>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::DPIArgDirection> attr = circt::moore::symbolizeEnum<circt::moore::DPIArgDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [in, out, inout, return] for DPI argument direction, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::DPIArgDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::DPIArgDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::DPIArgDirection getEmptyKey() {
    return static_cast<circt::moore::DPIArgDirection>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::DPIArgDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::DPIArgDirection &lhs, const circt::moore::DPIArgDirection &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// assertion deferring mode
enum class DeferAssert : uint32_t {
  Immediate = 0,
  Observed = 1,
  Final = 2,
};

::std::optional<DeferAssert> symbolizeDeferAssert(uint32_t);
::llvm::StringRef stringifyDeferAssert(DeferAssert);
::std::optional<DeferAssert> symbolizeDeferAssert(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDeferAssert() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(DeferAssert enumValue) {
  return stringifyDeferAssert(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DeferAssert> symbolizeEnum<DeferAssert>(::llvm::StringRef str) {
  return symbolizeDeferAssert(str);
}

class DeferAssertAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DeferAssert;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DeferAssertAttr get(::mlir::MLIRContext *context, DeferAssert val);
  DeferAssert getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::DeferAssert, circt::moore::DeferAssert> {
  template <typename ParserT>
  static FailureOr<circt::moore::DeferAssert> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for assertion deferring mode");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::DeferAssert> attr = circt::moore::symbolizeEnum<circt::moore::DeferAssert>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [immediate, observed, final] for assertion deferring mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::DeferAssert>, std::optional<circt::moore::DeferAssert>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::DeferAssert>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"immediate", "observed", "final"})))
      return std::optional<circt::moore::DeferAssert>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::DeferAssert> attr = circt::moore::symbolizeEnum<circt::moore::DeferAssert>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [immediate, observed, final] for assertion deferring mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::DeferAssert value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::DeferAssert> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::DeferAssert getEmptyKey() {
    return static_cast<circt::moore::DeferAssert>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::DeferAssert &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::DeferAssert &lhs, const circt::moore::DeferAssert &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Edge kind
enum class Edge : uint32_t {
  AnyChange = 0,
  PosEdge = 1,
  NegEdge = 2,
  BothEdges = 3,
};

::std::optional<Edge> symbolizeEdge(uint32_t);
::llvm::StringRef stringifyEdge(Edge);
::std::optional<Edge> symbolizeEdge(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForEdge() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(Edge enumValue) {
  return stringifyEdge(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Edge> symbolizeEnum<Edge>(::llvm::StringRef str) {
  return symbolizeEdge(str);
}

class EdgeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Edge;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static EdgeAttr get(::mlir::MLIRContext *context, Edge val);
  Edge getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::Edge, circt::moore::Edge> {
  template <typename ParserT>
  static FailureOr<circt::moore::Edge> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Edge kind");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::Edge> attr = circt::moore::symbolizeEnum<circt::moore::Edge>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [any, posedge, negedge, edge] for Edge kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::Edge>, std::optional<circt::moore::Edge>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::Edge>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"any", "posedge", "negedge", "edge"})))
      return std::optional<circt::moore::Edge>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::Edge> attr = circt::moore::symbolizeEnum<circt::moore::Edge>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [any, posedge, negedge, edge] for Edge kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::Edge value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::Edge> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::Edge getEmptyKey() {
    return static_cast<circt::moore::Edge>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::Edge &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::Edge &lhs, const circt::moore::Edge &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// File open mode
enum class FOpenMode : uint32_t {
  Read = 0,
  Write = 1,
  Append = 2,
  ReadUpdate = 3,
  WriteUpdate = 4,
  AppendUpdate = 5,
};

::std::optional<FOpenMode> symbolizeFOpenMode(uint32_t);
::llvm::StringRef stringifyFOpenMode(FOpenMode);
::std::optional<FOpenMode> symbolizeFOpenMode(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForFOpenMode() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(FOpenMode enumValue) {
  return stringifyFOpenMode(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<FOpenMode> symbolizeEnum<FOpenMode>(::llvm::StringRef str) {
  return symbolizeFOpenMode(str);
}

class FOpenModeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = FOpenMode;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static FOpenModeAttr get(::mlir::MLIRContext *context, FOpenMode val);
  FOpenMode getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::FOpenMode, circt::moore::FOpenMode> {
  template <typename ParserT>
  static FailureOr<circt::moore::FOpenMode> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for File open mode");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::FOpenMode> attr = circt::moore::symbolizeEnum<circt::moore::FOpenMode>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [r, w, a, r_update, w_update, a_update] for File open mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::FOpenMode>, std::optional<circt::moore::FOpenMode>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::FOpenMode>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"r", "w", "a", "r_update", "w_update", "a_update"})))
      return std::optional<circt::moore::FOpenMode>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::FOpenMode> attr = circt::moore::symbolizeEnum<circt::moore::FOpenMode>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [r, w, a, r_update, w_update, a_update] for File open mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::FOpenMode value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::FOpenMode> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::FOpenMode getEmptyKey() {
    return static_cast<circt::moore::FOpenMode>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::FOpenMode &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::FOpenMode &lhs, const circt::moore::FOpenMode &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Integer alignment
enum class IntAlign : uint32_t {
  Right = 0,
  Left = 1,
};

::std::optional<IntAlign> symbolizeIntAlign(uint32_t);
::llvm::StringRef stringifyIntAlign(IntAlign);
::std::optional<IntAlign> symbolizeIntAlign(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForIntAlign() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(IntAlign enumValue) {
  return stringifyIntAlign(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<IntAlign> symbolizeEnum<IntAlign>(::llvm::StringRef str) {
  return symbolizeIntAlign(str);
}

class IntAlignAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = IntAlign;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static IntAlignAttr get(::mlir::MLIRContext *context, IntAlign val);
  IntAlign getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::IntAlign, circt::moore::IntAlign> {
  template <typename ParserT>
  static FailureOr<circt::moore::IntAlign> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Integer alignment");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntAlign> attr = circt::moore::symbolizeEnum<circt::moore::IntAlign>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [right, left] for Integer alignment, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::IntAlign>, std::optional<circt::moore::IntAlign>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::IntAlign>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"right", "left"})))
      return std::optional<circt::moore::IntAlign>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntAlign> attr = circt::moore::symbolizeEnum<circt::moore::IntAlign>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [right, left] for Integer alignment, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::IntAlign value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::IntAlign> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::IntAlign getEmptyKey() {
    return static_cast<circt::moore::IntAlign>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::IntAlign &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::IntAlign &lhs, const circt::moore::IntAlign &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Integer format
enum class IntFormat : uint32_t {
  Decimal = 0,
  Binary = 1,
  Octal = 2,
  HexLower = 3,
  HexUpper = 4,
};

::std::optional<IntFormat> symbolizeIntFormat(uint32_t);
::llvm::StringRef stringifyIntFormat(IntFormat);
::std::optional<IntFormat> symbolizeIntFormat(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForIntFormat() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(IntFormat enumValue) {
  return stringifyIntFormat(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<IntFormat> symbolizeEnum<IntFormat>(::llvm::StringRef str) {
  return symbolizeIntFormat(str);
}

class IntFormatAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = IntFormat;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static IntFormatAttr get(::mlir::MLIRContext *context, IntFormat val);
  IntFormat getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::IntFormat, circt::moore::IntFormat> {
  template <typename ParserT>
  static FailureOr<circt::moore::IntFormat> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Integer format");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntFormat> attr = circt::moore::symbolizeEnum<circt::moore::IntFormat>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [decimal, binary, octal, hex_lower, hex_upper] for Integer format, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::IntFormat>, std::optional<circt::moore::IntFormat>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::IntFormat>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"decimal", "binary", "octal", "hex_lower", "hex_upper"})))
      return std::optional<circt::moore::IntFormat>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntFormat> attr = circt::moore::symbolizeEnum<circt::moore::IntFormat>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [decimal, binary, octal, hex_lower, hex_upper] for Integer format, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::IntFormat value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::IntFormat> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::IntFormat getEmptyKey() {
    return static_cast<circt::moore::IntFormat>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::IntFormat &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::IntFormat &lhs, const circt::moore::IntFormat &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Integer alignment
enum class IntPadding : uint32_t {
  Space = 0,
  Zero = 1,
};

::std::optional<IntPadding> symbolizeIntPadding(uint32_t);
::llvm::StringRef stringifyIntPadding(IntPadding);
::std::optional<IntPadding> symbolizeIntPadding(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForIntPadding() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(IntPadding enumValue) {
  return stringifyIntPadding(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<IntPadding> symbolizeEnum<IntPadding>(::llvm::StringRef str) {
  return symbolizeIntPadding(str);
}

class IntPaddingAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = IntPadding;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static IntPaddingAttr get(::mlir::MLIRContext *context, IntPadding val);
  IntPadding getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::IntPadding, circt::moore::IntPadding> {
  template <typename ParserT>
  static FailureOr<circt::moore::IntPadding> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Integer alignment");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntPadding> attr = circt::moore::symbolizeEnum<circt::moore::IntPadding>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [space, zero] for Integer alignment, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::IntPadding>, std::optional<circt::moore::IntPadding>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::IntPadding>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"space", "zero"})))
      return std::optional<circt::moore::IntPadding>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::IntPadding> attr = circt::moore::symbolizeEnum<circt::moore::IntPadding>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [space, zero] for Integer alignment, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::IntPadding value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::IntPadding> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::IntPadding getEmptyKey() {
    return static_cast<circt::moore::IntPadding>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::IntPadding &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::IntPadding &lhs, const circt::moore::IntPadding &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Join kind
enum class JoinKind : uint32_t {
  Join = 0,
  JoinAny = 1,
  JoinNone = 2,
};

::std::optional<JoinKind> symbolizeJoinKind(uint32_t);
::llvm::StringRef stringifyJoinKind(JoinKind);
::std::optional<JoinKind> symbolizeJoinKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForJoinKind() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(JoinKind enumValue) {
  return stringifyJoinKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<JoinKind> symbolizeEnum<JoinKind>(::llvm::StringRef str) {
  return symbolizeJoinKind(str);
}

class JoinKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = JoinKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static JoinKindAttr get(::mlir::MLIRContext *context, JoinKind val);
  JoinKind getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::JoinKind, circt::moore::JoinKind> {
  template <typename ParserT>
  static FailureOr<circt::moore::JoinKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Join kind");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::JoinKind> attr = circt::moore::symbolizeEnum<circt::moore::JoinKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [join_all, join_any, join_none] for Join kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::JoinKind>, std::optional<circt::moore::JoinKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::JoinKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"join_all", "join_any", "join_none"})))
      return std::optional<circt::moore::JoinKind>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::JoinKind> attr = circt::moore::symbolizeEnum<circt::moore::JoinKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [join_all, join_any, join_none] for Join kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::JoinKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::JoinKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::JoinKind getEmptyKey() {
    return static_cast<circt::moore::JoinKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::JoinKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::JoinKind &lhs, const circt::moore::JoinKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Net type kind
enum class NetKind : uint32_t {
  Supply0 = 0,
  Supply1 = 1,
  Tri = 2,
  TriAnd = 3,
  TriOr = 4,
  TriReg = 5,
  Tri0 = 6,
  Tri1 = 7,
  UWire = 8,
  Wire = 9,
  WAnd = 10,
  WOr = 11,
  Interconnect = 12,
  UserDefined = 13,
  Unknown = 14,
};

::std::optional<NetKind> symbolizeNetKind(uint32_t);
::llvm::StringRef stringifyNetKind(NetKind);
::std::optional<NetKind> symbolizeNetKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForNetKind() {
  return 14;
}


inline ::llvm::StringRef stringifyEnum(NetKind enumValue) {
  return stringifyNetKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<NetKind> symbolizeEnum<NetKind>(::llvm::StringRef str) {
  return symbolizeNetKind(str);
}

class NetKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = NetKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static NetKindAttr get(::mlir::MLIRContext *context, NetKind val);
  NetKind getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::moore::NetKind, ::circt::moore::NetKind> {
  template <typename ParserT>
  static FailureOr<::circt::moore::NetKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Net type kind");

    // Symbolize the keyword.
    if (::std::optional<::circt::moore::NetKind> attr = ::circt::moore::symbolizeEnum<::circt::moore::NetKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [supply0, supply1, tri, triand, trior, trireg, tri0, tri1, uwire, wire, wand, wor, interconnect, userdefined, unknown] for Net type kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::moore::NetKind>, std::optional<::circt::moore::NetKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::moore::NetKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"supply0", "supply1", "tri", "triand", "trior", "trireg", "tri0", "tri1", "uwire", "wire", "wand", "wor", "interconnect", "userdefined", "unknown"})))
      return std::optional<::circt::moore::NetKind>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::moore::NetKind> attr = ::circt::moore::symbolizeEnum<::circt::moore::NetKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [supply0, supply1, tri, triand, trior, trireg, tri0, tri1, uwire, wire, wand, wor, interconnect, userdefined, unknown] for Net type kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::moore::NetKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::moore::NetKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::moore::NetKind getEmptyKey() {
    return static_cast<::circt::moore::NetKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::moore::NetKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::moore::NetKind &lhs, const ::circt::moore::NetKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Procedure kind
enum class ProcedureKind : uint32_t {
  Initial = 0,
  Final = 1,
  Always = 2,
  AlwaysComb = 3,
  AlwaysLatch = 4,
  AlwaysFF = 5,
};

::std::optional<ProcedureKind> symbolizeProcedureKind(uint32_t);
::llvm::StringRef stringifyProcedureKind(ProcedureKind);
::std::optional<ProcedureKind> symbolizeProcedureKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForProcedureKind() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(ProcedureKind enumValue) {
  return stringifyProcedureKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ProcedureKind> symbolizeEnum<ProcedureKind>(::llvm::StringRef str) {
  return symbolizeProcedureKind(str);
}

class ProcedureKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ProcedureKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ProcedureKindAttr get(::mlir::MLIRContext *context, ProcedureKind val);
  ProcedureKind getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::ProcedureKind, circt::moore::ProcedureKind> {
  template <typename ParserT>
  static FailureOr<circt::moore::ProcedureKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Procedure kind");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::ProcedureKind> attr = circt::moore::symbolizeEnum<circt::moore::ProcedureKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [initial, final, always, always_comb, always_latch, always_ff] for Procedure kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::ProcedureKind>, std::optional<circt::moore::ProcedureKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::ProcedureKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"initial", "final", "always", "always_comb", "always_latch", "always_ff"})))
      return std::optional<circt::moore::ProcedureKind>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::ProcedureKind> attr = circt::moore::symbolizeEnum<circt::moore::ProcedureKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [initial, final, always, always_comb, always_latch, always_ff] for Procedure kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::ProcedureKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::ProcedureKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::ProcedureKind getEmptyKey() {
    return static_cast<circt::moore::ProcedureKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::ProcedureKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::ProcedureKind &lhs, const circt::moore::ProcedureKind &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Real format
enum class RealFormat : uint32_t {
  Float = 0,
  Exponential = 1,
  General = 2,
};

::std::optional<RealFormat> symbolizeRealFormat(uint32_t);
::llvm::StringRef stringifyRealFormat(RealFormat);
::std::optional<RealFormat> symbolizeRealFormat(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForRealFormat() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(RealFormat enumValue) {
  return stringifyRealFormat(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<RealFormat> symbolizeEnum<RealFormat>(::llvm::StringRef str) {
  return symbolizeRealFormat(str);
}

class RealFormatAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = RealFormat;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static RealFormatAttr get(::mlir::MLIRContext *context, RealFormat val);
  RealFormat getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::RealFormat, circt::moore::RealFormat> {
  template <typename ParserT>
  static FailureOr<circt::moore::RealFormat> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Real format");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::RealFormat> attr = circt::moore::symbolizeEnum<circt::moore::RealFormat>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [float, exponential, general] for Real format, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::RealFormat>, std::optional<circt::moore::RealFormat>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::RealFormat>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"float", "exponential", "general"})))
      return std::optional<circt::moore::RealFormat>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::RealFormat> attr = circt::moore::symbolizeEnum<circt::moore::RealFormat>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [float, exponential, general] for Real format, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::RealFormat value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::RealFormat> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::RealFormat getEmptyKey() {
    return static_cast<circt::moore::RealFormat>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::RealFormat &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::RealFormat &lhs, const circt::moore::RealFormat &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// Diagnostic severity
enum class Severity : uint32_t {
  Info = 0,
  Warning = 1,
  Error = 2,
  Fatal = 3,
};

::std::optional<Severity> symbolizeSeverity(uint32_t);
::llvm::StringRef stringifySeverity(Severity);
::std::optional<Severity> symbolizeSeverity(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForSeverity() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(Severity enumValue) {
  return stringifySeverity(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Severity> symbolizeEnum<Severity>(::llvm::StringRef str) {
  return symbolizeSeverity(str);
}

class SeverityAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = Severity;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static SeverityAttr get(::mlir::MLIRContext *context, Severity val);
  Severity getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::Severity, circt::moore::Severity> {
  template <typename ParserT>
  static FailureOr<circt::moore::Severity> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Diagnostic severity");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::Severity> attr = circt::moore::symbolizeEnum<circt::moore::Severity>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [info, warning, error, fatal] for Diagnostic severity, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::Severity>, std::optional<circt::moore::Severity>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::Severity>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"info", "warning", "error", "fatal"})))
      return std::optional<circt::moore::Severity>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::Severity> attr = circt::moore::symbolizeEnum<circt::moore::Severity>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [info, warning, error, fatal] for Diagnostic severity, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::Severity value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::Severity> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::moore::Severity getEmptyKey() {
    return static_cast<circt::moore::Severity>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::Severity &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::moore::Severity &lhs, const circt::moore::Severity &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// allowed 64-bit signless integer cases: 0, 1, 2, 3, 4, 5
enum class StringCmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
  lt = 2,
  le = 3,
  gt = 4,
  ge = 5,
};

::std::optional<StringCmpPredicate> symbolizeStringCmpPredicate(uint64_t);
::llvm::StringRef stringifyStringCmpPredicate(StringCmpPredicate);
::std::optional<StringCmpPredicate> symbolizeStringCmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForStringCmpPredicate() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(StringCmpPredicate enumValue) {
  return stringifyStringCmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<StringCmpPredicate> symbolizeEnum<StringCmpPredicate>(::llvm::StringRef str) {
  return symbolizeStringCmpPredicate(str);
}

class StringCmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = StringCmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static StringCmpPredicateAttr get(::mlir::MLIRContext *context, StringCmpPredicate val);
  StringCmpPredicate getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::StringCmpPredicate, circt::moore::StringCmpPredicate> {
  template <typename ParserT>
  static FailureOr<circt::moore::StringCmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 64-bit signless integer cases: 0, 1, 2, 3, 4, 5");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::StringCmpPredicate> attr = circt::moore::symbolizeEnum<circt::moore::StringCmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne, lt, le, gt, ge] for allowed 64-bit signless integer cases: 0, 1, 2, 3, 4, 5, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::StringCmpPredicate>, std::optional<circt::moore::StringCmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::StringCmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"eq", "ne", "lt", "le", "gt", "ge"})))
      return std::optional<circt::moore::StringCmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::StringCmpPredicate> attr = circt::moore::symbolizeEnum<circt::moore::StringCmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne, lt, le, gt, ge] for allowed 64-bit signless integer cases: 0, 1, 2, 3, 4, 5, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::StringCmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::StringCmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline circt::moore::StringCmpPredicate getEmptyKey() {
    return static_cast<circt::moore::StringCmpPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::StringCmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const circt::moore::StringCmpPredicate &lhs, const circt::moore::StringCmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::moore {

// allowed 64-bit signless integer cases: 0, 1
enum class UArrayCmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
};

::std::optional<UArrayCmpPredicate> symbolizeUArrayCmpPredicate(uint64_t);
::llvm::StringRef stringifyUArrayCmpPredicate(UArrayCmpPredicate);
::std::optional<UArrayCmpPredicate> symbolizeUArrayCmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForUArrayCmpPredicate() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(UArrayCmpPredicate enumValue) {
  return stringifyUArrayCmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<UArrayCmpPredicate> symbolizeEnum<UArrayCmpPredicate>(::llvm::StringRef str) {
  return symbolizeUArrayCmpPredicate(str);
}

class UArrayCmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = UArrayCmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static UArrayCmpPredicateAttr get(::mlir::MLIRContext *context, UArrayCmpPredicate val);
  UArrayCmpPredicate getValue() const;
};

} // namespace circt::moore

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::moore::UArrayCmpPredicate, circt::moore::UArrayCmpPredicate> {
  template <typename ParserT>
  static FailureOr<circt::moore::UArrayCmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for allowed 64-bit signless integer cases: 0, 1");

    // Symbolize the keyword.
    if (::std::optional<circt::moore::UArrayCmpPredicate> attr = circt::moore::symbolizeEnum<circt::moore::UArrayCmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne] for allowed 64-bit signless integer cases: 0, 1, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::moore::UArrayCmpPredicate>, std::optional<circt::moore::UArrayCmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::moore::UArrayCmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"eq", "ne"})))
      return std::optional<circt::moore::UArrayCmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::moore::UArrayCmpPredicate> attr = circt::moore::symbolizeEnum<circt::moore::UArrayCmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne] for allowed 64-bit signless integer cases: 0, 1, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::moore::UArrayCmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::moore::UArrayCmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline circt::moore::UArrayCmpPredicate getEmptyKey() {
    return static_cast<circt::moore::UArrayCmpPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::moore::UArrayCmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const circt::moore::UArrayCmpPredicate &lhs, const circt::moore::UArrayCmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

