/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Element type of the underlying storage.
::mlir::Type circt::hls_analysis::MemoryResourceOpInterface::getElementType() {
      return getImpl()->getElementType(getImpl(), getOperation());
  }

/// Static shape; empty if dynamic.
::llvm::SmallVector<int64_t> circt::hls_analysis::MemoryResourceOpInterface::getStaticShape() {
      return getImpl()->getStaticShape(getImpl(), getOperation());
  }

/// Total static size in bits.
int64_t circt::hls_analysis::MemoryResourceOpInterface::getStaticSizeInBits() {
      return getImpl()->getStaticSizeInBits(getImpl(), getOperation());
  }

/// Pragma-requested storage kind, if any.
::std::optional<::circt::hls_analysis::StorageKind> circt::hls_analysis::MemoryResourceOpInterface::getPragmaStorageKind() {
      return getImpl()->getPragmaStorageKind(getImpl(), getOperation());
  }

/// Partitioning spec from array_partition pragma.
::std::optional<::circt::hls_analysis::PartitionSpec> circt::hls_analysis::MemoryResourceOpInterface::getPartitionSpec() {
      return getImpl()->getPartitionSpec(getImpl(), getOperation());
  }

/// True if this op participates in cost accounting.
bool circt::hls_analysis::MemoryResourceOpInterface::contributesToBRAMCost() {
      return getImpl()->contributesToBRAMCost(getImpl(), getOperation());
  }
