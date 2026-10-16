

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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

/// Removes the documentation keys (`_...`) of every object, recursively.
/// A device file's `_status` (validated | unvalidated) and `_sources` stay:
/// they are part of what the description claims.
void stripDocKeys(json::Value &valueHandle) {
  if (json::Object *opHandle = valueHandle.getAsObject()) {
    std::vector<std::string> drop;
    for (auto &kv : *opHandle)
      if (StringRef(kv.first).starts_with("_") && kv.first != "_status" &&
          kv.first != "_sources")
        drop.push_back(kv.first.str());
    for (const std::string &keyValue : drop)
      opHandle->erase(keyValue);
    for (auto &kv : *opHandle)
      stripDocKeys(kv.second);
  } else if (json::Array *arrayValue = valueHandle.getAsArray()) {
    for (json::Value &entryValue : *arrayValue)
      stripDocKeys(entryValue);
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
  llvm::Expected<json::Value> valueHandle = json::parse(text);
  if (!valueHandle) {
    diag.errors.push_back(origin.str() + ": not valid JSON: " +
                          llvm::toString(valueHandle.takeError()));
    return std::nullopt;
  }
  if (!valueHandle->getAsObject()) {
    diag.errors.push_back(origin.str() + ": the top level is not an object");
    return std::nullopt;
  }
  stripDocKeys(*valueHandle);
  return std::move(*valueHandle);
}

std::optional<json::Value> readJsonFile(StringRef path,
                                        ConfigDiagnostics &diag) {
  auto buf = llvm::MemoryBuffer::getFile(path);
  if (!buf) {
    diag.errors.push_back(path.str() +
                          ": cannot read: " + buf.getError().message());
    return std::nullopt;
  }
  return parseJson((*buf)->getBuffer(), path, diag);
}

/// A path relative to the directory of `baseFile` (empty: the working
/// directory), made absolute; absolute paths are returned unchanged.
std::string resolveRelative(StringRef path, StringRef baseFile) {
  if (path.empty() || llvm::sys::path::is_absolute(path) || baseFile.empty())
    return path.str();
  llvm::SmallString<256> portValue(llvm::sys::path::parent_path(baseFile));
  llvm::sys::path::append(portValue, path);
  llvm::sys::path::remove_dots(portValue, true);
  return std::string(portValue);
}

bool looksLikePath(StringRef stringValue) {
  return stringValue.contains('/') || stringValue.ends_with(".json");
}

/// The device file `idOrPath` (a compiled-in id, or a path relative to the
/// file that names it), with its own relative paths resolved.
std::optional<json::Value> loadDevice(StringRef idOrPath, StringRef baseFile,
                                      StringRef origin,
                                      ConfigDiagnostics &diag) {
  for (const CompiledIn &dimensionIndex : kDevices)
    if (idOrPath == dimensionIndex.id)
      return parseJson(dimensionIndex.text,
                       std::string("<compiled-in ") + dimensionIndex.id + ">",
                       diag);
  if (!looksLikePath(idOrPath)) {
    std::string known;
    for (const CompiledIn &dimensionIndex : kDevices)
      known += (known.empty() ? "" : ", ") + std::string(dimensionIndex.id);
    diag.errors.push_back(origin.str() + ": run.device: '" + idOrPath.str() +
                          "' is neither a compiled-in device (" + known +
                          ") nor a .json path");
    return std::nullopt;
  }
  std::string path = resolveRelative(idOrPath, baseFile);
  std::optional<json::Value> valueHandle = readJsonFile(path, diag);
  if (!valueHandle)
    return std::nullopt;
  if (json::Value *typeValue =
          valueHandle->getAsObject()->get("operator_table"))
    if (std::optional<StringRef> stringValue = typeValue->getAsString())
      *typeValue = resolveRelative(*stringValue, path);
  return valueHandle;
}

/// The profile file `idOrPath`: an object with `tool` and `scheduling`.
std::optional<json::Value> loadProfile(StringRef idOrPath, StringRef baseFile,
                                       StringRef origin,
                                       ConfigDiagnostics &diag) {
  std::optional<json::Value> valueHandle;
  std::string path;
  for (const CompiledIn &portValue : kProfiles)
    if (idOrPath == portValue.id)
      valueHandle =
          parseJson(portValue.text,
                    std::string("<compiled-in ") + portValue.id + ">", diag);
  if (!valueHandle) {
    if (!looksLikePath(idOrPath)) {
      std::string known;
      for (const CompiledIn &portValue : kProfiles)
        known += (known.empty() ? "" : ", ") + std::string(portValue.id);
      diag.errors.push_back(origin.str() + ": run.tool: '" + idOrPath.str() +
                            "' is neither a compiled-in profile (" + known +
                            ") nor a .json path");
      return std::nullopt;
    }
    path = resolveRelative(idOrPath, baseFile);
    valueHandle = readJsonFile(path, diag);
    if (!valueHandle)
      return std::nullopt;
  }
  json::Object *opHandle = valueHandle->getAsObject();
  if (!opHandle->getObject("tool") || !opHandle->getObject("scheduling")) {
    diag.errors.push_back(origin.str() + ": run.tool: '" + idOrPath.str() +
                          "' has no \"tool\" and \"scheduling\" objects");
    return std::nullopt;
  }
  if (!path.empty())
    if (json::Object *hls = opHandle->getObject("tool")->getObject("hls"))
      if (json::Object *ml = hls->getObject("math_library"))
        if (json::Value *typeValue = ml->get("table"))
          if (std::optional<StringRef> stringValue = typeValue->getAsString())
            *typeValue = resolveRelative(*stringValue, path);
  return valueHandle;
}

/// Records which origin last set every leaf path of `overlay`.
void recordSources(const json::Value &overlay, const std::string &prefix,
                   const std::string &origin,
                   std::map<std::string, std::string> &sources) {
  if (const json::Object *opHandle = overlay.getAsObject()) {
    if (opHandle->empty() && !prefix.empty()) {
      sources[prefix] = origin;
      return;
    }
    for (const auto &kv : *opHandle)
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
    std::optional<json::Value> base =
        parseJson(kBaseJson, "<compiled-in base>", diag);
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
    json::Object *opHandle = overlay.getAsObject();
    if (json::Value *ver = opHandle->get("version")) {
      std::optional<int64_t> valueHandle = ver->getAsInteger();
      if (!valueHandle || *valueHandle != 1)
        diag.errors.push_back(origin.str() +
                              ": version: this hls-est reads version 1");
    }
    if (json::Object *run = opHandle->getObject("run")) {
      if (std::optional<StringRef> dev = run->getString("device")) {
        std::optional<json::Value> dimensionIndex =
            loadDevice(*dev, baseFile, origin, diag);
        if (dimensionIndex)
          (*doc.getAsObject())["device"] = std::move(*dimensionIndex);
        recordSources(json::Object{{"device", json::Object{}}}, "",
                      origin.str() + " (run.device)", sources);
        replaced.insert("device");
      }
      if (std::optional<StringRef> tool = run->getString("tool")) {
        std::optional<json::Value> portValue =
            loadProfile(*tool, baseFile, origin, diag);
        if (portValue)
          for (auto &kv : *portValue->getAsObject())
            (*doc.getAsObject())[kv.first] = kv.second;
        replaced.insert("tool");
        replaced.insert("scheduling");
      }
    }

    if (!baseFile.empty()) {
      if (json::Object *tool = opHandle->getObject("tool"))
        if (json::Object *hls = tool->getObject("hls"))
          if (json::Object *ml = hls->getObject("math_library"))
            if (json::Value *typeValue = ml->get("table"))
              if (std::optional<StringRef> stringValue =
                      typeValue->getAsString())
                *typeValue = resolveRelative(*stringValue, baseFile);
      if (json::Object *dev = opHandle->getObject("device"))
        if (json::Value *typeValue = dev->get("operator_table"))
          if (std::optional<StringRef> stringValue = typeValue->getAsString())
            *typeValue = resolveRelative(*stringValue, baseFile);
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
      value = text.str();
    }
    if (path == "run.device" || path == "run.tool") {
      json::Object run{{path.drop_front(4).str(), value}};
      apply(json::Object{{"run", std::move(run)}}, "", origin);
      return;
    }

    SmallVector<StringRef> parts;
    path.split(parts, '.');
    json::Value *cur = &doc;
    std::string done;
    for (size_t loopIndex = 0; loopIndex < parts.size(); ++loopIndex) {
      StringRef part = parts[loopIndex];
      std::optional<size_t> index;
      if (part.ends_with("]")) {
        size_t lb = part.find('[');
        size_t elementCount = 0;
        if (lb == StringRef::npos || part.slice(lb + 1, part.size() - 1)
                                         .getAsInteger(10, elementCount)) {
          diag.errors.push_back(origin + ": bad array index in '" + part.str() +
                                "'");
          return;
        }
        index = elementCount;
        part = part.take_front(lb);
      }
      done += (done.empty() ? "" : ".") + part.str();
      json::Object *opHandle = cur->getAsObject();
      if (!opHandle) {
        diag.errors.push_back(origin + ": " + done + " is not an object");
        return;
      }
      bool last = loopIndex + 1 == parts.size();
      if (last && !index) {
        (*opHandle)[part.str()] = value;
        sources[path.str()] = origin;
        return;
      }
      json::Value *next = opHandle->get(part);
      if (!next) {
        if (index) {
          diag.errors.push_back(origin + ": " + done + " is not an array");
          return;
        }
        (*opHandle)[part.str()] = json::Object{};
        next = opHandle->get(part);
      }
      if (index) {
        json::Array *arrayValue = next->getAsArray();
        if (!arrayValue || *index >= arrayValue->size()) {
          diag.errors.push_back(origin + ": " + done + "[" +
                                std::to_string(*index) + "] does not exist");
          return;
        }
        next = &(*arrayValue)[*index];
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

/// Levenshtein distance, for "did you mean".
unsigned editDistance(StringRef arrayValue, StringRef b) {
  return arrayValue.edit_distance(b, true);
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
    for (const KeySpec &keyValue : configSchema()) {
      StringRef portValue(keyValue.path);
      if (pattern.empty()) {
        if (!portValue.contains('.'))
          out.push_back(&keyValue);
        continue;
      }
      if (portValue.starts_with(pattern + ".") &&
          !portValue.drop_front(pattern.size() + 1).contains('.'))
        out.push_back(&keyValue);
    }
    return out;
  }

  void object(const json::Value &valueHandle, const std::string &pattern,
              const std::string &where) {
    const json::Object *opHandle = valueHandle.getAsObject();
    if (!opHandle) {
      error(where, "expected an object");
      return;
    }
    std::vector<const KeySpec *> kids = childrenOf(pattern);
    for (const auto &kv : *opHandle) {
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
        for (const KeySpec *keyValue : kids) {
          StringRef name = StringRef(keyValue->path).rsplit('.').second;
          if (name.empty())
            name = keyValue->path;
          unsigned dimensionIndex = editDistance(key, name);
          if (dimensionIndex < best) {
            best = dimensionIndex;
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
    for (const KeySpec *keyValue : kids) {
      StringRef name = StringRef(keyValue->path).rsplit('.').second;
      if (name.empty())
        name = keyValue->path;
      if (!keyValue->optional && !opHandle->get(name))
        error(pattern.empty() ? name.str() : where + "." + name.str(),
              "missing (required)");
    }
  }

  void number(const json::Value &valueHandle, const KeySpec &spec,
              const std::string &where) {
    std::optional<double> dimensionIndex = valueHandle.getAsNumber();
    if (!dimensionIndex)
      return;
    if (!std::isnan(spec.min) && *dimensionIndex < spec.min)
      error(where, "out of range: " + formatNumber(*dimensionIndex) +
                       " < minimum " + formatNumber(spec.min));
    if (!std::isnan(spec.max) && *dimensionIndex > spec.max)
      error(where, "out of range: " + formatNumber(*dimensionIndex) +
                       " > maximum " + formatNumber(spec.max));
  }

  static std::string formatNumber(double dimensionIndex) {
    if (dimensionIndex == std::floor(dimensionIndex) &&
        std::fabs(dimensionIndex) < 1e15)
      return std::to_string(static_cast<int64_t>(dimensionIndex));
    return std::to_string(dimensionIndex);
  }

  bool isInteger(const json::Value &valueHandle) {
    return valueHandle.getAsInteger().has_value();
  }

  /// A whole number beyond the 64-bit signed range (JSON reads it, but not as
  /// an integer): out of range rather than of the wrong type.
  bool tooLarge(const json::Value &valueHandle, const std::string &where) {
    std::optional<double> dimensionIndex = valueHandle.getAsNumber();
    if (isInteger(valueHandle) || !dimensionIndex ||
        *dimensionIndex != std::floor(*dimensionIndex))
      return false;
    char text[32];
    std::snprintf(text, sizeof(text), "%.17g", *dimensionIndex);
    error(where, "out of range: " + std::string(text) +
                     " exceeds the 64-bit integer range");
    return true;
  }

  void enumValue(StringRef stringValue, StringRef values,
                 const std::string &where) {
    SmallVector<StringRef> allowed;
    values.split(allowed, '|');
    if (!llvm::is_contained(allowed, stringValue))
      error(where, "'" + stringValue.str() + "' is not one of " +
                       llvm::join(allowed, ", "));
  }

  void value(const json::Value &valueHandle, const KeySpec &spec,
             const std::string &where) {
    auto typeError = [&](StringRef expected) {
      error(where, "wrong type: expected " + expected.str());
    };
    switch (spec.kind) {
    case KeyKind::Section:
      object(valueHandle, spec.path, where);
      return;
    case KeyKind::ObjectList: {
      const json::Array *arrayValue = valueHandle.getAsArray();
      if (!arrayValue)
        return typeError("an array of objects");
      for (size_t loopIndex = 0; loopIndex < arrayValue->size(); ++loopIndex)
        object((*arrayValue)[loopIndex], std::string(spec.path) + "[]",
               where + "[" + std::to_string(loopIndex) + "]");
      return;
    }
    case KeyKind::FreeObject:
      if (!valueHandle.getAsObject())
        typeError("an object");
      return;
    case KeyKind::FreeArray:
      if (!valueHandle.getAsArray())
        typeError("an array");
      return;
    case KeyKind::Bool:
      if (!valueHandle.getAsBoolean())
        typeError("true or false");
      return;
    case KeyKind::Int:
      if (tooLarge(valueHandle, where))
        return;
      if (!isInteger(valueHandle))
        return typeError("an integer");
      number(valueHandle, spec, where);
      return;
    case KeyKind::UInt:
      if (tooLarge(valueHandle, where))
        return;
      if (!isInteger(valueHandle) || *valueHandle.getAsInteger() < 0)
        return typeError("a non-negative integer");
      number(valueHandle, spec, where);
      return;
    case KeyKind::NullableUInt:
      if (valueHandle.kind() == json::Value::Null ||
          tooLarge(valueHandle, where))
        return;
      if (!isInteger(valueHandle) || *valueHandle.getAsInteger() < 0)
        return typeError("a non-negative integer or null");
      number(valueHandle, spec, where);
      return;
    case KeyKind::Number:
      if (!valueHandle.getAsNumber())
        return typeError("a number");
      number(valueHandle, spec, where);
      return;
    case KeyKind::String:
      if (!valueHandle.getAsString())
        typeError("a string");
      return;
    case KeyKind::NullablePath:
      if (valueHandle.kind() != json::Value::Null && !valueHandle.getAsString())
        typeError("a path string or null");
      return;
    case KeyKind::NullableObject:
      if (valueHandle.kind() != json::Value::Null && !valueHandle.getAsObject())
        typeError("an object or null");
      return;
    case KeyKind::Enum:
      if (std::optional<StringRef> stringValue = valueHandle.getAsString())
        enumValue(*stringValue, spec.values, where);
      else
        typeError("a string");
      return;
    case KeyKind::PluginName: {
      std::optional<StringRef> stringValue = valueHandle.getAsString();
      if (!stringValue)
        return typeError("a plugin name");
      const PluginNameCheck &check = getPluginNameCheck();
      std::string known;
      if (check && !check(spec.values, *stringValue, known))
        error(where, "no " + std::string(spec.values) + " plugin named '" +
                         stringValue->str() +
                         "' is registered (registered: " + known + ")");
      return;
    }
    case KeyKind::StringList: {
      const json::Array *arrayValue = valueHandle.getAsArray();
      if (!arrayValue)
        return typeError("an array of strings");
      for (size_t loopIndex = 0; loopIndex < arrayValue->size(); ++loopIndex) {
        std::optional<StringRef> stringValue =
            (*arrayValue)[loopIndex].getAsString();
        std::string widthValue = where + "[" + std::to_string(loopIndex) + "]";
        if (!stringValue)
          error(widthValue, "wrong type: expected a string");
        else if (*spec.values)
          enumValue(*stringValue, spec.values, widthValue);
      }
      return;
    }
    case KeyKind::PortSetList: {
      const json::Array *arrayValue = valueHandle.getAsArray();
      if (!arrayValue)
        return typeError("an array of port sets");
      for (size_t loopIndex = 0; loopIndex < arrayValue->size(); ++loopIndex) {
        std::string widthValue = where + "[" + std::to_string(loopIndex) + "]";
        const json::Array *set = (*arrayValue)[loopIndex].getAsArray();
        if (!set) {
          error(widthValue, "wrong type: expected an array of r / w / rw");
          continue;
        }
        for (size_t innerIndex = 0; innerIndex < set->size(); ++innerIndex) {
          std::optional<StringRef> stringValue =
              (*set)[innerIndex].getAsString();
          std::string wj = widthValue + "[" + std::to_string(innerIndex) + "]";
          if (!stringValue)
            error(wj, "wrong type: expected r, w or rw");
          else
            enumValue(*stringValue, "r|w|rw", wj);
        }
      }
      return;
    }
    case KeyKind::ResourceVector: {
      const json::Object *opHandle = valueHandle.getAsObject();
      if (!opHandle)
        return typeError("an object {class: count}");
      for (const auto &kv : *opHandle)
        if (!StringRef(kv.first).starts_with("_") &&
            !Rational::fromJson(kv.second))
          error(where + "." + kv.first.str(),
                "wrong type: expected a non-negative integer or \"n/d\"");
      return;
    }
    case KeyKind::IntMap: {
      const json::Object *opHandle = valueHandle.getAsObject();
      if (!opHandle)
        return typeError("an object {name: integer}");
      for (const auto &kv : *opHandle) {
        if (StringRef(kv.first).starts_with("_"))
          continue;
        std::string widthValue = where + "." + kv.first.str();
        if (tooLarge(kv.second, widthValue))
          continue;
        if (!isInteger(kv.second))
          error(widthValue, "wrong type: expected an integer");
        else
          number(kv.second, spec, widthValue);
      }
      return;
    }
    }
  }
};

const json::Object &obj(const json::Object &opHandle, StringRef key) {
  static const json::Object empty;
  const json::Object *portValue = opHandle.getObject(key);
  return portValue ? *portValue : empty;
}
std::string str(const json::Object &opHandle, StringRef key,
                StringRef dflt = StringRef()) {
  if (std::optional<StringRef> stringValue = opHandle.getString(key))
    return stringValue->str();
  return dflt.str();
}
int64_t integer(const json::Object &opHandle, StringRef key, int64_t dflt = 0) {
  if (std::optional<int64_t> loopIndex = opHandle.getInteger(key))
    return *loopIndex;
  return dflt;
}
std::optional<int64_t> optInteger(const json::Object &opHandle, StringRef key) {
  return opHandle.getInteger(key);
}
double number(const json::Object &opHandle, StringRef key, double dflt = 0) {
  if (std::optional<double> dimensionIndex = opHandle.getNumber(key))
    return *dimensionIndex;
  return dflt;
}
std::optional<double> optNumber(const json::Object &opHandle, StringRef key) {
  return opHandle.getNumber(key);
}
bool boolean(const json::Object &opHandle, StringRef key, bool dflt = false) {
  if (std::optional<bool> b = opHandle.getBoolean(key))
    return *b;
  return dflt;
}
std::vector<std::string> strings(const json::Object &opHandle, StringRef key) {
  std::vector<std::string> out;
  if (const json::Array *arrayValue = opHandle.getArray(key))
    for (const json::Value &valueHandle : *arrayValue)
      if (std::optional<StringRef> stringValue = valueHandle.getAsString())
        out.push_back(stringValue->str());
  return out;
}
ResourceVector resources(const json::Object &opHandle, StringRef key) {
  ResourceVector resultValue;
  if (const json::Object *rv = opHandle.getObject(key))
    for (const auto &kv : *rv)
      if (std::optional<Rational> elementCount = Rational::fromJson(kv.second))
        resultValue.add(kv.first, *elementCount);
  return resultValue;
}
template <class F>
void eachObject(const json::Object &opHandle, StringRef key, F fieldValue) {
  if (const json::Array *arrayValue = opHandle.getArray(key))
    for (const json::Value &valueHandle : *arrayValue)
      if (const json::Object *entryValue = valueHandle.getAsObject())
        fieldValue(*entryValue);
}

void fillDevice(const json::Object &dimensionIndex, Device &dev) {
  dev.id = str(dimensionIndex, "id");
  dev.part = str(dimensionIndex, "part");
  dev.speedGrade = str(dimensionIndex, "speed_grade");
  dev.status = str(dimensionIndex, "_status", "unvalidated");
  dev.toolIds = obj(dimensionIndex, "tool_ids");
  eachObject(dimensionIndex, "resource_classes", [&](const json::Object &c) {
    ResourceClass rc;
    rc.name = str(c, "name");
    rc.capacity = optInteger(c, "capacity");
    rc.reportLabel = str(c, "report_label");
    rc.equivalent = resources(c, "equivalent");
    dev.resourceClasses.push_back(std::move(rc));
  });
  eachObject(dimensionIndex, "memories", [&](const json::Object &memoryOp) {
    DeviceMemory mem;
    mem.id = str(memoryOp, "id");
    mem.tier = str(memoryOp, "tier");
    mem.cost = resources(memoryOp, "cost");
    mem.overhead = resources(memoryOp, "overhead");
    mem.bits = integer(memoryOp, "bits");
    eachObject(memoryOp, "geometries", [&](const json::Object &globalOp) {
      mem.geometries.push_back({integer(globalOp, "width"),
                                integer(globalOp, "depth"),
                                optInteger(globalOp, "byte")});
    });
    eachObject(memoryOp, "port_configs", [&](const json::Object &portValue) {
      PortConfig pc;
      pc.name = str(portValue, "name");
      pc.ports = strings(portValue, "ports");
      pc.maxWidth = integer(portValue, "max_width");
      pc.mixedWidth = boolean(portValue, "mixed_width");
      mem.portConfigs.push_back(std::move(pc));
    });
    mem.init = str(memoryOp, "init");
    eachObject(memoryOp, "read_latency_options",
               [&](const json::Object &resultValue) {
                 mem.readLatencyOptions.push_back(
                     {integer(resultValue, "cycles"),
                      optNumber(resultValue, "max_freq_mhz")});
               });
    mem.fmaxMhz = optNumber(memoryOp, "fmax_mhz");
    dev.memories.push_back(std::move(mem));
  });
  eachObject(
      dimensionIndex, "shift_registers", [&](const json::Object &stringValue) {
        dev.shiftRegisters.push_back(
            {str(stringValue, "id"), integer(stringValue, "max_depth"),
             integer(stringValue, "width"), resources(stringValue, "cost")});
      });
  eachObject(dimensionIndex, "arith", [&](const json::Object &arrayValue) {
    ArithBlock b;
    b.id = str(arrayValue, "id");
    b.cost = resources(arrayValue, "cost");
    b.overhead = resources(arrayValue, "overhead");
    eachObject(arrayValue, "mul", [&](const json::Object &memoryOp) {
      b.mul.push_back({integer(memoryOp, "a"), integer(memoryOp, "b"),
                       str(memoryOp, "signed"), integer(memoryOp, "count", 1)});
    });
    b.preAdd = optInteger(arrayValue, "pre_add");
    b.acc = optInteger(arrayValue, "acc");
    b.hardFp = strings(arrayValue, "hard_fp");
    b.fmaxMhz = optNumber(arrayValue, "fmax_mhz");
    dev.arith.push_back(std::move(b));
  });
  const json::Object &lowerIndex = obj(dimensionIndex, "logic");
  dev.logic.cell = str(lowerIndex, "cell");
  dev.logic.lutInputs = integer(lowerIndex, "lut_inputs");
  dev.logic.fracturable = lowerIndex.getBoolean("fracturable");
  dev.logic.regsPerCell = optInteger(lowerIndex, "regs_per_cell");
  dev.logic.cost = resources(lowerIndex, "cost");
  if (const json::Value *typeValue = dimensionIndex.get("timing"))
    if (typeValue->kind() != json::Value::Null)
      dev.timing = *typeValue;
  dev.operatorTable = str(dimensionIndex, "operator_table");
}

void fillTool(const json::Object &typeValue, ToolProfile &tool) {
  tool.id = str(typeValue, "id");
  tool.name = str(typeValue, "name");
  tool.version = str(typeValue, "version");
  tool.pipeline = str(typeValue, "pipeline");
  const json::Object &hls = obj(typeValue, "hls");
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
  MemoryArchitectureConfig &memoryOp = h.memoryArchitecture;
  memoryOp.plugin = str(ma, "plugin");
  memoryOp.untrackedMemoryPorts = integer(ma, "untracked_memory_ports");
  memoryOp.partitionedArgumentBankPorts =
      boolean(ma, "partitioned_argument_bank_ports", true);
  memoryOp.oneLoopReadWriteSdp = boolean(ma, "one_loop_read_write_sdp", true);
  memoryOp.iterationPrivateRegisters =
      boolean(ma, "iteration_private_registers", true);
  memoryOp.portOccupancyCycles = integer(ma, "port_occupancy_cycles");
  const json::Object &rep = obj(ma, "replication");
  memoryOp.replication.maxCopies = integer(rep, "max_copies");
  memoryOp.replication.maxStoresPerIteration =
      integer(rep, "max_stores_per_iteration");
  memoryOp.replication.sharedWritePortReadsWhenIdle =
      boolean(rep, "shared_write_port_reads_when_idle");
  memoryOp.replication.exclusiveArmStoresOnce =
      boolean(rep, "exclusive_arm_stores_once");
  memoryOp.replication.calleeStoresPerLoop =
      boolean(rep, "callee_stores_per_loop");
  memoryOp.replication.callerStoresPerLoop =
      boolean(rep, "caller_stores_per_loop", true);
  memoryOp.replication.portBoundSeveralArrays =
      boolean(rep, "port_bound_several_arrays", true);
  memoryOp.replication.portBoundWritableGlobals =
      boolean(rep, "port_bound_writable_globals", true);
  memoryOp.replication.rotatingReadsFullCopies =
      boolean(rep, "rotating_reads_full_copies", false);
  memoryOp.replication.userRam1wnrReplicable =
      boolean(rep, "user_ram_1wnr_replicable", false);
  memoryOp.replication.exclusiveSteeredReadsShareSlot =
      boolean(rep, "exclusive_steered_reads_share_slot", false);
  memoryOp.replication.selectOfLoadsReload =
      boolean(rep, "select_of_loads_reload", false);
  memoryOp.replication.sequentialStateReads =
      boolean(rep, "sequential_state_reads", false);
  memoryOp.replication.userPlainRamPinsKind =
      boolean(rep, "user_plain_ram_pins_kind", false);
  const json::Object &rom = obj(ma, "rom");
  memoryOp.rom.sdpMaxReads = integer(rom, "sdp_max_reads");
  memoryOp.rom.copies = str(rom, "copies");
  memoryOp.rom.sequentialStateReads =
      boolean(rom, "sequential_state_reads", true);
  memoryOp.rom.functionPipelineReads =
      boolean(rom, "function_pipeline_reads", true);
  memoryOp.rom.moduleCopies = boolean(rom, "module_copies", true);
  memoryOp.rom.moduleCopiesParentReads =
      boolean(rom, "module_copies_parent_reads", false);
  memoryOp.sequentialScopeModel = str(obj(ma, "sequential_scope"), "model");
  memoryOp.sequentialLoadsBeforeConsumer =
      boolean(obj(ma, "sequential_scope"), "loads_before_consumer", true);
  memoryOp.portSetRule = str(ma, "port_set_rule");
  if (const json::Array *sets = ma.getArray("wide_port_sets"))
    for (const json::Value &stringValue : *sets) {
      std::vector<std::string> set;
      if (const json::Array *arrayValue = stringValue.getAsArray())
        for (const json::Value &portValue : *arrayValue)
          if (std::optional<StringRef> ps = portValue.getAsString())
            set.push_back(ps->str());
      memoryOp.widePortSets.push_back(std::move(set));
    }
  const json::Object &pc = obj(ma, "priced_configs");
  memoryOp.pricedWide = str(pc, "wide");
  memoryOp.pricedNarrow = str(pc, "narrow");

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
    const json::Object &dimensionIndex = obj(b, "defaults");
    ib.defaults.maxReadBurstLength =
        integer(dimensionIndex, "max_read_burst_length", 16);
    ib.defaults.numReadOutstanding =
        integer(dimensionIndex, "num_read_outstanding", 16);
    ib.defaults.maxWriteBurstLength =
        integer(dimensionIndex, "max_write_burst_length", 16);
    ib.defaults.numWriteOutstanding =
        integer(dimensionIndex, "num_write_outstanding", 16);
    const json::Object &rf = obj(b, "read_fifo");
    ib.readFifoSrlMaxDepth = integer(rf, "srl_max_depth", 32);
    ib.readFifoMapper = str(rf, "mapper", "vitis-band7");
    ib.readFifoPricedConfig = str(rf, "priced_config", "tdp");
    ib.readFifoConfirmedMaxDepth = integer(rf, "confirmed_max_depth", 4096);
    ib.readFifoPerChannel = boolean(rf, "per_channel", true);
    ib.readFifoCastLoadWidth = boolean(rf, "cast_load_width", true);
    ib.readFifoPowerOfTwoWidth = boolean(rf, "power_of_two_width", true);
    ib.readFifoStrobedPartWrites = boolean(rf, "strobed_part_writes", true);
    ib.readCacheBram = integer(rf, "cache_bram", 0);
    const json::Object &wb = obj(b, "write_buffer");
    ib.writeBufferFreeMaxBurst = integer(wb, "free_max_burst", 16);
    ib.writeBufferPortWidthBits = integer(wb, "port_width_bits", 18);
    ib.writeBufferConfirmedMinBurst = integer(wb, "confirmed_min_burst", 32);
    ib.writeBufferMinBramBits = integer(wb, "min_bram_bits", 1024);
    ib.writeBufferElementWidth = boolean(wb, "element_width", true);
    ib.unresolvedCall = str(b, "unresolved_call", "rw");
    const json::Object &br = obj(b, "bus_requests");
    ib.readRequestsPerCycle = integer(br, "read_per_cycle", 1);
    ib.writeRequestsPerCycle = integer(br, "write_per_cycle", 1);
    ib.busRequestsThroughCalls = boolean(br, "through_calls", true);
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
  h.streams.declaredElementBits = boolean(st, "declared_element_bits", true);
  h.streams.staticStructStorageBits =
      boolean(st, "static_struct_storage_bits", true);
  h.streams.streamPragmaArrays = boolean(st, "stream_pragma_arrays", true);
  h.streams.elementDepthPragmas = boolean(st, "element_depth_pragmas", false);
  const json::Object &dc = obj(hls, "dataflow_channels");
  h.dataflowChannels.enabled = boolean(dc, "enabled");
  h.dataflowChannels.defaultBlocks = integer(dc, "default_blocks");
  h.dataflowChannels.throughNestedRegions =
      boolean(dc, "through_nested_regions", true);
  h.dataflowChannels.promotedInvariantAccesses =
      boolean(dc, "promoted_invariant_accesses", true);

  const json::Object &pd = obj(hls, "pipeline_decision");
  h.pipelineDecision.policy = str(pd, "policy");
  h.pipelineDecision.floatLoadsPerfect = boolean(pd, "float_loads_perfect");
  h.pipelineDecision.promotePipelined = boolean(pd, "promote_pipelined");
  h.pipelineDecision.flattenAcrossCalls = boolean(pd, "flatten_across_calls");
  h.pipelineDecision.sinkParentCode = boolean(pd, "sink_parent_code", true);
  h.pipelineDecision.sinkParentTrailingCode =
      boolean(pd, "sink_parent_trailing_code", true);
  h.pipelineDecision.sinkParentTrailingStores =
      boolean(pd, "sink_parent_trailing_stores", false);
  h.pipelineDecision.foldUnrolledGuards =
      boolean(pd, "fold_unrolled_guards", true);
  h.pipelineDecision.foldUnrolledZeroProducts =
      boolean(pd, "fold_unrolled_zero_products", false);
  h.pipelineDecision.foldNestedConstantGuards =
      boolean(pd, "fold_nested_constant_guards", true);
  h.pipelineDecision.foldDomainTrueGuards =
      boolean(pd, "fold_domain_true_guards", false);
  h.pipelineDecision.hoistCommonArmLoads =
      boolean(pd, "hoist_common_arm_loads", false);
  h.pipelineDecision.promoteNestInvariantOnly =
      boolean(pd, "promote_nest_invariant_only", false);
  h.pipelineDecision.promotedStoreCleanup =
      boolean(pd, "promoted_store_cleanup", false);
  h.pipelineDecision.promoteConditionalAccesses =
      boolean(pd, "promote_conditional_accesses", false);
  h.pipelineDecision.flattenNestInvariantBounds =
      boolean(pd, "flatten_nest_invariant_bounds", false);
  h.pipelineDecision.pipelineOffSequential =
      boolean(pd, "pipeline_off_sequential", true);
  h.pipelineDecision.doWhileFlattenRefusal =
      boolean(pd, "do_while_flatten_refusal", true);
  h.pipelineDecision.libraryCallsWithLoops =
      strings(pd, "library_calls_with_loops");
  h.pipelineDecision.pipelinedLibraryCalls =
      strings(pd, "pipelined_library_calls");
  h.pipelineDecision.doWhileMinSubLoopTrip =
      integer(pd, "do_while_min_subloop_trip", 3);
  h.pipelineDecision.partialUnrollRuntimeLoops =
      boolean(pd, "partial_unroll_runtime_loops", true);
  h.pipelineDecision.callOccupancyAfterPartition =
      boolean(pd, "call_occupancy_after_partition", true);

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
  h.partitioning.constantIndexThroughCalls =
      boolean(obj(pa, "constant_index"), "through_calls", true);
  h.partitioning.constantIndexFoldDivision =
      boolean(obj(pa, "constant_index"), "fold_division", true);
  h.partitioning.constantIndexFoldConditionals =
      boolean(obj(pa, "constant_index"), "fold_conditionals", true);
  h.partitioning.constantIndexThroughViews =
      boolean(obj(pa, "constant_index"), "through_views", true);
  h.partitioning.constantIndexBlockOffset =
      boolean(obj(pa, "constant_index"), "block_offset", true);
  h.partitioning.compoundAssignTwoStores =
      boolean(pa, "compound_assign_two_stores", true);
  h.partitioning.blockBankFromLoopRange =
      boolean(pa, "block_bank_from_loop_range", true);
  h.partitioning.reachableStoreBanks =
      boolean(pa, "reachable_store_banks", true);
  h.partitioning.completePartitionRegisters =
      boolean(pa, "complete_partition_registers", true);
  h.partitioning.knownResidueBanks = boolean(pa, "known_residue_banks", true);
  h.partitioning.banksFromValueRange =
      boolean(pa, "banks_from_value_range", false);
  h.partitioning.reshapedCalleeParameters =
      boolean(pa, "reshaped_callee_parameters", false);
  h.partitioning.sharedAddressBankReads =
      boolean(pa, "shared_address_bank_reads", false);
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
  h.partitioning.steerWindowGroups = boolean(pa, "steer_window_groups", true);
  h.partitioning.steerThroughGuards = boolean(pa, "steer_through_guards", true);
  h.partitioning.dropUnreadBanks = boolean(pa, "drop_unread_banks", true);
  h.partitioning.inductionResidueBanks =
      boolean(pa, "induction_residue_banks", true);

  const json::Object &fo = obj(hls, "folding");
  h.folding.ruleSet = str(fo, "rule_set");
  h.folding.canonicalize = boolean(fo, "canonicalize");
  h.folding.storageAddressNotNull =
      boolean(fo, "storage_address_not_null", true);
  h.folding.dropAsserts = boolean(fo, "drop_asserts", false);
  h.folding.evaluateConstantCalls =
      boolean(fo, "evaluate_constant_calls", true);
  h.folding.constantCallMaxSteps =
      integer(fo, "constant_call_max_steps", 1000000);
  h.folding.maxRounds = integer(fo, "max_rounds");
  h.folding.constantGlobalLoadsAfterUnroll =
      boolean(fo, "constant_global_loads_after_unroll", false);
  h.folding.evaluateConstantFills =
      boolean(fo, "evaluate_constant_fills", false);
  h.folding.constantFillMaxElements =
      integer(fo, "constant_fill_max_elements", 4096);

  const json::Object &me = obj(hls, "middle_end");
  MiddleEndConfig &mid = h.middleEnd;
  mid.licmHoistInvariantLoads = boolean(me, "licm_hoist_invariant_loads");
  mid.licmHoistPastCalls = boolean(me, "licm_hoist_past_calls");
  mid.licmHoistConditional = boolean(me, "licm_hoist_conditional");
  mid.licmHoistWhileConditions =
      boolean(me, "licm_hoist_while_conditions", true);
  mid.mergeIfElseAccesses = boolean(me, "merge_if_else_accesses");
  mid.gvnLoads = boolean(me, "gvn_loads");
  mid.gvnMemrefLoads = boolean(me, "gvn_memref_loads", true);
  mid.forwardBeforeBanking = boolean(me, "forward_before_banking", false);
  mid.gvnConditionalLoads = boolean(me, "gvn_conditional_loads", true);
  mid.trackGlobals = boolean(me, "globals", true);
  mid.dseGuardedStores = boolean(me, "dse_guarded_stores", true);
  mid.forwardToGuardedLoads = boolean(me, "forward_to_guarded_loads", true);
  mid.storeForwarding = boolean(me, "store_forwarding");
  const json::Object &dm = obj(me, "dead_memory");
  mid.deadMemory.overwrittenStores = boolean(dm, "overwritten_stores");
  mid.deadMemory.deadCalls = boolean(dm, "dead_calls");
  mid.deadMemory.honourPreserve = boolean(dm, "honour_preserve");
  mid.deadMemory.globalSharedByFunctionsEscapes =
      boolean(dm, "global_shared_by_functions_escapes");
  mid.deadMemory.keepLoadStoreCycles = boolean(dm, "load_store_cycles", true);
  mid.deadMemory.overwrittenCallOutputs =
      boolean(dm, "overwritten_call_outputs", true);
  mid.deadMemory.overwrittenByLoops = boolean(dm, "overwritten_by_loops", true);
  mid.deadMemory.unreadRegisterElements =
      boolean(dm, "unread_register_elements", true);

  h.honourInlineOff = boolean(obj(hls, "inlining"), "honour_inline_off");
  h.clonePerArgumentType =
      boolean(obj(hls, "inlining"), "clone_per_argument_type", false);
  const json::Object &sc = obj(hls, "structs");
  h.structs.aggregate = boolean(sc, "aggregate");
  h.structs.globals = boolean(sc, "globals");
  h.structs.scalarRegisters = boolean(sc, "scalar_registers");
  h.structs.throughCalls = boolean(sc, "through_calls");
  h.structs.elementCopyLoops = boolean(sc, "element_copy_loops", true);
  h.structs.temporaryRegisters = boolean(sc, "temporary_registers", true);
  h.structs.memberPartitions = boolean(sc, "member_partitions", true);
  h.structs.specializeSplitCasts = boolean(sc, "specialize_split_casts", true);
  h.structs.topPointerScalar = boolean(sc, "top_pointer_scalar", true);
  const json::Object &na = obj(hls, "narrowing");
  h.narrowing.storedRanges = boolean(na, "stored_ranges");
  h.narrowing.constantSetReinterpretation =
      boolean(na, "constant_set_reinterpretation", true);
  h.narrowing.undefContributesNothing =
      boolean(na, "undef_contributes_nothing", true);
  h.narrowing.reachingStoreRanges = boolean(na, "reaching_store_ranges", true);
  h.narrowing.accumulationRanges = boolean(na, "accumulation_ranges", true);
  h.narrowing.calleeParamStoresFullRange =
      boolean(na, "callee_param_stores_full_range", true);
  h.narrowing.copiesCloseRanges = boolean(na, "copies_close_ranges", false);
  h.narrowing.loadDemand = boolean(na, "load_demand");
  h.narrowing.fullAddressInterfaceModes =
      strings(na, "full_address_interface_modes");
  h.narrowing.completeReadSelector =
      boolean(na, "complete_read_selector", true);
  h.globalsAttributeAccesses =
      boolean(obj(hls, "globals"), "attribute_accesses");
  h.groupingPlugin = str(obj(hls, "grouping"), "plugin");
  h.mathLibraryTable = str(obj(hls, "math_library"), "table");
  h.localStructTablesAtRunTime = boolean(
      obj(hls, "math_library"), "local_struct_tables_at_run_time", true);
  h.fixedExpTablesWhenUnlisted =
      boolean(obj(hls, "math_library"), "fixed_exp_tables_when_unlisted", true);
  h.inlinedTablesInPipelines =
      boolean(obj(hls, "math_library"), "inlined_tables_in_pipelines", true);
  h.sharedLibraryModules =
      boolean(obj(hls, "math_library"), "shared_library_modules", false);
  h.sequentialCoreSharing =
      boolean(obj(hls, "math_library"), "sequential_core_sharing", false);
  h.axiLiteArrayMemories =
      boolean(obj(hls, "interfaces"), "axi_lite_array_memories", false);

  const json::Object &be = obj(typeValue, "backend");
  tool.backend.id = str(be, "id");
  const json::Object &ss = obj(be, "storage_selector");
  StorageSelectorConfig &sel = tool.backend.storageSelector;
  sel.plugin = str(ss, "plugin");
  sel.minBlockBits = integer(ss, "min_block_bits");
  sel.inclusive = boolean(ss, "inclusive");
  sel.block = str(ss, "block");
  sel.below = str(ss, "below");
  sel.forcingImpl = str(ss, "forcing_impl", "bram");
  sel.distributedImpl = str(ss, "distributed_impl", "");
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
  const json::Object &rp = obj(typeValue, "report");
  tool.report.primaryMemoryClass = str(rp, "primary_memory_class");
  tool.report.stdoutFormat = str(rp, "stdout_format");
  tool.report.referenceStage = str(rp, "reference_stage");
  tool.report.classes = strings(rp, "classes");
}

void fillScheduling(const json::Object &stringValue, SchedulingConfig &sc) {
  const json::Object &typeValue = obj(stringValue, "timing");
  sc.timingModel = str(typeValue, "model");
  for (const auto &kv : obj(typeValue, "operator_latencies"))
    if (std::optional<int64_t> loopIndex = kv.second.getAsInteger())
      sc.operatorLatencies[kv.first.str()] = *loopIndex;
  const json::Object &de = obj(stringValue, "dependences");
  sc.dependenceModel = str(de, "model");
  sc.memoryRecurrences = boolean(de, "memory_recurrences", true);
  sc.unknownAddressMinII = integer(de, "unknown_address_min_ii", 2);
  sc.userInterIndependence = boolean(de, "user_inter_independence", true);
  sc.enclosingIvSampleSteps = integer(de, "enclosing_iv_sample_steps", 0);
  sc.bankStoreRecurrences = boolean(de, "bank_store_recurrences", false);
  sc.registerRecurrenceLatencies =
      boolean(de, "register_recurrence_latencies", false);
  sc.promotedElementRegisterCycle =
      boolean(de, "promoted_element_register_cycle", true);
  sc.f64RegisterCycle = boolean(de, "f64_register_cycle", true);
  sc.laneRmwOnePort = boolean(de, "lane_rmw_one_port", true);
  sc.promotedElementSearchBudget =
      integer(de, "promoted_element_search_budget", 1000000);
  sc.dynamicLaneRmw = boolean(de, "dynamic_lane_rmw", true);
  for (const auto &kv : obj(de, "recurrence_latencies"))
    if (std::optional<int64_t> loopIndex = kv.second.getAsInteger())
      sc.recurrenceLatencies[kv.first.str()] = *loopIndex;
  const json::Object &mo = obj(stringValue, "modulo");
  sc.moduloModel = str(mo, "model");
  sc.fastThreshold = integer(mo, "fast_threshold");
  sc.fastOpsThreshold = integer(mo, "fast_ops_threshold");
  sc.maxPipelineBodyOps = integer(mo, "max_pipeline_body_ops", 250000);
  sc.maxIIBumps = integer(mo, "max_ii_bumps");
  sc.lowerIIOfBoth = boolean(mo, "lower_ii_of_both", true);
  sc.calleeGlobalRecurrence = boolean(mo, "callee_global_recurrence", true);
  sc.recurrenceRepairRounds = integer(mo, "recurrence_repair_rounds");
  sc.heightPriority = boolean(mo, "height_priority");
  sc.fpUnitLimits = boolean(mo, "fp_unit_limits", false);
  sc.userIITarget = boolean(mo, "user_ii_target");
  sc.sequentialModel = str(obj(stringValue, "sequential"), "model");
  sc.bindingModel = str(obj(stringValue, "binding"), "model");
  sc.emitDetail = boolean(stringValue, "emit_detail");
  const json::Object &cd = obj(stringValue, "call_depth");
  CallDepthConfig &c = sc.callDepth;
  c.loadDataNs = number(cd, "load_data_ns");
  c.logicNs = number(cd, "logic_ns");
  c.selectNs = number(cd, "select_ns");
  c.variableShiftNs = number(cd, "variable_shift_ns");
  c.constantMultiplierNs = number(cd, "constant_multiplier_ns");
  c.narrowMultiplyMaxBits = integer(cd, "narrow_multiply_max_bits");
  c.narrowMultiplyCycles = integer(cd, "narrow_multiply_cycles");
  c.portsPerMemory = integer(cd, "ports_per_memory");
  c.staggeredCallsShareInstance =
      boolean(cd, "staggered_calls_share_instance", true);
  c.inOrderCallStarts = boolean(cd, "in_order_call_starts", true);
  c.outlinedPipelineArrayInstances =
      boolean(cd, "outlined_pipeline_array_instances", true);
  c.sequentialLoopsShareInstance =
      boolean(cd, "sequential_loops_share_instance", true);
  c.outlinedLoopsOwnAllocation =
      boolean(cd, "outlined_loops_own_allocation", true);
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

void crossCheck(const Config &c, ConfigDiagnostics &diag) {
  auto err = [&](const std::string &where, const std::string &msg) {
    diag.errors.push_back(where + ": " + msg);
  };
  const Device &dimensionIndex = c.device;
  llvm::StringSet<> classes;
  for (const ResourceClass &rc : dimensionIndex.resourceClasses)
    if (!classes.insert(rc.name).second)
      err("device.resource_classes", "class '" + rc.name + "' declared twice");
  auto checkVector = [&](const ResourceVector &valueHandle,
                         const std::string &where) {
    for (const auto &[name, elementCount] : valueHandle.items())
      if (!classes.contains(name))
        err(where, "names the undeclared resource class '" + name + "'");
  };
  for (const ResourceClass &rc : dimensionIndex.resourceClasses)
    checkVector(rc.equivalent,
                "device.resource_classes(" + rc.name + ").equivalent");
  llvm::StringSet<> memIds;
  for (const DeviceMemory &memoryOp : dimensionIndex.memories) {
    std::string where = "device.memories(" + memoryOp.id + ")";
    if (!memIds.insert(memoryOp.id).second)
      err("device.memories", "memory id '" + memoryOp.id + "' declared twice");
    checkVector(memoryOp.cost, where + ".cost");
    checkVector(memoryOp.overhead, where + ".overhead");
    std::set<std::pair<int64_t, int64_t>> shapes;
    for (const Geometry &globalOp : memoryOp.geometries) {
      if (!shapes.insert({globalOp.width, globalOp.depth}).second)
        err(where + ".geometries",
            "the shape " + std::to_string(globalOp.depth) + "x" +
                std::to_string(globalOp.width) + " is listed twice");
      if (globalOp.width * globalOp.depth > memoryOp.bits)
        err(where + ".geometries",
            std::to_string(globalOp.depth) + "x" +
                std::to_string(globalOp.width) + " holds more than the " +
                std::to_string(memoryOp.bits) + " bits of one instance");
    }
    for (const PortConfig &portValue : memoryOp.portConfigs)
      if (llvm::none_of(memoryOp.geometries, [&](const Geometry &globalOp) {
            return globalOp.width == portValue.maxWidth;
          }))
        err(where + ".port_configs(" + portValue.name + ").max_width",
            std::to_string(portValue.maxWidth) +
                " is the width of no geometry");
  }
  for (const ShiftRegister &stringValue : dimensionIndex.shiftRegisters)
    checkVector(stringValue.cost,
                "device.shift_registers(" + stringValue.id + ").cost");
  for (const ArithBlock &arrayValue : dimensionIndex.arith) {
    checkVector(arrayValue.cost, "device.arith(" + arrayValue.id + ").cost");
    checkVector(arrayValue.overhead,
                "device.arith(" + arrayValue.id + ").overhead");
  }

  const ToolProfile &typeValue = c.tool;
  const TimingMargin &tm = typeValue.hls.timingMargin;
  if (tm.fraction && tm.ns)
    err("tool.hls.timing_margin", "give fraction or ns, not both");
  const MemoryMapperConfig &mm = typeValue.backend.memoryMapper;

  int64_t prev = 0;
  unsigned beyond = 0;
  for (size_t loopIndex = 0; loopIndex < mm.depthBands.size(); ++loopIndex) {
    const DepthBand &b = mm.depthBands[loopIndex];
    std::string where = "tool.backend.memory_mapper.depth_bands[" +
                        std::to_string(loopIndex) + "]";
    if (b.beyond) {
      ++beyond;
      if (loopIndex + 1 != mm.depthBands.size())
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

  auto checkPortConfig = [&](const std::string &where,
                             const std::string &name) {
    llvm::StringSet<> known;
    for (const DeviceMemory &memoryOp : dimensionIndex.memories)
      for (const PortConfig &portValue : memoryOp.portConfigs) {
        if (portValue.name == name)
          return;
        known.insert(portValue.name);
      }
    std::vector<std::string> names;
    for (const auto &keyValue : known)
      names.push_back(keyValue.getKey().str());
    llvm::sort(names);
    err(where, "'" + name +
                   "' is the port configuration of no device "
                   "memory (device: " +
                   llvm::join(names, ", ") + ")");
  };
  const MemoryArchitectureConfig &ma = typeValue.hls.memoryArchitecture;
  checkPortConfig("tool.hls.memory_architecture.priced_configs.wide",
                  ma.pricedWide);
  checkPortConfig("tool.hls.memory_architecture.priced_configs.narrow",
                  ma.pricedNarrow);
  if (typeValue.hls.streams.enabled)
    checkPortConfig("tool.hls.streams.priced_config",
                    typeValue.hls.streams.pricedConfig);
  for (size_t loopIndex = 0; loopIndex < typeValue.hls.implicitBuffers.size();
       ++loopIndex)
    if (typeValue.hls.implicitBuffers[loopIndex].enabled)
      checkPortConfig(
          "tool.hls.implicit_buffers[" + std::to_string(loopIndex) +
              "].read_fifo.priced_config",
          typeValue.hls.implicitBuffers[loopIndex].readFifoPricedConfig);

  if (typeValue.hls.pipelineDecision.flattenAcrossCalls)
    err("tool.hls.pipeline_decision.flatten_across_calls",
        "true is not implemented (reserved; only false, D-11)");

  llvm::StringSet<> selected;
  for (const std::string *elementCount :
       {&typeValue.backend.storageSelector.plugin, &ma.plugin,
        &typeValue.backend.memoryMapper.plugin, &typeValue.hls.streams.mapper,
        &typeValue.hls.groupingPlugin, &typeValue.hls.pipelineDecision.policy,
        &typeValue.hls.partitioning.policy, &typeValue.hls.folding.ruleSet,
        &c.scheduling.timingModel, &c.scheduling.dependenceModel,
        &c.scheduling.moduloModel, &c.scheduling.sequentialModel,
        &c.scheduling.bindingModel})
    selected.insert(*elementCount);
  for (const ImplicitBufferConfig &b : typeValue.hls.implicitBuffers) {
    selected.insert(b.plugin);
    selected.insert(b.readFifoMapper);
  }
  for (const auto &kv : c.plugins) {
    StringRef name = kv.first;
    if (name.starts_with("_") || selected.contains(name))
      continue;
    err("plugins." + name.str(), "no plugin key selects a plugin named '" +
                                     name.str() +
                                     "', so nothing reads this section");
  }

  if (!classes.contains(typeValue.report.primaryMemoryClass))
    err("tool.report.primary_memory_class",
        "'" + typeValue.report.primaryMemoryClass +
            "' is not a resource class of the device");
  for (const std::string &cls : typeValue.report.classes)
    if (!classes.contains(cls))
      err("tool.report.classes",
          "'" + cls + "' is not a resource class of the device");

  for (const auto &[cls, lat] : c.scheduling.operatorLatencies)
    if (lat < 0 && lat != -1)
      err("scheduling.timing.operator_latencies." + cls,
          "out of range: " + std::to_string(lat) + " < minimum -1");
    else if (lat == -1 && cls != "call" && cls != "kept_call" &&
             cls != "libm_call")
      err("scheduling.timing.operator_latencies." + cls,
          "-1 (stay sequential) is allowed only for call, kept_call and "
          "libm_call");
}

/// The math-core table's own `vitis` block names the configuration its
/// costs were measured in; a mismatch is a warning (memo section 4.2).
void checkMathTable(const Config &c, ConfigDiagnostics &diag) {
  const std::string &path = c.tool.hls.mathLibraryTable;
  if (path.empty())
    return;
  auto buf = llvm::MemoryBuffer::getFile(path);
  if (!buf) {
    diag.errors.push_back("tool.hls.math_library.table: cannot read '" + path +
                          "': " + buf.getError().message());
    return;
  }
  llvm::Expected<json::Value> valueHandle = json::parse((*buf)->getBuffer());
  if (!valueHandle) {
    llvm::consumeError(valueHandle.takeError());
    return;
  }
  const json::Object *root = valueHandle->getAsObject();
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

void diff(const json::Value *dflt, const json::Value &now,
          const std::string &path,
          const std::map<std::string, std::string> &src,
          std::vector<ConfigOverride> &out) {
  const json::Object *arrayValue = dflt ? dflt->getAsObject() : nullptr;
  const json::Object *b = now.getAsObject();
  if (arrayValue && b) {
    std::vector<std::string> keys;
    for (const auto &kv : *b)
      keys.push_back(kv.first.str());
    for (const auto &kv : *arrayValue)
      if (!b->get(kv.first))
        keys.push_back(kv.first.str());
    llvm::sort(keys);
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
    for (const std::string &keyValue : keys) {
      std::string portValue = path.empty() ? keyValue : path + "." + keyValue;
      const json::Value *nv = b->get(keyValue);
      if (!nv) {
        out.push_back({portValue, nullptr, "removed by run.device / run.tool"});
        continue;
      }
      diff(arrayValue->get(keyValue), *nv, portValue, src, out);
    }
    return;
  }
  if (dflt && *dflt == now)
    return;

  std::string origin = "--config-set";
  for (std::string portValue = path;;) {
    auto it = src.find(portValue);
    if (it != src.end()) {
      origin = it->second;
      break;
    }
    size_t dot = portValue.rfind('.');
    if (dot == std::string::npos)
      break;
    portValue.resize(dot);
  }

  if (origin == "--config-set")
    for (const auto &[setPath, setOrigin] : src)
      if (StringRef(setPath).starts_with(path + ".")) {
        origin = setOrigin;
        break;
      }
  out.push_back({path, now, origin});
}

/// Doubles: the shortest decimal that reads back to the same value.
std::string formatDouble(double dimensionIndex) {
  if (dimensionIndex == std::floor(dimensionIndex) &&
      std::fabs(dimensionIndex) < 1e15) {
    std::string stringValue =
        std::to_string(static_cast<int64_t>(dimensionIndex));
    return stringValue + ".0";
  }
  for (int prec = 1; prec <= 17; ++prec) {
    std::string stringValue =
        llvm::formatv("{0}", llvm::format("%.*g", prec, dimensionIndex)).str();
    if (std::strtod(stringValue.c_str(), nullptr) == dimensionIndex)
      return stringValue;
  }
  return llvm::formatv("{0}", llvm::format("%.17g", dimensionIndex)).str();
}

void printValue(const json::Value &valueHandle, llvm::raw_ostream &os,
                unsigned indent);

bool isFlat(const json::Value &valueHandle) {
  if (valueHandle.getAsObject())
    return false;
  if (const json::Array *arrayValue = valueHandle.getAsArray())
    return llvm::all_of(*arrayValue, [](const json::Value &entryValue) {
      if (const json::Array *inner = entryValue.getAsArray())
        return llvm::all_of(*inner, [](const json::Value &exprValue) {
          return !exprValue.getAsObject() && !exprValue.getAsArray();
        });
      return !entryValue.getAsObject();
    });
  return true;
}

void printScalar(const json::Value &valueHandle, llvm::raw_ostream &os) {
  switch (valueHandle.kind()) {
  case json::Value::Null:
    os << "null";
    return;
  case json::Value::Boolean:
    os << (*valueHandle.getAsBoolean() ? "true" : "false");
    return;
  case json::Value::Number:
    if (std::optional<int64_t> loopIndex = valueHandle.getAsInteger())
      os << *loopIndex;
    else
      os << formatDouble(*valueHandle.getAsNumber());
    return;
  case json::Value::String: {

    json::OStream innerIndex(os);
    innerIndex.value(valueHandle);
    return;
  }
  default:
    printValue(valueHandle, os, 0);
  }
}

void printValue(const json::Value &valueHandle, llvm::raw_ostream &os,
                unsigned indent) {
  std::string pad(indent, ' ');
  if (const json::Object *opHandle = valueHandle.getAsObject()) {
    if (opHandle->empty()) {
      os << "{}";
      return;
    }
    std::vector<StringRef> keys;
    for (const auto &kv : *opHandle)
      keys.push_back(kv.first);
    llvm::sort(keys);
    os << "{\n";
    for (size_t loopIndex = 0; loopIndex < keys.size(); ++loopIndex) {
      os << pad << "  ";
      printScalar(json::Value(keys[loopIndex].str()), os);
      os << ": ";
      printValue(*opHandle->get(keys[loopIndex]), os, indent + 2);
      os << (loopIndex + 1 < keys.size() ? ",\n" : "\n");
    }
    os << pad << "}";
    return;
  }
  if (const json::Array *arrayValue = valueHandle.getAsArray()) {
    if (arrayValue->empty()) {
      os << "[]";
      return;
    }
    if (isFlat(valueHandle)) {
      os << "[";
      for (size_t loopIndex = 0; loopIndex < arrayValue->size(); ++loopIndex) {
        if (loopIndex)
          os << ", ";
        printValue((*arrayValue)[loopIndex], os, indent);
      }
      os << "]";
      return;
    }
    os << "[\n";
    for (size_t loopIndex = 0; loopIndex < arrayValue->size(); ++loopIndex) {
      os << pad << "  ";
      printValue((*arrayValue)[loopIndex], os, indent + 2);
      os << (loopIndex + 1 < arrayValue->size() ? ",\n" : "\n");
    }
    os << pad << "]";
    return;
  }
  printScalar(valueHandle, os);
}

std::string sha256Hex(StringRef text) {
  llvm::SHA256 h;
  h.update(text);
  std::array<uint8_t, 32> digest = h.final();
  return llvm::toHex(digest, true);
}

/// Inserts `_doc` (section) and `_<key>` (key) descriptions from the schema.
void annotate(json::Value &valueHandle, const std::string &pattern) {
  json::Object *opHandle = valueHandle.getAsObject();
  if (!opHandle)
    return;
  if (!pattern.empty())
    if (const KeySpec *stringValue = findKeySpec(pattern);
        stringValue && (stringValue->kind == KeyKind::FreeObject))
      return;
  std::vector<std::string> keys;
  for (const auto &kv : *opHandle)
    keys.push_back(kv.first.str());
  for (const std::string &keyValue : keys) {
    if (StringRef(keyValue).starts_with("_"))
      continue;
    std::string portValue =
        pattern.empty() ? keyValue : pattern + "." + keyValue;
    const KeySpec *stringValue = findKeySpec(portValue);
    if (!stringValue)
      continue;
    std::string text = keyKindName(stringValue->kind).str();
    if (*stringValue->unit)
      text += ", " + std::string(stringValue->unit);
    if (stringValue->kind == KeyKind::Enum)
      text += " (" + std::string(stringValue->values) + ")";
    if (stringValue->kind == KeyKind::PluginName)
      text += " (a " + std::string(stringValue->values) + ")";
    text += ": " + std::string(stringValue->doc);
    if (*stringValue->rows)
      text += " [" + std::string(stringValue->rows) + "]";
    (*opHandle)["_" + keyValue] = text;
    json::Value &child = *opHandle->get(keyValue);
    if (stringValue->kind == KeyKind::Section)
      annotate(child, portValue);
    else if (stringValue->kind == KeyKind::ObjectList)
      if (json::Array *arrayValue = child.getAsArray())
        for (json::Value &entryValue : *arrayValue)
          annotate(entryValue, portValue + "[]");
  }
}

/// The compiled-in defaults, built once.
struct DefaultState {
  Config config;
  json::Value doc = nullptr;
};

const DefaultState &defaultState() {
  static const DefaultState state = [] {
    DefaultState stringValue;
    ConfigDiagnostics diag;
    DocumentBuilder b(diag);
    if (!b.start())
      llvm::report_fatal_error(
          llvm::Twine("hls-est: the compiled-in configuration does not "
                      "load: ") +
          (diag.errors.empty() ? "?" : diag.errors.front()));
    Validator(diag).validate(b.doc);
    fill(b.doc, stringValue.config);
    crossCheck(stringValue.config, diag);
    if (!diag.ok())
      llvm::report_fatal_error(
          llvm::Twine("hls-est: the compiled-in configuration is invalid: ") +
          diag.errors.front());
    stringValue.doc = b.doc;
    stringValue.config.merged = b.doc;
    std::string canonical;
    llvm::raw_string_ostream os(canonical);
    printValue(b.doc, os, 0);
    stringValue.config.hash = sha256Hex(os.str());
    return stringValue;
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
  std::string portValue;
  for (size_t loopIndex = 0; loopIndex < path.size(); ++loopIndex) {
    char ch = path[loopIndex];
    if (ch == '[' || ch == '(') {
      char close = ch == '[' ? ']' : ')';
      while (loopIndex < path.size() && path[loopIndex] != close)
        ++loopIndex;
      continue;
    }
    portValue += ch;
  }

  if (!sources.count(portValue)) {
    std::string below = portValue + ".";
    auto it = sources.lower_bound(below);
    if (it != sources.end() && StringRef(it->first).starts_with(below))
      return it->second;
  }
  for (;;) {
    auto it = sources.find(portValue);
    if (it != sources.end())
      return it->second;
    size_t dot = portValue.rfind('.');
    if (dot == std::string::npos)
      return "<defaults>";
    portValue.resize(dot);
  }
}

} // namespace

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
  for (const std::string &fieldValue : files)
    if (std::optional<json::Value> valueHandle =
            readJsonFile(fieldValue, diag)) {
      if (!valueHandle->getAsObject()->get("version"))
        diag.errors.push_back(fieldValue + ": version: missing (required; this "
                                           "hls-est reads version 1)");
      b.apply(std::move(*valueHandle), fieldValue, fieldValue);
    }
  for (const std::string &stringValue : sets)
    b.set(stringValue);
  if (!diag.ok())
    return c;

  auto attribute = [&](size_t first) {
    for (size_t loopIndex = first; loopIndex < diag.errors.size();
         ++loopIndex) {
      std::string &entryValue = diag.errors[loopIndex];
      size_t colon = entryValue.find(": ");
      if (colon == std::string::npos)
        continue;
      std::string origin = originOf(entryValue.substr(0, colon), b.sources);
      entryValue = origin + ": " + entryValue;
    }
  };
  Validator(diag).validate(b.doc);
  attribute(0);
  if (!diag.ok())
    return c;
  fill(b.doc, c);
  crossCheck(c, diag);
  attribute(0);

  if (const PluginConfigCheck &check = getPluginConfigCheck()) {
    size_t first = diag.errors.size();
    check(c, diag);

    for (size_t loopIndex = first; loopIndex < diag.errors.size();
         ++loopIndex) {
      std::string &entryValue = diag.errors[loopIndex];
      size_t colon = entryValue.find(": ");
      if (colon == std::string::npos)
        continue;
      std::string origin = originOf(entryValue.substr(0, colon), b.sources);
      if (origin != "<defaults>")
        entryValue = origin + ": " + entryValue;
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

std::string circt::hlsest::printSortedJson(const json::Value &valueHandle) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  printValue(valueHandle, os, 0);
  os << "\n";
  return stringValue;
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

  for (const ConfigOverride &opHandle : config.overrides) {
    StringRef path(opHandle.path);
    auto [parent, key] = path.rsplit('.');
    if (key.empty()) {
      key = parent;
      parent = "";
    }
    json::Value *cur = &doc;
    if (!parent.empty()) {
      SmallVector<StringRef> parts;
      parent.split(parts, '.');
      for (StringRef portValue : parts) {
        json::Object *obj = cur->getAsObject();
        cur = obj ? obj->get(portValue) : nullptr;
        if (!cur)
          break;
      }
    }
    if (!cur || !cur->getAsObject())
      continue;
    json::Object &obj = *cur->getAsObject();
    if (!obj.getObject("_source"))
      obj["_source"] = json::Object{};
    (*obj.getObject("_source"))[key.str()] = opHandle.source;
  }
  json::Object &root = *doc.getAsObject();
  root["_generated_by"] = "hls-est --dump-effective-config";
  root["_hash"] = config.hash;
  return printSortedJson(doc);
}

std::string circt::hlsest::dumpConfigSchema() {
  json::Array keys;
  const json::Value &dflt = defaultState().doc;
  for (const KeySpec &keyValue : configSchema()) {
    json::Object opHandle;
    opHandle["path"] = keyValue.path;
    opHandle["type"] = keyKindName(keyValue.kind);
    opHandle["unit"] = keyValue.unit;
    opHandle["doc"] = keyValue.doc;
    opHandle["rows"] = keyValue.rows;
    opHandle["readers"] = keyValue.readers;
    if (*keyValue.values)
      opHandle[keyValue.kind == KeyKind::PluginName ? "interface" : "values"] =
          keyValue.values;
    if (!std::isnan(keyValue.min))
      opHandle["min"] = keyValue.min;
    if (!std::isnan(keyValue.max))
      opHandle["max"] = keyValue.max;
    opHandle["optional"] = keyValue.optional;

    if (!StringRef(keyValue.path).contains("[]") &&
        keyValue.kind != KeyKind::Section) {
      SmallVector<StringRef> parts;
      StringRef(keyValue.path).split(parts, '.');
      const json::Value *cur = &dflt;
      for (StringRef portValue : parts) {
        const json::Object *obj = cur ? cur->getAsObject() : nullptr;
        cur = obj ? obj->get(portValue) : nullptr;
      }
      if (cur)
        opHandle["default"] = *cur;
    }
    keys.push_back(std::move(opHandle));
  }

  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  os << "{\n  \"_generated_by\": \"hls-est --dump-config-schema\",\n";
  os << "  \"keys\": [\n";
  for (size_t loopIndex = 0; loopIndex < keys.size(); ++loopIndex) {
    os << "    ";
    json::OStream innerIndex(os);
    innerIndex.value(keys[loopIndex]);
    os << (loopIndex + 1 < keys.size() ? ",\n" : "\n");
  }
  os << "  ],\n  \"plugin_interfaces\": [";
  llvm::interleave(
      pluginInterfaceKeys(), os,
      [&](const char *keyValue) { os << "\"" << keyValue << "\""; }, ", ");
  os << "],\n  \"version\": 1\n}\n";
  return stringValue;
}

std::vector<std::string> circt::hlsest::compiledInDevices() {
  std::vector<std::string> out;
  for (const CompiledIn &dimensionIndex : kDevices)
    out.push_back(dimensionIndex.id);
  return out;
}

std::vector<std::string> circt::hlsest::compiledInProfiles() {
  std::vector<std::string> out;
  for (const CompiledIn &portValue : kProfiles)
    out.push_back(portValue.id);
  return out;
}
