//===- Registry.cpp - Registries of the hls-est plugin interfaces ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The one definition of every registry (Registry.h explains why the members
// live here and nowhere else).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Config/Schema.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/raw_ostream.h"

using namespace circt::hlsest;
using llvm::StringRef;

PluginBase::~PluginBase() = default;
void PluginBase::configure(const Config &, ConfigDiagnostics &) {}
void PluginBase::checkDevice(const Device &, ConfigDiagnostics &) const {}
RuleFolder::~RuleFolder() = default;


template <class Interface>
PluginRegistry<Interface> &PluginRegistry<Interface>::instance() {
  static PluginRegistry registry;
  return registry;
}

static bool &registrationFailed() {
  static bool failed = false;
  return failed;
}

bool circt::hlsest::pluginRegistrationFailed() { return registrationFailed(); }

template <class Interface>
bool PluginRegistry<Interface>::add(StringRef name, StringRef description,
                                    Factory factory, StringRef origin) {
  if (find(name)) {
    registrationFailed() = true;
    llvm::errs() << "error: hls-est plugin: a " << interfaceKey()
                 << " named '" << name << "' is already registered (by "
                 << find(name)->origin << "); '" << origin
                 << "' must choose another name\n";
    return false;
  }
  slots.push_back(
      {PluginEntry{name.str(), description.str(), origin.str()},
       std::move(factory)});
  return true;
}

template <class Interface>
const PluginEntry *PluginRegistry<Interface>::find(StringRef name) const {
  for (const Slot &s : slots)
    if (s.entry.name == name)
      return &s.entry;
  return nullptr;
}

template <class Interface>
std::unique_ptr<Interface>
PluginRegistry<Interface>::create(StringRef name, const Config &config,
                                  ConfigDiagnostics &diag) const {
  for (const Slot &s : slots)
    if (s.entry.name == name) {
      std::unique_ptr<Interface> impl = s.factory();
      size_t before = diag.errors.size();
      impl->configure(config, diag);
      impl->checkDevice(config.device, diag);
      if (diag.errors.size() != before)
        return nullptr;
      return impl;
    }
  std::string known;
  for (const PluginEntry &e : entries())
    known += (known.empty() ? "" : ", ") + e.name;
  diag.errors.push_back(std::string("no ") + interfaceKey() +
                        " plugin named '" + name.str() +
                        "' is registered (registered: " + known + ")");
  return nullptr;
}

template <class Interface>
std::vector<PluginEntry> PluginRegistry<Interface>::entries() const {
  std::vector<PluginEntry> out;
  for (const Slot &s : slots)
    out.push_back(s.entry);
  llvm::sort(out, [](const PluginEntry &a, const PluginEntry &b) {
    return a.name < b.name;
  });
  return out;
}



namespace circt::hlsest {
template class PluginRegistry<StorageSelector>;
template class PluginRegistry<MemoryArchitecturePolicy>;
template class PluginRegistry<MemoryMapper>;
template class PluginRegistry<MemoryGrouping>;
template class PluginRegistry<ImplicitBufferModel>;
template class PluginRegistry<PipelinePolicy>;
template class PluginRegistry<PartitionPolicy>;
template class PluginRegistry<FoldRuleSet>;
template class PluginRegistry<OperatorTimingModel>;
template class PluginRegistry<DependenceModel>;
template class PluginRegistry<ModuloScheduler>;
template class PluginRegistry<SequentialScheduler>;
template class PluginRegistry<Binder>;
} // namespace circt::hlsest

std::vector<std::pair<std::string, std::vector<PluginEntry>>>
circt::hlsest::listPlugins() {
  std::vector<std::pair<std::string, std::vector<PluginEntry>>> out;
  auto add = [&](auto &registry, const char *key) {
    out.push_back({key, registry.entries()});
  };
  add(PluginRegistry<StorageSelector>::instance(), "storage_selector");
  add(PluginRegistry<MemoryArchitecturePolicy>::instance(),
      "memory_architecture_policy");
  add(PluginRegistry<MemoryMapper>::instance(), "memory_mapper");
  add(PluginRegistry<MemoryGrouping>::instance(), "memory_grouping");
  add(PluginRegistry<ImplicitBufferModel>::instance(), "implicit_buffer_model");
  add(PluginRegistry<PipelinePolicy>::instance(), "pipeline_policy");
  add(PluginRegistry<PartitionPolicy>::instance(), "partition_policy");
  add(PluginRegistry<FoldRuleSet>::instance(), "fold_rule_set");
  add(PluginRegistry<OperatorTimingModel>::instance(), "operator_timing_model");
  add(PluginRegistry<DependenceModel>::instance(), "dependence_model");
  add(PluginRegistry<ModuloScheduler>::instance(), "modulo_scheduler");
  add(PluginRegistry<SequentialScheduler>::instance(), "sequential_scheduler");
  add(PluginRegistry<Binder>::instance(), "binder");
  return out;
}

bool circt::hlsest::isRegisteredPlugin(StringRef interfaceKey, StringRef name,
                                       std::string &known) {
  for (const auto &[key, entries] : listPlugins()) {
    if (key != interfaceKey)
      continue;
    known.clear();
    for (const PluginEntry &e : entries) {
      if (e.name == name)
        return true;
      known += (known.empty() ? "" : ", ") + e.name;
    }
    return false;
  }
  known = "(unknown interface)";
  return false;
}

void circt::hlsest::checkConfiguredPlugins(const Config &config,
                                           ConfigDiagnostics &diag) {
  // configure() and checkDevice() of every implementation the configuration
  // names, each once; the registry reports the errors.
  const HlsToolConfig &hls = config.tool.hls;
  const BackendConfig &be = config.tool.backend;
  const SchedulingConfig &sc = config.scheduling;
  (void)PluginRegistry<StorageSelector>::instance().create(
      be.storageSelector.plugin, config, diag);
  (void)PluginRegistry<MemoryArchitecturePolicy>::instance().create(
      hls.memoryArchitecture.plugin, config, diag);
  llvm::StringSet<> mappers;
  auto checkMapper = [&](StringRef name) {
    if (mappers.insert(name).second)
      (void)PluginRegistry<MemoryMapper>::instance().create(name, config, diag);
  };
  checkMapper(be.memoryMapper.plugin);
  checkMapper(hls.streams.mapper);
  (void)PluginRegistry<MemoryGrouping>::instance().create(hls.groupingPlugin,
                                                         config, diag);
  for (const ImplicitBufferConfig &b : hls.implicitBuffers) {
    (void)PluginRegistry<ImplicitBufferModel>::instance().create(
        b.plugin, config, diag);
    checkMapper(b.readFifoMapper);
  }
  (void)PluginRegistry<PipelinePolicy>::instance().create(
      hls.pipelineDecision.policy, config, diag);
  (void)PluginRegistry<PartitionPolicy>::instance().create(
      hls.partitioning.policy, config, diag);
  (void)PluginRegistry<FoldRuleSet>::instance().create(hls.folding.ruleSet,
                                                      config, diag);
  (void)PluginRegistry<OperatorTimingModel>::instance().create(sc.timingModel,
                                                              config, diag);
  (void)PluginRegistry<DependenceModel>::instance().create(sc.dependenceModel,
                                                          config, diag);
  (void)PluginRegistry<ModuloScheduler>::instance().create(sc.moduloModel,
                                                          config, diag);
  (void)PluginRegistry<SequentialScheduler>::instance().create(
      sc.sequentialModel, config, diag);
  (void)PluginRegistry<Binder>::instance().create(sc.bindingModel, config,
                                                 diag);
}
