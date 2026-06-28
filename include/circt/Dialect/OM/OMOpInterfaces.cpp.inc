/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the lhs Value
mlir::Value circt::om::BinaryEqualityOp::getLhs() {
      return getImpl()->getLhs(getImpl(), getOperation());
  }

/// Get the rhs Value
mlir::Value circt::om::BinaryEqualityOp::getRhs() {
      return getImpl()->getRhs(getImpl(), getOperation());
  }

/// Get the result Value
mlir::Value circt::om::BinaryEqualityOp::getResult() {
      return getImpl()->getResult(getImpl(), getOperation());
  }

/// Evaluate the binary equality operation
mlir::FailureOr<mlir::Attribute> circt::om::BinaryEqualityOp::evaluateBinaryEquality(mlir::Attribute lhs, mlir::Attribute rhs) {
      return getImpl()->evaluateBinaryEquality(getImpl(), getOperation(), lhs, rhs);
  }

/// Get the class-like symbol name
llvm::StringRef circt::om::ClassLike::getSymName() {
      return getImpl()->getSymName(getImpl(), getOperation());
  }

/// Get the class-like symbol name attribute
mlir::StringAttr circt::om::ClassLike::getSymNameAttr() {
      return getImpl()->getSymNameAttr(getImpl(), getOperation());
  }

/// Get the class-like symbol name attribute name
mlir::StringAttr circt::om::ClassLike::getSymNameAttrName() {
      return getImpl()->getSymNameAttrName(getImpl(), getOperation());
  }

/// Get the class-like formal parameter names attribute
mlir::ArrayAttr circt::om::ClassLike::getFormalParamNames() {
      return getImpl()->getFormalParamNames(getImpl(), getOperation());
  }

/// Get the class-like formal parameter names attribute name
mlir::StringAttr circt::om::ClassLike::getFormalParamNamesAttrName() {
      return getImpl()->getFormalParamNamesAttrName(getImpl(), getOperation());
  }

/// Get the class-like dictionary mapping field names to type
mlir::DictionaryAttr circt::om::ClassLike::getFieldTypes() {
      return getImpl()->getFieldTypes(getImpl(), getOperation());
  }

/// Get the class-like body region
mlir::Region &circt::om::ClassLike::getBody() {
      return getImpl()->getBody(getImpl(), getOperation());
  }

/// Get the class-like body block
mlir::Block *circt::om::ClassLike::getBodyBlock() {
      return getImpl()->getBodyBlock(getImpl(), getOperation());
  }

/// Get the class-like field type
std::optional<mlir::Type> circt::om::ClassLike::getFieldType(mlir::StringAttr field) {
      return getImpl()->getFieldType(getImpl(), getOperation(), field);
  }

/// Get the class-like field names
mlir::ArrayAttr circt::om::ClassLike::getFieldNames() {
      return getImpl()->getFieldNames(getImpl(), getOperation());
  }

/// Replace field types dictionary attr
void circt::om::ClassLike::replaceFieldTypes(mlir::AttrTypeReplacer replacer) {
      return getImpl()->replaceFieldTypes(getImpl(), getOperation(), replacer);
  }

/// Get the lhs Value
mlir::Value circt::om::IntegerBinaryOp::getLhs() {
      return getImpl()->getLhs(getImpl(), getOperation());
  }

/// Get the rhs Value
mlir::Value circt::om::IntegerBinaryOp::getRhs() {
      return getImpl()->getRhs(getImpl(), getOperation());
  }

/// Get the result Value
mlir::Value circt::om::IntegerBinaryOp::getResult() {
      return getImpl()->getResult(getImpl(), getOperation());
  }

/// Evaluate the integer binary operation
mlir::FailureOr<llvm::APSInt> circt::om::IntegerBinaryOp::evaluateIntegerOperation(const llvm::APSInt & lhs, const llvm::APSInt & rhs) {
      return getImpl()->evaluateIntegerOperation(getImpl(), getOperation(), lhs, rhs);
  }
