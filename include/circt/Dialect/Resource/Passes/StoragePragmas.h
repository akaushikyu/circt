//===- StoragePragmas.h - bind_storage pragma helpers -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// cgeist writes `#pragma HLS bind_storage variable=v type=T impl=I` (and the
// legacy `#pragma HLS RESOURCE variable=v core=C`, as the same attribute) on
// the array's memref.alloca / memref.global as
// `hls.bind_storage = [{impl = "bram", type = "ram_2p", variable = "v"}]`;
// --memory-banking-bram copies it to every bank.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_STORAGEPRAGMAS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_STORAGEPRAGMAS_H

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/SymbolTable.h"
#include <optional>
#include <string>

namespace circt::hls_analysis {

constexpr llvm::StringLiteral kBindStorageAttr = "hls.bind_storage";

/// The `impl` of the first `hls.bind_storage` dictionary on the storage op
/// (lower case) that binds memory (`type` absent or not `fifo`: a FIFO's
/// binding is --bram-stream-fifos' business); nullopt without one. A
/// memref.get_global is resolved to its memref.global.
inline std::optional<std::string> bindStorageImpl(mlir::Operation *op) {
  if (!op)
    return std::nullopt;
  if (auto get = llvm::dyn_cast<mlir::memref::GetGlobalOp>(op))
    op = mlir::SymbolTable::lookupNearestSymbolFrom(op, get.getNameAttr());
  if (!op)
    return std::nullopt;
  auto arr = op->getAttrOfType<mlir::ArrayAttr>(kBindStorageAttr);
  if (!arr)
    return std::nullopt;
  for (mlir::Attribute a : arr)
    if (auto d = llvm::dyn_cast<mlir::DictionaryAttr>(a)) {
      if (auto type = d.getAs<mlir::StringAttr>("type"))
        if (type.getValue().equals_insensitive("fifo"))
          continue;
      if (auto impl = d.getAs<mlir::StringAttr>("impl"))
        return impl.getValue().lower();
    }
  return std::nullopt;
}

/// The `type` of the first `hls.bind_storage` dictionary on the storage op
/// (lower case) that binds memory (not `fifo`); nullopt without one. A
/// memref.get_global is resolved to its memref.global.
inline std::optional<std::string> bindStorageType(mlir::Operation *op) {
  if (!op)
    return std::nullopt;
  if (auto get = llvm::dyn_cast<mlir::memref::GetGlobalOp>(op))
    op = mlir::SymbolTable::lookupNearestSymbolFrom(op, get.getNameAttr());
  if (!op)
    return std::nullopt;
  auto arr = op->getAttrOfType<mlir::ArrayAttr>(kBindStorageAttr);
  if (!arr)
    return std::nullopt;
  for (mlir::Attribute a : arr)
    if (auto d = llvm::dyn_cast<mlir::DictionaryAttr>(a))
      if (auto type = d.getAs<mlir::StringAttr>("type")) {
        if (type.getValue().equals_insensitive("fifo"))
          continue;
        return type.getValue().lower();
      }
  return std::nullopt;
}

/// Whether `type` (a lower-case bind_storage type) is a plain RAM kind a
/// user binding pins: ram_1p, ram_2p, ram_t2p or ram_s2p (VITIS_NOTES N173:
/// no RAM_1WNR copies; the II absorbs the extra accesses). ram_1wnr and the
/// ROM types are not.
inline bool isPinnedRamType(llvm::StringRef type) {
  return type == "ram_1p" || type == "ram_2p" || type == "ram_t2p" ||
         type == "ram_s2p";
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_STORAGEPRAGMAS_H
