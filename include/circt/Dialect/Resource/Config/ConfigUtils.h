//===- ConfigUtils.h - Pass options over the configuration -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The precedence rule of the configuration (design memo section 5): a pass
// option given explicitly on the command line (or in the pass's option string)
// beats the configuration, which beats nothing. A pass option counts as given
// when `hasValue()` is true: its parse callback sets it, and the clones on which
// function passes run in parallel copy it with the value. A global llvm::cl::opt
// model switch (process-wide, never cloned) counts as given when it occurred on
// the command line.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_CONFIG_CONFIGUTILS_H
#define CIRCT_DIALECT_RESOURCE_CONFIG_CONFIGUTILS_H

#include "circt/Dialect/Resource/Config/Config.h"
#include "llvm/Support/CommandLine.h"

namespace circt::hlsest {

/// A pass option's value when it was given, else the configured one.
template <typename T, typename PassOption>
T resolveOption(const PassOption &option, T configured) {
  return option.hasValue() ? static_cast<T>(option) : configured;
}

/// A global llvm::cl::opt's value when it occurred, else the configured one.
template <typename T>
T resolveGlobalOption(const llvm::cl::opt<T> &option, T configured) {
  return option.getNumOccurrences() ? static_cast<T>(option) : configured;
}

/// Gives a pass option the configured value unless it was given explicitly,
/// so that the pass body reads its options as before. Used at the start of
/// runOnOperation of a module pass (a function pass's clones each apply it
/// to their own copy).
template <typename PassOption, typename T>
void applyConfigured(PassOption &option, T configured) {
  if (!option.hasValue())
    option = configured;
}

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_CONFIG_CONFIGUTILS_H
