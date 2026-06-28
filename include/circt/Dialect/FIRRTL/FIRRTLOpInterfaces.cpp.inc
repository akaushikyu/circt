/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the type for instances of this class
ClassType circt::firrtl::ClassLike::getInstanceType() {
      return getImpl()->getInstanceType(getImpl(), getOperation());
  }

/// Verify that the given type agrees with this class
LogicalResult circt::firrtl::ClassLike::verifyType(::circt::firrtl::ClassType type, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
      return getImpl()->verifyType(getImpl(), getOperation(), type, emitError);
  }

/// Returns the name of this symbol.
::mlir::StringAttr circt::firrtl::ClassLike::getNameAttr() {
      return getImpl()->implSymbolOpInterface->getNameAttr(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the name of this symbol.
void circt::firrtl::ClassLike::setName(::mlir::StringAttr name) {
      return getImpl()->implSymbolOpInterface->setName(getImpl()->implSymbolOpInterface, getOperation(), name);
  }

/// Gets the visibility of this symbol.
mlir::SymbolTable::Visibility circt::firrtl::ClassLike::getVisibility() {
      return getImpl()->implSymbolOpInterface->getVisibility(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has nested visibility.
bool circt::firrtl::ClassLike::isNested() {
      return getImpl()->implSymbolOpInterface->isNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has private visibility.
bool circt::firrtl::ClassLike::isPrivate() {
      return getImpl()->implSymbolOpInterface->isPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has public visibility.
bool circt::firrtl::ClassLike::isPublic() {
      return getImpl()->implSymbolOpInterface->isPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol.
void circt::firrtl::ClassLike::setVisibility(mlir::SymbolTable::Visibility vis) {
      return getImpl()->implSymbolOpInterface->setVisibility(getImpl()->implSymbolOpInterface, getOperation(), vis);
  }

/// Sets the visibility of this symbol to be nested.
void circt::firrtl::ClassLike::setNested() {
      return getImpl()->implSymbolOpInterface->setNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be private.
void circt::firrtl::ClassLike::setPrivate() {
      return getImpl()->implSymbolOpInterface->setPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be public.
void circt::firrtl::ClassLike::setPublic() {
      return getImpl()->implSymbolOpInterface->setPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get all of the uses of the current symbol that are nested within the
/// given operation 'from'.
/// Note: See mlir::SymbolTable::getSymbolUses for more details.
::std::optional<::mlir::SymbolTable::UseRange> circt::firrtl::ClassLike::getSymbolUses(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->getSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Return if the current symbol is known to have no uses that are nested
/// within the given operation 'from'.
/// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
bool circt::firrtl::ClassLike::symbolKnownUseEmpty(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->symbolKnownUseEmpty(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Attempt to replace all uses of the current symbol with the provided
/// symbol 'newSymbol' that are nested within the given operation 'from'.
/// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
::llvm::LogicalResult circt::firrtl::ClassLike::replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->replaceAllSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), newSymbol, from);
  }

/// Returns true if this operation optionally defines a symbol based on the
/// presence of the symbol name.
bool circt::firrtl::ClassLike::isOptionalSymbol() {
      return getImpl()->implSymbolOpInterface->isOptionalSymbol(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation can be discarded if it has no remaining
/// symbol uses.
bool circt::firrtl::ClassLike::canDiscardOnUseEmpty() {
      return getImpl()->implSymbolOpInterface->canDiscardOnUseEmpty(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation is a declaration of a symbol (as opposed
/// to a definition).
bool circt::firrtl::ClassLike::isDeclaration() {
      return getImpl()->implSymbolOpInterface->isDeclaration(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::firrtl::ClassLike::getPortList() {
      return getImpl()->implPortList->getPortList(getImpl()->implPortList, getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::firrtl::ClassLike::getPort(size_t idx) {
      return getImpl()->implPortList->getPort(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::firrtl::ClassLike::getPortIdForInputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForInputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::firrtl::ClassLike::getPortIdForOutputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForOutputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the number of ports
size_t circt::firrtl::ClassLike::getNumPorts() {
      return getImpl()->implPortList->getNumPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of input ports
size_t circt::firrtl::ClassLike::getNumInputPorts() {
      return getImpl()->implPortList->getNumInputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of output ports
size_t circt::firrtl::ClassLike::getNumOutputPorts() {
      return getImpl()->implPortList->getNumOutputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the module name
::llvm::StringRef circt::firrtl::ClassLike::getModuleName() {
      return getImpl()->implModuleOpInterface->getModuleName(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::firrtl::ClassLike::getModuleNameAttr() {
      return getImpl()->implModuleOpInterface->getModuleNameAttr(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the parameters
ArrayAttr circt::firrtl::ClassLike::getParameters() {
      return getImpl()->implFModuleLike->getParameters(getImpl()->implFModuleLike, getOperation());
  }

/// Get the module's instantiation convention
ConventionAttr circt::firrtl::ClassLike::getConventionAttr() {
      return getImpl()->implFModuleLike->getConventionAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the module's instantiation convention
Convention circt::firrtl::ClassLike::getConvention() {
      return getImpl()->implFModuleLike->getConvention(getImpl()->implFModuleLike, getOperation());
  }

/// Get the module's enabled layers
ArrayAttr circt::firrtl::ClassLike::getLayersAttr() {
      return getImpl()->implFModuleLike->getLayersAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the module's enabled layers.
ArrayRef<Attribute> circt::firrtl::ClassLike::getLayers() {
      return getImpl()->implFModuleLike->getLayers(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port directions attribute
mlir::DenseBoolArrayAttr circt::firrtl::ClassLike::getPortDirectionsAttr() {
      return getImpl()->implFModuleLike->getPortDirectionsAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port directions
ArrayRef<bool> circt::firrtl::ClassLike::getPortDirections() {
      return getImpl()->implFModuleLike->getPortDirections(getImpl()->implFModuleLike, getOperation());
  }

/// Get a port direction
Direction circt::firrtl::ClassLike::getPortDirection(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortDirection(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get the port names attribute
ArrayAttr circt::firrtl::ClassLike::getPortNamesAttr() {
      return getImpl()->implFModuleLike->getPortNamesAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port names
ArrayRef<Attribute> circt::firrtl::ClassLike::getPortNames() {
      return getImpl()->implFModuleLike->getPortNames(getImpl()->implFModuleLike, getOperation());
  }

/// Get a port name
StringAttr circt::firrtl::ClassLike::getPortNameAttr(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortNameAttr(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get a port name
StringRef circt::firrtl::ClassLike::getPortName(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortName(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get the port types attribute
ArrayAttr circt::firrtl::ClassLike::getPortTypesAttr() {
      return getImpl()->implFModuleLike->getPortTypesAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port types
ArrayRef<Attribute> circt::firrtl::ClassLike::getPortTypes() {
      return getImpl()->implFModuleLike->getPortTypes(getImpl()->implFModuleLike, getOperation());
  }

/// Set the types of all ports
void circt::firrtl::ClassLike::setPortTypesAttr(::mlir::ArrayAttr portTypes) {
      return getImpl()->implFModuleLike->setPortTypesAttr(getImpl()->implFModuleLike, getOperation(), portTypes);
  }

/// Get a port type
TypeAttr circt::firrtl::ClassLike::getPortTypeAttr(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortTypeAttr(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get a port type
Type circt::firrtl::ClassLike::getPortType(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortType(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get the port annotations attribute
ArrayAttr circt::firrtl::ClassLike::getPortAnnotationsAttr() {
      return getImpl()->implFModuleLike->getPortAnnotationsAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port annotations attribute
ArrayRef<Attribute> circt::firrtl::ClassLike::getPortAnnotations() {
      return getImpl()->implFModuleLike->getPortAnnotations(getImpl()->implFModuleLike, getOperation());
  }

/// Set the port annotations attribute
void circt::firrtl::ClassLike::setPortAnnotationsAttr(::mlir::ArrayAttr annotations) {
      return getImpl()->implFModuleLike->setPortAnnotationsAttr(getImpl()->implFModuleLike, getOperation(), annotations);
  }

/// Get a port's annotations attribute
ArrayAttr circt::firrtl::ClassLike::getAnnotationsAttrForPort(size_t portIndex) {
      return getImpl()->implFModuleLike->getAnnotationsAttrForPort(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get a port's annotations
ArrayRef<Attribute> circt::firrtl::ClassLike::getAnnotationsForPort(size_t portIndex) {
      return getImpl()->implFModuleLike->getAnnotationsForPort(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get the port symbols attribute
ArrayAttr circt::firrtl::ClassLike::getPortSymbolsAttr() {
      return getImpl()->implFModuleLike->getPortSymbolsAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port symbols
ArrayRef<Attribute> circt::firrtl::ClassLike::getPortSymbols() {
      return getImpl()->implFModuleLike->getPortSymbols(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port symbol attribute
circt::hw::InnerSymAttr circt::firrtl::ClassLike::getPortSymbolAttr(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortSymbolAttr(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Set the symbols of all ports and their fields
void circt::firrtl::ClassLike::setPortSymbolsAttr(::mlir::ArrayAttr symbols) {
      return getImpl()->implFModuleLike->setPortSymbolsAttr(getImpl()->implFModuleLike, getOperation(), symbols);
  }

/// Set the symbols of all ports and their fields
void circt::firrtl::ClassLike::setPortSymbols(::llvm::ArrayRef<Attribute> symbols) {
      return getImpl()->implFModuleLike->setPortSymbols(getImpl()->implFModuleLike, getOperation(), symbols);
  }

/// Set the symbols for a port including its fields
void circt::firrtl::ClassLike::setPortSymbolAttr(size_t portIndex, circt::hw::InnerSymAttr symbol) {
      return getImpl()->implFModuleLike->setPortSymbolAttr(getImpl()->implFModuleLike, getOperation(), portIndex, symbol);
  }

/// Get the port locations attribute
ArrayAttr circt::firrtl::ClassLike::getPortLocationsAttr() {
      return getImpl()->implFModuleLike->getPortLocationsAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get the port locations attribute
ArrayRef<Attribute> circt::firrtl::ClassLike::getPortLocations() {
      return getImpl()->implFModuleLike->getPortLocations(getImpl()->implFModuleLike, getOperation());
  }

/// Get a port's location attribute
LocationAttr circt::firrtl::ClassLike::getPortLocationAttr(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortLocationAttr(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get a port's location
Location circt::firrtl::ClassLike::getPortLocation(size_t portIndex) {
      return getImpl()->implFModuleLike->getPortLocation(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Get domain information attribute
ArrayAttr circt::firrtl::ClassLike::getDomainInfoAttr() {
      return getImpl()->implFModuleLike->getDomainInfoAttr(getImpl()->implFModuleLike, getOperation());
  }

/// Get domain information
ArrayRef<Attribute> circt::firrtl::ClassLike::getDomainInfo() {
      return getImpl()->implFModuleLike->getDomainInfo(getImpl()->implFModuleLike, getOperation());
  }

/// Get a port's domain info attribute
Attribute circt::firrtl::ClassLike::getDomainInfoAttrForPort(size_t portIndex) {
      return getImpl()->implFModuleLike->getDomainInfoAttrForPort(getImpl()->implFModuleLike, getOperation(), portIndex);
  }

/// Set the domain info of all ports
void circt::firrtl::ClassLike::setDomainInfoAttr(::mlir::ArrayAttr domainInfo) {
      return getImpl()->implFModuleLike->setDomainInfoAttr(getImpl()->implFModuleLike, getOperation(), domainInfo);
  }

/// Get information about all ports
SmallVector<PortInfo> circt::firrtl::ClassLike::getPorts() {
      return getImpl()->implFModuleLike->getPorts(getImpl()->implFModuleLike, getOperation());
  }

/// Inserts the given ports at the corresponding indices
void circt::firrtl::ClassLike::insertPorts(ArrayRef<std::pair<unsigned, PortInfo>> ports) {
      return getImpl()->implFModuleLike->insertPorts(getImpl()->implFModuleLike, getOperation(), ports);
  }

/// Erases the ports that have their corresponding bit set in `portIndices`
void circt::firrtl::ClassLike::erasePorts(const llvm::BitVector& portIndices) {
      return getImpl()->implFModuleLike->erasePorts(getImpl()->implFModuleLike, getOperation(), portIndices);
  }

/// Return a destination of connection.
Value circt::firrtl::FConnectLike::getDest() {
      return getImpl()->getDest(getImpl(), getOperation());
  }

/// Return a source of connection.
Value circt::firrtl::FConnectLike::getSrc() {
      return getImpl()->getSrc(getImpl(), getOperation());
  }

/// Return connection behavior kind.
ConnectBehaviorKind circt::firrtl::FConnectLike::getConnectBehaviorKind() {
      return getImpl()->getConnectBehaviorKind();
  }

/// Returns true if ConnectBehavior is StaticSingleConnect.
bool circt::firrtl::FConnectLike::hasStaticSingleConnectBehavior() {
      return getImpl()->hasStaticSingleConnectBehavior();
  }

/// Returns true if ConnectBehavior is LastConnect.
bool circt::firrtl::FConnectLike::hasLastConnectBehavior() {
      return getImpl()->hasLastConnectBehavior();
  }

/// Get the number of ports
size_t circt::firrtl::FInstanceLike::getNumPorts() {
      return getImpl()->getNumPorts(getImpl(), getOperation());
  }

/// Get the port direction for the specified result number
Direction circt::firrtl::FInstanceLike::getPortDirection(size_t resultNo) {
      return getImpl()->getPortDirection(getImpl(), getOperation(), resultNo);
  }

/// Get the port name attribute for the specified result number
StringAttr circt::firrtl::FInstanceLike::getPortNameAttr(size_t resultNo) {
      return getImpl()->getPortNameAttr(getImpl(), getOperation(), resultNo);
  }

/// Get the port name for the specified result number
StringRef circt::firrtl::FInstanceLike::getPortName(size_t resultNo) {
      return getImpl()->getPortName(getImpl(), getOperation(), resultNo);
  }

/// Get the port location for the specified result number
Location circt::firrtl::FInstanceLike::getPortLocation(size_t resultNo) {
      return getImpl()->getPortLocation(getImpl(), getOperation(), resultNo);
  }

/// Get the port directions attribute
mlir::DenseBoolArrayAttr circt::firrtl::FInstanceLike::getPortDirectionsAttr() {
      return getImpl()->getPortDirectionsAttr(getImpl(), getOperation());
  }

/// Get the port directions
ArrayRef<bool> circt::firrtl::FInstanceLike::getPortDirections() {
      return getImpl()->getPortDirections(getImpl(), getOperation());
  }

/// Get the port names attribute
ArrayAttr circt::firrtl::FInstanceLike::getPortNamesAttr() {
      return getImpl()->getPortNamesAttr(getImpl(), getOperation());
  }

/// Get inner symbol attribute
::circt::hw::InnerSymAttr circt::firrtl::FInstanceLike::getInnerSymAttr() {
      return getImpl()->getInnerSymAttr(getImpl(), getOperation());
  }

/// Clone this instance with inserted ports
FInstanceLike circt::firrtl::FInstanceLike::cloneWithInsertedPorts(ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
      return getImpl()->cloneWithInsertedPorts(getImpl(), getOperation(), insertions);
  }

/// Clone this instance with inserted ports, then replace uses
FInstanceLike circt::firrtl::FInstanceLike::cloneWithInsertedPortsAndReplaceUses(ArrayRef<std::pair<unsigned, PortInfo>> insertions) {
      return getImpl()->cloneWithInsertedPortsAndReplaceUses(getImpl(), getOperation(), insertions);
  }

/// Clone this instance with erased ports
FInstanceLike circt::firrtl::FInstanceLike::cloneWithErasedPorts(const llvm::BitVector & erasures) {
      return getImpl()->cloneWithErasedPorts(getImpl(), getOperation(), erasures);
  }

/// Clone this instance with erased ports, then replace uses
FInstanceLike circt::firrtl::FInstanceLike::cloneWithErasedPortsAndReplaceUses(const llvm::BitVector & erasures) {
      return getImpl()->cloneWithErasedPortsAndReplaceUses(getImpl(), getOperation(), erasures);
  }

/// Get domain information attribute
ArrayAttr circt::firrtl::FInstanceLike::getDomainInfoAttr() {
      return getImpl()->getDomainInfoAttr(getImpl(), getOperation());
  }

/// Set domain information attribute
void circt::firrtl::FInstanceLike::setDomainInfoAttr(ArrayAttr domainInfo) {
      return getImpl()->setDomainInfoAttr(getImpl(), getOperation(), domainInfo);
  }

/// Get domain information attribute
Attribute circt::firrtl::FInstanceLike::getPortDomain(size_t portIndex) {
      return getImpl()->getPortDomain(getImpl(), getOperation(), portIndex);
  }

/// Get layers attribute
ArrayAttr circt::firrtl::FInstanceLike::getLayersAttr() {
      return getImpl()->getLayersAttr(getImpl(), getOperation());
  }

/// Set layers attribute
void circt::firrtl::FInstanceLike::setLayersAttr(ArrayAttr layers) {
      return getImpl()->setLayersAttr(getImpl(), getOperation(), layers);
  }

/// Get the name of the instance
::llvm::StringRef circt::firrtl::FInstanceLike::getInstanceName() {
      return getImpl()->implInstanceOpInterface->getInstanceName(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the name of the instance
::mlir::StringAttr circt::firrtl::FInstanceLike::getInstanceNameAttr() {
      return getImpl()->implInstanceOpInterface->getInstanceNameAttr(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the name of all the possibly instantiated modules
::llvm::SmallVector<::llvm::StringRef, 1> circt::firrtl::FInstanceLike::getReferencedModuleNames() {
      return getImpl()->implInstanceOpInterface->getReferencedModuleNames(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the names of the instantiated modules as an ArrayAttr. Returns an ArrayAttr containing StringAttr elements, where each StringAttr represents the name of a potentially instantiated module.
::mlir::ArrayAttr circt::firrtl::FInstanceLike::getReferencedModuleNamesAttr() {
      return getImpl()->implInstanceOpInterface->getReferencedModuleNamesAttr(getImpl()->implInstanceOpInterface, getOperation());
  }

/// Get the parameters
ArrayAttr circt::firrtl::FModuleLike::getParameters() {
      return getImpl()->getParameters(getImpl(), getOperation());
  }

/// Get the module's instantiation convention
ConventionAttr circt::firrtl::FModuleLike::getConventionAttr() {
      return getImpl()->getConventionAttr(getImpl(), getOperation());
  }

/// Get the module's instantiation convention
Convention circt::firrtl::FModuleLike::getConvention() {
      return getImpl()->getConvention(getImpl(), getOperation());
  }

/// Get the module's enabled layers
ArrayAttr circt::firrtl::FModuleLike::getLayersAttr() {
      return getImpl()->getLayersAttr(getImpl(), getOperation());
  }

/// Get the module's enabled layers.
ArrayRef<Attribute> circt::firrtl::FModuleLike::getLayers() {
      return getImpl()->getLayers(getImpl(), getOperation());
  }

/// Get the port directions attribute
mlir::DenseBoolArrayAttr circt::firrtl::FModuleLike::getPortDirectionsAttr() {
      return getImpl()->getPortDirectionsAttr(getImpl(), getOperation());
  }

/// Get the port directions
ArrayRef<bool> circt::firrtl::FModuleLike::getPortDirections() {
      return getImpl()->getPortDirections(getImpl(), getOperation());
  }

/// Get a port direction
Direction circt::firrtl::FModuleLike::getPortDirection(size_t portIndex) {
      return getImpl()->getPortDirection(getImpl(), getOperation(), portIndex);
  }

/// Get the port names attribute
ArrayAttr circt::firrtl::FModuleLike::getPortNamesAttr() {
      return getImpl()->getPortNamesAttr(getImpl(), getOperation());
  }

/// Get the port names
ArrayRef<Attribute> circt::firrtl::FModuleLike::getPortNames() {
      return getImpl()->getPortNames(getImpl(), getOperation());
  }

/// Get a port name
StringAttr circt::firrtl::FModuleLike::getPortNameAttr(size_t portIndex) {
      return getImpl()->getPortNameAttr(getImpl(), getOperation(), portIndex);
  }

/// Get a port name
StringRef circt::firrtl::FModuleLike::getPortName(size_t portIndex) {
      return getImpl()->getPortName(getImpl(), getOperation(), portIndex);
  }

/// Get the port types attribute
ArrayAttr circt::firrtl::FModuleLike::getPortTypesAttr() {
      return getImpl()->getPortTypesAttr(getImpl(), getOperation());
  }

/// Get the port types
ArrayRef<Attribute> circt::firrtl::FModuleLike::getPortTypes() {
      return getImpl()->getPortTypes(getImpl(), getOperation());
  }

/// Set the types of all ports
void circt::firrtl::FModuleLike::setPortTypesAttr(::mlir::ArrayAttr portTypes) {
      return getImpl()->setPortTypesAttr(getImpl(), getOperation(), portTypes);
  }

/// Get a port type
TypeAttr circt::firrtl::FModuleLike::getPortTypeAttr(size_t portIndex) {
      return getImpl()->getPortTypeAttr(getImpl(), getOperation(), portIndex);
  }

/// Get a port type
Type circt::firrtl::FModuleLike::getPortType(size_t portIndex) {
      return getImpl()->getPortType(getImpl(), getOperation(), portIndex);
  }

/// Get the port annotations attribute
ArrayAttr circt::firrtl::FModuleLike::getPortAnnotationsAttr() {
      return getImpl()->getPortAnnotationsAttr(getImpl(), getOperation());
  }

/// Get the port annotations attribute
ArrayRef<Attribute> circt::firrtl::FModuleLike::getPortAnnotations() {
      return getImpl()->getPortAnnotations(getImpl(), getOperation());
  }

/// Set the port annotations attribute
void circt::firrtl::FModuleLike::setPortAnnotationsAttr(::mlir::ArrayAttr annotations) {
      return getImpl()->setPortAnnotationsAttr(getImpl(), getOperation(), annotations);
  }

/// Get a port's annotations attribute
ArrayAttr circt::firrtl::FModuleLike::getAnnotationsAttrForPort(size_t portIndex) {
      return getImpl()->getAnnotationsAttrForPort(getImpl(), getOperation(), portIndex);
  }

/// Get a port's annotations
ArrayRef<Attribute> circt::firrtl::FModuleLike::getAnnotationsForPort(size_t portIndex) {
      return getImpl()->getAnnotationsForPort(getImpl(), getOperation(), portIndex);
  }

/// Get the port symbols attribute
ArrayAttr circt::firrtl::FModuleLike::getPortSymbolsAttr() {
      return getImpl()->getPortSymbolsAttr(getImpl(), getOperation());
  }

/// Get the port symbols
ArrayRef<Attribute> circt::firrtl::FModuleLike::getPortSymbols() {
      return getImpl()->getPortSymbols(getImpl(), getOperation());
  }

/// Get the port symbol attribute
circt::hw::InnerSymAttr circt::firrtl::FModuleLike::getPortSymbolAttr(size_t portIndex) {
      return getImpl()->getPortSymbolAttr(getImpl(), getOperation(), portIndex);
  }

/// Set the symbols of all ports and their fields
void circt::firrtl::FModuleLike::setPortSymbolsAttr(::mlir::ArrayAttr symbols) {
      return getImpl()->setPortSymbolsAttr(getImpl(), getOperation(), symbols);
  }

/// Set the symbols of all ports and their fields
void circt::firrtl::FModuleLike::setPortSymbols(::llvm::ArrayRef<Attribute> symbols) {
      return getImpl()->setPortSymbols(getImpl(), getOperation(), symbols);
  }

/// Set the symbols for a port including its fields
void circt::firrtl::FModuleLike::setPortSymbolAttr(size_t portIndex, circt::hw::InnerSymAttr symbol) {
      return getImpl()->setPortSymbolAttr(getImpl(), getOperation(), portIndex, symbol);
  }

/// Get the port locations attribute
ArrayAttr circt::firrtl::FModuleLike::getPortLocationsAttr() {
      return getImpl()->getPortLocationsAttr(getImpl(), getOperation());
  }

/// Get the port locations attribute
ArrayRef<Attribute> circt::firrtl::FModuleLike::getPortLocations() {
      return getImpl()->getPortLocations(getImpl(), getOperation());
  }

/// Get a port's location attribute
LocationAttr circt::firrtl::FModuleLike::getPortLocationAttr(size_t portIndex) {
      return getImpl()->getPortLocationAttr(getImpl(), getOperation(), portIndex);
  }

/// Get a port's location
Location circt::firrtl::FModuleLike::getPortLocation(size_t portIndex) {
      return getImpl()->getPortLocation(getImpl(), getOperation(), portIndex);
  }

/// Get domain information attribute
ArrayAttr circt::firrtl::FModuleLike::getDomainInfoAttr() {
      return getImpl()->getDomainInfoAttr(getImpl(), getOperation());
  }

/// Get domain information
ArrayRef<Attribute> circt::firrtl::FModuleLike::getDomainInfo() {
      return getImpl()->getDomainInfo(getImpl(), getOperation());
  }

/// Get a port's domain info attribute
Attribute circt::firrtl::FModuleLike::getDomainInfoAttrForPort(size_t portIndex) {
      return getImpl()->getDomainInfoAttrForPort(getImpl(), getOperation(), portIndex);
  }

/// Set the domain info of all ports
void circt::firrtl::FModuleLike::setDomainInfoAttr(::mlir::ArrayAttr domainInfo) {
      return getImpl()->setDomainInfoAttr(getImpl(), getOperation(), domainInfo);
  }

/// Get information about all ports
SmallVector<PortInfo> circt::firrtl::FModuleLike::getPorts() {
      return getImpl()->getPorts(getImpl(), getOperation());
  }

/// Inserts the given ports at the corresponding indices
void circt::firrtl::FModuleLike::insertPorts(ArrayRef<std::pair<unsigned, PortInfo>> ports) {
      return getImpl()->insertPorts(getImpl(), getOperation(), ports);
  }

/// Erases the ports that have their corresponding bit set in `portIndices`
void circt::firrtl::FModuleLike::erasePorts(const llvm::BitVector& portIndices) {
      return getImpl()->erasePorts(getImpl(), getOperation(), portIndices);
  }

/// Returns the name of this symbol.
::mlir::StringAttr circt::firrtl::FModuleLike::getNameAttr() {
      return getImpl()->implSymbolOpInterface->getNameAttr(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the name of this symbol.
void circt::firrtl::FModuleLike::setName(::mlir::StringAttr name) {
      return getImpl()->implSymbolOpInterface->setName(getImpl()->implSymbolOpInterface, getOperation(), name);
  }

/// Gets the visibility of this symbol.
mlir::SymbolTable::Visibility circt::firrtl::FModuleLike::getVisibility() {
      return getImpl()->implSymbolOpInterface->getVisibility(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has nested visibility.
bool circt::firrtl::FModuleLike::isNested() {
      return getImpl()->implSymbolOpInterface->isNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has private visibility.
bool circt::firrtl::FModuleLike::isPrivate() {
      return getImpl()->implSymbolOpInterface->isPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this symbol has public visibility.
bool circt::firrtl::FModuleLike::isPublic() {
      return getImpl()->implSymbolOpInterface->isPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol.
void circt::firrtl::FModuleLike::setVisibility(mlir::SymbolTable::Visibility vis) {
      return getImpl()->implSymbolOpInterface->setVisibility(getImpl()->implSymbolOpInterface, getOperation(), vis);
  }

/// Sets the visibility of this symbol to be nested.
void circt::firrtl::FModuleLike::setNested() {
      return getImpl()->implSymbolOpInterface->setNested(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be private.
void circt::firrtl::FModuleLike::setPrivate() {
      return getImpl()->implSymbolOpInterface->setPrivate(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Sets the visibility of this symbol to be public.
void circt::firrtl::FModuleLike::setPublic() {
      return getImpl()->implSymbolOpInterface->setPublic(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get all of the uses of the current symbol that are nested within the
/// given operation 'from'.
/// Note: See mlir::SymbolTable::getSymbolUses for more details.
::std::optional<::mlir::SymbolTable::UseRange> circt::firrtl::FModuleLike::getSymbolUses(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->getSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Return if the current symbol is known to have no uses that are nested
/// within the given operation 'from'.
/// Note: See mlir::SymbolTable::symbolKnownUseEmpty for more details.
bool circt::firrtl::FModuleLike::symbolKnownUseEmpty(::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->symbolKnownUseEmpty(getImpl()->implSymbolOpInterface, getOperation(), from);
  }

/// Attempt to replace all uses of the current symbol with the provided
/// symbol 'newSymbol' that are nested within the given operation 'from'.
/// Note: See mlir::SymbolTable::replaceAllSymbolUses for more details.
::llvm::LogicalResult circt::firrtl::FModuleLike::replaceAllSymbolUses(::mlir::StringAttr newSymbol, ::mlir::Operation * from) {
      return getImpl()->implSymbolOpInterface->replaceAllSymbolUses(getImpl()->implSymbolOpInterface, getOperation(), newSymbol, from);
  }

/// Returns true if this operation optionally defines a symbol based on the
/// presence of the symbol name.
bool circt::firrtl::FModuleLike::isOptionalSymbol() {
      return getImpl()->implSymbolOpInterface->isOptionalSymbol(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation can be discarded if it has no remaining
/// symbol uses.
bool circt::firrtl::FModuleLike::canDiscardOnUseEmpty() {
      return getImpl()->implSymbolOpInterface->canDiscardOnUseEmpty(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Returns true if this operation is a declaration of a symbol (as opposed
/// to a definition).
bool circt::firrtl::FModuleLike::isDeclaration() {
      return getImpl()->implSymbolOpInterface->isDeclaration(getImpl()->implSymbolOpInterface, getOperation());
  }

/// Get port list
SmallVector<::circt::hw::PortInfo> circt::firrtl::FModuleLike::getPortList() {
      return getImpl()->implPortList->getPortList(getImpl()->implPortList, getOperation());
  }

/// Get port list
::circt::hw::PortInfo circt::firrtl::FModuleLike::getPort(size_t idx) {
      return getImpl()->implPortList->getPort(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific input
size_t circt::firrtl::FModuleLike::getPortIdForInputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForInputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the port a specific output
size_t circt::firrtl::FModuleLike::getPortIdForOutputId(size_t idx) {
      return getImpl()->implPortList->getPortIdForOutputId(getImpl()->implPortList, getOperation(), idx);
  }

/// Get the number of ports
size_t circt::firrtl::FModuleLike::getNumPorts() {
      return getImpl()->implPortList->getNumPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of input ports
size_t circt::firrtl::FModuleLike::getNumInputPorts() {
      return getImpl()->implPortList->getNumInputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the number of output ports
size_t circt::firrtl::FModuleLike::getNumOutputPorts() {
      return getImpl()->implPortList->getNumOutputPorts(getImpl()->implPortList, getOperation());
  }

/// Get the module name
::llvm::StringRef circt::firrtl::FModuleLike::getModuleName() {
      return getImpl()->implModuleOpInterface->getModuleName(getImpl()->implModuleOpInterface, getOperation());
  }

/// Get the module name
::mlir::StringAttr circt::firrtl::FModuleLike::getModuleNameAttr() {
      return getImpl()->implModuleOpInterface->getModuleNameAttr(getImpl()->implModuleOpInterface, getOperation());
  }

/// Return the name.
::mlir::StringAttr circt::firrtl::FNamableOp::getNameAttr() {
      return getImpl()->getNameAttr(getImpl(), getOperation());
  }

/// Return the name.
::llvm::StringRef circt::firrtl::FNamableOp::getName() {
      return getImpl()->getName(getImpl(), getOperation());
  }

/// Set the name.
void circt::firrtl::FNamableOp::setNameAttr(::mlir::StringAttr name) {
      return getImpl()->setNameAttr(getImpl(), getOperation(), name);
  }

/// Set the name.
void circt::firrtl::FNamableOp::setName(::llvm::StringRef name) {
      return getImpl()->setName(getImpl(), getOperation(), name);
  }

/// Get the namekind
::circt::firrtl::NameKindEnumAttr circt::firrtl::FNamableOp::getNameKindAttr() {
      return getImpl()->getNameKindAttr(getImpl(), getOperation());
  }

/// Get the namekind
::circt::firrtl::NameKindEnum circt::firrtl::FNamableOp::getNameKind() {
      return getImpl()->getNameKind(getImpl(), getOperation());
  }

/// Set a namekind.
void circt::firrtl::FNamableOp::setNameKindAttr(::circt::firrtl::NameKindEnumAttr nameKind) {
      return getImpl()->setNameKindAttr(getImpl(), getOperation(), nameKind);
  }

/// Set a namekind.
void circt::firrtl::FNamableOp::setNameKind(::circt::firrtl::NameKindEnum nameKind) {
      return getImpl()->setNameKind(getImpl(), getOperation(), nameKind);
  }

/// Return true if the name is droppable.
bool circt::firrtl::FNamableOp::hasDroppableName() {
      return getImpl()->hasDroppableName(getImpl(), getOperation());
  }

/// Return true if the operation is forceable.
bool circt::firrtl::Forceable::isForceable() {
      return getImpl()->isForceable(getImpl(), getOperation());
  }

/// Return data value that will be targeted.
mlir::TypedValue<FIRRTLBaseType> circt::firrtl::Forceable::getData() {
      return getImpl()->getData(getImpl(), getOperation());
  }

/// Return raw data value that will be targeted.
Value circt::firrtl::Forceable::getDataRaw() {
      return getImpl()->getDataRaw(getImpl(), getOperation());
  }

/// Return data type that will be referenced.
FIRRTLBaseType circt::firrtl::Forceable::getDataType() {
      return getImpl()->getDataType(getImpl(), getOperation());
  }

/// Return reference result, or null if not active.
mlir::TypedValue<RefType> circt::firrtl::Forceable::getDataRef() {
      return getImpl()->getDataRef(getImpl(), getOperation());
  }
