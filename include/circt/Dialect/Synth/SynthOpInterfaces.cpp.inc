/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Get the logical input values.
::mlir::ValueRange circt::synth::BooleanLogicOpInterface::getInputs() {
      return getImpl()->getInputs(getImpl(), getOperation());
  }

/// Get the logical input at the specified index and whether it is
/// inverted before the operation is evaluated.
::std::pair<::mlir::Value, bool> circt::synth::BooleanLogicOpInterface::getInputPair(unsigned index) {
      return getImpl()->getInputPair(getImpl(), getOperation(), index);
  }

/// Get the logical input value at the specified index.
::mlir::Value circt::synth::BooleanLogicOpInterface::getInput(unsigned index) {
      return getImpl()->getInput(getImpl(), getOperation(), index);
  }

/// Return whether the specified logical input is inverted before the
/// operation is evaluated.
bool circt::synth::BooleanLogicOpInterface::isInverted(unsigned index) {
      return getImpl()->isInverted(getImpl(), getOperation(), index);
  }

/// Get the inversion flags for all logical inputs.
::llvm::ArrayRef<bool> circt::synth::BooleanLogicOpInterface::getInverted() {
      return getImpl()->getInverted(getImpl(), getOperation());
  }

/// Set the inversion flags for all logical inputs.
void circt::synth::BooleanLogicOpInterface::setInverted(::llvm::ArrayRef<bool> inverted) {
      return getImpl()->setInverted(getImpl(), getOperation(), inverted);
  }

/// Get the primary logical result of this operation.
::mlir::Value circt::synth::BooleanLogicOpInterface::getResult() {
      return getImpl()->getResult(getImpl(), getOperation());
  }

/// Evaluate the boolean logic operation for the provided raw operand
/// inputs. The implementations are responsible for applying any per-input
/// inversion described by the operation itself.
::llvm::APInt circt::synth::BooleanLogicOpInterface::evaluateBooleanLogic(::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) {
      return getImpl()->evaluateBooleanLogic(getImpl(), getOperation(), getInputValue);
  }

/// Evaluate the boolean logic operation for the provided raw operand
/// inputs.
::llvm::APInt circt::synth::BooleanLogicOpInterface::evaluateBooleanLogic(::llvm::ArrayRef<::llvm::APInt> inputs) {
      return getImpl()->evaluateBooleanLogic_8(getImpl(), getOperation(), inputs);
  }

/// Compute known bits for the result from the logical inputs.
/// The implementations are responsible for applying any per-input inversion
/// described by the operation itself.
::llvm::KnownBits circt::synth::BooleanLogicOpInterface::computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits) {
      return getImpl()->computeKnownBits(getImpl(), getOperation(), getInputKnownBits);
  }

/// Return the abstract logic depth cost contributed by this operation.
/// This is the per-node delay used by analyses such as longest path.
int64_t circt::synth::BooleanLogicOpInterface::getLogicDepthCost() {
      return getImpl()->getLogicDepthCost(getImpl(), getOperation());
  }

/// Return the abstract logic area cost contributed by this operation.
/// This is the local resource cost used by analyses such as resource
/// usage. Implementations may return `std::nullopt` to indicate that
/// the area cost is unknown.
std::optional<uint64_t> circt::synth::BooleanLogicOpInterface::getLogicAreaCost() {
      return getImpl()->getLogicAreaCost(getImpl(), getOperation());
  }

/// Emit CNF clauses encoding `outVar <=> op(inputVars...)`.
/// The provided `inputVars` correspond to this operation's operands in
/// operand order. The default implementation materializes the per-input
/// inversion flags into the SAT literals and then delegates to
/// `emitCNFWithoutInversion`.
void circt::synth::BooleanLogicOpInterface::emitCNF(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
      return getImpl()->emitCNF(getImpl(), getOperation(), outVar, inputVars, addClause, newVar);
  }

/// Clone or fold this operation with the provided inputs while preserving
/// the existing inversion flags.
::mlir::Value circt::synth::BooleanLogicOpInterface::cloneWithSameInversion(::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs) {
      return getImpl()->cloneWithSameInversion(getImpl(), getOperation(), builder, newInputs);
  }

/// Return whether this op supports the given number of logical inputs.
bool circt::synth::BooleanLogicOpInterface::supportsNumInputs(unsigned numInputs) {
      return getImpl()->supportsNumInputs(numInputs);
  }

/// Evaluate the boolean logic operation for raw operand inputs after any
/// per-input inversion has already been applied by the caller.
::llvm::APInt circt::synth::BooleanLogicOpInterface::evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs) {
      return getImpl()->evaluateBooleanLogicWithoutInversion(inputs);
  }

/// Build this boolean logic operation with the given operands and
/// per-input inversion flags.
::mlir::Value circt::synth::BooleanLogicOpInterface::createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted) {
      return getImpl()->createBooleanLogicOp(builder, loc, operands, inverted);
  }

/// Return whether the operation semantics are invariant under
/// permutation of logical input pairs. Reordering an input means moving
/// both the input value and its inversion flag together.
bool circt::synth::BooleanLogicOpInterface::areInputsPermutationInvariant() {
      return getImpl()->areInputsPermutationInvariant();
  }

/// Emit CNF clauses encoding `outVar <=> op(inputVars...)` for the
/// non-inverted form of the operation. The provided `inputVars` are SAT
/// literals corresponding to the logical operands in operand order, after
/// any per-input inversion has already been materialized by the caller.
void circt::synth::BooleanLogicOpInterface::emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
      return getImpl()->emitCNFWithoutInversion(outVar, inputVars, addClause, newVar);
  }
