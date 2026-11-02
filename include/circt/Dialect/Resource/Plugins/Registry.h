//===- Registry.h - Registries of the hls-est plugin interfaces -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// One registry per interface, keyed by name. The registries are templates
// whose members are defined only in hls-est (Registry.cpp, one explicit
// instantiation per interface), so a plugin's translation units instantiate
// nothing of a registry: they call the executable's definitions and every
// plugin shares the one registry per interface. A name can be registered once
// (a plugin cannot replace a builtin; it chooses another name, and the
// configuration selects it).
//
// Registration:
//
//   HLS_EST_REGISTER_PLUGIN(MemoryMapper, "my-mapper", "what it does", MyMapper);
//
// at namespace scope in the plugin (a static registrar that runs when the
// library is loaded). HLS_EST_PLUGIN_ORIGIN names who registered it
// ("builtin" inside hls-est, the plugin's name in a plugin library; set it
// with a compile definition).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PLUGINS_REGISTRY_H
#define CIRCT_DIALECT_RESOURCE_PLUGINS_REGISTRY_H

#include "circt/Dialect/Resource/Plugins/Plugin.h"

#include "llvm/ADT/StringRef.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#ifndef HLS_EST_PLUGIN_ORIGIN
#define HLS_EST_PLUGIN_ORIGIN "builtin"
#endif

namespace circt::hlsest {

class StorageSelector;
class MemoryArchitecturePolicy;
class MemoryMapper;
class MemoryGrouping;
class ImplicitBufferModel;
class PipelinePolicy;
class PartitionPolicy;
class FoldRuleSet;
class OperatorTimingModel;
class DependenceModel;
class ModuloScheduler;
class SequentialScheduler;
class Binder;

/// The key of each interface (memory_mapper, ...), as the configuration and
/// hls-doc/plugins.md name it.
template <class Interface>
struct PluginInterfaceKey;
#define HLS_EST_INTERFACE_KEY(Interface, Key)                                  \
  template <>                                                                  \
  struct PluginInterfaceKey<Interface> {                                       \
    static constexpr const char *value = Key;                                  \
  };
HLS_EST_INTERFACE_KEY(StorageSelector, "storage_selector")
HLS_EST_INTERFACE_KEY(MemoryArchitecturePolicy, "memory_architecture_policy")
HLS_EST_INTERFACE_KEY(MemoryMapper, "memory_mapper")
HLS_EST_INTERFACE_KEY(MemoryGrouping, "memory_grouping")
HLS_EST_INTERFACE_KEY(ImplicitBufferModel, "implicit_buffer_model")
HLS_EST_INTERFACE_KEY(PipelinePolicy, "pipeline_policy")
HLS_EST_INTERFACE_KEY(PartitionPolicy, "partition_policy")
HLS_EST_INTERFACE_KEY(FoldRuleSet, "fold_rule_set")
HLS_EST_INTERFACE_KEY(OperatorTimingModel, "operator_timing_model")
HLS_EST_INTERFACE_KEY(DependenceModel, "dependence_model")
HLS_EST_INTERFACE_KEY(ModuloScheduler, "modulo_scheduler")
HLS_EST_INTERFACE_KEY(SequentialScheduler, "sequential_scheduler")
HLS_EST_INTERFACE_KEY(Binder, "binder")
#undef HLS_EST_INTERFACE_KEY

/// One registered implementation.
struct PluginEntry {
  std::string name;
  std::string description;
  std::string origin; ///< "builtin" or the plugin library's name
};

template <class Interface>
class PluginRegistry {
public:
  using Factory = std::function<std::unique_ptr<Interface>()>;

  /// The registry of `Interface` (one per process, in the executable).
  static PluginRegistry &instance();
  /// The interface's key (memory_mapper, ...).
  static const char *interfaceKey() {
    return PluginInterfaceKey<Interface>::value;
  }
  /// Registers `name`; false (and a message on stderr) when the name is taken.
  bool add(llvm::StringRef name, llvm::StringRef description, Factory factory,
           llvm::StringRef origin);
  /// A new instance of `name`, configured and checked against the
  /// configuration's device; null with an error in `diag` when `name` is not
  /// registered or the implementation refuses the configuration.
  std::unique_ptr<Interface> create(llvm::StringRef name, const Config &config,
                                    ConfigDiagnostics &diag) const;
  /// Every registered implementation, sorted by name.
  std::vector<PluginEntry> entries() const;
  /// The entry of `name`, or null.
  const PluginEntry *find(llvm::StringRef name) const;

private:
  struct Slot {
    PluginEntry entry;
    Factory factory;
  };
  std::vector<Slot> slots;
};

template <class Interface>
struct PluginRegistrar {
  PluginRegistrar(llvm::StringRef name, llvm::StringRef description,
                  typename PluginRegistry<Interface>::Factory factory,
                  llvm::StringRef origin) {
    PluginRegistry<Interface>::instance().add(name, description,
                                              std::move(factory), origin);
  }
};

extern template class PluginRegistry<StorageSelector>;
extern template class PluginRegistry<MemoryArchitecturePolicy>;
extern template class PluginRegistry<MemoryMapper>;
extern template class PluginRegistry<MemoryGrouping>;
extern template class PluginRegistry<ImplicitBufferModel>;
extern template class PluginRegistry<PipelinePolicy>;
extern template class PluginRegistry<PartitionPolicy>;
extern template class PluginRegistry<FoldRuleSet>;
extern template class PluginRegistry<OperatorTimingModel>;
extern template class PluginRegistry<DependenceModel>;
extern template class PluginRegistry<ModuloScheduler>;
extern template class PluginRegistry<SequentialScheduler>;
extern template class PluginRegistry<Binder>;

/// Whether a registration was refused (a name taken twice); the driver then
/// stops before running anything.
bool pluginRegistrationFailed();

/// Every interface key with its registered implementations (--list-plugins,
/// the debug report).
std::vector<std::pair<std::string, std::vector<PluginEntry>>> listPlugins();

/// Whether `name` is registered for the interface `interfaceKey` (the
/// configuration loader's check of a plugin-name key); `known` receives the
/// registered names.
bool isRegisteredPlugin(llvm::StringRef interfaceKey, llvm::StringRef name,
                        std::string &known);

/// Creates every implementation the configuration names (configure and
/// checkDevice), collecting their errors: the loader's last check.
void checkConfiguredPlugins(const Config &config, ConfigDiagnostics &diag);

/// Registers the compiled-in implementations (the builtins); called by the
/// hls-est driver before the command line is parsed, and installs the
/// configuration loader's plugin-name check.
void registerBuiltinPlugins();

} // namespace circt::hlsest

#define HLS_EST_PLUGIN_CONCAT_(a, b) a##b
#define HLS_EST_PLUGIN_CONCAT(a, b) HLS_EST_PLUGIN_CONCAT_(a, b)

/// Registers `Impl` (default-constructible) as the implementation `Name` of
/// `Interface`.
#define HLS_EST_REGISTER_PLUGIN(Interface, Name, Description, Impl)            \
  static ::circt::hlsest::PluginRegistrar<::circt::hlsest::Interface>          \
      HLS_EST_PLUGIN_CONCAT(hlsEstRegistrar_, Impl)(                           \
          Name, Description,                                                   \
          [] {                                                                 \
            return std::unique_ptr<::circt::hlsest::Interface>(                \
                std::make_unique<Impl>());                                     \
          },                                                                   \
          HLS_EST_PLUGIN_ORIGIN)

#endif // CIRCT_DIALECT_RESOURCE_PLUGINS_REGISTRY_H
