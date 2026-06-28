/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTG.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

// visibility specifiers for labels
enum class LabelVisibility : uint32_t {
  local = 0,
  global = 1,
  external = 2,
};

::std::optional<LabelVisibility> symbolizeLabelVisibility(uint32_t);
::llvm::StringRef stringifyLabelVisibility(LabelVisibility);
::std::optional<LabelVisibility> symbolizeLabelVisibility(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForLabelVisibility() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(LabelVisibility enumValue) {
  return stringifyLabelVisibility(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<LabelVisibility> symbolizeEnum<LabelVisibility>(::llvm::StringRef str) {
  return symbolizeLabelVisibility(str);
}

class LabelVisibilityAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = LabelVisibility;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static LabelVisibilityAttr get(::mlir::MLIRContext *context, LabelVisibility val);
  LabelVisibility getValue() const;
};

} // namespace circt::rtg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::rtg::LabelVisibility, ::circt::rtg::LabelVisibility> {
  template <typename ParserT>
  static FailureOr<::circt::rtg::LabelVisibility> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for visibility specifiers for labels");

    // Symbolize the keyword.
    if (::std::optional<::circt::rtg::LabelVisibility> attr = ::circt::rtg::symbolizeEnum<::circt::rtg::LabelVisibility>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [local, global, external] for visibility specifiers for labels, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::rtg::LabelVisibility>, std::optional<::circt::rtg::LabelVisibility>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::rtg::LabelVisibility>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"local", "global", "external"})))
      return std::optional<::circt::rtg::LabelVisibility>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::rtg::LabelVisibility> attr = ::circt::rtg::symbolizeEnum<::circt::rtg::LabelVisibility>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [local, global, external] for visibility specifiers for labels, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::rtg::LabelVisibility value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::rtg::LabelVisibility> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::rtg::LabelVisibility getEmptyKey() {
    return static_cast<::circt::rtg::LabelVisibility>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::rtg::LabelVisibility &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::rtg::LabelVisibility &lhs, const ::circt::rtg::LabelVisibility &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::rtg {

// kind of segment
enum class SegmentKind : uint32_t {
  Data = 0,
  Text = 1,
};

::std::optional<SegmentKind> symbolizeSegmentKind(uint32_t);
::llvm::StringRef stringifySegmentKind(SegmentKind);
::std::optional<SegmentKind> symbolizeSegmentKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForSegmentKind() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(SegmentKind enumValue) {
  return stringifySegmentKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<SegmentKind> symbolizeEnum<SegmentKind>(::llvm::StringRef str) {
  return symbolizeSegmentKind(str);
}

class SegmentKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = SegmentKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static SegmentKindAttr get(::mlir::MLIRContext *context, SegmentKind val);
  SegmentKind getValue() const;
};

} // namespace circt::rtg

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::rtg::SegmentKind, ::circt::rtg::SegmentKind> {
  template <typename ParserT>
  static FailureOr<::circt::rtg::SegmentKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for kind of segment");

    // Symbolize the keyword.
    if (::std::optional<::circt::rtg::SegmentKind> attr = ::circt::rtg::symbolizeEnum<::circt::rtg::SegmentKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [data, text] for kind of segment, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::rtg::SegmentKind>, std::optional<::circt::rtg::SegmentKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::rtg::SegmentKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"data", "text"})))
      return std::optional<::circt::rtg::SegmentKind>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::rtg::SegmentKind> attr = ::circt::rtg::symbolizeEnum<::circt::rtg::SegmentKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [data, text] for kind of segment, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::rtg::SegmentKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::rtg::SegmentKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::rtg::SegmentKind getEmptyKey() {
    return static_cast<::circt::rtg::SegmentKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::rtg::SegmentKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::rtg::SegmentKind &lhs, const ::circt::rtg::SegmentKind &rhs) {
    return lhs == rhs;
  }
};
}

