/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::handshake {

/// An interface for describing operations that define fine-grained dataflow regions.
/// The interface doesn't provide any methods, but is instead used to ensure
/// that users of handshake ops explicitly acknowledge that a given region has
/// fine-grained dataflow semantics.
class FineGrainedDataflowRegionOpInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// Sized Operation with Single Type (SOST).
/// 
/// These are operations whose operands all have the same type and which have
/// an integer size property, be it the number of operation operands (e.g.,
/// for a merge) or the number of operation results (e.g., for a fork).
class SOSTInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// Some handshake operations can have predecessors in other
/// blocks. This is primarily useful for verification purposes during
/// lowering from other dialect, such as the standard CDFG dialect.
class MergeLikeOpInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// "Simulate the Execution of ops. The op takes a set of input values and "
///         "returns the corresponding outputs assuming the precondition to "
///         "execute holds."
class GeneralOpInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// "Simulate the Execution of ops"
class ExecutableOpInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// "Allocate the memory to the meory map in the simulation. "
class MemoryOpInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// "Provides detailed names for the operands and results of an operation."
class NamedIOInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// "Provides information on whether this operation is a control operation."
class ControlInterface;

} // namespace circt::handshake
namespace circt::handshake {

/// An interface for describing operations that define fine-grained dataflow regions.
/// The interface doesn't provide any methods, but is instead used to ensure
/// that users of handshake ops explicitly acknowledge that a given region has
/// fine-grained dataflow semantics.
namespace detail {
struct FineGrainedDataflowRegionOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::FineGrainedDataflowRegionOpInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::FineGrainedDataflowRegionOpInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct FineGrainedDataflowRegionOpInterfaceTrait;

} // namespace detail
class FineGrainedDataflowRegionOpInterface : public ::mlir::OpInterface<FineGrainedDataflowRegionOpInterface, detail::FineGrainedDataflowRegionOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<FineGrainedDataflowRegionOpInterface, detail::FineGrainedDataflowRegionOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::FineGrainedDataflowRegionOpInterfaceTrait<ConcreteOp> {};
};

} // namespace circt::handshake
namespace circt::handshake {

/// Sized Operation with Single Type (SOST).
/// 
/// These are operations whose operands all have the same type and which have
/// an integer size property, be it the number of operation operands (e.g.,
/// for a merge) or the number of operation results (e.g., for a fork).
namespace detail {
struct SOSTInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Type (*getDataType)(const Concept *impl, ::mlir::Operation *);
    unsigned (*getSize)(const Concept *impl, ::mlir::Operation *);
    bool (*sostIsControl)(const Concept *impl, ::mlir::Operation *);
    void (*sostPrint)(const Concept *impl, ::mlir::Operation *, mlir::OpAsmPrinter &, bool);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::SOSTInterface;
    Model() : Concept{getDataType, getSize, sostIsControl, sostPrint} {}

    static inline mlir::Type getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getSize(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool sostIsControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void sostPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter & printer, bool explicitSize);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::SOSTInterface;
    FallbackModel() : Concept{getDataType, getSize, sostIsControl, sostPrint} {}

    static inline mlir::Type getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline unsigned getSize(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool sostIsControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void sostPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter & printer, bool explicitSize);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    mlir::Type getDataType(::mlir::Operation *tablegen_opaque_val) const;
    unsigned getSize(::mlir::Operation *tablegen_opaque_val) const;
    bool sostIsControl(::mlir::Operation *tablegen_opaque_val) const;
    void sostPrint(::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter &printer, bool explicitSize) const;
  };
};
template <typename ConcreteOp>
struct SOSTInterfaceTrait;

} // namespace detail
class SOSTInterface : public ::mlir::OpInterface<SOSTInterface, detail::SOSTInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<SOSTInterface, detail::SOSTInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::SOSTInterfaceTrait<ConcreteOp> {};

  /// Get the data type associated to the operation.
  /// The default implementation of this method simply returns the type of
  /// the first operation operand.
  mlir::Type getDataType();

  /// Get the size associated to the operation.
  /// The default implementation of this method simply returns the number of
  /// operation operands.
  unsigned getSize();

  /// Determine whether the operation is a control operation.
  /// The default implementation of this method assumes that the operation
  /// is a control operation if and only if its associated data type is a
  /// NoneType.
  bool sostIsControl();

  /// Print the "SOST characteristics" of an operation.
  /// If the `explicitSize` parameter is set to true, then the method prints
  /// the operation's size (in the SOST sense) between square brackets before
  /// printing the operation's operands, attributes, and data type.
  void sostPrint(mlir::OpAsmPrinter & printer, bool explicitSize);
};

} // namespace circt::handshake
namespace circt::handshake {

/// Some handshake operations can have predecessors in other
/// blocks. This is primarily useful for verification purposes during
/// lowering from other dialect, such as the standard CDFG dialect.
namespace detail {
struct MergeLikeOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::OperandRange (*getDataOperands)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::MergeLikeOpInterface;
    Model() : Concept{getDataOperands} {}

    static inline mlir::OperandRange getDataOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::MergeLikeOpInterface;
    FallbackModel() : Concept{getDataOperands} {}

    static inline mlir::OperandRange getDataOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MergeLikeOpInterfaceTrait;

} // namespace detail
class MergeLikeOpInterface : public ::mlir::OpInterface<MergeLikeOpInterface, detail::MergeLikeOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MergeLikeOpInterface, detail::MergeLikeOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MergeLikeOpInterfaceTrait<ConcreteOp> {};

  /// Returns an operand range over the data signals being merged.
  mlir::OperandRange getDataOperands();
};

} // namespace circt::handshake
namespace circt::handshake {

/// "Simulate the Execution of ops. The op takes a set of input values and "
///         "returns the corresponding outputs assuming the precondition to "
///         "execute holds."
namespace detail {
struct GeneralOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*execute)(const Concept *impl, ::mlir::Operation *, std::vector<llvm::Any> &, std::vector<llvm::Any> &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::GeneralOpInterface;
    Model() : Concept{execute} {}

    static inline void execute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::GeneralOpInterface;
    FallbackModel() : Concept{execute} {}

    static inline void execute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct GeneralOpInterfaceTrait;

} // namespace detail
class GeneralOpInterface : public ::mlir::OpInterface<GeneralOpInterface, detail::GeneralOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<GeneralOpInterface, detail::GeneralOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::GeneralOpInterfaceTrait<ConcreteOp> {};

  /// Simulate the Execution of the general op with given inputs
  void execute(std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs);
};

} // namespace circt::handshake
namespace circt::handshake {

/// "Simulate the Execution of ops"
namespace detail {
struct ExecutableOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*tryExecute)(const Concept *impl, ::mlir::Operation *, llvm::DenseMap<mlir::Value, llvm::Any> &, llvm::DenseMap<unsigned, unsigned> &, llvm::DenseMap<mlir::Value, double> &, std::vector<std::vector<llvm::Any>> &, std::vector<mlir::Value> &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::ExecutableOpInterface;
    Model() : Concept{tryExecute} {}

    static inline bool tryExecute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::ExecutableOpInterface;
    FallbackModel() : Concept{tryExecute} {}

    static inline bool tryExecute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ExecutableOpInterfaceTrait;

} // namespace detail
class ExecutableOpInterface : public ::mlir::OpInterface<ExecutableOpInterface, detail::ExecutableOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ExecutableOpInterface, detail::ExecutableOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ExecutableOpInterfaceTrait<ConcreteOp> {};

  /// The op checks its precondition to execute. If the precondition holds, the op executes with the given input values and returns zero. Otherwise, it returns a false value to suggest the simulator to reschedule. The execution interface of hpx ops take the following arguments: bool = returns whether the op has been executed;valueMap = a map of all values in the code;memoryMap = a map of memory ops to simualte;timeMap = a map of the last arrival time of all values;store = The store associates each allocation in the program(represented by a int) with a vector of values which can beaccessed by it.scheduleList = a list of values to be scheduled.
  bool tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList);
};

} // namespace circt::handshake
namespace circt::handshake {

/// "Allocate the memory to the meory map in the simulation. "
namespace detail {
struct MemoryOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*allocateMemory)(const Concept *impl, ::mlir::Operation *, llvm::DenseMap<unsigned, unsigned> &, std::vector<std::vector<llvm::Any>> &, std::vector<double> &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::MemoryOpInterface;
    Model() : Concept{allocateMemory} {}

    static inline bool allocateMemory(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::MemoryOpInterface;
    FallbackModel() : Concept{allocateMemory} {}

    static inline bool allocateMemory(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MemoryOpInterfaceTrait;

} // namespace detail
class MemoryOpInterface : public ::mlir::OpInterface<MemoryOpInterface, detail::MemoryOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MemoryOpInterface, detail::MemoryOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MemoryOpInterfaceTrait<ConcreteOp> {};

  /// Simulate the memory allocation in the memoryMap
  bool allocateMemory(llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes);
};

} // namespace circt::handshake
namespace circt::handshake {

/// "Provides detailed names for the operands and results of an operation."
namespace detail {
struct NamedIOInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    std::string (*getOperandName)(const Concept *impl, ::mlir::Operation *, unsigned);
    std::string (*getResultName)(const Concept *impl, ::mlir::Operation *, unsigned);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::NamedIOInterface;
    Model() : Concept{getOperandName, getResultName} {}

    static inline std::string getOperandName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx);
    static inline std::string getResultName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::NamedIOInterface;
    FallbackModel() : Concept{getOperandName, getResultName} {}

    static inline std::string getOperandName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx);
    static inline std::string getResultName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    std::string getOperandName(::mlir::Operation *tablegen_opaque_val, unsigned idx) const;
    std::string getResultName(::mlir::Operation *tablegen_opaque_val, unsigned idx) const;
  };
};
template <typename ConcreteOp>
struct NamedIOInterfaceTrait;

} // namespace detail
class NamedIOInterface : public ::mlir::OpInterface<NamedIOInterface, detail::NamedIOInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<NamedIOInterface, detail::NamedIOInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::NamedIOInterfaceTrait<ConcreteOp> {};

  /// Get the name of an operand.
  std::string getOperandName(unsigned idx);

  /// Get the name of a result.
  std::string getResultName(unsigned idx);
};

} // namespace circt::handshake
namespace circt::handshake {

/// "Provides information on whether this operation is a control operation."
namespace detail {
struct ControlInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isControl)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::handshake::ControlInterface;
    Model() : Concept{isControl} {}

    static inline bool isControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::handshake::ControlInterface;
    FallbackModel() : Concept{isControl} {}

    static inline bool isControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    bool isControl(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct ControlInterfaceTrait;

} // namespace detail
class ControlInterface : public ::mlir::OpInterface<ControlInterface, detail::ControlInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ControlInterface, detail::ControlInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ControlInterfaceTrait<ConcreteOp> {};

  /// Returns true if this operation is a control operation.
  bool isControl();
};

} // namespace circt::handshake
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct FineGrainedDataflowRegionOpInterfaceTrait : public ::mlir::OpInterface<FineGrainedDataflowRegionOpInterface, detail::FineGrainedDataflowRegionOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct SOSTInterfaceTrait : public ::mlir::OpInterface<SOSTInterface, detail::SOSTInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the data type associated to the operation.
    /// The default implementation of this method simply returns the type of
    /// the first operation operand.
    mlir::Type getDataType() {
      auto concreteOp = mlir::cast<ConcreteOp>((*static_cast<ConcreteOp *>(this)));
        return concreteOp->getOperands().front().getType();
    }

    /// Get the size associated to the operation.
    /// The default implementation of this method simply returns the number of
    /// operation operands.
    unsigned getSize() {
      auto concreteOp = mlir::cast<ConcreteOp>((*static_cast<ConcreteOp *>(this)));
        return concreteOp->getNumOperands();
    }

    /// Determine whether the operation is a control operation.
    /// The default implementation of this method assumes that the operation
    /// is a control operation if and only if its associated data type is a
    /// NoneType.
    bool sostIsControl() {
      auto concreteOp = mlir::cast<ConcreteOp>((*static_cast<ConcreteOp *>(this)));
        // The operation is a control operation if its single data type is a 
        // NoneType.
        return llvm::isa<mlir::NoneType>(concreteOp.getDataType());
    }

    /// Print the "SOST characteristics" of an operation.
    /// If the `explicitSize` parameter is set to true, then the method prints
    /// the operation's size (in the SOST sense) between square brackets before
    /// printing the operation's operands, attributes, and data type.
    void sostPrint(mlir::OpAsmPrinter & printer, bool explicitSize) {
      auto concreteOp = mlir::cast<ConcreteOp>((*static_cast<ConcreteOp *>(this)));

        if (explicitSize) {
          printer << " [" << concreteOp.getSize() << "]";
        }
        printer << " " << concreteOp->getOperands();
        printer.printOptionalAttrDict(concreteOp->getAttrs());
        printer << " : " << concreteOp.getDataType();
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      auto concreteOp = mlir::cast<ConcreteOp>(op);

    // SOST operation's size must be at least one
    if (concreteOp.getSize() < 1) {
      return concreteOp.emitOpError(
        "SOST operation's size must be at least 1, but has size ") 
        << concreteOp.getSize();
    }

    // SOST operation's operands must all have the same type
    auto dataType = concreteOp.getDataType();
    for (auto operand : concreteOp->getOperands())
      if (operand.getType() != dataType) 
        return concreteOp.emitOpError("SOST operation reports having data type ")
          << dataType << ", but one operand has type " << operand.getType();
    
    return mlir::success();
    }
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct MergeLikeOpInterfaceTrait : public ::mlir::OpInterface<MergeLikeOpInterface, detail::MergeLikeOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      auto concreteOp = mlir::cast<ConcreteOp>(op);

    auto operands = concreteOp.getDataOperands();

    if (!operands.size())
      return concreteOp.emitOpError("must have at least one data operand");

    mlir::Type resultType = op->getResult(0).getType();

    for (auto operand : operands)
      if (operand.getType() != resultType)
        return concreteOp.emitOpError("operand has type ") << operand.getType()
            << ", but result has type " << resultType;

    return mlir::success();
    }
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct GeneralOpInterfaceTrait : public ::mlir::OpInterface<GeneralOpInterface, detail::GeneralOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct ExecutableOpInterfaceTrait : public ::mlir::OpInterface<ExecutableOpInterface, detail::ExecutableOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct MemoryOpInterfaceTrait : public ::mlir::OpInterface<MemoryOpInterface, detail::MemoryOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct NamedIOInterfaceTrait : public ::mlir::OpInterface<NamedIOInterface, detail::NamedIOInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the name of an operand.
    std::string getOperandName(unsigned idx) {
      // Return the default name of an operand.
          return "in" + std::to_string(idx);
    }

    /// Get the name of a result.
    std::string getResultName(unsigned idx) {
      // Return the default name of a result.
          return "out" + std::to_string(idx);
    }
  };

} // namespace circt::handshake::detail
namespace circt::handshake::detail {

  template <typename ConcreteOp>
  struct ControlInterfaceTrait : public ::mlir::OpInterface<ControlInterface, detail::ControlInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns true if this operation is a control operation.
    bool isControl() {
      // Implemented outside of interface due to dependency on
          // SOSTInterface being declared at the time where this method is
          // defined.
          return isControlOpImpl((*static_cast<ConcreteOp *>(this)));
    }
  };

} // namespace circt::handshake::detail
namespace circt::handshake {


} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
mlir::Type detail::SOSTInterfaceInterfaceTraits::Model<ConcreteOp>::getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataType();
}
template<typename ConcreteOp>
unsigned detail::SOSTInterfaceInterfaceTraits::Model<ConcreteOp>::getSize(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSize();
}
template<typename ConcreteOp>
bool detail::SOSTInterfaceInterfaceTraits::Model<ConcreteOp>::sostIsControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).sostIsControl();
}
template<typename ConcreteOp>
void detail::SOSTInterfaceInterfaceTraits::Model<ConcreteOp>::sostPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter & printer, bool explicitSize) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).sostPrint(printer, explicitSize);
}
template<typename ConcreteOp>
mlir::Type detail::SOSTInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDataType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataType(tablegen_opaque_val);
}
template<typename ConcreteOp>
unsigned detail::SOSTInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getSize(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSize(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::SOSTInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::sostIsControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->sostIsControl(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::SOSTInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::sostPrint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter & printer, bool explicitSize) {
  return static_cast<const ConcreteOp *>(impl)->sostPrint(tablegen_opaque_val, printer, explicitSize);
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::Type detail::SOSTInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getDataType(::mlir::Operation *tablegen_opaque_val) const {
auto concreteOp = mlir::cast<ConcreteOp>((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
        return concreteOp->getOperands().front().getType();
}
template<typename ConcreteModel, typename ConcreteOp>
unsigned detail::SOSTInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getSize(::mlir::Operation *tablegen_opaque_val) const {
auto concreteOp = mlir::cast<ConcreteOp>((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
        return concreteOp->getNumOperands();
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::SOSTInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::sostIsControl(::mlir::Operation *tablegen_opaque_val) const {
auto concreteOp = mlir::cast<ConcreteOp>((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
        // The operation is a control operation if its single data type is a 
        // NoneType.
        return llvm::isa<mlir::NoneType>(concreteOp.getDataType());
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::SOSTInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::sostPrint(::mlir::Operation *tablegen_opaque_val, mlir::OpAsmPrinter &printer, bool explicitSize) const {
auto concreteOp = mlir::cast<ConcreteOp>((llvm::cast<ConcreteOp>(tablegen_opaque_val)));

        if (explicitSize) {
          printer << " [" << concreteOp.getSize() << "]";
        }
        printer << " " << concreteOp->getOperands();
        printer.printOptionalAttrDict(concreteOp->getAttrs());
        printer << " : " << concreteOp.getDataType();
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
mlir::OperandRange detail::MergeLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getDataOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getDataOperands();
}
template<typename ConcreteOp>
mlir::OperandRange detail::MergeLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getDataOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getDataOperands(tablegen_opaque_val);
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
void detail::GeneralOpInterfaceInterfaceTraits::Model<ConcreteOp>::execute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).execute(ins, outs);
}
template<typename ConcreteOp>
void detail::GeneralOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::execute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs) {
  return static_cast<const ConcreteOp *>(impl)->execute(tablegen_opaque_val, ins, outs);
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
bool detail::ExecutableOpInterfaceInterfaceTraits::Model<ConcreteOp>::tryExecute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).tryExecute(valueMap, memoryMap, timeMap, store, scheduleList);
}
template<typename ConcreteOp>
bool detail::ExecutableOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::tryExecute(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList) {
  return static_cast<const ConcreteOp *>(impl)->tryExecute(tablegen_opaque_val, valueMap, memoryMap, timeMap, store, scheduleList);
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
bool detail::MemoryOpInterfaceInterfaceTraits::Model<ConcreteOp>::allocateMemory(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).allocateMemory(memoryMap, store, storeTimes);
}
template<typename ConcreteOp>
bool detail::MemoryOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::allocateMemory(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes) {
  return static_cast<const ConcreteOp *>(impl)->allocateMemory(tablegen_opaque_val, memoryMap, store, storeTimes);
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::Model<ConcreteOp>::getOperandName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOperandName(idx);
}
template<typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::Model<ConcreteOp>::getResultName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResultName(idx);
}
template<typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getOperandName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx) {
  return static_cast<const ConcreteOp *>(impl)->getOperandName(tablegen_opaque_val, idx);
}
template<typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getResultName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned idx) {
  return static_cast<const ConcreteOp *>(impl)->getResultName(tablegen_opaque_val, idx);
}
template<typename ConcreteModel, typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getOperandName(::mlir::Operation *tablegen_opaque_val, unsigned idx) const {
// Return the default name of an operand.
          return "in" + std::to_string(idx);
}
template<typename ConcreteModel, typename ConcreteOp>
std::string detail::NamedIOInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getResultName(::mlir::Operation *tablegen_opaque_val, unsigned idx) const {
// Return the default name of a result.
          return "out" + std::to_string(idx);
}

} // namespace circt::handshake
namespace circt::handshake {

template<typename ConcreteOp>
bool detail::ControlInterfaceInterfaceTraits::Model<ConcreteOp>::isControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isControl();
}
template<typename ConcreteOp>
bool detail::ControlInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isControl(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isControl(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::ControlInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isControl(::mlir::Operation *tablegen_opaque_val) const {
// Implemented outside of interface due to dependency on
          // SOSTInterface being declared at the time where this method is
          // defined.
          return isControlOpImpl((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
}

} // namespace circt::handshake
