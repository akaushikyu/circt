/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FIRRTLEnums.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::firrtl {

// lowering convention
enum class Convention : uint32_t {
  Internal = 0,
  Scalarized = 1,
};

::std::optional<Convention> symbolizeConvention(uint32_t);
::llvm::StringRef stringifyConvention(Convention);
::std::optional<Convention> symbolizeConvention(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForConvention() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(Convention enumValue) {
  return stringifyConvention(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<Convention> symbolizeEnum<Convention>(::llvm::StringRef str) {
  return symbolizeConvention(str);
}

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::Convention, ::circt::firrtl::Convention> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::Convention> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for lowering convention");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::Convention> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::Convention>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [internal, scalarized] for lowering convention, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::Convention>, std::optional<::circt::firrtl::Convention>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::Convention>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"internal", "scalarized"})))
      return std::optional<::circt::firrtl::Convention>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::Convention> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::Convention>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [internal, scalarized] for lowering convention, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::Convention value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::Convention> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::Convention getEmptyKey() {
    return static_cast<::circt::firrtl::Convention>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::Convention &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::Convention &lhs, const ::circt::firrtl::Convention &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

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

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::EventControl, ::circt::firrtl::EventControl> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::EventControl> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for edge control trigger");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::EventControl> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::EventControl>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::EventControl>, std::optional<::circt::firrtl::EventControl>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::EventControl>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"posedge", "negedge", "edge"})))
      return std::optional<::circt::firrtl::EventControl>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::EventControl> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::EventControl>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [posedge, negedge, edge] for edge control trigger, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::EventControl value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::EventControl> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::EventControl getEmptyKey() {
    return static_cast<::circt::firrtl::EventControl>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::EventControl &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::EventControl &lhs, const ::circt::firrtl::EventControl &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// layer convention
enum class LayerConvention : uint32_t {
  Bind = 0,
  Inline = 1,
};

::std::optional<LayerConvention> symbolizeLayerConvention(uint32_t);
::llvm::StringRef stringifyLayerConvention(LayerConvention);
::std::optional<LayerConvention> symbolizeLayerConvention(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForLayerConvention() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(LayerConvention enumValue) {
  return stringifyLayerConvention(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<LayerConvention> symbolizeEnum<LayerConvention>(::llvm::StringRef str) {
  return symbolizeLayerConvention(str);
}

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::LayerConvention, ::circt::firrtl::LayerConvention> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::LayerConvention> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for layer convention");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::LayerConvention> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::LayerConvention>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [bind, inline] for layer convention, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::LayerConvention>, std::optional<::circt::firrtl::LayerConvention>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::LayerConvention>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"bind", "inline"})))
      return std::optional<::circt::firrtl::LayerConvention>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::LayerConvention> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::LayerConvention>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [bind, inline] for layer convention, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::LayerConvention value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::LayerConvention> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::LayerConvention getEmptyKey() {
    return static_cast<::circt::firrtl::LayerConvention>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::LayerConvention &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::LayerConvention &lhs, const ::circt::firrtl::LayerConvention &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// layer specialization
enum class LayerSpecialization : uint32_t {
  Enable = 0,
  Disable = 1,
};

::std::optional<LayerSpecialization> symbolizeLayerSpecialization(uint32_t);
::llvm::StringRef stringifyLayerSpecialization(LayerSpecialization);
::std::optional<LayerSpecialization> symbolizeLayerSpecialization(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForLayerSpecialization() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(LayerSpecialization enumValue) {
  return stringifyLayerSpecialization(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<LayerSpecialization> symbolizeEnum<LayerSpecialization>(::llvm::StringRef str) {
  return symbolizeLayerSpecialization(str);
}

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::LayerSpecialization, ::circt::firrtl::LayerSpecialization> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::LayerSpecialization> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for layer specialization");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::LayerSpecialization> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::LayerSpecialization>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [enable, disable] for layer specialization, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::LayerSpecialization>, std::optional<::circt::firrtl::LayerSpecialization>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::LayerSpecialization>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"enable", "disable"})))
      return std::optional<::circt::firrtl::LayerSpecialization>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::LayerSpecialization> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::LayerSpecialization>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [enable, disable] for layer specialization, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::LayerSpecialization value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::LayerSpecialization> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::LayerSpecialization getEmptyKey() {
    return static_cast<::circt::firrtl::LayerSpecialization>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::LayerSpecialization &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::LayerSpecialization &lhs, const ::circt::firrtl::LayerSpecialization &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// Memory Direction Enum
enum class MemDirAttr : uint32_t {
  Infer = 0,
  Read = 1,
  Write = 2,
  ReadWrite = 3,
};

::std::optional<MemDirAttr> symbolizeMemDirAttr(uint32_t);
::llvm::StringRef stringifyMemDirAttr(MemDirAttr);
::std::optional<MemDirAttr> symbolizeMemDirAttr(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForMemDirAttr() {
  return 3;
}


inline ::llvm::StringRef stringifyEnum(MemDirAttr enumValue) {
  return stringifyMemDirAttr(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<MemDirAttr> symbolizeEnum<MemDirAttr>(::llvm::StringRef str) {
  return symbolizeMemDirAttr(str);
}

class MemDirAttrAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = MemDirAttr;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static MemDirAttrAttr get(::mlir::MLIRContext *context, MemDirAttr val);
  MemDirAttr getValue() const;
};

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::MemDirAttr, ::circt::firrtl::MemDirAttr> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::MemDirAttr> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Memory Direction Enum");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::MemDirAttr> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::MemDirAttr>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Infer, Read, Write, ReadWrite] for Memory Direction Enum, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::MemDirAttr>, std::optional<::circt::firrtl::MemDirAttr>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::MemDirAttr>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"Infer", "Read", "Write", "ReadWrite"})))
      return std::optional<::circt::firrtl::MemDirAttr>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::MemDirAttr> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::MemDirAttr>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Infer, Read, Write, ReadWrite] for Memory Direction Enum, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::MemDirAttr value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::MemDirAttr> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::MemDirAttr getEmptyKey() {
    return static_cast<::circt::firrtl::MemDirAttr>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::MemDirAttr &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::MemDirAttr &lhs, const ::circt::firrtl::MemDirAttr &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// name kind
enum class NameKindEnum : uint32_t {
  DroppableName = 0,
  InterestingName = 1,
};

::std::optional<NameKindEnum> symbolizeNameKindEnum(uint32_t);
::llvm::StringRef stringifyNameKindEnum(NameKindEnum);
::std::optional<NameKindEnum> symbolizeNameKindEnum(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForNameKindEnum() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(NameKindEnum enumValue) {
  return stringifyNameKindEnum(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<NameKindEnum> symbolizeEnum<NameKindEnum>(::llvm::StringRef str) {
  return symbolizeNameKindEnum(str);
}

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::NameKindEnum, ::circt::firrtl::NameKindEnum> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::NameKindEnum> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for name kind");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::NameKindEnum> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::NameKindEnum>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [droppable_name, interesting_name] for name kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::NameKindEnum>, std::optional<::circt::firrtl::NameKindEnum>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::NameKindEnum>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"droppable_name", "interesting_name"})))
      return std::optional<::circt::firrtl::NameKindEnum>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::NameKindEnum> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::NameKindEnum>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [droppable_name, interesting_name] for name kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::NameKindEnum value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::NameKindEnum> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::NameKindEnum getEmptyKey() {
    return static_cast<::circt::firrtl::NameKindEnum>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::NameKindEnum &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::NameKindEnum &lhs, const ::circt::firrtl::NameKindEnum &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// read under write behavior
enum class RUWBehavior : uint32_t {
  Undefined = 0,
  Old = 1,
  New = 2,
};

::std::optional<RUWBehavior> symbolizeRUWBehavior(uint32_t);
::llvm::StringRef stringifyRUWBehavior(RUWBehavior);
::std::optional<RUWBehavior> symbolizeRUWBehavior(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForRUWBehavior() {
  return 2;
}


inline ::llvm::StringRef stringifyEnum(RUWBehavior enumValue) {
  return stringifyRUWBehavior(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<RUWBehavior> symbolizeEnum<RUWBehavior>(::llvm::StringRef str) {
  return symbolizeRUWBehavior(str);
}

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::RUWBehavior, ::circt::firrtl::RUWBehavior> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::RUWBehavior> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for read under write behavior");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::RUWBehavior> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::RUWBehavior>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [Undefined, Old, New] for read under write behavior, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::RUWBehavior>, std::optional<::circt::firrtl::RUWBehavior>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::RUWBehavior>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"Undefined", "Old", "New"})))
      return std::optional<::circt::firrtl::RUWBehavior>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::RUWBehavior> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::RUWBehavior>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [Undefined, Old, New] for read under write behavior, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::RUWBehavior value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::RUWBehavior> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::RUWBehavior getEmptyKey() {
    return static_cast<::circt::firrtl::RUWBehavior>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::RUWBehavior &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::RUWBehavior &lhs, const ::circt::firrtl::RUWBehavior &rhs) {
    return lhs == rhs;
  }
};
}

namespace circt::firrtl {

// object model target kind
enum class TargetKind : uint32_t {
  DontTouch = 0,
  Instance = 1,
  MemberInstance = 2,
  MemberReference = 3,
  Reference = 4,
};

::std::optional<TargetKind> symbolizeTargetKind(uint32_t);
::llvm::StringRef stringifyTargetKind(TargetKind);
::std::optional<TargetKind> symbolizeTargetKind(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForTargetKind() {
  return 4;
}


inline ::llvm::StringRef stringifyEnum(TargetKind enumValue) {
  return stringifyTargetKind(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<TargetKind> symbolizeEnum<TargetKind>(::llvm::StringRef str) {
  return symbolizeTargetKind(str);
}

class TargetKindAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = TargetKind;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static TargetKindAttr get(::mlir::MLIRContext *context, TargetKind val);
  TargetKind getValue() const;
};

} // namespace circt::firrtl

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::circt::firrtl::TargetKind, ::circt::firrtl::TargetKind> {
  template <typename ParserT>
  static FailureOr<::circt::firrtl::TargetKind> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for object model target kind");

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::TargetKind> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::TargetKind>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "expected one of [dont_touch, instance, member_instance, member_reference, reference] for object model target kind, got: ") << enumKeyword;
  }
};

/// Support for std::optional, useful in attribute/type definition where the enum is
/// used as:
///
///    let parameters = (ins OptionalParameter<"std::optional<TheEnumName>">:$value);
template<>
struct FieldParser<std::optional<::circt::firrtl::TargetKind>, std::optional<::circt::firrtl::TargetKind>> {
  template <typename ParserT>
  static FailureOr<std::optional<::circt::firrtl::TargetKind>> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword, {"dont_touch", "instance", "member_instance", "member_reference", "reference"})))
      return std::optional<::circt::firrtl::TargetKind>{};

    // Symbolize the keyword.
    if (::std::optional<::circt::firrtl::TargetKind> attr = ::circt::firrtl::symbolizeEnum<::circt::firrtl::TargetKind>(enumKeyword))
      return attr;
    return parser.emitError(loc, "expected one of [dont_touch, instance, member_instance, member_reference, reference] for object model target kind, got: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::circt::firrtl::TargetKind value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::circt::firrtl::TargetKind> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::circt::firrtl::TargetKind getEmptyKey() {
    return static_cast<::circt::firrtl::TargetKind>(StorageInfo::getEmptyKey());
  }

  static unsigned getHashValue(const ::circt::firrtl::TargetKind &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::circt::firrtl::TargetKind &lhs, const ::circt::firrtl::TargetKind &rhs) {
    return lhs == rhs;
  }
};
}

