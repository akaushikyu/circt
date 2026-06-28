/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::msft {

/// Interface for ops that define dynamic instance data.
class DynInstDataOpInterface;

} // namespace circt::msft
namespace circt::msft {

/// Interface for anything which needs to refer to a HierPathOp.
class UnaryDynInstDataOpInterface;

} // namespace circt::msft
namespace circt::msft {

/// Interface for ops that define dynamic instance data.
namespace detail {
struct DynInstDataOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    Operation *(*getTopModule)(const Concept *impl, ::mlir::Operation *, circt::hw::HWSymbolCache &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::msft::DynInstDataOpInterface;
    Model() : Concept{getTopModule} {}

    static inline Operation *getTopModule(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, circt::hw::HWSymbolCache & symCache);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::msft::DynInstDataOpInterface;
    FallbackModel() : Concept{getTopModule} {}

    static inline Operation *getTopModule(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, circt::hw::HWSymbolCache & symCache);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct DynInstDataOpInterfaceTrait;

} // namespace detail
class DynInstDataOpInterface : public ::mlir::OpInterface<DynInstDataOpInterface, detail::DynInstDataOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<DynInstDataOpInterface, detail::DynInstDataOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::DynInstDataOpInterfaceTrait<ConcreteOp> {};

  /// Get the top module op to which this op is providing data for.
  Operation *getTopModule(circt::hw::HWSymbolCache & symCache);
};

} // namespace circt::msft
namespace circt::msft {

/// Interface for anything which needs to refer to a HierPathOp.
namespace detail {
struct UnaryDynInstDataOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    void (*setPathOp)(const Concept *impl, ::mlir::Operation *, ::circt::hw::HierPathOp);
    FlatSymbolRefAttr (*getPathSym)(const Concept *impl, ::mlir::Operation *);
    /// The base classes of this interface.
    const ::circt::msft::DynInstDataOpInterface::Concept *implDynInstDataOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implDynInstDataOpInterface = interfaceMap.lookup<::circt::msft::DynInstDataOpInterface>();
      assert(implDynInstDataOpInterface && "`::circt::msft::UnaryDynInstDataOpInterface` expected its base interface `::circt::msft::DynInstDataOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::msft::UnaryDynInstDataOpInterface;
    Model() : Concept{setPathOp, getPathSym} {}

    static inline void setPathOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref);
    static inline FlatSymbolRefAttr getPathSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::msft::UnaryDynInstDataOpInterface;
    FallbackModel() : Concept{setPathOp, getPathSym} {}

    static inline void setPathOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref);
    static inline FlatSymbolRefAttr getPathSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    void setPathOp(::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref) const;
    FlatSymbolRefAttr getPathSym(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct UnaryDynInstDataOpInterfaceTrait;

} // namespace detail
class UnaryDynInstDataOpInterface : public ::mlir::OpInterface<UnaryDynInstDataOpInterface, detail::UnaryDynInstDataOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<UnaryDynInstDataOpInterface, detail::UnaryDynInstDataOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::UnaryDynInstDataOpInterfaceTrait<ConcreteOp> {};

  /// Set the HierPathOp to which this op is referring.
  void setPathOp(::circt::hw::HierPathOp ref);

  /// Get the symbol of the HierPathOp to which this op is referring.
  FlatSymbolRefAttr getPathSym();
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::msft::DynInstDataOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::msft::DynInstDataOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::msft::DynInstDataOpInterface(*this, getImpl()->implDynInstDataOpInterface);
  }


  /// Get the top module op to which this op is providing data for.
  Operation *getTopModule(circt::hw::HWSymbolCache & symCache);
};

} // namespace circt::msft
namespace circt::msft::detail {

  template <typename ConcreteOp>
  struct DynInstDataOpInterfaceTrait : public ::mlir::OpInterface<DynInstDataOpInterface, detail::DynInstDataOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::msft::detail
namespace circt::msft::detail {

  template <typename ConcreteOp>
  struct UnaryDynInstDataOpInterfaceTrait : public ::mlir::OpInterface<UnaryDynInstDataOpInterface, detail::UnaryDynInstDataOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Set the HierPathOp to which this op is referring.
    void setPathOp(::circt::hw::HierPathOp ref) {
      (*static_cast<ConcreteOp *>(this)).setRefAttr(FlatSymbolRefAttr::get(ref));
    }

    /// Get the symbol of the HierPathOp to which this op is referring.
    FlatSymbolRefAttr getPathSym() {
      return (*static_cast<ConcreteOp *>(this)).getRefAttr();
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return ::circt::msft::verifyUnaryDynInstDataOp(op);
    }
  };

} // namespace circt::msft::detail
namespace circt::msft {

template<typename ConcreteOp>
Operation *detail::DynInstDataOpInterfaceInterfaceTraits::Model<ConcreteOp>::getTopModule(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, circt::hw::HWSymbolCache & symCache) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getTopModule(symCache);
}
template<typename ConcreteOp>
Operation *detail::DynInstDataOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getTopModule(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, circt::hw::HWSymbolCache & symCache) {
  return static_cast<const ConcreteOp *>(impl)->getTopModule(tablegen_opaque_val, symCache);
}

} // namespace circt::msft
namespace circt::msft {

template<typename ConcreteOp>
void detail::UnaryDynInstDataOpInterfaceInterfaceTraits::Model<ConcreteOp>::setPathOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setPathOp(ref);
}
template<typename ConcreteOp>
FlatSymbolRefAttr detail::UnaryDynInstDataOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPathSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPathSym();
}
template<typename ConcreteOp>
void detail::UnaryDynInstDataOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setPathOp(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref) {
  return static_cast<const ConcreteOp *>(impl)->setPathOp(tablegen_opaque_val, ref);
}
template<typename ConcreteOp>
FlatSymbolRefAttr detail::UnaryDynInstDataOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPathSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPathSym(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::UnaryDynInstDataOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::setPathOp(::mlir::Operation *tablegen_opaque_val, ::circt::hw::HierPathOp ref) const {
(llvm::cast<ConcreteOp>(tablegen_opaque_val)).setRefAttr(FlatSymbolRefAttr::get(ref));
}
template<typename ConcreteModel, typename ConcreteOp>
FlatSymbolRefAttr detail::UnaryDynInstDataOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getPathSym(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRefAttr();
}

} // namespace circt::msft
