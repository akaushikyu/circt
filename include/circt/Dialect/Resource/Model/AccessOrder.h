//===- AccessOrder.h - Address and order relations of accesses -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// IR analyses of the accesses of one bank that the port model and the
// memory-architecture policies share: whether two accesses name the same or
// provably different addresses, what an op reads and writes, whether two
// effects are ordered, and whether two ops lie in different arms of one if.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_MODEL_ACCESSORDER_H
#define CIRCT_DIALECT_RESOURCE_MODEL_ACCESSORDER_H

#include "circt/Dialect/Resource/Model/MemoryModel.h"

#include "mlir/IR/Location.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"

#include <string>
#include <utility>

namespace circt::hls_analysis {

/// v = base + offset with a constant offset (base null: v is a constant),
/// through arith.addi / arith.subi with a constant operand, i.e. the lowered
/// form of an affine index `d0 + c`.
std::pair<mlir::Value, int64_t> splitConstantOffset(mlir::Value v);

enum class AddrRelation { Same, Disjoint, Unknown };

/// Address relation of two accesses of one bank: Disjoint when some
/// dimension is base + c1 vs. base + c2 with c1 != c2, Same when every
/// dimension is the same base + c. Anything that is not a plain memref.load /
/// memref.store is Unknown.
AddrRelation compareAddresses(mlir::Operation *a, mlir::Operation *b);

/// What `op` reads and writes. An op without MemoryEffectOpInterface, a call,
/// and an effect on no memref value may write any storage. An if has no
/// effects of its own: its arms are ops of the stretch themselves.
void memTouches(mlir::Operation *op, llvm::SmallVectorImpl<MemTouch> &out);

/// Whether two memory effects (of ops `a` before `b`) are ordered: one of
/// them writes and the storage may be the same. Two plain loads / stores of
/// one memref value at provably different addresses are not.
bool mayConflict(mlir::Operation *a, const MemTouch &ta, mlir::Operation *b,
                 const MemTouch &tb);

/// Whether two ops of a stretch lie in different arms of one if: nested in
/// them (`arms`), or hoisted out of them by --convert-affine-to-loopschedule
/// (`hoisted`, the hls.if_arms list [if id, arm, ...]).
bool inExclusiveArms(const SeqScopeIndex::OpInfo &x,
                     llvm::ArrayRef<int64_t> hoistedX,
                     const SeqScopeIndex::OpInfo &y,
                     llvm::ArrayRef<int64_t> hoistedY);

/// The hls.if_arms list of `op` (empty when it was not hoisted out of an if).
llvm::ArrayRef<int64_t> hoistedArmsOf(mlir::Operation *op);

/// "<op name> @ <location>" of an access, for the reports.
std::string accessText(const AccessSummary *a);

/// The first file:line:col reachable through fused / named / call-site
/// wrappers (null when there is none).
mlir::FileLineColLoc findFileLoc(mlir::Location loc);

/// "file:line:col" of `loc`, "<unknown>", or the printed location.
std::string locString(mlir::Location loc);

/// The effect of `op` on `mem`: false when it neither reads nor writes it
/// (views, casts, deallocs); else `isWrite` (a read-modify-write needs a write
/// port).
bool classifyAccess(mlir::Operation *op, mlir::Value mem, bool &isWrite);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_MODEL_ACCESSORDER_H
