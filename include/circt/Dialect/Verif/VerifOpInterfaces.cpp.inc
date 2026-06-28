/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the label
std::optional<llvm::StringRef> circt::verif::RequireLike::getLabel() {
      return getImpl()->getLabel(getImpl(), getOperation());
  }

/// Get the label attribute
mlir::StringAttr circt::verif::RequireLike::getLabelAttr() {
      return getImpl()->getLabelAttr(getImpl(), getOperation());
  }

/// Get the property
mlir::Value circt::verif::RequireLike::getProperty() {
      return getImpl()->getProperty(getImpl(), getOperation());
  }

/// Get the enable
mlir::Value circt::verif::RequireLike::getEnable() {
      return getImpl()->getEnable(getImpl(), getOperation());
  }
