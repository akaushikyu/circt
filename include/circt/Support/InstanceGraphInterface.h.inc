/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::igraph {

/// This interface provides hooks for an instance-like operation.
class InstanceOpInterface;

} // namespace circt::igraph
namespace circt::igraph {

/// This interface provides hooks for a module-like operation.
class ModuleOpInterface;

} // namespace circt::igraph
namespace circt::igraph {

/// This interface provides hooks for an instance-like operation.
namespace detail {
struct InstanceOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::StringRef (*getInstanceName)(const Concept *impl, ::mlir::Operation *);
    ::mlir::StringAttr (*getInstanceNameAttr)(const Concept *impl, ::mlir::Operation *);
    ::llvm::SmallVector<::llvm::StringRef, 1> (*getReferencedModuleNames)(const Concept *impl, ::mlir::Operation *);
    ::mlir::ArrayAttr (*getReferencedModuleNamesAttr)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::igraph::InstanceOpInterface;
    Model() : Concept{getInstanceName, getInstanceNameAttr, getReferencedModuleNames, getReferencedModuleNamesAttr} {}

    static inline ::llvm::StringRef getInstanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getInstanceNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::ArrayAttr getReferencedModuleNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::igraph::InstanceOpInterface;
    FallbackModel() : Concept{getInstanceName, getInstanceNameAttr, getReferencedModuleNames, getReferencedModuleNamesAttr} {}

    static inline ::llvm::StringRef getInstanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getInstanceNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::ArrayAttr getReferencedModuleNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::ArrayAttr getReferencedModuleNamesAttr(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct InstanceOpInterfaceTrait;

} // namespace detail
class InstanceOpInterface : public ::mlir::OpInterface<InstanceOpInterface, detail::InstanceOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<InstanceOpInterface, detail::InstanceOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::InstanceOpInterfaceTrait<ConcreteOp> {};

  /// Get the name of the instance
  ::llvm::StringRef getInstanceName();

  /// Get the name of the instance
  ::mlir::StringAttr getInstanceNameAttr();

  /// Get the name of all the possibly instantiated modules
  ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames();

  /// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
  ::mlir::ArrayAttr getReferencedModuleNamesAttr();
};

} // namespace circt::igraph
namespace circt::igraph {

/// This interface provides hooks for a module-like operation.
namespace detail {
struct ModuleOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::StringRef (*getModuleName)(const Concept *impl, ::mlir::Operation *);
    ::mlir::StringAttr (*getModuleNameAttr)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::igraph::ModuleOpInterface;
    Model() : Concept{getModuleName, getModuleNameAttr} {}

    static inline ::llvm::StringRef getModuleName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getModuleNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::igraph::ModuleOpInterface;
    FallbackModel() : Concept{getModuleName, getModuleNameAttr} {}

    static inline ::llvm::StringRef getModuleName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getModuleNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::llvm::StringRef getModuleName(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::StringAttr getModuleNameAttr(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct ModuleOpInterfaceTrait;

} // namespace detail
class ModuleOpInterface : public ::mlir::OpInterface<ModuleOpInterface, detail::ModuleOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ModuleOpInterface, detail::ModuleOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ModuleOpInterfaceTrait<ConcreteOp> {};

  /// Get the module name
  ::llvm::StringRef getModuleName();

  /// Get the module name
  ::mlir::StringAttr getModuleNameAttr();
};

} // namespace circt::igraph
namespace circt::igraph::detail {

  template <typename ConcreteOp>
  struct InstanceOpInterfaceTrait : public ::mlir::OpInterface<InstanceOpInterface, detail::InstanceOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the name of all the possibly instantiated modules
    ::llvm::SmallVector<::llvm::StringRef, 1> getReferencedModuleNames() {
      ::llvm::SmallVector<::llvm::StringRef, 1> targetNames;
      for (::mlir::Attribute targetNameAttr : (*static_cast<ConcreteOp *>(this)).getReferencedModuleNamesAttr())
        targetNames.push_back(
            llvm::cast<::mlir::StringAttr>(targetNameAttr).getValue());
      return targetNames;
    }

    /// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
    ::mlir::ArrayAttr getReferencedModuleNamesAttr() {
      auto attr = (*static_cast<ConcreteOp *>(this)).getReferencedModuleNameAttr();
      return ::mlir::ArrayAttr::get(attr.getContext(), {attr});
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      if (mlir::cast<ConcreteOp>(op)
            .getReferencedModuleNamesAttr()
            .size())
      return success();
    return op->emitOpError("expected a non-empty list of referenced modules");
    }
  };

} // namespace circt::igraph::detail
namespace circt::igraph::detail {

  template <typename ConcreteOp>
  struct ModuleOpInterfaceTrait : public ::mlir::OpInterface<ModuleOpInterface, detail::ModuleOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the module name
    ::llvm::StringRef getModuleName() {
      return (*static_cast<ConcreteOp *>(this)).getModuleNameAttr().getValue();
    }

    /// Get the module name
    ::mlir::StringAttr getModuleNameAttr() {
      return (*static_cast<ConcreteOp *>(this)).getNameAttr();
    }
  };

} // namespace circt::igraph::detail
namespace circt::igraph {

template<typename ConcreteOp>
::llvm::StringRef detail::InstanceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInstanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInstanceName();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::InstanceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInstanceNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInstanceNameAttr();
}
template<typename ConcreteOp>
::llvm::SmallVector<::llvm::StringRef, 1> detail::InstanceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getReferencedModuleNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReferencedModuleNames();
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::InstanceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getReferencedModuleNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReferencedModuleNamesAttr();
}
template<typename ConcreteOp>
::llvm::StringRef detail::InstanceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInstanceName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInstanceName(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::InstanceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInstanceNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInstanceNameAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::SmallVector<::llvm::StringRef, 1> detail::InstanceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getReferencedModuleNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReferencedModuleNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::ArrayAttr detail::InstanceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getReferencedModuleNamesAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReferencedModuleNamesAttr(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::SmallVector<::llvm::StringRef, 1> detail::InstanceOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getReferencedModuleNames(::mlir::Operation *tablegen_opaque_val) const {
::llvm::SmallVector<::llvm::StringRef, 1> targetNames;
      for (::mlir::Attribute targetNameAttr : (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReferencedModuleNamesAttr())
        targetNames.push_back(
            llvm::cast<::mlir::StringAttr>(targetNameAttr).getValue());
      return targetNames;
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::ArrayAttr detail::InstanceOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getReferencedModuleNamesAttr(::mlir::Operation *tablegen_opaque_val) const {
auto attr = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReferencedModuleNameAttr();
      return ::mlir::ArrayAttr::get(attr.getContext(), {attr});
}

} // namespace circt::igraph
namespace circt::igraph {

template<typename ConcreteOp>
::llvm::StringRef detail::ModuleOpInterfaceInterfaceTraits::Model<ConcreteOp>::getModuleName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getModuleName();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::ModuleOpInterfaceInterfaceTraits::Model<ConcreteOp>::getModuleNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getModuleNameAttr();
}
template<typename ConcreteOp>
::llvm::StringRef detail::ModuleOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getModuleName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getModuleName(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::ModuleOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getModuleNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getModuleNameAttr(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::StringRef detail::ModuleOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getModuleName(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getModuleNameAttr().getValue();
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::StringAttr detail::ModuleOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getModuleNameAttr(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameAttr();
}

} // namespace circt::igraph
