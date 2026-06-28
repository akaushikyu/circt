/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

/// Operations which produce a unified port list representation
class PortList;

} // namespace circt::hw
namespace circt::hw {

/// Provide common module information.
class HWModuleLike;

} // namespace circt::hw
namespace circt::hw {

/// Provide methods to mutate a module.
class HWMutableModuleLike;

} // namespace circt::hw
namespace circt::hw {

/// This interface indicates that the module like op is emittable in SV and
/// requires SV legalization on its body.
class HWEmittableModuleLike;

} // namespace circt::hw
namespace circt::hw {

/// Provide common instance information.
class HWInstanceLike;

} // namespace circt::hw
namespace circt::hw {

/// This interface describes an operation that may define an
/// `inner_sym`.  An `inner_sym` operation resides
/// in arbitrarily-nested regions of a region that defines a
/// `InnerSymbolTable`.
/// Inner Symbols are different from normal symbols due to
/// MLIR symbol table resolution rules.  Specifically normal
/// symbols are resolved by first going up to the closest
/// parent symbol table and resolving from there (recursing
/// down for complex symbol paths).  In HW and SV, modules
/// define a symbol in a circuit or std.module symbol table.
/// For instances to be able to resolve the modules they
/// instantiate, the symbol use in an instance must resolve
/// in the top-level symbol table.  If a module were a
/// symbol table, instances resolving a symbol would start from
/// their own module, never seeing other modules (since
/// resolution would start in the parent module of the
/// instance and be unable to go to the global scope).
/// The second problem arises from nesting.  Symbols defining
/// ops must be immediate children of a symbol table.  HW
/// and SV operations which define a inner_sym are grandchildren,
/// at least, of a symbol table and may be much further nested.
/// Lastly, ports need to define inner_sym, something not allowed
/// by normal symbols.
/// 
/// Any operation implementing an InnerSymbol may have the inner symbol be
/// optional and all methods should be robuse to the attribute not being
/// defined.
class InnerSymbolOpInterface;

} // namespace circt::hw
namespace circt::hw {

/// This interface describes an operation that may use a `InnerRef`. This
/// interface allows for users of inner symbols to hook into verification and
/// other inner symbol related utilities that are either costly or otherwise
/// disallowed within a traditional operation.
class InnerRefUserOpInterface;

} // namespace circt::hw
namespace circt::hw {

/// This interface is used for specifying the combinational dataflow that exists
/// in the results and operands of an operation.
/// Any operation that doesn't implement this interface is assumed to have a
/// combinational dependence from each operand to each result.
class CombDataFlow;

} // namespace circt::hw
namespace circt::hw {

/// Operations which produce a unified port list representation
namespace detail {
struct PortListInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    SmallVector<::circt::hw::PortInfo> (*getPortList)(const Concept *impl, ::mlir::Operation *);
    ::circt::hw::PortInfo (*getPort)(const Concept *impl, ::mlir::Operation *, size_t);
    size_t (*getPortIdForInputId)(const Concept *impl, ::mlir::Operation *, size_t);
    size_t (*getPortIdForOutputId)(const Concept *impl, ::mlir::Operation *, size_t);
    size_t (*getNumPorts)(const Concept *impl, ::mlir::Operation *);
    size_t (*getNumInputPorts)(const Concept *impl, ::mlir::Operation *);
    size_t (*getNumOutputPorts)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hw::PortList;
    Model() : Concept{getPortList, getPort, getPortIdForInputId, getPortIdForOutputId, getNumPorts, getNumInputPorts, getNumOutputPorts} {}

    static inline SmallVector<::circt::hw::PortInfo> getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::PortInfo getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getPortIdForInputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getPortIdForOutputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline size_t getNumInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline size_t getNumOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::PortList;
    FallbackModel() : Concept{getPortList, getPort, getPortIdForInputId, getPortIdForOutputId, getNumPorts, getNumInputPorts, getNumOutputPorts} {}

    static inline SmallVector<::circt::hw::PortInfo> getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::PortInfo getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getPortIdForInputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getPortIdForOutputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline size_t getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline size_t getNumInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline size_t getNumOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct PortListTrait;

} // namespace detail
class PortList : public ::mlir::OpInterface<PortList, detail::PortListInterfaceTraits> {
public:
  using ::mlir::OpInterface<PortList, detail::PortListInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::PortListTrait<ConcreteOp> {};

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
};

} // namespace circt::hw
namespace circt::hw {

/// Provide common module information.
namespace detail {
struct HWModuleLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::circt::hw::ModuleType (*getHWModuleType)(const Concept *impl, ::mlir::Operation *);
    ArrayRef<Attribute> (*getAllPortAttrs)(const Concept *impl, ::mlir::Operation *);
    void (*setAllPortAttrs)(const Concept *impl, ::mlir::Operation *, ArrayRef<Attribute>);
    void (*removeAllPortAttrs)(const Concept *impl, ::mlir::Operation *);
    SmallVector<Location> (*getAllPortLocs)(const Concept *impl, ::mlir::Operation *);
    void (*setAllPortLocsAttrs)(const Concept *impl, ::mlir::Operation *, ArrayRef<Attribute>);
    void (*setHWModuleType)(const Concept *impl, ::mlir::Operation *, ::circt::hw::ModuleType);
    void (*setAllPortNames)(const Concept *impl, ::mlir::Operation *, ArrayRef<Attribute>);
    /// The base classes of this interface.
    const ::mlir::SymbolOpInterface::Concept *implSymbolOpInterface = nullptr;
    const circt::hw::PortList::Concept *implPortList = nullptr;
    const ::circt::igraph::ModuleOpInterface::Concept *implModuleOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implSymbolOpInterface = interfaceMap.lookup<::mlir::SymbolOpInterface>();
      assert(implSymbolOpInterface && "`circt::hw::HWModuleLike` expected its base interface `::mlir::SymbolOpInterface` to be registered");
      implPortList = interfaceMap.lookup<circt::hw::PortList>();
      assert(implPortList && "`circt::hw::HWModuleLike` expected its base interface `circt::hw::PortList` to be registered");
      implModuleOpInterface = interfaceMap.lookup<::circt::igraph::ModuleOpInterface>();
      assert(implModuleOpInterface && "`circt::hw::HWModuleLike` expected its base interface `::circt::igraph::ModuleOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hw::HWModuleLike;
    Model() : Concept{getHWModuleType, getAllPortAttrs, setAllPortAttrs, removeAllPortAttrs, getAllPortLocs, setAllPortLocsAttrs, setHWModuleType, setAllPortNames} {}

    static inline ::circt::hw::ModuleType getHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> attrs);
    static inline void removeAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Location> getAllPortLocs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setAllPortLocsAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> locs);
    static inline void setHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::ModuleType type);
    static inline void setAllPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> names);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::HWModuleLike;
    FallbackModel() : Concept{getHWModuleType, getAllPortAttrs, setAllPortAttrs, removeAllPortAttrs, getAllPortLocs, setAllPortLocsAttrs, setHWModuleType, setAllPortNames} {}

    static inline ::circt::hw::ModuleType getHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ArrayRef<Attribute> getAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> attrs);
    static inline void removeAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Location> getAllPortLocs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setAllPortLocsAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> locs);
    static inline void setHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::ModuleType type);
    static inline void setAllPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> names);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct HWModuleLikeTrait;

} // namespace detail
class HWModuleLike : public ::mlir::OpInterface<HWModuleLike, detail::HWModuleLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<HWModuleLike, detail::HWModuleLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::HWModuleLikeTrait<ConcreteOp> {};

  /// Get the module type
  ::circt::hw::ModuleType getHWModuleType();

  /// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
  ArrayRef<Attribute> getAllPortAttrs();

  /// Set the port Attributes
  void setAllPortAttrs(ArrayRef<Attribute> attrs);

  /// Remove the port Attributes
  void removeAllPortAttrs();

  /// Get the port Locations
  SmallVector<Location> getAllPortLocs();

  /// Set the port Locations
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);

  /// Set the module type (and port names)
  void setHWModuleType(::circt::hw::ModuleType type);

  /// Set the port names
  void setAllPortNames(ArrayRef<Attribute> names);

    /// Attribute name for port symbols.
    static StringRef getPortSymbolAttrName() {
      return "hw.exportPort";
    }

    /// Return the region containing the body of this function.
    Region &getModuleBody() { return (*this)->getRegion(0); }
    Block *getBodyBlock() {
      Region &body = getModuleBody();
      if (body.empty())
        return nullptr;
      return &body.front();
    }

    /// Returns the entry block argument at the given index.
    BlockArgument getArgumentForInput(unsigned idx) {
      return (*this).getModuleBody().getArgument(idx);
    }

    /// Returns the entry block argument for the given port.  May be null.
    BlockArgument getArgumentForPort(unsigned idx) {
      return (*this).getModuleBody().getArgument((*this).getHWModuleType().getInputIdForPortId(idx));
    }

    SmallVector<mlir::Type> getPortTypes() {
      return (*this).getHWModuleType().getPortTypes();
    }

    SmallVector<mlir::Type> getInputTypes() {
      return (*this).getHWModuleType().getInputTypes();
    }

    SmallVector<mlir::Type> getOutputTypes() {
      return (*this).getHWModuleType().getOutputTypes();
    }

    /// Return the set of names on input and inout ports
    SmallVector<Attribute> getInputNames() {
      return (*this).getHWModuleType().getInputNames();
    }

    /// Return the set of names on output ports
    SmallVector<Attribute> getOutputNames() {
      return (*this).getHWModuleType().getOutputNames();
    }

    void setInputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForInputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    void setOutputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForOutputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    // Get the name for the specified input or inout port
    StringRef getPortName(size_t idx) {
      return (*this).getHWModuleType().getPortName(idx);
    }

    // Get the name for the specified input or inout port
    StringRef getInputName(size_t idx) {
      return (*this).getHWModuleType().getInputName(idx);
    }

    // Get the name for the specified output port
    StringRef getOutputName(size_t idx) {
      return (*this).getHWModuleType().getOutputName(idx);
    }

    StringAttr getInputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getInputNameAttr(idx);
    }

    StringAttr getOutputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getOutputNameAttr(idx);
    }

    Attribute getPortAttrs(size_t idx) {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return nullptr;
      return attrs[idx];
    }

    SmallVector<Attribute> getAllInputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumInputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForInputId(x)];
      return retval;
    }

    SmallVector<Attribute> getAllOutputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumOutputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForOutputId(x)];
      return retval;
    }

    void setAllInputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForInputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    void setAllOutputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForOutputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    Attribute getInputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForInputId(idx)];
    }

    Attribute getOutputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForOutputId(idx)];
    }

    void setPortAttrs(size_t idx, DictionaryAttr attr) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      attrs[idx] = attr;
      (*this).setAllPortAttrs(attrs);
    }

    void setPortAttr(size_t idx, StringAttr name, Attribute value) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      NamedAttrList pattr(cast<DictionaryAttr>(attrs[idx]));
      Attribute oldValue;
      if (!value)
        oldValue = pattr.erase(name);
      else
        oldValue = pattr.set(name, value);
      if (oldValue != value) {
        attrs[idx] = pattr.getDictionary((*this).getContext());
        (*this).setAllPortAttrs(attrs);
      }
    }

    void setPortAttrs(StringAttr attrName, ArrayRef<Attribute> newAttrs) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      auto ctxt = (*this).getContext();
      assert(newAttrs.size() == attrs.size());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx) {
        NamedAttrList pattr(cast_or_null<mlir::DictionaryAttr>(attrs[idx]));
        auto newAttr = newAttrs[idx];
        if (newAttr)
          pattr.set(attrName, newAttr);
        else
          pattr.erase(attrName);
        attrs[idx] = pattr.getDictionary(ctxt);
      }
      (*this).setAllPortAttrs(attrs);
    }

    void setAllPortLocs(ArrayRef<Location> locs) {
      std::vector<Attribute> nLocs(locs.begin(), locs.end());
      (*this).setAllPortLocsAttrs(nLocs);
    }

    Location getPortLoc(size_t idx) {
      return (*this).getAllPortLocs()[idx];
    }

    void setPortLoc(size_t idx, Location loc) {
      auto locs = (*this).getAllPortLocs();
      locs[idx] = loc;
      return (*this).setAllPortLocs(locs);
    }

    Location getInputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForInputId(idx)];
    }

    Location getOutputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForOutputId(idx)];
    }

    SmallVector<Location> getInputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return retval;
    }

    ArrayAttr getInputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setInputLocs(ArrayRef<Location> inLocs) {
      assert(inLocs.size() == (*this).getNumInputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = inLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForInputId(idx)] = inLocs[idx];
      (*this).setAllPortLocs(newLocs);

    }

    SmallVector<Location> getOutputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return retval;
    }

    ArrayAttr getOutputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setOutputLocs(ArrayRef<Location> outLocs) {
      assert(outLocs.size() == (*this).getNumOutputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = outLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForOutputId(idx)] = outLocs[idx];
      (*this).setAllPortLocs(newLocs);
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

} // namespace circt::hw
namespace circt::hw {

/// Provide methods to mutate a module.
namespace detail {
struct HWMutableModuleLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::circt::hw::ModulePortLookupInfo (*getPortLookupInfo)(const Concept *impl, ::mlir::Operation *);
    void (*modifyPorts)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>>, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>>, ArrayRef<unsigned>, ArrayRef<unsigned>);
    void (*insertPorts)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>>, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>>);
    void (*erasePorts)(const Concept *impl, ::mlir::Operation *, ArrayRef<unsigned>, ArrayRef<unsigned>);
    void (*appendOutputs)(const Concept *impl, ::mlir::Operation *, ArrayRef<std::pair<StringAttr, Value>>);
    /// The base classes of this interface.
    const ::mlir::SymbolOpInterface::Concept *implSymbolOpInterface = nullptr;
    const circt::hw::PortList::Concept *implPortList = nullptr;
    const ::circt::igraph::ModuleOpInterface::Concept *implModuleOpInterface = nullptr;
    const circt::hw::HWModuleLike::Concept *implHWModuleLike = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implSymbolOpInterface = interfaceMap.lookup<::mlir::SymbolOpInterface>();
      assert(implSymbolOpInterface && "`circt::hw::HWMutableModuleLike` expected its base interface `::mlir::SymbolOpInterface` to be registered");
      implPortList = interfaceMap.lookup<circt::hw::PortList>();
      assert(implPortList && "`circt::hw::HWMutableModuleLike` expected its base interface `circt::hw::PortList` to be registered");
      implModuleOpInterface = interfaceMap.lookup<::circt::igraph::ModuleOpInterface>();
      assert(implModuleOpInterface && "`circt::hw::HWMutableModuleLike` expected its base interface `::circt::igraph::ModuleOpInterface` to be registered");
      implHWModuleLike = interfaceMap.lookup<circt::hw::HWModuleLike>();
      assert(implHWModuleLike && "`circt::hw::HWMutableModuleLike` expected its base interface `circt::hw::HWModuleLike` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hw::HWMutableModuleLike;
    Model() : Concept{getPortLookupInfo, modifyPorts, insertPorts, erasePorts, appendOutputs} {}

    static inline ::circt::hw::ModulePortLookupInfo getPortLookupInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void modifyPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);
    static inline void insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs);
    static inline void erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);
    static inline void appendOutputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<StringAttr, Value>> outputs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::HWMutableModuleLike;
    FallbackModel() : Concept{getPortLookupInfo, modifyPorts, insertPorts, erasePorts, appendOutputs} {}

    static inline ::circt::hw::ModulePortLookupInfo getPortLookupInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void modifyPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);
    static inline void insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs);
    static inline void erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);
    static inline void appendOutputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<StringAttr, Value>> outputs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::circt::hw::ModulePortLookupInfo getPortLookupInfo(::mlir::Operation *tablegen_opaque_val) const;
    void insertPorts(::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) const;
    void erasePorts(::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) const;
  };
};
template <typename ConcreteOp>
struct HWMutableModuleLikeTrait;

} // namespace detail
class HWMutableModuleLike : public ::mlir::OpInterface<HWMutableModuleLike, detail::HWMutableModuleLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<HWMutableModuleLike, detail::HWMutableModuleLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::HWMutableModuleLikeTrait<ConcreteOp> {};

  /// Get a handle to a utility class which provides by-name lookup of port indices. The returned object does _not_ update if the module is mutated.
  ::circt::hw::ModulePortLookupInfo getPortLookupInfo();

  /// Insert and remove input and output ports
  void modifyPorts(ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);

  /// Insert ports into this module
  void insertPorts(ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs);

  /// Erase ports from this module
  void erasePorts(ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs);

  /// Append output values to this module
  void appendOutputs(ArrayRef<std::pair<StringAttr, Value>> outputs);
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
  // Inherited from circt::hw::HWModuleLike
  //===----------------------------------------------------------------===//

  operator circt::hw::HWModuleLike () const {
    if (!*this) return nullptr;
    return circt::hw::HWModuleLike(*this, getImpl()->implHWModuleLike);
  }


  /// Get the module type
  ::circt::hw::ModuleType getHWModuleType();

  /// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
  ArrayRef<Attribute> getAllPortAttrs();

  /// Set the port Attributes
  void setAllPortAttrs(ArrayRef<Attribute> attrs);

  /// Remove the port Attributes
  void removeAllPortAttrs();

  /// Get the port Locations
  SmallVector<Location> getAllPortLocs();

  /// Set the port Locations
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);

  /// Set the module type (and port names)
  void setHWModuleType(::circt::hw::ModuleType type);

  /// Set the port names
  void setAllPortNames(ArrayRef<Attribute> names);

    /// Attribute name for port symbols.
    static StringRef getPortSymbolAttrName() {
      return "hw.exportPort";
    }

    /// Return the region containing the body of this function.
    Region &getModuleBody() { return (*this)->getRegion(0); }
    Block *getBodyBlock() {
      Region &body = getModuleBody();
      if (body.empty())
        return nullptr;
      return &body.front();
    }

    /// Returns the entry block argument at the given index.
    BlockArgument getArgumentForInput(unsigned idx) {
      return (*this).getModuleBody().getArgument(idx);
    }

    /// Returns the entry block argument for the given port.  May be null.
    BlockArgument getArgumentForPort(unsigned idx) {
      return (*this).getModuleBody().getArgument((*this).getHWModuleType().getInputIdForPortId(idx));
    }

    SmallVector<mlir::Type> getPortTypes() {
      return (*this).getHWModuleType().getPortTypes();
    }

    SmallVector<mlir::Type> getInputTypes() {
      return (*this).getHWModuleType().getInputTypes();
    }

    SmallVector<mlir::Type> getOutputTypes() {
      return (*this).getHWModuleType().getOutputTypes();
    }

    /// Return the set of names on input and inout ports
    SmallVector<Attribute> getInputNames() {
      return (*this).getHWModuleType().getInputNames();
    }

    /// Return the set of names on output ports
    SmallVector<Attribute> getOutputNames() {
      return (*this).getHWModuleType().getOutputNames();
    }

    void setInputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForInputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    void setOutputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForOutputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    // Get the name for the specified input or inout port
    StringRef getPortName(size_t idx) {
      return (*this).getHWModuleType().getPortName(idx);
    }

    // Get the name for the specified input or inout port
    StringRef getInputName(size_t idx) {
      return (*this).getHWModuleType().getInputName(idx);
    }

    // Get the name for the specified output port
    StringRef getOutputName(size_t idx) {
      return (*this).getHWModuleType().getOutputName(idx);
    }

    StringAttr getInputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getInputNameAttr(idx);
    }

    StringAttr getOutputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getOutputNameAttr(idx);
    }

    Attribute getPortAttrs(size_t idx) {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return nullptr;
      return attrs[idx];
    }

    SmallVector<Attribute> getAllInputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumInputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForInputId(x)];
      return retval;
    }

    SmallVector<Attribute> getAllOutputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumOutputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForOutputId(x)];
      return retval;
    }

    void setAllInputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForInputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    void setAllOutputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForOutputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    Attribute getInputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForInputId(idx)];
    }

    Attribute getOutputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForOutputId(idx)];
    }

    void setPortAttrs(size_t idx, DictionaryAttr attr) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      attrs[idx] = attr;
      (*this).setAllPortAttrs(attrs);
    }

    void setPortAttr(size_t idx, StringAttr name, Attribute value) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      NamedAttrList pattr(cast<DictionaryAttr>(attrs[idx]));
      Attribute oldValue;
      if (!value)
        oldValue = pattr.erase(name);
      else
        oldValue = pattr.set(name, value);
      if (oldValue != value) {
        attrs[idx] = pattr.getDictionary((*this).getContext());
        (*this).setAllPortAttrs(attrs);
      }
    }

    void setPortAttrs(StringAttr attrName, ArrayRef<Attribute> newAttrs) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      auto ctxt = (*this).getContext();
      assert(newAttrs.size() == attrs.size());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx) {
        NamedAttrList pattr(cast_or_null<mlir::DictionaryAttr>(attrs[idx]));
        auto newAttr = newAttrs[idx];
        if (newAttr)
          pattr.set(attrName, newAttr);
        else
          pattr.erase(attrName);
        attrs[idx] = pattr.getDictionary(ctxt);
      }
      (*this).setAllPortAttrs(attrs);
    }

    void setAllPortLocs(ArrayRef<Location> locs) {
      std::vector<Attribute> nLocs(locs.begin(), locs.end());
      (*this).setAllPortLocsAttrs(nLocs);
    }

    Location getPortLoc(size_t idx) {
      return (*this).getAllPortLocs()[idx];
    }

    void setPortLoc(size_t idx, Location loc) {
      auto locs = (*this).getAllPortLocs();
      locs[idx] = loc;
      return (*this).setAllPortLocs(locs);
    }

    Location getInputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForInputId(idx)];
    }

    Location getOutputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForOutputId(idx)];
    }

    SmallVector<Location> getInputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return retval;
    }

    ArrayAttr getInputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setInputLocs(ArrayRef<Location> inLocs) {
      assert(inLocs.size() == (*this).getNumInputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = inLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForInputId(idx)] = inLocs[idx];
      (*this).setAllPortLocs(newLocs);

    }

    SmallVector<Location> getOutputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return retval;
    }

    ArrayAttr getOutputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setOutputLocs(ArrayRef<Location> outLocs) {
      assert(outLocs.size() == (*this).getNumOutputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = outLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForOutputId(idx)] = outLocs[idx];
      (*this).setAllPortLocs(newLocs);
    }
};

} // namespace circt::hw
namespace circt::hw {

/// This interface indicates that the module like op is emittable in SV and
/// requires SV legalization on its body.
namespace detail {
struct HWEmittableModuleLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    /// The base classes of this interface.
    const ::mlir::SymbolOpInterface::Concept *implSymbolOpInterface = nullptr;
    const circt::hw::PortList::Concept *implPortList = nullptr;
    const ::circt::igraph::ModuleOpInterface::Concept *implModuleOpInterface = nullptr;
    const circt::hw::HWModuleLike::Concept *implHWModuleLike = nullptr;
    const ::circt::emit::Emittable::Concept *implEmittable = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implSymbolOpInterface = interfaceMap.lookup<::mlir::SymbolOpInterface>();
      assert(implSymbolOpInterface && "`::circt::hw::HWEmittableModuleLike` expected its base interface `::mlir::SymbolOpInterface` to be registered");
      implPortList = interfaceMap.lookup<circt::hw::PortList>();
      assert(implPortList && "`::circt::hw::HWEmittableModuleLike` expected its base interface `circt::hw::PortList` to be registered");
      implModuleOpInterface = interfaceMap.lookup<::circt::igraph::ModuleOpInterface>();
      assert(implModuleOpInterface && "`::circt::hw::HWEmittableModuleLike` expected its base interface `::circt::igraph::ModuleOpInterface` to be registered");
      implHWModuleLike = interfaceMap.lookup<circt::hw::HWModuleLike>();
      assert(implHWModuleLike && "`::circt::hw::HWEmittableModuleLike` expected its base interface `circt::hw::HWModuleLike` to be registered");
      implEmittable = interfaceMap.lookup<::circt::emit::Emittable>();
      assert(implEmittable && "`::circt::hw::HWEmittableModuleLike` expected its base interface `::circt::emit::Emittable` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::hw::HWEmittableModuleLike;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::hw::HWEmittableModuleLike;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct HWEmittableModuleLikeTrait;

} // namespace detail
class HWEmittableModuleLike : public ::mlir::OpInterface<HWEmittableModuleLike, detail::HWEmittableModuleLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<HWEmittableModuleLike, detail::HWEmittableModuleLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::HWEmittableModuleLikeTrait<ConcreteOp> {};
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
  // Inherited from circt::hw::HWModuleLike
  //===----------------------------------------------------------------===//

  operator circt::hw::HWModuleLike () const {
    if (!*this) return nullptr;
    return circt::hw::HWModuleLike(*this, getImpl()->implHWModuleLike);
  }


  /// Get the module type
  ::circt::hw::ModuleType getHWModuleType();

  /// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
  ArrayRef<Attribute> getAllPortAttrs();

  /// Set the port Attributes
  void setAllPortAttrs(ArrayRef<Attribute> attrs);

  /// Remove the port Attributes
  void removeAllPortAttrs();

  /// Get the port Locations
  SmallVector<Location> getAllPortLocs();

  /// Set the port Locations
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);

  /// Set the module type (and port names)
  void setHWModuleType(::circt::hw::ModuleType type);

  /// Set the port names
  void setAllPortNames(ArrayRef<Attribute> names);

    /// Attribute name for port symbols.
    static StringRef getPortSymbolAttrName() {
      return "hw.exportPort";
    }

    /// Return the region containing the body of this function.
    Region &getModuleBody() { return (*this)->getRegion(0); }
    Block *getBodyBlock() {
      Region &body = getModuleBody();
      if (body.empty())
        return nullptr;
      return &body.front();
    }

    /// Returns the entry block argument at the given index.
    BlockArgument getArgumentForInput(unsigned idx) {
      return (*this).getModuleBody().getArgument(idx);
    }

    /// Returns the entry block argument for the given port.  May be null.
    BlockArgument getArgumentForPort(unsigned idx) {
      return (*this).getModuleBody().getArgument((*this).getHWModuleType().getInputIdForPortId(idx));
    }

    SmallVector<mlir::Type> getPortTypes() {
      return (*this).getHWModuleType().getPortTypes();
    }

    SmallVector<mlir::Type> getInputTypes() {
      return (*this).getHWModuleType().getInputTypes();
    }

    SmallVector<mlir::Type> getOutputTypes() {
      return (*this).getHWModuleType().getOutputTypes();
    }

    /// Return the set of names on input and inout ports
    SmallVector<Attribute> getInputNames() {
      return (*this).getHWModuleType().getInputNames();
    }

    /// Return the set of names on output ports
    SmallVector<Attribute> getOutputNames() {
      return (*this).getHWModuleType().getOutputNames();
    }

    void setInputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForInputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    void setOutputNames(ArrayRef<Attribute> names) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForOutputId(idx)] = names[idx];
      (*this).setAllPortNames(newNames);
    }

    // Get the name for the specified input or inout port
    StringRef getPortName(size_t idx) {
      return (*this).getHWModuleType().getPortName(idx);
    }

    // Get the name for the specified input or inout port
    StringRef getInputName(size_t idx) {
      return (*this).getHWModuleType().getInputName(idx);
    }

    // Get the name for the specified output port
    StringRef getOutputName(size_t idx) {
      return (*this).getHWModuleType().getOutputName(idx);
    }

    StringAttr getInputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getInputNameAttr(idx);
    }

    StringAttr getOutputNameAttr(size_t idx) {
      return (*this).getHWModuleType().getOutputNameAttr(idx);
    }

    Attribute getPortAttrs(size_t idx) {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return nullptr;
      return attrs[idx];
    }

    SmallVector<Attribute> getAllInputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumInputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForInputId(x)];
      return retval;
    }

    SmallVector<Attribute> getAllOutputAttrs() {
      auto attrs = (*this).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*this).getNumOutputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*this).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForOutputId(x)];
      return retval;
    }

    void setAllInputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForInputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    void setAllOutputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*this).getHWModuleType();
      SmallVector<Attribute> newAttrs((*this).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*this).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForOutputId(idx)] = attrs[idx];
      (*this).setAllPortAttrs(newAttrs);
    }

    Attribute getInputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForInputId(idx)];
    }

    Attribute getOutputAttrs(size_t idx) {
      return (*this).getAllPortAttrs()[(*this).getPortIdForOutputId(idx)];
    }

    void setPortAttrs(size_t idx, DictionaryAttr attr) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      attrs[idx] = attr;
      (*this).setAllPortAttrs(attrs);
    }

    void setPortAttr(size_t idx, StringAttr name, Attribute value) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      NamedAttrList pattr(cast<DictionaryAttr>(attrs[idx]));
      Attribute oldValue;
      if (!value)
        oldValue = pattr.erase(name);
      else
        oldValue = pattr.set(name, value);
      if (oldValue != value) {
        attrs[idx] = pattr.getDictionary((*this).getContext());
        (*this).setAllPortAttrs(attrs);
      }
    }

    void setPortAttrs(StringAttr attrName, ArrayRef<Attribute> newAttrs) {
      SmallVector<Attribute> attrs((*this).getAllPortAttrs());
      attrs.resize((*this).getNumPorts());
      auto ctxt = (*this).getContext();
      assert(newAttrs.size() == attrs.size());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx) {
        NamedAttrList pattr(cast_or_null<mlir::DictionaryAttr>(attrs[idx]));
        auto newAttr = newAttrs[idx];
        if (newAttr)
          pattr.set(attrName, newAttr);
        else
          pattr.erase(attrName);
        attrs[idx] = pattr.getDictionary(ctxt);
      }
      (*this).setAllPortAttrs(attrs);
    }

    void setAllPortLocs(ArrayRef<Location> locs) {
      std::vector<Attribute> nLocs(locs.begin(), locs.end());
      (*this).setAllPortLocsAttrs(nLocs);
    }

    Location getPortLoc(size_t idx) {
      return (*this).getAllPortLocs()[idx];
    }

    void setPortLoc(size_t idx, Location loc) {
      auto locs = (*this).getAllPortLocs();
      locs[idx] = loc;
      return (*this).setAllPortLocs(locs);
    }

    Location getInputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForInputId(idx)];
    }

    Location getOutputLoc(size_t idx) {
      return (*this).getAllPortLocs()[(*this).getPortIdForOutputId(idx)];
    }

    SmallVector<Location> getInputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return retval;
    }

    ArrayAttr getInputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForInputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setInputLocs(ArrayRef<Location> inLocs) {
      assert(inLocs.size() == (*this).getNumInputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = inLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForInputId(idx)] = inLocs[idx];
      (*this).setAllPortLocs(newLocs);

    }

    SmallVector<Location> getOutputLocs() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return retval;
    }

    ArrayAttr getOutputLocsAttr() {
      auto locs = (*this).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*this).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*this).getPortIdForOutputId(x)]);
      return ArrayAttr::get((*this)->getContext(), retval);
    }

    void setOutputLocs(ArrayRef<Location> outLocs) {
      assert(outLocs.size() == (*this).getNumOutputPorts());
      auto type = (*this).getHWModuleType();
      SmallVector<Location> newLocs((*this).getAllPortLocs());
      for (size_t idx = 0, e = outLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForOutputId(idx)] = outLocs[idx];
      (*this).setAllPortLocs(newLocs);
    }
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::emit::Emittable
  //===----------------------------------------------------------------===//

  operator ::circt::emit::Emittable () const {
    if (!*this) return nullptr;
    return ::circt::emit::Emittable(*this, getImpl()->implEmittable);
  }

};

} // namespace circt::hw
namespace circt::hw {

/// Provide common instance information.
namespace detail {
struct HWInstanceLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::StringAttr (*getInputName)(const Concept *impl, ::mlir::Operation *, size_t);
    ::mlir::StringAttr (*getOutputName)(const Concept *impl, ::mlir::Operation *, size_t);
    void (*setInputName)(const Concept *impl, ::mlir::Operation *, size_t, ::mlir::StringAttr);
    void (*setOutputName)(const Concept *impl, ::mlir::Operation *, size_t, ::mlir::StringAttr);
    ::mlir::ArrayAttr (*getInputNames)(const Concept *impl, ::mlir::Operation *);
    ::mlir::ArrayAttr (*getOutputNames)(const Concept *impl, ::mlir::Operation *);
    void (*setInputNames)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    void (*setOutputNames)(const Concept *impl, ::mlir::Operation *, ::mlir::ArrayAttr);
    bool (*getDoNotPrint)(const Concept *impl, ::mlir::Operation *);
    /// The base classes of this interface.
    const ::circt::igraph::InstanceOpInterface::Concept *implInstanceOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implInstanceOpInterface = interfaceMap.lookup<::circt::igraph::InstanceOpInterface>();
      assert(implInstanceOpInterface && "`circt::hw::HWInstanceLike` expected its base interface `::circt::igraph::InstanceOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hw::HWInstanceLike;
    Model() : Concept{getInputName, getOutputName, setInputName, setOutputName, getInputNames, getOutputNames, setInputNames, setOutputNames, getDoNotPrint} {}

    static inline ::mlir::StringAttr getInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline ::mlir::StringAttr getOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline void setInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name);
    static inline void setOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name);
    static inline ::mlir::ArrayAttr getInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::ArrayAttr getOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names);
    static inline void setOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names);
    static inline bool getDoNotPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::HWInstanceLike;
    FallbackModel() : Concept{getInputName, getOutputName, setInputName, setOutputName, getInputNames, getOutputNames, setInputNames, setOutputNames, getDoNotPrint} {}

    static inline ::mlir::StringAttr getInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline ::mlir::StringAttr getOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx);
    static inline void setInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name);
    static inline void setOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name);
    static inline ::mlir::ArrayAttr getInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::ArrayAttr getOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names);
    static inline void setOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names);
    static inline bool getDoNotPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::StringAttr getInputName(::mlir::Operation *tablegen_opaque_val, size_t idx) const;
    ::mlir::StringAttr getOutputName(::mlir::Operation *tablegen_opaque_val, size_t idx) const;
    void setInputName(::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) const;
    void setOutputName(::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) const;
    ::mlir::ArrayAttr getInputNames(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::ArrayAttr getOutputNames(::mlir::Operation *tablegen_opaque_val) const;
    void setInputNames(::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) const;
    void setOutputNames(::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) const;
  };
};
template <typename ConcreteOp>
struct HWInstanceLikeTrait;

} // namespace detail
class HWInstanceLike : public ::mlir::OpInterface<HWInstanceLike, detail::HWInstanceLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<HWInstanceLike, detail::HWInstanceLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::HWInstanceLikeTrait<ConcreteOp> {};

  /// Return the name of the specified input port or null if it cannot be
  /// determined.
  ::mlir::StringAttr getInputName(size_t idx);

  /// Return the name of the specified result or null if it cannot be
  /// determined.
  ::mlir::StringAttr getOutputName(size_t idx);

  /// Change the name of the specified input port.
  void setInputName(size_t idx, ::mlir::StringAttr name);

  /// Change the name of the specified output port.
  void setOutputName(size_t idx, ::mlir::StringAttr name);

  /// Return the names of all input ports. If the instance operation stores the
  /// names in an ArrayAttr this can avoid attribute constructions.
  ::mlir::ArrayAttr getInputNames();

  /// Return the name of all ouput ports. If the instance operation stores the
  /// names in an ArrayAttr this can avoid attribute constructions.
  ::mlir::ArrayAttr getOutputNames();

  /// Change the names of all input ports. If all names have to be changed, this
  /// can avoid repeated intermediate attribute constructions.
  void setInputNames(::mlir::ArrayAttr names);

  /// Change the names of all output ports. If all names have to be changed, this
  /// can avoid repeated intermediate attribute constructions.
  void setOutputNames(::mlir::ArrayAttr names);

  /// True if this instance is a phony placeholder
  bool getDoNotPrint();
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

} // namespace circt::hw
namespace circt::hw {

/// This interface describes an operation that may define an
/// `inner_sym`.  An `inner_sym` operation resides
/// in arbitrarily-nested regions of a region that defines a
/// `InnerSymbolTable`.
/// Inner Symbols are different from normal symbols due to
/// MLIR symbol table resolution rules.  Specifically normal
/// symbols are resolved by first going up to the closest
/// parent symbol table and resolving from there (recursing
/// down for complex symbol paths).  In HW and SV, modules
/// define a symbol in a circuit or std.module symbol table.
/// For instances to be able to resolve the modules they
/// instantiate, the symbol use in an instance must resolve
/// in the top-level symbol table.  If a module were a
/// symbol table, instances resolving a symbol would start from
/// their own module, never seeing other modules (since
/// resolution would start in the parent module of the
/// instance and be unable to go to the global scope).
/// The second problem arises from nesting.  Symbols defining
/// ops must be immediate children of a symbol table.  HW
/// and SV operations which define a inner_sym are grandchildren,
/// at least, of a symbol table and may be much further nested.
/// Lastly, ports need to define inner_sym, something not allowed
/// by normal symbols.
/// 
/// Any operation implementing an InnerSymbol may have the inner symbol be
/// optional and all methods should be robuse to the attribute not being
/// defined.
namespace detail {
struct InnerSymbolOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::StringAttr (*getInnerNameAttr)(const Concept *impl, ::mlir::Operation *);
    ::std::optional<::mlir::StringRef> (*getInnerName)(const Concept *impl, ::mlir::Operation *);
    void (*setInnerSymbol)(const Concept *impl, ::mlir::Operation *, ::mlir::StringAttr);
    void (*setInnerSymbolAttr)(const Concept *impl, ::mlir::Operation *, ::circt::hw::InnerSymAttr);
    ::circt::hw::InnerRefAttr (*getInnerRef)(const Concept *impl, ::mlir::Operation *);
    ::circt::hw::InnerSymAttr (*getInnerSymAttr)(const Concept *impl, ::mlir::Operation *);
    bool (*supportsPerFieldSymbols)();
    std::optional<size_t> (*getTargetResultIndex)();
    OpResult (*getTargetResult)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::hw::InnerSymbolOpInterface;
    Model() : Concept{getInnerNameAttr, getInnerName, setInnerSymbol, setInnerSymbolAttr, getInnerRef, getInnerSymAttr, supportsPerFieldSymbols, getTargetResultIndex, getTargetResult} {}

    static inline ::mlir::StringAttr getInnerNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::mlir::StringRef> getInnerName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInnerSymbol(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name);
    static inline void setInnerSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym);
    static inline ::circt::hw::InnerRefAttr getInnerRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::InnerSymAttr getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool supportsPerFieldSymbols();
    static inline std::optional<size_t> getTargetResultIndex();
    static inline OpResult getTargetResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::hw::InnerSymbolOpInterface;
    FallbackModel() : Concept{getInnerNameAttr, getInnerName, setInnerSymbol, setInnerSymbolAttr, getInnerRef, getInnerSymAttr, supportsPerFieldSymbols, getTargetResultIndex, getTargetResult} {}

    static inline ::mlir::StringAttr getInnerNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::mlir::StringRef> getInnerName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInnerSymbol(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name);
    static inline void setInnerSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym);
    static inline ::circt::hw::InnerRefAttr getInnerRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::circt::hw::InnerSymAttr getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool supportsPerFieldSymbols();
    static inline std::optional<size_t> getTargetResultIndex();
    static inline OpResult getTargetResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::StringAttr getInnerNameAttr(::mlir::Operation *tablegen_opaque_val) const;
    ::std::optional<::mlir::StringRef> getInnerName(::mlir::Operation *tablegen_opaque_val) const;
    void setInnerSymbol(::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) const;
    void setInnerSymbolAttr(::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym) const;
    ::circt::hw::InnerRefAttr getInnerRef(::mlir::Operation *tablegen_opaque_val) const;
    ::circt::hw::InnerSymAttr getInnerSymAttr(::mlir::Operation *tablegen_opaque_val) const;
    static bool supportsPerFieldSymbols();
    OpResult getTargetResult(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct InnerSymbolOpInterfaceTrait;

} // namespace detail
class InnerSymbolOpInterface : public ::mlir::OpInterface<InnerSymbolOpInterface, detail::InnerSymbolOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<InnerSymbolOpInterface, detail::InnerSymbolOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::InnerSymbolOpInterfaceTrait<ConcreteOp> {};

  /// Returns the name of the top-level inner symbol defined by this operation, if present.
  ::mlir::StringAttr getInnerNameAttr();

  /// Returns the name of the top-level inner symbol defined by this operation, if present.
  ::std::optional<::mlir::StringRef> getInnerName();

  /// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
  void setInnerSymbol(::mlir::StringAttr name);

  /// Sets the inner symbols defined by this operation.
  void setInnerSymbolAttr(::circt::hw::InnerSymAttr sym);

  /// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
  ::circt::hw::InnerRefAttr getInnerRef();

  /// Returns the InnerSymAttr representing all inner symbols defined by this operation.
  ::circt::hw::InnerSymAttr getInnerSymAttr();

  /// Returns whether per-field symbols are supported for this operation type.
  bool supportsPerFieldSymbols();

  /// Returns the index of the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
  std::optional<size_t> getTargetResultIndex();

  /// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
  OpResult getTargetResult();
};

} // namespace circt::hw
namespace circt::hw {

/// This interface describes an operation that may use a `InnerRef`. This
/// interface allows for users of inner symbols to hook into verification and
/// other inner symbol related utilities that are either costly or otherwise
/// disallowed within a traditional operation.
namespace detail {
struct InnerRefUserOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::LogicalResult (*verifyInnerRefs)(const Concept *impl, ::mlir::Operation *, ::circt::hw::InnerRefNamespace&);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::hw::InnerRefUserOpInterface;
    Model() : Concept{verifyInnerRefs} {}

    static inline ::mlir::LogicalResult verifyInnerRefs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerRefNamespace& ns);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::hw::InnerRefUserOpInterface;
    FallbackModel() : Concept{verifyInnerRefs} {}

    static inline ::mlir::LogicalResult verifyInnerRefs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerRefNamespace& ns);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct InnerRefUserOpInterfaceTrait;

} // namespace detail
class InnerRefUserOpInterface : public ::mlir::OpInterface<InnerRefUserOpInterface, detail::InnerRefUserOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<InnerRefUserOpInterface, detail::InnerRefUserOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::InnerRefUserOpInterfaceTrait<ConcreteOp> {};

  /// Verify the inner ref uses held by this operation.
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace& ns);
};

} // namespace circt::hw
namespace circt::hw {

/// This interface is used for specifying the combinational dataflow that exists
/// in the results and operands of an operation.
/// Any operation that doesn't implement this interface is assumed to have a
/// combinational dependence from each operand to each result.
namespace detail {
struct CombDataFlowInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> (*computeDataFlow)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hw::CombDataFlow;
    Model() : Concept{computeDataFlow} {}

    static inline llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> computeDataFlow(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::CombDataFlow;
    FallbackModel() : Concept{computeDataFlow} {}

    static inline llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> computeDataFlow(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct CombDataFlowTrait;

} // namespace detail
class CombDataFlow : public ::mlir::OpInterface<CombDataFlow, detail::CombDataFlowInterfaceTraits> {
public:
  using ::mlir::OpInterface<CombDataFlow, detail::CombDataFlowInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::CombDataFlowTrait<ConcreteOp> {};

  /// Get the combinational dataflow relations between the operands and the results.
  /// This returns a pair of ground type fieldrefs. The first element is the destination
  /// and the second is the source of the dependence. The default implementation returns
  /// an empty list, which implies that the operation is not combinational.
  llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> computeDataFlow();
};

} // namespace circt::hw
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct PortListTrait : public ::mlir::OpInterface<PortList, detail::PortListInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct HWModuleLikeTrait : public ::mlir::OpInterface<HWModuleLike, detail::HWModuleLikeInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      static_assert(
        ConcreteOp::template hasTrait<::mlir::SymbolOpInterface::Trait>(),
        "expected operation to be a symbol");
    return success();
    }

    /// Attribute name for port symbols.
    static StringRef getPortSymbolAttrName() {
      return "hw.exportPort";
    }

    /// Return the region containing the body of this function.
    Region &getModuleBody() { return (*static_cast<ConcreteOp *>(this))->getRegion(0); }
    Block *getBodyBlock() {
      Region &body = getModuleBody();
      if (body.empty())
        return nullptr;
      return &body.front();
    }

    /// Returns the entry block argument at the given index.
    BlockArgument getArgumentForInput(unsigned idx) {
      return (*static_cast<ConcreteOp *>(this)).getModuleBody().getArgument(idx);
    }

    /// Returns the entry block argument for the given port.  May be null.
    BlockArgument getArgumentForPort(unsigned idx) {
      return (*static_cast<ConcreteOp *>(this)).getModuleBody().getArgument((*static_cast<ConcreteOp *>(this)).getHWModuleType().getInputIdForPortId(idx));
    }

    SmallVector<mlir::Type> getPortTypes() {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getPortTypes();
    }

    SmallVector<mlir::Type> getInputTypes() {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getInputTypes();
    }

    SmallVector<mlir::Type> getOutputTypes() {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getOutputTypes();
    }

    /// Return the set of names on input and inout ports
    SmallVector<Attribute> getInputNames() {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getInputNames();
    }

    /// Return the set of names on output ports
    SmallVector<Attribute> getOutputNames() {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getOutputNames();
    }

    void setInputNames(ArrayRef<Attribute> names) {
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForInputId(idx)] = names[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortNames(newNames);
    }

    void setOutputNames(ArrayRef<Attribute> names) {
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Attribute> newNames(type.getPortNames());
      for (size_t idx = 0, e = names.size(); idx != e; ++idx)
        newNames[type.getPortIdForOutputId(idx)] = names[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortNames(newNames);
    }

    // Get the name for the specified input or inout port
    StringRef getPortName(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getPortName(idx);
    }

    // Get the name for the specified input or inout port
    StringRef getInputName(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getInputName(idx);
    }

    // Get the name for the specified output port
    StringRef getOutputName(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getOutputName(idx);
    }

    StringAttr getInputNameAttr(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getInputNameAttr(idx);
    }

    StringAttr getOutputNameAttr(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getHWModuleType().getOutputNameAttr(idx);
    }

    Attribute getPortAttrs(size_t idx) {
      auto attrs = (*static_cast<ConcreteOp *>(this)).getAllPortAttrs();
      if (attrs.empty())
        return nullptr;
      return attrs[idx];
    }

    SmallVector<Attribute> getAllInputAttrs() {
      auto attrs = (*static_cast<ConcreteOp *>(this)).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*static_cast<ConcreteOp *>(this)).getNumInputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForInputId(x)];
      return retval;
    }

    SmallVector<Attribute> getAllOutputAttrs() {
      auto attrs = (*static_cast<ConcreteOp *>(this)).getAllPortAttrs();
      if (attrs.empty())
        return {};
      auto num = (*static_cast<ConcreteOp *>(this)).getNumOutputPorts();
      SmallVector<Attribute> retval(num);
      auto modType = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      for (unsigned x = 0; x < num; ++x)
        retval[x] = attrs[modType.getPortIdForOutputId(x)];
      return retval;
    }

    void setAllInputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Attribute> newAttrs((*static_cast<ConcreteOp *>(this)).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*static_cast<ConcreteOp *>(this)).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForInputId(idx)] = attrs[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortAttrs(newAttrs);
    }

    void setAllOutputAttrs(ArrayRef<Attribute> attrs) {
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Attribute> newAttrs((*static_cast<ConcreteOp *>(this)).getAllPortAttrs());
      if (newAttrs.empty())
        newAttrs.resize((*static_cast<ConcreteOp *>(this)).getNumPorts());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx)
        newAttrs[type.getPortIdForOutputId(idx)] = attrs[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortAttrs(newAttrs);
    }

    Attribute getInputAttrs(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getAllPortAttrs()[(*static_cast<ConcreteOp *>(this)).getPortIdForInputId(idx)];
    }

    Attribute getOutputAttrs(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getAllPortAttrs()[(*static_cast<ConcreteOp *>(this)).getPortIdForOutputId(idx)];
    }

    void setPortAttrs(size_t idx, DictionaryAttr attr) {
      SmallVector<Attribute> attrs((*static_cast<ConcreteOp *>(this)).getAllPortAttrs());
      attrs.resize((*static_cast<ConcreteOp *>(this)).getNumPorts());
      attrs[idx] = attr;
      (*static_cast<ConcreteOp *>(this)).setAllPortAttrs(attrs);
    }

    void setPortAttr(size_t idx, StringAttr name, Attribute value) {
      SmallVector<Attribute> attrs((*static_cast<ConcreteOp *>(this)).getAllPortAttrs());
      attrs.resize((*static_cast<ConcreteOp *>(this)).getNumPorts());
      NamedAttrList pattr(cast<DictionaryAttr>(attrs[idx]));
      Attribute oldValue;
      if (!value)
        oldValue = pattr.erase(name);
      else
        oldValue = pattr.set(name, value);
      if (oldValue != value) {
        attrs[idx] = pattr.getDictionary((*static_cast<ConcreteOp *>(this)).getContext());
        (*static_cast<ConcreteOp *>(this)).setAllPortAttrs(attrs);
      }
    }

    void setPortAttrs(StringAttr attrName, ArrayRef<Attribute> newAttrs) {
      SmallVector<Attribute> attrs((*static_cast<ConcreteOp *>(this)).getAllPortAttrs());
      attrs.resize((*static_cast<ConcreteOp *>(this)).getNumPorts());
      auto ctxt = (*static_cast<ConcreteOp *>(this)).getContext();
      assert(newAttrs.size() == attrs.size());
      for (size_t idx = 0, e = attrs.size(); idx != e; ++idx) {
        NamedAttrList pattr(cast_or_null<mlir::DictionaryAttr>(attrs[idx]));
        auto newAttr = newAttrs[idx];
        if (newAttr)
          pattr.set(attrName, newAttr);
        else
          pattr.erase(attrName);
        attrs[idx] = pattr.getDictionary(ctxt);
      }
      (*static_cast<ConcreteOp *>(this)).setAllPortAttrs(attrs);
    }

    void setAllPortLocs(ArrayRef<Location> locs) {
      std::vector<Attribute> nLocs(locs.begin(), locs.end());
      (*static_cast<ConcreteOp *>(this)).setAllPortLocsAttrs(nLocs);
    }

    Location getPortLoc(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getAllPortLocs()[idx];
    }

    void setPortLoc(size_t idx, Location loc) {
      auto locs = (*static_cast<ConcreteOp *>(this)).getAllPortLocs();
      locs[idx] = loc;
      return (*static_cast<ConcreteOp *>(this)).setAllPortLocs(locs);
    }

    Location getInputLoc(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getAllPortLocs()[(*static_cast<ConcreteOp *>(this)).getPortIdForInputId(idx)];
    }

    Location getOutputLoc(size_t idx) {
      return (*static_cast<ConcreteOp *>(this)).getAllPortLocs()[(*static_cast<ConcreteOp *>(this)).getPortIdForOutputId(idx)];
    }

    SmallVector<Location> getInputLocs() {
      auto locs = (*static_cast<ConcreteOp *>(this)).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*static_cast<ConcreteOp *>(this)).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*static_cast<ConcreteOp *>(this)).getPortIdForInputId(x)]);
      return retval;
    }

    ArrayAttr getInputLocsAttr() {
      auto locs = (*static_cast<ConcreteOp *>(this)).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*static_cast<ConcreteOp *>(this)).getNumInputPorts(); x < e; ++x)
        retval.push_back(locs[(*static_cast<ConcreteOp *>(this)).getPortIdForInputId(x)]);
      return ArrayAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), retval);
    }

    void setInputLocs(ArrayRef<Location> inLocs) {
      assert(inLocs.size() == (*static_cast<ConcreteOp *>(this)).getNumInputPorts());
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Location> newLocs((*static_cast<ConcreteOp *>(this)).getAllPortLocs());
      for (size_t idx = 0, e = inLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForInputId(idx)] = inLocs[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortLocs(newLocs);

    }

    SmallVector<Location> getOutputLocs() {
      auto locs = (*static_cast<ConcreteOp *>(this)).getAllPortLocs();
      SmallVector<Location> retval;
      for (unsigned x = 0, e = (*static_cast<ConcreteOp *>(this)).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*static_cast<ConcreteOp *>(this)).getPortIdForOutputId(x)]);
      return retval;
    }

    ArrayAttr getOutputLocsAttr() {
      auto locs = (*static_cast<ConcreteOp *>(this)).getAllPortLocs();
      SmallVector<Attribute> retval;
      for (unsigned x = 0, e = (*static_cast<ConcreteOp *>(this)).getNumOutputPorts(); x < e; ++x)
        retval.push_back(locs[(*static_cast<ConcreteOp *>(this)).getPortIdForOutputId(x)]);
      return ArrayAttr::get((*static_cast<ConcreteOp *>(this))->getContext(), retval);
    }

    void setOutputLocs(ArrayRef<Location> outLocs) {
      assert(outLocs.size() == (*static_cast<ConcreteOp *>(this)).getNumOutputPorts());
      auto type = (*static_cast<ConcreteOp *>(this)).getHWModuleType();
      SmallVector<Location> newLocs((*static_cast<ConcreteOp *>(this)).getAllPortLocs());
      for (size_t idx = 0, e = outLocs.size(); idx != e; ++idx)
        newLocs[type.getPortIdForOutputId(idx)] = outLocs[idx];
      (*static_cast<ConcreteOp *>(this)).setAllPortLocs(newLocs);
    }
  
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct HWMutableModuleLikeTrait : public ::mlir::OpInterface<HWMutableModuleLike, detail::HWMutableModuleLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Get a handle to a utility class which provides by-name lookup of port indices. The returned object does _not_ update if the module is mutated.
    ::circt::hw::ModulePortLookupInfo getPortLookupInfo() {
      return hw::ModulePortLookupInfo(
        (*static_cast<ConcreteOp *>(this))->getContext(),
        (*static_cast<ConcreteOp *>(this)).getPortList());
    }

    /// Insert ports into this module
    void insertPorts(ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) {
      (*static_cast<ConcreteOp *>(this)).modifyPorts(insertInputs, insertOutputs, {}, {});
    }

    /// Erase ports from this module
    void erasePorts(ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
      (*static_cast<ConcreteOp *>(this)).modifyPorts({}, {}, eraseInputs, eraseOutputs);
    }
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct HWEmittableModuleLikeTrait : public ::mlir::OpInterface<HWEmittableModuleLike, detail::HWEmittableModuleLikeInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct HWInstanceLikeTrait : public ::mlir::OpInterface<HWInstanceLike, detail::HWInstanceLikeInterfaceTraits>::Trait<ConcreteOp> {

    /// Return the name of the specified input port or null if it cannot be
    /// determined.
    ::mlir::StringAttr getInputName(size_t idx) {
      return ::circt::hw::instance_like_impl::getName(
        (*static_cast<ConcreteOp *>(this)).getArgNames(), idx);
    }

    /// Return the name of the specified result or null if it cannot be
    /// determined.
    ::mlir::StringAttr getOutputName(size_t idx) {
      return ::circt::hw::instance_like_impl::getName(
        (*static_cast<ConcreteOp *>(this)).getResultNames(), idx);
    }

    /// Change the name of the specified input port.
    void setInputName(size_t idx, ::mlir::StringAttr name) {
      (*static_cast<ConcreteOp *>(this)).setArgNamesAttr(::circt::hw::instance_like_impl::updateName(
        (*static_cast<ConcreteOp *>(this)).getArgNames(), idx, name));
    }

    /// Change the name of the specified output port.
    void setOutputName(size_t idx, ::mlir::StringAttr name) {
      (*static_cast<ConcreteOp *>(this)).setResultNamesAttr(::circt::hw::instance_like_impl::updateName(
        (*static_cast<ConcreteOp *>(this)).getResultNames(), idx, name));
    }

    /// Return the names of all input ports. If the instance operation stores the
    /// names in an ArrayAttr this can avoid attribute constructions.
    ::mlir::ArrayAttr getInputNames() {
      return (*static_cast<ConcreteOp *>(this)).getArgNamesAttr();
    }

    /// Return the name of all ouput ports. If the instance operation stores the
    /// names in an ArrayAttr this can avoid attribute constructions.
    ::mlir::ArrayAttr getOutputNames() {
      return (*static_cast<ConcreteOp *>(this)).getResultNamesAttr();
    }

    /// Change the names of all input ports. If all names have to be changed, this
    /// can avoid repeated intermediate attribute constructions.
    void setInputNames(::mlir::ArrayAttr names) {
      (*static_cast<ConcreteOp *>(this)).setArgNamesAttr(names);
    }

    /// Change the names of all output ports. If all names have to be changed, this
    /// can avoid repeated intermediate attribute constructions.
    void setOutputNames(::mlir::ArrayAttr names) {
      (*static_cast<ConcreteOp *>(this)).setResultNamesAttr(names);
    }
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct InnerSymbolOpInterfaceTrait : public ::mlir::OpInterface<InnerSymbolOpInterface, detail::InnerSymbolOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the name of the top-level inner symbol defined by this operation, if present.
    ::mlir::StringAttr getInnerNameAttr() {
      if (auto attr =
              this->getOperation()->template getAttrOfType<hw::InnerSymAttr>(
              circt::hw::InnerSymbolTable::getInnerSymbolAttrName()))
          return attr.getSymName();
        return {};
    }

    /// Returns the name of the top-level inner symbol defined by this operation, if present.
    ::std::optional<::mlir::StringRef> getInnerName() {
      auto attr = this->getInnerNameAttr();
        return attr ? ::std::optional<StringRef>(attr.getValue()) : ::std::nullopt;
    }

    /// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
    void setInnerSymbol(::mlir::StringAttr name) {
      this->getOperation()->setAttr(
            InnerSymbolTable::getInnerSymbolAttrName(), hw::InnerSymAttr::get(name));
    }

    /// Sets the inner symbols defined by this operation.
    void setInnerSymbolAttr(::circt::hw::InnerSymAttr sym) {
      if (sym && !sym.empty())
          this->getOperation()->setAttr(
              InnerSymbolTable::getInnerSymbolAttrName(), sym);
        else
          this->getOperation()->removeAttr(InnerSymbolTable::getInnerSymbolAttrName());
    }

    /// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
    ::circt::hw::InnerRefAttr getInnerRef() {
      auto *op = this->getOperation();
        return hw::InnerRefAttr::get(
            SymbolTable::getSymbolName(
                op->template getParentWithTrait<OpTrait::InnerSymbolTable>()),
            InnerSymbolTable::getInnerSymbol(op));
    }

    /// Returns the InnerSymAttr representing all inner symbols defined by this operation.
    ::circt::hw::InnerSymAttr getInnerSymAttr() {
      return this->getOperation()->template getAttrOfType<hw::InnerSymAttr>(
              circt::hw::InnerSymbolTable::getInnerSymbolAttrName());
    }

    /// Returns whether per-field symbols are supported for this operation type.
    static bool supportsPerFieldSymbols() {
      return ConcreteOp::getTargetResultIndex().has_value();
    }

    /// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
    OpResult getTargetResult() {
      auto idx = ConcreteOp::getTargetResultIndex();
        if (!idx)
          return {};
        return (*static_cast<ConcreteOp *>(this))->getResult(*idx);
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyInnerSymOp(cast<circt::hw::InnerSymbolOpInterface>(op));
    }
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct InnerRefUserOpInterfaceTrait : public ::mlir::OpInterface<InnerRefUserOpInterface, detail::InnerRefUserOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteOp>
  struct CombDataFlowTrait : public ::mlir::OpInterface<CombDataFlow, detail::CombDataFlowInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::hw::detail
namespace circt::hw {

template<typename ConcreteOp>
SmallVector<::circt::hw::PortInfo> detail::PortListInterfaceTraits::Model<ConcreteOp>::getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortList();
}
template<typename ConcreteOp>
::circt::hw::PortInfo detail::PortListInterfaceTraits::Model<ConcreteOp>::getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPort(idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::Model<ConcreteOp>::getPortIdForInputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortIdForInputId(idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::Model<ConcreteOp>::getPortIdForOutputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortIdForOutputId(idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::Model<ConcreteOp>::getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumPorts();
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::Model<ConcreteOp>::getNumInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumInputPorts();
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::Model<ConcreteOp>::getNumOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNumOutputPorts();
}
template<typename ConcreteOp>
SmallVector<::circt::hw::PortInfo> detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getPortList(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortList(tablegen_opaque_val);
}
template<typename ConcreteOp>
::circt::hw::PortInfo detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getPort(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getPortIdForInputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getPortIdForInputId(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getPortIdForOutputId(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getPortIdForOutputId(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getNumPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getNumInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumInputPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
size_t detail::PortListInterfaceTraits::FallbackModel<ConcreteOp>::getNumOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNumOutputPorts(tablegen_opaque_val);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
::circt::hw::ModuleType detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::getHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getHWModuleType();
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::getAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAllPortAttrs();
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::setAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> attrs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setAllPortAttrs(attrs);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::removeAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).removeAllPortAttrs();
}
template<typename ConcreteOp>
SmallVector<Location> detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::getAllPortLocs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getAllPortLocs();
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::setAllPortLocsAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> locs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setAllPortLocsAttrs(locs);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::setHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::ModuleType type) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setHWModuleType(type);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::Model<ConcreteOp>::setAllPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> names) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setAllPortNames(names);
}
template<typename ConcreteOp>
::circt::hw::ModuleType detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getHWModuleType(tablegen_opaque_val);
}
template<typename ConcreteOp>
ArrayRef<Attribute> detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getAllPortAttrs(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> attrs) {
  return static_cast<const ConcreteOp *>(impl)->setAllPortAttrs(tablegen_opaque_val, attrs);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::removeAllPortAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->removeAllPortAttrs(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<Location> detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getAllPortLocs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getAllPortLocs(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setAllPortLocsAttrs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> locs) {
  return static_cast<const ConcreteOp *>(impl)->setAllPortLocsAttrs(tablegen_opaque_val, locs);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setHWModuleType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::ModuleType type) {
  return static_cast<const ConcreteOp *>(impl)->setHWModuleType(tablegen_opaque_val, type);
}
template<typename ConcreteOp>
void detail::HWModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::setAllPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<Attribute> names) {
  return static_cast<const ConcreteOp *>(impl)->setAllPortNames(tablegen_opaque_val, names);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
::circt::hw::ModulePortLookupInfo detail::HWMutableModuleLikeInterfaceTraits::Model<ConcreteOp>::getPortLookupInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortLookupInfo();
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::Model<ConcreteOp>::modifyPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
  (llvm::cast<ConcreteOp>(tablegen_opaque_val)).modifyPorts(insertInputs, insertOutputs, eraseInputs, eraseOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::Model<ConcreteOp>::insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).insertPorts(insertInputs, insertOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::Model<ConcreteOp>::erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).erasePorts(eraseInputs, eraseOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::Model<ConcreteOp>::appendOutputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<StringAttr, Value>> outputs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).appendOutputs(outputs);
}
template<typename ConcreteOp>
::circt::hw::ModulePortLookupInfo detail::HWMutableModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::getPortLookupInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortLookupInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::modifyPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
  return static_cast<const ConcreteOp *>(impl)->modifyPorts(tablegen_opaque_val, insertInputs, insertOutputs, eraseInputs, eraseOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::insertPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) {
  return static_cast<const ConcreteOp *>(impl)->insertPorts(tablegen_opaque_val, insertInputs, insertOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::erasePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
  return static_cast<const ConcreteOp *>(impl)->erasePorts(tablegen_opaque_val, eraseInputs, eraseOutputs);
}
template<typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::FallbackModel<ConcreteOp>::appendOutputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<StringAttr, Value>> outputs) {
  return static_cast<const ConcreteOp *>(impl)->appendOutputs(tablegen_opaque_val, outputs);
}
template<typename ConcreteModel, typename ConcreteOp>
::circt::hw::ModulePortLookupInfo detail::HWMutableModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortLookupInfo(::mlir::Operation *tablegen_opaque_val) const {
return hw::ModulePortLookupInfo(
        (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext(),
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortList());
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::insertPorts(::mlir::Operation *tablegen_opaque_val, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).modifyPorts(insertInputs, insertOutputs, {}, {});
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWMutableModuleLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::erasePorts(::mlir::Operation *tablegen_opaque_val, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).modifyPorts({}, {}, eraseInputs, eraseOutputs);
}

} // namespace circt::hw
namespace circt::hw {


} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::getInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputName(idx);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::getOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOutputName(idx);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::setInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setInputName(idx, name);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::setOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setOutputName(idx, name);
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::getInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputNames();
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::getOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOutputNames();
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::setInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setInputNames(names);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::setOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setOutputNames(names);
}
template<typename ConcreteOp>
bool detail::HWInstanceLikeInterfaceTraits::Model<ConcreteOp>::getDoNotPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDoNotPrint();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getInputName(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx) {
  return static_cast<const ConcreteOp *>(impl)->getOutputName(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setInputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) {
  return static_cast<const ConcreteOp *>(impl)->setInputName(tablegen_opaque_val, idx, name);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setOutputName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) {
  return static_cast<const ConcreteOp *>(impl)->setOutputName(tablegen_opaque_val, idx, name);
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInputNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getOutputNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setInputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) {
  return static_cast<const ConcreteOp *>(impl)->setInputNames(tablegen_opaque_val, names);
}
template<typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::setOutputNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) {
  return static_cast<const ConcreteOp *>(impl)->setOutputNames(tablegen_opaque_val, names);
}
template<typename ConcreteOp>
bool detail::HWInstanceLikeInterfaceTraits::FallbackModel<ConcreteOp>::getDoNotPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDoNotPrint(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInputName(::mlir::Operation *tablegen_opaque_val, size_t idx) const {
return ::circt::hw::instance_like_impl::getName(
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getArgNames(), idx);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::StringAttr detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getOutputName(::mlir::Operation *tablegen_opaque_val, size_t idx) const {
return ::circt::hw::instance_like_impl::getName(
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResultNames(), idx);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setInputName(::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setArgNamesAttr(::circt::hw::instance_like_impl::updateName(
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getArgNames(), idx, name));
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setOutputName(::mlir::Operation *tablegen_opaque_val, size_t idx, ::mlir::StringAttr name) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setResultNamesAttr(::circt::hw::instance_like_impl::updateName(
        (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResultNames(), idx, name));
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInputNames(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getArgNamesAttr();
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::ArrayAttr detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getOutputNames(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResultNamesAttr();
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setInputNames(::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setArgNamesAttr(names);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::HWInstanceLikeInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setOutputNames(::mlir::Operation *tablegen_opaque_val, ::mlir::ArrayAttr names) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setResultNamesAttr(names);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
::mlir::StringAttr detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInnerNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerNameAttr();
}
template<typename ConcreteOp>
::std::optional<::mlir::StringRef> detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInnerName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerName();
}
template<typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::setInnerSymbol(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setInnerSymbol(name);
}
template<typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::setInnerSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setInnerSymbolAttr(sym);
}
template<typename ConcreteOp>
::circt::hw::InnerRefAttr detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInnerRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerRef();
}
template<typename ConcreteOp>
::circt::hw::InnerSymAttr detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerSymAttr();
}
template<typename ConcreteOp>
bool detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::supportsPerFieldSymbols() {
  return ConcreteOp::supportsPerFieldSymbols();
}
template<typename ConcreteOp>
std::optional<size_t> detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTargetResultIndex() {
  return ConcreteOp::getTargetResultIndex();
}
template<typename ConcreteOp>
OpResult detail::InnerSymbolOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTargetResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTargetResult();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInnerNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInnerNameAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::std::optional<::mlir::StringRef> detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInnerName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInnerName(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setInnerSymbol(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) {
  return static_cast<const ConcreteOp *>(impl)->setInnerSymbol(tablegen_opaque_val, name);
}
template<typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setInnerSymbolAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym) {
  return static_cast<const ConcreteOp *>(impl)->setInnerSymbolAttr(tablegen_opaque_val, sym);
}
template<typename ConcreteOp>
::circt::hw::InnerRefAttr detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInnerRef(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInnerRef(tablegen_opaque_val);
}
template<typename ConcreteOp>
::circt::hw::InnerSymAttr detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInnerSymAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInnerSymAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::supportsPerFieldSymbols() {
  return ConcreteOp::supportsPerFieldSymbols();
}
template<typename ConcreteOp>
std::optional<size_t> detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTargetResultIndex() {
  return ConcreteOp::getTargetResultIndex();
}
template<typename ConcreteOp>
OpResult detail::InnerSymbolOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTargetResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getTargetResult(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::StringAttr detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInnerNameAttr(::mlir::Operation *tablegen_opaque_val) const {
if (auto attr =
              this->getOperation()->template getAttrOfType<hw::InnerSymAttr>(
              circt::hw::InnerSymbolTable::getInnerSymbolAttrName()))
          return attr.getSymName();
        return {};
}
template<typename ConcreteModel, typename ConcreteOp>
::std::optional<::mlir::StringRef> detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInnerName(::mlir::Operation *tablegen_opaque_val) const {
auto attr = this->getInnerNameAttr();
        return attr ? ::std::optional<StringRef>(attr.getValue()) : ::std::nullopt;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setInnerSymbol(::mlir::Operation *tablegen_opaque_val, ::mlir::StringAttr name) const {
this->getOperation()->setAttr(
            InnerSymbolTable::getInnerSymbolAttrName(), hw::InnerSymAttr::get(name));
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setInnerSymbolAttr(::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerSymAttr sym) const {
if (sym && !sym.empty())
          this->getOperation()->setAttr(
              InnerSymbolTable::getInnerSymbolAttrName(), sym);
        else
          this->getOperation()->removeAttr(InnerSymbolTable::getInnerSymbolAttrName());
}
template<typename ConcreteModel, typename ConcreteOp>
::circt::hw::InnerRefAttr detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInnerRef(::mlir::Operation *tablegen_opaque_val) const {
auto *op = this->getOperation();
        return hw::InnerRefAttr::get(
            SymbolTable::getSymbolName(
                op->template getParentWithTrait<OpTrait::InnerSymbolTable>()),
            InnerSymbolTable::getInnerSymbol(op));
}
template<typename ConcreteModel, typename ConcreteOp>
::circt::hw::InnerSymAttr detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInnerSymAttr(::mlir::Operation *tablegen_opaque_val) const {
return this->getOperation()->template getAttrOfType<hw::InnerSymAttr>(
              circt::hw::InnerSymbolTable::getInnerSymbolAttrName());
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::supportsPerFieldSymbols() {
return ConcreteOp::getTargetResultIndex().has_value();
}
template<typename ConcreteModel, typename ConcreteOp>
OpResult detail::InnerSymbolOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getTargetResult(::mlir::Operation *tablegen_opaque_val) const {
auto idx = ConcreteOp::getTargetResultIndex();
        if (!idx)
          return {};
        return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResult(*idx);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
::mlir::LogicalResult detail::InnerRefUserOpInterfaceInterfaceTraits::Model<ConcreteOp>::verifyInnerRefs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerRefNamespace& ns) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).verifyInnerRefs(ns);
}
template<typename ConcreteOp>
::mlir::LogicalResult detail::InnerRefUserOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::verifyInnerRefs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::InnerRefNamespace& ns) {
  return static_cast<const ConcreteOp *>(impl)->verifyInnerRefs(tablegen_opaque_val, ns);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteOp>
llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> detail::CombDataFlowInterfaceTraits::Model<ConcreteOp>::computeDataFlow(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).computeDataFlow();
}
template<typename ConcreteOp>
llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> detail::CombDataFlowInterfaceTraits::FallbackModel<ConcreteOp>::computeDataFlow(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->computeDataFlow(tablegen_opaque_val);
}

} // namespace circt::hw
