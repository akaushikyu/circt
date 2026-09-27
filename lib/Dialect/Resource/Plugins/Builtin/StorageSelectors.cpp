//===- StorageSelectors.cpp - The builtin storage selector ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// vitis-bits-threshold: Vitis HLS implements an array of at least
// `min_block_bits` (Words x exact element Bits, 1024, inclusive) in block RAM
// and anything smaller in distributed RAM, which costs no block RAM: 64x16 =
// 1024 bits -> 1 BRAM, 93x11 = 1023 -> LUTRAM, 64x15 = 960 -> LUTRAM
// (VITIS_NOTES N5, 23 kernels). It reads no access count and no schedule.
// A bind_storage impl equal to `forcing_impl` (bram) puts a bank of any size
// in block RAM (N98: a 16 x 16-bit array bound impl=bram is 1 BRAM).
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

using namespace circt::hlsest;
using llvm::StringRef;

namespace {

class VitisBitsThresholdSelector : public StorageSelector {
public:
  StringRef name() const override { return "vitis-bits-threshold"; }

  void configure(const Config &config, ConfigDiagnostics &) override {
    rule = config.tool.backend.storageSelector;
  }

  void checkDevice(const Device &device,
                   ConfigDiagnostics &diag) const override {
    if (!device.memory(rule.block))
      diag.errors.push_back("tool.backend.storage_selector.block: device '" +
                            device.id + "' has no memory '" + rule.block +
                            "'");
  }

  TierChoice select(const MemoryRequest &request, const Device &device,
                    const SelectionContext &) const override {
    TierChoice c;
    int64_t bits = request.bits();
    bool forced = !rule.forcingImpl.empty() && request.pragmaImpl &&
                  *request.pragmaImpl == rule.forcingImpl;
    if (rule.belowBlock(bits) && !forced) {
      c.tier = rule.below;
      c.note = "size " + std::to_string(bits) + " bits" +
               (request.narrowed ? " (narrowed element width)" : "") + " " +
               rule.belowSymbol() + " " + std::to_string(rule.minBlockBits) +
               "-bit BRAM promotion threshold (Words*Bits " +
               (rule.inclusive ? ">= " : "> ") +
               std::to_string(rule.minBlockBits) +
               " -> BRAM); distributed RAM, 0 BRAM";
      return c;
    }
    c.memory = rule.block;
    if (const DeviceMemory *m = device.memory(rule.block))
      c.tier = m->tier;
    return c;
  }

private:
  StorageSelectorConfig rule;
};

} // namespace

void circt::hlsest::builtin::registerStorageSelectors() {
  PluginRegistry<StorageSelector>::instance().add(
      "vitis-bits-threshold",
      "block RAM from min_block_bits (words x bits, Vitis: 1024), else "
      "distributed RAM",
      [] { return std::make_unique<VitisBitsThresholdSelector>(); }, "builtin");
}
