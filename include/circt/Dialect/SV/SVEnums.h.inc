/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SV.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

// case type
enum class CaseStmtType : uint32_t {
  CaseStmt = 0,
  CaseXStmt = 1,
  CaseZStmt = 2,
};

::std::optional<CaseStmtType> symbolizeCaseStmtType(uint32_t);
::llvm::StringRef stringifyCaseStmtType(CaseStmtType);
::std::optional<CaseStmtType> symbolizeCaseStmtType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForCaseStmtType() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(CaseStmtType enumValue) {
  return stringifyCaseStmtType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<CaseStmtType> symbolizeEnum<CaseStmtType>(::llvm::StringRef str) {
  return symbolizeCaseStmtType(str);
}

class CaseStmtTypeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = CaseStmtType;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static CaseStmtTypeAttr get(::mlir::MLIRContext *context, CaseStmtType val);
  CaseStmtType getValue() const;
};

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::CaseStmtType, ::CaseStmtType> {
  template <typename ParserT>
  static FailureOr<::CaseStmtType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for case type");

    // Symbolize the keyword.
    if (::std::optional<::CaseStmtType> attr = ::symbolizeEnum<::CaseStmtType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [case, casex, casez] for case type, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::CaseStmtType>, std::optional<::CaseStmtType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::CaseStmtType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"case", "casex", "casez"})))
      return std::optional<::CaseStmtType>{};

    // Symbolize the keyword.
    if (::std::optional<::CaseStmtType> attr = ::symbolizeEnum<::CaseStmtType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [case, casex, casez] for case type, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::CaseStmtType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::CaseStmtType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::CaseStmtType getEmptyKey() {
    return static_cast<::CaseStmtType>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::CaseStmtType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::CaseStmtType &lhs, const ::CaseStmtType &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sv {

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

} // namespace circt::sv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::sv::DeferAssert, circt::sv::DeferAssert> {
  template <typename ParserT>
  static FailureOr<circt::sv::DeferAssert> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for assertion deferring mode");

    // Symbolize the keyword.
    if (::std::optional<circt::sv::DeferAssert> attr = circt::sv::symbolizeEnum<circt::sv::DeferAssert>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [immediate, observed, final] for assertion deferring mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::sv::DeferAssert>, std::optional<circt::sv::DeferAssert>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::sv::DeferAssert>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"immediate", "observed", "final"})))
      return std::optional<circt::sv::DeferAssert>{};

    // Symbolize the keyword.
    if (::std::optional<circt::sv::DeferAssert> attr = circt::sv::symbolizeEnum<circt::sv::DeferAssert>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [immediate, observed, final] for assertion deferring mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::sv::DeferAssert value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::sv::DeferAssert> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::sv::DeferAssert getEmptyKey() {
    return static_cast<circt::sv::DeferAssert>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::sv::DeferAssert &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::sv::DeferAssert &lhs, const circt::sv::DeferAssert &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sv {

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

} // namespace circt::sv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::sv::EventControl, circt::sv::EventControl> {
  template <typename ParserT>
  static FailureOr<circt::sv::EventControl> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for edge control trigger");

    // Symbolize the keyword.
    if (::std::optional<circt::sv::EventControl> attr = circt::sv::symbolizeEnum<circt::sv::EventControl>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::sv::EventControl>, std::optional<circt::sv::EventControl>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::sv::EventControl>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"posedge", "negedge", "edge"})))
      return std::optional<circt::sv::EventControl>{};

    // Symbolize the keyword.
    if (::std::optional<circt::sv::EventControl> attr = circt::sv::symbolizeEnum<circt::sv::EventControl>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::sv::EventControl value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::sv::EventControl> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::sv::EventControl getEmptyKey() {
    return static_cast<circt::sv::EventControl>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::sv::EventControl &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::sv::EventControl &lhs, const circt::sv::EventControl &rhs) {
    return lhs == rhs;
  }
};
}

// Double-quoted local include, or angle bracketed system include
enum class IncludeStyle : uint32_t {
  Local = 0,
  System = 1,
};

::std::optional<IncludeStyle> symbolizeIncludeStyle(uint32_t);
::llvm::StringRef stringifyIncludeStyle(IncludeStyle);
::std::optional<IncludeStyle> symbolizeIncludeStyle(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForIncludeStyle() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(IncludeStyle enumValue) {
  return stringifyIncludeStyle(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<IncludeStyle> symbolizeEnum<IncludeStyle>(::llvm::StringRef str) {
  return symbolizeIncludeStyle(str);
}

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::IncludeStyle, ::IncludeStyle> {
  template <typename ParserT>
  static FailureOr<::IncludeStyle> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Double-quoted local include, or angle bracketed system include");

    // Symbolize the keyword.
    if (::std::optional<::IncludeStyle> attr = ::symbolizeEnum<::IncludeStyle>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [local, system] for Double-quoted local include, or angle bracketed system include, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::IncludeStyle>, std::optional<::IncludeStyle>> {
  template <typename ParserT>
  static FailureOr<std::optional<::IncludeStyle>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"local", "system"})))
      return std::optional<::IncludeStyle>{};

    // Symbolize the keyword.
    if (::std::optional<::IncludeStyle> attr = ::symbolizeEnum<::IncludeStyle>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [local, system] for Double-quoted local include, or angle bracketed system include, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::IncludeStyle value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::IncludeStyle> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::IncludeStyle getEmptyKey() {
    return static_cast<::IncludeStyle>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::IncludeStyle &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::IncludeStyle &lhs, const ::IncludeStyle &rhs) {
    return lhs == rhs;
  }
};
}

// the numeric base of a memory file
enum class MemBaseTypeAttr : uint32_t {
  MemBaseBin = 0,
  MemBaseHex = 1,
};

::std::optional<MemBaseTypeAttr> symbolizeMemBaseTypeAttr(uint32_t);
::llvm::StringRef stringifyMemBaseTypeAttr(MemBaseTypeAttr);
::std::optional<MemBaseTypeAttr> symbolizeMemBaseTypeAttr(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForMemBaseTypeAttr() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(MemBaseTypeAttr enumValue) {
  return stringifyMemBaseTypeAttr(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<MemBaseTypeAttr> symbolizeEnum<MemBaseTypeAttr>(::llvm::StringRef str) {
  return symbolizeMemBaseTypeAttr(str);
}

class MemBaseTypeAttrAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = MemBaseTypeAttr;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static MemBaseTypeAttrAttr get(::mlir::MLIRContext *context, MemBaseTypeAttr val);
  MemBaseTypeAttr getValue() const;
};

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::MemBaseTypeAttr, ::MemBaseTypeAttr> {
  template <typename ParserT>
  static FailureOr<::MemBaseTypeAttr> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for the numeric base of a memory file");

    // Symbolize the keyword.
    if (::std::optional<::MemBaseTypeAttr> attr = ::symbolizeEnum<::MemBaseTypeAttr>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [MemBaseBin, MemBaseHex] for the numeric base of a memory file, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::MemBaseTypeAttr>, std::optional<::MemBaseTypeAttr>> {
  template <typename ParserT>
  static FailureOr<std::optional<::MemBaseTypeAttr>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"MemBaseBin", "MemBaseHex"})))
      return std::optional<::MemBaseTypeAttr>{};

    // Symbolize the keyword.
    if (::std::optional<::MemBaseTypeAttr> attr = ::symbolizeEnum<::MemBaseTypeAttr>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [MemBaseBin, MemBaseHex] for the numeric base of a memory file, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::MemBaseTypeAttr value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::MemBaseTypeAttr> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::MemBaseTypeAttr getEmptyKey() {
    return static_cast<::MemBaseTypeAttr>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::MemBaseTypeAttr &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::MemBaseTypeAttr &lhs, const ::MemBaseTypeAttr &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sv {

// Defines direction in a modport
enum class ModportDirection : uint32_t {
  input = 0,
  output = 1,
  inout = 2,
};

::std::optional<ModportDirection> symbolizeModportDirection(uint32_t);
::llvm::StringRef stringifyModportDirection(ModportDirection);
::std::optional<ModportDirection> symbolizeModportDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForModportDirection() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ModportDirection enumValue) {
  return stringifyModportDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ModportDirection> symbolizeEnum<ModportDirection>(::llvm::StringRef str) {
  return symbolizeModportDirection(str);
}

} // namespace circt::sv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::sv::ModportDirection, ::circt::sv::ModportDirection> {
  template <typename ParserT>
  static FailureOr<::circt::sv::ModportDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Defines direction in a modport");

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ModportDirection> attr = ::circt::sv::symbolizeEnum<::circt::sv::ModportDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [input, output, inout] for Defines direction in a modport, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::sv::ModportDirection>, std::optional<::circt::sv::ModportDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::sv::ModportDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"input", "output", "inout"})))
      return std::optional<::circt::sv::ModportDirection>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ModportDirection> attr = ::circt::sv::symbolizeEnum<::circt::sv::ModportDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [input, output, inout] for Defines direction in a modport, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::sv::ModportDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::sv::ModportDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::sv::ModportDirection getEmptyKey() {
    return static_cast<::circt::sv::ModportDirection>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::sv::ModportDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::sv::ModportDirection &lhs, const ::circt::sv::ModportDirection &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sv {

// reset type
enum class ResetType : uint32_t {
  NoReset = 0,
  SyncReset = 1,
  AsyncReset = 2,
};

::std::optional<ResetType> symbolizeResetType(uint32_t);
::llvm::StringRef stringifyResetType(ResetType);
::std::optional<ResetType> symbolizeResetType(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForResetType() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(ResetType enumValue) {
  return stringifyResetType(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ResetType> symbolizeEnum<ResetType>(::llvm::StringRef str) {
  return symbolizeResetType(str);
}

class ResetTypeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = ResetType;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static ResetTypeAttr get(::mlir::MLIRContext *context, ResetType val);
  ResetType getValue() const;
};

} // namespace circt::sv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::sv::ResetType, ::circt::sv::ResetType> {
  template <typename ParserT>
  static FailureOr<::circt::sv::ResetType> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for reset type");

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ResetType> attr = ::circt::sv::symbolizeEnum<::circt::sv::ResetType>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [noreset, syncreset, asyncreset] for reset type, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::sv::ResetType>, std::optional<::circt::sv::ResetType>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::sv::ResetType>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"noreset", "syncreset", "asyncreset"})))
      return std::optional<::circt::sv::ResetType>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ResetType> attr = ::circt::sv::symbolizeEnum<::circt::sv::ResetType>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [noreset, syncreset, asyncreset] for reset type, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::sv::ResetType value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::sv::ResetType> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::sv::ResetType getEmptyKey() {
    return static_cast<::circt::sv::ResetType>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::sv::ResetType &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::sv::ResetType &lhs, const ::circt::sv::ResetType &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sv {

// validation qualifier type
enum class ValidationQualifierTypeEnum : uint32_t {
  ValidationQualifierPlain = 0,
  ValidationQualifierUnique = 1,
  ValidationQualifierUnique0 = 2,
  ValidationQualifierPriority = 3,
};

::std::optional<ValidationQualifierTypeEnum> symbolizeValidationQualifierTypeEnum(uint32_t);
::llvm::StringRef stringifyValidationQualifierTypeEnum(ValidationQualifierTypeEnum);
::std::optional<ValidationQualifierTypeEnum> symbolizeValidationQualifierTypeEnum(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForValidationQualifierTypeEnum() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(ValidationQualifierTypeEnum enumValue) {
  return stringifyValidationQualifierTypeEnum(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<ValidationQualifierTypeEnum> symbolizeEnum<ValidationQualifierTypeEnum>(::llvm::StringRef str) {
  return symbolizeValidationQualifierTypeEnum(str);
}

} // namespace circt::sv

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::sv::ValidationQualifierTypeEnum, ::circt::sv::ValidationQualifierTypeEnum> {
  template <typename ParserT>
  static FailureOr<::circt::sv::ValidationQualifierTypeEnum> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for validation qualifier type");

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ValidationQualifierTypeEnum> attr = ::circt::sv::symbolizeEnum<::circt::sv::ValidationQualifierTypeEnum>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [plain, unique, unique0, priority] for validation qualifier type, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::sv::ValidationQualifierTypeEnum>, std::optional<::circt::sv::ValidationQualifierTypeEnum>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::sv::ValidationQualifierTypeEnum>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"plain", "unique", "unique0", "priority"})))
      return std::optional<::circt::sv::ValidationQualifierTypeEnum>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::sv::ValidationQualifierTypeEnum> attr = ::circt::sv::symbolizeEnum<::circt::sv::ValidationQualifierTypeEnum>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [plain, unique, unique0, priority] for validation qualifier type, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::sv::ValidationQualifierTypeEnum value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::sv::ValidationQualifierTypeEnum> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::sv::ValidationQualifierTypeEnum getEmptyKey() {
    return static_cast<::circt::sv::ValidationQualifierTypeEnum>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::sv::ValidationQualifierTypeEnum &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::sv::ValidationQualifierTypeEnum &lhs, const ::circt::sv::ValidationQualifierTypeEnum &rhs) {
    return lhs == rhs;
  }
};
}

