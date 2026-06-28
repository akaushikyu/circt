/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::calyx {

/// This is an op interface for Calyx Groups.
class GroupInterface;

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx Cells. Cells consist
/// of primitives and instances of components.
class CellInterface;

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx Components.
class ComponentInterface;

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx If control ops. Implemented
/// by Dynamic and Static If ops.
class IfInterface;

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx floating point ops.
class FloatingPointOpInterface;

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx Groups.
namespace detail {
struct GroupInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::StringAttr (*symName)(const Concept *impl, ::mlir::Operation *);
    Block*(*getBody)(const Concept *impl, ::mlir::Operation *);
    LogicalResult (*drivesPort)(const Concept *impl, ::mlir::Operation *, Value);
    LogicalResult (*drivesAllPorts)(const Concept *impl, ::mlir::Operation *, ValueRange);
    LogicalResult (*drivesAnyPort)(const Concept *impl, ::mlir::Operation *, ValueRange);
    LogicalResult (*readsAnyPort)(const Concept *impl, ::mlir::Operation *, ValueRange);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::calyx::GroupInterface;
    Model() : Concept{symName, getBody, drivesPort, drivesAllPorts, drivesAnyPort, readsAnyPort} {}

    static inline mlir::StringAttr symName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LogicalResult drivesPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline LogicalResult drivesAllPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
    static inline LogicalResult drivesAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
    static inline LogicalResult readsAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::calyx::GroupInterface;
    FallbackModel() : Concept{symName, getBody, drivesPort, drivesAllPorts, drivesAnyPort, readsAnyPort} {}

    static inline mlir::StringAttr symName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline LogicalResult drivesPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline LogicalResult drivesAllPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
    static inline LogicalResult drivesAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
    static inline LogicalResult readsAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct GroupInterfaceTrait;

} // namespace detail
class GroupInterface : public ::mlir::OpInterface<GroupInterface, detail::GroupInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<GroupInterface, detail::GroupInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::GroupInterfaceTrait<ConcreteOp> {};

  /// This returns the symbol name of the group.
  mlir::StringAttr symName();

  /// This returns the body of the group.
  Block*getBody();

  /// Determines whether the given port is driven by this group.
  LogicalResult drivesPort(Value port);

  /// Determines whether all the given ports are driven by this group.
  LogicalResult drivesAllPorts(ValueRange ports);

  /// Determines whether any of the given ports are driven by this group.
  LogicalResult drivesAnyPort(ValueRange ports);

  /// Determines whether any of the given ports are read by this group.
  LogicalResult readsAnyPort(ValueRange ports);
};

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx Cells. Cells consist
/// of primitives and instances of components.
namespace detail {
struct CellInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    SmallVector<StringRef> (*portNames)(const Concept *impl, ::mlir::Operation *);
    SmallVector<circt::calyx::Direction> (*portDirections)(const Concept *impl, ::mlir::Operation *);
    SmallVector<DictionaryAttr> (*portAttributes)(const Concept *impl, ::mlir::Operation *);
    StringRef (*instanceName)(const Concept *impl, ::mlir::Operation *);
    unsigned (*portIndex)(const Concept *impl, ::mlir::Operation *, Value);
    SmallVector<circt::calyx::PortInfo> (*getPortInfo)(const Concept *impl, ::mlir::Operation *);
    circt::calyx::PortInfo (*portInfo)(const Concept *impl, ::mlir::Operation *, Value);
    circt::calyx::Direction (*direction)(const Concept *impl, ::mlir::Operation *, Value);
    StringRef (*portName)(const Concept *impl, ::mlir::Operation *, Value);
    DictionaryAttr (*portDictionaryAttr)(const Concept *impl, ::mlir::Operation *, Value);
    SmallVector<Value> (*getInputPorts)(const Concept *impl, ::mlir::Operation *);
    SmallVector<Value> (*getOutputPorts)(const Concept *impl, ::mlir::Operation *);
    SmallVector<Value> (*filterInterfacePorts)(const Concept *impl, ::mlir::Operation *, calyx::Direction);
    bool (*isCombinational)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::calyx::CellInterface;
    Model() : Concept{portNames, portDirections, portAttributes, instanceName, portIndex, getPortInfo, portInfo, direction, portName, portDictionaryAttr, getInputPorts, getOutputPorts, filterInterfacePorts, isCombinational} {}

    static inline SmallVector<StringRef> portNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::Direction> portDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<DictionaryAttr> portAttributes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringRef instanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned portIndex(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline SmallVector<circt::calyx::PortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline circt::calyx::PortInfo portInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline circt::calyx::Direction direction(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline StringRef portName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline DictionaryAttr portDictionaryAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline SmallVector<Value> getInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Value> getOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Value> filterInterfacePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, calyx::Direction dir);
    static inline bool isCombinational(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::calyx::CellInterface;
    FallbackModel() : Concept{portNames, portDirections, portAttributes, instanceName, portIndex, getPortInfo, portInfo, direction, portName, portDictionaryAttr, getInputPorts, getOutputPorts, filterInterfacePorts, isCombinational} {}

    static inline SmallVector<StringRef> portNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::Direction> portDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<DictionaryAttr> portAttributes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringRef instanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned portIndex(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline SmallVector<circt::calyx::PortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline circt::calyx::PortInfo portInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline circt::calyx::Direction direction(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline StringRef portName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline DictionaryAttr portDictionaryAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port);
    static inline SmallVector<Value> getInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Value> getOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<Value> filterInterfacePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, calyx::Direction dir);
    static inline bool isCombinational(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    StringRef instanceName(::mlir::Operation *tablegen_opaque_val) const;
    unsigned portIndex(::mlir::Operation *tablegen_opaque_val, Value port) const;
    SmallVector<circt::calyx::PortInfo> getPortInfo(::mlir::Operation *tablegen_opaque_val) const;
    circt::calyx::PortInfo portInfo(::mlir::Operation *tablegen_opaque_val, Value port) const;
    circt::calyx::Direction direction(::mlir::Operation *tablegen_opaque_val, Value port) const;
    StringRef portName(::mlir::Operation *tablegen_opaque_val, Value port) const;
    DictionaryAttr portDictionaryAttr(::mlir::Operation *tablegen_opaque_val, Value port) const;
    SmallVector<Value> getInputPorts(::mlir::Operation *tablegen_opaque_val) const;
    SmallVector<Value> getOutputPorts(::mlir::Operation *tablegen_opaque_val) const;
    SmallVector<Value> filterInterfacePorts(::mlir::Operation *tablegen_opaque_val, calyx::Direction dir) const;
  };
};
template <typename ConcreteOp>
struct CellInterfaceTrait;

} // namespace detail
class CellInterface : public ::mlir::OpInterface<CellInterface, detail::CellInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<CellInterface, detail::CellInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::CellInterfaceTrait<ConcreteOp> {};

  /// This returns the port names associated with the cell.
  SmallVector<StringRef> portNames();

  /// This returns the port directions associated with the cell.
  SmallVector<circt::calyx::Direction> portDirections();

  /// This returns the port attributes associated with the cell.
  SmallVector<DictionaryAttr> portAttributes();

  /// This returns the instance name of the cell.
  StringRef instanceName();

  /// This returns the index of the port within the result values of this cell.
  unsigned portIndex(Value port);

  /// This returns the PortInfo associated with all of the ports of a cell.
  SmallVector<circt::calyx::PortInfo> getPortInfo();

  /// This returns the PortInfo associated with the port of a cell.
  circt::calyx::PortInfo portInfo(Value port);

  /// This returns the direction of a given port of a cell.
  circt::calyx::Direction direction(Value port);

  /// This returns the name of a given port of a cell.
  StringRef portName(Value port);

  /// This returns the attributes of a given port of a cell.
  DictionaryAttr portDictionaryAttr(Value port);

  /// This returns the input ports of a cell.
  SmallVector<Value> getInputPorts();

  /// This returns the output ports of a cell.
  SmallVector<Value> getOutputPorts();

  /// This returns the ports of a cell, filtering out any interface ports.
  SmallVector<Value> filterInterfacePorts(calyx::Direction dir);

  /// This returns true iff the cell is combinational
  bool isCombinational();
};

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx Components.
namespace detail {
struct ComponentInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ArrayAttr (*getPortNames)(const Concept *impl, ::mlir::Operation *);
    SmallVector<circt::calyx::PortInfo> (*getPortInfo)(const Concept *impl, ::mlir::Operation *);
    SmallVector<circt::calyx::PortInfo> (*getInputPortInfo)(const Concept *impl, ::mlir::Operation *);
    SmallVector<circt::calyx::PortInfo> (*getOutputPortInfo)(const Concept *impl, ::mlir::Operation *);
    StringRef (*getName)(const Concept *impl, ::mlir::Operation *);
    bool (*isComb)(const Concept *impl, ::mlir::Operation *);
    Region*(*getRegion)(const Concept *impl, ::mlir::Operation *);
    Block*(*getBodyBlock)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::calyx::ComponentInterface;
    Model() : Concept{getPortNames, getPortInfo, getInputPortInfo, getOutputPortInfo, getName, isComb, getRegion, getBodyBlock} {}

    static inline ArrayAttr getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getInputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getOutputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool isComb(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Region*getRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::calyx::ComponentInterface;
    FallbackModel() : Concept{getPortNames, getPortInfo, getInputPortInfo, getOutputPortInfo, getName, isComb, getRegion, getBodyBlock} {}

    static inline ArrayAttr getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getInputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline SmallVector<circt::calyx::PortInfo> getOutputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool isComb(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Region*getRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ComponentInterfaceTrait;

} // namespace detail
class ComponentInterface : public ::mlir::OpInterface<ComponentInterface, detail::ComponentInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ComponentInterface, detail::ComponentInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ComponentInterfaceTrait<ConcreteOp> {};

  /// This returns the port names associated with the component.
  ArrayAttr getPortNames();

  /// This returns the port info associated with the component.
  SmallVector<circt::calyx::PortInfo> getPortInfo();

  /// This returns the input port info associated with the component.
  SmallVector<circt::calyx::PortInfo> getInputPortInfo();

  /// This returns the output port info associated with the component.
  SmallVector<circt::calyx::PortInfo> getOutputPortInfo();

  /// This returns the name of the component.
  StringRef getName();

  /// This returns true iff the component is combinational.
  bool isComb();

  /// This returns the body region of the component.
  Region*getRegion();

  /// This returns the body block of the component.
  Block*getBodyBlock();
};

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx If control ops. Implemented
/// by Dynamic and Static If ops.
namespace detail {
struct IfInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*thenBodyExists)(const Concept *impl, ::mlir::Operation *);
    bool (*elseBodyExists)(const Concept *impl, ::mlir::Operation *);
    Block*(*getThenBody)(const Concept *impl, ::mlir::Operation *);
    Block*(*getElseBody)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::calyx::IfInterface;
    Model() : Concept{thenBodyExists, elseBodyExists, getThenBody, getElseBody} {}

    static inline bool thenBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool elseBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getThenBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getElseBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::calyx::IfInterface;
    FallbackModel() : Concept{thenBodyExists, elseBodyExists, getThenBody, getElseBody} {}

    static inline bool thenBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool elseBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getThenBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Block*getElseBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    bool thenBodyExists(::mlir::Operation *tablegen_opaque_val) const;
    bool elseBodyExists(::mlir::Operation *tablegen_opaque_val) const;
    Block*getThenBody(::mlir::Operation *tablegen_opaque_val) const;
    Block*getElseBody(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct IfInterfaceTrait;

} // namespace detail
class IfInterface : public ::mlir::OpInterface<IfInterface, detail::IfInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<IfInterface, detail::IfInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::IfInterfaceTrait<ConcreteOp> {};

  /// This returns true if the then body exists.
  bool thenBodyExists();

  /// This returns true if the else body exists.
  bool elseBodyExists();

  /// This returns the then body block.
  Block*getThenBody();

  /// This returns the else body block.
  Block*getElseBody();
};

} // namespace circt::calyx
namespace circt::calyx {

/// This is an op interface for Calyx floating point ops.
namespace detail {
struct FloatingPointOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    FloatingPointStandard (*getFloatingPointStandard)();
    std::string (*getCalyxLibraryName)();
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::calyx::FloatingPointOpInterface;
    Model() : Concept{getFloatingPointStandard, getCalyxLibraryName} {}

    static inline FloatingPointStandard getFloatingPointStandard();
    static inline std::string getCalyxLibraryName();
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::calyx::FloatingPointOpInterface;
    FallbackModel() : Concept{getFloatingPointStandard, getCalyxLibraryName} {}

    static inline FloatingPointStandard getFloatingPointStandard();
    static inline std::string getCalyxLibraryName();
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct FloatingPointOpInterfaceTrait;

} // namespace detail
class FloatingPointOpInterface : public ::mlir::OpInterface<FloatingPointOpInterface, detail::FloatingPointOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<FloatingPointOpInterface, detail::FloatingPointOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FloatingPointOpInterfaceTrait<ConcreteOp> {};

  /// This returns the floating point standard.
  FloatingPointStandard getFloatingPointStandard();

  /// This returns the Calyx native library name.
  std::string getCalyxLibraryName();
};

} // namespace circt::calyx
namespace circt::calyx::detail {

  template <typename ConcreteOp>
  struct GroupInterfaceTrait : public ::mlir::OpInterface<GroupInterface, detail::GroupInterfaceInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyGroupInterface(op);
    }
  };

} // namespace circt::calyx::detail
namespace circt::calyx::detail {

  template <typename ConcreteOp>
  struct CellInterfaceTrait : public ::mlir::OpInterface<CellInterface, detail::CellInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// This returns the instance name of the cell.
    StringRef instanceName() {
      return (*static_cast<ConcreteOp *>(this)).getOperation()->template getAttrOfType<mlir::StringAttr>(
          mlir::SymbolTable::getSymbolAttrName()).getValue();
    }

    /// This returns the index of the port within the result values of this cell.
    unsigned portIndex(Value port) {
      for (auto it : llvm::enumerate((*static_cast<ConcreteOp *>(this))->getResults()))
          if (it.value() == port)
            return it.index();
        assert(false && "argument port not found in this cell.");
        return  {};
    }

    /// This returns the PortInfo associated with all of the ports of a cell.
    SmallVector<circt::calyx::PortInfo> getPortInfo() {
      SmallVector<circt::calyx::PortInfo> ports;
        MLIRContext* context = (*static_cast<ConcreteOp *>(this))->getContext();
        auto portAttrs = (*static_cast<ConcreteOp *>(this)).portAttributes();
        portAttrs.resize((*static_cast<ConcreteOp *>(this))->getResults().size());
        auto zippedPortInfo = llvm::zip_equal(
          (*static_cast<ConcreteOp *>(this))->getResults(),
          (*static_cast<ConcreteOp *>(this)).portDirections(),
          (*static_cast<ConcreteOp *>(this)).portNames(),
          portAttrs
        );
        for (auto&& [result, direction, name, attributes] : zippedPortInfo)
          ports.push_back(PortInfo{
              StringAttr::get(context, name),
              result.getType(),
              direction,
              attributes
          });
        return ports;
    }

    /// This returns the PortInfo associated with the port of a cell.
    circt::calyx::PortInfo portInfo(Value port) {
      return getPortInfo()[portIndex(port)];
    }

    /// This returns the direction of a given port of a cell.
    circt::calyx::Direction direction(Value port) {
      return portInfo(port).direction;
    }

    /// This returns the name of a given port of a cell.
    StringRef portName(Value port) {
      return portInfo(port).name.getValue();
    }

    /// This returns the attributes of a given port of a cell.
    DictionaryAttr portDictionaryAttr(Value port) {
      return portInfo(port).attributes;
    }

    /// This returns the input ports of a cell.
    SmallVector<Value> getInputPorts() {
      SmallVector<Value> ports;
        for (auto&& [result, direction] : llvm::zip((*static_cast<ConcreteOp *>(this))->getResults(), (*static_cast<ConcreteOp *>(this)).portDirections()))
          if (direction == calyx::Direction::Input)
            ports.push_back(result);
        return ports;
    }

    /// This returns the output ports of a cell.
    SmallVector<Value> getOutputPorts() {
      SmallVector<Value> ports;
        for (auto&& [result, direction] : llvm::zip((*static_cast<ConcreteOp *>(this))->getResults(), (*static_cast<ConcreteOp *>(this)).portDirections()))
          if (direction == calyx::Direction::Output)
            ports.push_back(result);
        return ports;
    }

    /// This returns the ports of a cell, filtering out any interface ports.
    SmallVector<Value> filterInterfacePorts(calyx::Direction dir) {
      auto isInterfacePort = [](const PortInfo& port) {
          return port.hasAttribute("go")   || port.hasAttribute("reset") ||
                 port.hasAttribute("done") || port.hasAttribute("clk");
        };

        SmallVector<Value> filteredPorts;
        for (auto&& [result, port] : llvm::zip((*static_cast<ConcreteOp *>(this))->getResults(), (*static_cast<ConcreteOp *>(this)).getPortInfo())) {
          if (port.direction != dir || !isInterfacePort(port))
            continue;
          filteredPorts.push_back(result);
        }
        return filteredPorts;
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyCell(op);
    }
  };

} // namespace circt::calyx::detail
namespace circt::calyx::detail {

  template <typename ConcreteOp>
  struct ComponentInterfaceTrait : public ::mlir::OpInterface<ComponentInterface, detail::ComponentInterfaceInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyComponent(op);
    }
  };

} // namespace circt::calyx::detail
namespace circt::calyx::detail {

  template <typename ConcreteOp>
  struct IfInterfaceTrait : public ::mlir::OpInterface<IfInterface, detail::IfInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// This returns true if the then body exists.
    bool thenBodyExists() {
      Region* region = &(*static_cast<ConcreteOp *>(this))->getRegion(0);
        if (region == nullptr)
          return false;
        return !region->empty();
    }

    /// This returns true if the else body exists.
    bool elseBodyExists() {
      Region* region = &(*static_cast<ConcreteOp *>(this))->getRegion(1);
        if (region == nullptr)
          return false;
        return !region->empty();
    }

    /// This returns the then body block.
    Block*getThenBody() {
      assert(thenBodyExists() && "Then region does not exist.");
        Region* region = &(*static_cast<ConcreteOp *>(this))->getRegion(0);
        assert(region->hasOneBlock() && "The Then body should have one Block.");
        return &region->front();
    }

    /// This returns the else body block.
    Block*getElseBody() {
      assert(elseBodyExists() && "Else region does not exist.");
        Region* region = &(*static_cast<ConcreteOp *>(this))->getRegion(1);
        assert(region->hasOneBlock() && "The Else body should have one Block.");
        return &region->front();
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return verifyIf(op);
    }
  };

} // namespace circt::calyx::detail
namespace circt::calyx::detail {

  template <typename ConcreteOp>
  struct FloatingPointOpInterfaceTrait : public ::mlir::OpInterface<FloatingPointOpInterface, detail::FloatingPointOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::calyx::detail
namespace circt::calyx {

template<typename ConcreteOp>
mlir::StringAttr detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::symName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  Operation* op = (llvm::cast<ConcreteOp>(tablegen_opaque_val));
        return op->getAttrOfType<mlir::StringAttr>("sym_name");
}
template<typename ConcreteOp>
Block*detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  Region* region = &(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0);
        assert(region->hasOneBlock() && "The body should have one Block.");
        return &region->front();
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::drivesPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).drivesPort(port);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::drivesAllPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).drivesAllPorts(ports);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::drivesAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).drivesAnyPort(ports);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::Model<ConcreteOp>::readsAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).readsAnyPort(ports);
}
template<typename ConcreteOp>
mlir::StringAttr detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::symName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->symName(tablegen_opaque_val);
}
template<typename ConcreteOp>
Block*detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getBody(tablegen_opaque_val);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::drivesPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->drivesPort(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::drivesAllPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return static_cast<const ConcreteOp *>(impl)->drivesAllPorts(tablegen_opaque_val, ports);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::drivesAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return static_cast<const ConcreteOp *>(impl)->drivesAnyPort(tablegen_opaque_val, ports);
}
template<typename ConcreteOp>
LogicalResult detail::GroupInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::readsAnyPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ValueRange ports) {
  return static_cast<const ConcreteOp *>(impl)->readsAnyPort(tablegen_opaque_val, ports);
}

} // namespace circt::calyx
namespace circt::calyx {

template<typename ConcreteOp>
SmallVector<StringRef> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portNames();
}
template<typename ConcreteOp>
SmallVector<circt::calyx::Direction> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portDirections();
}
template<typename ConcreteOp>
SmallVector<DictionaryAttr> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portAttributes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portAttributes();
}
template<typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::instanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).instanceName();
}
template<typename ConcreteOp>
unsigned detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portIndex(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portIndex(port);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortInfo();
}
template<typename ConcreteOp>
circt::calyx::PortInfo detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portInfo(port);
}
template<typename ConcreteOp>
circt::calyx::Direction detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::direction(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).direction(port);
}
template<typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portName(port);
}
template<typename ConcreteOp>
DictionaryAttr detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::portDictionaryAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portDictionaryAttr(port);
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::getInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputPorts();
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::getOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOutputPorts();
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::filterInterfacePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, calyx::Direction dir) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).filterInterfacePorts(dir);
}
template<typename ConcreteOp>
bool detail::CellInterfaceInterfaceTraits::Model<ConcreteOp>::isCombinational(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isCombinational();
}
template<typename ConcreteOp>
SmallVector<StringRef> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->portNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::Direction> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portDirections(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->portDirections(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<DictionaryAttr> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portAttributes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->portAttributes(tablegen_opaque_val);
}
template<typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::instanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->instanceName(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portIndex(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->portIndex(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
circt::calyx::PortInfo detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->portInfo(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
circt::calyx::Direction detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::direction(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->direction(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->portName(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
DictionaryAttr detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::portDictionaryAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, Value port) {
  return static_cast<const ConcreteOp *>(impl)->portDictionaryAttr(tablegen_opaque_val, port);
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInputPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getOutputPorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getOutputPorts(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::filterInterfacePorts(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, calyx::Direction dir) {
  return static_cast<const ConcreteOp *>(impl)->filterInterfacePorts(tablegen_opaque_val, dir);
}
template<typename ConcreteOp>
bool detail::CellInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isCombinational(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isCombinational(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::instanceName(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOperation()->template getAttrOfType<mlir::StringAttr>(
          mlir::SymbolTable::getSymbolAttrName()).getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::portIndex(::mlir::Operation *tablegen_opaque_val, Value port) const {
for (auto it : llvm::enumerate((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults()))
          if (it.value() == port)
            return it.index();
        assert(false && "argument port not found in this cell.");
        return  {};
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPortInfo(::mlir::Operation *tablegen_opaque_val) const {
SmallVector<circt::calyx::PortInfo> ports;
        MLIRContext* context = (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getContext();
        auto portAttrs = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portAttributes();
        portAttrs.resize((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults().size());
        auto zippedPortInfo = llvm::zip_equal(
          (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults(),
          (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portDirections(),
          (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portNames(),
          portAttrs
        );
        for (auto&& [result, direction, name, attributes] : zippedPortInfo)
          ports.push_back(PortInfo{
              StringAttr::get(context, name),
              result.getType(),
              direction,
              attributes
          });
        return ports;
}
template<typename ConcreteModel, typename ConcreteOp>
circt::calyx::PortInfo detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::portInfo(::mlir::Operation *tablegen_opaque_val, Value port) const {
return getPortInfo()[portIndex(port)];
}
template<typename ConcreteModel, typename ConcreteOp>
circt::calyx::Direction detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::direction(::mlir::Operation *tablegen_opaque_val, Value port) const {
return portInfo(port).direction;
}
template<typename ConcreteModel, typename ConcreteOp>
StringRef detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::portName(::mlir::Operation *tablegen_opaque_val, Value port) const {
return portInfo(port).name.getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
DictionaryAttr detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::portDictionaryAttr(::mlir::Operation *tablegen_opaque_val, Value port) const {
return portInfo(port).attributes;
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInputPorts(::mlir::Operation *tablegen_opaque_val) const {
SmallVector<Value> ports;
        for (auto&& [result, direction] : llvm::zip((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults(), (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portDirections()))
          if (direction == calyx::Direction::Input)
            ports.push_back(result);
        return ports;
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getOutputPorts(::mlir::Operation *tablegen_opaque_val) const {
SmallVector<Value> ports;
        for (auto&& [result, direction] : llvm::zip((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults(), (llvm::cast<ConcreteOp>(tablegen_opaque_val)).portDirections()))
          if (direction == calyx::Direction::Output)
            ports.push_back(result);
        return ports;
}
template<typename ConcreteModel, typename ConcreteOp>
SmallVector<Value> detail::CellInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::filterInterfacePorts(::mlir::Operation *tablegen_opaque_val, calyx::Direction dir) const {
auto isInterfacePort = [](const PortInfo& port) {
          return port.hasAttribute("go")   || port.hasAttribute("reset") ||
                 port.hasAttribute("done") || port.hasAttribute("clk");
        };

        SmallVector<Value> filteredPorts;
        for (auto&& [result, port] : llvm::zip((llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResults(), (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortInfo())) {
          if (port.direction != dir || !isInterfacePort(port))
            continue;
          filteredPorts.push_back(result);
        }
        return filteredPorts;
}

} // namespace circt::calyx
namespace circt::calyx {

template<typename ConcreteOp>
ArrayAttr detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortNames();
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortInfo();
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getInputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputPortInfo();
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getOutputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOutputPortInfo();
}
template<typename ConcreteOp>
StringRef detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getName();
}
template<typename ConcreteOp>
bool detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::isComb(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isComb();
}
template<typename ConcreteOp>
Region*detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRegion();
}
template<typename ConcreteOp>
Block*detail::ComponentInterfaceInterfaceTraits::Model<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getBodyBlock();
}
template<typename ConcreteOp>
ArrayAttr detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInputPortInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
SmallVector<circt::calyx::PortInfo> detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getOutputPortInfo(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getOutputPortInfo(tablegen_opaque_val);
}
template<typename ConcreteOp>
StringRef detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getName(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isComb(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isComb(tablegen_opaque_val);
}
template<typename ConcreteOp>
Region*detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getRegion(tablegen_opaque_val);
}
template<typename ConcreteOp>
Block*detail::ComponentInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getBodyBlock(tablegen_opaque_val);
}

} // namespace circt::calyx
namespace circt::calyx {

template<typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::Model<ConcreteOp>::thenBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).thenBodyExists();
}
template<typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::Model<ConcreteOp>::elseBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).elseBodyExists();
}
template<typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::Model<ConcreteOp>::getThenBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getThenBody();
}
template<typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::Model<ConcreteOp>::getElseBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getElseBody();
}
template<typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::thenBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->thenBodyExists(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::elseBodyExists(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->elseBodyExists(tablegen_opaque_val);
}
template<typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getThenBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getThenBody(tablegen_opaque_val);
}
template<typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getElseBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getElseBody(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::thenBodyExists(::mlir::Operation *tablegen_opaque_val) const {
Region* region = &(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0);
        if (region == nullptr)
          return false;
        return !region->empty();
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::IfInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::elseBodyExists(::mlir::Operation *tablegen_opaque_val) const {
Region* region = &(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(1);
        if (region == nullptr)
          return false;
        return !region->empty();
}
template<typename ConcreteModel, typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getThenBody(::mlir::Operation *tablegen_opaque_val) const {
assert(thenBodyExists() && "Then region does not exist.");
        Region* region = &(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(0);
        assert(region->hasOneBlock() && "The Then body should have one Block.");
        return &region->front();
}
template<typename ConcreteModel, typename ConcreteOp>
Block*detail::IfInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getElseBody(::mlir::Operation *tablegen_opaque_val) const {
assert(elseBodyExists() && "Else region does not exist.");
        Region* region = &(llvm::cast<ConcreteOp>(tablegen_opaque_val))->getRegion(1);
        assert(region->hasOneBlock() && "The Else body should have one Block.");
        return &region->front();
}

} // namespace circt::calyx
namespace circt::calyx {

template<typename ConcreteOp>
FloatingPointStandard detail::FloatingPointOpInterfaceInterfaceTraits::Model<ConcreteOp>::getFloatingPointStandard() {
  return ConcreteOp::getFloatingPointStandard();
}
template<typename ConcreteOp>
std::string detail::FloatingPointOpInterfaceInterfaceTraits::Model<ConcreteOp>::getCalyxLibraryName() {
  return ConcreteOp::getCalyxLibraryName();
}
template<typename ConcreteOp>
FloatingPointStandard detail::FloatingPointOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getFloatingPointStandard() {
  return ConcreteOp::getFloatingPointStandard();
}
template<typename ConcreteOp>
std::string detail::FloatingPointOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getCalyxLibraryName() {
  return ConcreteOp::getCalyxLibraryName();
}

} // namespace circt::calyx
