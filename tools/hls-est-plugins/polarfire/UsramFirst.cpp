//===- UsramFirst.cpp - Example StorageSelector for Microchip PolarFire ----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// usram-first: the storage selection hls-doc/new-architecture.md uses for a
// Microchip PolarFire device (microchip-polarfire.device.json). PolarFire has
// two RAM tiers, the 20 Kbit LSRAM (tier block) and the 64 x 12 uSRAM (tier
// hard-small, one read and one write port). An array goes to uSRAM when it
// fits in at most `max_tiles` uSRAM blocks (plugins.usram-first.max_tiles,
// default 1) and no loop body reads it more than once or writes it more than
// once (the static counts of SelectionContext: the selector runs before
// scheduling, so the per-cycle demand is not known yet); any other array goes
// to LSRAM.
//
// A designer knob, not a model: how SmartHLS or Libero choose between LSRAM
// and uSRAM was not measured here.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "mlir/Tools/Plugins/PassPlugin.h"
#include "llvm/Config/llvm-config.h"

using namespace circt::hlsest;

namespace {

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

class UsramFirst : public StorageSelector {
public:
  llvm::StringRef name() const override { return "usram-first"; }

  void configure(const Config &config, ConfigDiagnostics &diag) override {
    if (const llvm::json::Object *own = config.plugins.getObject(name()))
      if (const llvm::json::Value *v = own->get("max_tiles")) {
        std::optional<int64_t> i = v->getAsInteger();
        if (!i || *i < 0)
          diag.errors.push_back(
              "plugins.usram-first.max_tiles: expected an integer >= 0");
        else
          maxTiles = *i;
      }
  }

  void checkDevice(const Device &device,
                   ConfigDiagnostics &diag) const override {
    for (const char *id : {"lsram", "usram"})
      if (!device.memory(id))
        diag.errors.push_back(std::string("usram-first: device '") +
                              device.id + "' has no memory '" + id + "'");
  }

  TierChoice select(const MemoryRequest &request, const Device &device,
                    const SelectionContext &context) const override {
    const DeviceMemory *usram = device.memory("usram");
    const BankStaticProfile *profile = context.profile;
    if (usram && !usram->geometries.empty() && profile) {
      const Geometry &g = usram->geometries.front();
      int64_t tiles = ceilDiv(request.words, g.depth) *
                      ceilDiv(request.writeWidth, g.width);
      if (tiles <= maxTiles && profile->maxReads <= 1 &&
          profile->maxWrites <= 1)
        return {"usram", usram->tier,
                "fits " + std::to_string(tiles) + " uSRAM"};
    }
    return {"lsram", "block", "LSRAM"};
  }

private:
  int64_t maxTiles = 1;
};

} // namespace

HLS_EST_REGISTER_PLUGIN(StorageSelector, "usram-first",
                        "example (PolarFire): uSRAM when an array fits "
                        "max_tiles uSRAM blocks with at most one read and one "
                        "write per loop body, else LSRAM",
                        UsramFirst);

extern "C" LLVM_ATTRIBUTE_WEAK mlir::PassPluginLibraryInfo
mlirGetPassPluginInfo() {
  return {MLIR_PLUGIN_API_VERSION, "HlsEstPolarFirePlugin", LLVM_VERSION_STRING,
          []() {}};
}

extern "C" LLVM_ATTRIBUTE_WEAK circt::hlsest::HlsEstPluginInfo
hlsEstGetPluginInfo() {
  return {HLS_EST_PLUGIN_API_VERSION, "HlsEstPolarFirePlugin"};
}
