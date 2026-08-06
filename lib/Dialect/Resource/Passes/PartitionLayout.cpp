

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"

using namespace mlir;
using namespace circt::hls_analysis;

void circt::hls_analysis::parsePartitionEntries(
    ArrayAttr arr, StringRef from, SmallVectorImpl<PartitionEntry> &out) {
  if (!arr)
    return;
  for (Attribute arrayValue : arr) {
    auto dict = dyn_cast<DictionaryAttr>(arrayValue);
    if (!dict)
      continue;
    auto kindAttr = dict.getAs<StringAttr>("kind");
    if (!kindAttr)
      continue;
    PartitionEntry entryValue;
    StringRef keyValue = kindAttr.getValue();
    if (keyValue == "cyclic")
      entryValue.kind = PartitionSpec::Cyclic;
    else if (keyValue == "block")
      entryValue.kind = PartitionSpec::Block;
    else if (keyValue == "complete")
      entryValue.kind = PartitionSpec::Complete;
    else
      continue;
    if (auto fieldValue = dict.getAs<IntegerAttr>("factor"))
      entryValue.factor = fieldValue.getInt();
    if (auto dimensionIndex = dict.getAs<IntegerAttr>("dim"))
      entryValue.dim = dimensionIndex.getInt() > 0
                           ? dimensionIndex.getInt() - 1
                           : (dimensionIndex.getInt() == 0 ? -1 : 0);
    entryValue.source = dict.get("source");
    entryValue.from = from.str();
    out.push_back(entryValue);
  }
}

std::optional<BankLayout>
circt::hls_analysis::buildBankLayout(ArrayRef<PartitionEntry> entries,
                                     MemRefType memRefType) {
  int64_t rank = memRefType.getRank();
  SmallVector<std::optional<DimPartition>> best(rank);
  for (const PartitionEntry &entryValue : entries) {
    SmallVector<int64_t> dims;
    if (entryValue.dim < 0)
      for (int64_t dimensionIndex = 0; dimensionIndex < rank; ++dimensionIndex)
        dims.push_back(dimensionIndex);
    else if (entryValue.dim < rank)
      dims.push_back(entryValue.dim);
    for (int64_t dimensionIndex : dims) {
      int64_t extent = memRefType.getShape()[dimensionIndex];
      if (ShapedType::isDynamic(extent) || extent <= 1)
        continue;
      DimPartition portValue;
      portValue.dim = static_cast<unsigned>(dimensionIndex);
      portValue.kind = entryValue.kind;
      portValue.extent = extent;
      portValue.factor = entryValue.kind == PartitionSpec::Complete
                             ? extent
                             : entryValue.factor;
      if (portValue.factor > extent) {
        portValue.factor = extent;
        portValue.kind = PartitionSpec::Complete;
      }
      if (portValue.factor <= 1)
        continue;
      portValue.depth = (extent + portValue.factor - 1) / portValue.factor;
      portValue.source = entryValue.source;
      portValue.from = entryValue.from;
      if (!best[dimensionIndex] ||
          portValue.factor > best[dimensionIndex]->factor)
        best[dimensionIndex] = portValue;
    }
  }
  BankLayout layout;
  for (auto &portValue : best)
    if (portValue)
      layout.dims.push_back(*portValue);
  if (layout.dims.empty())
    return std::nullopt;
  layout.strides.assign(layout.dims.size(), 1);
  for (int64_t loopIndex = static_cast<int64_t>(layout.dims.size()) - 2;
       loopIndex >= 0; --loopIndex)
    layout.strides[loopIndex] =
        layout.strides[loopIndex + 1] * layout.dims[loopIndex + 1].factor;
  layout.numBanks = layout.strides[0] * layout.dims[0].factor;
  SmallVector<int64_t> shape(memRefType.getShape().begin(),
                             memRefType.getShape().end());
  for (const DimPartition &portValue : layout.dims)
    shape[portValue.dim] = portValue.depth;
  layout.bankType =
      MemRefType::get(shape, memRefType.getElementType(),
                      memRefType.getLayout(), memRefType.getMemorySpace());
  return layout;
}

std::pair<AffineExpr, AffineExpr>
circt::hls_analysis::bankAndOffset(AffineExpr indexValue,
                                   const DimPartition &portValue) {
  if (portValue.kind == PartitionSpec::Block)
    return {indexValue.floorDiv(portValue.depth), indexValue % portValue.depth};
  return {indexValue % portValue.factor, indexValue.floorDiv(portValue.factor)};
}

std::pair<int64_t, int64_t>
circt::hls_analysis::bankAndOffset(int64_t indexValue,
                                   const DimPartition &portValue) {
  if (portValue.kind == PartitionSpec::Block)
    return {indexValue / portValue.depth, indexValue % portValue.depth};
  return {indexValue % portValue.factor, indexValue / portValue.factor};
}

std::string circt::hls_analysis::partitionFormKey(
    ArrayRef<std::optional<BankLayout>> layouts) {
  std::string key;
  for (const std::optional<BankLayout> &lowerIndex : layouts) {
    key += "(";
    if (lowerIndex)
      for (const DimPartition &portValue : lowerIndex->dims)
        key += std::to_string(portValue.dim) + ":" +
               std::to_string(static_cast<int>(portValue.kind)) + ":" +
               std::to_string(portValue.factor) + ";";
    key += ")";
  }
  return key;
}

unsigned PartitionRoots::addNode(Node elementCount, const void *key) {
  unsigned id = nodes.size();
  nodes.push_back(std::move(elementCount));
  nodeOf[key] = id;
  badReasons.emplace_back();
  edges.emplace_back();
  return id;
}

std::optional<unsigned> PartitionRoots::nodeOfValue(Value valueHandle) const {
  if (auto it = nodeOf.find(valueHandle.getAsOpaquePointer());
      it != nodeOf.end())
    return it->second;
  if (auto globalUse = valueHandle.getDefiningOp<memref::GetGlobalOp>())
    if (Operation *globalOp = symbols.lookup(globalUse.getName()))
      if (auto it = nodeOf.find(globalOp); it != nodeOf.end())
        return it->second;
  return std::nullopt;
}

MemRefType PartitionRoots::typeOf(const Node &elementCount) const {
  if (elementCount.kind == Node::Global)
    return cast<memref::GlobalOp>(elementCount.op).getType();
  return cast<MemRefType>(elementCount.value.getType());
}

ArrayAttr PartitionRoots::specOf(const Node &elementCount) const {
  if (elementCount.kind == Node::Arg)
    return func::FuncOp(elementCount.func)
        .getArgAttrOfType<ArrayAttr>(elementCount.argNo, "hls.array_partition");
  return elementCount.op->getAttrOfType<ArrayAttr>("hls.array_partition");
}

std::string PartitionRoots::describe(const Node &elementCount) const {
  switch (elementCount.kind) {
  case Node::Alloca:
    if (auto valueHandle =
            elementCount.op->getAttrOfType<StringAttr>("polygeist.varname"))
      return "'" + valueHandle.getValue().str() + "'";
    return "a local array";
  case Node::Global:
    return "@" + cast<memref::GlobalOp>(elementCount.op).getSymName().str();
  case Node::Arg:
    return "parameter " + std::to_string(elementCount.argNo) + " of @" +
           func::FuncOp(elementCount.func).getName().str();
  }
  return "?";
}

std::optional<BankLayout>
PartitionRoots::layoutOfRootValue(Value valueHandle) const {
  std::optional<unsigned> id = nodeOfValue(valueHandle);
  if (!id || nodes[*id].kind == Node::Arg)
    return std::nullopt;
  return layoutOf(nodes[*id].op);
}

PartitionRoots::PartitionRoots(ModuleOp module, bool warn)
    : module(module), symbols(module) {

  for (auto globalOp : module.getOps<memref::GlobalOp>())
    if (globalOp.getType().hasStaticShape())
      addNode(Node{Node::Global, Value(), globalOp, func::FuncOp(), 0, {}},
              globalOp.getOperation());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      auto memRefType = dyn_cast<MemRefType>(arg.getType());
      if (memRefType && memRefType.hasStaticShape())
        addNode(Node{Node::Arg, arg, nullptr, fn, arg.getArgNumber(), {arg}},
                arg.getAsOpaquePointer());
    }
    fn.walk([&](memref::AllocaOp arrayValue) {
      if (arrayValue.getType().hasStaticShape())
        addNode(Node{Node::Alloca,
                     arrayValue.getResult(),
                     arrayValue,
                     func::FuncOp(),
                     0,
                     {arrayValue.getResult()}},
                arrayValue.getResult().getAsOpaquePointer());
    });
  });
  module.walk([&](memref::GetGlobalOp globalUse) {
    if (auto id = nodeOfValue(globalUse.getResult()))
      nodes[*id].sites.push_back(globalUse.getResult());
  });
  auto markBad = [&](unsigned id, std::string why) {
    if (badReasons[id].empty())
      badReasons[id] = std::move(why);
  };

  module.walk([&](func::CallOp callSite) {
    func::FuncOp callee = resolveDefinedCallee(callSite);
    if (callee)
      calledFuncs.insert(callee.getOperation());
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(callSite.getArgOperands())) {
      if (!isa<MemRefType>(valueHandle.getType()))
        continue;
      std::optional<unsigned> src = nodeOfValue(valueHandle);
      if (!callee || loopIndex >= callee.getNumArguments()) {
        if (src)
          markBad(*src, "passed to a function without a body (@" +
                            callSite.getCallee().str() + ")");
        continue;
      }
      std::optional<unsigned> param =
          nodeOfValue(callee.getArgument(static_cast<unsigned>(loopIndex)));
      if (src && param) {
        edges[*src].push_back(*param);
        continue;
      }
      if (param)
        markBad(*param, "given a view or a cast by a call");
      if (src)
        markBad(*src, "passed to a parameter that is not a static array");
    }
  });

  for (unsigned id = 0; id < nodes.size(); ++id)
    for (Value site : nodes[id].sites)
      for (OpOperand &use : site.getUses()) {
        Operation *user = use.getOwner();
        if (isa<affine::AffineLoadOp, memref::LoadOp, func::CallOp>(user))
          continue;
        if (auto st = dyn_cast<affine::AffineStoreOp>(user))
          if (use.getOperandNumber() == st.getMemRefOperandIndex())
            continue;
        if (auto st = dyn_cast<memref::StoreOp>(user))
          if (st.getValueToStore() != site)
            continue;
        markBad(id, "used by " + user->getName().getStringRef().str());
      }

  for (unsigned id = 0; id < nodes.size(); ++id) {
    const Node &elementCount = nodes[id];
    if (elementCount.kind == Node::Arg)
      continue;
    SmallVector<unsigned> reached;
    DenseSet<unsigned> seen{id};
    SmallVector<unsigned> work{id};
    while (!work.empty()) {
      unsigned cur = work.pop_back_val();
      for (unsigned portValue : edges[cur])
        if (seen.insert(portValue).second) {
          reached.push_back(portValue);
          work.push_back(portValue);
        }
    }
    SmallVector<PartitionEntry> entries;
    parsePartitionEntries(specOf(elementCount), "", entries);
    for (unsigned portValue : reached)
      parsePartitionEntries(specOf(nodes[portValue]),
                            describe(nodes[portValue]), entries);
    if (entries.empty())
      continue;
    MemRefType memRefType = typeOf(elementCount);
    std::optional<BankLayout> layout = buildBankLayout(entries, memRefType);
    if (!layout)
      continue;
    std::string why;
    if (!badReasons[id].empty())
      why = describe(elementCount) + " is " + badReasons[id];
    for (unsigned portValue : reached) {
      if (!why.empty())
        break;
      if (!badReasons[portValue].empty())
        why = describe(nodes[portValue]) + " is " + badReasons[portValue];
      else if (typeOf(nodes[portValue]).getShape() != memRefType.getShape())
        why = describe(nodes[portValue]) + " has another shape than " +
              describe(elementCount);
    }
    if (!why.empty()) {
      if (warn)
        elementCount.op->emitWarning("array_partition not applied: ") << why;
      continue;
    }
    rootLayout[elementCount.op] = layout;
  }
}
