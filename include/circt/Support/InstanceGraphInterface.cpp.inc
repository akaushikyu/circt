/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the name of the instance
::llvm::StringRef circt::igraph::InstanceOpInterface::getInstanceName() {
      return getImpl()->getInstanceName(getImpl(), getOperation());
  }

/// Get the name of the instance
::mlir::StringAttr circt::igraph::InstanceOpInterface::getInstanceNameAttr() {
      return getImpl()->getInstanceNameAttr(getImpl(), getOperation());
  }

/// Get the name of all the possibly instantiated modules
::llvm::SmallVector<::llvm::StringRef, 1> circt::igraph::InstanceOpInterface::getReferencedModuleNames() {
      return getImpl()->getReferencedModuleNames(getImpl(), getOperation());
  }

/// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
::mlir::ArrayAttr circt::igraph::InstanceOpInterface::getReferencedModuleNamesAttr() {
      return getImpl()->getReferencedModuleNamesAttr(getImpl(), getOperation());
  }

/// Get the module name
::llvm::StringRef circt::igraph::ModuleOpInterface::getModuleName() {
      return getImpl()->getModuleName(getImpl(), getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::igraph::ModuleOpInterface::getModuleNameAttr() {
      return getImpl()->getModuleNameAttr(getImpl(), getOperation());
  }
