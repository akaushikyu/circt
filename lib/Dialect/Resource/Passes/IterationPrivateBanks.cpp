//===- IterationPrivateBanks.cpp - banks one loop iteration owns ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Vitis keeps no memory for a bank whose elements belong to one iteration of
// an enclosing loop (VITIS_NOTES N92, kernels w9r12p_rp_*): `short X[64][64]`
// completely partitioned on dim 2, `for i { X[i][j] = 0 (j unrolled); for a
// (pipelined) X[i][col[a]] += val[a]; for j (pipelined) C[i][j] = X[i][j]; }`
// has no X in Vitis' memory table (rp_base). Each of the 64 banks is
// addressed by i alone; reflow's LICM promotes `X_j[i]` to a scalar in every
// loop nested in the i body, forwards the init store into the promoted load,
// and with no load left the stores are dead and the alloca is deleted
// (arati lab3 `local_C`: a.o.1.ll has the banks, a.o.2.ll none). A reader
// after the i loop (rp_later) or an address that changes inside the i body
// (rp_nopart, no partition: the bank is the whole array) keeps the memory.
//
// The rule, per bank of a partitioned local array (after
// --memory-banking-bram):
//   - every user is a load or store of the bank (no call, cast or view), and
//     at least one reads it;
//   - there is a loop L whose body holds every access, and every access has
//     the same address on the dimensions longer than 1, an affine function
//     of L's index and of values that do not change inside L (defined
//     outside L, or in L's body outside any loop nested in it), injective in
//     L's index: one dimension is a pure affine expression with L's index in
//     it, so two iterations never share an element;
//   - the first access in L's body (program order) is a store that is not
//     under a condition: no iteration reads a value from before it.
// Elements read in another iteration or after L are excluded by the first
// two points. The bank becomes `hls.registers`, priced 0 and port free.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/IterationPrivateBanks.h"

#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/AffineStructures.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/AffineExprVisitor.h"
#include "mlir/Interfaces/LoopLikeInterface.h"

#include "llvm/Support/raw_ostream.h"

#include <optional>
#include <string>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

/// Attribute that names the original array of a bank (set by the banking).
constexpr llvm::StringLiteral kBankOfAttr = "hls.bank_of";

/// `map` over `operands` composed with the affine.apply ops it reads,
/// restricted to the dimensions of `bank` longer than 1 (a dimension a
/// complete partition left is always 0, whatever its index computes), with
/// the operands those results do not use dropped.
affine::AffineValueMap longDimsAddress(AffineMap map,
                                       SmallVector<Value> operands,
                                       Value bank) {
  auto type = cast<MemRefType>(bank.getType());
  affine::fullyComposeAffineMapAndOperands(&map, &operands);
  SmallVector<AffineExpr> kept;
  for (unsigned d = 0; d < map.getNumResults(); ++d)
    if (d >= type.getRank() || type.getDimSize(d) != 1)
      kept.push_back(map.getResult(d));
  map = AffineMap::get(map.getNumDims(), map.getNumSymbols(), kept,
                       map.getContext());
  affine::canonicalizeMapAndOperands(&map, &operands);
  return affine::AffineValueMap(map, operands);
}

/// The address of one access of `bank` on its dimensions longer than 1, as
/// an affine map over Values.
std::optional<affine::AffineValueMap> addressOf(Operation *op, Value bank) {
  if (isa<affine::AffineReadOpInterface, affine::AffineWriteOpInterface>(op)) {
    affine::MemRefAccess access(op);
    if (access.memref != bank)
      return std::nullopt;
    affine::AffineValueMap vm;
    access.getAccessMap(&vm);
    AffineMap map = vm.getAffineMap();
    SmallVector<Value> operands(vm.getOperands().begin(),
                                vm.getOperands().end());
    return longDimsAddress(map, operands, bank);
  }
  ValueRange indices;
  if (auto ld = dyn_cast<memref::LoadOp>(op)) {
    if (ld.getMemRef() != bank)
      return std::nullopt;
    indices = ld.getIndices();
  } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
    if (st.getMemRef() != bank || st.getValueToStore() == bank)
      return std::nullopt;
    indices = st.getIndices();
  } else if (auto st = dyn_cast<StoreEnableOp>(op)) {
    if (st.getMemref() != bank || st.getValue() == bank)
      return std::nullopt;
    indices = st.getIndices();
  } else {
    return std::nullopt;
  }
  AffineMap map = AffineMap::getMultiDimIdentityMap(indices.size(),
                                                    bank.getContext());
  SmallVector<Value> operands(indices.begin(), indices.end());
  return longDimsAddress(map, operands, bank);
}

bool isStore(Operation *op) {
  return isa<affine::AffineWriteOpInterface, memref::StoreOp, StoreEnableOp>(
      op);
}

/// A store that writes whenever its block runs (no predicate operand).
bool isUnconditionalStoreOp(Operation *op) {
  return isa<affine::AffineStoreOp, memref::StoreOp>(op);
}

/// Whether `v` does not change while a loop nested in `loop` runs: L's own
/// index, or a value defined outside L or in L's body outside any nested
/// loop.
bool invariantInNestedLoops(Value v, Operation *loop) {
  Operation *def = v.getDefiningOp();
  if (!def)
    def = cast<BlockArgument>(v).getOwner()->getParentOp();
  if (!loop->isAncestor(def))
    return true;
  if (def == loop)
    return true; // L's index (or another argument of its body)
  for (Operation *p = def->getParentOp(); p && p != loop; p = p->getParentOp())
    if (isa<LoopLikeOpInterface>(p))
      return false;
  return !isa<LoopLikeOpInterface>(def);
}

/// Why `bank` is not private to one iteration of `loop` (empty: it is).
std::string checkLoop(Value bank, Operation *loop, Value iv,
                      ArrayRef<Operation *> accesses,
                      ArrayRef<affine::AffineValueMap> addresses) {
  // Every access in the body.
  for (Operation *op : accesses)
    if (!loop->isAncestor(op) || op == loop)
      return "an access outside the loop";
  // One address, invariant in nested loops.
  affine::AffineValueMap first = addresses.front();
  for (affine::AffineValueMap vm : addresses) {
    for (Value o : vm.getOperands())
      if (!invariantInNestedLoops(o, loop))
        return "an address that changes inside the loop";
    affine::AffineValueMap diff;
    affine::AffineValueMap::difference(vm, first, &diff);
    for (unsigned d = 0; d < diff.getNumResults(); ++d) {
      AffineExpr e = simplifyAffineExpr(diff.getResult(d), diff.getNumDims(),
                                        diff.getNumSymbols());
      auto c = dyn_cast<AffineConstantExpr>(e);
      if (!c || c.getValue() != 0)
        return "accesses at different addresses";
    }
  }
  // Injective in the loop's index.
  bool injective = false;
  for (unsigned d = 0; d < first.getNumResults() && !injective; ++d) {
    AffineExpr e = first.getResult(d);
    if (!e.isPureAffine())
      continue;
    for (unsigned j = 0; j < first.getNumOperands(); ++j)
      if (first.getOperand(j) == iv &&
          (j < first.getNumDims() ? e.isFunctionOfDim(j)
                                  : e.isFunctionOfSymbol(
                                        j - first.getNumDims())))
        injective = true;
  }
  if (!injective)
    return "an address that is no injective function of the loop's index";
  // The first access of an iteration writes.
  Operation *firstAccess = nullptr;
  loop->walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (op != loop && llvm::is_contained(accesses, op)) {
      firstAccess = op;
      return WalkResult::interrupt();
    }
    return WalkResult::advance();
  });
  if (!firstAccess || !isUnconditionalStoreOp(firstAccess))
    return "the first access of an iteration is no unconditional store";
  for (Operation *p = firstAccess->getParentOp(); p != loop;
       p = p->getParentOp())
    if (!isa<LoopLikeOpInterface>(p))
      return "the first store is under a condition";
  return "";
}

std::string locText(Location loc) {
  std::string s;
  llvm::raw_string_ostream os(s);
  if (auto fl = dyn_cast<FileLineColLoc>(loc))
    os << "line " << fl.getLine();
  else
    loc.print(os);
  return s;
}

/// The loop that makes `bank` iteration-private, with its location, or
/// nullopt.
std::optional<Operation *> privateLoop(Value bank) {
  SmallVector<Operation *> accesses;
  SmallVector<affine::AffineValueMap> addresses;
  for (Operation *user : bank.getUsers()) {
    std::optional<affine::AffineValueMap> a = addressOf(user, bank);
    if (!a)
      return std::nullopt; // a call, a cast, a view, a store of the bank
    accesses.push_back(user);
    addresses.push_back(*a);
  }
  // A bank no access reads is not this rule's (the kernels read every bank
  // they write; a write-only bank is left to the other rules, unconfirmed).
  if (accesses.empty() || !llvm::any_of(accesses, isStore) ||
      llvm::all_of(accesses, isStore))
    return std::nullopt;
  // Candidate loops: the enclosing loops of the first access, innermost
  // first.
  for (Operation *p = accesses.front()->getParentOp(); p;
       p = p->getParentOp()) {
    if (isa<func::FuncOp>(p))
      break;
    auto loop = dyn_cast<LoopLikeOpInterface>(p);
    if (!loop)
      continue;
    std::optional<Value> iv = loop.getSingleInductionVar();
    if (!iv)
      continue;
    if (checkLoop(bank, p, *iv, accesses, addresses).empty())
      return p;
  }
  return std::nullopt;
}

} // namespace

unsigned circt::hls_analysis::markIterationPrivateBanks(ModuleOp module) {
  unsigned marked = 0;
  module.walk([&](memref::AllocaOp alloca) {
    if (!alloca->hasAttr(kBankOfAttr) || alloca->hasAttr(kRegistersAttrName))
      return;
    auto type = alloca.getType();
    if (!type.hasStaticShape() || type.getNumElements() <= 1)
      return;
    std::optional<Operation *> loop = privateLoop(alloca.getResult());
    if (!loop)
      return;
    OpBuilder b(alloca);
    alloca->setAttr(kRegistersAttrName, b.getUnitAttr());
    alloca->setAttr(
        kRegistersReasonAttrName,
        b.getStringAttr("iteration-private element (VITIS_NOTES N92): every "
                        "access in the loop at " +
                        locText((*loop)->getLoc()) +
                        " at one address of its index, first written in the "
                        "iteration; Vitis promotes it to a scalar and "
                        "deletes the array"));
    ++marked;
  });
  return marked;
}
