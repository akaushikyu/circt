/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::synth {

/// Common interface for boolean-logic DAG nodes whose semantics are defined by
/// a list of input values together with per-input inversion flags.
/// 
/// Modern logic-network representations often use the same "value plus
/// complemented edge" model across several node kinds, for example AIG-style
/// nodes as well as closely related 3-input or otherwise non-binary DAG
/// nodes. Passes such as structural hashing, bit lowering, and simulation
/// should be able to operate on those common semantics without hardcoding a
/// specific concrete op.
class BooleanLogicOpInterface;

} // namespace circt::synth
namespace circt::synth {

/// Common interface for boolean-logic DAG nodes whose semantics are defined by
/// a list of input values together with per-input inversion flags.
/// 
/// Modern logic-network representations often use the same "value plus
/// complemented edge" model across several node kinds, for example AIG-style
/// nodes as well as closely related 3-input or otherwise non-binary DAG
/// nodes. Passes such as structural hashing, bit lowering, and simulation
/// should be able to operate on those common semantics without hardcoding a
/// specific concrete op.
namespace detail {
struct BooleanLogicOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::ValueRange (*getInputs)(const Concept *impl, ::mlir::Operation *);
    ::std::pair<::mlir::Value, bool> (*getInputPair)(const Concept *impl, ::mlir::Operation *, unsigned);
    ::mlir::Value (*getInput)(const Concept *impl, ::mlir::Operation *, unsigned);
    bool (*isInverted)(const Concept *impl, ::mlir::Operation *, unsigned);
    ::llvm::ArrayRef<bool> (*getInverted)(const Concept *impl, ::mlir::Operation *);
    void (*setInverted)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<bool>);
    ::mlir::Value (*getResult)(const Concept *impl, ::mlir::Operation *);
    ::llvm::APInt (*evaluateBooleanLogic)(const Concept *impl, ::mlir::Operation *, ::llvm::function_ref<const ::llvm::APInt &(unsigned)>);
    ::llvm::APInt (*evaluateBooleanLogic_8)(const Concept *impl, ::mlir::Operation *, ::llvm::ArrayRef<::llvm::APInt>);
    ::llvm::KnownBits (*computeKnownBits)(const Concept *impl, ::mlir::Operation *, ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>);
    int64_t (*getLogicDepthCost)(const Concept *impl, ::mlir::Operation *);
    std::optional<uint64_t> (*getLogicAreaCost)(const Concept *impl, ::mlir::Operation *);
    void (*emitCNF)(const Concept *impl, ::mlir::Operation *, int, ::llvm::ArrayRef<int>, ::llvm::function_ref<void(::llvm::ArrayRef<int>)>, ::llvm::function_ref<int()>);
    ::mlir::Value (*cloneWithSameInversion)(const Concept *impl, ::mlir::Operation *, ::mlir::OpBuilder &, ::mlir::ValueRange);
    bool (*supportsNumInputs)(unsigned);
    ::llvm::APInt (*evaluateBooleanLogicWithoutInversion)(::llvm::ArrayRef<::llvm::APInt>);
    ::mlir::Value (*createBooleanLogicOp)(::mlir::OpBuilder &, ::mlir::Location, ::llvm::ArrayRef<::mlir::Value>, ::llvm::ArrayRef<bool>);
    bool (*areInputsPermutationInvariant)();
    void (*emitCNFWithoutInversion)(int, ::llvm::ArrayRef<int>, ::llvm::function_ref<void(::llvm::ArrayRef<int>)>, ::llvm::function_ref<int()>);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::synth::BooleanLogicOpInterface;
    Model() : Concept{getInputs, getInputPair, getInput, isInverted, getInverted, setInverted, getResult, evaluateBooleanLogic, evaluateBooleanLogic_8, computeKnownBits, getLogicDepthCost, getLogicAreaCost, emitCNF, cloneWithSameInversion, supportsNumInputs, evaluateBooleanLogicWithoutInversion, createBooleanLogicOp, areInputsPermutationInvariant, emitCNFWithoutInversion} {}

    static inline ::mlir::ValueRange getInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::pair<::mlir::Value, bool> getInputPair(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::mlir::Value getInput(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline bool isInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::llvm::ArrayRef<bool> getInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<bool> inverted);
    static inline ::mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::APInt evaluateBooleanLogic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue);
    static inline ::llvm::APInt evaluateBooleanLogic_8(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs);
    static inline ::llvm::KnownBits computeKnownBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
    static inline int64_t getLogicDepthCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::optional<uint64_t> getLogicAreaCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void emitCNF(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
    static inline ::mlir::Value cloneWithSameInversion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs);
    static inline bool supportsNumInputs(unsigned numInputs);
    static inline ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
    static inline ::mlir::Value createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted);
    static inline bool areInputsPermutationInvariant();
    static inline void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::synth::BooleanLogicOpInterface;
    FallbackModel() : Concept{getInputs, getInputPair, getInput, isInverted, getInverted, setInverted, getResult, evaluateBooleanLogic, evaluateBooleanLogic_8, computeKnownBits, getLogicDepthCost, getLogicAreaCost, emitCNF, cloneWithSameInversion, supportsNumInputs, evaluateBooleanLogicWithoutInversion, createBooleanLogicOp, areInputsPermutationInvariant, emitCNFWithoutInversion} {}

    static inline ::mlir::ValueRange getInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::std::pair<::mlir::Value, bool> getInputPair(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::mlir::Value getInput(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline bool isInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index);
    static inline ::llvm::ArrayRef<bool> getInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void setInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<bool> inverted);
    static inline ::mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::APInt evaluateBooleanLogic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue);
    static inline ::llvm::APInt evaluateBooleanLogic_8(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs);
    static inline ::llvm::KnownBits computeKnownBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
    static inline int64_t getLogicDepthCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::optional<uint64_t> getLogicAreaCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void emitCNF(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
    static inline ::mlir::Value cloneWithSameInversion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs);
    static inline bool supportsNumInputs(unsigned numInputs);
    static inline ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
    static inline ::mlir::Value createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted);
    static inline bool areInputsPermutationInvariant();
    static inline void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::mlir::ValueRange getInputs(::mlir::Operation *tablegen_opaque_val) const;
    ::std::pair<::mlir::Value, bool> getInputPair(::mlir::Operation *tablegen_opaque_val, unsigned index) const;
    ::mlir::Value getInput(::mlir::Operation *tablegen_opaque_val, unsigned index) const;
    bool isInverted(::mlir::Operation *tablegen_opaque_val, unsigned index) const;
    ::mlir::Value getResult(::mlir::Operation *tablegen_opaque_val) const;
    ::llvm::APInt evaluateBooleanLogic(::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) const;
    ::llvm::APInt evaluateBooleanLogic_8(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs) const;
    int64_t getLogicDepthCost(::mlir::Operation *tablegen_opaque_val) const;
    void emitCNF(::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) const;
    ::mlir::Value cloneWithSameInversion(::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder &builder, ::mlir::ValueRange newInputs) const;
  };
};
template <typename ConcreteOp>
struct BooleanLogicOpInterfaceTrait;

} // namespace detail
class BooleanLogicOpInterface : public ::mlir::OpInterface<BooleanLogicOpInterface, detail::BooleanLogicOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<BooleanLogicOpInterface, detail::BooleanLogicOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BooleanLogicOpInterfaceTrait<ConcreteOp> {};

  /// Get the logical input values.
  ::mlir::ValueRange getInputs();

  /// Get the logical input at the specified index and whether it is
  /// inverted before the operation is evaluated.
  ::std::pair<::mlir::Value, bool> getInputPair(unsigned index);

  /// Get the logical input value at the specified index.
  ::mlir::Value getInput(unsigned index);

  /// Return whether the specified logical input is inverted before the
  /// operation is evaluated.
  bool isInverted(unsigned index);

  /// Get the inversion flags for all logical inputs.
  ::llvm::ArrayRef<bool> getInverted();

  /// Set the inversion flags for all logical inputs.
  void setInverted(::llvm::ArrayRef<bool> inverted);

  /// Get the primary logical result of this operation.
  ::mlir::Value getResult();

  /// Evaluate the boolean logic operation for the provided raw operand
  /// inputs. The implementations are responsible for applying any per-input
  /// inversion described by the operation itself.
  ::llvm::APInt evaluateBooleanLogic(::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue);

  /// Evaluate the boolean logic operation for the provided raw operand
  /// inputs.
  ::llvm::APInt evaluateBooleanLogic(::llvm::ArrayRef<::llvm::APInt> inputs);

  /// Compute known bits for the result from the logical inputs.
  /// The implementations are responsible for applying any per-input inversion
  /// described by the operation itself.
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);

  /// Return the abstract logic depth cost contributed by this operation.
  /// This is the per-node delay used by analyses such as longest path.
  int64_t getLogicDepthCost();

  /// Return the abstract logic area cost contributed by this operation.
  /// This is the local resource cost used by analyses such as resource
  /// usage. Implementations may return `std::nullopt` to indicate that
  /// the area cost is unknown.
  std::optional<uint64_t> getLogicAreaCost();

  /// Emit CNF clauses encoding `outVar <=> op(inputVars...)`.
  /// The provided `inputVars` correspond to this operation's operands in
  /// operand order. The default implementation materializes the per-input
  /// inversion flags into the SAT literals and then delegates to
  /// `emitCNFWithoutInversion`.
  void emitCNF(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);

  /// Clone or fold this operation with the provided inputs while preserving
  /// the existing inversion flags.
  ::mlir::Value cloneWithSameInversion(::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs);

  /// Return whether this op supports the given number of logical inputs.
  bool supportsNumInputs(unsigned numInputs);

  /// Evaluate the boolean logic operation for raw operand inputs after any
  /// per-input inversion has already been applied by the caller.
  ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);

  /// Build this boolean logic operation with the given operands and
  /// per-input inversion flags.
  ::mlir::Value createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted);

  /// Return whether the operation semantics are invariant under
  /// permutation of logical input pairs. Reordering an input means moving
  /// both the input value and its inversion flag together.
  bool areInputsPermutationInvariant();

  /// Emit CNF clauses encoding `outVar <=> op(inputVars...)` for the
  /// non-inverted form of the operation. The provided `inputVars` are SAT
  /// literals corresponding to the logical operands in operand order, after
  /// any per-input inversion has already been materialized by the caller.
  void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
};

} // namespace circt::synth
namespace circt::synth::detail {

  template <typename ConcreteOp>
  struct BooleanLogicOpInterfaceTrait : public ::mlir::OpInterface<BooleanLogicOpInterface, detail::BooleanLogicOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the logical input values.
    ::mlir::ValueRange getInputs() {
      return (*static_cast<ConcreteOp *>(this)).getOperands();
    }

    /// Get the logical input at the specified index and whether it is
    /// inverted before the operation is evaluated.
    ::std::pair<::mlir::Value, bool> getInputPair(unsigned index) {
      return {(*static_cast<ConcreteOp *>(this)).getInput(index), (*static_cast<ConcreteOp *>(this)).isInverted(index)};
    }

    /// Get the logical input value at the specified index.
    ::mlir::Value getInput(unsigned index) {
      return (*static_cast<ConcreteOp *>(this)).getInputs()[index];
    }

    /// Return whether the specified logical input is inverted before the
    /// operation is evaluated.
    bool isInverted(unsigned index) {
      return (*static_cast<ConcreteOp *>(this)).getInverted()[index];
    }

    /// Get the primary logical result of this operation.
    ::mlir::Value getResult() {
      return (*static_cast<ConcreteOp *>(this))->getResult(0);
    }

    /// Evaluate the boolean logic operation for the provided raw operand
    /// inputs. The implementations are responsible for applying any per-input
    /// inversion described by the operation itself.
    ::llvm::APInt evaluateBooleanLogic(::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) {
      ::llvm::SmallVector<::llvm::APInt, 4> adjustedInputs;
        auto inverted = (*static_cast<ConcreteOp *>(this)).getInverted();
        adjustedInputs.reserve(inverted.size());
        for (auto [index, isInverted] : llvm::enumerate(inverted)) {
          ::llvm::APInt input = getInputValue(index);
          if (isInverted)
            input.flipAllBits();
          adjustedInputs.push_back(std::move(input));
        }
        return ConcreteOp::evaluateBooleanLogicWithoutInversion(adjustedInputs);
    }

    /// Evaluate the boolean logic operation for the provided raw operand
    /// inputs.
    ::llvm::APInt evaluateBooleanLogic(::llvm::ArrayRef<::llvm::APInt> inputs) {
      auto getInputValue = [&](unsigned index) -> const ::llvm::APInt & {
          return inputs[index];
        };
        return (*static_cast<ConcreteOp *>(this)).evaluateBooleanLogic(getInputValue);
    }

    /// Return the abstract logic depth cost contributed by this operation.
    /// This is the per-node delay used by analyses such as longest path.
    int64_t getLogicDepthCost() {
      return 1;
    }

    /// Emit CNF clauses encoding `outVar <=> op(inputVars...)`.
    /// The provided `inputVars` correspond to this operation's operands in
    /// operand order. The default implementation materializes the per-input
    /// inversion flags into the SAT literals and then delegates to
    /// `emitCNFWithoutInversion`.
    void emitCNF(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
      ::llvm::SmallVector<int> inputLits;
        inputLits.reserve(inputVars.size());
        auto inverted = (*static_cast<ConcreteOp *>(this)).getInverted();
        assert(inverted.size() == inputVars.size() &&
              "inputVars should have the same size as the number of inputs");
        for (auto [inverted, inputVar] : llvm::zip(inverted, inputVars))
          inputLits.push_back(inverted ? -inputVar : inputVar);
        return ConcreteOp::emitCNFWithoutInversion(outVar, inputLits, addClause,
                                                   newVar);
    }

    /// Clone or fold this operation with the provided inputs while preserving
    /// the existing inversion flags.
    ::mlir::Value cloneWithSameInversion(::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs) {
      auto concreteOp = mlir::cast<ConcreteOp>((*static_cast<ConcreteOp *>(this)));
        assert(!newInputs.empty());
        auto resultType = newInputs.front().getType();
        return builder.createOrFold<ConcreteOp>(concreteOp.getLoc(), resultType,
                                                newInputs,
                                                concreteOp.getInverted());
    }
  };

} // namespace circt::synth::detail
namespace circt::synth {

template<typename ConcreteOp>
::mlir::ValueRange detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputs();
}
template<typename ConcreteOp>
::std::pair<::mlir::Value, bool> detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInputPair(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputPair(index);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInput(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInput(index);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::isInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isInverted(index);
}
template<typename ConcreteOp>
::llvm::ArrayRef<bool> detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInverted();
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::setInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<bool> inverted) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).setInverted(inverted);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResult();
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::evaluateBooleanLogic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).evaluateBooleanLogic(getInputValue);
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::evaluateBooleanLogic_8(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).evaluateBooleanLogic(inputs);
}
template<typename ConcreteOp>
::llvm::KnownBits detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::computeKnownBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).computeKnownBits(getInputKnownBits);
}
template<typename ConcreteOp>
int64_t detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getLogicDepthCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLogicDepthCost();
}
template<typename ConcreteOp>
std::optional<uint64_t> detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::getLogicAreaCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLogicAreaCost();
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::emitCNF(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).emitCNF(outVar, inputVars, addClause, newVar);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::cloneWithSameInversion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).cloneWithSameInversion(builder, newInputs);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::supportsNumInputs(unsigned numInputs) {
  return ConcreteOp::supportsNumInputs(numInputs);
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs) {
  return ConcreteOp::evaluateBooleanLogicWithoutInversion(inputs);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted) {
  assert(!operands.empty() && "expected at least one operand");
        return builder.createOrFold<ConcreteOp>(loc, operands.front().getType(),
                                                operands, inverted);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::areInputsPermutationInvariant() {
  return ConcreteOp::areInputsPermutationInvariant();
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::Model<ConcreteOp>::emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
  return ConcreteOp::emitCNFWithoutInversion(outVar, inputVars, addClause, newVar);
}
template<typename ConcreteOp>
::mlir::ValueRange detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInputs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInputs(tablegen_opaque_val);
}
template<typename ConcreteOp>
::std::pair<::mlir::Value, bool> detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInputPair(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return static_cast<const ConcreteOp *>(impl)->getInputPair(tablegen_opaque_val, index);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInput(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return static_cast<const ConcreteOp *>(impl)->getInput(tablegen_opaque_val, index);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, unsigned index) {
  return static_cast<const ConcreteOp *>(impl)->isInverted(tablegen_opaque_val, index);
}
template<typename ConcreteOp>
::llvm::ArrayRef<bool> detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getInverted(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::setInverted(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<bool> inverted) {
  return static_cast<const ConcreteOp *>(impl)->setInverted(tablegen_opaque_val, inverted);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getResult(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::evaluateBooleanLogic(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) {
  return static_cast<const ConcreteOp *>(impl)->evaluateBooleanLogic(tablegen_opaque_val, getInputValue);
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::evaluateBooleanLogic_8(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs) {
  return static_cast<const ConcreteOp *>(impl)->evaluateBooleanLogic_8(tablegen_opaque_val, inputs);
}
template<typename ConcreteOp>
::llvm::KnownBits detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::computeKnownBits(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits) {
  return static_cast<const ConcreteOp *>(impl)->computeKnownBits(tablegen_opaque_val, getInputKnownBits);
}
template<typename ConcreteOp>
int64_t detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getLogicDepthCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLogicDepthCost(tablegen_opaque_val);
}
template<typename ConcreteOp>
std::optional<uint64_t> detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getLogicAreaCost(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLogicAreaCost(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::emitCNF(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
  return static_cast<const ConcreteOp *>(impl)->emitCNF(tablegen_opaque_val, outVar, inputVars, addClause, newVar);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::cloneWithSameInversion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder & builder, ::mlir::ValueRange newInputs) {
  return static_cast<const ConcreteOp *>(impl)->cloneWithSameInversion(tablegen_opaque_val, builder, newInputs);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::supportsNumInputs(unsigned numInputs) {
  return ConcreteOp::supportsNumInputs(numInputs);
}
template<typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs) {
  return ConcreteOp::evaluateBooleanLogicWithoutInversion(inputs);
}
template<typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::createBooleanLogicOp(::mlir::OpBuilder & builder, ::mlir::Location loc, ::llvm::ArrayRef<::mlir::Value> operands, ::llvm::ArrayRef<bool> inverted) {
  return ConcreteOp::createBooleanLogicOp(builder, loc, operands, inverted);
}
template<typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::areInputsPermutationInvariant() {
  return ConcreteOp::areInputsPermutationInvariant();
}
template<typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) {
  return ConcreteOp::emitCNFWithoutInversion(outVar, inputVars, addClause, newVar);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::ValueRange detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInputs(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getOperands();
}
template<typename ConcreteModel, typename ConcreteOp>
::std::pair<::mlir::Value, bool> detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInputPair(::mlir::Operation *tablegen_opaque_val, unsigned index) const {
return {(llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInput(index), (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isInverted(index)};
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getInput(::mlir::Operation *tablegen_opaque_val, unsigned index) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInputs()[index];
}
template<typename ConcreteModel, typename ConcreteOp>
bool detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::isInverted(::mlir::Operation *tablegen_opaque_val, unsigned index) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInverted()[index];
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getResult(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val))->getResult(0);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::evaluateBooleanLogic(::mlir::Operation *tablegen_opaque_val, ::llvm::function_ref<const ::llvm::APInt &(unsigned)> getInputValue) const {
::llvm::SmallVector<::llvm::APInt, 4> adjustedInputs;
        auto inverted = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInverted();
        adjustedInputs.reserve(inverted.size());
        for (auto [index, isInverted] : llvm::enumerate(inverted)) {
          ::llvm::APInt input = getInputValue(index);
          if (isInverted)
            input.flipAllBits();
          adjustedInputs.push_back(std::move(input));
        }
        return ConcreteOp::evaluateBooleanLogicWithoutInversion(adjustedInputs);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::APInt detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::evaluateBooleanLogic_8(::mlir::Operation *tablegen_opaque_val, ::llvm::ArrayRef<::llvm::APInt> inputs) const {
auto getInputValue = [&](unsigned index) -> const ::llvm::APInt & {
          return inputs[index];
        };
        return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).evaluateBooleanLogic(getInputValue);
}
template<typename ConcreteModel, typename ConcreteOp>
int64_t detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getLogicDepthCost(::mlir::Operation *tablegen_opaque_val) const {
return 1;
}
template<typename ConcreteModel, typename ConcreteOp>
void detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::emitCNF(::mlir::Operation *tablegen_opaque_val, int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar) const {
::llvm::SmallVector<int> inputLits;
        inputLits.reserve(inputVars.size());
        auto inverted = (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getInverted();
        assert(inverted.size() == inputVars.size() &&
              "inputVars should have the same size as the number of inputs");
        for (auto [inverted, inputVar] : llvm::zip(inverted, inputVars))
          inputLits.push_back(inverted ? -inputVar : inputVar);
        return ConcreteOp::emitCNFWithoutInversion(outVar, inputLits, addClause,
                                                   newVar);
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::Value detail::BooleanLogicOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::cloneWithSameInversion(::mlir::Operation *tablegen_opaque_val, ::mlir::OpBuilder &builder, ::mlir::ValueRange newInputs) const {
auto concreteOp = mlir::cast<ConcreteOp>((llvm::cast<ConcreteOp>(tablegen_opaque_val)));
        assert(!newInputs.empty());
        auto resultType = newInputs.front().getType();
        return builder.createOrFold<ConcreteOp>(concreteOp.getLoc(), resultType,
                                                newInputs,
                                                concreteOp.getInverted());
}

} // namespace circt::synth
