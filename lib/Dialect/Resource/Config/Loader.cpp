//===- Loader.cpp - hls-est configuration: merge, validate, fill, dump ----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The configuration is built as one JSON document (design memo section 5):
//
//   1. the compiled-in defaults: data/base.json (run, frontend, plugins), the
//      device file named by run.device and the profile named by run.tool;
//   2. each --hls-config file in command-line order;
//   3. each --config-set assignment.
//
// Objects merge key by key, everything else (numbers, strings, arrays) is
// replaced as a whole. A file or an assignment that sets run.device (run.tool)
// first replaces the device section (the tool and scheduling sections) with
// the named file. Keys starting with `_` are documentation and are dropped.
// The merged document is validated against the schema (Schema.cpp), checked
// across keys, and copied into the typed Config.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Config/Schema.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/SHA256.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/FormatVariadic.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <set>

using namespace circt::hlsest;
using llvm::SmallVector;
using llvm::StringRef;
namespace json = llvm::json;

namespace {

//===----------------------------------------------------------------------===//
// The compiled-in files.
//===----------------------------------------------------------------------===//

const char kBaseJson[] =
#include "base.json.inc"
    ;
const char kXc7z020Json[] =
#include "amd-xc7z020clg400-1.device.json.inc"
    ;
const char kVitis2025Json[] =
#include "vitis-2025.1.profile.json.inc"
    ;

struct CompiledIn {
  const char *id;
  const char *text;
};
const CompiledIn kDevices[] = {{"amd-xc7z020clg400-1", kXc7z020Json}};
const CompiledIn kProfiles[] = {{"vitis-2025.1", kVitis2025Json}};

//===----------------------------------------------------------------------===//
// JSON helpers.
//===----------------------------------------------------------------------===//

/// Removes the documentation keys (`_...`) of every object, recursively.
/// A device file's `_status` (validated | unvalidated) and `_sources` stay:
/// they are part of what the description claims.
void stripDocKeys(json::Value &v) {
  if (json::Object *o = v.getAsObject()) {
    std::vector<std::string> drop;
    for (auto &kv : *o)
      if (StringRef(kv.first).starts_with("_") && kv.first != "_status" &&
          kv.first != "_sources")
        drop.push_back(kv.first.str());
    for (const std::string &k : drop)
      o->erase(k);
    for (auto &kv : *o)
      stripDocKeys(kv.second);
  } else if (json::Array *a = v.getAsArray()) {
    for (json::Value &e : *a)
      stripDocKeys(e);
  }
}

/// Deep merge: objects key by key, anything else replaced.
void mergeInto(json::Value &target, const json::Value &overlay) {
  const json::Object *src = overlay.getAsObject();
  json::Object *dst = target.getAsObject();
  if (!src || !dst) {
    target = overlay;
    return;
  }
  for (const auto &kv : *src) {
    json::Value *existing = dst->get(kv.first);
    if (existing && existing->getAsObject() && kv.second.getAsObject())
      mergeInto(*existing, kv.second);
    else
      (*dst)[kv.first] = kv.second;
  }
}

std::optional<json::Value> parseJson(StringRef text, StringRef origin,
                                     ConfigDiagnostics &diag) {
  llvm::Expected<json::Value> v = json::parse(text);
  if (!v) {
    diag.errors.push_back(origin.str() + ": not valid JSON: " +
                          llvm::toString(v.takeError()));
    return std::nullopt;
  }
  if (!v->getAsObject()) {
    diag.errors.push_back(origin.str() + ": the top level is not an object");
    return std::nullopt;
  }
  stripDocKeys(*v);
  return std::move(*v);
}

std::optional<json::Value> readJsonFile(StringRef path,
                                        ConfigDiagnostics &diag) {
  auto buf = llvm::MemoryBuffer::getFile(path);
  if (!buf) {
    diag.errors.push_back(path.str() + ": cannot read: " +
                          buf.getError().message());
    return std::nullopt;
  }
  return parseJson((*buf)->getBuffer(), path, diag);
}

/// A path relative to the directory of `baseFile` (empty: the working
/// directory), made absolute; absolute paths are returned unchanged.
std::string resolveRelative(StringRef path, StringRef baseFile) {
  if (path.empty() || llvm::sys::path::is_absolute(path) || baseFile.empty())
    return path.str();
  llvm::SmallString<256> p(llvm::sys::path::parent_path(baseFile));
  llvm::sys::path::append(p, path);
  llvm::sys::path::remove_dots(p, /*remove_dot_dot=*/true);
  return std::string(p);
}

bool looksLikePath(StringRef s) {
  return s.contains('/') || s.ends_with(".json");
}

/// The device file `idOrPath` (a compiled-in id, or a path relative to the
/// file that names it), with its own relative paths resolved.
std::optional<json::Value> loadDevice(StringRef idOrPath, StringRef baseFile,
                                      StringRef origin,
                                      ConfigDiagnostics &diag) {
  for (const CompiledIn &d : kDevices)
    if (idOrPath == d.id)
      return parseJson(d.text, std::string("<compiled-in ") + d.id + ">",
                       diag);
  if (!looksLikePath(idOrPath)) {
    std::string known;
    for (const CompiledIn &d : kDevices)
      known += (known.empty() ? "" : ", ") + std::string(d.id);
    diag.errors.push_back(origin.str() + ": run.device: '" + idOrPath.str() +
                          "' is neither a compiled-in device (" + known +
                          ") nor a .json path");
    return std::nullopt;
  }
  std::string path = resolveRelative(idOrPath, baseFile);
  std::optional<json::Value> v = readJsonFile(path, diag);
  if (!v)
    return std::nullopt;
  if (json::Value *t = v->getAsObject()->get("operator_table"))
    if (std::optional<StringRef> s = t->getAsString())
      *t = resolveRelative(*s, path);
  return v;
}

/// The profile file `idOrPath`: an object with `tool` and `scheduling`.
std::optional<json::Value> loadProfile(StringRef idOrPath, StringRef baseFile,
                                       StringRef origin,
                                       ConfigDiagnostics &diag) {
  std::optional<json::Value> v;
  std::string path;
  for (const CompiledIn &p : kProfiles)
    if (idOrPath == p.id)
      v = parseJson(p.text, std::string("<compiled-in ") + p.id + ">", diag);
  if (!v) {
    if (!looksLikePath(idOrPath)) {
      std::string known;
      for (const CompiledIn &p : kProfiles)
        known += (known.empty() ? "" : ", ") + std::string(p.id);
      diag.errors.push_back(origin.str() + ": run.tool: '" + idOrPath.str() +
                            "' is neither a compiled-in profile (" + known +
                            ") nor a .json path");
      return std::nullopt;
    }
    path = resolveRelative(idOrPath, baseFile);
    v = readJsonFile(path, diag);
    if (!v)
      return std::nullopt;
  }
  json::Object *o = v->getAsObject();
  if (!o->getObject("tool") || !o->getObject("scheduling")) {
    diag.errors.push_back(origin.str() + ": run.tool: '" + idOrPath.str() +
                          "' has no \"tool\" and \"scheduling\" objects");
    return std::nullopt;
  }
  if (!path.empty())
    if (json::Object *hls = o->getObject("tool")->getObject("hls"))
      if (json::Object *ml = hls->getObject("math_library"))
        if (json::Value *t = ml->get("table"))
          if (std::optional<StringRef> s = t->getAsString())
            *t = resolveRelative(*s, path);
  return v;
}

//===----------------------------------------------------------------------===//
// Building the document.
//===----------------------------------------------------------------------===//

/// Records which origin last set every leaf path of `overlay`.
void recordSources(const json::Value &overlay, const std::string &prefix,
                   const std::string &origin,
                   std::map<std::string, std::string> &sources) {
  if (const json::Object *o = overlay.getAsObject()) {
    if (o->empty() && !prefix.empty()) {
      sources[prefix] = origin; // an empty section is a leaf of the overlay
      return;
    }
    for (const auto &kv : *o)
      recordSources(kv.second,
                    prefix.empty() ? kv.first.str()
                                   : prefix + "." + kv.first.str(),
                    origin, sources);
    return;
  }
  sources[prefix] = origin;
}

class DocumentBuilder {
public:
  DocumentBuilder(ConfigDiagnostics &diag) : diag(diag) {}

  bool start() {
    std::optional<json::Value> base = parseJson(kBaseJson, "<compiled-in base>",
                                                diag);
    if (!base)
      return false;
    doc = std::move(*base);
    json::Object *run = doc.getAsObject()->getObject("run");
    std::optional<json::Value> dev =
        loadDevice(*run->getString("device"), "", "<defaults>", diag);
    std::optional<json::Value> prof =
        loadProfile(*run->getString("tool"), "", "<defaults>", diag);
    if (!dev || !prof)
      return false;
    (*doc.getAsObject())["device"] = std::move(*dev);
    for (auto &kv : *prof->getAsObject())
      (*doc.getAsObject())[kv.first] = kv.second;
    return true;
  }

  /// Applies one file (or the document an assignment built).
  void apply(json::Value overlay, StringRef baseFile, StringRef origin) {
    json::Object *o = overlay.getAsObject();
    if (json::Value *ver = o->get("version")) {
      std::optional<int64_t> v = ver->getAsInteger();
      if (!v || *v != 1)
        diag.errors.push_back(origin.str() +
                              ": version: this hls-est reads version 1");
    }
    if (json::Object *run = o->getObject("run")) {
      if (std::optional<StringRef> dev = run->getString("device")) {
        std::optional<json::Value> d = loadDevice(*dev, baseFile, origin, diag);
        if (d)
          (*doc.getAsObject())["device"] = std::move(*d);
        recordSources(json::Object{{"device", json::Object{}}}, "",
                      origin.str() + " (run.device)", sources);
        replaced.insert("device");
      }
      if (std::optional<StringRef> tool = run->getString("tool")) {
        std::optional<json::Value> p = loadProfile(*tool, baseFile, origin,
                                                   diag);
        if (p)
          for (auto &kv : *p->getAsObject())
            (*doc.getAsObject())[kv.first] = kv.second;
        replaced.insert("tool");
        replaced.insert("scheduling");
      }
    }
    // Paths in a file are relative to that file.
    if (!baseFile.empty()) {
      if (json::Object *tool = o->getObject("tool"))
        if (json::Object *hls = tool->getObject("hls"))
          if (json::Object *ml = hls->getObject("math_library"))
            if (json::Value *t = ml->get("table"))
              if (std::optional<StringRef> s = t->getAsString())
                *t = resolveRelative(*s, baseFile);
      if (json::Object *dev = o->getObject("device"))
        if (json::Value *t = dev->get("operator_table"))
          if (std::optional<StringRef> s = t->getAsString())
            *t = resolveRelative(*s, baseFile);
    }
    recordSources(overlay, "", origin.str(), sources);
    mergeInto(doc, overlay);
  }

  /// `path=value`; the path may index arrays (`a.b[0].c`).
  void set(StringRef assignment) {
    std::string origin = "--config-set " + assignment.str();
    auto [path, text] = assignment.split('=');
    path = path.trim();
    if (path.empty() || !assignment.contains('=')) {
      diag.errors.push_back(origin + ": expected <key.path>=<value>");
      return;
    }
    json::Value value = nullptr;
    llvm::Expected<json::Value> parsed = json::parse(text);
    if (parsed) {
      value = std::move(*parsed);
      stripDocKeys(value);
    } else {
      llvm::consumeError(parsed.takeError());
      value = text.str(); // a bare word is a string
    }
    if (path == "run.device" || path == "run.tool") {
      json::Object run{{path.drop_front(4).str(), value}};
      apply(json::Object{{"run", std::move(run)}}, "", origin);
      return;
    }
    // Walk to the parent, creating objects on the way.
    SmallVector<StringRef> parts;
    path.split(parts, '.');
    json::Value *cur = &doc;
    std::string done;
    for (size_t i = 0; i < parts.size(); ++i) {
      StringRef part = parts[i];
      std::optional<size_t> index;
      if (part.ends_with("]")) {
        size_t lb = part.find('[');
        size_t n = 0;
        if (lb == StringRef::npos ||
            part.slice(lb + 1, part.size() - 1).getAsInteger(10, n)) {
          diag.errors.push_back(origin + ": bad array index in '" +
                                part.str() + "'");
          return;
        }
        index = n;
        part = part.take_front(lb);
      }
      done += (done.empty() ? "" : ".") + part.str();
      json::Object *o = cur->getAsObject();
      if (!o) {
        diag.errors.push_back(origin + ": " + done + " is not an object");
        return;
      }
      bool last = i + 1 == parts.size();
      if (last && !index) {
        (*o)[part.str()] = value;
        sources[path.str()] = origin;
        return;
      }
      json::Value *next = o->get(part);
      if (!next) {
        if (index) {
          diag.errors.push_back(origin + ": " + done + " is not an array");
          return;
        }
        (*o)[part.str()] = json::Object{};
        next = o->get(part);
      }
      if (index) {
        json::Array *a = next->getAsArray();
        if (!a || *index >= a->size()) {
          diag.errors.push_back(origin + ": " + done + "[" +
                                std::to_string(*index) +
                                "] does not exist");
          return;
        }
        next = &(*a)[*index];
        done += "[" + std::to_string(*index) + "]";
        if (last) {
          *next = value;
          sources[path.str()] = origin;
          return;
        }
      }
      cur = next;
    }
  }

  json::Value doc = nullptr;
  std::map<std::string, std::string> sources;
  llvm::StringSet<> replaced;

private:
  ConfigDiagnostics &diag;
};

//===----------------------------------------------------------------------===//
// Validation against the schema.
//===----------------------------------------------------------------------===//

/// Levenshtein distance, for "did you mean".
unsigned editDistance(StringRef a, StringRef b) {
  return a.edit_distance(b, /*AllowReplacements=*/true);
}

class Validator {
public:
  explicit Validator(ConfigDiagnostics &diag) : diag(diag) {}

  void validate(const json::Value &doc) { object(doc, "", "<config>"); }

private:
  ConfigDiagnostics &diag;

  void error(const std::string &where, const std::string &msg) {
    diag.errors.push_back(where + ": " + msg);
  }

  static std::string child(const std::string &pattern, StringRef key) {
    return pattern.empty() ? key.str() : pattern + "." + key.str();
  }

  /// The keys a section at `pattern` may hold.
  static std::vector<const KeySpec *> childrenOf(const std::string &pattern) {
    std::vector<const KeySpec *> out;
    for (const KeySpec &k : configSchema()) {
      StringRef p(k.path);
      if (pattern.empty()) {
        if (!p.contains('.'))
          out.push_back(&k);
        continue;
      }
      if (p.starts_with(pattern + ".") &&
          !p.drop_front(pattern.size() + 1).contains('.'))
        out.push_back(&k);
    }
    return out;
  }

  void object(const json::Value &v, const std::string &pattern,
              const std::string &where) {
    const json::Object *o = v.getAsObject();
    if (!o) {
      error(where, "expected an object");
      return;
    }
    std::vector<const KeySpec *> kids = childrenOf(pattern);
    for (const auto &kv : *o) {
      StringRef key = kv.first;
      if (key.starts_with("_"))
        continue;
      std::string childPattern = child(pattern, key);
      std::string childWhere =
          pattern.empty() ? key.str() : where + "." + key.str();
      const KeySpec *spec = findKeySpec(childPattern);
      if (!spec) {
        std::string msg = "unknown key";
        unsigned best = ~0u;
        StringRef bestName;
        for (const KeySpec *k : kids) {
          StringRef name = StringRef(k->path).rsplit('.').second;
          if (name.empty())
            name = k->path;
          unsigned d = editDistance(key, name);
          if (d < best) {
            best = d;
            bestName = name;
          }
        }
        if (!bestName.empty() && best <= std::max<size_t>(2, key.size() / 3))
          msg += " (did you mean " + bestName.str() + "?)";
        error(childWhere, msg);
        continue;
      }
      value(kv.second, *spec, childWhere);
    }
    for (const KeySpec *k : kids) {
      StringRef name = StringRef(k->path).rsplit('.').second;
      if (name.empty())
        name = k->path;
      if (!k->optional && !o->get(name))
        error(pattern.empty() ? name.str() : where + "." + name.str(),
              "missing (required)");
    }
  }

  void number(const json::Value &v, const KeySpec &spec,
              const std::string &where) {
    std::optional<double> d = v.getAsNumber();
    if (!d)
      return;
    if (!std::isnan(spec.min) && *d < spec.min)
      error(where, "out of range: " + formatNumber(*d) + " < minimum " +
                       formatNumber(spec.min));
    if (!std::isnan(spec.max) && *d > spec.max)
      error(where, "out of range: " + formatNumber(*d) + " > maximum " +
                       formatNumber(spec.max));
  }

  static std::string formatNumber(double d) {
    if (d == std::floor(d) && std::fabs(d) < 1e15)
      return std::to_string(static_cast<int64_t>(d));
    return std::to_string(d);
  }

  bool isInteger(const json::Value &v) { return v.getAsInteger().has_value(); }

  /// A whole number beyond the 64-bit signed range (JSON reads it, but not as
  /// an integer): out of range rather than of the wrong type.
  bool tooLarge(const json::Value &v, const std::string &where) {
    std::optional<double> d = v.getAsNumber();
    if (isInteger(v) || !d || *d != std::floor(*d))
      return false;
    char text[32];
    std::snprintf(text, sizeof(text), "%.17g", *d);
    error(where, "out of range: " + std::string(text) +
                     " exceeds the 64-bit integer range");
    return true;
  }

  void enumValue(StringRef s, StringRef values, const std::string &where) {
    SmallVector<StringRef> allowed;
    values.split(allowed, '|');
    if (!llvm::is_contained(allowed, s))
      error(where, "'" + s.str() + "' is not one of " +
                       llvm::join(allowed, ", "));
  }

  void value(const json::Value &v, const KeySpec &spec,
             const std::string &where) {
    auto typeError = [&](StringRef expected) {
      error(where, "wrong type: expected " + expected.str());
    };
    switch (spec.kind) {
    case KeyKind::Section:
      object(v, spec.path, where);
      return;
    case KeyKind::ObjectList: {
      const json::Array *a = v.getAsArray();
      if (!a)
        return typeError("an array of objects");
      for (size_t i = 0; i < a->size(); ++i)
        object((*a)[i], std::string(spec.path) + "[]",
               where + "[" + std::to_string(i) + "]");
      return;
    }
    case KeyKind::FreeObject:
      if (!v.getAsObject())
        typeError("an object");
      return;
    case KeyKind::FreeArray:
      if (!v.getAsArray())
        typeError("an array");
      return;
    case KeyKind::Bool:
      if (!v.getAsBoolean())
        typeError("true or false");
      return;
    case KeyKind::Int:
      if (tooLarge(v, where))
        return;
      if (!isInteger(v))
        return typeError("an integer");
      number(v, spec, where);
      return;
    case KeyKind::UInt:
      if (tooLarge(v, where))
        return;
      if (!isInteger(v) || *v.getAsInteger() < 0)
        return typeError("a non-negative integer");
      number(v, spec, where);
      return;
    case KeyKind::NullableUInt:
      if (v.kind() == json::Value::Null || tooLarge(v, where))
        return;
      if (!isInteger(v) || *v.getAsInteger() < 0)
        return typeError("a non-negative integer or null");
      number(v, spec, where);
      return;
    case KeyKind::Number:
      if (!v.getAsNumber())
        return typeError("a number");
      number(v, spec, where);
      return;
    case KeyKind::String:
      if (!v.getAsString())
        typeError("a string");
      return;
    case KeyKind::NullablePath:
      if (v.kind() != json::Value::Null && !v.getAsString())
        typeError("a path string or null");
      return;
    case KeyKind::NullableObject:
      if (v.kind() != json::Value::Null && !v.getAsObject())
        typeError("an object or null");
      return;
    case KeyKind::Enum:
      if (std::optional<StringRef> s = v.getAsString())
        enumValue(*s, spec.values, where);
      else
        typeError("a string");
      return;
    case KeyKind::PluginName: {
      std::optional<StringRef> s = v.getAsString();
      if (!s)
        return typeError("a plugin name");
      const PluginNameCheck &check = getPluginNameCheck();
      std::string known;
      if (check && !check(spec.values, *s, known))
        error(where, "no " + std::string(spec.values) + " plugin named '" +
                         s->str() + "' is registered (registered: " + known +
                         ")");
      return;
    }
    case KeyKind::StringList: {
      const json::Array *a = v.getAsArray();
      if (!a)
        return typeError("an array of strings");
      for (size_t i = 0; i < a->size(); ++i) {
        std::optional<StringRef> s = (*a)[i].getAsString();
        std::string w = where + "[" + std::to_string(i) + "]";
        if (!s)
          error(w, "wrong type: expected a string");
        else if (*spec.values)
          enumValue(*s, spec.values, w);
      }
      return;
    }
    case KeyKind::PortSetList: {
      const json::Array *a = v.getAsArray();
      if (!a)
        return typeError("an array of port sets");
      for (size_t i = 0; i < a->size(); ++i) {
        std::string w = where + "[" + std::to_string(i) + "]";
        const json::Array *set = (*a)[i].getAsArray();
        if (!set) {
          error(w, "wrong type: expected an array of r / w / rw");
          continue;
        }
        for (size_t j = 0; j < set->size(); ++j) {
          std::optional<StringRef> s = (*set)[j].getAsString();
          std::string wj = w + "[" + std::to_string(j) + "]";
          if (!s)
            error(wj, "wrong type: expected r, w or rw");
          else
            enumValue(*s, "r|w|rw", wj);
        }
      }
      return;
    }
    case KeyKind::ResourceVector: {
      const json::Object *o = v.getAsObject();
      if (!o)
        return typeError("an object {class: count}");
      for (const auto &kv : *o)
        if (!StringRef(kv.first).starts_with("_") &&
            !Rational::fromJson(kv.second))
          error(where + "." + kv.first.str(),
                "wrong type: expected a non-negative integer or \"n/d\"");
      return;
    }
    case KeyKind::IntMap: {
      const json::Object *o = v.getAsObject();
      if (!o)
        return typeError("an object {name: integer}");
      for (const auto &kv : *o) {
        if (StringRef(kv.first).starts_with("_"))
          continue;
        std::string w = where + "." + kv.first.str();
        if (tooLarge(kv.second, w))
          continue;
        if (!isInteger(kv.second))
          error(w, "wrong type: expected an integer");
        else
          number(kv.second, spec, w);
      }
      return;
    }
    }
  }
};

//===----------------------------------------------------------------------===//
// Typed fill (after validation: present keys have the right type).
//===----------------------------------------------------------------------===//

const json::Object &obj(const json::Object &o, StringRef key) {
  static const json::Object empty;
  const json::Object *p = o.getObject(key);
  return p ? *p : empty;
}
std::string str(const json::Object &o, StringRef key,
                StringRef dflt = StringRef()) {
  if (std::optional<StringRef> s = o.getString(key))
    return s->str();
  return dflt.str();
}
int64_t integer(const json::Object &o, StringRef key, int64_t dflt = 0) {
  if (std::optional<int64_t> i = o.getInteger(key))
    return *i;
  return dflt;
}
std::optional<int64_t> optInteger(const json::Object &o, StringRef key) {
  return o.getInteger(key);
}
double number(const json::Object &o, StringRef key, double dflt = 0) {
  if (std::optional<double> d = o.getNumber(key))
    return *d;
  return dflt;
}
std::optional<double> optNumber(const json::Object &o, StringRef key) {
  return o.getNumber(key);
}
bool boolean(const json::Object &o, StringRef key, bool dflt = false) {
  if (std::optional<bool> b = o.getBoolean(key))
    return *b;
  return dflt;
}
std::vector<std::string> strings(const json::Object &o, StringRef key) {
  std::vector<std::string> out;
  if (const json::Array *a = o.getArray(key))
    for (const json::Value &v : *a)
      if (std::optional<StringRef> s = v.getAsString())
        out.push_back(s->str());
  return out;
}
ResourceVector resources(const json::Object &o, StringRef key) {
  ResourceVector r;
  if (const json::Object *rv = o.getObject(key))
    for (const auto &kv : *rv)
      if (std::optional<Rational> n = Rational::fromJson(kv.second))
        r.add(kv.first, *n);
  return r;
}
template <class F>
void eachObject(const json::Object &o, StringRef key, F f) {
  if (const json::Array *a = o.getArray(key))
    for (const json::Value &v : *a)
      if (const json::Object *e = v.getAsObject())
        f(*e);
}

void fillDevice(const json::Object &d, Device &dev) {
  dev.id = str(d, "id");
  dev.part = str(d, "part");
  dev.speedGrade = str(d, "speed_grade");
  dev.status = str(d, "_status", "unvalidated");
  dev.toolIds = obj(d, "tool_ids");
  eachObject(d, "resource_classes", [&](const json::Object &c) {
    ResourceClass rc;
    rc.name = str(c, "name");
    rc.capacity = optInteger(c, "capacity");
    rc.reportLabel = str(c, "report_label");
    rc.equivalent = resources(c, "equivalent");
    dev.resourceClasses.push_back(std::move(rc));
  });
  eachObject(d, "memories", [&](const json::Object &m) {
    DeviceMemory mem;
    mem.id = str(m, "id");
    mem.tier = str(m, "tier");
    mem.cost = resources(m, "cost");
    mem.overhead = resources(m, "overhead");
    mem.bits = integer(m, "bits");
    eachObject(m, "geometries", [&](const json::Object &g) {
      mem.geometries.push_back(
          {integer(g, "width"), integer(g, "depth"), optInteger(g, "byte")});
    });
    eachObject(m, "port_configs", [&](const json::Object &p) {
      PortConfig pc;
      pc.name = str(p, "name");
      pc.ports = strings(p, "ports");
      pc.maxWidth = integer(p, "max_width");
      pc.mixedWidth = boolean(p, "mixed_width");
      mem.portConfigs.push_back(std::move(pc));
    });
    mem.init = str(m, "init");
    eachObject(m, "read_latency_options", [&](const json::Object &r) {
      mem.readLatencyOptions.push_back(
          {integer(r, "cycles"), optNumber(r, "max_freq_mhz")});
    });
    mem.fmaxMhz = optNumber(m, "fmax_mhz");
    dev.memories.push_back(std::move(mem));
  });
  eachObject(d, "shift_registers", [&](const json::Object &s) {
    dev.shiftRegisters.push_back({str(s, "id"), integer(s, "max_depth"),
                                  integer(s, "width"), resources(s, "cost")});
  });
  eachObject(d, "arith", [&](const json::Object &a) {
    ArithBlock b;
    b.id = str(a, "id");
    b.cost = resources(a, "cost");
    b.overhead = resources(a, "overhead");
    eachObject(a, "mul", [&](const json::Object &m) {
      b.mul.push_back({integer(m, "a"), integer(m, "b"), str(m, "signed"),
                       integer(m, "count", 1)});
    });
    b.preAdd = optInteger(a, "pre_add");
    b.acc = optInteger(a, "acc");
    b.hardFp = strings(a, "hard_fp");
    b.fmaxMhz = optNumber(a, "fmax_mhz");
    dev.arith.push_back(std::move(b));
  });
  const json::Object &l = obj(d, "logic");
  dev.logic.cell = str(l, "cell");
  dev.logic.lutInputs = integer(l, "lut_inputs");
  dev.logic.fracturable = l.getBoolean("fracturable");
  dev.logic.regsPerCell = optInteger(l, "regs_per_cell");
  dev.logic.cost = resources(l, "cost");
  if (const json::Value *t = d.get("timing"))
    if (t->kind() != json::Value::Null)
      dev.timing = *t;
  dev.operatorTable = str(d, "operator_table");
}

void fillTool(const json::Object &t, ToolProfile &tool) {
  tool.id = str(t, "id");
  tool.name = str(t, "name");
  tool.version = str(t, "version");
  tool.pipeline = str(t, "pipeline");
  const json::Object &hls = obj(t, "hls");
  HlsToolConfig &h = tool.hls;
  const json::Object &opts = obj(hls, "options");
  h.options.flowTarget = str(opts, "flow_target");
  h.options.pipelineLoops = integer(opts, "pipeline_loops");
  const json::Object &ap = obj(opts, "array_partition");
  h.options.arrayPartition.throughputDriven = str(ap, "throughput_driven");
  h.options.arrayPartition.completeThreshold =
      integer(ap, "complete_threshold");
  h.options.arrayPartition.includePorts = boolean(ap, "include_ports");
  const json::Object &tm = obj(hls, "timing_margin");
  h.timingMargin.fraction = optNumber(tm, "fraction");
  h.timingMargin.ns = optNumber(tm, "ns");

  const json::Object &ma = obj(hls, "memory_architecture");
  MemoryArchitectureConfig &m = h.memoryArchitecture;
  m.plugin = str(ma, "plugin");
  m.untrackedMemoryPorts = integer(ma, "untracked_memory_ports");
  m.partitionedArgumentBankPorts =
      boolean(ma, "partitioned_argument_bank_ports", true);
  m.oneLoopReadWriteSdp = boolean(ma, "one_loop_read_write_sdp", true);
  m.iterationPrivateRegisters =
      boolean(ma, "iteration_private_registers", true);
  m.portOccupancyCycles = integer(ma, "port_occupancy_cycles");
  const json::Object &rep = obj(ma, "replication");
  m.replication.maxCopies = integer(rep, "max_copies");
  m.replication.maxStoresPerIteration =
      integer(rep, "max_stores_per_iteration");
  m.replication.sharedWritePortReadsWhenIdle =
      boolean(rep, "shared_write_port_reads_when_idle");
  m.replication.exclusiveArmStoresOnce =
      boolean(rep, "exclusive_arm_stores_once");
  m.replication.calleeStoresPerLoop = boolean(rep, "callee_stores_per_loop");
  m.replication.portBoundSeveralArrays =
      boolean(rep, "port_bound_several_arrays", true);
  m.replication.portBoundWritableGlobals =
      boolean(rep, "port_bound_writable_globals", true);
  const json::Object &rom = obj(ma, "rom");
  m.rom.sdpMaxReads = integer(rom, "sdp_max_reads");
  m.rom.copies = str(rom, "copies");
  m.sequentialScopeModel = str(obj(ma, "sequential_scope"), "model");
  m.portSetRule = str(ma, "port_set_rule");
  if (const json::Array *sets = ma.getArray("wide_port_sets"))
    for (const json::Value &s : *sets) {
      std::vector<std::string> set;
      if (const json::Array *a = s.getAsArray())
        for (const json::Value &p : *a)
          if (std::optional<StringRef> ps = p.getAsString())
            set.push_back(ps->str());
      m.widePortSets.push_back(std::move(set));
    }
  const json::Object &pc = obj(ma, "priced_configs");
  m.pricedWide = str(pc, "wide");
  m.pricedNarrow = str(pc, "narrow");

  eachObject(hls, "implicit_buffers", [&](const json::Object &b) {
    ImplicitBufferConfig ib;
    ib.source = str(b, "source");
    ib.protocol = str(b, "protocol");
    ib.mode = str(b, "mode");
    ib.plugin = str(b, "plugin");
    ib.enabled = boolean(b, "enabled", true);
    ib.defaultBundle = str(b, "default_bundle");
    ib.minBusBits = integer(b, "min_bus_bits", 32);
    ib.maxBusBits = integer(b, "max_bus_bits", 1024);
    const json::Object &d = obj(b, "defaults");
    ib.defaults.maxReadBurstLength = integer(d, "max_read_burst_length", 16);
    ib.defaults.numReadOutstanding = integer(d, "num_read_outstanding", 16);
    ib.defaults.maxWriteBurstLength = integer(d, "max_write_burst_length", 16);
    ib.defaults.numWriteOutstanding = integer(d, "num_write_outstanding", 16);
    const json::Object &rf = obj(b, "read_fifo");
    ib.readFifoSrlMaxDepth = integer(rf, "srl_max_depth", 32);
    ib.readFifoMapper = str(rf, "mapper", "vitis-band7");
    ib.readFifoPricedConfig = str(rf, "priced_config", "tdp");
    ib.readFifoConfirmedMaxDepth = integer(rf, "confirmed_max_depth", 4096);
    ib.readFifoPerChannel = boolean(rf, "per_channel", true);
    ib.readFifoCastLoadWidth = boolean(rf, "cast_load_width", true);
    ib.readFifoPowerOfTwoWidth = boolean(rf, "power_of_two_width", true);
    const json::Object &wb = obj(b, "write_buffer");
    ib.writeBufferFreeMaxBurst = integer(wb, "free_max_burst", 16);
    ib.writeBufferPortWidthBits = integer(wb, "port_width_bits", 18);
    ib.writeBufferConfirmedMinBurst = integer(wb, "confirmed_min_burst", 32);
    ib.unresolvedCall = str(b, "unresolved_call", "rw");
    h.implicitBuffers.push_back(std::move(ib));
  });

  const json::Object &st = obj(hls, "streams");
  h.streams.enabled = boolean(st, "enabled");
  h.streams.defaultDepth = integer(st, "default_depth");
  h.streams.srlMaxDepth = integer(st, "srl_max_depth");
  h.streams.srlMaxBits = integer(st, "srl_max_bits");
  h.streams.mapper = str(st, "mapper");
  h.streams.pricedConfig = str(st, "priced_config");
  h.streams.dataflowArgumentFifos =
      boolean(st, "dataflow_argument_fifos", true);
  h.streams.distinctElementInstances =
      boolean(st, "distinct_element_instances", true);
  h.streams.declaredElementBits =
      boolean(st, "declared_element_bits", true);
  h.streams.streamPragmaArrays = boolean(st, "stream_pragma_arrays", true);
  const json::Object &dc = obj(hls, "dataflow_channels");
  h.dataflowChannels.enabled = boolean(dc, "enabled");
  h.dataflowChannels.defaultBlocks = integer(dc, "default_blocks");
  h.dataflowChannels.throughNestedRegions =
      boolean(dc, "through_nested_regions", true);

  const json::Object &pd = obj(hls, "pipeline_decision");
  h.pipelineDecision.policy = str(pd, "policy");
  h.pipelineDecision.floatLoadsPerfect = boolean(pd, "float_loads_perfect");
  h.pipelineDecision.promotePipelined = boolean(pd, "promote_pipelined");
  h.pipelineDecision.flattenAcrossCalls = boolean(pd, "flatten_across_calls");
  h.pipelineDecision.sinkParentCode =
      boolean(pd, "sink_parent_code", true);
  h.pipelineDecision.foldUnrolledGuards =
      boolean(pd, "fold_unrolled_guards", true);

  const json::Object &pa = obj(hls, "partitioning");
  h.partitioning.policy = str(pa, "policy");
  h.partitioning.constantIndexMinExtent =
      integer(obj(pa, "constant_index"), "min_extent");
  h.partitioning.constantIndexMaxExtent =
      integer(obj(pa, "constant_index"), "max_extent", 0);
  h.partitioning.constantIndexAfterUserPartition =
      boolean(obj(pa, "constant_index"), "after_user_partition", true);
  h.partitioning.constantIndexNonAffineArrays =
      boolean(obj(pa, "constant_index"), "non_affine_arrays", true);
  h.partitioning.constantIndexPipoStreams =
      boolean(obj(pa, "constant_index"), "pipo_streams", true);
  h.partitioning.constantIndexGlobals =
      boolean(obj(pa, "constant_index"), "globals", true);
  h.partitioning.compoundAssignTwoStores =
      boolean(pa, "compound_assign_two_stores", true);
  h.partitioning.blockBankFromLoopRange =
      boolean(pa, "block_bank_from_loop_range", true);
  const json::Object &inf = obj(pa, "inference");
  PartitionInferenceConfig &pi = h.partitioning.inference;
  pi.targetII = integer(inf, "target_ii");
  const json::Object &ports = obj(inf, "ports");
  pi.portsAny = integer(ports, "any");
  pi.portsRead = integer(ports, "read");
  pi.portsWrite = integer(ports, "write");
  pi.maxFactor = integer(inf, "max_factor");
  pi.maxDims = integer(inf, "max_dims");
  pi.rotatingBanks = boolean(inf, "rotating_banks");
  pi.maxScannedFactor = integer(inf, "max_scanned_factor");
  h.partitioning.steerAffineLoads = boolean(pa, "steer_affine_loads");
  h.partitioning.steerWindowGroups =
      boolean(pa, "steer_window_groups", true);

  const json::Object &fo = obj(hls, "folding");
  h.folding.ruleSet = str(fo, "rule_set");
  h.folding.canonicalize = boolean(fo, "canonicalize");
  h.folding.maxRounds = integer(fo, "max_rounds");

  const json::Object &me = obj(hls, "middle_end");
  MiddleEndConfig &mid = h.middleEnd;
  mid.licmHoistInvariantLoads = boolean(me, "licm_hoist_invariant_loads");
  mid.licmHoistPastCalls = boolean(me, "licm_hoist_past_calls");
  mid.licmHoistConditional = boolean(me, "licm_hoist_conditional");
  mid.mergeIfElseAccesses = boolean(me, "merge_if_else_accesses");
  mid.gvnLoads = boolean(me, "gvn_loads");
  mid.gvnConditionalLoads = boolean(me, "gvn_conditional_loads", true);
  mid.dseGuardedStores = boolean(me, "dse_guarded_stores", true);
  mid.forwardToGuardedLoads = boolean(me, "forward_to_guarded_loads", true);
  mid.storeForwarding = boolean(me, "store_forwarding");
  const json::Object &dm = obj(me, "dead_memory");
  mid.deadMemory.overwrittenStores = boolean(dm, "overwritten_stores");
  mid.deadMemory.deadCalls = boolean(dm, "dead_calls");
  mid.deadMemory.honourPreserve = boolean(dm, "honour_preserve");
  mid.deadMemory.globalSharedByFunctionsEscapes =
      boolean(dm, "global_shared_by_functions_escapes");
  mid.deadMemory.keepLoadStoreCycles =
      boolean(dm, "load_store_cycles", true);

  h.honourInlineOff = boolean(obj(hls, "inlining"), "honour_inline_off");
  const json::Object &sc = obj(hls, "structs");
  h.structs.aggregate = boolean(sc, "aggregate");
  h.structs.globals = boolean(sc, "globals");
  h.structs.scalarRegisters = boolean(sc, "scalar_registers");
  h.structs.throughCalls = boolean(sc, "through_calls");
  h.structs.elementCopyLoops = boolean(sc, "element_copy_loops", true);
  h.structs.temporaryRegisters = boolean(sc, "temporary_registers", true);
  h.structs.memberPartitions = boolean(sc, "member_partitions", true);
  const json::Object &na = obj(hls, "narrowing");
  h.narrowing.storedRanges = boolean(na, "stored_ranges");
  h.narrowing.loadDemand = boolean(na, "load_demand");
  h.narrowing.fullAddressInterfaceModes =
      strings(na, "full_address_interface_modes");
  h.narrowing.completeReadSelector =
      boolean(na, "complete_read_selector", true);
  h.globalsAttributeAccesses =
      boolean(obj(hls, "globals"), "attribute_accesses");
  h.groupingPlugin = str(obj(hls, "grouping"), "plugin");
  h.mathLibraryTable = str(obj(hls, "math_library"), "table");
  h.localStructTablesAtRunTime =
      boolean(obj(hls, "math_library"), "local_struct_tables_at_run_time", true);

  const json::Object &be = obj(t, "backend");
  tool.backend.id = str(be, "id");
  const json::Object &ss = obj(be, "storage_selector");
  StorageSelectorConfig &sel = tool.backend.storageSelector;
  sel.plugin = str(ss, "plugin");
  sel.minBlockBits = integer(ss, "min_block_bits");
  sel.inclusive = boolean(ss, "inclusive");
  sel.block = str(ss, "block");
  sel.below = str(ss, "below");
  const json::Object &mm = obj(be, "memory_mapper");
  MemoryMapperConfig &map = tool.backend.memoryMapper;
  map.plugin = str(mm, "plugin");
  map.primitive = str(mm, "primitive");
  map.depthRounding = str(mm, "depth_rounding");
  map.acceptedLibraries = strings(mm, "accepted_libraries");
  map.mixedColumns = boolean(mm, "mixed_columns");
  map.depthStack = boolean(mm, "depth_stack");
  eachObject(mm, "depth_bands", [&](const json::Object &b) {
    DepthBand band;
    band.maxDepth = optInteger(b, "max_depth");
    band.beyond = boolean(b, "beyond");
    band.width = optInteger(b, "width");
    band.sdpWidth = optInteger(b, "sdp_width");
    band.tdpWidth = optInteger(b, "tdp_width");
    if (const json::Object *alt = b.getObject("alternative")) {
      band.altWidth = optInteger(*alt, "width");
      band.altStack = optInteger(*alt, "stack");
    }
    band.wordsPerBlock = optInteger(b, "words_per_block");
    map.depthBands.push_back(band);
  });
  const json::Object &rp = obj(t, "report");
  tool.report.primaryMemoryClass = str(rp, "primary_memory_class");
  tool.report.stdoutFormat = str(rp, "stdout_format");
  tool.report.referenceStage = str(rp, "reference_stage");
  tool.report.classes = strings(rp, "classes");
}

void fillScheduling(const json::Object &s, SchedulingConfig &sc) {
  const json::Object &t = obj(s, "timing");
  sc.timingModel = str(t, "model");
  for (const auto &kv : obj(t, "operator_latencies"))
    if (std::optional<int64_t> i = kv.second.getAsInteger())
      sc.operatorLatencies[kv.first.str()] = *i;
  const json::Object &de = obj(s, "dependences");
  sc.dependenceModel = str(de, "model");
  sc.memoryRecurrences = boolean(de, "memory_recurrences", true);
  for (const auto &kv : obj(de, "recurrence_latencies"))
    if (std::optional<int64_t> i = kv.second.getAsInteger())
      sc.recurrenceLatencies[kv.first.str()] = *i;
  const json::Object &mo = obj(s, "modulo");
  sc.moduloModel = str(mo, "model");
  sc.fastThreshold = integer(mo, "fast_threshold");
  sc.fastOpsThreshold = integer(mo, "fast_ops_threshold");
  sc.maxPipelineBodyOps = integer(mo, "max_pipeline_body_ops", 250000);
  sc.maxIIBumps = integer(mo, "max_ii_bumps");
  sc.recurrenceRepairRounds = integer(mo, "recurrence_repair_rounds");
  sc.userIITarget = boolean(mo, "user_ii_target");
  sc.sequentialModel = str(obj(s, "sequential"), "model");
  sc.bindingModel = str(obj(s, "binding"), "model");
  sc.emitDetail = boolean(s, "emit_detail");
  const json::Object &cd = obj(s, "call_depth");
  CallDepthConfig &c = sc.callDepth;
  c.loadDataNs = number(cd, "load_data_ns");
  c.logicNs = number(cd, "logic_ns");
  c.selectNs = number(cd, "select_ns");
  c.variableShiftNs = number(cd, "variable_shift_ns");
  c.constantMultiplierNs = number(cd, "constant_multiplier_ns");
  c.narrowMultiplyMaxBits = integer(cd, "narrow_multiply_max_bits");
  c.narrowMultiplyCycles = integer(cd, "narrow_multiply_cycles");
  c.portsPerMemory = integer(cd, "ports_per_memory");
  c.indexBits = integer(cd, "index_bits");
  eachObject(cd, "carry_chain_ns", [&](const json::Object &b) {
    c.carryChainNs.push_back({optInteger(b, "max_bits"), number(b, "ns")});
  });
  eachObject(cd, "ternary_adder_ns", [&](const json::Object &b) {
    c.ternaryAdderNs.push_back({optInteger(b, "max_bits"), number(b, "ns")});
  });
}

void fill(const json::Value &doc, Config &cfg) {
  const json::Object &root = *doc.getAsObject();
  cfg.version = integer(root, "version", 1);
  const json::Object &run = obj(root, "run");
  cfg.run.device = str(run, "device");
  cfg.run.tool = str(run, "tool");
  cfg.run.clockNs = number(run, "clock_ns", 10);
  fillDevice(obj(root, "device"), cfg.device);
  fillTool(obj(root, "tool"), cfg.tool);
  fillScheduling(obj(root, "scheduling"), cfg.scheduling);
  const json::Object &fe = obj(root, "frontend");
  cfg.frontend.indexBits = integer(fe, "index_bits", 64);
  cfg.frontend.elementTypes = strings(fe, "element_types");
  cfg.frontend.userStoragePragmas = strings(fe, "user_storage_pragmas");
  cfg.plugins = obj(root, "plugins");
}

//===----------------------------------------------------------------------===//
// Cross-key checks (on the typed configuration).
//===----------------------------------------------------------------------===//

void crossCheck(const Config &c, ConfigDiagnostics &diag) {
  auto err = [&](const std::string &where, const std::string &msg) {
    diag.errors.push_back(where + ": " + msg);
  };
  const Device &d = c.device;
  llvm::StringSet<> classes;
  for (const ResourceClass &rc : d.resourceClasses)
    if (!classes.insert(rc.name).second)
      err("device.resource_classes", "class '" + rc.name + "' declared twice");
  auto checkVector = [&](const ResourceVector &v, const std::string &where) {
    for (const auto &[name, n] : v.items())
      if (!classes.contains(name))
        err(where, "names the undeclared resource class '" + name + "'");
  };
  for (const ResourceClass &rc : d.resourceClasses)
    checkVector(rc.equivalent, "device.resource_classes(" + rc.name +
                                   ").equivalent");
  llvm::StringSet<> memIds;
  for (const DeviceMemory &m : d.memories) {
    std::string where = "device.memories(" + m.id + ")";
    if (!memIds.insert(m.id).second)
      err("device.memories", "memory id '" + m.id + "' declared twice");
    checkVector(m.cost, where + ".cost");
    checkVector(m.overhead, where + ".overhead");
    std::set<std::pair<int64_t, int64_t>> shapes;
    for (const Geometry &g : m.geometries) {
      if (!shapes.insert({g.width, g.depth}).second)
        err(where + ".geometries", "the shape " + std::to_string(g.depth) +
                                       "x" + std::to_string(g.width) +
                                       " is listed twice");
      if (g.width * g.depth > m.bits)
        err(where + ".geometries",
            std::to_string(g.depth) + "x" + std::to_string(g.width) +
                " holds more than the " + std::to_string(m.bits) +
                " bits of one instance");
    }
    for (const PortConfig &p : m.portConfigs)
      if (llvm::none_of(m.geometries, [&](const Geometry &g) {
            return g.width == p.maxWidth;
          }))
        err(where + ".port_configs(" + p.name + ").max_width",
            std::to_string(p.maxWidth) + " is the width of no geometry");
  }
  for (const ShiftRegister &s : d.shiftRegisters)
    checkVector(s.cost, "device.shift_registers(" + s.id + ").cost");
  for (const ArithBlock &a : d.arith) {
    checkVector(a.cost, "device.arith(" + a.id + ").cost");
    checkVector(a.overhead, "device.arith(" + a.id + ").overhead");
  }

  const ToolProfile &t = c.tool;
  const TimingMargin &tm = t.hls.timingMargin;
  if (tm.fraction && tm.ns)
    err("tool.hls.timing_margin", "give fraction or ns, not both");
  const MemoryMapperConfig &mm = t.backend.memoryMapper;
  // The depth bands of vitis-band7: increasing, exactly one `beyond`, last.
  int64_t prev = 0;
  unsigned beyond = 0;
  for (size_t i = 0; i < mm.depthBands.size(); ++i) {
    const DepthBand &b = mm.depthBands[i];
    std::string where =
        "tool.backend.memory_mapper.depth_bands[" + std::to_string(i) + "]";
    if (b.beyond) {
      ++beyond;
      if (i + 1 != mm.depthBands.size())
        err(where, "the beyond band must be the last one");
      if (!b.width || !b.wordsPerBlock)
        err(where, "the beyond band needs width and words_per_block");
      continue;
    }
    if (!b.maxDepth) {
      err(where, "needs max_depth (or beyond: true)");
      continue;
    }
    if (*b.maxDepth <= prev)
      err(where, "max_depth " + std::to_string(*b.maxDepth) +
                     " is not above the previous band's " +
                     std::to_string(prev));
    prev = *b.maxDepth;
    if (!b.width && !(b.sdpWidth && b.tdpWidth))
      err(where, "needs width, or sdp_width and tdp_width");
    if (b.altWidth.has_value() != b.altStack.has_value())
      err(where + ".alternative", "needs width and stack");
  }
  if (!mm.depthBands.empty() && beyond != 1)
    err("tool.backend.memory_mapper.depth_bands",
        "needs exactly one beyond band");

  // A port configuration a bank is priced at must exist in some memory of
  // the device (which memory prices a bank is decided later, per bank).
  auto checkPortConfig = [&](const std::string &where,
                             const std::string &name) {
    llvm::StringSet<> known;
    for (const DeviceMemory &m : d.memories)
      for (const PortConfig &p : m.portConfigs) {
        if (p.name == name)
          return;
        known.insert(p.name);
      }
    std::vector<std::string> names;
    for (const auto &k : known)
      names.push_back(k.getKey().str());
    llvm::sort(names);
    err(where, "'" + name + "' is the port configuration of no device "
                            "memory (device: " +
                   llvm::join(names, ", ") + ")");
  };
  const MemoryArchitectureConfig &ma = t.hls.memoryArchitecture;
  checkPortConfig("tool.hls.memory_architecture.priced_configs.wide",
                  ma.pricedWide);
  checkPortConfig("tool.hls.memory_architecture.priced_configs.narrow",
                  ma.pricedNarrow);
  if (t.hls.streams.enabled)
    checkPortConfig("tool.hls.streams.priced_config",
                    t.hls.streams.pricedConfig);
  for (size_t i = 0; i < t.hls.implicitBuffers.size(); ++i)
    if (t.hls.implicitBuffers[i].enabled)
      checkPortConfig("tool.hls.implicit_buffers[" + std::to_string(i) +
                          "].read_fifo.priced_config",
                      t.hls.implicitBuffers[i].readFifoPricedConfig);

  // Reserved: --auto-pipeline-unroll implements only the documented
  // assumption (D-11: a loop is never flattened across a call).
  if (t.hls.pipelineDecision.flattenAcrossCalls)
    err("tool.hls.pipeline_decision.flatten_across_calls",
        "true is not implemented (reserved; only false, D-11)");

  // A plugins.<name> section belongs to a plugin some plugin key selects;
  // any other name (a misspelt plugin) would drop its parameters silently.
  llvm::StringSet<> selected;
  for (const std::string *n :
       {&t.backend.storageSelector.plugin, &ma.plugin,
        &t.backend.memoryMapper.plugin, &t.hls.streams.mapper,
        &t.hls.groupingPlugin, &t.hls.pipelineDecision.policy,
        &t.hls.partitioning.policy, &t.hls.folding.ruleSet,
        &c.scheduling.timingModel, &c.scheduling.dependenceModel,
        &c.scheduling.moduloModel, &c.scheduling.sequentialModel,
        &c.scheduling.bindingModel})
    selected.insert(*n);
  for (const ImplicitBufferConfig &b : t.hls.implicitBuffers) {
    selected.insert(b.plugin);
    selected.insert(b.readFifoMapper);
  }
  for (const auto &kv : c.plugins) {
    StringRef name = kv.first;
    if (name.starts_with("_") || selected.contains(name))
      continue;
    err("plugins." + name.str(),
        "no plugin key selects a plugin named '" + name.str() +
            "', so nothing reads this section");
  }

  if (!classes.contains(t.report.primaryMemoryClass))
    err("tool.report.primary_memory_class",
        "'" + t.report.primaryMemoryClass +
            "' is not a resource class of the device");
  for (const std::string &cls : t.report.classes)
    if (!classes.contains(cls))
      err("tool.report.classes",
          "'" + cls + "' is not a resource class of the device");

  for (const auto &[cls, lat] : c.scheduling.operatorLatencies)
    if (lat < 0 && lat != -1)
      err("scheduling.timing.operator_latencies." + cls,
          "out of range: " + std::to_string(lat) + " < minimum -1");
    else if (lat == -1 && cls != "call" && cls != "kept_call")
      err("scheduling.timing.operator_latencies." + cls,
          "-1 (stay sequential) is allowed only for call and kept_call");
}

/// The math-core table's own `vitis` block names the configuration its
/// costs were measured in; a mismatch is a warning (memo section 4.2).
void checkMathTable(const Config &c, ConfigDiagnostics &diag) {
  const std::string &path = c.tool.hls.mathLibraryTable;
  if (path.empty())
    return;
  auto buf = llvm::MemoryBuffer::getFile(path);
  if (!buf) {
    diag.errors.push_back("tool.hls.math_library.table: cannot read '" +
                          path + "': " + buf.getError().message());
    return;
  }
  llvm::Expected<json::Value> v = json::parse((*buf)->getBuffer());
  if (!v) {
    llvm::consumeError(v.takeError());
    return; // --bram-analysis reports the parse error with its own context
  }
  const json::Object *root = v->getAsObject();
  const json::Object *vitis = root ? root->getObject("vitis") : nullptr;
  if (!vitis)
    return;
  auto warn = [&](StringRef what, const std::string &table,
                  const std::string &cfg) {
    diag.warnings.push_back("tool.hls.math_library.table: '" + path +
                            "' was measured with " + what.str() + " " + table +
                            ", the configuration has " + cfg);
  };
  if (std::optional<StringRef> ver = vitis->getString("version"))
    if (*ver != c.tool.version)
      warn("tool version", ver->str(), c.tool.version);
  if (std::optional<StringRef> part = vitis->getString("part"))
    if (*part != c.device.part)
      warn("part", part->str(), c.device.part);
  if (std::optional<double> clk = vitis->getNumber("clock_ns"))
    if (*clk != c.run.clockNs)
      warn("clock_ns", llvm::formatv("{0}", *clk).str(),
           llvm::formatv("{0}", c.run.clockNs).str());
  if (std::optional<StringRef> td =
          vitis->getString("syn.array_partition.throughput_driven"))
    if (*td != c.tool.hls.options.arrayPartition.throughputDriven)
      warn("throughput_driven", td->str(),
           c.tool.hls.options.arrayPartition.throughputDriven);
}

//===----------------------------------------------------------------------===//
// Provenance: overrides and hash.
//===----------------------------------------------------------------------===//

void diff(const json::Value *dflt, const json::Value &now,
          const std::string &path, const std::map<std::string, std::string> &src,
          std::vector<ConfigOverride> &out) {
  const json::Object *a = dflt ? dflt->getAsObject() : nullptr;
  const json::Object *b = now.getAsObject();
  if (a && b) {
    std::vector<std::string> keys;
    for (const auto &kv : *b)
      keys.push_back(kv.first.str());
    for (const auto &kv : *a)
      if (!b->get(kv.first))
        keys.push_back(kv.first.str());
    llvm::sort(keys);
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
    for (const std::string &k : keys) {
      std::string p = path.empty() ? k : path + "." + k;
      const json::Value *nv = b->get(k);
      if (!nv) {
        out.push_back({p, nullptr, "removed by run.device / run.tool"});
        continue;
      }
      diff(a->get(k), *nv, p, src, out);
    }
    return;
  }
  if (dflt && *dflt == now)
    return;
  // The origin: the longest recorded prefix of the path.
  std::string origin = "--config-set";
  for (std::string p = path;;) {
    auto it = src.find(p);
    if (it != src.end()) {
      origin = it->second;
      break;
    }
    size_t dot = p.rfind('.');
    if (dot == std::string::npos)
      break;
    p.resize(dot);
  }
  // A free-form value (plugins.<name>) set key by key: the assignment of one
  // of its keys.
  if (origin == "--config-set")
    for (const auto &[setPath, setOrigin] : src)
      if (StringRef(setPath).starts_with(path + ".")) {
        origin = setOrigin;
        break;
      }
  out.push_back({path, now, origin});
}

/// Doubles: the shortest decimal that reads back to the same value.
std::string formatDouble(double d) {
  if (d == std::floor(d) && std::fabs(d) < 1e15) {
    std::string s = std::to_string(static_cast<int64_t>(d));
    return s + ".0";
  }
  for (int prec = 1; prec <= 17; ++prec) {
    std::string s = llvm::formatv("{0}", llvm::format("%.*g", prec, d)).str();
    if (std::strtod(s.c_str(), nullptr) == d)
      return s;
  }
  return llvm::formatv("{0}", llvm::format("%.17g", d)).str();
}

void printValue(const json::Value &v, llvm::raw_ostream &os, unsigned indent);

bool isFlat(const json::Value &v) {
  if (v.getAsObject())
    return false;
  if (const json::Array *a = v.getAsArray())
    return llvm::all_of(*a, [](const json::Value &e) {
      if (const json::Array *inner = e.getAsArray())
        return llvm::all_of(*inner, [](const json::Value &x) {
          return !x.getAsObject() && !x.getAsArray();
        });
      return !e.getAsObject();
    });
  return true;
}

void printScalar(const json::Value &v, llvm::raw_ostream &os) {
  switch (v.kind()) {
  case json::Value::Null:
    os << "null";
    return;
  case json::Value::Boolean:
    os << (*v.getAsBoolean() ? "true" : "false");
    return;
  case json::Value::Number:
    if (std::optional<int64_t> i = v.getAsInteger())
      os << *i;
    else
      os << formatDouble(*v.getAsNumber());
    return;
  case json::Value::String: {
    // Let llvm::json escape the string.
    json::OStream j(os);
    j.value(v);
    return;
  }
  default:
    printValue(v, os, 0);
  }
}

void printValue(const json::Value &v, llvm::raw_ostream &os, unsigned indent) {
  std::string pad(indent, ' ');
  if (const json::Object *o = v.getAsObject()) {
    if (o->empty()) {
      os << "{}";
      return;
    }
    std::vector<StringRef> keys;
    for (const auto &kv : *o)
      keys.push_back(kv.first);
    llvm::sort(keys);
    os << "{\n";
    for (size_t i = 0; i < keys.size(); ++i) {
      os << pad << "  ";
      printScalar(json::Value(keys[i].str()), os);
      os << ": ";
      printValue(*o->get(keys[i]), os, indent + 2);
      os << (i + 1 < keys.size() ? ",\n" : "\n");
    }
    os << pad << "}";
    return;
  }
  if (const json::Array *a = v.getAsArray()) {
    if (a->empty()) {
      os << "[]";
      return;
    }
    if (isFlat(v)) {
      os << "[";
      for (size_t i = 0; i < a->size(); ++i) {
        if (i)
          os << ", ";
        printValue((*a)[i], os, indent);
      }
      os << "]";
      return;
    }
    os << "[\n";
    for (size_t i = 0; i < a->size(); ++i) {
      os << pad << "  ";
      printValue((*a)[i], os, indent + 2);
      os << (i + 1 < a->size() ? ",\n" : "\n");
    }
    os << pad << "]";
    return;
  }
  printScalar(v, os);
}

std::string sha256Hex(StringRef text) {
  llvm::SHA256 h;
  h.update(text);
  std::array<uint8_t, 32> digest = h.final();
  return llvm::toHex(digest, /*LowerCase=*/true);
}

/// Inserts `_doc` (section) and `_<key>` (key) descriptions from the schema.
void annotate(json::Value &v, const std::string &pattern) {
  json::Object *o = v.getAsObject();
  if (!o)
    return;
  if (!pattern.empty())
    if (const KeySpec *s = findKeySpec(pattern);
        s && (s->kind == KeyKind::FreeObject))
      return;
  std::vector<std::string> keys;
  for (const auto &kv : *o)
    keys.push_back(kv.first.str());
  for (const std::string &k : keys) {
    if (StringRef(k).starts_with("_"))
      continue;
    std::string p = pattern.empty() ? k : pattern + "." + k;
    const KeySpec *s = findKeySpec(p);
    if (!s)
      continue;
    std::string text = keyKindName(s->kind).str();
    if (*s->unit)
      text += ", " + std::string(s->unit);
    if (s->kind == KeyKind::Enum)
      text += " (" + std::string(s->values) + ")";
    if (s->kind == KeyKind::PluginName)
      text += " (a " + std::string(s->values) + ")";
    text += ": " + std::string(s->doc);
    if (*s->rows)
      text += " [" + std::string(s->rows) + "]";
    (*o)["_" + k] = text;
    json::Value &child = *o->get(k);
    if (s->kind == KeyKind::Section)
      annotate(child, p);
    else if (s->kind == KeyKind::ObjectList)
      if (json::Array *a = child.getAsArray())
        for (json::Value &e : *a)
          annotate(e, p + "[]");
  }
}

/// The compiled-in defaults, built once.
struct DefaultState {
  Config config;
  json::Value doc = nullptr;
};

const DefaultState &defaultState() {
  static const DefaultState state = [] {
    DefaultState s;
    ConfigDiagnostics diag;
    DocumentBuilder b(diag);
    if (!b.start())
      llvm::report_fatal_error(
          llvm::Twine("hls-est: the compiled-in configuration does not "
                      "load: ") +
          (diag.errors.empty() ? "?" : diag.errors.front()));
    Validator(diag).validate(b.doc);
    fill(b.doc, s.config);
    crossCheck(s.config, diag);
    if (!diag.ok())
      llvm::report_fatal_error(
          llvm::Twine("hls-est: the compiled-in configuration is invalid: ") +
          diag.errors.front());
    s.doc = b.doc;
    s.config.merged = b.doc;
    std::string canonical;
    llvm::raw_string_ostream os(canonical);
    printValue(b.doc, os, 0);
    s.config.hash = sha256Hex(os.str());
    return s;
  }();
  return state;
}

std::optional<Config> &installedConfig() {
  static std::optional<Config> c;
  return c;
}

/// The file or --config-set that set `path` (array indexes and the
/// "(id)" of a named element are ignored): `path` itself, else a leaf below
/// it, else the longest recorded prefix; "<defaults>" when the key comes from
/// the compiled-in files.
std::string originOf(StringRef path,
                     const std::map<std::string, std::string> &sources) {
  std::string p;
  for (size_t i = 0; i < path.size(); ++i) {
    char ch = path[i];
    if (ch == '[' || ch == '(') {
      char close = ch == '[' ? ']' : ')';
      while (i < path.size() && path[i] != close)
        ++i;
      continue;
    }
    p += ch;
  }
  // Sources are recorded per leaf: a key that is wrong as a whole (an unknown
  // section) was put there by the leaves below it.
  if (!sources.count(p)) {
    std::string below = p + ".";
    auto it = sources.lower_bound(below);
    if (it != sources.end() && StringRef(it->first).starts_with(below))
      return it->second;
  }
  for (;;) {
    auto it = sources.find(p);
    if (it != sources.end())
      return it->second;
    size_t dot = p.rfind('.');
    if (dot == std::string::npos)
      return "<defaults>";
    p.resize(dot);
  }
}

} // namespace

//===----------------------------------------------------------------------===//
// Public API.
//===----------------------------------------------------------------------===//

const Config &Config::defaults() { return defaultState().config; }

const Config &Config::get() {
  std::optional<Config> &c = installedConfig();
  return c ? *c : defaults();
}

void Config::install(Config config) { installedConfig() = std::move(config); }

Config circt::hlsest::buildConfig(llvm::ArrayRef<std::string> files,
                                  llvm::ArrayRef<std::string> sets,
                                  ConfigDiagnostics &diag) {
  Config c;
  DocumentBuilder b(diag);
  if (!b.start())
    return c;
  for (const std::string &f : files)
    if (std::optional<json::Value> v = readJsonFile(f, diag)) {
      if (!v->getAsObject()->get("version"))
        diag.errors.push_back(f + ": version: missing (required; this "
                                  "hls-est reads version 1)");
      b.apply(std::move(*v), f, f);
    }
  for (const std::string &s : sets)
    b.set(s);
  if (!diag.ok())
    return c;
  // Validation and cross-key errors name the key; prefix the file or the
  // --config-set that put it there.
  auto attribute = [&](size_t first) {
    for (size_t i = first; i < diag.errors.size(); ++i) {
      std::string &e = diag.errors[i];
      size_t colon = e.find(": ");
      if (colon == std::string::npos)
        continue;
      std::string origin = originOf(e.substr(0, colon), b.sources);
      e = origin + ": " + e;
    }
  };
  Validator(diag).validate(b.doc);
  attribute(0);
  if (!diag.ok())
    return c;
  fill(b.doc, c);
  crossCheck(c, diag);
  attribute(0);
  // Every plugin the configuration names reads its parameters and checks the
  // device (a builtin refuses a device it cannot price), also when a cross-key
  // check failed, so that a refusal names everything the device lacks.
  if (const PluginConfigCheck &check = getPluginConfigCheck()) {
    size_t first = diag.errors.size();
    check(c, diag);
    // A plugin's error that names a key some file or --config-set set gets
    // that origin too (a device refusal names no key and stays as it is).
    for (size_t i = first; i < diag.errors.size(); ++i) {
      std::string &e = diag.errors[i];
      size_t colon = e.find(": ");
      if (colon == std::string::npos)
        continue;
      std::string origin = originOf(e.substr(0, colon), b.sources);
      if (origin != "<defaults>")
        e = origin + ": " + e;
    }
  }
  if (!diag.ok())
    return c;
  checkMathTable(c, diag);
  c.files.assign(files.begin(), files.end());
  c.sets.assign(sets.begin(), sets.end());
  c.merged = b.doc;
  diff(&defaultState().doc, b.doc, "", b.sources, c.overrides);
  std::string canonical;
  llvm::raw_string_ostream os(canonical);
  printValue(b.doc, os, 0);
  c.hash = sha256Hex(os.str());
  return c;
}

std::string circt::hlsest::printSortedJson(const json::Value &v) {
  std::string s;
  llvm::raw_string_ostream os(s);
  printValue(v, os, 0);
  os << "\n";
  return s;
}

std::string circt::hlsest::dumpDefaultConfig() {
  json::Value doc = defaultState().doc;
  annotate(doc, "");
  json::Object &root = *doc.getAsObject();
  root["_doc"] = "hls-est configuration: the compiled-in defaults (device " +
                 Config::defaults().device.id + ", tool profile " +
                 Config::defaults().tool.id +
                 "). Keys starting with _ are documentation and are ignored "
                 "when this file is read back with --hls-config.";
  root["_generated_by"] = "hls-est --dump-default-config";
  return printSortedJson(doc);
}

std::string circt::hlsest::dumpEffectiveConfig(const Config &config) {
  json::Value doc = config.merged;
  // `_source` next to every changed key.
  for (const ConfigOverride &o : config.overrides) {
    StringRef path(o.path);
    auto [parent, key] = path.rsplit('.');
    if (key.empty()) {
      key = parent;
      parent = "";
    }
    json::Value *cur = &doc;
    if (!parent.empty()) {
      SmallVector<StringRef> parts;
      parent.split(parts, '.');
      for (StringRef p : parts) {
        json::Object *obj = cur->getAsObject();
        cur = obj ? obj->get(p) : nullptr;
        if (!cur)
          break;
      }
    }
    if (!cur || !cur->getAsObject())
      continue;
    json::Object &obj = *cur->getAsObject();
    if (!obj.getObject("_source"))
      obj["_source"] = json::Object{};
    (*obj.getObject("_source"))[key.str()] = o.source;
  }
  json::Object &root = *doc.getAsObject();
  root["_generated_by"] = "hls-est --dump-effective-config";
  root["_hash"] = config.hash;
  return printSortedJson(doc);
}

std::string circt::hlsest::dumpConfigSchema() {
  json::Array keys;
  const json::Value &dflt = defaultState().doc;
  for (const KeySpec &k : configSchema()) {
    json::Object o;
    o["path"] = k.path;
    o["type"] = keyKindName(k.kind);
    o["unit"] = k.unit;
    o["doc"] = k.doc;
    o["rows"] = k.rows;
    o["readers"] = k.readers;
    if (*k.values)
      o[k.kind == KeyKind::PluginName ? "interface" : "values"] = k.values;
    if (!std::isnan(k.min))
      o["min"] = k.min;
    if (!std::isnan(k.max))
      o["max"] = k.max;
    o["optional"] = k.optional;
    // The default: the value at the path in the compiled-in document (a key
    // of an array element has none of its own).
    if (!StringRef(k.path).contains("[]") && k.kind != KeyKind::Section) {
      SmallVector<StringRef> parts;
      StringRef(k.path).split(parts, '.');
      const json::Value *cur = &dflt;
      for (StringRef p : parts) {
        const json::Object *obj = cur ? cur->getAsObject() : nullptr;
        cur = obj ? obj->get(p) : nullptr;
      }
      if (cur)
        o["default"] = *cur;
    }
    keys.push_back(std::move(o));
  }
  // One key per line (in the schema's order), so that the output can be
  // grepped and diffed key by key.
  std::string s;
  llvm::raw_string_ostream os(s);
  os << "{\n  \"_generated_by\": \"hls-est --dump-config-schema\",\n";
  os << "  \"keys\": [\n";
  for (size_t i = 0; i < keys.size(); ++i) {
    os << "    ";
    json::OStream j(os);
    j.value(keys[i]);
    os << (i + 1 < keys.size() ? ",\n" : "\n");
  }
  os << "  ],\n  \"plugin_interfaces\": [";
  llvm::interleave(
      pluginInterfaceKeys(), os, [&](const char *k) { os << "\"" << k << "\""; },
      ", ");
  os << "],\n  \"version\": 1\n}\n";
  return s;
}

std::vector<std::string> circt::hlsest::compiledInDevices() {
  std::vector<std::string> out;
  for (const CompiledIn &d : kDevices)
    out.push_back(d.id);
  return out;
}

std::vector<std::string> circt::hlsest::compiledInProfiles() {
  std::vector<std::string> out;
  for (const CompiledIn &p : kProfiles)
    out.push_back(p.id);
  return out;
}
