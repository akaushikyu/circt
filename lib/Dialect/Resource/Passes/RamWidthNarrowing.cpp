

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Affine/IR/AffineMemoryOpInterfaces.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/InferIntRangeInterface.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"

#include "llvm/ADT/EquivalenceClasses.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"

#include <optional>
#include <string>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

/// Fixpoint rounds in which the stored range of an array (or the range of a
/// callee parameter) may still grow before it is set to the full range. It
/// counts rounds, not stores: any number of stores in one pass over
/// straight-line code (an unrolled loop) is one change. A recurrence through
/// memory never reaches this, its loads are full range (`cyclic`); the cap
/// only bounds the work.
constexpr unsigned kWidenAfterRounds = 8;
/// Nesting of `&&` / `||` conditions a bound is read through.
constexpr unsigned kMaxConditionDepth = 8;
/// Rounds of the demanded-bits fixpoint (it grows at most to the widths, so
/// it ends; the cap only bounds the work).
constexpr unsigned kMaxDemandRounds = 128;
/// Steps of the def-use chain the reason prints.
constexpr unsigned kMaxChainSteps = 6;

/// Bits of an integer or index value (index: 64), 0 for anything else.
unsigned bitWidthOf(Type typeValue) {
  if (auto it = dyn_cast<IntegerType>(typeValue))
    return it.getWidth();
  if (isa<IndexType>(typeValue))
    return IndexType::kInternalStorageBitWidth;
  return 0;
}

/// file:line:col (file name only) of the first file location in `loc`.
std::string shortLoc(Location loc) {
  if (auto fieldValue = dyn_cast<FileLineColLoc>(loc))
    return (llvm::sys::path::filename(fieldValue.getFilename().getValue()) +
            ":" + Twine(fieldValue.getLine()) + ":" +
            Twine(fieldValue.getColumn()))
        .str();
  if (auto elementCount = dyn_cast<NameLoc>(loc))
    return shortLoc(elementCount.getChildLoc());
  if (auto candidateValue = dyn_cast<CallSiteLoc>(loc))
    return shortLoc(candidateValue.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location lowerIndex : fu.getLocations()) {
      std::string stringValue = shortLoc(lowerIndex);
      if (stringValue != "?")
        return stringValue;
    }
  return "?";
}

/// The bits a range needs: unsigned width when no value is negative, else
/// the signed width. At least 1.
unsigned bitsForRange(const ConstantIntRanges &resultValue) {
  if (!resultValue.smin().isNegative())
    return std::max(1u, resultValue.smax().getActiveBits());
  return std::max(resultValue.smin().getSignificantBits(),
                  resultValue.smax().getSignificantBits());
}

std::string rangeText(const ConstantIntRanges &resultValue) {
  bool isSigned = resultValue.smin().isNegative();
  const APInt &lo = isSigned ? resultValue.smin() : resultValue.umin();
  const APInt &hi = isSigned ? resultValue.smax() : resultValue.umax();
  return "[" + llvm::toString(lo, 10, isSigned) + ", " +
         llvm::toString(hi, 10, isSigned) + "]";
}

/// A read or write of one memref element.
struct Access {
  Value memref;
  Value stored;
};

std::optional<Access> asAccess(Operation *op) {
  if (auto ld = dyn_cast<memref::LoadOp>(op))
    return Access{ld.getMemRef(), {}};
  if (auto st = dyn_cast<memref::StoreOp>(op))
    return Access{st.getMemRef(), st.getValueToStore()};
  if (auto st = dyn_cast<StoreEnableOp>(op))
    return Access{st.getMemref(), st.getValue()};
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(op))
    return Access{rd.getMemRef(), {}};
  if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(op))
    return Access{wr.getMemRef(), wr.getValueToStore()};
  return std::nullopt;
}

/// The subscript position of operand `operandNo` of a non-affine access, or
/// nullopt when the operand is not a subscript.
std::optional<unsigned> plainSubscriptPosition(Operation *op,
                                               unsigned operandNo) {
  unsigned first = 0;
  if (isa<memref::LoadOp>(op))
    first = 1;
  else if (isa<memref::StoreOp>(op))
    first = 2;
  else if (isa<StoreEnableOp>(op))
    first = 3;
  else
    return std::nullopt;
  if (operandNo < first)
    return std::nullopt;
  return operandNo - first;
}

bool hasDivOrMod(AffineExpr entryValue) {
  bool found = false;
  entryValue.walk([&](AffineExpr stringValue) {
    if (stringValue.getKind() == AffineExprKind::Mod ||
        stringValue.getKind() == AffineExprKind::FloorDiv ||
        stringValue.getKind() == AffineExprKind::CeilDiv)
      found = true;
  });
  return found;
}

/// Whether map operand `j` (dims first, then symbols) occurs in `e`.
bool usesOperand(AffineExpr entryValue, AffineMap map, unsigned innerIndex) {
  if (innerIndex < map.getNumDims())
    return entryValue.isFunctionOfDim(innerIndex);
  return entryValue.isFunctionOfSymbol(innerIndex - map.getNumDims());
}

struct MemClass {
  SmallVector<Operation *> roots;
  SmallVector<Operation *> loads;
  SmallVector<Operation *> stores;

  bool fixed = false;
  bool opaque = false;
  std::string fixedReason;
  Type elemType;
  unsigned declaredBits = 0;

  std::optional<ConstantIntRanges> initRange;

  IntegerValueRange stored;
  unsigned rangeChanges = 0;
  bool grewThisRound = false;
  bool rangePinned = false;
  std::string pinReason;

  bool cyclic = false;
  int scc = -1;

  bool unknownStore = false;
  unsigned demand = 0;
  bool demandPinned = false;

  Operation *widestStore = nullptr;
  unsigned widestBits = 0;
  Operation *decidingLoad = nullptr;
};

class Narrowing {
public:
  Narrowing(ModuleOp module, bool useRanges, bool useDemand, bool remarks)
      : module(module), symbols(module), partitions(module, false),
        rangesOn(useRanges), demandOn(useDemand), remarksOn(remarks) {}

  void run();

private:
  void buildClasses();
  unsigned nodeOf(const void *key);
  void trackValue(Value valueHandle, unsigned node,
                  SmallVectorImpl<std::pair<Value, unsigned>> &work);
  MemClass *classOf(Value memref) const;
  func::FuncOp internalCallee(func::CallOp callSite) const;
  bool isInternalFunction(func::FuncOp fieldValue) const;
  bool computeInternal(func::FuncOp fieldValue) const;

  void solveRanges();
  void markCyclicClasses();
  const SmallVector<unsigned, 2> &loadClassesOf(Value valueHandle);
  IntegerValueRange rangeOf(Value valueHandle);
  IntegerValueRange operandRange(OpOperand &use);
  std::optional<ConstantIntRanges>
  conditionBound(Value valueHandle, Value cond, bool holds, unsigned depth = 0);
  std::optional<ConstantIntRanges> compareBound(Value valueHandle,
                                                arith::CmpIOp cmp, bool holds);
  std::optional<APInt> constantOf(Value valueHandle);
  std::optional<std::pair<uint64_t, uint64_t>>
  smallUnsignedRange(Value valueHandle);
  IntegerValueRange blockArgRange(BlockArgument arg);
  void forwardOp(Operation *op);
  void endRound();
  std::optional<std::pair<int64_t, int64_t>>
  affineRange(AffineExpr entryValue, ValueRange dims, ValueRange syms);

  void solveDemand();
  std::pair<unsigned, Operation *> valueDemand(Value valueHandle);
  unsigned useDemand(OpOperand &use);
  unsigned resultDemand(Value resultValue) const {
    return demand.lookup(resultValue);
  }
  std::optional<unsigned> subscriptBits(Value memref, unsigned dim) const;
  std::optional<SmallVector<bool>> completeDims(Value memref) const;
  std::optional<std::pair<int64_t, int64_t>> subscriptRange(Operation *access,
                                                            unsigned dim);
  bool differentBanks(Operation *arrayValue, Operation *buildPoint);
  bool feedsBackIntoSameBank(Value valueHandle, unsigned cls, Operation *store);
  unsigned affineAccessDemand(Operation *op, OpOperand &use,
                              unsigned widthValue);

  void annotate();
  std::string demandChain(Operation *load) const;
  std::string nameOf(Value memref) const;

  ModuleOp module;
  SymbolTable symbols;
  PartitionRoots partitions;
  bool rangesOn, demandOn, remarksOn;

  llvm::EquivalenceClasses<unsigned> unionFind;
  DenseMap<const void *, unsigned> nodeIds;
  DenseMap<Value, unsigned> nodeOfValue;
  DenseMap<unsigned, std::string> opaqueNodes;
  SmallVector<Operation *> nodeRoot;
  std::vector<MemClass> classes;
  DenseMap<unsigned, unsigned> classOfLeader;

  SmallVector<Operation *> ops;

  DenseMap<Value, IntegerValueRange> ranges;
  DenseMap<Value, IntegerValueRange> paramRange;
  DenseMap<Value, unsigned> paramRangeChanges;
  DenseSet<Value> paramGrewThisRound;
  DenseSet<Value> paramRangePinned;
  bool rangesChanged = false;
  DenseMap<Value, SmallVector<unsigned, 2>> loadClasses;
  DenseMap<Operation *, SmallVector<func::CallOp>> callSites;
  mutable DenseMap<Operation *, bool> internalFunctions;

  DenseMap<Value, unsigned> demand;
  DenseMap<Value, Operation *> demandUser;
  DenseMap<Value, unsigned> paramDemand;
  DenseSet<Value> paramDemandPinned;
};

unsigned Narrowing::nodeOf(const void *key) {
  auto [it, inserted] = nodeIds.try_emplace(key, nodeIds.size());
  if (inserted) {
    unionFind.insert(it->second);
    nodeRoot.push_back(nullptr);
  }
  return it->second;
}

func::FuncOp Narrowing::internalCallee(func::CallOp callSite) const {
  auto fieldValue = symbols.lookup<func::FuncOp>(callSite.getCallee());
  if (!fieldValue || fieldValue.isExternal() || !isInternalFunction(fieldValue))
    return {};
  return fieldValue;
}

/// A private function whose every symbol use is a direct call: its parameters
/// are what the call sites pass.
bool Narrowing::isInternalFunction(func::FuncOp fieldValue) const {
  auto cached = internalFunctions.find(fieldValue);
  if (cached != internalFunctions.end())
    return cached->second;
  bool internal = computeInternal(fieldValue);
  internalFunctions[fieldValue] = internal;
  return internal;
}

bool Narrowing::computeInternal(func::FuncOp fieldValue) const {
  if (!fieldValue.isPrivate() || fieldValue.isExternal())
    return false;
  std::optional<SymbolTable::UseRange> symbolUses =
      SymbolTable::getSymbolUses(fieldValue, module);
  if (!symbolUses)
    return false;
  bool any = false;
  for (const SymbolTable::SymbolUse &useValue : *symbolUses) {
    if (!isa<func::CallOp>(useValue.getUser()))
      return false;
    any = true;
  }
  return any;
}

void Narrowing::trackValue(Value valueHandle, unsigned node,
                           SmallVectorImpl<std::pair<Value, unsigned>> &work) {
  if (nodeOfValue.try_emplace(valueHandle, node).second)
    work.push_back({valueHandle, node});
}

void Narrowing::buildClasses() {
  module.walk([&](func::CallOp callSite) {
    if (auto fieldValue = symbols.lookup<func::FuncOp>(callSite.getCallee()))
      callSites[fieldValue].push_back(callSite);
  });
  SmallVector<std::pair<Value, unsigned>> work;
  module.walk([&](Operation *op) {
    if (isa<memref::AllocaOp, memref::AllocOp>(op)) {
      unsigned elementCount = nodeOf(op);
      nodeRoot[elementCount] = op;
      trackValue(op->getResult(0), elementCount, work);
    }
  });
  for (auto g : module.getOps<memref::GlobalOp>()) {
    unsigned elementCount = nodeOf(g.getOperation());
    nodeRoot[elementCount] = g;
    if (g.isExternal())
      opaqueNodes[elementCount] = "external global";
    std::optional<SymbolTable::UseRange> symbolUses =
        SymbolTable::getSymbolUses(g, module);
    if (!symbolUses) {
      opaqueNodes[elementCount] = "symbol uses unknown";
      continue;
    }
    for (const SymbolTable::SymbolUse &useValue : *symbolUses) {
      if (auto globalUse = dyn_cast<memref::GetGlobalOp>(useValue.getUser()))
        trackValue(globalUse.getResult(), elementCount, work);
      else
        opaqueNodes[elementCount] =
            ("symbol used by " + useValue.getUser()->getName().getStringRef())
                .str();
    }
  }
  for (auto fieldValue : module.getOps<func::FuncOp>()) {
    if (fieldValue.isExternal())
      continue;
    bool internal = isInternalFunction(fieldValue);
    for (BlockArgument arrayValue : fieldValue.getArguments()) {
      if (!isa<BaseMemRefType>(arrayValue.getType()))
        continue;
      unsigned elementCount = nodeOf(arrayValue.getAsOpaquePointer());
      if (!internal)
        opaqueNodes[elementCount] = "interface (memref parameter of " +
                                    fieldValue.getSymName().str() + ")";
      trackValue(arrayValue, elementCount, work);
    }
  }

  while (!work.empty()) {
    auto [valueHandle, elementCount] = work.pop_back_val();
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (std::optional<Access> acc = asAccess(user))
        if (acc->memref == valueHandle && acc->stored != valueHandle)
          continue;
      if (auto view = dyn_cast<ViewLikeOpInterface>(user))
        if (view.getViewSource() == valueHandle) {
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()))
              trackValue(resultValue, elementCount, work);
          continue;
        }
      if (isa<memref::DimOp, memref::DeallocOp>(user))
        continue;
      if (auto callSite = dyn_cast<func::CallOp>(user))
        if (func::FuncOp callee = internalCallee(callSite)) {
          BlockArgument portValue = callee.getArgument(use.getOperandNumber());
          unionFind.unionSets(elementCount,
                              nodeOf(portValue.getAsOpaquePointer()));
          continue;
        }
      opaqueNodes[elementCount] =
          ("escapes to " + user->getName().getStringRef()).str();
    }
  }

  for (const auto *ec : unionFind) {
    if (!ec->isLeader())
      continue;
    unsigned leader = ec->getData();
    classOfLeader[leader] = classes.size();
    classes.emplace_back();
    MemClass &candidateValue = classes.back();
    for (auto memoryOp = unionFind.member_begin(*ec);
         memoryOp != unionFind.member_end(); ++memoryOp) {
      if (Operation *root = nodeRoot[*memoryOp])
        candidateValue.roots.push_back(root);
      auto o = opaqueNodes.find(*memoryOp);
      if (o != opaqueNodes.end() && !candidateValue.opaque) {
        candidateValue.opaque = candidateValue.fixed = true;
        candidateValue.fixedReason = o->second;
      }
    }
  }

  module.walk([&](Operation *op) {
    std::optional<Access> acc = asAccess(op);
    if (!acc)
      return;
    MemClass *candidateValue = classOf(acc->memref);
    if (!candidateValue)
      return;
    (acc->stored ? candidateValue->stores : candidateValue->loads)
        .push_back(op);
  });
  for (MemClass &candidateValue : classes) {
    auto setFixed = [&](const std::string &why) {
      if (!candidateValue.fixed) {
        candidateValue.fixed = true;
        candidateValue.fixedReason = why;
      }
    };
    for (Operation *root : candidateValue.roots) {
      Type elt =
          isa<memref::GlobalOp>(root)
              ? cast<memref::GlobalOp>(root).getType().getElementType()
              : cast<MemRefType>(root->getResult(0).getType()).getElementType();
      if (!candidateValue.elemType)
        candidateValue.elemType = elt;
      else if (candidateValue.elemType != elt)
        setFixed("element types differ");
      if (root->hasAttr("hls.const_fill"))
        setFixed("array written only with constants (ROM width rule)");
      auto g = dyn_cast<memref::GlobalOp>(root);
      if (!g || g.isExternal())
        continue;
      unsigned widthValue = bitWidthOf(elt);
      ConstantIntRanges initialValue =
          ConstantIntRanges::constant(APInt(widthValue ? widthValue : 1, 0));
      if (auto dimensionIndex =
              dyn_cast_or_null<DenseIntElementsAttr>(g.getInitialValueAttr())) {
        bool first = true;
        for (const APInt &valueHandle : dimensionIndex.getValues<APInt>()) {
          ConstantIntRanges resultValue =
              ConstantIntRanges::constant(valueHandle);
          initialValue =
              first ? resultValue : initialValue.rangeUnion(resultValue);
          first = false;
        }
      }
      if (widthValue)
        candidateValue.initRange =
            candidateValue.initRange
                ? candidateValue.initRange->rangeUnion(initialValue)
                : initialValue;
      if (!g.isUninitialized() && candidateValue.stores.empty())
        setFixed("initialised global never written: a ROM (ROM width rule)");
    }
    if (!candidateValue.elemType && candidateValue.roots.empty())
      continue;
    candidateValue.declaredBits =
        candidateValue.elemType ? bitWidthOf(candidateValue.elemType) : 0;
    if (!isa_and_nonnull<IntegerType>(candidateValue.elemType))
      setFixed("element type is not an integer");

    for (Operation *ld : candidateValue.loads)
      if (ld->getNumResults() != 1 ||
          ld->getResult(0).getType() != candidateValue.elemType)
        setFixed("an access moves more than one element");
    for (Operation *st : candidateValue.stores)
      if (asAccess(st)->stored.getType() != candidateValue.elemType)
        setFixed("an access moves more than one element");
  }
}

MemClass *Narrowing::classOf(Value memref) const {
  auto elementCount = nodeOfValue.find(memref);
  if (elementCount == nodeOfValue.end())
    return nullptr;
  unsigned leader = unionFind.getLeaderValue(elementCount->second);
  auto candidateValue = classOfLeader.find(leader);
  if (candidateValue == classOfLeader.end())
    return nullptr;
  return const_cast<MemClass *>(&classes[candidateValue->second]);
}

std::string Narrowing::nameOf(Value memref) const {
  MemClass *candidateValue = classOf(memref);
  if (candidateValue)
    for (Operation *root : candidateValue->roots) {
      if (auto variableName =
              root->getAttrOfType<StringAttr>("polygeist.varname"))
        return variableName.getValue().str();
      if (auto g = dyn_cast<memref::GlobalOp>(root))
        return g.getSymName().str();
    }
  if (auto arg = dyn_cast<BlockArgument>(memref))
    if (auto fieldValue = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
      return "argument " + std::to_string(arg.getArgNumber()) + " of @" +
             fieldValue.getSymName().str();
  return "<memref>";
}

std::optional<std::pair<int64_t, int64_t>>
Narrowing::affineRange(AffineExpr entryValue, ValueRange dims,
                       ValueRange syms) {
  using Range = std::pair<int64_t, int64_t>;
  auto ofValue = [&](Value valueHandle) -> std::optional<Range> {
    IntegerValueRange resultValue = rangeOf(valueHandle);
    if (resultValue.isUninitialized())
      return std::nullopt;
    const ConstantIntRanges &candidateValue = resultValue.getValue();
    if (candidateValue.smin().getSignificantBits() > 62 ||
        candidateValue.smax().getSignificantBits() > 62)
      return std::nullopt;
    return Range{candidateValue.smin().getSExtValue(),
                 candidateValue.smax().getSExtValue()};
  };
  if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
    return Range{candidateValue.getValue(), candidateValue.getValue()};
  if (auto dimensionIndex = dyn_cast<AffineDimExpr>(entryValue))
    return ofValue(dims[dimensionIndex.getPosition()]);
  if (auto stringValue = dyn_cast<AffineSymbolExpr>(entryValue))
    return ofValue(syms[stringValue.getPosition()]);
  auto bin = dyn_cast<AffineBinaryOpExpr>(entryValue);
  if (!bin)
    return std::nullopt;
  std::optional<Range> lowerIndex = affineRange(bin.getLHS(), dims, syms);
  std::optional<Range> resultValue = affineRange(bin.getRHS(), dims, syms);
  if (!lowerIndex || !resultValue)
    return std::nullopt;
  constexpr int64_t kLimit = int64_t(1) << 60;
  auto bounded = [&](Range exprValue) -> std::optional<Range> {
    if (exprValue.first < -kLimit || exprValue.second > kLimit)
      return std::nullopt;
    return exprValue;
  };
  switch (entryValue.getKind()) {
  case AffineExprKind::Add:
    return bounded({lowerIndex->first + resultValue->first,
                    lowerIndex->second + resultValue->second});
  case AffineExprKind::Mul: {
    if (std::abs(lowerIndex->first) > (1 << 30) ||
        std::abs(lowerIndex->second) > (1 << 30) ||
        std::abs(resultValue->first) > (1 << 30) ||
        std::abs(resultValue->second) > (1 << 30))
      return std::nullopt;
    int64_t portValue[] = {lowerIndex->first * resultValue->first,
                           lowerIndex->first * resultValue->second,
                           lowerIndex->second * resultValue->first,
                           lowerIndex->second * resultValue->second};
    return Range{*std::min_element(portValue, portValue + 4),
                 *std::max_element(portValue, portValue + 4)};
  }
  case AffineExprKind::FloorDiv:
  case AffineExprKind::CeilDiv: {
    if (resultValue->first != resultValue->second || resultValue->first <= 0)
      return std::nullopt;
    int64_t candidateValue = resultValue->first;
    bool ceil = entryValue.getKind() == AffineExprKind::CeilDiv;
    auto div = [&](int64_t exprValue) {
      return ceil ? llvm::divideCeilSigned(exprValue, candidateValue)
                  : llvm::divideFloorSigned(exprValue, candidateValue);
    };
    return Range{div(lowerIndex->first), div(lowerIndex->second)};
  }
  case AffineExprKind::Mod: {
    if (resultValue->first != resultValue->second || resultValue->first <= 0)
      return std::nullopt;
    if (lowerIndex->first >= 0 && lowerIndex->second < resultValue->first)
      return *lowerIndex;
    return Range{0, resultValue->first - 1};
  }
  default:
    return std::nullopt;
  }
}

IntegerValueRange Narrowing::blockArgRange(BlockArgument arg) {
  Operation *owner = arg.getOwner()->getParentOp();
  auto fromBounds = [&](std::optional<int64_t> lo,
                        std::optional<int64_t> hiExclusive, int64_t step) {
    if (!lo || !hiExclusive || step <= 0)
      return IntegerValueRange::getMaxRange(arg);
    if (*hiExclusive <= *lo)
      return IntegerValueRange();
    int64_t last = *lo + ((*hiExclusive - 1 - *lo) / step) * step;
    unsigned widthValue = bitWidthOf(arg.getType());
    return IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(widthValue, *lo, true), APInt(widthValue, last, true)));
  };
  if (auto fieldValue = dyn_cast<affine::AffineForOp>(owner)) {
    if (arg != fieldValue.getInductionVar())
      return IntegerValueRange::getMaxRange(arg);
    std::optional<int64_t> lo, hi;
    AffineMap lbMap = fieldValue.getLowerBoundMap(),
              ubMap = fieldValue.getUpperBoundMap();
    auto lbOps = fieldValue.getLowerBoundOperands(),
         ubOps = fieldValue.getUpperBoundOperands();

    for (AffineExpr entryValue : lbMap.getResults()) {
      auto resultValue = affineRange(
          entryValue, ValueRange(lbOps).take_front(lbMap.getNumDims()),
          ValueRange(lbOps).drop_front(lbMap.getNumDims()));
      if (!resultValue)
        continue;
      lo = lo ? std::max(*lo, resultValue->first) : resultValue->first;
    }
    for (AffineExpr entryValue : ubMap.getResults()) {
      auto resultValue = affineRange(
          entryValue, ValueRange(ubOps).take_front(ubMap.getNumDims()),
          ValueRange(ubOps).drop_front(ubMap.getNumDims()));
      if (!resultValue) {
        hi.reset();
        break;
      }
      hi = hi ? std::min(*hi, resultValue->second) : resultValue->second;
    }
    if (lbMap.getNumResults() == 0)
      lo.reset();

    if (!lo || !hi)
      return IntegerValueRange::getMaxRange(arg);
    if (*hi <= *lo)
      return IntegerValueRange();
    unsigned widthValue = bitWidthOf(arg.getType());
    return IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(widthValue, *lo, true), APInt(widthValue, *hi - 1, true)));
  }
  if (auto fieldValue = dyn_cast<scf::ForOp>(owner)) {
    if (arg != fieldValue.getInductionVar())
      return IntegerValueRange::getMaxRange(arg);
    std::optional<int64_t> step = getConstantIntValue(fieldValue.getStep());
    IntegerValueRange lb = rangeOf(fieldValue.getLowerBound());
    IntegerValueRange ub = rangeOf(fieldValue.getUpperBound());
    if (lb.isUninitialized() || ub.isUninitialized() || !step || *step <= 0)
      return IntegerValueRange::getMaxRange(arg);
    const ConstantIntRanges &lowerIndex = lb.getValue(),
                            &useValue = ub.getValue();
    if (lowerIndex.smin().getSignificantBits() > 62 ||
        useValue.smax().getSignificantBits() > 62)
      return IntegerValueRange::getMaxRange(arg);
    return fromBounds(lowerIndex.smin().getSExtValue(),
                      useValue.smax().getSExtValue(), 1);
  }
  if (auto fieldValue = dyn_cast<func::FuncOp>(owner)) {
    if (!isInternalFunction(fieldValue) || paramRangePinned.count(arg))
      return IntegerValueRange::getMaxRange(arg);
    auto it = paramRange.find(arg);
    return it == paramRange.end() ? IntegerValueRange() : it->second;
  }
  return IntegerValueRange::getMaxRange(arg);
}

IntegerValueRange Narrowing::rangeOf(Value valueHandle) {
  if (!bitWidthOf(valueHandle.getType()))
    return IntegerValueRange::getMaxRange(valueHandle);
  auto it = ranges.find(valueHandle);
  if (it != ranges.end())
    return it->second;
  if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
    IntegerValueRange resultValue = blockArgRange(arg);
    ranges[valueHandle] = resultValue;
    return resultValue;
  }
  return IntegerValueRange::getMaxRange(valueHandle);
}

/// The range of `use`'s value at the user: its range, narrowed by the
/// condition of every scf.if the user sits in (the else arm of
/// `x < -128 ? -128 : min(x, 127)` sees x >= -128).
IntegerValueRange Narrowing::operandRange(OpOperand &use) {
  Value valueHandle = use.get();
  IntegerValueRange resultValue = rangeOf(valueHandle);
  if (resultValue.isUninitialized())
    return resultValue;
  ConstantIntRanges cur = resultValue.getValue();
  for (Operation *at = use.getOwner(); at && !isa<func::FuncOp>(at);
       at = at->getParentOp()) {
    auto ifOp = dyn_cast_or_null<scf::IfOp>(at->getParentOp());
    if (!ifOp)
      continue;
    bool inThen = at->getParentRegion() == &ifOp.getThenRegion();
    if (std::optional<ConstantIntRanges> buildPoint =
            conditionBound(valueHandle, ifOp.getCondition(), inThen)) {
      ConstantIntRanges exprValue = cur.intersection(*buildPoint);
      if (exprValue.smin().sle(exprValue.smax()) &&
          exprValue.umin().ule(exprValue.umax()))
        cur = exprValue;
    }
  }
  return IntegerValueRange(cur);
}

/// A compile-time value of `v`: a constant op, or a range of one value.
std::optional<APInt> Narrowing::constantOf(Value valueHandle) {
  APInt candidateValue;
  if (matchPattern(valueHandle, m_ConstantInt(&candidateValue)))
    return candidateValue;
  auto it = ranges.find(valueHandle);
  if (it != ranges.end() && !it->second.isUninitialized() &&
      it->second.getValue().smin() == it->second.getValue().smax())
    return it->second.getValue().smin();
  return std::nullopt;
}

/// [umin, umax] of a value known to be non-negative and below 2^32.
std::optional<std::pair<uint64_t, uint64_t>>
Narrowing::smallUnsignedRange(Value valueHandle) {
  std::optional<ConstantIntRanges> resultValue;
  APInt candidateValue;
  if (matchPattern(valueHandle, m_ConstantInt(&candidateValue)))
    resultValue = ConstantIntRanges::constant(candidateValue);
  else if (auto it = ranges.find(valueHandle);
           it != ranges.end() && !it->second.isUninitialized())
    resultValue = it->second.getValue();
  if (!resultValue || resultValue->smin().isNegative() ||
      resultValue->umax().getActiveBits() > 32)
    return std::nullopt;
  return std::make_pair(resultValue->umin().getZExtValue(),
                        resultValue->umax().getZExtValue());
}

/// Both bounds at once; nullopt when they contradict (no value satisfies
/// both, so the code is dead and the bound is not used).
static std::optional<ConstantIntRanges>
meetBounds(std::optional<ConstantIntRanges> arrayValue,
           std::optional<ConstantIntRanges> buildPoint) {
  if (!arrayValue)
    return buildPoint;
  if (!buildPoint)
    return arrayValue;
  ConstantIntRanges exprValue = arrayValue->intersection(*buildPoint);
  if (exprValue.smin().sgt(exprValue.smax()) ||
      exprValue.umin().ugt(exprValue.umax()))
    return std::nullopt;

  APInt smin = exprValue.smin(), smax = exprValue.smax(),
        umin = exprValue.umin(), umax = exprValue.umax();
  if (!smin.isNegative()) {
    umin = llvm::APIntOps::umax(umin, smin);
    umax = llvm::APIntOps::umin(umax, smax);
  }
  if (!umax.isNegative()) {
    smin = llvm::APIntOps::smax(smin, umin);
    smax = llvm::APIntOps::smin(smax, umax);
  }
  if (smin.sgt(smax) || umin.ugt(umax))
    return std::nullopt;
  return ConstantIntRanges(umin, umax, smin, smax);
}

/// Either bound: a bound only when both sides give one.
static std::optional<ConstantIntRanges>
joinBounds(std::optional<ConstantIntRanges> arrayValue,
           std::optional<ConstantIntRanges> buildPoint) {
  if (!arrayValue || !buildPoint)
    return std::nullopt;
  return arrayValue->rangeUnion(*buildPoint);
}

/// What `cond` being `holds` says about `v`: a bound when cond compares v (or
/// v sign / zero extended) with a constant, or combines such comparisons with
/// `&&` / `||`. The front end lowers `p && q` to `scf.if p { yield q } else
/// { yield false }` and `p || q` to `scf.if p { yield true } else { yield q }`;
/// an `arith.andi` / `arith.ori` of i1s is the same. When the conjunction
/// holds, both bounds hold (Vitis narrows `x >= 0 && x < 300` to 9 bits);
/// when a disjunction holds, one of them does. nullopt: it says nothing.
std::optional<ConstantIntRanges> Narrowing::conditionBound(Value valueHandle,
                                                           Value cond,
                                                           bool holds,
                                                           unsigned depth) {
  if (depth > kMaxConditionDepth)
    return std::nullopt;
  if (auto cmp = cond.getDefiningOp<arith::CmpIOp>())
    return compareBound(valueHandle, cmp, holds);
  auto bound = [&](Value candidateValue, bool h) {
    return conditionBound(valueHandle, candidateValue, h, depth + 1);
  };

  auto combine = [&](Value lhs, Value rhs, bool isAnd) {
    if (isAnd == holds)
      return meetBounds(bound(lhs, holds), bound(rhs, holds));
    return joinBounds(bound(lhs, holds), bound(rhs, holds));
  };
  if (auto arrayValue = cond.getDefiningOp<arith::AndIOp>();
      arrayValue && arrayValue.getType().isInteger(1))
    return combine(arrayValue.getLhs(), arrayValue.getRhs(), true);
  if (auto o = cond.getDefiningOp<arith::OrIOp>();
      o && o.getType().isInteger(1))
    return combine(o.getLhs(), o.getRhs(), false);
  auto ifOp = cond.getDefiningOp<scf::IfOp>();
  if (!ifOp || ifOp.getNumResults() != 1 || ifOp.getElseRegion().empty() ||
      !cond.getType().isInteger(1))
    return std::nullopt;
  Value yThen = ifOp.thenYield().getOperand(0);
  Value yElse = ifOp.elseYield().getOperand(0);
  APInt keyValue;
  if (matchPattern(yElse, m_ConstantInt(&keyValue)) && keyValue.isZero())
    return combine(ifOp.getCondition(), yThen, true);
  if (matchPattern(yThen, m_ConstantInt(&keyValue)) && keyValue.isOne())
    return combine(ifOp.getCondition(), yElse, false);
  return std::nullopt;
}

/// What the comparison `cmp` being `holds` says about `v` (see
/// conditionBound).
std::optional<ConstantIntRanges>
Narrowing::compareBound(Value valueHandle, arith::CmpIOp cmp, bool holds) {
  using P = arith::CmpIPredicate;
  P pred = cmp.getPredicate();
  Value side = cmp.getLhs();
  std::optional<APInt> candidateValue = constantOf(cmp.getRhs());
  if (!candidateValue) {

    candidateValue = constantOf(cmp.getLhs());
    side = cmp.getRhs();
    if (!candidateValue)
      return std::nullopt;
    switch (pred) {
    case P::slt:
      pred = P::sgt;
      break;
    case P::sle:
      pred = P::sge;
      break;
    case P::sgt:
      pred = P::slt;
      break;
    case P::sge:
      pred = P::sle;
      break;
    case P::ult:
      pred = P::ugt;
      break;
    case P::ule:
      pred = P::uge;
      break;
    case P::ugt:
      pred = P::ult;
      break;
    case P::uge:
      pred = P::ule;
      break;
    default:
      break;
    }
  }
  if (!holds)
    pred = arith::invertPredicate(pred);
  bool sext = false, zext = false;
  if (side != valueHandle) {
    if (auto entryValue = side.getDefiningOp<arith::ExtSIOp>();
        entryValue && entryValue.getIn() == valueHandle)
      sext = true;
    else if (auto entryValue = side.getDefiningOp<arith::ExtUIOp>();
             entryValue && entryValue.getIn() == valueHandle)
      zext = true;
    else
      return std::nullopt;
  }
  unsigned wide = candidateValue->getBitWidth();
  bool isSigned =
      pred == P::slt || pred == P::sle || pred == P::sgt || pred == P::sge;
  APInt lo = isSigned ? APInt::getSignedMinValue(wide) : APInt::getZero(wide);
  APInt hi =
      isSigned ? APInt::getSignedMaxValue(wide) : APInt::getMaxValue(wide);
  switch (pred) {
  case P::eq:
    lo = hi = *candidateValue;
    break;
  case P::slt:
    if (candidateValue->isMinSignedValue())
      return std::nullopt;
    hi = *candidateValue - 1;
    break;
  case P::sle:
    hi = *candidateValue;
    break;
  case P::sgt:
    if (candidateValue->isMaxSignedValue())
      return std::nullopt;
    lo = *candidateValue + 1;
    break;
  case P::sge:
    lo = *candidateValue;
    break;
  case P::ult:
    if (candidateValue->isZero())
      return std::nullopt;
    hi = *candidateValue - 1;
    break;
  case P::ule:
    hi = *candidateValue;
    break;
  case P::ugt:
    if (candidateValue->isMaxValue())
      return std::nullopt;
    lo = *candidateValue + 1;
    break;
  case P::uge:
    lo = *candidateValue;
    break;
  default:
    return std::nullopt;
  }
  unsigned widthValue = bitWidthOf(valueHandle.getType());
  if (!sext && !zext)
    return isSigned || pred == P::eq ? ConstantIntRanges::fromSigned(lo, hi)
                                     : ConstantIntRanges::fromUnsigned(lo, hi);

  if (pred == P::eq)
    isSigned = sext;
  if (sext && isSigned) {
    APInt mn = APInt::getSignedMinValue(widthValue).sext(wide);
    APInt mx = APInt::getSignedMaxValue(widthValue).sext(wide);
    if (lo.slt(mn))
      lo = mn;
    if (hi.sgt(mx))
      hi = mx;
    if (lo.sgt(hi))
      return std::nullopt;
    return ConstantIntRanges::fromSigned(lo.trunc(widthValue),
                                         hi.trunc(widthValue));
  }
  if (zext && !isSigned) {
    APInt mx = APInt::getMaxValue(widthValue).zext(wide);
    if (hi.ugt(mx))
      hi = mx;
    if (lo.ugt(hi))
      return std::nullopt;
    return ConstantIntRanges::fromUnsigned(lo.trunc(widthValue),
                                           hi.trunc(widthValue));
  }
  return std::nullopt;
}

void Narrowing::forwardOp(Operation *op) {
  auto setMax = [&]() {
    for (Value resultValue : op->getResults())
      if (bitWidthOf(resultValue.getType()))
        ranges[resultValue] = IntegerValueRange::getMaxRange(resultValue);
  };

  if (std::optional<Access> acc = asAccess(op)) {
    MemClass *candidateValue = classOf(acc->memref);
    if (acc->stored) {
      if (candidateValue && !candidateValue->fixed &&
          !candidateValue->rangePinned && bitWidthOf(acc->stored.getType())) {
        IntegerValueRange resultValue = operandRange(op->getOpOperand(0));
        candidateValue->unknownStore |= resultValue.isUninitialized();
        if (!resultValue.isUninitialized()) {
          IntegerValueRange joined =
              IntegerValueRange::join(candidateValue->stored, resultValue);
          if (!(joined == candidateValue->stored)) {
            rangesChanged = true;
            candidateValue->grewThisRound = true;
            candidateValue->stored = joined;
          }
          unsigned bits = bitsForRange(resultValue.getValue());
          if (!candidateValue->widestStore ||
              bits > candidateValue->widestBits) {
            candidateValue->widestStore = op;
            candidateValue->widestBits = bits;
          }
        }
      }
      return;
    }
    if (op->getNumResults() != 1)
      return setMax();
    Value passResult = op->getResult(0);
    if (!bitWidthOf(passResult.getType()))
      return;
    if (!rangesOn || !candidateValue || candidateValue->opaque ||
        candidateValue->rangePinned || candidateValue->cyclic) {
      ranges[passResult] = IntegerValueRange::getMaxRange(passResult);
      return;
    }
    if (candidateValue->fixed) {
      ranges[passResult] = candidateValue->initRange
                               ? IntegerValueRange(*candidateValue->initRange)
                               : IntegerValueRange::getMaxRange(passResult);
      return;
    }
    ranges[passResult] = candidateValue->stored;
    return;
  }
  if (auto callSite = dyn_cast<func::CallOp>(op)) {
    if (func::FuncOp callee = internalCallee(callSite))
      for (OpOperand &operand : callSite->getOpOperands())
        if (bitWidthOf(operand.get().getType())) {
          Value portValue = callee.getArgument(operand.getOperandNumber());
          if (paramRangePinned.count(portValue))
            continue;
          IntegerValueRange &cur = paramRange[portValue];
          IntegerValueRange joined =
              IntegerValueRange::join(cur, operandRange(operand));
          if (joined == cur)
            continue;
          rangesChanged = true;
          paramGrewThisRound.insert(portValue);
          cur = joined;
        }
    return setMax();
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(op)) {
    AffineMap map = apply.getAffineMap();
    auto ops = apply.getMapOperands();
    auto resultValue = affineRange(
        map.getResult(0), ValueRange(ops).take_front(map.getNumDims()),
        ValueRange(ops).drop_front(map.getNumDims()));
    if (!resultValue)
      return setMax();
    unsigned widthValue = bitWidthOf(apply.getType());
    ranges[apply.getResult()] = IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(widthValue, resultValue->first, true),
        APInt(widthValue, resultValue->second, true)));
    return;
  }
  if (isa<scf::IfOp, affine::AffineIfOp>(op) && op->getNumResults()) {
    SmallVector<IntegerValueRange> joined(op->getNumResults());
    for (Region &region : op->getRegions())
      for (Block &buildPoint : region)
        if (Operation *term = buildPoint.getTerminator())
          for (OpOperand &valueHandle : term->getOpOperands())
            if (valueHandle.getOperandNumber() < joined.size() &&
                bitWidthOf(valueHandle.get().getType()))
              joined[valueHandle.getOperandNumber()] = IntegerValueRange::join(
                  joined[valueHandle.getOperandNumber()],
                  operandRange(valueHandle));
    for (auto [loopIndex, resultValue] : llvm::enumerate(op->getResults()))
      if (bitWidthOf(resultValue.getType()))
        ranges[resultValue] = joined[loopIndex];
    return;
  }
  if (auto sel = dyn_cast<arith::SelectOp>(op);
      sel && bitWidthOf(sel.getType())) {

    IntegerValueRange typeValue = operandRange(op->getOpOperand(1));
    IntegerValueRange fieldValue = operandRange(op->getOpOperand(2));
    auto refine = [&](IntegerValueRange resultValue, Value arm, bool holds) {
      if (resultValue.isUninitialized())
        return resultValue;
      if (std::optional<ConstantIntRanges> buildPoint =
              conditionBound(arm, sel.getCondition(), holds)) {
        ConstantIntRanges exprValue =
            resultValue.getValue().intersection(*buildPoint);
        if (exprValue.smin().sle(exprValue.smax()) &&
            exprValue.umin().ule(exprValue.umax()))
          return IntegerValueRange(exprValue);
      }
      return resultValue;
    };
    typeValue = refine(typeValue, sel.getTrueValue(), true);
    fieldValue = refine(fieldValue, sel.getFalseValue(), false);
    ranges[sel.getResult()] =
        typeValue.isUninitialized() || fieldValue.isUninitialized()
            ? IntegerValueRange()
            : IntegerValueRange::join(typeValue, fieldValue);
    return;
  }
  auto infer = dyn_cast<InferIntRangeInterface>(op);
  if (!infer || op->getNumRegions()) {
    setMax();
    return;
  }
  SmallVector<IntegerValueRange> args;
  bool bottom = false;
  for (OpOperand &operand : op->getOpOperands()) {
    if (!bitWidthOf(operand.get().getType()))
      return setMax();
    IntegerValueRange resultValue = operandRange(operand);
    bottom |= resultValue.isUninitialized();
    args.push_back(resultValue);
  }
  if (bottom) {
    for (Value resultValue : op->getResults())
      ranges[resultValue] = IntegerValueRange();
    return;
  }
  setMax();
  infer.inferResultRangesFromOptional(
      args, [&](Value valueHandle, const IntegerValueRange &resultValue) {
        if (!resultValue.isUninitialized())
          ranges[valueHandle] = resultValue;
      });
}

/// The classes whose loads `v` is computed from (through ops, scf.if arms
/// and the call sites of an internal function's parameter; not through loop
/// iter_args, which are full range anyway).
const SmallVector<unsigned, 2> &Narrowing::loadClassesOf(Value root) {

  SmallVector<std::pair<Value, bool>> stack{{root, false}};
  DenseSet<Value> onStack;
  while (!stack.empty()) {
    auto [valueHandle, expanded] = stack.pop_back_val();
    if (loadClasses.count(valueHandle))
      continue;
    SmallVector<Value> inputs;
    std::optional<unsigned> own;
    if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
      if (auto fieldValue =
              dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        if (isInternalFunction(fieldValue))
          for (func::CallOp callSite : callSites.lookup(fieldValue))
            inputs.push_back(callSite.getOperand(arg.getArgNumber()));
    } else if (Operation *def = valueHandle.getDefiningOp()) {
      if (std::optional<Access> acc = asAccess(def)) {
        if (MemClass *candidateValue = classOf(acc->memref))
          own = static_cast<unsigned>(candidateValue - classes.data());
      } else {
        inputs.append(def->operand_begin(), def->operand_end());
        if (isa<scf::IfOp, affine::AffineIfOp>(def))
          for (Region &region : def->getRegions())
            for (Block &buildPoint : region)
              if (Operation *term = buildPoint.getTerminator())
                inputs.append(term->operand_begin(), term->operand_end());
      }
    }
    if (!expanded) {
      if (!onStack.insert(valueHandle).second) {
        loadClasses[valueHandle];
        continue;
      }
      stack.push_back({valueHandle, true});
      for (Value in : inputs)
        if (!loadClasses.count(in))
          stack.push_back({in, false});
      continue;
    }
    SmallVector<unsigned, 2> set;
    if (own)
      set.push_back(*own);
    for (Value in : inputs) {
      auto it = loadClasses.find(in);
      if (it != loadClasses.end())
        set.append(it->second.begin(), it->second.end());
    }
    llvm::sort(set);
    set.erase(std::unique(set.begin(), set.end()), set.end());
    loadClasses[valueHandle] = std::move(set);
  }
  return loadClasses[root];
}

/// Vitis computes an array's stored range once, from the ranges of the
/// arrays its stored values are loaded from; it does not iterate around a
/// cycle (`a[i] = a[i + 1] ^ (a[i] >> 1)` keeps 64 bits although 32 would
/// do: w9i_self; the same expression into another array is narrowed:
/// w9i_noself). Loads of an array on a cycle of this dependence are full
/// range; masks after them still bound what is stored (w9i_selfadd: 8).
void Narrowing::markCyclicClasses() {
  unsigned elementCount = classes.size();
  std::vector<SmallVector<unsigned, 4>> succ(elementCount);
  for (auto [ci, candidateValue] : llvm::enumerate(classes))
    if (!candidateValue.fixed)
      for (Operation *st : candidateValue.stores)
        if (bitWidthOf(asAccess(st)->stored.getType()))
          for (unsigned dimensionIndex : loadClassesOf(asAccess(st)->stored))
            if (dimensionIndex != ci ||
                feedsBackIntoSameBank(asAccess(st)->stored, dimensionIndex, st))
              succ[dimensionIndex].push_back(static_cast<unsigned>(ci));

  std::vector<int> index(elementCount, -1), low(elementCount, 0);
  std::vector<bool> onStack(elementCount, false);
  SmallVector<unsigned> sccStack;
  int counter = 0;
  for (unsigned start = 0; start < elementCount; ++start) {
    if (index[start] >= 0)
      continue;
    SmallVector<std::pair<unsigned, unsigned>> work{{start, 0}};
    index[start] = low[start] = counter++;
    sccStack.push_back(start);
    onStack[start] = true;
    while (!work.empty()) {
      auto &[valueHandle, next] = work.back();
      if (next < succ[valueHandle].size()) {
        unsigned widthValue = succ[valueHandle][next++];
        if (index[widthValue] < 0) {
          index[widthValue] = low[widthValue] = counter++;
          sccStack.push_back(widthValue);
          onStack[widthValue] = true;
          work.push_back({widthValue, 0});
        } else if (onStack[widthValue]) {
          low[valueHandle] = std::min(low[valueHandle], index[widthValue]);
        }
        continue;
      }
      unsigned done = valueHandle;
      work.pop_back();
      if (!work.empty())
        low[work.back().first] = std::min(low[work.back().first], low[done]);
      if (low[done] != index[done])
        continue;
      SmallVector<unsigned> scc;
      unsigned widthValue;
      do {
        widthValue = sccStack.pop_back_val();
        onStack[widthValue] = false;
        scc.push_back(widthValue);
      } while (widthValue != done);
      bool selfLoop = llvm::is_contained(succ[done], done);
      if (scc.size() > 1 || selfLoop)
        for (unsigned memoryOp : scc) {
          classes[memoryOp].cyclic = true;
          classes[memoryOp].scc = static_cast<int>(done);
        }
    }
  }
}

/// Counts the rounds in which each range grew, and sets a range that grew in
/// more than kWidenAfterRounds rounds to the full range (pinning changes the
/// loads' ranges, so it asks for one more round).
void Narrowing::endRound() {
  for (MemClass &candidateValue : classes) {
    if (!candidateValue.grewThisRound)
      continue;
    candidateValue.grewThisRound = false;
    if (++candidateValue.rangeChanges > kWidenAfterRounds &&
        !candidateValue.rangePinned) {
      candidateValue.rangePinned = true;
      candidateValue.pinReason = "still growing after " +
                                 std::to_string(kWidenAfterRounds) + " rounds";
      rangesChanged = true;
    }
  }
  for (Value portValue : paramGrewThisRound)
    if (++paramRangeChanges[portValue] > kWidenAfterRounds &&
        paramRangePinned.insert(portValue).second)
      rangesChanged = true;
  paramGrewThisRound.clear();
}

void Narrowing::solveRanges() {
  markCyclicClasses();
  for (MemClass &candidateValue : classes) {
    if (candidateValue.fixed)
      continue;
    if (candidateValue.initRange)
      candidateValue.stored = IntegerValueRange(*candidateValue.initRange);
    else if (candidateValue.stores.empty()) {
      candidateValue.rangePinned = true;
      candidateValue.pinReason = "never written";
    }
  }

  for (bool again = true; again;) {
    do {
      rangesChanged = false;
      ranges.clear();
      for (MemClass &candidateValue : classes)
        candidateValue.unknownStore = false;
      for (Operation *op : ops)
        forwardOp(op);
      endRound();
    } while (rangesChanged);
    again = false;
    for (MemClass &candidateValue : classes)
      if (candidateValue.unknownStore && !candidateValue.rangePinned) {
        candidateValue.rangePinned = true;
        candidateValue.pinReason = "a stored value has no known range";
        again = true;
      }
  }
}

/// The low bits of a subscript at `dim` of `memref` that reach the address:
/// the bits of the flattened address of the array (without the dimensions a
/// complete partition removes), less the bits a power-of-two stride shifts
/// out. nullopt: every bit (an interface, an unknown memref, a dimension
/// split into registers, a dynamic shape).
/// Which dimensions of `memref` a complete partition splits into separate
/// memories (from the partition of the arrays of its class); nullopt when
/// the class's arrays have another shape.
std::optional<SmallVector<bool>> Narrowing::completeDims(Value memref) const {
  MemClass *candidateValue = classOf(memref);
  auto type = dyn_cast<MemRefType>(memref.getType());
  if (!candidateValue || !type)
    return std::nullopt;
  SmallVector<bool> complete(type.getRank(), false);
  for (Operation *root : candidateValue->roots)
    if (std::optional<BankLayout> lowerIndex = partitions.layoutOf(root)) {
      MemRefType rootType =
          isa<memref::GlobalOp>(root)
              ? cast<memref::GlobalOp>(root).getType()
              : cast<MemRefType>(root->getResult(0).getType());
      if (rootType.getShape() != type.getShape())
        return std::nullopt;
      for (const DimPartition &portValue : lowerIndex->dims)
        if (portValue.kind == PartitionSpec::Complete &&
            portValue.dim < complete.size())
          complete[portValue.dim] = true;
    }
  return complete;
}

/// The values the subscript at `dim` of an access can take.
std::optional<std::pair<int64_t, int64_t>>
Narrowing::subscriptRange(Operation *access, unsigned dim) {
  auto ofValue =
      [&](Value valueHandle) -> std::optional<std::pair<int64_t, int64_t>> {
    IntegerValueRange resultValue = rangeOf(valueHandle);
    if (resultValue.isUninitialized() ||
        resultValue.getValue().smin().getSignificantBits() > 62 ||
        resultValue.getValue().smax().getSignificantBits() > 62)
      return std::nullopt;
    return std::make_pair(resultValue.getValue().smin().getSExtValue(),
                          resultValue.getValue().smax().getSExtValue());
  };
  for (unsigned no = 0; no < access->getNumOperands(); ++no)
    if (plainSubscriptPosition(access, no) == dim)
      return ofValue(access->getOperand(no));
  AffineMap map;
  SmallVector<Value> operands;
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(access)) {
    map = rd.getAffineMap();
    operands = llvm::to_vector(rd.getMapOperands());
  } else if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(access)) {
    map = wr.getAffineMap();
    operands = llvm::to_vector(wr.getMapOperands());
  } else {
    return std::nullopt;
  }
  if (dim >= map.getNumResults())
    return std::nullopt;
  return affineRange(map.getResult(dim),
                     ValueRange(operands).take_front(map.getNumDims()),
                     ValueRange(operands).drop_front(map.getNumDims()));
}

/// Whether two accesses of one array reach different memories of a complete
/// partition (`t[0][k]` and `t[i][k]` with i in [1, 7]): after the split,
/// which comes before the narrowing in Vitis, they are two arrays.
bool Narrowing::differentBanks(Operation *arrayValue, Operation *buildPoint) {
  Value memref = asAccess(arrayValue)->memref;
  std::optional<SmallVector<bool>> complete = completeDims(memref);
  if (!complete || asAccess(buildPoint)->memref.getType() != memref.getType())
    return false;
  for (auto [dimensionIndex, split] : llvm::enumerate(*complete)) {
    if (!split)
      continue;
    auto ra = subscriptRange(arrayValue, dimensionIndex),
         rb = subscriptRange(buildPoint, dimensionIndex);
    if (ra && rb && (ra->second < rb->first || rb->second < ra->first))
      return true;
  }
  return false;
}

/// Whether some load of class `cls` that `v` is computed from may read the
/// memory `store` writes (see differentBanks).
bool Narrowing::feedsBackIntoSameBank(Value valueHandle, unsigned cls,
                                      Operation *store) {
  SmallVector<Value> work{valueHandle};
  DenseSet<Value> seen;
  while (!work.empty()) {
    Value exprValue = work.pop_back_val();
    if (!seen.insert(exprValue).second)
      continue;
    auto it = loadClasses.find(exprValue);
    if (it != loadClasses.end() && !llvm::is_contained(it->second, cls))
      continue;
    if (auto arg = dyn_cast<BlockArgument>(exprValue)) {
      if (auto fieldValue =
              dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        for (func::CallOp callSite : callSites.lookup(fieldValue))
          work.push_back(callSite.getOperand(arg.getArgNumber()));
      continue;
    }
    Operation *def = exprValue.getDefiningOp();
    if (!def)
      continue;
    if (std::optional<Access> acc = asAccess(def)) {
      MemClass *candidateValue = classOf(acc->memref);
      if (candidateValue &&
          static_cast<unsigned>(candidateValue - classes.data()) == cls &&
          !differentBanks(def, store))
        return true;
      continue;
    }
    work.append(def->operand_begin(), def->operand_end());
    if (isa<scf::IfOp, affine::AffineIfOp>(def))
      for (Region &region : def->getRegions())
        for (Block &buildPoint : region)
          if (Operation *term = buildPoint.getTerminator())
            work.append(term->operand_begin(), term->operand_end());
  }
  return false;
}

std::optional<unsigned> Narrowing::subscriptBits(Value memref,
                                                 unsigned dim) const {
  MemClass *candidateValue = classOf(memref);
  auto type = dyn_cast<MemRefType>(memref.getType());
  if (!candidateValue || candidateValue->opaque || !type ||
      !type.hasStaticShape() || dim >= type.getRank())
    return std::nullopt;
  std::optional<SmallVector<bool>> completeOpt = completeDims(memref);
  if (!completeOpt)
    return std::nullopt;
  SmallVector<bool> &complete = *completeOpt;
  if (complete[dim])
    return std::nullopt;
  uint64_t words = 1, stride = 1;
  for (unsigned dimensionIndex = 0; dimensionIndex < type.getRank();
       ++dimensionIndex) {
    if (complete[dimensionIndex])
      continue;
    words *= static_cast<uint64_t>(type.getDimSize(dimensionIndex));
    if (dimensionIndex > dim)
      stride *= static_cast<uint64_t>(type.getDimSize(dimensionIndex));
  }
  unsigned addrBits = llvm::Log2_64_Ceil(words);
  if (llvm::isPowerOf2_64(stride))
    return addrBits - std::min(addrBits, llvm::Log2_64(stride));
  return addrBits;
}

unsigned Narrowing::affineAccessDemand(Operation *op, OpOperand &use,
                                       unsigned widthValue) {
  AffineMap map;
  OperandRange mapOps = op->getOperands().take_front(0);
  Value memref;
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(op)) {
    map = rd.getAffineMap();
    mapOps = rd.getMapOperands();
    memref = rd.getMemRef();
  } else if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(op)) {
    map = wr.getAffineMap();
    mapOps = wr.getMapOperands();
    memref = wr.getMemRef();
  } else {
    return widthValue;
  }
  unsigned no = use.getOperandNumber();
  unsigned begin = mapOps.getBeginOperandIndex();
  if (no < begin || no >= begin + mapOps.size())
    return widthValue;
  unsigned innerIndex = no - begin;
  unsigned need = 0;
  for (auto [dimensionIndex, entryValue] : llvm::enumerate(map.getResults())) {
    if (!usesOperand(entryValue, map, innerIndex))
      continue;
    if (hasDivOrMod(entryValue))
      return widthValue;
    std::optional<unsigned> bits = subscriptBits(memref, dimensionIndex);
    if (!bits)
      return widthValue;
    need = std::max(need, *bits);
  }
  return std::min(need, widthValue);
}

unsigned Narrowing::useDemand(OpOperand &use) {
  Value valueHandle = use.get();
  unsigned widthValue = bitWidthOf(valueHandle.getType());
  if (!widthValue)
    return 0;
  Operation *user = use.getOwner();
  unsigned no = use.getOperandNumber();
  auto capped = [&](uint64_t exprValue) {
    return static_cast<unsigned>(std::min<uint64_t>(exprValue, widthValue));
  };
  auto operandRangeAt = [&](unsigned loopIndex) {
    return loopIndex < user->getNumOperands()
               ? smallUnsignedRange(user->getOperand(loopIndex))
               : std::nullopt;
  };
  auto constOperand = [&](unsigned loopIndex) -> std::optional<APInt> {
    return loopIndex < user->getNumOperands()
               ? constantOf(user->getOperand(loopIndex))
               : std::nullopt;
  };

  if (std::optional<Access> acc = asAccess(user)) {
    if (acc->stored && no == 0 && acc->stored == valueHandle) {
      MemClass *candidateValue = classOf(acc->memref);
      if (!candidateValue || candidateValue->fixed ||
          candidateValue->demandPinned)
        return widthValue;

      if (candidateValue->cyclic) {
        unsigned own = static_cast<unsigned>(candidateValue - classes.data());
        for (unsigned dimensionIndex : loadClassesOf(valueHandle))
          if (classes[dimensionIndex].scc == candidateValue->scc &&
              (dimensionIndex != own ||
               feedsBackIntoSameBank(valueHandle, dimensionIndex, user)))
            return widthValue;
      }
      return capped(candidateValue->demand);
    }
    if (std::optional<unsigned> pos = plainSubscriptPosition(user, no)) {
      std::optional<unsigned> bits = subscriptBits(acc->memref, *pos);
      return bits ? capped(*bits) : widthValue;
    }
    return affineAccessDemand(user, use, widthValue);
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(user)) {
    AffineMap map = apply.getAffineMap();
    if (hasDivOrMod(map.getResult(0)))
      return widthValue;
    return capped(resultDemand(apply.getResult()));
  }
  if (auto callSite = dyn_cast<func::CallOp>(user)) {
    func::FuncOp callee = internalCallee(callSite);
    if (!callee)
      return widthValue;
    Value portValue = callee.getArgument(no);
    if (paramDemandPinned.count(portValue))
      return widthValue;
    return capped(paramDemand.lookup(portValue));
  }
  if (isa<scf::YieldOp, affine::AffineYieldOp>(user)) {
    Operation *parent = user->getParentOp();
    if (isa<scf::IfOp, affine::AffineIfOp>(parent) &&
        no < parent->getNumResults())
      return capped(resultDemand(parent->getResult(no)));
    return widthValue;
  }
  if (user->getNumResults() != 1)
    return widthValue;
  unsigned rd = resultDemand(user->getResult(0));
  return llvm::TypeSwitch<Operation *, unsigned>(user)
      .Case<arith::AddIOp, arith::SubIOp, arith::MulIOp, arith::OrIOp,
            arith::XOrIOp>([&](auto) { return capped(rd); })
      .Case<arith::AndIOp>([&](auto) {
        if (auto memoryOp = operandRangeAt(1 - no))
          return capped(
              std::min<unsigned>(rd, 64 - llvm::countl_zero(memoryOp->second)));
        return capped(rd);
      })
      .Case<arith::ShLIOp>([&](auto) {
        auto stringValue = operandRangeAt(1);
        if (no != 0 || !stringValue)
          return widthValue;
        return capped(rd > stringValue->first ? rd - stringValue->first : 0);
      })
      .Case<arith::ShRUIOp, arith::ShRSIOp>([&](auto) {
        auto stringValue = operandRangeAt(1);
        if (no != 0 || !stringValue)
          return widthValue;
        return rd ? capped(uint64_t(rd) + stringValue->second) : 0u;
      })
      .Case<arith::RemUIOp>([&](auto) {
        std::optional<APInt> candidateValue = constOperand(1);
        if (no != 0 || !candidateValue || !candidateValue->isPowerOf2())
          return widthValue;
        return capped(std::min<unsigned>(rd, candidateValue->logBase2()));
      })
      .Case<arith::DivUIOp>([&](auto) {
        std::optional<APInt> candidateValue = constOperand(1);
        if (no != 0 || !candidateValue || !candidateValue->isPowerOf2())
          return widthValue;
        return rd ? capped(uint64_t(rd) + candidateValue->logBase2()) : 0u;
      })
      .Case<arith::TruncIOp, arith::ExtUIOp, arith::ExtSIOp, arith::IndexCastOp,
            arith::IndexCastUIOp>([&](auto) { return capped(rd); })
      .Case<arith::SelectOp>(
          [&](auto) { return no == 0 ? widthValue : capped(rd); })
      .Default([&](Operation *) { return widthValue; });
}

std::pair<unsigned, Operation *> Narrowing::valueDemand(Value valueHandle) {
  unsigned best = 0;
  Operation *by = nullptr;
  for (OpOperand &use : valueHandle.getUses()) {
    unsigned dimensionIndex = useDemand(use);
    if (dimensionIndex > best || !by) {
      best = std::max(best, dimensionIndex);
      by = use.getOwner();
    }
  }
  return {best, by};
}

void Narrowing::solveDemand() {
  for (unsigned round = 0;; ++round) {
    demand.clear();
    demandUser.clear();
    std::vector<unsigned> newDemand(classes.size(), 0);
    std::vector<Operation *> newDeciding(classes.size(), nullptr);
    for (Operation *op : llvm::reverse(ops)) {
      for (Value resultValue : op->getResults()) {
        if (!bitWidthOf(resultValue.getType()))
          continue;
        auto [dimensionIndex, by] = valueDemand(resultValue);
        demand[resultValue] = dimensionIndex;
        demandUser[resultValue] = by;
      }
      std::optional<Access> acc = asAccess(op);
      if (!acc || acc->stored || op->getNumResults() != 1)
        continue;
      MemClass *candidateValue = classOf(acc->memref);
      if (!candidateValue || candidateValue->fixed)
        continue;
      unsigned indexValue =
          static_cast<unsigned>(candidateValue - classes.data());
      unsigned dimensionIndex = demand.lookup(op->getResult(0));
      if (!newDeciding[indexValue] || dimensionIndex > newDemand[indexValue]) {
        newDemand[indexValue] = std::max(newDemand[indexValue], dimensionIndex);
        newDeciding[indexValue] = op;
      }
    }
    DenseMap<Value, unsigned> newParam;
    for (auto fieldValue : module.getOps<func::FuncOp>())
      if (isInternalFunction(fieldValue))
        for (BlockArgument arrayValue : fieldValue.getArguments())
          if (bitWidthOf(arrayValue.getType()))
            newParam[arrayValue] = valueDemand(arrayValue).first;
    bool changed = false;
    for (auto [loopIndex, candidateValue] : llvm::enumerate(classes)) {
      if (candidateValue.fixed || candidateValue.demandPinned)
        continue;
      candidateValue.decidingLoad = newDeciding[loopIndex];
      if (newDemand[loopIndex] == candidateValue.demand)
        continue;
      changed = true;
      if (round >= kMaxDemandRounds)
        candidateValue.demandPinned = true;
      else
        candidateValue.demand = newDemand[loopIndex];
    }
    for (auto &[portValue, dimensionIndex] : newParam) {
      if (paramDemandPinned.count(portValue) ||
          paramDemand.lookup(portValue) == dimensionIndex)
        continue;
      changed = true;
      if (round >= kMaxDemandRounds)
        paramDemandPinned.insert(portValue);
      else
        paramDemand[portValue] = dimensionIndex;
    }
    if (!changed)
      break;
  }
}

/// "load (k.cpp:9:40) -> arith.index_cast -> subscript of 'tbl' (64 words)".
std::string Narrowing::demandChain(Operation *load) const {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  os << load->getName().getStringRef() << " (" << shortLoc(load->getLoc())
     << ")";
  Value valueHandle = load->getResult(0);
  for (unsigned step = 0; step < kMaxChainSteps; ++step) {
    Operation *user = demandUser.lookup(valueHandle);
    if (!user)
      return os.str() + " (unused)";
    os << " -> ";
    if (std::optional<Access> acc = asAccess(user)) {
      if (acc->stored == valueHandle)
        os << "store to '" << nameOf(acc->memref) << "' ("
           << shortLoc(user->getLoc()) << ")";
      else
        os << "subscript of '" << nameOf(acc->memref) << "' ("
           << shortLoc(user->getLoc()) << ")";
      return os.str();
    }
    os << user->getName().getStringRef();
    if (auto callSite = dyn_cast<func::CallOp>(user)) {
      os << " @" << callSite.getCallee();
      return os.str();
    }
    if (user->getNumResults() != 1 ||
        isa<scf::YieldOp, affine::AffineYieldOp>(user))
      return os.str();
    valueHandle = user->getResult(0);
  }
  return os.str() + " -> ...";
}

void Narrowing::annotate() {
  for (MemClass &candidateValue : classes) {
    if (remarksOn && candidateValue.fixed)
      for (Operation *root : candidateValue.roots)
        root->emitRemark() << "narrow-ram-widths: not narrowed: "
                           << candidateValue.fixedReason;
    if (candidateValue.fixed || candidateValue.roots.empty() ||
        !candidateValue.declaredBits)
      continue;
    unsigned width = candidateValue.declaredBits;
    std::string wr = "stored values: none reach it";
    if (rangesOn) {
      if (candidateValue.rangePinned) {
        wr = "stored values: full range (" + candidateValue.pinReason + ")";
      } else if (!candidateValue.stored.isUninitialized()) {
        unsigned bits = bitsForRange(candidateValue.stored.getValue());
        wr = "stored values " + rangeText(candidateValue.stored.getValue()) +
             " need " + std::to_string(bits) + " bits";
        if (candidateValue.widestStore)
          wr += " (widest store at " +
                shortLoc(candidateValue.widestStore->getLoc()) + ")";
        width = std::min(width, bits);
      }
    } else {
      wr = "stored ranges off";
    }
    std::string wd = "loads: none used";
    if (demandOn) {
      if (candidateValue.demandPinned) {
        wd = "loads demand every bit (no fixpoint after " +
             std::to_string(kMaxDemandRounds) + " rounds)";
      } else if (candidateValue.decidingLoad && candidateValue.demand > 0) {
        wd = "loads demand " + std::to_string(candidateValue.demand) +
             " bits: " + demandChain(candidateValue.decidingLoad);
        width = std::min(width, candidateValue.demand);
      }
    } else {
      wd = "load demand off";
    }
    if (remarksOn)
      for (Operation *root : candidateValue.roots)
        root->emitRemark() << "narrow-ram-widths: " << width << " of "
                           << candidateValue.declaredBits << " bits; " << wr
                           << "; " << wd
                           << (candidateValue.cyclic ? "; on a cycle of arrays"
                                                     : "")
                           << "; " << candidateValue.stores.size()
                           << " store(s), " << candidateValue.loads.size()
                           << " load(s)";
    if (width >= candidateValue.declaredBits)
      continue;
    std::string reason = std::to_string(width) + " of " +
                         std::to_string(candidateValue.declaredBits) +
                         " bits: " + wr + "; " + wd;
    Builder buildPoint(module.getContext());
    for (Operation *root : candidateValue.roots) {
      root->setAttr(kNarrowBitsAttrName,
                    buildPoint.getI32IntegerAttr(static_cast<int32_t>(width)));
      root->setAttr(kNarrowReasonAttrName, buildPoint.getStringAttr(reason));
    }
  }
}

void Narrowing::run() {
  buildClasses();
  module.walk([&](Operation *op) {
    if (!isa<ModuleOp, func::FuncOp>(op))
      ops.push_back(op);
  });
  if (rangesOn)
    solveRanges();
  if (demandOn)
    solveDemand();
  annotate();
}

struct NarrowRamWidthsPass
    : PassWrapper<NarrowRamWidthsPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(NarrowRamWidthsPass)

  NarrowRamWidthsPass() = default;
  NarrowRamWidthsPass(const NarrowRamWidthsPass &other) : PassWrapper(other) {}

  Option<bool> storedRanges{
      *this, "stored-ranges",
      llvm::cl::desc("Narrow to the bits the stored values need"),
      llvm::cl::init(true)};
  Option<bool> loadDemand{
      *this, "load-demand",
      llvm::cl::desc("Narrow to the low bits the loads' users demand"),
      llvm::cl::init(true)};
  Option<bool> remarks{
      *this, "remarks",
      llvm::cl::desc("Emit one remark per array with its widths and why"),
      llvm::cl::init(false)};

  StringRef getArgument() const final { return "narrow-ram-widths"; }
  StringRef getDescription() const final {
    return "Mark the element width Vitis gives each local / global array: "
           "min(bits the stored values need, low bits the loads' users "
           "demand) as hls.narrow_bits (run before --memory-banking-bram)";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<arith::ArithDialect, memref::MemRefDialect>();
  }
  void runOnOperation() override {
    Narrowing(getOperation(), storedRanges, loadDemand, remarks).run();
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createNarrowRamWidthsPass() {
  return std::make_unique<NarrowRamWidthsPass>();
}
