//===- MemoryGroupings.cpp - The builtin memory grouping ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// identity: every memref is a memory of its own (Vitis merges arrays only
// on an explicit pragma, which hls-est does not model).
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

using namespace circt::hlsest;

namespace {
class IdentityGrouping : public MemoryGrouping {
public:
  llvm::StringRef name() const override { return "identity"; }
  void group(llvm::ArrayRef<GroupCandidate>,
             llvm::SmallVectorImpl<MemoryGroup> &) const override {}
};
} // namespace

void circt::hlsest::builtin::registerMemoryGroupings() {
  PluginRegistry<MemoryGrouping>::instance().add(
      "identity", "one memref, one memory",
      [] { return std::make_unique<IdentityGrouping>(); }, "builtin");
}
