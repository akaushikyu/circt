//===- PartitionLayout.h - how Vitis partitions an array --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The partition of every storage root (memref.alloca / memref.global) of a
// module, from its own `hls.array_partition` pragma and the pragmas of the
// callee parameters it is passed to (VITIS_NOTES.md N17 (b), N24). Shared by
// --memory-banking-bram, which splits the arrays, and
// --dead-memory-elimination, which needs the partitions to tell which call
// sites of a non-inlined callee Vitis turns into one function (N14 R4).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_PARTITIONLAYOUT_H
#define CIRCT_DIALECT_RESOURCE_PASSES_PARTITIONLAYOUT_H

#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"

#include <optional>
#include <string>

namespace circt::hls_analysis {

/// One `hls.array_partition` entry as written. `dim` is 0-based; -1 means
/// every dimension (Vitis `dim = 0`).
struct PartitionEntry {
  int64_t dim = 0;
  PartitionSpec::Kind kind = PartitionSpec::Cyclic;
  int64_t factor = 1;
  mlir::Attribute source; // the entry's `source` field ("pragma" if absent)
  std::string from;       // the callee parameter that carries it ("" = own)
};

/// How one dimension is split.
struct DimPartition {
  unsigned dim = 0; // 0-based
  PartitionSpec::Kind kind = PartitionSpec::Cyclic; // complete: f = extent
  int64_t factor = 1;                               // banks along the dim
  int64_t extent = 1;
  int64_t depth = 1; // words of one bank along the dim: ceil(extent / f)
  mlir::Attribute source;
  std::string from;
};

/// The banks of one array: the split dimensions in ascending order, the
/// row-major bank-index strides over them and the type of one bank.
struct BankLayout {
  llvm::SmallVector<DimPartition> dims;
  llvm::SmallVector<int64_t> strides; // bank index = sum(bank_d * strides[d])
  int64_t numBanks = 1;
  mlir::MemRefType bankType;
};

/// Append the entries of an `hls.array_partition` array attribute.
void parsePartitionEntries(mlir::ArrayAttr arr, llvm::StringRef from,
                           llvm::SmallVectorImpl<PartitionEntry> &out);

/// Apply the entries to `ty` (N17 (c), N20, N21, N24). nullopt when no
/// dimension is split.
std::optional<BankLayout> buildBankLayout(llvm::ArrayRef<PartitionEntry> entries,
                                          mlir::MemRefType ty);

/// (bank, offset) of an index along one split dimension.
///   cyclic / complete: bank = idx mod f        offset = idx floordiv f
///   block:             bank = idx floordiv bs  offset = idx mod bs
std::pair<mlir::AffineExpr, mlir::AffineExpr>
bankAndOffset(mlir::AffineExpr idx, const DimPartition &p);
std::pair<int64_t, int64_t> bankAndOffset(int64_t idx, const DimPartition &p);

/// A key that is equal for equal partitions (per parameter, in order).
std::string
partitionFormKey(llvm::ArrayRef<std::optional<BankLayout>> layouts);

/// The partition of every storage root of a module. A root's partition is
/// the merge of its own pragma and the pragmas of every callee parameter it
/// reaches through calls, transitively; pragmas do not flow sideways (an
/// array that only shares an unpartitioned callee with a partitioned one
/// stays unpartitioned: forgebench diff_orders_module BRAM_C3). A root that
/// would be partitioned but reaches an op the banking cannot rewrite (a
/// view, a cast, an external call, a return, a memref stored as a value) or
/// a parameter of another shape stays one memory.
class PartitionRoots {
public:
  /// `warn`: emit "array_partition not applied" warnings on such roots.
  PartitionRoots(mlir::ModuleOp module, bool warn);

  /// The partition of a root (alloca / global op), nullopt if none.
  std::optional<BankLayout> layoutOf(mlir::Operation *root) const {
    auto it = rootLayout.find(root);
    return it == rootLayout.end() ? std::nullopt : it->second;
  }
  /// The partition of the memory a value names when it is a root's alloca
  /// result or a get_global of a root; nullopt otherwise.
  std::optional<BankLayout> layoutOfRootValue(mlir::Value v) const;
  /// Functions some func.call reaches.
  const llvm::DenseSet<mlir::Operation *> &called() const {
    return calledFuncs;
  }

private:
  struct Node {
    enum Kind { Alloca, Global, Arg } kind;
    mlir::Value value;
    mlir::Operation *op = nullptr; // alloca / global
    mlir::func::FuncOp func;       // Arg
    unsigned argNo = 0;
    llvm::SmallVector<mlir::Value> sites;
  };
  mlir::ModuleOp module;
  mlir::SymbolTable symbols;
  llvm::SmallVector<Node> nodes;
  llvm::DenseMap<const void *, unsigned> nodeOf;
  llvm::SmallVector<std::string> badReasons;
  llvm::SmallVector<llvm::SmallVector<unsigned>> edges;
  llvm::DenseSet<mlir::Operation *> calledFuncs;
  llvm::DenseMap<mlir::Operation *, std::optional<BankLayout>> rootLayout;

  unsigned addNode(Node n, const void *key);
  std::optional<unsigned> nodeOfValue(mlir::Value v) const;
  mlir::MemRefType typeOf(const Node &n) const;
  mlir::ArrayAttr specOf(const Node &n) const;
  std::string describe(const Node &n) const;
};

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_PARTITIONLAYOUT_H
