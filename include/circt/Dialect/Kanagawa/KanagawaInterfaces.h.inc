/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::kanagawa {

/// An interface for operations which define inner symbols with an optional
/// namehint.
class NamedInnerSymbolInterface;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for operations which describe ports.
class PortOpInterface;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for operations which define Kanagawa scopes.
class ScopeOpInterface;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for Kanagawa block-like operations.
class BlockOpInterface;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for Kanagawa operations that act like callable methods.
/// This partially implements similar functionality to the FunctionLike interface
/// which cannot be used for Kanagawa Methods due to Kanagawa methods defining InnerSym's
/// whereas the FunctionLike interface is built on the assumption of the function
/// defining a Symbol (i.e. inherits from the Symbol interface).
class MethodLikeOpInterface;

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for operations which define inner symbols with an optional
/// namehint.
namespace detail {
struct NamedInnerSymbolInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::StringAttr (*getNameHintAttr)(const Concept *impl, ::mlir::Operation *);
    llvm::StringRef (*getNameHint)(const Concept *impl, ::mlir::Operation *);
    /// The base classes of this interface.
    const ::circt::hw::InnerSymbolOpInterface::Concept *implInnerSymbolOpInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implInnerSymbolOpInterface = interfaceMap.lookup<::circt::hw::InnerSymbolOpInterface>();
      assert(implInnerSymbolOpInterface && "`circt::kanagawa::NamedInnerSymbolInterface` expected its base interface `::circt::hw::InnerSymbolOpInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::kanagawa::NamedInnerSymbolInterface;
    Model() : Concept{getNameHintAttr, getNameHint} {}

    static inline mlir::StringAttr getNameHintAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline llvm::StringRef getNameHint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::kanagawa::NamedInnerSymbolInterface;
    FallbackModel() : Concept{getNameHintAttr, getNameHint} {}

    static inline mlir::StringAttr getNameHintAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline llvm::StringRef getNameHint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    mlir::StringAttr getNameHintAttr(::mlir::Operation *tablegen_opaque_val) const;
    llvm::StringRef getNameHint(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct NamedInnerSymbolInterfaceTrait;

} // namespace detail
class NamedInnerSymbolInterface : public ::mlir::OpInterface<NamedInnerSymbolInterface, detail::NamedInnerSymbolInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<NamedInnerSymbolInterface, detail::NamedInnerSymbolInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::NamedInnerSymbolInterfaceTrait<ConcreteOp> {};

  /// Returns the namehint attribute of this op
  mlir::StringAttr getNameHintAttr();

  /// Returns the namehint of this op
  llvm::StringRef getNameHint();
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::hw::InnerSymbolOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::hw::InnerSymbolOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::hw::InnerSymbolOpInterface(*this, getImpl()->implInnerSymbolOpInterface);
  }


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

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for operations which describe ports.
namespace detail {
struct PortOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Type (*getPortType)(const Concept *impl, ::mlir::Operation *);
    mlir::TypedValue<PortRefType> (*getPort)(const Concept *impl, ::mlir::Operation *);
    /// The base classes of this interface.
    const ::circt::hw::InnerSymbolOpInterface::Concept *implInnerSymbolOpInterface = nullptr;
    const circt::kanagawa::NamedInnerSymbolInterface::Concept *implNamedInnerSymbolInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implInnerSymbolOpInterface = interfaceMap.lookup<::circt::hw::InnerSymbolOpInterface>();
      assert(implInnerSymbolOpInterface && "`circt::kanagawa::PortOpInterface` expected its base interface `::circt::hw::InnerSymbolOpInterface` to be registered");
      implNamedInnerSymbolInterface = interfaceMap.lookup<circt::kanagawa::NamedInnerSymbolInterface>();
      assert(implNamedInnerSymbolInterface && "`circt::kanagawa::PortOpInterface` expected its base interface `circt::kanagawa::NamedInnerSymbolInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::kanagawa::PortOpInterface;
    Model() : Concept{getPortType, getPort} {}

    static inline mlir::Type getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<PortRefType> getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::kanagawa::PortOpInterface;
    FallbackModel() : Concept{getPortType, getPort} {}

    static inline mlir::Type getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::TypedValue<PortRefType> getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct PortOpInterfaceTrait;

} // namespace detail
class PortOpInterface : public ::mlir::OpInterface<PortOpInterface, detail::PortOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<PortOpInterface, detail::PortOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::PortOpInterfaceTrait<ConcreteOp> {};

  /// Returns the data type of the port.
  mlir::Type getPortType();

  /// Returns the `!kanagawa.portref` value defined by the op
  mlir::TypedValue<PortRefType> getPort();
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::hw::InnerSymbolOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::hw::InnerSymbolOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::hw::InnerSymbolOpInterface(*this, getImpl()->implInnerSymbolOpInterface);
  }


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
  //===----------------------------------------------------------------===//
  // Inherited from circt::kanagawa::NamedInnerSymbolInterface
  //===----------------------------------------------------------------===//

  operator circt::kanagawa::NamedInnerSymbolInterface () const {
    if (!*this) return nullptr;
    return circt::kanagawa::NamedInnerSymbolInterface(*this, getImpl()->implNamedInnerSymbolInterface);
  }


  /// Returns the namehint attribute of this op
  mlir::StringAttr getNameHintAttr();

  /// Returns the namehint of this op
  llvm::StringRef getNameHint();
};

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for operations which define Kanagawa scopes.
namespace detail {
struct ScopeOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Block*(*getBodyBlock)(const Concept *impl, ::mlir::Operation *);
    mlir::StringAttr (*getScopeName)(const Concept *impl, ::mlir::Operation *);
    Operation*(*lookupInnerSym)(const Concept *impl, ::mlir::Operation *, llvm::StringRef);
    kanagawa::PortOpInterface (*lookupPort)(const Concept *impl, ::mlir::Operation *, llvm::StringRef);
    /// The base classes of this interface.
    const ::circt::hw::InnerSymbolOpInterface::Concept *implInnerSymbolOpInterface = nullptr;
    const circt::kanagawa::NamedInnerSymbolInterface::Concept *implNamedInnerSymbolInterface = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implInnerSymbolOpInterface = interfaceMap.lookup<::circt::hw::InnerSymbolOpInterface>();
      assert(implInnerSymbolOpInterface && "`circt::kanagawa::ScopeOpInterface` expected its base interface `::circt::hw::InnerSymbolOpInterface` to be registered");
      implNamedInnerSymbolInterface = interfaceMap.lookup<circt::kanagawa::NamedInnerSymbolInterface>();
      assert(implNamedInnerSymbolInterface && "`circt::kanagawa::ScopeOpInterface` expected its base interface `circt::kanagawa::NamedInnerSymbolInterface` to be registered");
    }
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::kanagawa::ScopeOpInterface;
    Model() : Concept{getBodyBlock, getScopeName, lookupInnerSym, lookupPort} {}

    static inline mlir::Block*getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getScopeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Operation*lookupInnerSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName);
    static inline kanagawa::PortOpInterface lookupPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::kanagawa::ScopeOpInterface;
    FallbackModel() : Concept{getBodyBlock, getScopeName, lookupInnerSym, lookupPort} {}

    static inline mlir::Block*getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getScopeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline Operation*lookupInnerSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName);
    static inline kanagawa::PortOpInterface lookupPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    Operation*lookupInnerSym(::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName) const;
    kanagawa::PortOpInterface lookupPort(::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName) const;
  };
};
template <typename ConcreteOp>
struct ScopeOpInterfaceTrait;

} // namespace detail
class ScopeOpInterface : public ::mlir::OpInterface<ScopeOpInterface, detail::ScopeOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ScopeOpInterface, detail::ScopeOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ScopeOpInterfaceTrait<ConcreteOp> {};

  /// Returns the body of the scope
  mlir::Block*getBodyBlock();

  /// Returns the symbol name of the scope
  mlir::StringAttr getScopeName();

  /// Lookup an inner symbol in the scope
  Operation*lookupInnerSym(llvm::StringRef symName);

  /// Lookup a port in the scope
  kanagawa::PortOpInterface lookupPort(llvm::StringRef portName);
  //===----------------------------------------------------------------===//
  // Inherited from ::circt::hw::InnerSymbolOpInterface
  //===----------------------------------------------------------------===//

  operator ::circt::hw::InnerSymbolOpInterface () const {
    if (!*this) return nullptr;
    return ::circt::hw::InnerSymbolOpInterface(*this, getImpl()->implInnerSymbolOpInterface);
  }


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
  //===----------------------------------------------------------------===//
  // Inherited from circt::kanagawa::NamedInnerSymbolInterface
  //===----------------------------------------------------------------===//

  operator circt::kanagawa::NamedInnerSymbolInterface () const {
    if (!*this) return nullptr;
    return circt::kanagawa::NamedInnerSymbolInterface(*this, getImpl()->implNamedInnerSymbolInterface);
  }


  /// Returns the namehint attribute of this op
  mlir::StringAttr getNameHintAttr();

  /// Returns the namehint of this op
  llvm::StringRef getNameHint();
};

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for Kanagawa block-like operations.
namespace detail {
struct BlockOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    llvm::SmallVector<Type> (*getInternalResultTypes)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::kanagawa::BlockOpInterface;
    Model() : Concept{getInternalResultTypes} {}

    static inline llvm::SmallVector<Type> getInternalResultTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::kanagawa::BlockOpInterface;
    FallbackModel() : Concept{getInternalResultTypes} {}

    static inline llvm::SmallVector<Type> getInternalResultTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct BlockOpInterfaceTrait;

} // namespace detail
class BlockOpInterface : public ::mlir::OpInterface<BlockOpInterface, detail::BlockOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<BlockOpInterface, detail::BlockOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BlockOpInterfaceTrait<ConcreteOp> {};

  /// Returns the result types of this block from the point of view of inside the block
  llvm::SmallVector<Type> getInternalResultTypes();
};

} // namespace circt::kanagawa
namespace circt::kanagawa {

/// An interface for Kanagawa operations that act like callable methods.
/// This partially implements similar functionality to the FunctionLike interface
/// which cannot be used for Kanagawa Methods due to Kanagawa methods defining InnerSym's
/// whereas the FunctionLike interface is built on the assumption of the function
/// defining a Symbol (i.e. inherits from the Symbol interface).
namespace detail {
struct MethodLikeOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::FunctionType (*getFunctionType)(const Concept *impl, ::mlir::Operation *);
    ::mlir::StringAttr (*getMethodName)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::kanagawa::MethodLikeOpInterface;
    Model() : Concept{getFunctionType, getMethodName} {}

    static inline ::mlir::FunctionType getFunctionType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getMethodName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::kanagawa::MethodLikeOpInterface;
    FallbackModel() : Concept{getFunctionType, getMethodName} {}

    static inline ::mlir::FunctionType getFunctionType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getMethodName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MethodLikeOpInterfaceTrait;

} // namespace detail
class MethodLikeOpInterface : public ::mlir::OpInterface<MethodLikeOpInterface, detail::MethodLikeOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MethodLikeOpInterface, detail::MethodLikeOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MethodLikeOpInterfaceTrait<ConcreteOp> {};

  /// Returns the type of the method.
  ::mlir::FunctionType getFunctionType();

  /// Returns the name of the method.
  ::mlir::StringAttr getMethodName();

    //===------------------------------------------------------------------===//
    // FunctionOpInterface Methods
    //===------------------------------------------------------------------===//

    /// Returns the argument types of this function.
    ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

    /// Returns the result types of this function.
    ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

    /// Returns the entry block of the function.
    Block* getBodyBlock() {
      auto& region = getFunctionBody();
      assert(!region.empty() && "expected non-empty function body");
      return &region.front();
    }

    using BlockArgListType = Region::BlockArgListType;
    BlockArgListType getArguments() { return getFunctionBody().getArguments(); }
    Region &getFunctionBody() {
      assert((*this)->getNumRegions() == 1 && "expected one region");
      return (*this)->getRegion(0);
    }
};

} // namespace circt::kanagawa
namespace circt::kanagawa::detail {

  template <typename ConcreteOp>
  struct NamedInnerSymbolInterfaceTrait : public ::mlir::OpInterface<NamedInnerSymbolInterface, detail::NamedInnerSymbolInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the namehint attribute of this op
    mlir::StringAttr getNameHintAttr() {
      if(auto nameHint = (*static_cast<ConcreteOp *>(this)).getNameAttr())
          return nameHint;
        return (*static_cast<ConcreteOp *>(this)).getInnerSymAttr().getSymName();
    }

    /// Returns the namehint of this op
    llvm::StringRef getNameHint() {
      return getNameHintAttr().strref();
    }
  };

} // namespace circt::kanagawa::detail
namespace circt::kanagawa::detail {

  template <typename ConcreteOp>
  struct PortOpInterfaceTrait : public ::mlir::OpInterface<PortOpInterface, detail::PortOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::kanagawa::detail
namespace circt::kanagawa::detail {

  template <typename ConcreteOp>
  struct ScopeOpInterfaceTrait : public ::mlir::OpInterface<ScopeOpInterface, detail::ScopeOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Lookup an inner symbol in the scope
    Operation*lookupInnerSym(llvm::StringRef symName) {
      // TODO: @mortbopet: fix once we have a way to do nested symbol
        // tables, and by extension, do nested symbol table lookup inside this
        // scope.
        // Until then, brute-force scan the inner symbol ops for a match.
        for (auto op : (*static_cast<ConcreteOp *>(this)).getBodyBlock()->template getOps<hw::InnerSymbolOpInterface>()) {
          auto innerName = op.getInnerName();
          if(!innerName)
            continue;
          if (*innerName == symName)
            return op;
        }
        return nullptr;
    }

    /// Lookup a port in the scope
    kanagawa::PortOpInterface lookupPort(llvm::StringRef portName) {
      return dyn_cast_or_null<kanagawa::PortOpInterface>(this->lookupInnerSym(portName));
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      return detail::verifyScopeOpInterface(op);
    }
  };

} // namespace circt::kanagawa::detail
namespace circt::kanagawa::detail {

  template <typename ConcreteOp>
  struct BlockOpInterfaceTrait : public ::mlir::OpInterface<BlockOpInterface, detail::BlockOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::kanagawa::detail
namespace circt::kanagawa::detail {

  template <typename ConcreteOp>
  struct MethodLikeOpInterfaceTrait : public ::mlir::OpInterface<MethodLikeOpInterface, detail::MethodLikeOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Returns the entry block of the function.
    Block* getBodyBlock() {
      auto& region = getFunctionBody();
      assert(!region.empty() && "expected non-empty function body");
      return &region.front();
    }

    using BlockArgListType = Region::BlockArgListType;
    BlockArgListType getArguments() { return getFunctionBody().getArguments(); }
    Region &getFunctionBody() {
      assert((*static_cast<ConcreteOp *>(this))->getNumRegions() == 1 && "expected one region");
      return (*static_cast<ConcreteOp *>(this))->getRegion(0);
    }
  
  };

} // namespace circt::kanagawa::detail
namespace circt::kanagawa {

template<typename ConcreteOp>
mlir::StringAttr detail::NamedInnerSymbolInterfaceInterfaceTraits::Model<ConcreteOp>::getNameHintAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameHintAttr();
}
template<typename ConcreteOp>
llvm::StringRef detail::NamedInnerSymbolInterfaceInterfaceTraits::Model<ConcreteOp>::getNameHint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameHint();
}
template<typename ConcreteOp>
mlir::StringAttr detail::NamedInnerSymbolInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNameHintAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameHintAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
llvm::StringRef detail::NamedInnerSymbolInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNameHint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameHint(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
mlir::StringAttr detail::NamedInnerSymbolInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNameHintAttr(::mlir::Operation *tablegen_opaque_val) const {
if(auto nameHint = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameAttr())
          return nameHint;
        return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerSymAttr().getSymName();
}
template<typename ConcreteModel, typename ConcreteOp>
llvm::StringRef detail::NamedInnerSymbolInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNameHint(::mlir::Operation *tablegen_opaque_val) const {
return getNameHintAttr().strref();
}

} // namespace circt::kanagawa
namespace circt::kanagawa {

template<typename ConcreteOp>
mlir::Type detail::PortOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPortType();
}
template<typename ConcreteOp>
mlir::TypedValue<PortRefType> detail::PortOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPort();
}
template<typename ConcreteOp>
mlir::Type detail::PortOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPortType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPortType(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::TypedValue<PortRefType> detail::PortOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPort(tablegen_opaque_val);
}

} // namespace circt::kanagawa
namespace circt::kanagawa {

template<typename ConcreteOp>
mlir::Block*detail::ScopeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getBodyBlock();
}
template<typename ConcreteOp>
mlir::StringAttr detail::ScopeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getScopeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInnerNameAttr();
}
template<typename ConcreteOp>
Operation*detail::ScopeOpInterfaceInterfaceTraits::Model<ConcreteOp>::lookupInnerSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).lookupInnerSym(symName);
}
template<typename ConcreteOp>
kanagawa::PortOpInterface detail::ScopeOpInterfaceInterfaceTraits::Model<ConcreteOp>::lookupPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).lookupPort(portName);
}
template<typename ConcreteOp>
mlir::Block*detail::ScopeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getBodyBlock(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::StringAttr detail::ScopeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getScopeName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getScopeName(tablegen_opaque_val);
}
template<typename ConcreteOp>
Operation*detail::ScopeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::lookupInnerSym(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName) {
  return static_cast<const ConcreteOp *>(impl)->lookupInnerSym(tablegen_opaque_val, symName);
}
template<typename ConcreteOp>
kanagawa::PortOpInterface detail::ScopeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::lookupPort(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName) {
  return static_cast<const ConcreteOp *>(impl)->lookupPort(tablegen_opaque_val, portName);
}
template<typename ConcreteModel, typename ConcreteOp>
Operation*detail::ScopeOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::lookupInnerSym(::mlir::Operation *tablegen_opaque_val, llvm::StringRef symName) const {
// TODO: @mortbopet: fix once we have a way to do nested symbol
        // tables, and by extension, do nested symbol table lookup inside this
        // scope.
        // Until then, brute-force scan the inner symbol ops for a match.
        for (auto op : (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getBodyBlock()->template getOps<hw::InnerSymbolOpInterface>()) {
          auto innerName = op.getInnerName();
          if(!innerName)
            continue;
          if (*innerName == symName)
            return op;
        }
        return nullptr;
}
template<typename ConcreteModel, typename ConcreteOp>
kanagawa::PortOpInterface detail::ScopeOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::lookupPort(::mlir::Operation *tablegen_opaque_val, llvm::StringRef portName) const {
return dyn_cast_or_null<kanagawa::PortOpInterface>(this->lookupInnerSym(portName));
}

} // namespace circt::kanagawa
namespace circt::kanagawa {

template<typename ConcreteOp>
llvm::SmallVector<Type> detail::BlockOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInternalResultTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInternalResultTypes();
}
template<typename ConcreteOp>
llvm::SmallVector<Type> detail::BlockOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInternalResultTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInternalResultTypes(tablegen_opaque_val);
}

} // namespace circt::kanagawa
namespace circt::kanagawa {

template<typename ConcreteOp>
::mlir::FunctionType detail::MethodLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getFunctionType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFunctionType();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::MethodLikeOpInterfaceInterfaceTraits::Model<ConcreteOp>::getMethodName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getMethodName();
}
template<typename ConcreteOp>
::mlir::FunctionType detail::MethodLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getFunctionType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFunctionType(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::MethodLikeOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getMethodName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getMethodName(tablegen_opaque_val);
}

} // namespace circt::kanagawa
