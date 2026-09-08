//===- StreamFifos.h - hls::stream FIFOs for --bram-analysis -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Vitis builds one FIFO for every hls::stream object of the design (each
// element of an array of streams, each stream member of a struct). cgeist
// lowers a stream object to an opaque i32 "handle" (the storage of a local
// stream, an array of streams, or a static stream) that is only ever passed to
// the external hls::stream methods; the handle is not a RAM. This file
// recognises the handles, reads the depth and the element width of each FIFO
// and prices it (StreamFifos.cpp has the Vitis rules).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_STREAMFIFOS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_STREAMFIFOS_H

#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLFunctionalExtras.h"
#include "llvm/ADT/StringRef.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace circt::hls_analysis {

/// The template arguments of an hls::stream<T, DEPTH> method symbol
/// (`_ZN3hls6streamI<T>Li<DEPTH>EE<method>`).
struct StreamTemplate {
  std::string elementMangled;  ///< the mangling of T
  std::optional<int64_t> depth; ///< DEPTH (0 is the default depth)
  std::string method;          ///< the mangled method after the class name
};

/// The template arguments of `symbol` when it names a method of hls::stream,
/// otherwise nullopt. `depth` is unset when the arguments cannot be parsed.
std::optional<StreamTemplate> parseStreamMethod(llvm::StringRef symbol);

/// How an hls::stream method moves the object its data argument refers to:
/// `write` / `write_nb` / `<<` read it, `read(T&)` / `read_nb` / `>>` write
/// it (StreamFifos.cpp ioType names the same methods). `method` is
/// StreamTemplate::method.
enum class StreamData { ReadsElement, WritesElement };
inline std::optional<StreamData> streamDataAccess(llvm::StringRef method) {
  if (method.starts_with("5write") || method.starts_with("8write_nb") ||
      method.starts_with("ls"))
    return StreamData::ReadsElement;
  if ((method.starts_with("4read") && !method.starts_with("4readEv")) ||
      method.starts_with("7read_nb") || method.starts_with("rs"))
    return StreamData::WritesElement;
  return std::nullopt;
}

/// Bits of the element type T from its mangling, for the types whose width
/// the IR does not carry exactly (bool is an i8 in memory, a 1-bit FIFO in
/// Vitis) and the arbitrary-precision types; nullopt otherwise.
std::optional<unsigned> mangledElementBits(llvm::StringRef elementMangled);

/// Packed bits of an IR element type: an integer / float its width, an LLVM
/// struct the sum of its members (no padding), an LLVM array the element
/// times the count. 0 when unknown.
unsigned packedTypeBits(mlir::Type type);

/// How Vitis implements one FIFO and what it costs.
struct FifoPrice {
  unsigned bram = 0;
  std::string reason;
};

/// One FIFO of `depth` words x `bits` (`bindImpl`: the impl of a
/// bind_storage type=fifo pragma, empty without one). `bandBlocks(depth,
/// bits)` is the RAM's BRAM_18K by the depth bands at the 18-bit port width.
FifoPrice priceFifo(int64_t depth, unsigned bits, llvm::StringRef bindImpl,
                    llvm::function_ref<int64_t(int64_t, unsigned)> bandBlocks);

/// FIFOs of one stream handle with the same depth and width.
struct FifoGroup {
  int64_t count = 0;      ///< FIFOs (elements of the handle's shape)
  std::string countSource; ///< which elements / member handles count
  std::optional<unsigned> member; ///< struct member index, if any
  int64_t depth = 0;
  std::string depthSource; ///< "pragma" | "template" | "default"
  unsigned bits = 0;
  std::string bitsSource;  ///< "mangled <T>" | "ir <type>" | "unknown"
  unsigned bramEach = 0;
  std::string reason;
};

/// What --bram-analysis reports for one stream handle.
struct StreamHandleRecord {
  std::vector<FifoGroup> groups;
  std::vector<std::string> methods; ///< hls::stream methods reached (sorted)
  std::string note;  ///< anything the model could not resolve
  unsigned bram = 0; ///< one instance of the owning function
  int64_t fifos = 0; ///< FIFOs of one instance
};

/// When `storage` (a memref.alloca, or a memref.global whose uses are
/// `sites`) holds hls::stream objects, i.e. its handles reach hls::stream
/// methods as the object argument (directly, through views and pointer
/// casts, or through calls into the callees' parameters), the FIFOs it
/// stands for; nullopt otherwise.
std::optional<StreamHandleRecord>
analyzeStreamHandle(mlir::Operation *storage, llvm::ArrayRef<mlir::Value> sites,
                    llvm::function_ref<int64_t(int64_t, unsigned)> bandBlocks);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_STREAMFIFOS_H
