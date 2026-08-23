//===- Schema.h - The keys of the hls-est configuration --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// One table describes every key of the configuration: its dotted path (an
// element of an array of objects is written `[]`, as in
// `device.memories[].bits`), its type, unit, range, one-line description,
// the rows of hls-doc/design/assumptions-inventory.md it exposes and the
// passes that read it. The loader validates every document against it,
// --dump-default-config prints its descriptions next to the values,
// --dump-config-schema prints it, and tools/hls-est-validate/make_config_doc.py
// turns that print into hls-doc/configuration.md, so the four cannot drift
// apart. The default values are not in the table: they are the compiled-in
// device and profile files (lib/Dialect/Resource/Config/data/).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_CONFIG_SCHEMA_H
#define CIRCT_DIALECT_RESOURCE_CONFIG_SCHEMA_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"

#include <functional>
#include <string>

namespace circt::hlsest {

enum class KeyKind {
  Section,        ///< an object whose keys are in the table
  ObjectList,     ///< an array of objects whose keys are `<path>[].<key>`
  FreeObject,     ///< an object the schema does not look into
  FreeArray,      ///< an array the schema does not look into (reserved)
  Bool,
  Int,
  UInt,           ///< a non-negative integer
  Number,         ///< any JSON number
  String,
  Enum,           ///< one of `values` ("a|b|c")
  PluginName,     ///< a registered implementation of interface `values`
  StringList,     ///< an array of strings (of `values` when given)
  PortSetList,    ///< an array of arrays of "r" / "w" / "rw"
  ResourceVector, ///< {class: count}; counts are integers or "n/d" strings
  IntMap,         ///< {name: integer}
  NullableUInt,   ///< a non-negative integer or null
  NullablePath,   ///< a file path or null
  NullableObject, ///< an object or null (reserved)
};

/// One key of the configuration.
struct KeySpec {
  const char *path;
  KeyKind kind;
  const char *unit;    ///< "bits", "cycles", "ns", ... or ""
  const char *doc;     ///< one line
  const char *rows;    ///< inventory rows, e.g. "K-02"; "" for new keys
  const char *readers; ///< the passes / components that read it
  const char *values;  ///< Enum: "a|b"; PluginName: the interface key
  double min, max;     ///< inclusive range of a number (NaN: unbounded)
  bool optional;       ///< may be absent (only meaningful in arrays)
};

/// Every key, sections included, in documentation order.
llvm::ArrayRef<KeySpec> configSchema();

/// The key with this pattern path (`device.memories[].bits`), or null.
const KeySpec *findKeySpec(llvm::StringRef path);

/// The name of a KeyKind as --dump-config-schema prints it.
llvm::StringRef keyKindName(KeyKind kind);

/// The interface keys of the plugin selectors (`memory_mapper`, ...), in the
/// order of hls-doc/plugins.md.
llvm::ArrayRef<const char *> pluginInterfaceKeys();

/// How the loader checks a PluginName value: returns true when `name` is a
/// registered implementation of `interfaceKey`, else false with the
/// registered names in `known`. Installed by the plugin registry; without
/// one every name is accepted.
using PluginNameCheck = std::function<bool(
    llvm::StringRef interfaceKey, llvm::StringRef name, std::string &known)>;
void setPluginNameCheck(PluginNameCheck check);
const PluginNameCheck &getPluginNameCheck();

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_CONFIG_SCHEMA_H
