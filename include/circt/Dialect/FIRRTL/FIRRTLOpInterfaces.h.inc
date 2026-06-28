/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::firrtl {

/// Provide common module information.
class FModuleLike;

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common instance information for FIRRTL instance-like operations.
class FInstanceLike;

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common class information.
class ClassLike;

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common connection information.
class FConnectLike;

} // namespace circt::firrtl
namespace circt::firrtl {

/// This interface provides common methods for namable operations.
class FNamableOp;

} // namespace circt::firrtl
namespace circt::firrtl {

/// Interaction with declarations of forceable hardware components,
/// and managing references to them.
class Forceable;

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common module information.
namespace detail {
struct FModuleLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ArrayAttr (*getParameters)(const Concept *impl, ::mlir::Operation *);
    ConventionAttr (*getConventionAttr)(const Concept *impl, ::mlir::Operation *);
    Convention (*getConvention)(const Concept *impl, ::mlir::Operation *);
    ArrayAttr (*getLayersAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getLayers)(const Concept *impl, ::mlir::Operation *);
    mlir::DenseBoolArrayAttr (*getPortDirectionsAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<bool> (*getPortDirections)(const Concept *impl, ::mlir::Operation *);
    Direction (*getPortDirection)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getPortNamesAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getPortNames)(const Concept *impl, ::mlir::Operation *);
    StringAttr (*getPortNameAttr)(const Concept *impl, ::mlir::Operation *, size_t);
    StringRef (*getPortName)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getPortTypesAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getPortTypes)(const Concept *impl, ::mlir::Operation *);
    void (*setPortTypesAttr)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    TypeAttr (*getPortTypeAttr)(const Concept *impl, ::mlir::Operation *, size_t);
    Type (*getPortType)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getPortAnnotationsAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getPortAnnotations)(const Concept *impl, ::mlir::Operation *);
    void (*setPortAnnotationsAttr)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    ArrayAttr (*getAnnotationsAttrForPort)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayRef<Attribute> (*getAnnotationsForPort)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getPortSymbolsAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getPortSymbols)(const Concept *impl, ::mlir::Operation *);
    circt::hw::InnerSymAttr (*getPortSymbolAttr)(const Concept *impl, ::mlir::Operation *, size_t);
    void (*setPortSymbolsAttr)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    void (*setPortSymbols)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<Attribute>);
    void (*setPortSymbolAttr)(const Concept *impl, ::mlir::Operation *, size_t, circt::hw::InnerSymAttr);
    ArrayAttr (*getPortLocationsAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getPortLocations)(const Concept *impl, ::mlir::Operation *);
    LocationAttr (*getPortLocationAttr)(const Concept *impl, ::mlir::Operation *, size_t);
    Location (*getPortLocation)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getDomainInfoAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getDomainInfo)(const Concept *impl, ::mlir::Operation *);
    Attribute (*getDomainInfoAttrForPort)(const Concept *impl, ::mlir::Operation *, size_t);
    void (*setDomainInfoAttr)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    SmallVector<PortInfo> (*getPorts)(const Concept *impl, ::mlir::Operation *);
    void (*insertPorts)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<unsigned, PortInfo>>);
    void (*erasePorts)(const Concept *impl, ::mlir::Operation *, const llvm::BitVector&);
    /// The base classes of this interface.
    const ::mlir::SymbolOpInterface::Concept *implSymbolOpInterface = nullptr;
    const circt::hw::PortList::Concept *implPortList = nullptr;
    const ::circt::igraph::ModuleOpInterface::Concept *implModuleOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implSymbolOpInterface = interfaceMap.lookup<::mlir::SymbolOpInterface>();
      assert(implSymbolOpInterface && "`circt::firrtl::FModuleLike` expected its base interface `::mlir::SymbolOpInterface` to be registered");
      implPortList = interfaceMap.lookup<circt::hw::PortList>();
      assert(implPortList && "`circt::firrtl::FModuleLike` expected its base interface `circt::hw::PortList` to be registered");
      implModuleOpInterface = interfaceMap.lookup<::circt::igraph::ModuleOpInterface>();
      assert(implModuleOpInterface && "`circt::firrtl::FModuleLike` expected its base interface `::circt::igraph::ModuleOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::firrtl::FModuleLike;
    Model() : Concept{getParameters, getConventionAttr, getConvention, getLayersAttr, getLayers, getPortDirectionsAttr, getPortDirections, getPortDirection, getPortNamesAttr, getPortNames, getPortNameAttr, getPortName, getPortTypesAttr, getPortTypes, setPortTypesAttr, getPortTypeAttr, getPortType, getPortAnnotationsAttr, getPortAnnotations, setPortAnnotationsAttr, getAnnotationsAttrForPort, getAnnotationsForPort, getPortSymbolsAttr, getPortSymbols, getPortSymbolAttr, setPortSymbolsAttr, setPortSymbols, setPortSymbolAttr, getPortLocationsAttr, getPortLocations, getPortLocationAttr, getPortLocation, getDomainInfoAttr, getDomainInfo, getDomainInfoAttrForPort, setDomainInfoAttr, getPorts, insertPorts, erasePorts} {}

    static inline ArrayAttr getParameters(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ConventionAttr getConventionAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Convention getConvention(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayAttr getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getLayers(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::DenseBoolArrayAttr getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<bool> getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Direction getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringAttr getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline StringRef getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr portTypes);
    static inline TypeAttr getPortTypeAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline Type getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortAnnotations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr annotations);
    static inline ArrayAttr getAnnotationsAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayRef<Attribute> getAnnotationsForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline circt::hw::InnerSymAttr getPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline void setPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr symbols);
    static inline void setPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<Attribute> symbols);
    static inline void setPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol);
    static inline ArrayAttr getPortLocationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortLocations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LocationAttr getPortLocationAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline Location getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getDomainInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Attribute getDomainInfoAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline void setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr domainInfo);
    static inline SmallVector<PortInfo> getPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> ports);
    static inline void erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector& portIndices);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::firrtl::FModuleLike;
    FallbackModel() : Concept{getParameters, getConventionAttr, getConvention, getLayersAttr, getLayers, getPortDirectionsAttr, getPortDirections, getPortDirection, getPortNamesAttr, getPortNames, getPortNameAttr, getPortName, getPortTypesAttr, getPortTypes, setPortTypesAttr, getPortTypeAttr, getPortType, getPortAnnotationsAttr, getPortAnnotations, setPortAnnotationsAttr, getAnnotationsAttrForPort, getAnnotationsForPort, getPortSymbolsAttr, getPortSymbols, getPortSymbolAttr, setPortSymbolsAttr, setPortSymbols, setPortSymbolAttr, getPortLocationsAttr, getPortLocations, getPortLocationAttr, getPortLocation, getDomainInfoAttr, getDomainInfo, getDomainInfoAttrForPort, setDomainInfoAttr, getPorts, insertPorts, erasePorts} {}

    static inline ArrayAttr getParameters(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ConventionAttr getConventionAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Convention getConvention(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayAttr getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getLayers(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::DenseBoolArrayAttr getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<bool> getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Direction getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringAttr getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline StringRef getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr portTypes);
    static inline TypeAttr getPortTypeAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline Type getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortAnnotations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr annotations);
    static inline ArrayAttr getAnnotationsAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayRef<Attribute> getAnnotationsForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline circt::hw::InnerSymAttr getPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline void setPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr symbols);
    static inline void setPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<Attribute> symbols);
    static inline void setPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol);
    static inline ArrayAttr getPortLocationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getPortLocations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LocationAttr getPortLocationAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline Location getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getDomainInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Attribute getDomainInfoAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline void setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr domainInfo);
    static inline SmallVector<PortInfo> getPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> ports);
    static inline void erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector& portIndices);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    Direction getPortDirection(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    StringAttr getPortNameAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    StringRef getPortName(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    TypeAttr getPortTypeAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    Type getPortType(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    ArrayAttr getAnnotationsAttrForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    ArrayRef<Attribute> getAnnotationsForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    circt::hw::InnerSymAttr getPortSymbolAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    void setPortSymbolAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol) const;
    LocationAttr getPortLocationAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    Location getPortLocation(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    ArrayAttr getDomainInfoAttr(::mlir::Operation *tablegen_opaque_val) const;
    Attribute getDomainInfoAttrForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
  };
};
template <typename ConcreteOp>
struct FModuleLikeTrait;

} // namespace detail
class FModuleLike : public ::mlir::OpInterface<FModuleLike, detail::FModuleLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<FModuleLike, detail::FModuleLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FModuleLikeTrait<ConcreteOp> {};

  /// Get the parameters
  ArrayAttr getParameters();

  /// Get the module's instantiation convention
  ConventionAttr getConventionAttr();

  /// Get the module's instantiation convention
  Convention getConvention();

  /// Get the module's enabled layers
  ArrayAttr getLayersAttr();

  /// Get the module's enabled layers.
  ArrayRef<Attribute> getLayers();

  /// Get the port directions attribute
  mlir::DenseBoolArrayAttr getPortDirectionsAttr();

  /// Get the port directions
  ArrayRef<bool> getPortDirections();

  /// Get a port direction
  Direction getPortDirection(size_t portIndex);

  /// Get the port names attribute
  ArrayAttr getPortNamesAttr();

  /// Get the port names
  ArrayRef<Attribute> getPortNames();

  /// Get a port name
  StringAttr getPortNameAttr(size_t portIndex);

  /// Get a port name
  StringRef getPortName(size_t portIndex);

  /// Get the port types attribute
  ArrayAttr getPortTypesAttr();

  /// Get the port types
  ArrayRef<Attribute> getPortTypes();

  /// Set the types of all ports
  void setPortTypesAttr(::mlir::ArrayAttr portTypes);

  /// Get a port type
  TypeAttr getPortTypeAttr(size_t portIndex);

  /// Get a port type
  Type getPortType(size_t portIndex);

  /// Get the port annotations attribute
  ArrayAttr getPortAnnotationsAttr();

  /// Get the port annotations attribute
  ArrayRef<Attribute> getPortAnnotations();

  /// Set the port annotations attribute
  void setPortAnnotationsAttr(::mlir::ArrayAttr annotations);

  /// Get a port's annotations attribute
  ArrayAttr getAnnotationsAttrForPort(size_t portIndex);

  /// Get a port's annotations
  ArrayRef<Attribute> getAnnotationsForPort(size_t portIndex);

  /// Get the port symbols attribute
  ArrayAttr getPortSymbolsAttr();

  /// Get the port symbols
  ArrayRef<Attribute> getPortSymbols();

  /// Get the port symbol attribute
  circt::hw::InnerSymAttr getPortSymbolAttr(size_t portIndex);

  /// Set the symbols of all ports and their fields
  void setPortSymbolsAttr(::mlir::ArrayAttr symbols);

  /// Set the symbols of all ports and their fields
  void setPortSymbols(::llvm::ArrayRef<Attribute> symbols);

  /// Set the symbols for a port including its fields
  void setPortSymbolAttr(size_t portIndex, circt::hw::InnerSymAttr symbol);

  /// Get the port locations attribute
  ArrayAttr getPortLocationsAttr();

  /// Get the port locations attribute
  ArrayRef<Attribute> getPortLocations();

  /// Get a port's location attribute
  LocationAttr getPortLocationAttr(size_t portIndex);

  /// Get a port's location
  Location getPortLocation(size_t portIndex);

  /// Get domain information attribute
  ArrayAttr getDomainInfoAttr();

  /// Get domain information
  ArrayRef<Attribute> getDomainInfo();

  /// Get a port's domain info attribute
  Attribute getDomainInfoAttrForPort(size_t portIndex);

  /// Set the domain info of all ports
  void setDomainInfoAttr(::mlir::ArrayAttr domainInfo);

  /// Get information about all ports
  SmallVector<PortInfo> getPorts();

  /// Inserts the given ports at the corresponding indices
  void insertPorts(ArrayRef<std::pair<unsigned, PortInfo>> ports);

  /// Erases the ports that have their corresponding bit set in `portIndices`
  void erasePorts(const llvm::BitVector& portIndices);


    /// Replace NULL entries with an empty InnerSymbol. If all elements of the
    /// array are empty, then it will clear the array.
    static void fixupPortSymsArray(SmallVectorImpl<Attribute> &syms,
                                   MLIRContext *context) {
      // The lack of *any* port symbol is represented by an empty `portSymbols`
      // array as a shorthand.
      if (llvm::none_of(syms, [&](auto &sym) {
            return sym && !cast<hw::InnerSymAttr>(sym).empty();
          })) {
        syms.clear();
        return;
      }
      auto empty = hw::InnerSymAttr::get(context);
      for (auto &sym : syms)
        if (!sym)
          sym = empty;
    }
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::SymbolOpInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::SymbolOpInterface () const {
    if (!*this) return nullptr;
    return ::mlir::SymbolOpInterface(*this, getImpl()->implSymbolOpInterface);
  }


  /// Returns the name of this symbol.
  ::mlir::StringAttr getNameAttr();

  /// Sets the name of this symbol.
  void setName(::mlir::StringAttr name);

  /// Gets the visibility of this symbol.
  mlir::SymbolTable::Visibility getVisibility();

  /// Returns true if this symbol has nested visibility.
  bool isNested();

  /// Returns true if this symbol has private visibility.
  bool isPrivate();

  /// Returns true if this symbol has public visibility.
  bool isPublic();

  /// Sets the visibility of this symbol.
  void setVisibility(mlir::SymbolTable::Visibility vis);

  /// Sets the visibility of this symbol to be nested.
  void setNested();

  /// Sets the visibility of this symbol to be private.
  void setPrivate();

  /// Sets the visibility of this symbol to be public.
  void setPublic();

  /// Get all of the uses of the current symbol that are nested within the
  /// given operation 'from'.
  /// Note: See mlir::SymbolTable::getSymbolUses for more details.
  ::std::optional<::mlir::SymbolTable::UseRange> getSymbolUses(::mlir::Operation * from);

  /// Return if the current symbol is known to have no uses that are nested
  /// within the given operation 'from'.
  /// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
  bool symbolKnownUseEmpty(::mlir::Operation * from);

  /// Attempt to replace all uses of the current symbol with the provided
  /// symbol 'newSymbol' that are nested within the given operation 'from'.
  /// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
  ::llvm::LogicalResult replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from);

  /// Returns true if this operation optionally defines a symbol based on the
  /// presence of the symbol name.
  bool isOptionalSymbol();

  /// Returns true if this operation can be discarded if it has no remaining
  /// symbol uses.
  bool canDiscardOnUseEmpty();

  /// Returns true if this operation is a declaration of a symbol (as opposed
  /// to a definition).
  bool isDeclaration();

    using Visibility = mlir::SymbolTable::Visibility;

    /// Convenience version of `getNameAttr` that returns a StringRef.
    ::mlir::StringRef getName() {
      return getNameAttr().getValue();
    }

    /// Convenience version of `setName` that take a StringRef.
    void setName(::mlir::StringRef name) {
      setName(::mlir::StringAttr::get((*this)->getContext(), name));
    }
  //===----------------------------------------------------------------===//
  // Inherited from circt::hw::PortList
  //===----------------------------------------------------------------===//

  operator circt::hw::PortList () const {
    if (!*this) return nullptr;
    return circt::hw::PortList(*this, getImpl()->implPortList);
  }


  /// Get port list
  SmallVector<::circt::hw::PortInfo> getPortList();

  /// Get port list
  ::circt::hw::PortInfo getPort(size_t idx);

  /// Get the port a specific input
  size_t getPortIdForInputId(size_t idx);

  /// Get the port a specific output
  size_t getPortIdForOutputId(size_t idx);

  /// Get the number of ports
  size_t getNumPorts();

  /// Get the number of input ports
  size_t getNumInputPorts();

  /// Get the number of output ports
  size_t getNumOutputPorts();
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::igraph::ModuleOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::igraph::ModuleOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::igraph::ModuleOpInterface(*this, getImpl()->implModuleOpInterface);
  }


  /// Get the module name
  ::llvm::StringRef getModuleName();

  /// Get the module name
  ::mlir::StringAttr getModuleNameAttr();
};

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common instance information for FIRRTL instance-like operations.
namespace detail {
struct FInstanceLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    size_t (*getNumPorts)(const Concept *impl, ::mlir::Operation *);
    Direction (*getPortDirection)(const Concept *impl, ::mlir::Operation *, size_t);
    StringAttr (*getPortNameAttr)(const Concept *impl, ::mlir::Operation *, size_t);
    StringRef (*getPortName)(const Concept *impl, ::mlir::Operation *, size_t);
    Location (*getPortLocation)(const Concept *impl, ::mlir::Operation *, size_t);
    mlir::DenseBoolArrayAttr (*getPortDirectionsAttr)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<bool> (*getPortDirections)(const Concept *impl, ::mlir::Operation *);
    ArrayAttr (*getPortNamesAttr)(const Concept *impl, ::mlir::Operation *);
    ::circt::hw::InnerSymAttr (*getInnerSymAttr)(const Concept *impl, ::mlir::Operation *);
    FInstanceLike (*cloneWithInsertedPorts)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<unsigned, PortInfo>>);
    FInstanceLike (*cloneWithInsertedPortsAndReplaceUses)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<unsigned, PortInfo>>);
    FInstanceLike (*cloneWithErasedPorts)(const Concept *impl, ::mlir::Operation *, const llvm::BitVector &);
    FInstanceLike (*cloneWithErasedPortsAndReplaceUses)(const Concept *impl, ::mlir::Operation *, const llvm::BitVector &);
    ArrayAttr (*getDomainInfoAttr)(const Concept *impl, ::mlir::Operation *);
    void (*setDomainInfoAttr)(const Concept *impl, ::mlir::Operation *, ArrayAttr);
    Attribute (*getPortDomain)(const Concept *impl, ::mlir::Operation *, size_t);
    ArrayAttr (*getLayersAttr)(const Concept *impl, ::mlir::Operation *);
    void (*setLayersAttr)(const Concept *impl, ::mlir::Operation *, ArrayAttr);
    /// The base classes of this interface.
    const ::circt::igraph::InstanceOpInterface::Concept *implInstanceOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implInstanceOpInterface = interfaceMap.lookup<::circt::igraph::InstanceOpInterface>();
      assert(implInstanceOpInterface && "`circt::firrtl::FInstanceLike` expected its base interface `::circt::igraph::InstanceOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::firrtl::FInstanceLike;
    Model() : Concept{getNumPorts, getPortDirection, getPortNameAttr, getPortName, getPortLocation, getPortDirectionsAttr, getPortDirections, getPortNamesAttr, getInnerSymAttr, cloneWithInsertedPorts, cloneWithInsertedPortsAndReplaceUses, cloneWithErasedPorts, cloneWithErasedPortsAndReplaceUses, getDomainInfoAttr, setDomainInfoAttr, getPortDomain, getLayersAttr, setLayersAttr} {}

    static inline size_t getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Direction getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline StringAttr getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline StringRef getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline Location getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline mlir::DenseBoolArrayAttr getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<bool> getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayAttr getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::InnerSymAttr getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FInstanceLike cloneWithInsertedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions);
    static inline FInstanceLike cloneWithInsertedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions);
    static inline FInstanceLike cloneWithErasedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures);
    static inline FInstanceLike cloneWithErasedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures);
    static inline ArrayAttr getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo);
    static inline Attribute getPortDomain(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr layers);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::firrtl::FInstanceLike;
    FallbackModel() : Concept{getNumPorts, getPortDirection, getPortNameAttr, getPortName, getPortLocation, getPortDirectionsAttr, getPortDirections, getPortNamesAttr, getInnerSymAttr, cloneWithInsertedPorts, cloneWithInsertedPortsAndReplaceUses, cloneWithErasedPorts, cloneWithErasedPortsAndReplaceUses, getDomainInfoAttr, setDomainInfoAttr, getPortDomain, getLayersAttr, setLayersAttr} {}

    static inline size_t getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Direction getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline StringAttr getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline StringRef getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline Location getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo);
    static inline mlir::DenseBoolArrayAttr getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<bool> getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayAttr getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::InnerSymAttr getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FInstanceLike cloneWithInsertedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions);
    static inline FInstanceLike cloneWithInsertedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions);
    static inline FInstanceLike cloneWithErasedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures);
    static inline FInstanceLike cloneWithErasedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures);
    static inline ArrayAttr getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo);
    static inline Attribute getPortDomain(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex);
    static inline ArrayAttr getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr layers);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    size_t getNumPorts(::mlir::Operation *tablegen_opaque_val) const;
    Direction getPortDirection(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const;
    StringAttr getPortNameAttr(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const;
    StringRef getPortName(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const;
    Location getPortLocation(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const;
    ArrayAttr getDomainInfoAttr(::mlir::Operation *tablegen_opaque_val) const;
    void setDomainInfoAttr(::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo) const;
    Attribute getPortDomain(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const;
    ArrayAttr getLayersAttr(::mlir::Operation *tablegen_opaque_val) const;
    void setLayersAttr(::mlir::Operation *tablegen_opaque_val, ArrayAttr layers) const;
  };
};
template <typename ConcreteOp>
struct FInstanceLikeTrait;

} // namespace detail
class FInstanceLike : public ::mlir::OpInterface<FInstanceLike, detail::FInstanceLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<FInstanceLike, detail::FInstanceLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FInstanceLikeTrait<ConcreteOp> {};

  /// Get the number of ports
  size_t getNumPorts();

  /// Get the port direction for the specified result number
  Direction getPortDirection(size_t resultNo);

  /// Get the port name attribute for the specified result number
  StringAttr getPortNameAttr(size_t resultNo);

  /// Get the port name for the specified result number
  StringRef getPortName(size_t resultNo);

  /// Get the port location for the specified result number
  Location getPortLocation(size_t resultNo);

  /// Get the port directions attribute
  mlir::DenseBoolArrayAttr getPortDirectionsAttr();

  /// Get the port directions
  ArrayRef<bool> getPortDirections();

  /// Get the port names attribute
  ArrayAttr getPortNamesAttr();

  /// Get inner symbol attribute
  ::circt::hw::InnerSymAttr getInnerSymAttr();

  /// Clone this instance with inserted ports
  FInstanceLike cloneWithInsertedPorts(ArrayRef<std::pair<unsigned, PortInfo>> insertions);

  /// Clone this instance with inserted ports, then replace uses
  FInstanceLike cloneWithInsertedPortsAndReplaceUses(ArrayRef<std::pair<unsigned, PortInfo>> insertions);

  /// Clone this instance with erased ports
  FInstanceLike cloneWithErasedPorts(const llvm::BitVector & erasures);

  /// Clone this instance with erased ports, then replace uses
  FInstanceLike cloneWithErasedPortsAndReplaceUses(const llvm::BitVector & erasures);

  /// Get domain information attribute
  ArrayAttr getDomainInfoAttr();

  /// Set domain information attribute
  void setDomainInfoAttr(ArrayAttr domainInfo);

  /// Get domain information attribute
  Attribute getPortDomain(size_t portIndex);

  /// Get layers attribute
  ArrayAttr getLayersAttr();

  /// Set layers attribute
  void setLayersAttr(ArrayAttr layers);
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::igraph::InstanceOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::igraph::InstanceOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::igraph::InstanceOpInterface(*this, getImpl()->implInstanceOpInterface);
  }


  /// Get the name of the instance
  ::llvm::StringRef getInstanceName();

  /// Get the name of the instance
  ::mlir::StringAttr getInstanceNameAttr();

  /// Get the name of all the possibly instantiated modules
  ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames();

  /// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
  ::mlir::ArrayAttr getReferencedModuleNamesAttr();
};

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common class information.
namespace detail {
struct ClassLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ClassType (*getInstanceType)(const Concept *impl, ::mlir::Operation *);
    LogicalResult (*verifyType)(const Concept *impl, ::mlir::Operation *, ::circt::firrtl::ClassType, ::llvm::function_ref<::mlir::InFlightDiagnostic()>);
    /// The base classes of this interface.
    const ::mlir::SymbolOpInterface::Concept *implSymbolOpInterface = nullptr;
    const circt::hw::PortList::Concept *implPortList = nullptr;
    const ::circt::igraph::ModuleOpInterface::Concept *implModuleOpInterface = nullptr;
    const circt::firrtl::FModuleLike::Concept *implFModuleLike = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implSymbolOpInterface = interfaceMap.lookup<::mlir::SymbolOpInterface>();
      assert(implSymbolOpInterface && "`circt::firrtl::ClassLike` expected its base interface `::mlir::SymbolOpInterface` to be registered");
      implPortList = interfaceMap.lookup<circt::hw::PortList>();
      assert(implPortList && "`circt::firrtl::ClassLike` expected its base interface `circt::hw::PortList` to be registered");
      implModuleOpInterface = interfaceMap.lookup<::circt::igraph::ModuleOpInterface>();
      assert(implModuleOpInterface && "`circt::firrtl::ClassLike` expected its base interface `::circt::igraph::ModuleOpInterface` to be registered");
      implFModuleLike = interfaceMap.lookup<circt::firrtl::FModuleLike>();
      assert(implFModuleLike && "`circt::firrtl::ClassLike` expected its base interface `circt::firrtl::FModuleLike` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::firrtl::ClassLike;
    Model() : Concept{getInstanceType, verifyType} {}

    static inline ClassType getInstanceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LogicalResult verifyType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::firrtl::ClassLike;
    FallbackModel() : Concept{getInstanceType, verifyType} {}

    static inline ClassType getInstanceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LogicalResult verifyType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ClassType getInstanceType(::mlir::Operation *tablegen_opaque_val) const;
    LogicalResult verifyType(::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const;
  };
};
template <typename ConcreteOp>
struct ClassLikeTrait;

} // namespace detail
class ClassLike : public ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ClassLikeTrait<ConcreteOp> {};

  /// Get the type for instances of this class
  ClassType getInstanceType();

  /// Verify that the given type agrees with this class
  LogicalResult verifyType(::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::SymbolOpInterface
  //===----------------------------------------------------------------===//

  operator ::mlir::SymbolOpInterface () const {
    if (!*this) return nullptr;
    return ::mlir::SymbolOpInterface(*this, getImpl()->implSymbolOpInterface);
  }


  /// Returns the name of this symbol.
  ::mlir::StringAttr getNameAttr();

  /// Sets the name of this symbol.
  void setName(::mlir::StringAttr name);

  /// Gets the visibility of this symbol.
  mlir::SymbolTable::Visibility getVisibility();

  /// Returns true if this symbol has nested visibility.
  bool isNested();

  /// Returns true if this symbol has private visibility.
  bool isPrivate();

  /// Returns true if this symbol has public visibility.
  bool isPublic();

  /// Sets the visibility of this symbol.
  void setVisibility(mlir::SymbolTable::Visibility vis);

  /// Sets the visibility of this symbol to be nested.
  void setNested();

  /// Sets the visibility of this symbol to be private.
  void setPrivate();

  /// Sets the visibility of this symbol to be public.
  void setPublic();

  /// Get all of the uses of the current symbol that are nested within the
  /// given operation 'from'.
  /// Note: See mlir::SymbolTable::getSymbolUses for more details.
  ::std::optional<::mlir::SymbolTable::UseRange> getSymbolUses(::mlir::Operation * from);

  /// Return if the current symbol is known to have no uses that are nested
  /// within the given operation 'from'.
  /// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
  bool symbolKnownUseEmpty(::mlir::Operation * from);

  /// Attempt to replace all uses of the current symbol with the provided
  /// symbol 'newSymbol' that are nested within the given operation 'from'.
  /// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
  ::llvm::LogicalResult replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from);

  /// Returns true if this operation optionally defines a symbol based on the
  /// presence of the symbol name.
  bool isOptionalSymbol();

  /// Returns true if this operation can be discarded if it has no remaining
  /// symbol uses.
  bool canDiscardOnUseEmpty();

  /// Returns true if this operation is a declaration of a symbol (as opposed
  /// to a definition).
  bool isDeclaration();

    using Visibility = mlir::SymbolTable::Visibility;

    /// Convenience version of `getNameAttr` that returns a StringRef.
    ::mlir::StringRef getName() {
      return getNameAttr().getValue();
    }

    /// Convenience version of `setName` that take a StringRef.
    void setName(::mlir::StringRef name) {
      setName(::mlir::StringAttr::get((*this)->getContext(), name));
    }
  //===----------------------------------------------------------------===//
  // Inherited from circt::hw::PortList
  //===----------------------------------------------------------------===//

  operator circt::hw::PortList () const {
    if (!*this) return nullptr;
    return circt::hw::PortList(*this, getImpl()->implPortList);
  }


  /// Get port list
  SmallVector<::circt::hw::PortInfo> getPortList();

  /// Get port list
  ::circt::hw::PortInfo getPort(size_t idx);

  /// Get the port a specific input
  size_t getPortIdForInputId(size_t idx);

  /// Get the port a specific output
  size_t getPortIdForOutputId(size_t idx);

  /// Get the number of ports
  size_t getNumPorts();

  /// Get the number of input ports
  size_t getNumInputPorts();

  /// Get the number of output ports
  size_t getNumOutputPorts();
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::igraph::ModuleOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::igraph::ModuleOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::igraph::ModuleOpInterface(*this, getImpl()->implModuleOpInterface);
  }


  /// Get the module name
  ::llvm::StringRef getModuleName();

  /// Get the module name
  ::mlir::StringAttr getModuleNameAttr();
  //===----------------------------------------------------------------===//
  // Inherited from circt::firrtl::FModuleLike
  //===----------------------------------------------------------------===//

  operator circt::firrtl::FModuleLike () const {
    if (!*this) return nullptr;
    return circt::firrtl::FModuleLike(*this, getImpl()->implFModuleLike);
  }


  /// Get the parameters
  ArrayAttr getParameters();

  /// Get the module's instantiation convention
  ConventionAttr getConventionAttr();

  /// Get the module's instantiation convention
  Convention getConvention();

  /// Get the module's enabled layers
  ArrayAttr getLayersAttr();

  /// Get the module's enabled layers.
  ArrayRef<Attribute> getLayers();

  /// Get the port directions attribute
  mlir::DenseBoolArrayAttr getPortDirectionsAttr();

  /// Get the port directions
  ArrayRef<bool> getPortDirections();

  /// Get a port direction
  Direction getPortDirection(size_t portIndex);

  /// Get the port names attribute
  ArrayAttr getPortNamesAttr();

  /// Get the port names
  ArrayRef<Attribute> getPortNames();

  /// Get a port name
  StringAttr getPortNameAttr(size_t portIndex);

  /// Get a port name
  StringRef getPortName(size_t portIndex);

  /// Get the port types attribute
  ArrayAttr getPortTypesAttr();

  /// Get the port types
  ArrayRef<Attribute> getPortTypes();

  /// Set the types of all ports
  void setPortTypesAttr(::mlir::ArrayAttr portTypes);

  /// Get a port type
  TypeAttr getPortTypeAttr(size_t portIndex);

  /// Get a port type
  Type getPortType(size_t portIndex);

  /// Get the port annotations attribute
  ArrayAttr getPortAnnotationsAttr();

  /// Get the port annotations attribute
  ArrayRef<Attribute> getPortAnnotations();

  /// Set the port annotations attribute
  void setPortAnnotationsAttr(::mlir::ArrayAttr annotations);

  /// Get a port's annotations attribute
  ArrayAttr getAnnotationsAttrForPort(size_t portIndex);

  /// Get a port's annotations
  ArrayRef<Attribute> getAnnotationsForPort(size_t portIndex);

  /// Get the port symbols attribute
  ArrayAttr getPortSymbolsAttr();

  /// Get the port symbols
  ArrayRef<Attribute> getPortSymbols();

  /// Get the port symbol attribute
  circt::hw::InnerSymAttr getPortSymbolAttr(size_t portIndex);

  /// Set the symbols of all ports and their fields
  void setPortSymbolsAttr(::mlir::ArrayAttr symbols);

  /// Set the symbols of all ports and their fields
  void setPortSymbols(::llvm::ArrayRef<Attribute> symbols);

  /// Set the symbols for a port including its fields
  void setPortSymbolAttr(size_t portIndex, circt::hw::InnerSymAttr symbol);

  /// Get the port locations attribute
  ArrayAttr getPortLocationsAttr();

  /// Get the port locations attribute
  ArrayRef<Attribute> getPortLocations();

  /// Get a port's location attribute
  LocationAttr getPortLocationAttr(size_t portIndex);

  /// Get a port's location
  Location getPortLocation(size_t portIndex);

  /// Get domain information attribute
  ArrayAttr getDomainInfoAttr();

  /// Get domain information
  ArrayRef<Attribute> getDomainInfo();

  /// Get a port's domain info attribute
  Attribute getDomainInfoAttrForPort(size_t portIndex);

  /// Set the domain info of all ports
  void setDomainInfoAttr(::mlir::ArrayAttr domainInfo);

  /// Get information about all ports
  SmallVector<PortInfo> getPorts();

  /// Inserts the given ports at the corresponding indices
  void insertPorts(ArrayRef<std::pair<unsigned, PortInfo>> ports);

  /// Erases the ports that have their corresponding bit set in `portIndices`
  void erasePorts(const llvm::BitVector& portIndices);


    /// Replace NULL entries with an empty InnerSymbol. If all elements of the
    /// array are empty, then it will clear the array.
    static void fixupPortSymsArray(SmallVectorImpl<Attribute> &syms,
                                   MLIRContext *context) {
      // The lack of *any* port symbol is represented by an empty `portSymbols`
      // array as a shorthand.
      if (llvm::none_of(syms, [&](auto &sym) {
            return sym && !cast<hw::InnerSymAttr>(sym).empty();
          })) {
        syms.clear();
        return;
      }
      auto empty = hw::InnerSymAttr::get(context);
      for (auto &sym : syms)
        if (!sym)
          sym = empty;
    }
};

} // namespace circt::firrtl
namespace circt::firrtl {

/// Provide common connection information.
namespace detail {
struct FConnectLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    Value (*getDest)(const Concept *impl, ::mlir::Operation *);
    Value (*getSrc)(const Concept *impl, ::mlir::Operation *);
    ConnectBehaviorKind (*getConnectBehaviorKind)();
    bool (*hasStaticSingleConnectBehavior)();
    bool (*hasLastConnectBehavior)();
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::firrtl::FConnectLike;
    Model() : Concept{getDest, getSrc, getConnectBehaviorKind, hasStaticSingleConnectBehavior, hasLastConnectBehavior} {}

    static inline Value getDest(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Value getSrc(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ConnectBehaviorKind getConnectBehaviorKind();
    static inline bool hasStaticSingleConnectBehavior();
    static inline bool hasLastConnectBehavior();
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::firrtl::FConnectLike;
    FallbackModel() : Concept{getDest, getSrc, getConnectBehaviorKind, hasStaticSingleConnectBehavior, hasLastConnectBehavior} {}

    static inline Value getDest(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Value getSrc(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ConnectBehaviorKind getConnectBehaviorKind();
    static inline bool hasStaticSingleConnectBehavior();
    static inline bool hasLastConnectBehavior();
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    static ConnectBehaviorKind getConnectBehaviorKind();
  };
};
template <typename ConcreteOp>
struct FConnectLikeTrait;

} // namespace detail
class FConnectLike : public ::mlir::OpInterface<FConnectLike, detail::FConnectLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<FConnectLike, detail::FConnectLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FConnectLikeTrait<ConcreteOp> {};

  /// Return a destination of connection.
  Value getDest();

  /// Return a source of connection.
  Value getSrc();

  /// Return connection behavior kind.
  ConnectBehaviorKind getConnectBehaviorKind();

  /// Returns true if ConnectBehavior is StaticSingleConnect.
  bool hasStaticSingleConnectBehavior();

  /// Returns true if ConnectBehavior is LastConnect.
  bool hasLastConnectBehavior();
};

} // namespace circt::firrtl
namespace circt::firrtl {

/// This interface provides common methods for namable operations.
namespace detail {
struct FNamableOpInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::StringAttr (*getNameAttr)(const Concept *impl, ::mlir::Operation *);
    ::llvm::StringRef (*getName)(const Concept *impl, ::mlir::Operation *);
    void (*setNameAttr)(const Concept *impl, ::mlir::Operation *, ::mlir::StringAttr);
    void (*setName)(const Concept *impl, ::mlir::Operation *, ::llvm::StringRef);
    ::circt::firrtl::NameKindEnumAttr (*getNameKindAttr)(const Concept *impl, ::mlir::Operation *);
    ::circt::firrtl::NameKindEnum (*getNameKind)(const Concept *impl, ::mlir::Operation *);
    void (*setNameKindAttr)(const Concept *impl, ::mlir::Operation *, ::circt::firrtl::NameKindEnumAttr);
    void (*setNameKind)(const Concept *impl, ::mlir::Operation *, ::circt::firrtl::NameKindEnum);
    bool (*hasDroppableName)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::firrtl::FNamableOp;
    Model() : Concept{getNameAttr, getName, setNameAttr, setName, getNameKindAttr, getNameKind, setNameKindAttr, setNameKind, hasDroppableName} {}

    static inline ::mlir::StringAttr getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name);
    static inline void setName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::StringRef name);
    static inline ::circt::firrtl::NameKindEnumAttr getNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::firrtl::NameKindEnum getNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnumAttr nameKind);
    static inline void setNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnum nameKind);
    static inline bool hasDroppableName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::firrtl::FNamableOp;
    FallbackModel() : Concept{getNameAttr, getName, setNameAttr, setName, getNameKindAttr, getNameKind, setNameKindAttr, setNameKind, hasDroppableName} {}

    static inline ::mlir::StringAttr getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name);
    static inline void setName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::StringRef name);
    static inline ::circt::firrtl::NameKindEnumAttr getNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::firrtl::NameKindEnum getNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnumAttr nameKind);
    static inline void setNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnum nameKind);
    static inline bool hasDroppableName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    bool hasDroppableName(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct FNamableOpTrait;

} // namespace detail
class FNamableOp : public ::mlir::OpInterface<FNamableOp, detail::FNamableOpInterfaceTraits> {
public:
  using ::mlir::OpInterface<FNamableOp, detail::FNamableOpInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FNamableOpTrait<ConcreteOp> {};

  /// Return the name.
  ::mlir::StringAttr getNameAttr();

  /// Return the name.
  ::llvm::StringRef getName();

  /// Set the name.
  void setNameAttr(::mlir::StringAttr name);

  /// Set the name.
  void setName(::llvm::StringRef name);

  /// Get the namekind
  ::circt::firrtl::NameKindEnumAttr getNameKindAttr();

  /// Get the namekind
  ::circt::firrtl::NameKindEnum getNameKind();

  /// Set a namekind.
  void setNameKindAttr(::circt::firrtl::NameKindEnumAttr nameKind);

  /// Set a namekind.
  void setNameKind(::circt::firrtl::NameKindEnum nameKind);

  /// Return true if the name is droppable.
  bool hasDroppableName();
};

} // namespace circt::firrtl
namespace circt::firrtl {

/// Interaction with declarations of forceable hardware components,
/// and managing references to them.
namespace detail {
struct ForceableInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isForceable)(const Concept *impl, ::mlir::Operation *);
    mlir::TypedValue<FIRRTLBaseType> (*getData)(const Concept *impl, ::mlir::Operation *);
    Value (*getDataRaw)(const Concept *impl, ::mlir::Operation *);
    FIRRTLBaseType (*getDataType)(const Concept *impl, ::mlir::Operation *);
    mlir::TypedValue<RefType> (*getDataRef)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::firrtl::Forceable;
    Model() : Concept{isForceable, getData, getDataRaw, getDataType, getDataRef} {}

    static inline bool isForceable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<FIRRTLBaseType> getData(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Value getDataRaw(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FIRRTLBaseType getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<RefType> getDataRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::firrtl::Forceable;
    FallbackModel() : Concept{isForceable, getData, getDataRaw, getDataType, getDataRef} {}

    static inline bool isForceable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<FIRRTLBaseType> getData(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Value getDataRaw(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline FIRRTLBaseType getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<RefType> getDataRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    bool isForceable(::mlir::Operation *tablegen_opaque_val) const;
    mlir::TypedValue<FIRRTLBaseType> getData(::mlir::Operation *tablegen_opaque_val) const;
    Value getDataRaw(::mlir::Operation *tablegen_opaque_val) const;
    FIRRTLBaseType getDataType(::mlir::Operation *tablegen_opaque_val) const;
    mlir::TypedValue<RefType> getDataRef(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct ForceableTrait;

} // namespace detail
class Forceable : public ::mlir::OpInterface<Forceable, detail::ForceableInterfaceTraits> {
public:
  using ::mlir::OpInterface<Forceable, detail::ForceableInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ForceableTrait<ConcreteOp> {};

  /// Return true if the operation is forceable.
  bool isForceable();

  /// Return data value that will be targeted.
  mlir::TypedValue<FIRRTLBaseType> getData();

  /// Return raw data value that will be targeted.
  Value getDataRaw();

  /// Return data type that will be referenced.
  FIRRTLBaseType getDataType();

  /// Return reference result, or null if not active.
  mlir::TypedValue<RefType> getDataRef();

    /// Attribute name for 'forceable' tracking.
    static StringRef getForceableAttrName() { return "forceable"; }
};

} // namespace circt::firrtl
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct FModuleLikeTrait : public ::mlir::OpInterface<FModuleLike, detail::FModuleLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Get a port direction
    Direction getPortDirection(size_t portIndex) {
      return direction::get((*static_cast<ConcreteOp *>(this)).getPortDirections()[portIndex]);
    }

    /// Get a port name
    StringAttr getPortNameAttr(size_t portIndex) {
      return llvm::cast<StringAttr>((*static_cast<ConcreteOp *>(this)).getPortNames()[portIndex]);
    }

    /// Get a port name
    StringRef getPortName(size_t portIndex) {
      return (*static_cast<ConcreteOp *>(this)).getPortNameAttr(portIndex).getValue();
    }

    /// Get a port type
    TypeAttr getPortTypeAttr(size_t portIndex) {
      return llvm::cast<TypeAttr>((*static_cast<ConcreteOp *>(this)).getPortTypes()[portIndex]);
    }

    /// Get a port type
    Type getPortType(size_t portIndex) {
      return (*static_cast<ConcreteOp *>(this)).getPortTypeAttr(portIndex).getValue();
    }

    /// Get a port's annotations attribute
    ArrayAttr getAnnotationsAttrForPort(size_t portIndex) {
      auto annos = (*static_cast<ConcreteOp *>(this)).getPortAnnotationsAttr();
      if (annos.empty())
        return annos; // annos already is an empty array
      return llvm::cast<ArrayAttr>(annos[portIndex]);
    }

    /// Get a port's annotations
    ArrayRef<Attribute> getAnnotationsForPort(size_t portIndex) {
      return (*static_cast<ConcreteOp *>(this)).getAnnotationsAttrForPort(portIndex).getValue();
    }

    /// Get the port symbol attribute
    circt::hw::InnerSymAttr getPortSymbolAttr(size_t portIndex) {
      auto syms = (*static_cast<ConcreteOp *>(this)).getPortSymbols();
      if (syms.empty() ||
          llvm::cast<hw::InnerSymAttr>(syms[portIndex]).empty())
        return hw::InnerSymAttr();
      return llvm::cast<hw::InnerSymAttr>(syms[portIndex]);
    }

    /// Set the symbols for a port including its fields
    void setPortSymbolAttr(size_t portIndex, circt::hw::InnerSymAttr symbol) {
      SmallVector<Attribute> symbols((*static_cast<ConcreteOp *>(this)).getPortSymbols().begin(),
                                     (*static_cast<ConcreteOp *>(this)).getPortSymbols().end());
      if (symbols.empty()) {
        if (symbol.empty())
          return;
        symbols.resize((*static_cast<ConcreteOp *>(this)).getNumPorts(),
                      hw::InnerSymAttr::get((*static_cast<ConcreteOp *>(this)).getContext()));
      }
      assert(symbols.size() == (*static_cast<ConcreteOp *>(this)).getNumPorts());
      symbols[portIndex] = symbol;

      FModuleLike::fixupPortSymsArray(symbols, (*static_cast<ConcreteOp *>(this)).getContext());
      assert(symbols.empty() || symbols.size() == (*static_cast<ConcreteOp *>(this)).getNumPorts());
      (*static_cast<ConcreteOp *>(this)).setPortSymbolsAttr(ArrayAttr::get((*static_cast<ConcreteOp *>(this)).getContext(), symbols));
    }

    /// Get a port's location attribute
    LocationAttr getPortLocationAttr(size_t portIndex) {
      return llvm::cast<LocationAttr>((*static_cast<ConcreteOp *>(this)).getPortLocationsAttr()[portIndex]);
    }

    /// Get a port's location
    Location getPortLocation(size_t portIndex) {
      return (*static_cast<ConcreteOp *>(this)).getPortLocationAttr(portIndex);
    }

    /// Get domain information attribute
    ArrayAttr getDomainInfoAttr() {
      return {};
    }

    /// Get a port's domain info attribute
    Attribute getDomainInfoAttrForPort(size_t portIndex) {
      auto domains = (*static_cast<ConcreteOp *>(this)).getDomainInfoAttr();
      if (domains.empty())
        return domains; // domains already is an empty array
      return domains[portIndex];
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      static_assert(
        ConcreteOp::template hasTrait<::mlir::SymbolOpInterface::Trait>(),
        "expected operation to be a symbol");
    static_assert(
        ConcreteOp::template hasTrait<OpTrait::InnerSymbolTable>(),
        "expected operation to be an inner symbol table");
    return verifyModuleLikeOpInterface(cast<::circt::firrtl::FModuleLike>(op));
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct FInstanceLikeTrait : public ::mlir::OpInterface<FInstanceLike, detail::FInstanceLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the number of ports
    size_t getNumPorts() {
      return (*static_cast<ConcreteOp *>(this)).getNumResults();
    }

    /// Get the port direction for the specified result number
    Direction getPortDirection(size_t resultNo) {
      return direction::get((*static_cast<ConcreteOp *>(this)).getPortDirections()[resultNo]);
    }

    /// Get the port name attribute for the specified result number
    StringAttr getPortNameAttr(size_t resultNo) {
      return llvm::cast<StringAttr>((*static_cast<ConcreteOp *>(this)).getPortNames()[resultNo]);
    }

    /// Get the port name for the specified result number
    StringRef getPortName(size_t resultNo) {
      return (*static_cast<ConcreteOp *>(this)).getPortNameAttr(resultNo).getValue();
    }

    /// Get the port location for the specified result number
    Location getPortLocation(size_t resultNo) {
      return (*static_cast<ConcreteOp *>(this)).getLoc();
    }

    /// Get domain information attribute
    ArrayAttr getDomainInfoAttr() {
      return (*static_cast<ConcreteOp *>(this)).getDomainInfo();
    }

    /// Set domain information attribute
    void setDomainInfoAttr(ArrayAttr domainInfo) {
      (*static_cast<ConcreteOp *>(this)).setDomainInfo(domainInfo);
    }

    /// Get domain information attribute
    Attribute getPortDomain(size_t portIndex) {
      return (*static_cast<ConcreteOp *>(this)).getDomainInfo()[portIndex];
    }

    /// Get layers attribute
    ArrayAttr getLayersAttr() {
      return (*static_cast<ConcreteOp *>(this)).getLayers();
    }

    /// Set layers attribute
    void setLayersAttr(ArrayAttr layers) {
      (*static_cast<ConcreteOp *>(this)).setLayers(layers);
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct ClassLikeTrait : public ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the type for instances of this class
    ClassType getInstanceType() {
      return detail::getInstanceTypeForClassLike((*static_cast<ConcreteOp *>(this)));
    }

    /// Verify that the given type agrees with this class
    LogicalResult verifyType(::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
      return detail::verifyTypeAgainstClassLike((*static_cast<ConcreteOp *>(this)), type, emitError);
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct FConnectLikeTrait : public ::mlir::OpInterface<FConnectLike, detail::FConnectLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Return connection behavior kind.
    static ConnectBehaviorKind getConnectBehaviorKind() {
      return ConnectBehaviorKind::LastConnect;
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct FNamableOpTrait : public ::mlir::OpInterface<FNamableOp, detail::FNamableOpInterfaceTraits>::Trait<ConcreteOp> {

    /// Return true if the name is droppable.
    bool hasDroppableName() {
      return (*static_cast<ConcreteOp *>(this)).getNameKind() == NameKindEnum::DroppableName;
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl::detail {

  template <typename ConcreteOp>
  struct ForceableTrait : public ::mlir::OpInterface<Forceable, detail::ForceableInterfaceTraits>::Trait<ConcreteOp> {

    /// Return true if the operation is forceable.
    bool isForceable() {
      return (*static_cast<ConcreteOp *>(this)).getForceable();
    }

    /// Return data value that will be targeted.
    mlir::TypedValue<FIRRTLBaseType> getData() {
      return llvm::cast<mlir::TypedValue<FIRRTLBaseType>>((*static_cast<ConcreteOp *>(this)).getDataRaw());
    }

    /// Return raw data value that will be targeted.
    Value getDataRaw() {
      return (*static_cast<ConcreteOp *>(this)).getResult();
    }

    /// Return data type that will be referenced.
    FIRRTLBaseType getDataType() {
      return firrtl::type_cast<FIRRTLBaseType>((*static_cast<ConcreteOp *>(this)).getDataRaw().getType());
    }

    /// Return reference result, or null if not active.
    mlir::TypedValue<RefType> getDataRef() {
      return llvm::cast_or_null<mlir::TypedValue<RefType>>((*static_cast<ConcreteOp *>(this)).getRef());
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return detail::verifyForceableOp(cast<::circt::firrtl::Forceable>(op));
    }
  };

} // namespace circt::firrtl::detail
namespace circt::firrtl {

template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getParameters(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getParameters();
}
template<typename ConcreteOp>
ConventionAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getConventionAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getConventionAttr();
}
template<typename ConcreteOp>
Convention detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getConvention(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getConvention();
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLayersAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getLayers(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLayers();
}
template<typename ConcreteOp>
mlir::DenseBoolArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirectionsAttr();
}
template<typename ConcreteOp>
ArrayRef<bool> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirections();
}
template<typename ConcreteOp>
Direction detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirection(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNamesAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNames();
}
template<typename ConcreteOp>
StringAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNameAttr(portIndex);
}
template<typename ConcreteOp>
StringRef detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortName(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortTypesAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortTypes();
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr portTypes) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortTypesAttr(portTypes);
}
template<typename ConcreteOp>
TypeAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortTypeAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortTypeAttr(portIndex);
}
template<typename ConcreteOp>
Type detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortType(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortAnnotationsAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortAnnotations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortAnnotations();
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr annotations) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortAnnotationsAttr(annotations);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getAnnotationsAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAnnotationsAttrForPort(portIndex);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getAnnotationsForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAnnotationsForPort(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbolsAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbols();
}
template<typename ConcreteOp>
circt::hw::InnerSymAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbolAttr(portIndex);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr symbols) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortSymbolsAttr(symbols);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<Attribute> symbols) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortSymbols(symbols);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortSymbolAttr(portIndex, symbol);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortLocationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocationsAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortLocations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocations();
}
template<typename ConcreteOp>
LocationAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortLocationAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocationAttr(portIndex);
}
template<typename ConcreteOp>
Location detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocation(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfoAttr();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getDomainInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfoAttr().getValue();
}
template<typename ConcreteOp>
Attribute detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getDomainInfoAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfoAttrForPort(portIndex);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr domainInfo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setDomainInfoAttr(domainInfo);
}
template<typename ConcreteOp>
SmallVector<PortInfo> detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::getPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPorts();
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> ports) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).insertPorts(ports);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::Model<ConcreteOp>::erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector& portIndices) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).erasePorts(portIndices);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getParameters(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getParameters(tablegen_opaque_val);
}
template<typename ConcreteOp>
ConventionAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getConventionAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getConventionAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
Convention detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getConvention(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getConvention(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLayersAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getLayers(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLayers(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::DenseBoolArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirectionsAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<bool> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirections(tablegen_opaque_val);
}
template<typename ConcreteOp>
Direction detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirection(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortNamesAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
StringAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortNameAttr(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
StringRef detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortName(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortTypesAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortTypes(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setPortTypesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr portTypes) {
  return static_cast<const ConcreteOp *>(impl)->setPortTypesAttr(tablegen_opaque_val, portTypes);
}
template<typename ConcreteOp>
TypeAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortTypeAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortTypeAttr(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
Type detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortType(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortAnnotationsAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortAnnotations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortAnnotations(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setPortAnnotationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr annotations) {
  return static_cast<const ConcreteOp *>(impl)->setPortAnnotationsAttr(tablegen_opaque_val, annotations);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getAnnotationsAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getAnnotationsAttrForPort(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getAnnotationsForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getAnnotationsForPort(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortSymbolsAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortSymbols(tablegen_opaque_val);
}
template<typename ConcreteOp>
circt::hw::InnerSymAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortSymbolAttr(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setPortSymbolsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr symbols) {
  return static_cast<const ConcreteOp *>(impl)->setPortSymbolsAttr(tablegen_opaque_val, symbols);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setPortSymbols(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<Attribute> symbols) {
  return static_cast<const ConcreteOp *>(impl)->setPortSymbols(tablegen_opaque_val, symbols);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setPortSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol) {
  return static_cast<const ConcreteOp *>(impl)->setPortSymbolAttr(tablegen_opaque_val, portIndex, symbol);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLocationsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortLocationsAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLocations(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortLocations(tablegen_opaque_val);
}
template<typename ConcreteOp>
LocationAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLocationAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortLocationAttr(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
Location detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortLocation(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDomainInfoAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDomainInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDomainInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
Attribute detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDomainInfoAttrForPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getDomainInfoAttrForPort(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr domainInfo) {
  return static_cast<const ConcreteOp *>(impl)->setDomainInfoAttr(tablegen_opaque_val, domainInfo);
}
template<typename ConcreteOp>
SmallVector<PortInfo> detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> ports) {
  return static_cast<const ConcreteOp *>(impl)->insertPorts(tablegen_opaque_val, ports);
}
template<typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector& portIndices) {
  return static_cast<const ConcreteOp *>(impl)->erasePorts(tablegen_opaque_val, portIndices);
}
template<typename ConcreteModel, typename ConcreteOp>
Direction detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortDirection(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return direction::get((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirections()[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
StringAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortNameAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return llvm::cast<StringAttr>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNames()[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
StringRef detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortName(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNameAttr(portIndex).getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
TypeAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortTypeAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return llvm::cast<TypeAttr>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortTypes()[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
Type detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortType(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortTypeAttr(portIndex).getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getAnnotationsAttrForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
auto annos = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortAnnotationsAttr();
      if (annos.empty())
        return annos; // annos already is an empty array
      return llvm::cast<ArrayAttr>(annos[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
ArrayRef<Attribute> detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getAnnotationsForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAnnotationsAttrForPort(portIndex).getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
circt::hw::InnerSymAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortSymbolAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
auto syms = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbols();
      if (syms.empty() ||
          llvm::cast<hw::InnerSymAttr>(syms[portIndex]).empty())
        return hw::InnerSymAttr();
      return llvm::cast<hw::InnerSymAttr>(syms[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setPortSymbolAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex, circt::hw::InnerSymAttr symbol) const {
SmallVector<Attribute> symbols((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbols().begin(),
                                     (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortSymbols().end());
      if (symbols.empty()) {
        if (symbol.empty())
          return;
        symbols.resize((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumPorts(),
                      hw::InnerSymAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getContext()));
      }
      assert(symbols.size() == (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumPorts());
      symbols[portIndex] = symbol;

      FModuleLike::fixupPortSymsArray(symbols, (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getContext());
      assert(symbols.empty() || symbols.size() == (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumPorts());
      (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPortSymbolsAttr(ArrayAttr::get((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getContext(), symbols));
}
template<typename ConcreteModel, typename ConcreteOp>
LocationAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortLocationAttr(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return llvm::cast<LocationAttr>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocationsAttr()[portIndex]);
}
template<typename ConcreteModel, typename ConcreteOp>
Location detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortLocation(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocationAttr(portIndex);
}
template<typename ConcreteModel, typename ConcreteOp>
ArrayAttr detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDomainInfoAttr(::mlir::Operation *tablegen_opaque_val) const {
return {};
}
template<typename ConcreteModel, typename ConcreteOp>
Attribute detail::FModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDomainInfoAttrForPort(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
auto domains = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfoAttr();
      if (domains.empty())
        return domains; // domains already is an empty array
      return domains[portIndex];
}

} // namespace circt::firrtl
namespace circt::firrtl {

template<typename ConcreteOp>
size_t detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumPorts();
}
template<typename ConcreteOp>
Direction detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirection(resultNo);
}
template<typename ConcreteOp>
StringAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNameAttr(resultNo);
}
template<typename ConcreteOp>
StringRef detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortName(resultNo);
}
template<typename ConcreteOp>
Location detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLocation(resultNo);
}
template<typename ConcreteOp>
mlir::DenseBoolArrayAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirectionsAttr();
}
template<typename ConcreteOp>
ArrayRef<bool> detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirections();
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNamesAttr();
}
template<typename ConcreteOp>
::circt::hw::InnerSymAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerSymAttr();
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::cloneWithInsertedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneWithInsertedPorts(insertions);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::cloneWithInsertedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneWithInsertedPortsAndReplaceUses(insertions);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::cloneWithErasedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneWithErasedPorts(erasures);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::cloneWithErasedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneWithErasedPortsAndReplaceUses(erasures);
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfoAttr();
}
template<typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setDomainInfoAttr(domainInfo);
}
template<typename ConcreteOp>
Attribute detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getPortDomain(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDomain(portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLayersAttr();
}
template<typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::Model<ConcreteOp>::setLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr layers) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setLayersAttr(layers);
}
template<typename ConcreteOp>
size_t detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
Direction detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirection(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirection(tablegen_opaque_val, resultNo);
}
template<typename ConcreteOp>
StringAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return static_cast<const ConcreteOp *>(impl)->getPortNameAttr(tablegen_opaque_val, resultNo);
}
template<typename ConcreteOp>
StringRef detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return static_cast<const ConcreteOp *>(impl)->getPortName(tablegen_opaque_val, resultNo);
}
template<typename ConcreteOp>
Location detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLocation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t resultNo) {
  return static_cast<const ConcreteOp *>(impl)->getPortLocation(tablegen_opaque_val, resultNo);
}
template<typename ConcreteOp>
mlir::DenseBoolArrayAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirectionsAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirectionsAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<bool> detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortDirections(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortNamesAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::circt::hw::InnerSymAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInnerSymAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::cloneWithInsertedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
  return static_cast<const ConcreteOp *>(impl)->cloneWithInsertedPorts(tablegen_opaque_val, insertions);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::cloneWithInsertedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
  return static_cast<const ConcreteOp *>(impl)->cloneWithInsertedPortsAndReplaceUses(tablegen_opaque_val, insertions);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::cloneWithErasedPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures) {
  return static_cast<const ConcreteOp *>(impl)->cloneWithErasedPorts(tablegen_opaque_val, erasures);
}
template<typename ConcreteOp>
FInstanceLike detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::cloneWithErasedPortsAndReplaceUses(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::BitVector & erasures) {
  return static_cast<const ConcreteOp *>(impl)->cloneWithErasedPortsAndReplaceUses(tablegen_opaque_val, erasures);
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDomainInfoAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setDomainInfoAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo) {
  return static_cast<const ConcreteOp *>(impl)->setDomainInfoAttr(tablegen_opaque_val, domainInfo);
}
template<typename ConcreteOp>
Attribute detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortDomain(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t portIndex) {
  return static_cast<const ConcreteOp *>(impl)->getPortDomain(tablegen_opaque_val, portIndex);
}
template<typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLayersAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setLayersAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayAttr layers) {
  return static_cast<const ConcreteOp *>(impl)->setLayersAttr(tablegen_opaque_val, layers);
}
template<typename ConcreteModel, typename ConcreteOp>
size_t detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNumPorts(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumResults();
}
template<typename ConcreteModel, typename ConcreteOp>
Direction detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortDirection(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const {
return direction::get((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortDirections()[resultNo]);
}
template<typename ConcreteModel, typename ConcreteOp>
StringAttr detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortNameAttr(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const {
return llvm::cast<StringAttr>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNames()[resultNo]);
}
template<typename ConcreteModel, typename ConcreteOp>
StringRef detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortName(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNameAttr(resultNo).getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
Location detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortLocation(::mlir::Operation *tablegen_opaque_val, size_t resultNo) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLoc();
}
template<typename ConcreteModel, typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDomainInfoAttr(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfo();
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setDomainInfoAttr(::mlir::Operation *tablegen_opaque_val, ArrayAttr domainInfo) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setDomainInfo(domainInfo);
}
template<typename ConcreteModel, typename ConcreteOp>
Attribute detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortDomain(::mlir::Operation *tablegen_opaque_val, size_t portIndex) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDomainInfo()[portIndex];
}
template<typename ConcreteModel, typename ConcreteOp>
ArrayAttr detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getLayersAttr(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLayers();
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::FInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setLayersAttr(::mlir::Operation *tablegen_opaque_val, ArrayAttr layers) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setLayers(layers);
}

} // namespace circt::firrtl
namespace circt::firrtl {

template<typename ConcreteOp>
ClassType detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getInstanceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInstanceType();
}
template<typename ConcreteOp>
LogicalResult detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::verifyType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).verifyType(type, emitError);
}
template<typename ConcreteOp>
ClassType detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getInstanceType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInstanceType(tablegen_opaque_val);
}
template<typename ConcreteOp>
LogicalResult detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::verifyType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  return static_cast<const ConcreteOp *>(impl)->verifyType(tablegen_opaque_val, type, emitError);
}
template<typename ConcreteModel, typename ConcreteOp>
ClassType detail::ClassLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInstanceType(::mlir::Operation *tablegen_opaque_val) const {
return detail::getInstanceTypeForClassLike((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
}
template<typename ConcreteModel, typename ConcreteOp>
LogicalResult detail::ClassLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::verifyType(::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) const {
return detail::verifyTypeAgainstClassLike((llvm::cast<ConcreteOp>(tablegen_opaque_val)), type, emitError);
}

} // namespace circt::firrtl
namespace circt::firrtl {

template<typename ConcreteOp>
Value detail::FConnectLikeInterfaceTraits::Model<ConcreteOp>::getDest(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDest();
}
template<typename ConcreteOp>
Value detail::FConnectLikeInterfaceTraits::Model<ConcreteOp>::getSrc(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSrc();
}
template<typename ConcreteOp>
ConnectBehaviorKind detail::FConnectLikeInterfaceTraits::Model<ConcreteOp>::getConnectBehaviorKind() {
  return ConcreteOp::getConnectBehaviorKind();
}
template<typename ConcreteOp>
bool detail::FConnectLikeInterfaceTraits::Model<ConcreteOp>::hasStaticSingleConnectBehavior() {
  return getConnectBehaviorKind() == ConnectBehaviorKind::StaticSingleConnect;
}
template<typename ConcreteOp>
bool detail::FConnectLikeInterfaceTraits::Model<ConcreteOp>::hasLastConnectBehavior() {
  return getConnectBehaviorKind() == ConnectBehaviorKind::LastConnect;
}
template<typename ConcreteOp>
Value detail::FConnectLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDest(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDest(tablegen_opaque_val);
}
template<typename ConcreteOp>
Value detail::FConnectLikeInterfaceTraits::FallbackModel<ConcreteOp>::getSrc(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSrc(tablegen_opaque_val);
}
template<typename ConcreteOp>
ConnectBehaviorKind detail::FConnectLikeInterfaceTraits::FallbackModel<ConcreteOp>::getConnectBehaviorKind() {
  return ConcreteOp::getConnectBehaviorKind();
}
template<typename ConcreteOp>
bool detail::FConnectLikeInterfaceTraits::FallbackModel<ConcreteOp>::hasStaticSingleConnectBehavior() {
  return ConcreteOp::hasStaticSingleConnectBehavior();
}
template<typename ConcreteOp>
bool detail::FConnectLikeInterfaceTraits::FallbackModel<ConcreteOp>::hasLastConnectBehavior() {
  return ConcreteOp::hasLastConnectBehavior();
}
template<typename ConcreteModel, typename ConcreteOp>
ConnectBehaviorKind detail::FConnectLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getConnectBehaviorKind() {
return ConnectBehaviorKind::LastConnect;
}

} // namespace circt::firrtl
namespace circt::firrtl {

template<typename ConcreteOp>
::mlir::StringAttr detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameAttr();
}
template<typename ConcreteOp>
::llvm::StringRef detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getName();
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::setNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setNameAttr(name);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::setName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::StringRef name) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setName(name);
}
template<typename ConcreteOp>
::circt::firrtl::NameKindEnumAttr detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::getNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameKindAttr();
}
template<typename ConcreteOp>
::circt::firrtl::NameKindEnum detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::getNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameKind();
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::setNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnumAttr nameKind) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setNameKindAttr(nameKind);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::setNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnum nameKind) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setNameKind(nameKind);
}
template<typename ConcreteOp>
bool detail::FNamableOpInterfaceTraits::Model<ConcreteOp>::hasDroppableName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).hasDroppableName();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::StringRef detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getName(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::setNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) {
  return static_cast<const ConcreteOp *>(impl)->setNameAttr(tablegen_opaque_val, name);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::setName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::StringRef name) {
  return static_cast<const ConcreteOp *>(impl)->setName(tablegen_opaque_val, name);
}
template<typename ConcreteOp>
::circt::firrtl::NameKindEnumAttr detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::getNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameKindAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::circt::firrtl::NameKindEnum detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::getNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameKind(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::setNameKindAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnumAttr nameKind) {
  return static_cast<const ConcreteOp *>(impl)->setNameKindAttr(tablegen_opaque_val, nameKind);
}
template<typename ConcreteOp>
void detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::setNameKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::firrtl::NameKindEnum nameKind) {
  return static_cast<const ConcreteOp *>(impl)->setNameKind(tablegen_opaque_val, nameKind);
}
template<typename ConcreteOp>
bool detail::FNamableOpInterfaceTraits::FallbackModel<ConcreteOp>::hasDroppableName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->hasDroppableName(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::FNamableOpInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::hasDroppableName(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameKind() == NameKindEnum::DroppableName;
}

} // namespace circt::firrtl
namespace circt::firrtl {

template<typename ConcreteOp>
bool detail::ForceableInterfaceTraits::Model<ConcreteOp>::isForceable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isForceable();
}
template<typename ConcreteOp>
mlir::TypedValue<FIRRTLBaseType> detail::ForceableInterfaceTraits::Model<ConcreteOp>::getData(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getData();
}
template<typename ConcreteOp>
Value detail::ForceableInterfaceTraits::Model<ConcreteOp>::getDataRaw(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataRaw();
}
template<typename ConcreteOp>
FIRRTLBaseType detail::ForceableInterfaceTraits::Model<ConcreteOp>::getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataType();
}
template<typename ConcreteOp>
mlir::TypedValue<RefType> detail::ForceableInterfaceTraits::Model<ConcreteOp>::getDataRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataRef();
}
template<typename ConcreteOp>
bool detail::ForceableInterfaceTraits::FallbackModel<ConcreteOp>::isForceable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isForceable(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::TypedValue<FIRRTLBaseType> detail::ForceableInterfaceTraits::FallbackModel<ConcreteOp>::getData(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getData(tablegen_opaque_val);
}
template<typename ConcreteOp>
Value detail::ForceableInterfaceTraits::FallbackModel<ConcreteOp>::getDataRaw(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataRaw(tablegen_opaque_val);
}
template<typename ConcreteOp>
FIRRTLBaseType detail::ForceableInterfaceTraits::FallbackModel<ConcreteOp>::getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataType(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::TypedValue<RefType> detail::ForceableInterfaceTraits::FallbackModel<ConcreteOp>::getDataRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataRef(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::ForceableInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isForceable(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getForceable();
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::TypedValue<FIRRTLBaseType> detail::ForceableInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getData(::mlir::Operation *tablegen_opaque_val) const {
return llvm::cast<mlir::TypedValue<FIRRTLBaseType>>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataRaw());
}
template<typename ConcreteModel, typename ConcreteOp>
Value detail::ForceableInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDataRaw(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResult();
}
template<typename ConcreteModel, typename ConcreteOp>
FIRRTLBaseType detail::ForceableInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDataType(::mlir::Operation *tablegen_opaque_val) const {
return firrtl::type_cast<FIRRTLBaseType>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataRaw().getType());
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::TypedValue<RefType> detail::ForceableInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDataRef(::mlir::Operation *tablegen_opaque_val) const {
return llvm::cast_or_null<mlir::TypedValue<RefType>>((llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRef());
}

} // namespace circt::firrtl
