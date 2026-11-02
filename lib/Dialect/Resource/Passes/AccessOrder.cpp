//===- AccessOrder.cpp - Address and order relations of accesses ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Moved from BRAMAnalysis.cpp (P2: the port model and the memory-architecture
// policy plugins share them).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/Support/raw_ostream.h"

using namespace mlir;
using namespace circt::hls_analysis;

// v = base + offset with a constant offset (base null: v is a constant),
// through arith.addi / arith.subi with a constant operand, i.e. the lowered
// form of an affine index `d0 + c`.
std::pair<Value, int64_t> circt::hls_analysis::splitConstantOffset(Value v) {
  int64_t off = 0;
  for (unsigned guard = 0; guard < 64; ++guard) {
    if (std::optional<int64_t> c = getConstantIntValue(v))
      return {Value(), off + *c};
    if (auto add = v.getDefiningOp<arith::AddIOp>()) {
      if (std::optional<int64_t> c = getConstantIntValue(add.getRhs())) {
        off += *c;
        v = add.getLhs();
        continue;
      }
      if (std::optional<int64_t> c = getConstantIntValue(add.getLhs())) {
        off += *c;
        v = add.getRhs();
        continue;
      }
    }
    if (auto sub = v.getDefiningOp<arith::SubIOp>())
      if (std::optional<int64_t> c = getConstantIntValue(sub.getRhs())) {
        off -= *c;
        v = sub.getLhs();
        continue;
      }
    break;
  }
  return {v, off};
}


// Address relation of two accesses of one bank: Disjoint when some dimension
// is base + c1 vs. base + c2 with c1 != c2, Same when every dimension is the
// same base + c. Anything that is not a plain memref.load / memref.store
// (hls.store_enable, another op with memory effects) is Unknown.
AddrRelation circt::hls_analysis::compareAddresses(Operation *a,
                                                  Operation *b) {
  auto indices = [](Operation *op) -> std::optional<SmallVector<Value, 4>> {
    if (auto l = dyn_cast<memref::LoadOp>(op))
      return SmallVector<Value, 4>(l.getIndices());
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return SmallVector<Value, 4>(st.getIndices());
    return std::nullopt;
  };
  auto ia = indices(a), ib = indices(b);
  if (!ia || !ib || ia->size() != ib->size())
    return AddrRelation::Unknown;
  bool same = true;
  for (auto [x, y] : llvm::zip(*ia, *ib)) {
    if (x == y)
      continue;
    auto [bx, ox] = splitConstantOffset(x);
    auto [by, oy] = splitConstantOffset(y);
    if (bx == by) {
      if (ox != oy)
        return AddrRelation::Disjoint;
      continue;
    }
    same = false;
  }
  return same ? AddrRelation::Same : AddrRelation::Unknown;
}

// The storage a memref value names, for the memory order between the ops of a
// stretch: views are followed to their source, every get_global of one global
// is that global, and an alloc / alloca / function argument is its own storage
// (every top-level array is its own memory in Vitis). Null: produced by
// something else, may be any storage.
static const void *storageKey(Value v) {
  for (unsigned guard = 0; guard < 64; ++guard) {
    auto view = v.getDefiningOp<ViewLikeOpInterface>();
    if (!view)
      break;
    v = view.getViewSource();
  }
  if (auto g = v.getDefiningOp<memref::GetGlobalOp>())
    return g.getNameAttr().getAttr().getAsOpaquePointer();
  if (v.getDefiningOp<memref::AllocaOp>() || v.getDefiningOp<memref::AllocOp>())
    return v.getAsOpaquePointer();
  if (auto arg = dyn_cast<BlockArgument>(v))
    if (arg.getOwner()->isEntryBlock() &&
        isa<FunctionOpInterface>(arg.getOwner()->getParentOp()))
      return v.getAsOpaquePointer();
  return nullptr;
}


// What `op` reads and writes. An op without MemoryEffectOpInterface, a call,
// and an effect on no memref value may write any storage. An if has no
// effects of its own here: its arms are ops of the stretch themselves.
void circt::hls_analysis::memTouches(Operation *op,
                                     SmallVectorImpl<MemTouch> &out) {
  if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
    return;
  auto iface = dyn_cast<MemoryEffectOpInterface>(op);
  if (!iface || isa<CallOpInterface>(op)) {
    out.push_back({nullptr, Value(), true});
    return;
  }
  SmallVector<MemoryEffects::EffectInstance, 2> effects;
  iface.getEffects(effects);
  for (const MemoryEffects::EffectInstance &e : effects) {
    if (isa<MemoryEffects::Allocate>(e.getEffect()))
      continue;
    bool write = !isa<MemoryEffects::Read>(e.getEffect());
    Value v = e.getValue();
    if (!v || !isa<BaseMemRefType>(v.getType()))
      out.push_back({nullptr, Value(), write});
    else
      out.push_back({storageKey(v), v, write});
  }
}

// Whether two memory effects (of ops `a` before `b`) are ordered: one of them
// writes and the storage may be the same. Two plain loads / stores of one
// memref value at provably different addresses are not.
bool circt::hls_analysis::mayConflict(Operation *a, const MemTouch &ta,
                                      Operation *b, const MemTouch &tb) {
  if (!ta.write && !tb.write)
    return false;
  if (ta.key && tb.key && ta.key != tb.key)
    return false;
  if (ta.memref && ta.memref == tb.memref &&
      compareAddresses(a, b) == AddrRelation::Disjoint)
    return false;
  return true;
}

// Whether two ops of a stretch lie in different arms of one if: nested in them
// (`arms`), or hoisted out of them by --convert-affine-to-loopschedule
// (`hoisted`, the hls.if_arms list [if id, arm, ...]).
bool circt::hls_analysis::inExclusiveArms(const SeqScopeIndex::OpInfo &x,
                                          ArrayRef<int64_t> hoistedX,
                                          const SeqScopeIndex::OpInfo &y,
                                          ArrayRef<int64_t> hoistedY) {
  for (const auto &ax : x.arms)
    for (const auto &ay : y.arms)
      if (ax.first == ay.first && ax.second != ay.second)
        return true;
  for (size_t a = 0; a + 1 < hoistedX.size(); a += 2)
    for (size_t b = 0; b + 1 < hoistedY.size(); b += 2)
      if (hoistedX[a] == hoistedY[b] && hoistedX[a + 1] != hoistedY[b + 1])
        return true;
  return false;
}

ArrayRef<int64_t> circt::hls_analysis::hoistedArmsOf(Operation *op) {
  if (auto a = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr))
    return a.asArrayRef();
  return {};
}

std::string circt::hls_analysis::accessText(const AccessSummary *a) {
  std::string s;
  llvm::raw_string_ostream os(s);
  os << a->op->getName() << " @ ";
  a->op->getLoc().print(os);
  return s;
}

// First file:line:col reachable through fused / named / call-site wrappers.
FileLineColLoc circt::hls_analysis::findFileLoc(Location loc) {
  if (auto f = dyn_cast<FileLineColLoc>(loc))
    return f;
  if (auto n = dyn_cast<NameLoc>(loc))
    return findFileLoc(n.getChildLoc());
  if (auto c = dyn_cast<CallSiteLoc>(loc))
    return findFileLoc(c.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location l : fu.getLocations())
      if (auto f = findFileLoc(l))
        return f;
  if (auto o = dyn_cast<OpaqueLoc>(loc))
    return findFileLoc(o.getFallbackLocation());
  return {};
}

std::string circt::hls_analysis::locString(Location loc) {
  if (auto f = findFileLoc(loc))
    return (f.getFilename().str() + ":" + std::to_string(f.getLine()) + ":" +
            std::to_string(f.getColumn()));
  if (isa<UnknownLoc>(loc))
    return "<unknown>";
  std::string s;
  llvm::raw_string_ostream os(s);
  loc.print(os);
  return s;
}


// Classify an op's effect on `mem`. Works for memref.load/store, affine
// load/store, or any op exposing memory effects; non-accessing aliasing ops
// (subview, cast, dealloc) report no read/write effect and are skipped.
bool circt::hls_analysis::classifyAccess(Operation *op, Value mem,
                                         bool &isWrite) {
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff)
    return false;
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  bool reads = false, writes = false;
  for (auto &e : effects) {
    if (e.getValue() && e.getValue() != mem)
      continue;
    if (isa<MemoryEffects::Read>(e.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(e.getEffect()))
      writes = true;
  }
  if (!reads && !writes)
    return false;
  isWrite = writes; // a read-modify-write op needs a write port
  return true;
}

