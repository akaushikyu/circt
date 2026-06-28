/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns whether the specified type is a valid content type, e.g., if this
/// type is an integer register it is a handle to a bit-vector stored in that
/// register, thus an immediate of the width of the register is a valid
/// content type.
bool circt::rtg::ValidationTypeInterface::isValidContentType(mlir::Type contentType) const {
      return getImpl()->isValidContentType(getImpl(), *this, contentType);
  }

/// Parses the given string as a value of the given content type and returns
/// an Attribute representing the value for that type. A null attribute may be
/// returned if the string cannot be parsed as a value of the given type.
mlir::TypedAttr circt::rtg::ValidationTypeInterface::parseContentValue(mlir::StringRef valueString, mlir::Type contentType) const {
      return getImpl()->parseContentValue(getImpl(), *this, valueString, contentType);
  }

/// Returns the name of the intrinsic label that the desired simulator
/// understands to print the content of this ref value annotated with the
/// given ID. The 'value' attribute represents the concrete value, e.g., the
/// exact register to print the content of instead of. Note: this might be
/// generalized to an SSA value argument in the future if needed.
std::string circt::rtg::ValidationTypeInterface::getIntrinsicLabel(mlir::Attribute value, mlir::StringRef id) const {
      return getImpl()->getIntrinsicLabel(getImpl(), *this, value, id);
  }
