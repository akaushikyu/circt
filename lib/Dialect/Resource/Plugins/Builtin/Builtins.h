//===- Builtins.h - Registration of the builtin plugins -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// One registration function per builtin file (a static registrar in a static
// library is dropped by the linker unless something references it);
// registerBuiltinPlugins (RegisterBuiltins.cpp) calls them all.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_LIB_DIALECT_RESOURCE_PLUGINS_BUILTIN_BUILTINS_H
#define CIRCT_LIB_DIALECT_RESOURCE_PLUGINS_BUILTIN_BUILTINS_H

namespace circt::hlsest::builtin {

void registerMemoryMappers();
void registerStorageSelectors();
void registerMemoryArchitecturePolicies();
void registerMemoryGroupings();
void registerImplicitBufferModels();
void registerPipelinePolicies();
void registerPartitionPolicies();
void registerFoldRuleSets();
void registerOperatorTimingModels();
void registerDependenceModels();
void registerModuloSchedulers();
void registerSequentialSchedulers();
void registerBinders();

} // namespace circt::hlsest::builtin

#endif // CIRCT_LIB_DIALECT_RESOURCE_PLUGINS_BUILTIN_BUILTINS_H
