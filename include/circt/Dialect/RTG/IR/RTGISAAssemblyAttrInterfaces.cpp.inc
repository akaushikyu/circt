/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns the class specific index of the register. This translates from
/// the flat internal representation to the architectural representation.
unsigned circt::rtg::RegisterAttrInterface::getClassIndex() const {
      return getImpl()->getClassIndex(getImpl(), *this);
  }

/// Returns a suitable string for use in assembly format.
llvm::StringLiteral circt::rtg::RegisterAttrInterface::getRegisterAssembly() const {
      return getImpl()->getRegisterAssembly(getImpl(), *this);
  }

/// Get the attribute's type
::mlir::Type circt::rtg::RegisterAttrInterface::getType() const {
      return getImpl()->implTypedAttr->getType(getImpl()->implTypedAttr, *this);
  }
