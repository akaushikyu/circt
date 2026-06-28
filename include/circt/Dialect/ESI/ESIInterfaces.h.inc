/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::esi {

/// "An interface for operations which carries channel semantics."
class ChannelOpInterface;

} // namespace circt::esi
namespace circt::esi {

/// Op can be identified by an AppID.
class HasAppID;

} // namespace circt::esi
namespace circt::esi {

/// Op's attributes should be represented in the manifest.
class IsManifestData;

} // namespace circt::esi
namespace circt::esi {

/// Any op which represents a service declaration should implement this
/// interface.
class ServiceDeclOpInterface;

} // namespace circt::esi
namespace circt::esi {

/// "An interface for operations which carries channel semantics."
namespace detail {
struct ChannelOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    circt::esi::ChannelType (*channelType)(const Concept *impl, ::mlir::Operation *);
    mlir::Type (*innerType)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::esi::ChannelOpInterface;
    Model() : Concept{channelType, innerType} {}

    static inline circt::esi::ChannelType channelType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Type innerType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::esi::ChannelOpInterface;
    FallbackModel() : Concept{channelType, innerType} {}

    static inline circt::esi::ChannelType channelType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Type innerType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    mlir::Type innerType(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct ChannelOpInterfaceTrait;

} // namespace detail
class ChannelOpInterface : public ::mlir::OpInterface<ChannelOpInterface, detail::ChannelOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ChannelOpInterface, detail::ChannelOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ChannelOpInterfaceTrait<ConcreteOp> {};

  /// "Returns the channel type of this operation."
  circt::esi::ChannelType channelType();

  /// "Returns the inner type of this channel. This will be the type of the
  ///            data value of the channel, if the channel carries data semantics. Else,
  ///            return NoneType."
  mlir::Type innerType();
};

} // namespace circt::esi
namespace circt::esi {

/// Op can be identified by an AppID.
namespace detail {
struct HasAppIDInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::circt::esi::AppIDAttr (*getAppID)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::esi::HasAppID;
    Model() : Concept{getAppID} {}

    static inline ::circt::esi::AppIDAttr getAppID(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::esi::HasAppID;
    FallbackModel() : Concept{getAppID} {}

    static inline ::circt::esi::AppIDAttr getAppID(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::circt::esi::AppIDAttr getAppID(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct HasAppIDTrait;

} // namespace detail
class HasAppID : public ::mlir::OpInterface<HasAppID, detail::HasAppIDInterfaceTraits> {
public:
  using ::mlir::OpInterface<HasAppID, detail::HasAppIDInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::HasAppIDTrait<ConcreteOp> {};

  /// Returns the AppID of this operation.
  ::circt::esi::AppIDAttr getAppID();
};

} // namespace circt::esi
namespace circt::esi {

/// Op's attributes should be represented in the manifest.
namespace detail {
struct IsManifestDataInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    StringRef (*getManifestClass)(const Concept *impl, ::mlir::Operation *);
    FlatSymbolRefAttr (*getSymbolRefAttr)(const Concept *impl, ::mlir::Operation *);
    void (*getDetails)(const Concept *impl, ::mlir::Operation *, SmallVectorImpl<NamedAttribute>&);
    DictionaryAttr (*getDetailsAsDict)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::esi::IsManifestData;
    Model() : Concept{getManifestClass, getSymbolRefAttr, getDetails, getDetailsAsDict} {}

    static inline StringRef getManifestClass(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FlatSymbolRefAttr getSymbolRefAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void getDetails(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>& results);
    static inline DictionaryAttr getDetailsAsDict(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::esi::IsManifestData;
    FallbackModel() : Concept{getManifestClass, getSymbolRefAttr, getDetails, getDetailsAsDict} {}

    static inline StringRef getManifestClass(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FlatSymbolRefAttr getSymbolRefAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void getDetails(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>& results);
    static inline DictionaryAttr getDetailsAsDict(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    FlatSymbolRefAttr getSymbolRefAttr(::mlir::Operation *tablegen_opaque_val) const;
    void getDetails(::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>&results) const;
    DictionaryAttr getDetailsAsDict(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct IsManifestDataTrait;

} // namespace detail
class IsManifestData : public ::mlir::OpInterface<IsManifestData, detail::IsManifestDataInterfaceTraits> {
public:
  using ::mlir::OpInterface<IsManifestData, detail::IsManifestDataInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::IsManifestDataTrait<ConcreteOp> {};

  /// Get the class name for this op.
  StringRef getManifestClass();

  /// Get the symbol to which this manifest data is referring, if any.
  FlatSymbolRefAttr getSymbolRefAttr();

  /// Populate results with the manifest data.
  void getDetails(SmallVectorImpl<NamedAttribute>& results);

  /// Get the manifest data from this op as an attribute.
  DictionaryAttr getDetailsAsDict();
};

} // namespace circt::esi
namespace circt::esi {

/// Any op which represents a service declaration should implement this
/// interface.
namespace detail {
struct ServiceDeclOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*getPortList)(const Concept *impl, ::mlir::Operation *, llvm::SmallVectorImpl<ServicePortInfo>&);
    std::optional<StringRef> (*getTypeName)(const Concept *impl, ::mlir::Operation *);
    FailureOr<ServicePortInfo> (*getPortInfo)(const Concept *impl, ::mlir::Operation *, StringAttr);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::esi::ServiceDeclOpInterface;
    Model() : Concept{getPortList, getTypeName, getPortInfo} {}

    static inline void getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::SmallVectorImpl<ServicePortInfo>& ports);
    static inline std::optional<StringRef> getTypeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FailureOr<ServicePortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, StringAttr portName);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::esi::ServiceDeclOpInterface;
    FallbackModel() : Concept{getPortList, getTypeName, getPortInfo} {}

    static inline void getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::SmallVectorImpl<ServicePortInfo>& ports);
    static inline std::optional<StringRef> getTypeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FailureOr<ServicePortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, StringAttr portName);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    std::optional<StringRef> getTypeName(::mlir::Operation *tablegen_opaque_val) const;
    FailureOr<ServicePortInfo> getPortInfo(::mlir::Operation *tablegen_opaque_val, StringAttr portName) const;
  };
};
template <typename ConcreteOp>
struct ServiceDeclOpInterfaceTrait;

} // namespace detail
class ServiceDeclOpInterface : public ::mlir::OpInterface<ServiceDeclOpInterface, detail::ServiceDeclOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ServiceDeclOpInterface, detail::ServiceDeclOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ServiceDeclOpInterfaceTrait<ConcreteOp> {};

  /// Returns the list of interface ports for this service interface.
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>& ports);

  /// Return a well-known name for this service type.
  std::optional<StringRef> getTypeName();

  /// Get info on a particular port.
  FailureOr<ServicePortInfo> getPortInfo(StringAttr portName);
};

} // namespace circt::esi
namespace circt::esi::detail {

  template <typename ConcreteOp>
  struct ChannelOpInterfaceTrait : public ::mlir::OpInterface<ChannelOpInterface, detail::ChannelOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// "Returns the inner type of this channel. This will be the type of the
    ///            data value of the channel, if the channel carries data semantics. Else,
    ///            return NoneType."
    mlir::Type innerType() {
      return (*static_cast<ConcreteOp *>(this)).channelType().getInner();
    }
  };

} // namespace circt::esi::detail
namespace circt::esi::detail {

  template <typename ConcreteOp>
  struct HasAppIDTrait : public ::mlir::OpInterface<HasAppID, detail::HasAppIDInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the AppID of this operation.
    ::circt::esi::AppIDAttr getAppID() {
      return (*static_cast<ConcreteOp *>(this)).getAppID();
    }
  };

} // namespace circt::esi::detail
namespace circt::esi::detail {

  template <typename ConcreteOp>
  struct IsManifestDataTrait : public ::mlir::OpInterface<IsManifestData, detail::IsManifestDataInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the symbol to which this manifest data is referring, if any.
    FlatSymbolRefAttr getSymbolRefAttr() {
      return FlatSymbolRefAttr();
    }

    /// Populate results with the manifest data.
    void getDetails(SmallVectorImpl<NamedAttribute>& results) {
      auto attrs = (*static_cast<ConcreteOp *>(this))->getAttrs();
          results.append(attrs.begin(), attrs.end());
    }

    /// Get the manifest data from this op as an attribute.
    DictionaryAttr getDetailsAsDict() {
      SmallVector<NamedAttribute, 8> attrs;
          (*static_cast<ConcreteOp *>(this)).getDetails(attrs);
          return DictionaryAttr::get((*static_cast<ConcreteOp *>(this)).getContext(), attrs);
    }
  };

} // namespace circt::esi::detail
namespace circt::esi::detail {

  template <typename ConcreteOp>
  struct ServiceDeclOpInterfaceTrait : public ::mlir::OpInterface<ServiceDeclOpInterface, detail::ServiceDeclOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Return a well-known name for this service type.
    std::optional<StringRef> getTypeName() {
      return {};
    }

    /// Get info on a particular port.
    FailureOr<ServicePortInfo> getPortInfo(StringAttr portName) {
      SmallVector<ServicePortInfo> ports;
        (*static_cast<ConcreteOp *>(this)).getPortList(ports);
        auto f = llvm::find_if(ports, [&](ServicePortInfo port) {
          return port.port.getName() == portName;
        });
        if (f != ports.end()) return *f;
        return failure();
    }
  };

} // namespace circt::esi::detail
namespace circt::esi {

template<typename ConcreteOp>
circt::esi::ChannelType detail::ChannelOpInterfaceInterfaceTraits::Model<ConcreteOp>::channelType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).channelType();
}
template<typename ConcreteOp>
mlir::Type detail::ChannelOpInterfaceInterfaceTraits::Model<ConcreteOp>::innerType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).innerType();
}
template<typename ConcreteOp>
circt::esi::ChannelType detail::ChannelOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::channelType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->channelType(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Type detail::ChannelOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::innerType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->innerType(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::Type detail::ChannelOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::innerType(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).channelType().getInner();
}

} // namespace circt::esi
namespace circt::esi {

template<typename ConcreteOp>
::circt::esi::AppIDAttr detail::HasAppIDInterfaceTraits::Model<ConcreteOp>::getAppID(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAppID();
}
template<typename ConcreteOp>
::circt::esi::AppIDAttr detail::HasAppIDInterfaceTraits::FallbackModel<ConcreteOp>::getAppID(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getAppID(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::circt::esi::AppIDAttr detail::HasAppIDInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getAppID(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAppID();
}

} // namespace circt::esi
namespace circt::esi {

template<typename ConcreteOp>
StringRef detail::IsManifestDataInterfaceTraits::Model<ConcreteOp>::getManifestClass(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getManifestClass();
}
template<typename ConcreteOp>
FlatSymbolRefAttr detail::IsManifestDataInterfaceTraits::Model<ConcreteOp>::getSymbolRefAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSymbolRefAttr();
}
template<typename ConcreteOp>
void detail::IsManifestDataInterfaceTraits::Model<ConcreteOp>::getDetails(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>& results) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDetails(results);
}
template<typename ConcreteOp>
DictionaryAttr detail::IsManifestDataInterfaceTraits::Model<ConcreteOp>::getDetailsAsDict(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDetailsAsDict();
}
template<typename ConcreteOp>
StringRef detail::IsManifestDataInterfaceTraits::FallbackModel<ConcreteOp>::getManifestClass(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getManifestClass(tablegen_opaque_val);
}
template<typename ConcreteOp>
FlatSymbolRefAttr detail::IsManifestDataInterfaceTraits::FallbackModel<ConcreteOp>::getSymbolRefAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSymbolRefAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::IsManifestDataInterfaceTraits::FallbackModel<ConcreteOp>::getDetails(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>& results) {
  return static_cast<const ConcreteOp *>(impl)->getDetails(tablegen_opaque_val, results);
}
template<typename ConcreteOp>
DictionaryAttr detail::IsManifestDataInterfaceTraits::FallbackModel<ConcreteOp>::getDetailsAsDict(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDetailsAsDict(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
FlatSymbolRefAttr detail::IsManifestDataInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSymbolRefAttr(::mlir::Operation *tablegen_opaque_val) const {
return FlatSymbolRefAttr();
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::IsManifestDataInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDetails(::mlir::Operation *tablegen_opaque_val, SmallVectorImpl<NamedAttribute>&results) const {
auto attrs = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getAttrs();
          results.append(attrs.begin(), attrs.end());
}
template<typename ConcreteModel, typename ConcreteOp>
DictionaryAttr detail::IsManifestDataInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDetailsAsDict(::mlir::Operation *tablegen_opaque_val) const {
SmallVector<NamedAttribute, 8> attrs;
          (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDetails(attrs);
          return DictionaryAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getContext(), attrs);
}

} // namespace circt::esi
namespace circt::esi {

template<typename ConcreteOp>
void detail::ServiceDeclOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::SmallVectorImpl<ServicePortInfo>& ports) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortList(ports);
}
template<typename ConcreteOp>
std::optional<StringRef> detail::ServiceDeclOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTypeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTypeName();
}
template<typename ConcreteOp>
FailureOr<ServicePortInfo> detail::ServiceDeclOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, StringAttr portName) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortInfo(portName);
}
template<typename ConcreteOp>
void detail::ServiceDeclOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::SmallVectorImpl<ServicePortInfo>& ports) {
  return static_cast<const ConcreteOp *>(impl)->getPortList(tablegen_opaque_val, ports);
}
template<typename ConcreteOp>
std::optional<StringRef> detail::ServiceDeclOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTypeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTypeName(tablegen_opaque_val);
}
template<typename ConcreteOp>
FailureOr<ServicePortInfo> detail::ServiceDeclOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, StringAttr portName) {
  return static_cast<const ConcreteOp *>(impl)->getPortInfo(tablegen_opaque_val, portName);
}
template<typename ConcreteModel, typename ConcreteOp>
std::optional<StringRef> detail::ServiceDeclOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTypeName(::mlir::Operation *tablegen_opaque_val) const {
return {};
}
template<typename ConcreteModel, typename ConcreteOp>
FailureOr<ServicePortInfo> detail::ServiceDeclOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortInfo(::mlir::Operation *tablegen_opaque_val, StringAttr portName) const {
SmallVector<ServicePortInfo> ports;
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortList(ports);
        auto f = llvm::find_if(ports, [&](ServicePortInfo port) {
          return port.port.getName() == portName;
        });
        if (f != ports.end()) return *f;
        return failure();
}

} // namespace circt::esi
