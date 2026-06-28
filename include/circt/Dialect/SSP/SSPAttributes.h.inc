/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::ssp {

/// Internal representation of dependence edges.
/// An attribute to uniformly model def-use and auxiliary
/// [dependences](https://circt.llvm.org/docs/Scheduling/#components) as well as
/// to attach [properties](https://circt.llvm.org/docs/Scheduling/#properties)
/// to them. This attribute is an implementation detail of the `ssp.OperationOp`
/// and as such is supposed to be hidden by the custom parser/printer.
class DependenceAttr;
/// Models the `LinkedOperatorType` property in `::circt::scheduling::Problem`.
class LinkedOperatorTypeAttr;
/// Models the `LinkedResourceTypes` property in `::circt::scheduling::Problem`.
class LinkedResourceTypesAttr;
/// Models the `StartTime` property in `::circt::scheduling::Problem`.
class StartTimeAttr;
/// Models the `Latency` property in `::circt::scheduling::Problem`.
class LatencyAttr;
/// Models the `Distance` property in `::circt::scheduling::CyclicProblem`.
class DistanceAttr;
/// Models the `InitiationInterval` property in `::circt::scheduling::CyclicProblem`.
class InitiationIntervalAttr;
/// Models the `StartTimeInCycle` property in `::circt::scheduling::ChainingProblem`.
class StartTimeInCycleAttr;
/// Models the `IncomingDelay` property in `::circt::scheduling::ChainingProblem`.
class IncomingDelayAttr;
/// Models the `OutgoingDelay` property in `::circt::scheduling::ChainingProblem`.
class OutgoingDelayAttr;
/// Models the `Limit` property in `::circt::scheduling::SharedOperatorsProblem`.
class LimitAttr;
namespace detail {

struct DependenceAttrStorage;

} // namespace detail
class DependenceAttr : public ::mlir::Attribute::AttrBase<DependenceAttr, ::mlir::Attribute, detail::DependenceAttrStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "ssp.dependence";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static DependenceAttr get(::mlir::MLIRContext *context, unsigned operandIdx, ::mlir::FlatSymbolRefAttr sourceRef, ::mlir::ArrayAttr properties);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dependence"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getOperandIdx() const;
  ::mlir::FlatSymbolRefAttr getSourceRef() const;
  ::mlir::ArrayAttr getProperties() const;
};
namespace detail {

struct LinkedOperatorTypeAttrStorage;

} // namespace detail
class LinkedOperatorTypeAttr : public ::mlir::Attribute::AttrBase<LinkedOperatorTypeAttr, ::mlir::Attribute, detail::LinkedOperatorTypeAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::Problem &prob, ::mlir::Operation *op) {
    prob.setLinkedOperatorType(op,  getValue().getLeafReference() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::Problem &prob,
                                          ::mlir::Operation *op, ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getLinkedOperatorType(op)) {
      auto value = *optValue;
      return LinkedOperatorTypeAttr::get(ctx,  ::mlir::FlatSymbolRefAttr::get(ctx, value.getAttr()) );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.opr";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static LinkedOperatorTypeAttr get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"opr"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::SymbolRefAttr getValue() const;
};
namespace detail {

struct LinkedResourceTypesAttrStorage;

} // namespace detail
class LinkedResourceTypesAttr : public ::mlir::Attribute::AttrBase<LinkedResourceTypesAttr, ::mlir::Attribute, detail::LinkedResourceTypesAttrStorage> {
public:
  using Base::Base;
  static SmallVector<::circt::scheduling::Problem::ResourceType>
  arrayAttrToResourceTypes(::mlir::ArrayAttr attr) {
    SmallVector<::circt::scheduling::Problem::ResourceType> result;
    for (auto a : attr.getAsRange<::mlir::SymbolRefAttr>())
      result.push_back(::circt::scheduling::Problem::ResourceType(a.getLeafReference()));
    return result;
  }

  static ::mlir::ArrayAttr
  resourceTypesToArrayAttr(::mlir::MLIRContext *ctx,
                            ::llvm::ArrayRef<::circt::scheduling::Problem::ResourceType> rsrcs) {
    SmallVector<::mlir::Attribute> attrs;
    for (auto r : rsrcs) {
      auto value = r.getAttr().getValue();
      auto strAttr = mlir::StringAttr::get(ctx, value);
      attrs.push_back(::mlir::FlatSymbolRefAttr::get(strAttr));
    }
    return ::mlir::ArrayAttr::get(ctx, attrs);
  }

  void setInProblem(::circt::scheduling::Problem &prob, ::mlir::Operation *op) {
    SmallVector<::circt::scheduling::Problem::ResourceType> result;
    for (auto a : getValue().getAsRange<::mlir::SymbolRefAttr>()) {
      auto attr = a.getLeafReference();
      result.push_back(::circt::scheduling::Problem::ResourceType(attr));
    }
    prob.setLinkedResourceTypes(op, result);
  }

  static ::mlir::Attribute getFromProblem(::circt::scheduling::Problem &prob,
                                          ::mlir::Operation *op,
                                          ::mlir::MLIRContext *context) {
    if (auto optValue = prob.getLinkedResourceTypes(op)) {
      const SmallVector<::circt::scheduling::Problem::ResourceType> &vec = *optValue;
      return LinkedResourceTypesAttr::get(context, resourceTypesToArrayAttr(context, vec));
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.rsrcs";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static LinkedResourceTypesAttr get(::mlir::MLIRContext *context, ::mlir::ArrayAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"rsrcs"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::ArrayAttr getValue() const;
};
namespace detail {

struct StartTimeAttrStorage;

} // namespace detail
class StartTimeAttr : public ::mlir::Attribute::AttrBase<StartTimeAttr, ::mlir::Attribute, detail::StartTimeAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::Problem &prob, ::mlir::Operation *op) {
    prob.setStartTime(op,  getValue() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::Problem &prob,
                                          ::mlir::Operation *op, ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getStartTime(op)) {
      auto value = *optValue;
      return StartTimeAttr::get(ctx,  value );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.t";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static StartTimeAttr get(::mlir::MLIRContext *context, unsigned value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"t"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getValue() const;
};
namespace detail {

struct LatencyAttrStorage;

} // namespace detail
class LatencyAttr : public ::mlir::Attribute::AttrBase<LatencyAttr, ::mlir::Attribute, detail::LatencyAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::Problem &prob,
                    ::circt::scheduling::Problem::OperatorType opr) {
    prob.setLatency(opr,  getValue() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::Problem &prob,
                                          ::circt::scheduling::Problem::OperatorType opr,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getLatency(opr)) {
      auto value = *optValue;
      return LatencyAttr::get(ctx,  value );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.latency";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static LatencyAttr get(::mlir::MLIRContext *context, unsigned value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"latency"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getValue() const;
};
namespace detail {

struct DistanceAttrStorage;

} // namespace detail
class DistanceAttr : public ::mlir::Attribute::AttrBase<DistanceAttr, ::mlir::Attribute, detail::DistanceAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::CyclicProblem &prob,
                    ::circt::scheduling::Problem::Dependence dep) {
    prob.setDistance(dep,  getValue() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::CyclicProblem &prob,
                                          ::circt::scheduling::Problem::Dependence dep,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getDistance(dep)) {
      auto value = *optValue;
      return DistanceAttr::get(ctx,  value );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.dist";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static DistanceAttr get(::mlir::MLIRContext *context, unsigned value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dist"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getValue() const;
};
namespace detail {

struct InitiationIntervalAttrStorage;

} // namespace detail
class InitiationIntervalAttr : public ::mlir::Attribute::AttrBase<InitiationIntervalAttr, ::mlir::Attribute, detail::InitiationIntervalAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::CyclicProblem &prob) {
    prob.setInitiationInterval( getValue() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::CyclicProblem &prob,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getInitiationInterval()) {
      auto value = *optValue;
      return InitiationIntervalAttr::get(ctx,  value );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.II";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static InitiationIntervalAttr get(::mlir::MLIRContext *context, unsigned value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"II"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getValue() const;
};
namespace detail {

struct StartTimeInCycleAttrStorage;

} // namespace detail
class StartTimeInCycleAttr : public ::mlir::Attribute::AttrBase<StartTimeInCycleAttr, ::mlir::Attribute, detail::StartTimeInCycleAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::ChainingProblem &prob, ::mlir::Operation *op) {
    prob.setStartTimeInCycle(op,  (float) getValue().getValueAsDouble() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::ChainingProblem &prob,
                                          ::mlir::Operation *op, ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getStartTimeInCycle(op)) {
      auto value = *optValue;
      return StartTimeInCycleAttr::get(ctx,  ::mlir::FloatAttr::get(::mlir::Float32Type::get(ctx), value) );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.z";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static StartTimeInCycleAttr get(::mlir::MLIRContext *context, ::mlir::FloatAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"z"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FloatAttr getValue() const;
};
namespace detail {

struct IncomingDelayAttrStorage;

} // namespace detail
class IncomingDelayAttr : public ::mlir::Attribute::AttrBase<IncomingDelayAttr, ::mlir::Attribute, detail::IncomingDelayAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::ChainingProblem &prob,
                    ::circt::scheduling::Problem::OperatorType opr) {
    prob.setIncomingDelay(opr,  (float) getValue().getValueAsDouble() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::ChainingProblem &prob,
                                          ::circt::scheduling::Problem::OperatorType opr,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getIncomingDelay(opr)) {
      auto value = *optValue;
      return IncomingDelayAttr::get(ctx,  ::mlir::FloatAttr::get(::mlir::Float32Type::get(ctx), value) );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.incDelay";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static IncomingDelayAttr get(::mlir::MLIRContext *context, ::mlir::FloatAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"incDelay"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FloatAttr getValue() const;
};
namespace detail {

struct OutgoingDelayAttrStorage;

} // namespace detail
class OutgoingDelayAttr : public ::mlir::Attribute::AttrBase<OutgoingDelayAttr, ::mlir::Attribute, detail::OutgoingDelayAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::ChainingProblem &prob,
                    ::circt::scheduling::Problem::OperatorType opr) {
    prob.setOutgoingDelay(opr,  (float) getValue().getValueAsDouble() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::ChainingProblem &prob,
                                          ::circt::scheduling::Problem::OperatorType opr,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getOutgoingDelay(opr)) {
      auto value = *optValue;
      return OutgoingDelayAttr::get(ctx,  ::mlir::FloatAttr::get(::mlir::Float32Type::get(ctx), value) );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.outDelay";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static OutgoingDelayAttr get(::mlir::MLIRContext *context, ::mlir::FloatAttr value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"outDelay"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::FloatAttr getValue() const;
};
namespace detail {

struct LimitAttrStorage;

} // namespace detail
class LimitAttr : public ::mlir::Attribute::AttrBase<LimitAttr, ::mlir::Attribute, detail::LimitAttrStorage> {
public:
  using Base::Base;
  void setInProblem(::circt::scheduling::SharedOperatorsProblem &prob,
                    ::circt::scheduling::Problem::ResourceType rsrc) {
    prob.setLimit(rsrc,  getValue() );
  }
  static ::mlir::Attribute getFromProblem(::circt::scheduling::SharedOperatorsProblem &prob,
                                          ::circt::scheduling::Problem::ResourceType rsrc,
                                          ::mlir::MLIRContext *ctx) {
    if (auto optValue = prob.getLimit(rsrc)) {
      auto value = *optValue;
      return LimitAttr::get(ctx,  value );
    }
    return {};
  }
  static constexpr ::llvm::StringLiteral name = "ssp.limit";
  static constexpr ::llvm::StringLiteral dialectName = "ssp";
  static LimitAttr get(::mlir::MLIRContext *context, unsigned value);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"limit"};
  }

  static ::mlir::Attribute parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getValue() const;
};

} // namespace circt::ssp
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::DependenceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::LinkedOperatorTypeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::LinkedResourceTypesAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::StartTimeAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::LatencyAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::DistanceAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::InitiationIntervalAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::StartTimeInCycleAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::IncomingDelayAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::OutgoingDelayAttr)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::ssp::LimitAttr)

#endif // GET_ATTRDEF_CLASSES

