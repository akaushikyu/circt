/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns true if this operation is a control operation.
bool circt::handshake::ControlInterface::isControl() {
      return getImpl()->isControl(getImpl(), getOperation());
  }

/// The op checks its precondition to execute. If the precondition holds, the op executes with the given input values and returns zero. Otherwise, it returns a false value to suggest the simulator to reschedule. The execution interface of hpx ops take the following arguments: bool = returns whether the op has been executed;valueMap = a map of all values in the code;memoryMap = a map of memory ops to simualte;timeMap = a map of the last arrival time of all values;store = The store associates each allocation in the program(represented by a int) with a vector of values which can beaccessed by it.scheduleList = a list of values to be scheduled.
bool circt::handshake::ExecutableOpInterface::tryExecute(llvm::DenseMap<mlir::Value, llvm::Any> & valueMap, llvm::DenseMap<unsigned, unsigned> & memoryMap, llvm::DenseMap<mlir::Value, double> & timeMap, std::vector<std::vector<llvm::Any>> & store, std::vector<mlir::Value> & scheduleList) {
      return getImpl()->tryExecute(getImpl(), getOperation(), valueMap, memoryMap, timeMap, store, scheduleList);
  }

/// Simulate the Execution of the general op with given inputs
void circt::handshake::GeneralOpInterface::execute(std::vector<llvm::Any> & ins, std::vector<llvm::Any> & outs) {
      return getImpl()->execute(getImpl(), getOperation(), ins, outs);
  }

/// Simulate the memory allocation in the memoryMap
bool circt::handshake::MemoryOpInterface::allocateMemory(llvm::DenseMap<unsigned, unsigned> & memoryMap, std::vector<std::vector<llvm::Any>> & store, std::vector<double> & storeTimes) {
      return getImpl()->allocateMemory(getImpl(), getOperation(), memoryMap, store, storeTimes);
  }

/// Returns an operand range over the data signals being merged.
mlir::OperandRange circt::handshake::MergeLikeOpInterface::getDataOperands() {
      return getImpl()->getDataOperands(getImpl(), getOperation());
  }

/// Get the name of an operand.
std::string circt::handshake::NamedIOInterface::getOperandName(unsigned idx) {
      return getImpl()->getOperandName(getImpl(), getOperation(), idx);
  }

/// Get the name of a result.
std::string circt::handshake::NamedIOInterface::getResultName(unsigned idx) {
      return getImpl()->getResultName(getImpl(), getOperation(), idx);
  }

/// Get the data type associated to the operation.
/// The default implementation of this method simply returns the type of
/// the first operation operand.
mlir::Type circt::handshake::SOSTInterface::getDataType() {
      return getImpl()->getDataType(getImpl(), getOperation());
  }

/// Get the size associated to the operation.
/// The default implementation of this method simply returns the number of
/// operation operands.
unsigned circt::handshake::SOSTInterface::getSize() {
      return getImpl()->getSize(getImpl(), getOperation());
  }

/// Determine whether the operation is a control operation.
/// The default implementation of this method assumes that the operation
/// is a control operation if and only if its associated data type is a
/// NoneType.
bool circt::handshake::SOSTInterface::sostIsControl() {
      return getImpl()->sostIsControl(getImpl(), getOperation());
  }

/// Print the "SOST characteristics" of an operation.
/// If the `explicitSize` parameter is set to true, then the method prints
/// the operation's size (in the SOST sense) between square brackets before
/// printing the operation's operands, attributes, and data type.
void circt::handshake::SOSTInterface::sostPrint(mlir::OpAsmPrinter & printer, bool explicitSize) {
      return getImpl()->sostPrint(getImpl(), getOperation(), printer, explicitSize);
  }
