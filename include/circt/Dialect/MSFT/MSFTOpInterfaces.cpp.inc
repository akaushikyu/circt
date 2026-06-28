/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the top module op to which this op is providing data for.
Operation *circt::msft::DynInstDataOpInterface::getTopModule(circt::hw::HWSymbolCache & symCache) {
      return getImpl()->getTopModule(getImpl(), getOperation(), symCache);
  }

/// Set the HierPathOp to which this op is referring.
void circt::msft::UnaryDynInstDataOpInterface::setPathOp(::circt::hw::HierPathOp ref) {
      return getImpl()->setPathOp(getImpl(), getOperation(), ref);
  }

/// Get the symbol of the HierPathOp to which this op is referring.
FlatSymbolRefAttr circt::msft::UnaryDynInstDataOpInterface::getPathSym() {
      return getImpl()->getPathSym(getImpl(), getOperation());
  }

/// Get the top module op to which this op is providing data for.
Operation *circt::msft::UnaryDynInstDataOpInterface::getTopModule(circt::hw::HWSymbolCache & symCache) {
      return getImpl()->implDynInstDataOpInterface->getTopModule(getImpl()->implDynInstDataOpInterface, getOperation(), symCache);
  }
