//===- Plugin.h - The common base of every hls-est plugin ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// hls-est models what cannot be data (an algorithm, a rule over the IR) as
// plugin interfaces (hls-doc/plugins.md, design memo section 8). Every
// interface derives from PluginBase; an implementation is registered by name
// in the interface's registry (Registry.h), and the configuration selects it
// by name (`tool.backend.memory_mapper.plugin = "vitis-band7"`, ...). The
// compiled-in implementations ("builtins") are registered the same way as an
// external plugin loaded with --load-plugin, so every run goes through the
// registries.
//
// ABI: a plugin is compiled against the same CIRCT build tree as the hls-est
// that loads it (same compiler, C++17, -fno-rtti, the same LLVM ABI-breaking
// checks), links nothing that hls-est contains, and resolves every symbol in
// the hls-est executable at load time. HLS_EST_PLUGIN_API_VERSION changes
// whenever an interface or one of its data types changes; --load-plugin
// refuses a plugin built for another version.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PLUGINS_PLUGIN_H
#define CIRCT_DIALECT_RESOURCE_PLUGINS_PLUGIN_H

#include "circt/Dialect/Resource/Config/Config.h"

#include "llvm/ADT/StringRef.h"

#include <cstdint>

/// The version of the plugin interfaces and their data types.
#define HLS_EST_PLUGIN_API_VERSION 1

namespace circt::hlsest {

/// What a plugin library reports through its optional entry point
/// `extern "C" HlsEstPluginInfo hlsEstGetPluginInfo()`.
struct HlsEstPluginInfo {
  uint32_t apiVersion; ///< HLS_EST_PLUGIN_API_VERSION it was built with
  const char *name;    ///< the plugin library's name
};

/// The common part of every interface.
///
/// Life cycle: the registry constructs an implementation; configure() is
/// called once with the merged configuration; checkDevice() once with the
/// run's device (a builtin refuses a device it cannot price and names the
/// missing capability). After that only const methods are called, possibly
/// from several threads at once (function passes run in parallel), so an
/// implementation keeps no mutable state. A `trace` argument, when non-null,
/// receives intermediate values for --bram-debug and must never influence a
/// result.
class PluginBase {
public:
  virtual ~PluginBase();
  /// The registered name.
  virtual llvm::StringRef name() const = 0;
  /// Reads the implementation's parameters (schema keys, or its own
  /// `plugins.<name>` section for an external plugin). Errors go to `diag`.
  virtual void configure(const Config &config, ConfigDiagnostics &diag);
  /// Refuses a device the implementation cannot model (an error in `diag`).
  virtual void checkDevice(const Device &device,
                           ConfigDiagnostics &diag) const;
};

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_PLUGINS_PLUGIN_H
