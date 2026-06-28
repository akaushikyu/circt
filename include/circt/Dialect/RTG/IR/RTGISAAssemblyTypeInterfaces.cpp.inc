/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns the number of registers in the class. Class indices are assumed
/// to be a continuous range from 0 
unsigned circt::rtg::RegisterTypeInterface::getRegisterClassSize() const {
      return getImpl()->getRegisterClassSize();
  }

/// Returns the register attribute for the given class-specific index.
/// Returns nullptr if the index is out of range.
::circt::rtg::RegisterAttrInterface circt::rtg::RegisterTypeInterface::getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index) const {
      return getImpl()->getRegisterAttrForClassIndex(ctx, index);
  }
