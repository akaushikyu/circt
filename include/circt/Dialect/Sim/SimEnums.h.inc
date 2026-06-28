/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Sim.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sim {

// DPI port direction
enum class DPIDirection : uint32_t {
  Input = 0,
  Output = 1,
  InOut = 2,
  Return = 3,
  Ref = 4,
};

::std::optional<DPIDirection> symbolizeDPIDirection(uint32_t);
::llvm::StringRef stringifyDPIDirection(DPIDirection);
::std::optional<DPIDirection> symbolizeDPIDirection(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForDPIDirection() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(DPIDirection enumValue) {
  return stringifyDPIDirection(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<DPIDirection> symbolizeEnum<DPIDirection>(::llvm::StringRef str) {
  return symbolizeDPIDirection(str);
}

class DPIDirectionAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = DPIDirection;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static DPIDirectionAttr get(::mlir::MLIRContext *context, DPIDirection val);
  DPIDirection getValue() const;
};

} // namespace circt::sim

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::sim::DPIDirection, circt::sim::DPIDirection> {
  template <typename ParserT>
  static FailureOr<circt::sim::DPIDirection> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for DPI port direction");

    // Symbolize the keyword.
    if (::std::optional<circt::sim::DPIDirection> attr = circt::sim::symbolizeEnum<circt::sim::DPIDirection>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [in, out, inout, return, ref] for DPI port direction, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::sim::DPIDirection>, std::optional<circt::sim::DPIDirection>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::sim::DPIDirection>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"in", "out", "inout", "return", "ref"})))
      return std::optional<circt::sim::DPIDirection>{};

    // Symbolize the keyword.
    if (::std::optional<circt::sim::DPIDirection> attr = circt::sim::symbolizeEnum<circt::sim::DPIDirection>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [in, out, inout, return, ref] for DPI port direction, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::sim::DPIDirection value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::sim::DPIDirection> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::sim::DPIDirection getEmptyKey() {
    return static_cast<circt::sim::DPIDirection>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::sim::DPIDirection &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::sim::DPIDirection &lhs, const circt::sim::DPIDirection &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sim {

// queue.cmp comparison predicate
enum class QueueCmpPredicate : uint64_t {
  eq = 0,
  ne = 1,
};

::std::optional<QueueCmpPredicate> symbolizeQueueCmpPredicate(uint64_t);
::llvm::StringRef stringifyQueueCmpPredicate(QueueCmpPredicate);
::std::optional<QueueCmpPredicate> symbolizeQueueCmpPredicate(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForQueueCmpPredicate() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(QueueCmpPredicate enumValue) {
  return stringifyQueueCmpPredicate(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<QueueCmpPredicate> symbolizeEnum<QueueCmpPredicate>(::llvm::StringRef str) {
  return symbolizeQueueCmpPredicate(str);
}

class QueueCmpPredicateAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = QueueCmpPredicate;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static QueueCmpPredicateAttr get(::mlir::MLIRContext *context, QueueCmpPredicate val);
  QueueCmpPredicate getValue() const;
};

} // namespace circt::sim

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::sim::QueueCmpPredicate, circt::sim::QueueCmpPredicate> {
  template <typename ParserT>
  static FailureOr<circt::sim::QueueCmpPredicate> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for queue.cmp comparison predicate");

    // Symbolize the keyword.
    if (::std::optional<circt::sim::QueueCmpPredicate> attr = circt::sim::symbolizeEnum<circt::sim::QueueCmpPredicate>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [eq, ne] for queue.cmp comparison predicate, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::sim::QueueCmpPredicate>, std::optional<circt::sim::QueueCmpPredicate>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::sim::QueueCmpPredicate>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"eq", "ne"})))
      return std::optional<circt::sim::QueueCmpPredicate>{};

    // Symbolize the keyword.
    if (::std::optional<circt::sim::QueueCmpPredicate> attr = circt::sim::symbolizeEnum<circt::sim::QueueCmpPredicate>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [eq, ne] for queue.cmp comparison predicate, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::sim::QueueCmpPredicate value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::sim::QueueCmpPredicate> {
  using StorageInfo = ::llvm::DenseMapInfo<uint64_t>;

  static inline circt::sim::QueueCmpPredicate getEmptyKey() {
    return static_cast<circt::sim::QueueCmpPredicate>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::sim::QueueCmpPredicate &val) {
    return StorageInfo::getHashValue(static_cast<uint64_t>(val));
  }

  static bool isEqual(const circt::sim::QueueCmpPredicate &lhs, const circt::sim::QueueCmpPredicate &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::sim {

// SV file open mode
enum class SVFOpenMode : uint32_t {
  Read = 0,
  Write = 1,
  Append = 2,
  ReadUpdate = 3,
  WriteUpdate = 4,
  AppendUpdate = 5,
};

::std::optional<SVFOpenMode> symbolizeSVFOpenMode(uint32_t);
::llvm::StringRef stringifySVFOpenMode(SVFOpenMode);
::std::optional<SVFOpenMode> symbolizeSVFOpenMode(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForSVFOpenMode() {
  return 5;
}


inline ::llvm::StringRef stringifyEnum(SVFOpenMode enumValue) {
  return stringifySVFOpenMode(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<SVFOpenMode> symbolizeEnum<SVFOpenMode>(::llvm::StringRef str) {
  return symbolizeSVFOpenMode(str);
}

class SVFOpenModeAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = SVFOpenMode;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static SVFOpenModeAttr get(::mlir::MLIRContext *context, SVFOpenMode val);
  SVFOpenMode getValue() const;
};

} // namespace circt::sim

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<circt::sim::SVFOpenMode, circt::sim::SVFOpenMode> {
  template <typename ParserT>
  static FailureOr<circt::sim::SVFOpenMode> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for SV file open mode");

    // Symbolize the keyword.
    if (::std::optional<circt::sim::SVFOpenMode> attr = circt::sim::symbolizeEnum<circt::sim::SVFOpenMode>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [r, w, a, r_update, w_update, a_update] for SV file open mode, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<circt::sim::SVFOpenMode>, std::optional<circt::sim::SVFOpenMode>> {
  template <typename ParserT>
  static FailureOr<std::optional<circt::sim::SVFOpenMode>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"r", "w", "a", "r_update", "w_update", "a_update"})))
      return std::optional<circt::sim::SVFOpenMode>{};

    // Symbolize the keyword.
    if (::std::optional<circt::sim::SVFOpenMode> attr = circt::sim::symbolizeEnum<circt::sim::SVFOpenMode>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [r, w, a, r_update, w_update, a_update] for SV file open mode, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, circt::sim::SVFOpenMode value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<circt::sim::SVFOpenMode> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline circt::sim::SVFOpenMode getEmptyKey() {
    return static_cast<circt::sim::SVFOpenMode>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const circt::sim::SVFOpenMode &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const circt::sim::SVFOpenMode &lhs, const circt::sim::SVFOpenMode &rhs) {
    return lhs == rhs;
  }
};
}

