/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

/// This interface should be implemented by operations that have clocked
/// behavior. Don't use this interface for operations that are not themselves
/// clocked but only define a clocked region.
class ClockedOpInterface;

} // namespace circt::arc
namespace circt::arc {

/// This interface should be implemented by operations that have clocked
/// behavior. Don't use this interface for operations that are not themselves
/// clocked but only define a clocked region.
namespace detail {
struct ClockedOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isClocked)();
    ::mlir::Value (*getClock)(const Concept *impl, ::mlir::Operation *);
    void (*eraseClock)(const Concept *impl, ::mlir::Operation *);
    uint32_t (*getLatency)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::arc::ClockedOpInterface;
    Model() : Concept{isClocked, getClock, eraseClock, getLatency} {}

    static inline bool isClocked();
    static inline ::mlir::Value getClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void eraseClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline uint32_t getLatency(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::arc::ClockedOpInterface;
    FallbackModel() : Concept{isClocked, getClock, eraseClock, getLatency} {}

    static inline bool isClocked();
    static inline ::mlir::Value getClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void eraseClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline uint32_t getLatency(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    static bool isClocked();
    void eraseClock(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct ClockedOpInterfaceTrait;

} // namespace detail
class ClockedOpInterface : public ::mlir::OpInterface<ClockedOpInterface, detail::ClockedOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ClockedOpInterface, detail::ClockedOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ClockedOpInterfaceTrait<ConcreteOp> {};

  /// Allows non-clocked counterparts to clocked operations (e.g., `arc.call`)
  /// to implement this interface to simplify the implementation of some
  /// passes.
  bool isClocked();

  /// Returns the SSA value representing the clock signal. It is valid to
  /// return a null value if the operation is inside a clocked region and thus
  /// the clock is defined by the operation with the clocked region, or if the
  /// operation is not clocked as determined by the `isClocked` static
  /// function.
  ::mlir::Value getClock();

  /// Removes the clock value, e.g., used when moving a clocked operation into
  /// a clocked region. If the operation already does not have a clock, this
  /// should be a nop.
  void eraseClock();

  /// Returns the latency w.r.t. to the clock returned by the `getClock`
  /// function.
  uint32_t getLatency();
};

} // namespace circt::arc
namespace circt::arc::detail {

  template <typename ConcreteOp>
  struct ClockedOpInterfaceTrait : public ::mlir::OpInterface<ClockedOpInterface, detail::ClockedOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Allows non-clocked counterparts to clocked operations (e.g., `arc.call`)
    /// to implement this interface to simplify the implementation of some
    /// passes.
    static bool isClocked() {
      return true;
    }

    /// Removes the clock value, e.g., used when moving a clocked operation into
    /// a clocked region. If the operation already does not have a clock, this
    /// should be a nop.
    void eraseClock() {
      return (*static_cast<ConcreteOp *>(this)).getClockMutable().clear();
    }
  };

} // namespace circt::arc::detail
namespace circt::arc {

template<typename ConcreteOp>
bool detail::ClockedOpInterfaceInterfaceTraits::Model<ConcreteOp>::isClocked() {
  return ConcreteOp::isClocked();
}
template<typename ConcreteOp>
::mlir::Value detail::ClockedOpInterfaceInterfaceTraits::Model<ConcreteOp>::getClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getClock();
}
template<typename ConcreteOp>
void detail::ClockedOpInterfaceInterfaceTraits::Model<ConcreteOp>::eraseClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).eraseClock();
}
template<typename ConcreteOp>
uint32_t detail::ClockedOpInterfaceInterfaceTraits::Model<ConcreteOp>::getLatency(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLatency();
}
template<typename ConcreteOp>
bool detail::ClockedOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isClocked() {
  return ConcreteOp::isClocked();
}
template<typename ConcreteOp>
::mlir::Value detail::ClockedOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getClock(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::ClockedOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::eraseClock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->eraseClock(tablegen_opaque_val);
}
template<typename ConcreteOp>
uint32_t detail::ClockedOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getLatency(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLatency(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::ClockedOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isClocked() {
return true;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::ClockedOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::eraseClock(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getClockMutable().clear();
}

} // namespace circt::arc
