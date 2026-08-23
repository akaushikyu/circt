//===- Mappers.cpp - The builtin memory mappers ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Three MemoryMappers (blocks of one bank in a device memory):
//
//   vitis-band7       the depth bands Vitis HLS 2025.1 prices a RAMB18 bank
//                     with on 7-series parts (VITIS_NOTES N8 (a)-(d), written
//                     from the 23003 memory rows of results/vitis.json and the
//                     fr_* kernels); the bands are its parameters
//                     (tool.backend.memory_mapper.depth_bands);
//   vitis-aspect-min  the minimum over the primitive's aspect-ratio modes
//                     (VITIS_NOTES N6; equal to the bands up to 4096 words,
//                     deeper Vitis does not stack 2Kx9 / 1Kx18 / 512x36
//                     blocks: 8192x9 = 4 here, Vitis 5);
//   geometry-min      the vendor-neutral minimum-cost tiling of words x width
//                     over the geometries the priced port configuration
//                     allows, whole columns of one geometry (no mixed widths,
//                     no depth stacking, like Vitis).
//
// A bank of D words x W bits is priced at the address depth P = 2^ceil(log2
// D) (depth_rounding pow2: Vitis prices the address space, 2500 x 18 one-port
// is 4 blocks, not 3) or at D (exact).
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/MathExtras.h"

#include <algorithm>

using namespace circt::hlsest;
using llvm::StringRef;

namespace {

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

/// The depth a bank of `words` words is priced at.
int64_t pricedDepth(int64_t words, StringRef rounding) {
  if (rounding == "exact")
    return words;
  return static_cast<int64_t>(
      llvm::PowerOf2Ceil(static_cast<uint64_t>(words)));
}

/// Words of `memory`'s geometry of width `width` (0 when it has none).
int64_t depthOf(const DeviceMemory &memory, int64_t width) {
  for (const Geometry &g : memory.geometries)
    if (g.width == width)
      return g.depth;
  return 0;
}

/// blocks x (cost + overhead) of `memory`.
ResourceVector blockCost(const DeviceMemory &memory, int64_t blocks) {
  ResourceVector unit = memory.cost;
  unit.add(memory.overhead);
  return unit.scaled(Rational(blocks));
}

//===----------------------------------------------------------------------===//
// vitis-band7
//===----------------------------------------------------------------------===//

class VitisBand7Mapper : public MemoryMapper {
public:
  StringRef name() const override { return "vitis-band7"; }
  StringRef reportLabel() const override { return "band"; }
  std::string reportDescription() const override {
    return "7-series depth bands, VITIS_NOTES.md N8";
  }

  void configure(const Config &config, ConfigDiagnostics &) override {
    const MemoryMapperConfig &m = config.tool.backend.memoryMapper;
    bands = m.depthBands;
    rounding = m.depthRounding;
    accepted = m.acceptedLibraries;
  }

  /// Vitis prices identical geometry differently per part family, so the
  /// bands apply only to a device whose Vitis library they were measured on
  /// (design memo gap G1), with the RAMB18 block they describe.
  void checkDevice(const Device &device,
                   ConfigDiagnostics &diag) const override {
    std::string why;
    std::optional<std::string> library = device.toolId("vitis", "library");
    if (!library)
      why = "the device has no tool_ids.vitis.library (the Vitis part "
            "library the bands were measured on)";
    else if (!llvm::is_contained(accepted, *library))
      why = "its Vitis library '" + *library +
            "' is not in tool.backend.memory_mapper.accepted_libraries "
            "(measured: " +
            llvm::join(accepted, ", ") + ")";
    const DeviceMemory *block = nullptr;
    for (const DeviceMemory &m : device.memories)
      if (m.tier == "block")
        block = &m;
    if (why.empty() && !block)
      why = "it has no block-tier memory";
    if (why.empty() && block->bits != 18432)
      why = "its block memory '" + block->id + "' has " +
            std::to_string(block->bits) + " bits, the bands price 18432-bit "
            "RAMB18 blocks";
    if (why.empty())
      for (const DepthBand &b : bands)
        for (std::optional<int64_t> w :
             {b.width, b.sdpWidth, b.tdpWidth, b.altWidth})
          if (w && *w > 0 && depthOf(*block, *w) == 0) {
            why = "its block memory '" + block->id + "' has no geometry of "
                  "width " + std::to_string(*w) + " that the bands use";
            break;
          }
    if (why.empty()) {
      const PortConfig *sdp = block->portConfig("sdp");
      const PortConfig *tdp = block->portConfig("tdp");
      if (!sdp || sdp->maxWidth != 36 || !tdp || tdp->maxWidth != 18)
        why = "its block memory '" + block->id +
              "' lacks an sdp configuration of width 36 and a tdp "
              "configuration of width 18";
    }
    if (!why.empty())
      diag.errors.push_back("tool.backend.memory_mapper: vitis-band7 cannot "
                            "price device '" +
                            device.id + "': " + why);
  }

  Mapping map(const MemoryRequest &request, const DeviceMemory &memory,
              const PortConfig &priced, MappingTrace *trace) const override {
    Mapping out;
    if (trace) {
      trace->bitsPerBlock = memory.bits;
      trace->pricedConfig = priced.name;
      trace->maxWidth = static_cast<unsigned>(priced.maxWidth);
    }
    if (request.words <= 0 || request.writeWidth == 0)
      return out;
    const bool pow2 = rounding != "exact";
    int64_t addrDepth = pricedDepth(request.words, rounding);
    int64_t w = request.writeWidth;
    int64_t mode = 0, depthPerBlock = 0, cols = 0, perCol = 0;
    std::string band;
    int64_t prevMax = 0;
    for (const DepthBand &b : bands) {
      if (b.beyond) {
        mode = *b.width;
        depthPerBlock = *b.wordsPerBlock;
        cols = ceilDiv(w, mode);
        perCol = ceilDiv(addrDepth, depthPerBlock);
        band = "depth > " + std::to_string(prevMax) + ": " +
               (pow2 ? "2^ceil(log2 ceil(D/" + std::to_string(depthPerBlock) +
                           "))"
                     : "ceil(D/" + std::to_string(depthPerBlock) + ")") +
               " * " +
               (mode == 1 ? std::string("W")
                          : "ceil(W/" + std::to_string(mode) + ")");
        break;
      }
      if (addrDepth > *b.maxDepth) {
        prevMax = *b.maxDepth;
        continue;
      }
      std::string range = prevMax == 0
                              ? "depth <= " + std::to_string(*b.maxDepth)
                              : "depth " + std::to_string(prevMax + 1) + "-" +
                                    std::to_string(*b.maxDepth);
      if (b.sdpWidth && b.tdpWidth && !b.width) {
        // The wide column when the priced configuration allows it (a bank
        // priced at sdp: x36), else the narrow one (x18).
        bool sdp = priced.maxWidth >= *b.sdpWidth;
        mode = sdp ? *b.sdpWidth : *b.tdpWidth;
        depthPerBlock = depthOf(memory, mode);
        cols = ceilDiv(w, mode);
        perCol = 1;
        band = range + (sdp ? ", SDP: " : ", not SDP: ") + "ceil(W/" +
               std::to_string(mode) + ")";
        break;
      }
      mode = *b.width;
      if (b.altWidth) {
        band = range + ": min(ceil(W/" + std::to_string(*b.width) + "), " +
               std::to_string(*b.altStack) + "*ceil(W/" +
               std::to_string(*b.altWidth) + "))";
        if (ceilDiv(w, *b.width) > *b.altStack * ceilDiv(w, *b.altWidth)) {
          mode = *b.altWidth;
          depthPerBlock = depthOf(memory, mode);
          cols = ceilDiv(w, mode);
          perCol = *b.altStack;
          break;
        }
      } else {
        band = range + ": ceil(W/" + std::to_string(mode) + ")";
      }
      depthPerBlock = depthOf(memory, mode);
      cols = ceilDiv(w, mode);
      perCol = 1;
      break;
    }
    out.blocks = cols * perCol;
    out.cost = blockCost(memory, out.blocks);
    out.configWidth = static_cast<unsigned>(mode);
    out.widthTiles = cols;
    out.depthTiles = perCol;
    out.addrDepth = addrDepth;
    out.depthPerBlock = depthPerBlock;
    out.band = band;
    return out;
  }

private:
  std::vector<DepthBand> bands;
  std::string rounding = "pow2";
  std::vector<std::string> accepted;
};

//===----------------------------------------------------------------------===//
// vitis-aspect-min, geometry-min
//===----------------------------------------------------------------------===//

/// The cheapest layout of whole columns of one geometry no wider than the
/// priced configuration allows; widest geometry first, so that a tie is the
/// fewest-columns layout.
Mapping minOverGeometries(const MemoryRequest &request,
                          const DeviceMemory &memory, const PortConfig &priced,
                          StringRef rounding, bool depthCeil,
                          std::string band) {
  Mapping out;
  out.band = std::move(band);
  if (request.words <= 0 || request.writeWidth == 0)
    return out;
  int64_t addrDepth = pricedDepth(request.words, rounding);
  std::vector<Geometry> modes = memory.geometries;
  llvm::stable_sort(modes, [](const Geometry &a, const Geometry &b) {
    return a.width > b.width;
  });
  int64_t best = -1;
  Geometry bestMode;
  int64_t bestCols = 0, bestPerCol = 0;
  for (const Geometry &mode : modes) {
    if (mode.width > priced.maxWidth)
      continue;
    int64_t cols = ceilDiv(request.writeWidth, mode.width);
    int64_t perCol = depthCeil ? ceilDiv(addrDepth, mode.depth)
                               : std::max<int64_t>(addrDepth / mode.depth, 1);
    int64_t blocks = cols * perCol;
    if (best < 0 || blocks < best) {
      best = blocks;
      bestMode = mode;
      bestCols = cols;
      bestPerCol = perCol;
    }
  }
  if (best < 0)
    return out; // no geometry fits the configuration
  out.blocks = best;
  out.cost = blockCost(memory, best);
  out.configWidth = static_cast<unsigned>(bestMode.width);
  out.widthTiles = bestCols;
  out.depthTiles = bestPerCol;
  out.addrDepth = addrDepth;
  out.depthPerBlock = bestMode.depth;
  return out;
}

class VitisAspectMinMapper : public MemoryMapper {
public:
  StringRef name() const override { return "vitis-aspect-min"; }
  StringRef reportLabel() const override { return "n6"; }
  std::string reportDescription() const override {
    return "min over aspect-ratio modes, VITIS_NOTES.md N6";
  }
  void configure(const Config &config, ConfigDiagnostics &) override {
    rounding = config.tool.backend.memoryMapper.depthRounding;
  }
  Mapping map(const MemoryRequest &request, const DeviceMemory &memory,
              const PortConfig &priced, MappingTrace *trace) const override {
    if (trace) {
      trace->bitsPerBlock = memory.bits;
      trace->pricedConfig = priced.name;
      trace->maxWidth = static_cast<unsigned>(priced.maxWidth);
    }
    return minOverGeometries(request, memory, priced, rounding,
                             /*depthCeil=*/false,
                             "min over the aspect-ratio modes (N6)");
  }

private:
  std::string rounding = "pow2";
};

class GeometryMinMapper : public MemoryMapper {
public:
  StringRef name() const override { return "geometry-min"; }
  std::string reportDescription() const override {
    return "minimum-cost tiling over the device geometries the priced port "
           "configuration allows";
  }
  void configure(const Config &config, ConfigDiagnostics &diag) override {
    const MemoryMapperConfig &m = config.tool.backend.memoryMapper;
    rounding = m.depthRounding;
    if (m.mixedColumns || m.depthStack)
      diag.errors.push_back("tool.backend.memory_mapper: geometry-min: "
                            "mixed_columns and depth_stack are not "
                            "implemented");
  }
  Mapping map(const MemoryRequest &request, const DeviceMemory &memory,
              const PortConfig &priced, MappingTrace *trace) const override {
    if (trace) {
      trace->bitsPerBlock = memory.bits;
      trace->pricedConfig = priced.name;
      trace->maxWidth = static_cast<unsigned>(priced.maxWidth);
    }
    return minOverGeometries(request, memory, priced, rounding,
                             /*depthCeil=*/true,
                             "minimum over the geometries of " + memory.id +
                                 " up to x" +
                                 std::to_string(priced.maxWidth) + " (" +
                                 priced.name + ")");
  }

private:
  std::string rounding = "pow2";
};

} // namespace

void circt::hlsest::builtin::registerMemoryMappers() {
  auto &r = PluginRegistry<MemoryMapper>::instance();
  r.add("vitis-band7",
        "Vitis HLS 2025.1 7-series depth bands of a RAMB18 bank (VITIS_NOTES "
        "N8)",
        [] { return std::make_unique<VitisBand7Mapper>(); }, "builtin");
  r.add("vitis-aspect-min",
        "minimum over the primitive's aspect-ratio modes (VITIS_NOTES N6)",
        [] { return std::make_unique<VitisAspectMinMapper>(); }, "builtin");
  r.add("geometry-min",
        "vendor-neutral minimum-cost tiling over the legal geometries",
        [] { return std::make_unique<GeometryMinMapper>(); }, "builtin");
}
