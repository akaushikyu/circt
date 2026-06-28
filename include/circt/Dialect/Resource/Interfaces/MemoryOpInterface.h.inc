/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hls_analysis {

/// Per-op interface for allocations whose memory cost should be estimated.
class MemoryResourceOpInterface;

} // namespace circt::hls_analysis
namespace circt::hls_analysis {

/// Per-op interface for allocations whose memory cost should be estimated.
namespace detail {
struct MemoryResourceOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::Type (*getElementType)(const Concept *impl, ::mlir::Operation *);
    ::llvm::SmallVector<int64_t> (*getStaticShape)(const Concept *impl, ::mlir::Operation *);
    int64_t (*getStaticSizeInBits)(const Concept *impl, ::mlir::Operation *);
    ::std::optional<::circt::hls_analysis::StorageKind> (*getPragmaStorageKind)(const Concept *impl, ::mlir::Operation *);
    ::std::optional<::circt::hls_analysis::PartitionSpec> (*getPartitionSpec)(const Concept *impl, ::mlir::Operation *);
    bool (*contributesToBRAMCost)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::hls_analysis::MemoryResourceOpInterface;
    Model() : Concept{getElementType, getStaticShape, getStaticSizeInBits, getPragmaStorageKind, getPartitionSpec, contributesToBRAMCost} {}

    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::SmallVector<int64_t> getStaticShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline int64_t getStaticSizeInBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::circt::hls_analysis::StorageKind> getPragmaStorageKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::circt::hls_analysis::PartitionSpec> getPartitionSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool contributesToBRAMCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hls_analysis::MemoryResourceOpInterface;
    FallbackModel() : Concept{getElementType, getStaticShape, getStaticSizeInBits, getPragmaStorageKind, getPartitionSpec, contributesToBRAMCost} {}

    static inline ::mlir::Type getElementType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::SmallVector<int64_t> getStaticShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline int64_t getStaticSizeInBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::circt::hls_analysis::StorageKind> getPragmaStorageKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::optional<::circt::hls_analysis::PartitionSpec> getPartitionSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline bool contributesToBRAMCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct MemoryResourceOpInterfaceTrait;

} // namespace detail
class MemoryResourceOpInterface : public ::mlir::OpInterface<MemoryResourceOpInterface, detail::MemoryResourceOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<MemoryResourceOpInterface, detail::MemoryResourceOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::MemoryResourceOpInterfaceTrait<ConcreteOp> {};

  /// Element type of the underlying storage.
  ::mlir::Type getElementType();

  /// Static shape; empty if dynamic.
  ::llvm::SmallVector<int64_t> getStaticShape();

  /// Total static size in bits.
  int64_t getStaticSizeInBits();

  /// Pragma-requested storage kind, if any.
  ::std::optional<::circt::hls_analysis::StorageKind> getPragmaStorageKind();

  /// Partitioning spec from array_partition pragma.
  ::std::optional<::circt::hls_analysis::PartitionSpec> getPartitionSpec();

  /// True if this op participates in cost accounting.
  bool contributesToBRAMCost();
};

} // namespace circt::hls_analysis
namespace circt::hls_analysis::detail {

  template <typename ConcreteOp>
  struct MemoryResourceOpInterfaceTrait : public ::mlir::OpInterface<MemoryResourceOpInterface, detail::MemoryResourceOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::hls_analysis::detail
namespace circt::hls_analysis {

template<typename ConcreteOp>
::mlir::Type detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getElementType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getElementType();
}
template<typename ConcreteOp>
::llvm::SmallVector<int64_t> detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getStaticShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getStaticShape();
}
template<typename ConcreteOp>
int64_t detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getStaticSizeInBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getStaticSizeInBits();
}
template<typename ConcreteOp>
::std::optional<::circt::hls_analysis::StorageKind> detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPragmaStorageKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPragmaStorageKind();
}
template<typename ConcreteOp>
::std::optional<::circt::hls_analysis::PartitionSpec> detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::getPartitionSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getPartitionSpec();
}
template<typename ConcreteOp>
bool detail::MemoryResourceOpInterfaceInterfaceTraits::Model<ConcreteOp>::contributesToBRAMCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).contributesToBRAMCost();
}
template<typename ConcreteOp>
::mlir::Type detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getElementType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getElementType(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::SmallVector<int64_t> detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getStaticShape(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getStaticShape(tablegen_opaque_val);
}
template<typename ConcreteOp>
int64_t detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getStaticSizeInBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getStaticSizeInBits(tablegen_opaque_val);
}
template<typename ConcreteOp>
::std::optional<::circt::hls_analysis::StorageKind> detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPragmaStorageKind(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPragmaStorageKind(tablegen_opaque_val);
}
template<typename ConcreteOp>
::std::optional<::circt::hls_analysis::PartitionSpec> detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getPartitionSpec(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getPartitionSpec(tablegen_opaque_val);
}
template<typename ConcreteOp>
bool detail::MemoryResourceOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::contributesToBRAMCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->contributesToBRAMCost(tablegen_opaque_val);
}

} // namespace circt::hls_analysis
