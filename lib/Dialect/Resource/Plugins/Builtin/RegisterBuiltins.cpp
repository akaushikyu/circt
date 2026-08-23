//===- RegisterBuiltins.cpp - Register every builtin plugin ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/Resource/Config/Schema.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

void circt::hlsest::registerBuiltinPlugins() {
  static bool done = false;
  if (done)
    return;
  done = true;
  builtin::registerStorageSelectors();
  builtin::registerMemoryArchitecturePolicies();
  builtin::registerMemoryMappers();
  builtin::registerMemoryGroupings();
  builtin::registerImplicitBufferModels();
  builtin::registerPipelinePolicies();
  builtin::registerPartitionPolicies();
  builtin::registerFoldRuleSets();
  builtin::registerOperatorTimingModels();
  builtin::registerDependenceModels();
  builtin::registerModuloSchedulers();
  builtin::registerSequentialSchedulers();
  builtin::registerBinders();
  // The configuration loader checks every plugin-name key against the
  // registries (after the command line has loaded the external plugins).
  setPluginNameCheck([](llvm::StringRef key, llvm::StringRef name,
                        std::string &known) {
    return isRegisteredPlugin(key, name, known);
  });
  setPluginConfigCheck(checkConfiguredPlugins);
}
