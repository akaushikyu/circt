/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the attribute's type
::mlir::Type circt::rtg::ContextResourceAttrInterface::getType() const {
      return getImpl()->implTypedAttr->getType(getImpl()->implTypedAttr, *this);
  }
