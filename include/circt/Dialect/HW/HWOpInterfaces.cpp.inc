/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the combinational dataflow relations between the operands and the results.
/// This returns a pair of ground type fieldrefs. The first element is the destination
/// and the second is the source of the dependence. The default implementation returns
/// an empty list, which implies that the operation is not combinational.
llvm::SmallVector<std::pair<circt::FieldRef, circt::FieldRef>> circt::hw::CombDataFlow::computeDataFlow() {
      return getImpl()->computeDataFlow(getImpl(), getOperation());
  }

/// Returns the name of this symbol.
::mlir::StringAttr circt::hw::HWEmittableModuleLike::getNameAttr() {
      return getImpl()->implSymbolOpInterface->getNameAttr(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the name of this symbol.
void circt::hw::HWEmittableModuleLike::setName(::mlir::StringAttr name) {
      return getImpl()->implSymbolOpInterface->setName(getImpl()->implSymbolOpInterface, getOperation(), name);
  }

/// Gets the visibility of this symbol.
mlir::SymbolTable::Visibility circt::hw::HWEmittableModuleLike::getVisibility() {
      return getImpl()->implSymbolOpInterface->getVisibility(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has nested visibility.
bool circt::hw::HWEmittableModuleLike::isNested() {
      return getImpl()->implSymbolOpInterface->isNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has private visibility.
bool circt::hw::HWEmittableModuleLike::isPrivate() {
      return getImpl()->implSymbolOpInterface->isPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has public visibility.
bool circt::hw::HWEmittableModuleLike::isPublic() {
      return getImpl()->implSymbolOpInterface->isPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol.
void circt::hw::HWEmittableModuleLike::setVisibility(mlir::SymbolTable::Visibility vis) {
      return getImpl()->implSymbolOpInterface->setVisibility(getImpl()->implSymbolOpInterface, getOperation(), vis);
  }

/// Sets the visibility of this symbol to be nested.
void circt::hw::HWEmittableModuleLike::setNested() {
      return getImpl()->implSymbolOpInterface->setNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be private.
void circt::hw::HWEmittableModuleLike::setPrivate() {
      return getImpl()->implSymbolOpInterface->setPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be public.
void circt::hw::HWEmittableModuleLike::setPublic() {
      return getImpl()->implSymbolOpInterface->setPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get all of the uses of the current symbol that are nested within the
/// given operation 'from'.
/// Note: See mlir::SymbolTable::getSymbolUses for more details.
::std::optional<::mlir::SymbolTable::UseRange> circt::hw::HWEmittableModuleLike::getSymbolUses(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->getSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Return if the current symbol is known to have no uses that are nested
/// within the given operation 'from'.
/// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
bool circt::hw::HWEmittableModuleLike::symbolKnownUseEmpty(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->symbolKnownUseEmpty(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Attempt to replace all uses of the current symbol with the provided
/// symbol 'newSymbol' that are nested within the given operation 'from'.
/// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
::llvm::LogicalResult circt::hw::HWEmittableModuleLike::replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->replaceAllSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), newSymbol, from);
  }

/// Returns true if this operation optionally defines a symbol based on the
/// presence of the symbol name.
bool circt::hw::HWEmittableModuleLike::isOptionalSymbol() {
      return getImpl()->implSymbolOpInterface->isOptionalSymbol(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation can be discarded if it has no remaining
/// symbol uses.
bool circt::hw::HWEmittableModuleLike::canDiscardOnUseEmpty() {
      return getImpl()->implSymbolOpInterface->canDiscardOnUseEmpty(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation is a declaration of a symbol (as opposed
/// to a definition).
bool circt::hw::HWEmittableModuleLike::isDeclaration() {
      return getImpl()->implSymbolOpInterface->isDeclaration(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::hw::HWEmittableModuleLike::getPortList() {
      return getImpl()->implPortList->getPortList(getImpl()->implPortList, getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::hw::HWEmittableModuleLike::getPort(size_t idx) {
      return getImpl()->implPortList->getPort(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::hw::HWEmittableModuleLike::getPortIdForInputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForInputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::hw::HWEmittableModuleLike::getPortIdForOutputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForOutputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the number of ports
size_t circt::hw::HWEmittableModuleLike::getNumPorts() {
      return getImpl()->implPortList->getNumPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of input ports
size_t circt::hw::HWEmittableModuleLike::getNumInputPorts() {
      return getImpl()->implPortList->getNumInputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of output ports
size_t circt::hw::HWEmittableModuleLike::getNumOutputPorts() {
      return getImpl()->implPortList->getNumOutputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the module name
::llvm::StringRef circt::hw::HWEmittableModuleLike::getModuleName() {
      return getImpl()->implModuleOpInterface->getModuleName(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::hw::HWEmittableModuleLike::getModuleNameAttr() {
      return getImpl()->implModuleOpInterface->getModuleNameAttr(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module type
::circt::hw::ModuleType circt::hw::HWEmittableModuleLike::getHWModuleType() {
      return getImpl()->implHWModuleLike->getHWModuleType(getImpl()->implHWModuleLike, getOperation());
  }

/// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
ArrayRef<Attribute> circt::hw::HWEmittableModuleLike::getAllPortAttrs() {
      return getImpl()->implHWModuleLike->getAllPortAttrs(getImpl()->implHWModuleLike, getOperation());
  }

/// Set the port Attributes
void circt::hw::HWEmittableModuleLike::setAllPortAttrs(ArrayRef<Attribute> attrs) {
      return getImpl()->implHWModuleLike->setAllPortAttrs(getImpl()->implHWModuleLike, getOperation(), attrs);
  }

/// Remove the port Attributes
void circt::hw::HWEmittableModuleLike::removeAllPortAttrs() {
      return getImpl()->implHWModuleLike->removeAllPortAttrs(getImpl()->implHWModuleLike, getOperation());
  }

/// Get the port Locations
SmallVector<Location> circt::hw::HWEmittableModuleLike::getAllPortLocs() {
      return getImpl()->implHWModuleLike->getAllPortLocs(getImpl()->implHWModuleLike, getOperation());
  }

/// Set the port Locations
void circt::hw::HWEmittableModuleLike::setAllPortLocsAttrs(ArrayRef<Attribute> locs) {
      return getImpl()->implHWModuleLike->setAllPortLocsAttrs(getImpl()->implHWModuleLike, getOperation(), locs);
  }

/// Set the module type (and port names)
void circt::hw::HWEmittableModuleLike::setHWModuleType(::circt::hw::ModuleType type) {
      return getImpl()->implHWModuleLike->setHWModuleType(getImpl()->implHWModuleLike, getOperation(), type);
  }

/// Set the port names
void circt::hw::HWEmittableModuleLike::setAllPortNames(ArrayRef<Attribute> names) {
      return getImpl()->implHWModuleLike->setAllPortNames(getImpl()->implHWModuleLike, getOperation(), names);
  }

/// Return the name of the specified input port or null if it cannot be
/// determined.
::mlir::StringAttr circt::hw::HWInstanceLike::getInputName(size_t idx) {
      return getImpl()->getInputName(getImpl(), getOperation(), idx);
  }

/// Return the name of the specified result or null if it cannot be
/// determined.
::mlir::StringAttr circt::hw::HWInstanceLike::getOutputName(size_t idx) {
      return getImpl()->getOutputName(getImpl(), getOperation(), idx);
  }

/// Change the name of the specified input port.
void circt::hw::HWInstanceLike::setInputName(size_t idx, ::mlir::StringAttr name) {
      return getImpl()->setInputName(getImpl(), getOperation(), idx, name);
  }

/// Change the name of the specified output port.
void circt::hw::HWInstanceLike::setOutputName(size_t idx, ::mlir::StringAttr name) {
      return getImpl()->setOutputName(getImpl(), getOperation(), idx, name);
  }

/// Return the names of all input ports. If the instance operation stores the
/// names in an ArrayAttr this can avoid attribute constructions.
::mlir::ArrayAttr circt::hw::HWInstanceLike::getInputNames() {
      return getImpl()->getInputNames(getImpl(), getOperation());
  }

/// Return the name of all ouput ports. If the instance operation stores the
/// names in an ArrayAttr this can avoid attribute constructions.
::mlir::ArrayAttr circt::hw::HWInstanceLike::getOutputNames() {
      return getImpl()->getOutputNames(getImpl(), getOperation());
  }

/// Change the names of all input ports. If all names have to be changed, this
/// can avoid repeated intermediate attribute constructions.
void circt::hw::HWInstanceLike::setInputNames(::mlir::ArrayAttr names) {
      return getImpl()->setInputNames(getImpl(), getOperation(), names);
  }

/// Change the names of all output ports. If all names have to be changed, this
/// can avoid repeated intermediate attribute constructions.
void circt::hw::HWInstanceLike::setOutputNames(::mlir::ArrayAttr names) {
      return getImpl()->setOutputNames(getImpl(), getOperation(), names);
  }

/// True if this instance is a phony placeholder
bool circt::hw::HWInstanceLike::getDoNotPrint() {
      return getImpl()->getDoNotPrint(getImpl(), getOperation());
  }

/// Get the name of the instance
::llvm::StringRef circt::hw::HWInstanceLike::getInstanceName() {
      return getImpl()->implInstanceOpInterface->getInstanceName(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the name of the instance
::mlir::StringAttr circt::hw::HWInstanceLike::getInstanceNameAttr() {
      return getImpl()->implInstanceOpInterface->getInstanceNameAttr(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the name of all the possibly instantiated modules
::llvm::SmallVector<::llvm::StringRef, 1> circt::hw::HWInstanceLike::getReferencedModuleNames() {
      return getImpl()->implInstanceOpInterface->getReferencedModuleNames(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
::mlir::ArrayAttr circt::hw::HWInstanceLike::getReferencedModuleNamesAttr() {
      return getImpl()->implInstanceOpInterface->getReferencedModuleNamesAttr(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the module type
::circt::hw::ModuleType circt::hw::HWModuleLike::getHWModuleType() {
      return getImpl()->getHWModuleType(getImpl(), getOperation());
  }

/// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
ArrayRef<Attribute> circt::hw::HWModuleLike::getAllPortAttrs() {
      return getImpl()->getAllPortAttrs(getImpl(), getOperation());
  }

/// Set the port Attributes
void circt::hw::HWModuleLike::setAllPortAttrs(ArrayRef<Attribute> attrs) {
      return getImpl()->setAllPortAttrs(getImpl(), getOperation(), attrs);
  }

/// Remove the port Attributes
void circt::hw::HWModuleLike::removeAllPortAttrs() {
      return getImpl()->removeAllPortAttrs(getImpl(), getOperation());
  }

/// Get the port Locations
SmallVector<Location> circt::hw::HWModuleLike::getAllPortLocs() {
      return getImpl()->getAllPortLocs(getImpl(), getOperation());
  }

/// Set the port Locations
void circt::hw::HWModuleLike::setAllPortLocsAttrs(ArrayRef<Attribute> locs) {
      return getImpl()->setAllPortLocsAttrs(getImpl(), getOperation(), locs);
  }

/// Set the module type (and port names)
void circt::hw::HWModuleLike::setHWModuleType(::circt::hw::ModuleType type) {
      return getImpl()->setHWModuleType(getImpl(), getOperation(), type);
  }

/// Set the port names
void circt::hw::HWModuleLike::setAllPortNames(ArrayRef<Attribute> names) {
      return getImpl()->setAllPortNames(getImpl(), getOperation(), names);
  }

/// Returns the name of this symbol.
::mlir::StringAttr circt::hw::HWModuleLike::getNameAttr() {
      return getImpl()->implSymbolOpInterface->getNameAttr(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the name of this symbol.
void circt::hw::HWModuleLike::setName(::mlir::StringAttr name) {
      return getImpl()->implSymbolOpInterface->setName(getImpl()->implSymbolOpInterface, getOperation(), name);
  }

/// Gets the visibility of this symbol.
mlir::SymbolTable::Visibility circt::hw::HWModuleLike::getVisibility() {
      return getImpl()->implSymbolOpInterface->getVisibility(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has nested visibility.
bool circt::hw::HWModuleLike::isNested() {
      return getImpl()->implSymbolOpInterface->isNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has private visibility.
bool circt::hw::HWModuleLike::isPrivate() {
      return getImpl()->implSymbolOpInterface->isPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has public visibility.
bool circt::hw::HWModuleLike::isPublic() {
      return getImpl()->implSymbolOpInterface->isPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol.
void circt::hw::HWModuleLike::setVisibility(mlir::SymbolTable::Visibility vis) {
      return getImpl()->implSymbolOpInterface->setVisibility(getImpl()->implSymbolOpInterface, getOperation(), vis);
  }

/// Sets the visibility of this symbol to be nested.
void circt::hw::HWModuleLike::setNested() {
      return getImpl()->implSymbolOpInterface->setNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be private.
void circt::hw::HWModuleLike::setPrivate() {
      return getImpl()->implSymbolOpInterface->setPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be public.
void circt::hw::HWModuleLike::setPublic() {
      return getImpl()->implSymbolOpInterface->setPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get all of the uses of the current symbol that are nested within the
/// given operation 'from'.
/// Note: See mlir::SymbolTable::getSymbolUses for more details.
::std::optional<::mlir::SymbolTable::UseRange> circt::hw::HWModuleLike::getSymbolUses(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->getSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Return if the current symbol is known to have no uses that are nested
/// within the given operation 'from'.
/// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
bool circt::hw::HWModuleLike::symbolKnownUseEmpty(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->symbolKnownUseEmpty(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Attempt to replace all uses of the current symbol with the provided
/// symbol 'newSymbol' that are nested within the given operation 'from'.
/// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
::llvm::LogicalResult circt::hw::HWModuleLike::replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->replaceAllSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), newSymbol, from);
  }

/// Returns true if this operation optionally defines a symbol based on the
/// presence of the symbol name.
bool circt::hw::HWModuleLike::isOptionalSymbol() {
      return getImpl()->implSymbolOpInterface->isOptionalSymbol(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation can be discarded if it has no remaining
/// symbol uses.
bool circt::hw::HWModuleLike::canDiscardOnUseEmpty() {
      return getImpl()->implSymbolOpInterface->canDiscardOnUseEmpty(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation is a declaration of a symbol (as opposed
/// to a definition).
bool circt::hw::HWModuleLike::isDeclaration() {
      return getImpl()->implSymbolOpInterface->isDeclaration(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::hw::HWModuleLike::getPortList() {
      return getImpl()->implPortList->getPortList(getImpl()->implPortList, getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::hw::HWModuleLike::getPort(size_t idx) {
      return getImpl()->implPortList->getPort(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::hw::HWModuleLike::getPortIdForInputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForInputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::hw::HWModuleLike::getPortIdForOutputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForOutputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the number of ports
size_t circt::hw::HWModuleLike::getNumPorts() {
      return getImpl()->implPortList->getNumPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of input ports
size_t circt::hw::HWModuleLike::getNumInputPorts() {
      return getImpl()->implPortList->getNumInputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of output ports
size_t circt::hw::HWModuleLike::getNumOutputPorts() {
      return getImpl()->implPortList->getNumOutputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the module name
::llvm::StringRef circt::hw::HWModuleLike::getModuleName() {
      return getImpl()->implModuleOpInterface->getModuleName(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::hw::HWModuleLike::getModuleNameAttr() {
      return getImpl()->implModuleOpInterface->getModuleNameAttr(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get a handle to a utility class which provides by-name lookup of port indices. The returned object does _not_ update if the module is mutated.
::circt::hw::ModulePortLookupInfo circt::hw::HWMutableModuleLike::getPortLookupInfo() {
      return getImpl()->getPortLookupInfo(getImpl(), getOperation());
  }

/// Insert and remove input and output ports
void circt::hw::HWMutableModuleLike::modifyPorts(ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs, ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
      return getImpl()->modifyPorts(getImpl(), getOperation(), insertInputs, insertOutputs, eraseInputs, eraseOutputs);
  }

/// Insert ports into this module
void circt::hw::HWMutableModuleLike::insertPorts(ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertInputs, ArrayRef<std::pair<unsigned, circt::hw::PortInfo>> insertOutputs) {
      return getImpl()->insertPorts(getImpl(), getOperation(), insertInputs, insertOutputs);
  }

/// Erase ports from this module
void circt::hw::HWMutableModuleLike::erasePorts(ArrayRef<unsigned> eraseInputs, ArrayRef<unsigned> eraseOutputs) {
      return getImpl()->erasePorts(getImpl(), getOperation(), eraseInputs, eraseOutputs);
  }

/// Append output values to this module
void circt::hw::HWMutableModuleLike::appendOutputs(ArrayRef<std::pair<StringAttr, Value>> outputs) {
      return getImpl()->appendOutputs(getImpl(), getOperation(), outputs);
  }

/// Returns the name of this symbol.
::mlir::StringAttr circt::hw::HWMutableModuleLike::getNameAttr() {
      return getImpl()->implSymbolOpInterface->getNameAttr(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the name of this symbol.
void circt::hw::HWMutableModuleLike::setName(::mlir::StringAttr name) {
      return getImpl()->implSymbolOpInterface->setName(getImpl()->implSymbolOpInterface, getOperation(), name);
  }

/// Gets the visibility of this symbol.
mlir::SymbolTable::Visibility circt::hw::HWMutableModuleLike::getVisibility() {
      return getImpl()->implSymbolOpInterface->getVisibility(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has nested visibility.
bool circt::hw::HWMutableModuleLike::isNested() {
      return getImpl()->implSymbolOpInterface->isNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has private visibility.
bool circt::hw::HWMutableModuleLike::isPrivate() {
      return getImpl()->implSymbolOpInterface->isPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has public visibility.
bool circt::hw::HWMutableModuleLike::isPublic() {
      return getImpl()->implSymbolOpInterface->isPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol.
void circt::hw::HWMutableModuleLike::setVisibility(mlir::SymbolTable::Visibility vis) {
      return getImpl()->implSymbolOpInterface->setVisibility(getImpl()->implSymbolOpInterface, getOperation(), vis);
  }

/// Sets the visibility of this symbol to be nested.
void circt::hw::HWMutableModuleLike::setNested() {
      return getImpl()->implSymbolOpInterface->setNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be private.
void circt::hw::HWMutableModuleLike::setPrivate() {
      return getImpl()->implSymbolOpInterface->setPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be public.
void circt::hw::HWMutableModuleLike::setPublic() {
      return getImpl()->implSymbolOpInterface->setPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get all of the uses of the current symbol that are nested within the
/// given operation 'from'.
/// Note: See mlir::SymbolTable::getSymbolUses for more details.
::std::optional<::mlir::SymbolTable::UseRange> circt::hw::HWMutableModuleLike::getSymbolUses(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->getSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Return if the current symbol is known to have no uses that are nested
/// within the given operation 'from'.
/// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
bool circt::hw::HWMutableModuleLike::symbolKnownUseEmpty(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->symbolKnownUseEmpty(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Attempt to replace all uses of the current symbol with the provided
/// symbol 'newSymbol' that are nested within the given operation 'from'.
/// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
::llvm::LogicalResult circt::hw::HWMutableModuleLike::replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->replaceAllSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), newSymbol, from);
  }

/// Returns true if this operation optionally defines a symbol based on the
/// presence of the symbol name.
bool circt::hw::HWMutableModuleLike::isOptionalSymbol() {
      return getImpl()->implSymbolOpInterface->isOptionalSymbol(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation can be discarded if it has no remaining
/// symbol uses.
bool circt::hw::HWMutableModuleLike::canDiscardOnUseEmpty() {
      return getImpl()->implSymbolOpInterface->canDiscardOnUseEmpty(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation is a declaration of a symbol (as opposed
/// to a definition).
bool circt::hw::HWMutableModuleLike::isDeclaration() {
      return getImpl()->implSymbolOpInterface->isDeclaration(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::hw::HWMutableModuleLike::getPortList() {
      return getImpl()->implPortList->getPortList(getImpl()->implPortList, getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::hw::HWMutableModuleLike::getPort(size_t idx) {
      return getImpl()->implPortList->getPort(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::hw::HWMutableModuleLike::getPortIdForInputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForInputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::hw::HWMutableModuleLike::getPortIdForOutputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForOutputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the number of ports
size_t circt::hw::HWMutableModuleLike::getNumPorts() {
      return getImpl()->implPortList->getNumPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of input ports
size_t circt::hw::HWMutableModuleLike::getNumInputPorts() {
      return getImpl()->implPortList->getNumInputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of output ports
size_t circt::hw::HWMutableModuleLike::getNumOutputPorts() {
      return getImpl()->implPortList->getNumOutputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the module name
::llvm::StringRef circt::hw::HWMutableModuleLike::getModuleName() {
      return getImpl()->implModuleOpInterface->getModuleName(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::hw::HWMutableModuleLike::getModuleNameAttr() {
      return getImpl()->implModuleOpInterface->getModuleNameAttr(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module type
::circt::hw::ModuleType circt::hw::HWMutableModuleLike::getHWModuleType() {
      return getImpl()->implHWModuleLike->getHWModuleType(getImpl()->implHWModuleLike, getOperation());
  }

/// Get the port Attributes.  This will return either an empty array or an array of size numPorts.
ArrayRef<Attribute> circt::hw::HWMutableModuleLike::getAllPortAttrs() {
      return getImpl()->implHWModuleLike->getAllPortAttrs(getImpl()->implHWModuleLike, getOperation());
  }

/// Set the port Attributes
void circt::hw::HWMutableModuleLike::setAllPortAttrs(ArrayRef<Attribute> attrs) {
      return getImpl()->implHWModuleLike->setAllPortAttrs(getImpl()->implHWModuleLike, getOperation(), attrs);
  }

/// Remove the port Attributes
void circt::hw::HWMutableModuleLike::removeAllPortAttrs() {
      return getImpl()->implHWModuleLike->removeAllPortAttrs(getImpl()->implHWModuleLike, getOperation());
  }

/// Get the port Locations
SmallVector<Location> circt::hw::HWMutableModuleLike::getAllPortLocs() {
      return getImpl()->implHWModuleLike->getAllPortLocs(getImpl()->implHWModuleLike, getOperation());
  }

/// Set the port Locations
void circt::hw::HWMutableModuleLike::setAllPortLocsAttrs(ArrayRef<Attribute> locs) {
      return getImpl()->implHWModuleLike->setAllPortLocsAttrs(getImpl()->implHWModuleLike, getOperation(), locs);
  }

/// Set the module type (and port names)
void circt::hw::HWMutableModuleLike::setHWModuleType(::circt::hw::ModuleType type) {
      return getImpl()->implHWModuleLike->setHWModuleType(getImpl()->implHWModuleLike, getOperation(), type);
  }

/// Set the port names
void circt::hw::HWMutableModuleLike::setAllPortNames(ArrayRef<Attribute> names) {
      return getImpl()->implHWModuleLike->setAllPortNames(getImpl()->implHWModuleLike, getOperation(), names);
  }

/// Verify the inner ref uses held by this operation.
::mlir::LogicalResult circt::hw::InnerRefUserOpInterface::verifyInnerRefs(::circt::hw::InnerRefNamespace& ns) {
      return getImpl()->verifyInnerRefs(getImpl(), getOperation(), ns);
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::mlir::StringAttr circt::hw::InnerSymbolOpInterface::getInnerNameAttr() {
      return getImpl()->getInnerNameAttr(getImpl(), getOperation());
  }

/// Returns the name of the top-level inner symbol defined by this operation, if present.
::std::optional<::mlir::StringRef> circt::hw::InnerSymbolOpInterface::getInnerName() {
      return getImpl()->getInnerName(getImpl(), getOperation());
  }

/// Sets the name of the top-level inner symbol defined by this operation to the specified string, dropping any symbols on fields.
void circt::hw::InnerSymbolOpInterface::setInnerSymbol(::mlir::StringAttr name) {
      return getImpl()->setInnerSymbol(getImpl(), getOperation(), name);
  }

/// Sets the inner symbols defined by this operation.
void circt::hw::InnerSymbolOpInterface::setInnerSymbolAttr(::circt::hw::InnerSymAttr sym) {
      return getImpl()->setInnerSymbolAttr(getImpl(), getOperation(), sym);
  }

/// Returns an InnerRef to this operation's top-level inner symbol, which must be present.
::circt::hw::InnerRefAttr circt::hw::InnerSymbolOpInterface::getInnerRef() {
      return getImpl()->getInnerRef(getImpl(), getOperation());
  }

/// Returns the InnerSymAttr representing all inner symbols defined by this operation.
::circt::hw::InnerSymAttr circt::hw::InnerSymbolOpInterface::getInnerSymAttr() {
      return getImpl()->getInnerSymAttr(getImpl(), getOperation());
  }

/// Returns whether per-field symbols are supported for this operation type.
bool circt::hw::InnerSymbolOpInterface::supportsPerFieldSymbols() {
      return getImpl()->supportsPerFieldSymbols();
  }

/// Returns the index of the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
std::optional<size_t> circt::hw::InnerSymbolOpInterface::getTargetResultIndex() {
      return getImpl()->getTargetResultIndex();
  }

/// Returns the result the innner symbol targets, if applicable.  Per-field symbols are resolved into this.
OpResult circt::hw::InnerSymbolOpInterface::getTargetResult() {
      return getImpl()->getTargetResult(getImpl(), getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::hw::PortList::getPortList() {
      return getImpl()->getPortList(getImpl(), getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::hw::PortList::getPort(size_t idx) {
      return getImpl()->getPort(getImpl(), getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::hw::PortList::getPortIdForInputId(size_t idx) {
      return getImpl()->getPortIdForInputId(getImpl(), getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::hw::PortList::getPortIdForOutputId(size_t idx) {
      return getImpl()->getPortIdForOutputId(getImpl(), getOperation(), idx);
  }

/// Get the number of ports
size_t circt::hw::PortList::getNumPorts() {
      return getImpl()->getNumPorts(getImpl(), getOperation());
  }

/// Get the number of input ports
size_t circt::hw::PortList::getNumInputPorts() {
      return getImpl()->getNumInputPorts(getImpl(), getOperation());
  }

/// Get the number of output ports
size_t circt::hw::PortList::getNumOutputPorts() {
      return getImpl()->getNumOutputPorts(getImpl(), getOperation());
  }
