/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns the result types of this block from the point of view of inside the block
llvm::SmallVector<Type> circt::kanagawa::BlockOpInterface::getInternalResultTypes() {
      return getImpl()->getInternalResultTypes(getImpl(), getOperation());
  }

/// Returns the type of the method.
::mlir::FunctionType circt::kanagawa::MethodLikeOpInterface::getFunctionType() {
      return getImpl()->getFunctionType(getImpl(), getOperation());
  }

/// Returns the name of the method.
::mlir::StringAttr circt::kanagawa::MethodLikeOpInterface::getMethodName() {
      return getImpl()->getMethodName(getImpl(), getOperation());
  }

/// Returns the namehint attribute of this op
mlir::StringAttr circt::kanagawa::NamedInnerSymbolInterface::getNameHintAttr() {
      return getImpl()->getNameHintAttr(getImpl(), getOperation());
  }

/// Returns the namehint of this op
llvm::StringRef circt::kanagawa::NamedInnerSymbolInterface::getNameHint() {
      return getImpl()->getNameHint(getImpl(), getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::mlir::StringAttr circt::kanagawa::NamedInnerSymbolInterface::getInnerNameAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerNameAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::std::optional<::mlir::StringRef> circt::kanagawa::NamedInnerSymbolInterface::getInnerName() {
      return getImpl()->implInnerSymbolOpInterface->getInnerName(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
void circt::kanagawa::NamedInnerSymbolInterface::setInnerSymbol(::mlir::StringAttr name) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbol(getImpl()->implInnerSymbolOpInterface, getOperation(), name);
  }

/// Sets the inner symbols defined by this operation.
void circt::kanagawa::NamedInnerSymbolInterface::setInnerSymbolAttr(::circt::hw::InnerSymAttr sym) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbolAttr(getImpl()->implInnerSymbolOpInterface, getOperation(), sym);
  }

/// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
::circt::hw::InnerRefAttr circt::kanagawa::NamedInnerSymbolInterface::getInnerRef() {
      return getImpl()->implInnerSymbolOpInterface->getInnerRef(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the InnerSymAttr representing all inner symbols defined by this operation.
::circt::hw::InnerSymAttr circt::kanagawa::NamedInnerSymbolInterface::getInnerSymAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerSymAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns whether per-field symbols are supported for this operation type.
bool circt::kanagawa::NamedInnerSymbolInterface::supportsPerFieldSymbols() {
      return getImpl()->implInnerSymbolOpInterface->supportsPerFieldSymbols();
  }

/// Returns the index of the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
std::optional<size_t> circt::kanagawa::NamedInnerSymbolInterface::getTargetResultIndex() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResultIndex();
  }

/// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
OpResult circt::kanagawa::NamedInnerSymbolInterface::getTargetResult() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResult(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the data type of the port.
mlir::Type circt::kanagawa::PortOpInterface::getPortType() {
      return getImpl()->getPortType(getImpl(), getOperation());
  }

/// Returns the `!kanagawa.portref` value defined by the op
mlir::TypedValue<PortRefType> circt::kanagawa::PortOpInterface::getPort() {
      return getImpl()->getPort(getImpl(), getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::mlir::StringAttr circt::kanagawa::PortOpInterface::getInnerNameAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerNameAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::std::optional<::mlir::StringRef> circt::kanagawa::PortOpInterface::getInnerName() {
      return getImpl()->implInnerSymbolOpInterface->getInnerName(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
void circt::kanagawa::PortOpInterface::setInnerSymbol(::mlir::StringAttr name) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbol(getImpl()->implInnerSymbolOpInterface, getOperation(), name);
  }

/// Sets the inner symbols defined by this operation.
void circt::kanagawa::PortOpInterface::setInnerSymbolAttr(::circt::hw::InnerSymAttr sym) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbolAttr(getImpl()->implInnerSymbolOpInterface, getOperation(), sym);
  }

/// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
::circt::hw::InnerRefAttr circt::kanagawa::PortOpInterface::getInnerRef() {
      return getImpl()->implInnerSymbolOpInterface->getInnerRef(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the InnerSymAttr representing all inner symbols defined by this operation.
::circt::hw::InnerSymAttr circt::kanagawa::PortOpInterface::getInnerSymAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerSymAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns whether per-field symbols are supported for this operation type.
bool circt::kanagawa::PortOpInterface::supportsPerFieldSymbols() {
      return getImpl()->implInnerSymbolOpInterface->supportsPerFieldSymbols();
  }

/// Returns the index of the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
std::optional<size_t> circt::kanagawa::PortOpInterface::getTargetResultIndex() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResultIndex();
  }

/// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
OpResult circt::kanagawa::PortOpInterface::getTargetResult() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResult(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the namehint attribute of this op
mlir::StringAttr circt::kanagawa::PortOpInterface::getNameHintAttr() {
      return getImpl()->implNamedInnerSymbolInterface->getNameHintAttr(getImpl()->implNamedInnerSymbolInterface, getOperation());
  }

/// Returns the namehint of this op
llvm::StringRef circt::kanagawa::PortOpInterface::getNameHint() {
      return getImpl()->implNamedInnerSymbolInterface->getNameHint(getImpl()->implNamedInnerSymbolInterface, getOperation());
  }

/// Returns the body of the scope
mlir::Block*circt::kanagawa::ScopeOpInterface::getBodyBlock() {
      return getImpl()->getBodyBlock(getImpl(), getOperation());
  }

/// Returns the symbol name of the scope
mlir::StringAttr circt::kanagawa::ScopeOpInterface::getScopeName() {
      return getImpl()->getScopeName(getImpl(), getOperation());
  }

/// Lookup an inner symbol in the scope
Operation*circt::kanagawa::ScopeOpInterface::lookupInnerSym(llvm::StringRef symName) {
      return getImpl()->lookupInnerSym(getImpl(), getOperation(), symName);
  }

/// Lookup a port in the scope
kanagawa::PortOpInterface circt::kanagawa::ScopeOpInterface::lookupPort(llvm::StringRef portName) {
      return getImpl()->lookupPort(getImpl(), getOperation(), portName);
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::mlir::StringAttr circt::kanagawa::ScopeOpInterface::getInnerNameAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerNameAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::std::optional<::mlir::StringRef> circt::kanagawa::ScopeOpInterface::getInnerName() {
      return getImpl()->implInnerSymbolOpInterface->getInnerName(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
void circt::kanagawa::ScopeOpInterface::setInnerSymbol(::mlir::StringAttr name) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbol(getImpl()->implInnerSymbolOpInterface, getOperation(), name);
  }

/// Sets the inner symbols defined by this operation.
void circt::kanagawa::ScopeOpInterface::setInnerSymbolAttr(::circt::hw::InnerSymAttr sym) {
      return getImpl()->implInnerSymbolOpInterface->setInnerSymbolAttr(getImpl()->implInnerSymbolOpInterface, getOperation(), sym);
  }

/// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
::circt::hw::InnerRefAttr circt::kanagawa::ScopeOpInterface::getInnerRef() {
      return getImpl()->implInnerSymbolOpInterface->getInnerRef(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the InnerSymAttr representing all inner symbols defined by this operation.
::circt::hw::InnerSymAttr circt::kanagawa::ScopeOpInterface::getInnerSymAttr() {
      return getImpl()->implInnerSymbolOpInterface->getInnerSymAttr(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns whether per-field symbols are supported for this operation type.
bool circt::kanagawa::ScopeOpInterface::supportsPerFieldSymbols() {
      return getImpl()->implInnerSymbolOpInterface->supportsPerFieldSymbols();
  }

/// Returns the index of the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
std::optional<size_t> circt::kanagawa::ScopeOpInterface::getTargetResultIndex() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResultIndex();
  }

/// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
OpResult circt::kanagawa::ScopeOpInterface::getTargetResult() {
      return getImpl()->implInnerSymbolOpInterface->getTargetResult(getImpl()->implInnerSymbolOpInterface, getOperation());
  }

/// Returns the namehint attribute of this op
mlir::StringAttr circt::kanagawa::ScopeOpInterface::getNameHintAttr() {
      return getImpl()->implNamedInnerSymbolInterface->getNameHintAttr(getImpl()->implNamedInnerSymbolInterface, getOperation());
  }

/// Returns the namehint of this op
llvm::StringRef circt::kanagawa::ScopeOpInterface::getNameHint() {
      return getImpl()->implNamedInnerSymbolInterface->getNameHint(getImpl()->implNamedInnerSymbolInterface, getOperation());
  }
