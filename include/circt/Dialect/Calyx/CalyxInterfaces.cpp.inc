/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// This returns the port names associated with the cell.
SmallVector<StringRef> circt::calyx::CellInterface::portNames() {
      return getImpl()->portNames(getImpl(), getOperation());
  }

/// This returns the port directions associated with the cell.
SmallVector<circt::calyx::Direction> circt::calyx::CellInterface::portDirections() {
      return getImpl()->portDirections(getImpl(), getOperation());
  }

/// This returns the port attributes associated with the cell.
SmallVector<DictionaryAttr> circt::calyx::CellInterface::portAttributes() {
      return getImpl()->portAttributes(getImpl(), getOperation());
  }

/// This returns the instance name of the cell.
StringRef circt::calyx::CellInterface::instanceName() {
      return getImpl()->instanceName(getImpl(), getOperation());
  }

/// This returns the index of the port within the result values of this cell.
unsigned circt::calyx::CellInterface::portIndex(Value port) {
      return getImpl()->portIndex(getImpl(), getOperation(), port);
  }

/// This returns the PortInfo associated with all of the ports of a cell.
SmallVector<circt::calyx::PortInfo> circt::calyx::CellInterface::getPortInfo() {
      return getImpl()->getPortInfo(getImpl(), getOperation());
  }

/// This returns the PortInfo associated with the port of a cell.
circt::calyx::PortInfo circt::calyx::CellInterface::portInfo(Value port) {
      return getImpl()->portInfo(getImpl(), getOperation(), port);
  }

/// This returns the direction of a given port of a cell.
circt::calyx::Direction circt::calyx::CellInterface::direction(Value port) {
      return getImpl()->direction(getImpl(), getOperation(), port);
  }

/// This returns the name of a given port of a cell.
StringRef circt::calyx::CellInterface::portName(Value port) {
      return getImpl()->portName(getImpl(), getOperation(), port);
  }

/// This returns the attributes of a given port of a cell.
DictionaryAttr circt::calyx::CellInterface::portDictionaryAttr(Value port) {
      return getImpl()->portDictionaryAttr(getImpl(), getOperation(), port);
  }

/// This returns the input ports of a cell.
SmallVector<Value> circt::calyx::CellInterface::getInputPorts() {
      return getImpl()->getInputPorts(getImpl(), getOperation());
  }

/// This returns the output ports of a cell.
SmallVector<Value> circt::calyx::CellInterface::getOutputPorts() {
      return getImpl()->getOutputPorts(getImpl(), getOperation());
  }

/// This returns the ports of a cell, filtering out any interface ports.
SmallVector<Value> circt::calyx::CellInterface::filterInterfacePorts(calyx::Direction dir) {
      return getImpl()->filterInterfacePorts(getImpl(), getOperation(), dir);
  }

/// This returns true iff the cell is combinational
bool circt::calyx::CellInterface::isCombinational() {
      return getImpl()->isCombinational(getImpl(), getOperation());
  }

/// This returns the port names associated with the component.
ArrayAttr circt::calyx::ComponentInterface::getPortNames() {
      return getImpl()->getPortNames(getImpl(), getOperation());
  }

/// This returns the port info associated with the component.
SmallVector<circt::calyx::PortInfo> circt::calyx::ComponentInterface::getPortInfo() {
      return getImpl()->getPortInfo(getImpl(), getOperation());
  }

/// This returns the input port info associated with the component.
SmallVector<circt::calyx::PortInfo> circt::calyx::ComponentInterface::getInputPortInfo() {
      return getImpl()->getInputPortInfo(getImpl(), getOperation());
  }

/// This returns the output port info associated with the component.
SmallVector<circt::calyx::PortInfo> circt::calyx::ComponentInterface::getOutputPortInfo() {
      return getImpl()->getOutputPortInfo(getImpl(), getOperation());
  }

/// This returns the name of the component.
StringRef circt::calyx::ComponentInterface::getName() {
      return getImpl()->getName(getImpl(), getOperation());
  }

/// This returns true iff the component is combinational.
bool circt::calyx::ComponentInterface::isComb() {
      return getImpl()->isComb(getImpl(), getOperation());
  }

/// This returns the body region of the component.
Region*circt::calyx::ComponentInterface::getRegion() {
      return getImpl()->getRegion(getImpl(), getOperation());
  }

/// This returns the body block of the component.
Block*circt::calyx::ComponentInterface::getBodyBlock() {
      return getImpl()->getBodyBlock(getImpl(), getOperation());
  }

/// This returns the floating point standard.
FloatingPointStandard circt::calyx::FloatingPointOpInterface::getFloatingPointStandard() {
      return getImpl()->getFloatingPointStandard();
  }

/// This returns the Calyx native library name.
std::string circt::calyx::FloatingPointOpInterface::getCalyxLibraryName() {
      return getImpl()->getCalyxLibraryName();
  }

/// This returns the symbol name of the group.
mlir::StringAttr circt::calyx::GroupInterface::symName() {
      return getImpl()->symName(getImpl(), getOperation());
  }

/// This returns the body of the group.
Block*circt::calyx::GroupInterface::getBody() {
      return getImpl()->getBody(getImpl(), getOperation());
  }

/// Determines whether the given port is driven by this group.
LogicalResult circt::calyx::GroupInterface::drivesPort(Value port) {
      return getImpl()->drivesPort(getImpl(), getOperation(), port);
  }

/// Determines whether all the given ports are driven by this group.
LogicalResult circt::calyx::GroupInterface::drivesAllPorts(ValueRange ports) {
      return getImpl()->drivesAllPorts(getImpl(), getOperation(), ports);
  }

/// Determines whether any of the given ports are driven by this group.
LogicalResult circt::calyx::GroupInterface::drivesAnyPort(ValueRange ports) {
      return getImpl()->drivesAnyPort(getImpl(), getOperation(), ports);
  }

/// Determines whether any of the given ports are read by this group.
LogicalResult circt::calyx::GroupInterface::readsAnyPort(ValueRange ports) {
      return getImpl()->readsAnyPort(getImpl(), getOperation(), ports);
  }

/// This returns true if the then body exists.
bool circt::calyx::IfInterface::thenBodyExists() {
      return getImpl()->thenBodyExists(getImpl(), getOperation());
  }

/// This returns true if the else body exists.
bool circt::calyx::IfInterface::elseBodyExists() {
      return getImpl()->elseBodyExists(getImpl(), getOperation());
  }

/// This returns the then body block.
Block*circt::calyx::IfInterface::getThenBody() {
      return getImpl()->getThenBody(getImpl(), getOperation());
  }

/// This returns the else body block.
Block*circt::calyx::IfInterface::getElseBody() {
      return getImpl()->getElseBody(getImpl(), getOperation());
  }
