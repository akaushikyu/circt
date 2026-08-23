//===- PluginInfo.cpp - Entry points of the example plugin ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The two entry points --load-plugin looks for: MLIR's pass-plugin entry
// point (required; this plugin adds no pass) and hls-est's (the interface
// version it was built for).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/Plugin.h"

#include "mlir/Tools/Plugins/PassPlugin.h"
#include "llvm/Config/llvm-config.h"

extern "C" LLVM_ATTRIBUTE_WEAK mlir::PassPluginLibraryInfo
mlirGetPassPluginInfo() {
  return {MLIR_PLUGIN_API_VERSION, "HlsEstExamplePlugin", LLVM_VERSION_STRING,
          []() {}};
}

extern "C" LLVM_ATTRIBUTE_WEAK circt::hlsest::HlsEstPluginInfo
hlsEstGetPluginInfo() {
  return {HLS_EST_PLUGIN_API_VERSION, "HlsEstExamplePlugin"};
}
