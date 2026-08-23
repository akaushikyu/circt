//===- ClockScaledTiming.cpp - Example OperatorTimingModel plugin ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// clock-scaled: a replacement delay model (select it with
// scheduling.timing.model = "clock-scaled"). It takes the classes and
// latencies of the builtin calyx-fixed model, which hold at a reference clock
// (plugins.clock-scaled.reference_ns, default 10 ns), and scales every
// multi-cycle latency with the run's clock: latency' = ceil(latency x
// reference_ns / run.clock_ns), at least 1; combinational operations stay 0
// and memory accesses keep their latency. At 5 ns a floating-point multiply
// (4 cycles at 10 ns) takes 8 cycles.
//
// An example of the interface, not a characterisation of any device: a real
// clock-aware model reads the device's operator table
// (device.operator_table) and chains operations within the period.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"

#include <cmath>

using namespace circt::hlsest;

namespace {

class ClockScaledTiming : public OperatorTimingModel {
public:
  llvm::StringRef name() const override { return "clock-scaled"; }

  void configure(const Config &config, ConfigDiagnostics &diag) override {
    base = PluginRegistry<OperatorTimingModel>::instance().create(
        "calyx-fixed", config, diag);
    double referenceNs = 10;
    if (const llvm::json::Object *own = config.plugins.getObject(name()))
      if (std::optional<double> r = own->getNumber("reference_ns"))
        referenceNs = *r;
    scale = referenceNs / config.run.clockNs;
  }

  void library(llvm::SmallVectorImpl<OperatorTiming> &out) const override {
    base->library(out);
    for (OperatorTiming &t : out)
      t.latency = scaled(t.cls, t.latency);
  }

  std::optional<OperatorTiming>
  timing(mlir::Operation *op, const SchedulingContext &ctx) const override {
    std::optional<OperatorTiming> t = base->timing(op, ctx);
    if (!t)
      return t;
    unsigned latency = scaled(t->cls, t->latency);
    // The class name carries the latency, so that one operator type of the
    // problem never holds two latencies.
    if (latency != t->latency && llvm::StringRef(t->cls).starts_with("call"))
      t->cls += "_x" + std::to_string(latency);
    t->latency = latency;
    return t;
  }

  void listClasses(llvm::SmallVectorImpl<std::string> &out) const override {
    base->listClasses(out);
  }

private:
  std::unique_ptr<OperatorTimingModel> base;
  double scale = 1;

  unsigned scaled(llvm::StringRef cls, unsigned latency) const {
    if (latency == 0 || cls == "mem")
      return latency;
    return std::max(1u, static_cast<unsigned>(std::ceil(latency * scale)));
  }
};

} // namespace

HLS_EST_REGISTER_PLUGIN(OperatorTimingModel, "clock-scaled",
                        "example: calyx-fixed latencies scaled from a "
                        "reference clock to run.clock_ns",
                        ClockScaledTiming);
