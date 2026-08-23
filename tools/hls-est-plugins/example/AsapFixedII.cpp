//===- AsapFixedII.cpp - Example ModuloScheduler plugin for hls-est -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// asap-fixed-ii: a replacement for the builtin modulo scheduler (select it
// with scheduling.modulo.model = "asap-fixed-ii"). The II is the largest of
// the II the user asked for (SchedulingContext::requestedII), the resource
// minimum II (every port pool's uses / limit) and the plugin's own floor
// (plugins.asap-fixed-ii.min_ii, default 1); every operation starts as soon
// as its intra-iteration predecessors are done and a slot of each of its
// resources is free modulo the II; a violated recurrence raises the II.
//
// It is an example of the interface, not a model of a tool: its stage starts
// are not the builtin's, so the BRAM port model (which reads the II and the
// stage starts) can give other numbers. Its result depends on a parameter
// outside the scheduling problem, so isFunctionOfProblem() is false and the
// pass does not reuse schedules for it.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"

#include <algorithm>
#include <map>
#include <string>

using namespace circt::hlsest;
using circt::scheduling::ModuloProblem;

namespace {

class AsapFixedII : public ModuloScheduler {
public:
  llvm::StringRef name() const override { return "asap-fixed-ii"; }

  void configure(const Config &config, ConfigDiagnostics &diag) override {
    if (const llvm::json::Object *own = config.plugins.getObject(name())) {
      for (const auto &kv : *own)
        if (kv.first != "min_ii" && !llvm::StringRef(kv.first).starts_with("_"))
          diag.errors.push_back("plugins.asap-fixed-ii." + kv.first.str() +
                                ": unknown key");
      if (const llvm::json::Value *v = own->get("min_ii")) {
        std::optional<int64_t> i = v->getAsInteger();
        if (!i || *i < 1)
          diag.errors.push_back(
              "plugins.asap-fixed-ii.min_ii: expected an integer >= 1");
        else
          minII = static_cast<unsigned>(*i);
      }
    }
  }

  ScheduleOutcome schedule(ModuloProblem &problem, mlir::Operation *,
                           const SchedulingContext &context) const override {
    unsigned ii = std::max({minII, context.requestedII.value_or(1u),
                            resourceMinII(problem)});
    for (unsigned attempt = 0; attempt < 1024; ++attempt, ++ii)
      if (place(problem, ii))
        return {true, "asap-fixed-ii", {}};
    return {false, "asap-fixed-ii", {}};
  }

private:
  unsigned minII = 1;

  static unsigned latencyOf(ModuloProblem &p, mlir::Operation *op) {
    auto opr = p.getLinkedOperatorType(op);
    return opr ? p.getLatency(*opr).value_or(0) : 0;
  }

  /// max over the resources of ceil(uses / limit).
  static unsigned resourceMinII(ModuloProblem &p) {
    std::map<std::string, std::pair<unsigned, unsigned>> uses; // uses, limit
    for (mlir::Operation *op : p.getOperations())
      if (auto rsrcs = p.getLinkedResourceTypes(op))
        for (auto r : *rsrcs)
          if (std::optional<unsigned> limit = p.getLimit(r)) {
            auto &u = uses[r.str()];
            ++u.first;
            u.second = *limit;
          }
    unsigned ii = 1;
    for (const auto &[name, u] : uses)
      if (u.second)
        ii = std::max(ii, (u.first + u.second - 1) / u.second);
    return ii;
  }

  /// ASAP placement in program order at `ii`; false when a dependence
  /// (a recurrence, or an edge to an earlier operation) is violated.
  static bool place(ModuloProblem &p, unsigned ii) {
    p.setInitiationInterval(ii);
    std::map<std::pair<std::string, unsigned>, unsigned> used;
    for (mlir::Operation *op : p.getOperations()) {
      unsigned start = 0;
      for (auto dep : p.getDependences(op)) {
        mlir::Operation *src = dep.getSource();
        if (src == op || p.getDistance(dep).value_or(0) != 0)
          continue;
        if (std::optional<unsigned> s = p.getStartTime(src))
          start = std::max(start, *s + latencyOf(p, src));
      }
      auto rsrcs = p.getLinkedResourceTypes(op);
      auto isFree = [&](unsigned t) {
        if (rsrcs)
          for (auto r : *rsrcs)
            if (used[{r.str(), t % ii}] >= p.getLimit(r).value_or(~0u))
              return false;
        return true;
      };
      while (!isFree(start))
        ++start;
      if (rsrcs)
        for (auto r : *rsrcs)
          ++used[{r.str(), start % ii}];
      p.setStartTime(op, start);
    }
    for (mlir::Operation *op : p.getOperations())
      for (auto dep : p.getDependences(op)) {
        mlir::Operation *src = dep.getSource();
        unsigned distance = p.getDistance(dep).value_or(0);
        if (*p.getStartTime(op) + distance * ii <
            *p.getStartTime(src) + latencyOf(p, src))
          return false;
      }
    return true;
  }
};

} // namespace

HLS_EST_REGISTER_PLUGIN(ModuloScheduler, "asap-fixed-ii",
                        "example: ASAP placement at the requested / resource "
                        "minimum II (plugins.asap-fixed-ii.min_ii)",
                        AsapFixedII);
