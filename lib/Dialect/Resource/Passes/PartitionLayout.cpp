//===- PartitionLayout.cpp - how Vitis partitions an array ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See PartitionLayout.h. The Vitis rules (VITIS_NOTES.md N17, N20, N21, N24):
//   - every entry partitions its own dimension; entries on different
//     dimensions combine (w7_p2d, w7_prop_2d: cyclic 4 on dim 1 and cyclic 8
//     on dim 2 of int[64][64] = 32 banks of 16x8);
//   - `dim = 0` partitions every dimension (w7_dim0c: cyclic 2 dim 0 of
//     int[8][64] = 4 banks);
//   - two entries on one dimension: the larger factor wins, whatever the
//     order and whether it sits on the array or on a parameter it reaches
//     (fbh6_conf_up / fbh6_conf_down, w7_prop_conflict / w7_prop_conflict8,
//     w7_conf_gt / w7_conf_lt); for two kinds with one factor the first entry
//     is kept (unconfirmed: w7_conf_kind timed out);
//   - a cyclic / block factor beyond the dimension partitions it completely
//     (N21); a dimension past the rank is ignored (N20);
//   - a parameter's pragma partitions the caller's array (N17 (b):
//     fbh1_prop_whole, w7_prop_two: two arrays passed to one callee are both
//     partitioned; w7_prop_inline: also when Vitis inlines the callee).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"

using namespace mlir;
using namespace circt::hls_analysis;

void circt::hls_analysis::parsePartitionEntries(
    ArrayAttr arr, StringRef from, SmallVectorImpl<PartitionEntry> &out) {
  if (!arr)
    return;
  for (Attribute a : arr) {
    auto dict = dyn_cast<DictionaryAttr>(a);
    if (!dict)
      continue;
    auto kindAttr = dict.getAs<StringAttr>("kind");
    if (!kindAttr)
      continue;
    PartitionEntry e;
    StringRef k = kindAttr.getValue();
    if (k == "cyclic")
      e.kind = PartitionSpec::Cyclic;
    else if (k == "block")
      e.kind = PartitionSpec::Block;
    else if (k == "complete")
      e.kind = PartitionSpec::Complete;
    else
      continue; // unknown kind: do not guess
    if (auto f = dict.getAs<IntegerAttr>("factor"))
      e.factor = f.getInt();
    if (auto d = dict.getAs<IntegerAttr>("dim"))
      e.dim = d.getInt() > 0 ? d.getInt() - 1 : (d.getInt() == 0 ? -1 : 0);
    e.source = dict.get("source");
    if (auto r = dict.getAs<IntegerAttr>("rows"))
      e.rows = r.getInt();
    e.from = from.str();
    out.push_back(e);
  }
}

std::optional<BankLayout>
circt::hls_analysis::buildBankLayout(ArrayRef<PartitionEntry> entries,
                                     MemRefType ty) {
  int64_t rank = ty.getRank();
  SmallVector<std::optional<DimPartition>> best(rank);
  for (const PartitionEntry &e : entries) {
    SmallVector<int64_t> dims;
    if (e.dim < 0)
      for (int64_t d = 0; d < rank; ++d)
        dims.push_back(d);
    else if (e.dim < rank)
      dims.push_back(e.dim);
    for (int64_t d : dims) {
      int64_t extent = ty.getShape()[d];
      if (ShapedType::isDynamic(extent) || extent <= 1)
        continue;
      DimPartition p;
      p.dim = static_cast<unsigned>(d);
      p.kind = e.kind;
      p.extent = extent;
      p.factor = e.kind == PartitionSpec::Complete ? extent : e.factor;
      if (p.factor > extent) {
        p.factor = extent; // N21: complete
        p.kind = PartitionSpec::Complete;
      }
      if (p.factor <= 1)
        continue;
      p.depth = (extent + p.factor - 1) / p.factor;
      p.source = e.source;
      p.from = e.from;
      if (!best[d] || p.factor > best[d]->factor) // N17 (c)
        best[d] = p;
    }
  }
  BankLayout layout;
  for (auto &p : best)
    if (p)
      layout.dims.push_back(*p);
  if (layout.dims.empty())
    return std::nullopt;
  layout.strides.assign(layout.dims.size(), 1);
  for (int64_t i = static_cast<int64_t>(layout.dims.size()) - 2; i >= 0; --i)
    layout.strides[i] = layout.strides[i + 1] * layout.dims[i + 1].factor;
  layout.numBanks = layout.strides[0] * layout.dims[0].factor;
  SmallVector<int64_t> shape(ty.getShape().begin(), ty.getShape().end());
  for (const DimPartition &p : layout.dims)
    shape[p.dim] = p.depth;
  layout.bankType = MemRefType::get(shape, ty.getElementType(), ty.getLayout(),
                                    ty.getMemorySpace());
  return layout;
}

std::pair<AffineExpr, AffineExpr>
circt::hls_analysis::bankAndOffset(AffineExpr idx, const DimPartition &p) {
  if (p.kind == PartitionSpec::Block)
    return {idx.floorDiv(p.depth), idx % p.depth};
  return {idx % p.factor, idx.floorDiv(p.factor)};
}

std::pair<int64_t, int64_t>
circt::hls_analysis::bankAndOffset(int64_t idx, const DimPartition &p) {
  if (p.kind == PartitionSpec::Block)
    return {idx / p.depth, idx % p.depth};
  return {idx % p.factor, idx / p.factor};
}

std::string circt::hls_analysis::partitionFormKey(
    ArrayRef<std::optional<BankLayout>> layouts) {
  std::string key;
  for (const std::optional<BankLayout> &l : layouts) {
    key += "(";
    if (l)
      for (const DimPartition &p : l->dims)
        key += std::to_string(p.dim) + ":" +
               std::to_string(static_cast<int>(p.kind)) + ":" +
               std::to_string(p.factor) + ";";
    key += ")";
  }
  return key;
}

//===----------------------------------------------------------------------===//
// PartitionRoots
//===----------------------------------------------------------------------===//

unsigned PartitionRoots::addNode(Node n, const void *key) {
  unsigned id = nodes.size();
  nodes.push_back(std::move(n));
  nodeOf[key] = id;
  badReasons.emplace_back();
  edges.emplace_back();
  return id;
}

std::optional<unsigned> PartitionRoots::nodeOfValue(Value v) const {
  if (auto it = nodeOf.find(v.getAsOpaquePointer()); it != nodeOf.end())
    return it->second;
  if (auto gg = v.getDefiningOp<memref::GetGlobalOp>())
    if (Operation *g = symbols.lookup(gg.getName()))
      if (auto it = nodeOf.find(g); it != nodeOf.end())
        return it->second;
  return std::nullopt;
}

MemRefType PartitionRoots::typeOf(const Node &n) const {
  if (n.kind == Node::Global)
    return cast<memref::GlobalOp>(n.op).getType();
  return cast<MemRefType>(n.value.getType());
}

ArrayAttr PartitionRoots::specOf(const Node &n) const {
  if (n.kind == Node::Arg)
    return func::FuncOp(n.func).getArgAttrOfType<ArrayAttr>(
        n.argNo, "hls.array_partition");
  return n.op->getAttrOfType<ArrayAttr>("hls.array_partition");
}

std::string PartitionRoots::describe(const Node &n) const {
  switch (n.kind) {
  case Node::Alloca:
    if (auto v = n.op->getAttrOfType<StringAttr>("polygeist.varname"))
      return "'" + v.getValue().str() + "'";
    return "a local array";
  case Node::Global:
    return "@" + cast<memref::GlobalOp>(n.op).getSymName().str();
  case Node::Arg:
    return "parameter " + std::to_string(n.argNo) + " of @" +
           func::FuncOp(n.func).getName().str();
  }
  return "?";
}

std::optional<BankLayout>
PartitionRoots::layoutOfRootValue(Value v) const {
  std::optional<unsigned> id = nodeOfValue(v);
  if (!id || nodes[*id].kind == Node::Arg)
    return std::nullopt;
  return layoutOf(nodes[*id].op);
}

/// A pragma carried from a parameter with fewer rows than the root array
/// (`rows`, set by cgeist at inline time) applies one dimension deeper in
/// the root: parameter dimension d to root dimension d + 1, `dim=0` to
/// dimensions 2..rank, and what falls past the root's rank is ignored
/// (Vitis HLS 214-253; VITIS_NOTES N123, W9r16 review fixes: kernels
/// w9r16p_pm_mis / w9r16fx_pm_d2cyc ignored, w9r16rv_pm_dim1 cyclic 2 on
/// dimension 2, w9r16fx_pm_d0 complete on dimension 2).
static void shiftMismatchedEntries(SmallVectorImpl<PartitionEntry> &entries,
                                   MemRefType ty) {
  if (ty.getRank() == 0)
    return;
  const int64_t rank = ty.getRank();
  SmallVector<PartitionEntry> out;
  for (const PartitionEntry &e : entries) {
    if (!e.rows || *e.rows >= ty.getShape()[0]) {
      out.push_back(e);
      continue;
    }
    // 0-based dims: -1 (every dimension) becomes 1..rank-1, d becomes d + 1.
    if (e.dim < 0) {
      for (int64_t q = 1; q < rank; ++q) {
        PartitionEntry s = e;
        s.dim = q;
        out.push_back(s);
      }
    } else if (e.dim + 1 < rank) {
      PartitionEntry s = e;
      s.dim = e.dim + 1;
      out.push_back(s);
    }
  }
  entries.assign(out.begin(), out.end());
}

PartitionRoots::PartitionRoots(ModuleOp module, bool warn)
    : module(module), symbols(module) {
  // Nodes: globals, the static memref parameters of defined functions,
  // allocas.
  for (auto g : module.getOps<memref::GlobalOp>())
    if (g.getType().hasStaticShape())
      addNode(Node{Node::Global, Value(), g, func::FuncOp(), 0, {}},
              g.getOperation());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      auto ty = dyn_cast<MemRefType>(arg.getType());
      if (ty && ty.hasStaticShape())
        addNode(Node{Node::Arg, arg, nullptr, fn, arg.getArgNumber(), {arg}},
                arg.getAsOpaquePointer());
    }
    fn.walk([&](memref::AllocaOp a) {
      if (a.getType().hasStaticShape())
        addNode(Node{Node::Alloca, a.getResult(), a, func::FuncOp(), 0,
                     {a.getResult()}},
                a.getResult().getAsOpaquePointer());
    });
  });
  module.walk([&](memref::GetGlobalOp gg) {
    if (auto id = nodeOfValue(gg.getResult()))
      nodes[*id].sites.push_back(gg.getResult());
  });
  auto markBad = [&](unsigned id, std::string why) {
    if (badReasons[id].empty())
      badReasons[id] = std::move(why);
  };

  // Edges: an array (or a parameter) passed to a callee's parameter.
  module.walk([&](func::CallOp call) {
    func::FuncOp callee = resolveDefinedCallee(call);
    if (callee)
      calledFuncs.insert(callee.getOperation());
    for (auto [i, v] : llvm::enumerate(call.getArgOperands())) {
      if (!isa<MemRefType>(v.getType()))
        continue;
      std::optional<unsigned> src = nodeOfValue(v);
      if (!callee || i >= callee.getNumArguments()) {
        if (src)
          markBad(*src, "passed to a function without a body (@" +
                            call.getCallee().str() + ")");
        continue;
      }
      std::optional<unsigned> param =
          nodeOfValue(callee.getArgument(static_cast<unsigned>(i)));
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
  // Users the banking rewrites: loads, stores of the memref (not of it as a
  // value) and calls (through the parameters).
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

  // The partition of every root.
  for (unsigned id = 0; id < nodes.size(); ++id) {
    const Node &n = nodes[id];
    if (n.kind == Node::Arg)
      continue;
    SmallVector<unsigned> reached;
    DenseSet<unsigned> seen{id};
    SmallVector<unsigned> work{id};
    while (!work.empty()) {
      unsigned cur = work.pop_back_val();
      for (unsigned p : edges[cur])
        if (seen.insert(p).second) {
          reached.push_back(p);
          work.push_back(p);
        }
    }
    SmallVector<PartitionEntry> entries;
    parsePartitionEntries(specOf(n), "", entries);
    for (unsigned p : reached)
      parsePartitionEntries(specOf(nodes[p]), describe(nodes[p]), entries);
    MemRefType ty = typeOf(n);
    shiftMismatchedEntries(entries, ty);
    if (entries.empty())
      continue;
    std::optional<BankLayout> layout = buildBankLayout(entries, ty);
    if (!layout)
      continue;
    std::string why;
    if (!badReasons[id].empty())
      why = describe(n) + " is " + badReasons[id];
    for (unsigned p : reached) {
      if (!why.empty())
        break;
      if (!badReasons[p].empty())
        why = describe(nodes[p]) + " is " + badReasons[p];
      else if (typeOf(nodes[p]).getShape() != ty.getShape())
        why = describe(nodes[p]) + " has another shape than " + describe(n);
    }
    if (!why.empty()) {
      if (warn)
        n.op->emitWarning("array_partition not applied: ") << why;
      continue;
    }
    rootLayout[n.op] = layout;
  }
}
