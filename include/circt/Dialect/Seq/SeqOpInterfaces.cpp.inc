/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the clock signal
mlir::Value circt::seq::Clocked::getClk() {
      return getImpl()->getClk(getImpl(), getOperation());
  }

/// Get the reset signal
mlir::Value circt::seq::Resettable::getReset() {
      return getImpl()->getReset(getImpl(), getOperation());
  }

/// Get the reset value
mlir::Value circt::seq::Resettable::getResetValue() {
      return getImpl()->getResetValue(getImpl(), getOperation());
  }
