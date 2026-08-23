//===- Config.cpp - hls-est configuration: value types --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/Config.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/MathExtras.h"

#include <algorithm>
#include <numeric>

using namespace circt::hlsest;
using llvm::StringRef;

//===----------------------------------------------------------------------===//
// Rational, ResourceVector.
//===----------------------------------------------------------------------===//

Rational::Rational(int64_t n, int64_t d) : num(n), den(d) {
  if (den < 0) {
    num = -num;
    den = -den;
  }
  if (den == 0) {
    num = 0;
    den = 1;
    return;
  }
  int64_t g = std::gcd(num < 0 ? -num : num, den);
  if (g > 1) {
    num /= g;
    den /= g;
  }
}

int64_t Rational::ceil() const {
  if (den == 1)
    return num;
  return num >= 0 ? (num + den - 1) / den : num / den;
}

Rational Rational::operator+(const Rational &o) const {
  return Rational(num * o.den + o.num * den, den * o.den);
}

Rational Rational::operator*(const Rational &o) const {
  return Rational(num * o.num, den * o.den);
}

std::string Rational::str() const {
  if (den == 1)
    return std::to_string(num);
  return std::to_string(num) + "/" + std::to_string(den);
}

std::optional<Rational> Rational::fromJson(const llvm::json::Value &v) {
  if (std::optional<int64_t> i = v.getAsInteger())
    return *i >= 0 ? std::optional<Rational>(Rational(*i)) : std::nullopt;
  if (std::optional<StringRef> s = v.getAsString()) {
    auto [a, b] = s->split('/');
    int64_t n = 0, d = 1;
    if (a.trim().getAsInteger(10, n) || n < 0)
      return std::nullopt;
    if (!b.empty() && (b.trim().getAsInteger(10, d) || d <= 0))
      return std::nullopt;
    return Rational(n, d);
  }
  return std::nullopt;
}

Rational ResourceVector::get(StringRef cls) const {
  for (const auto &[name, n] : entries)
    if (name == cls)
      return n;
  return Rational();
}

void ResourceVector::add(StringRef cls, Rational n) {
  auto it = llvm::lower_bound(
      entries, cls, [](const std::pair<std::string, Rational> &e,
                       StringRef c) { return StringRef(e.first) < c; });
  if (it != entries.end() && it->first == cls) {
    it->second = it->second + n;
    return;
  }
  entries.insert(it, {cls.str(), n});
}

void ResourceVector::add(const ResourceVector &o) {
  for (const auto &[name, n] : o.entries)
    add(name, n);
}

ResourceVector ResourceVector::scaled(Rational factor) const {
  ResourceVector r;
  for (const auto &[name, n] : entries)
    r.entries.push_back({name, n * factor});
  return r;
}

llvm::json::Value ResourceVector::toJson() const {
  llvm::json::Object o;
  for (const auto &[name, n] : entries)
    o[name] = n.isInteger() ? llvm::json::Value(n.num)
                            : llvm::json::Value(n.str());
  return o;
}

std::string ResourceVector::str() const {
  std::string s;
  for (const auto &[name, n] : entries) {
    if (!s.empty())
      s += ", ";
    s += name + " " + n.str();
  }
  return s;
}

//===----------------------------------------------------------------------===//
// Lookups.
//===----------------------------------------------------------------------===//

const PortConfig *DeviceMemory::portConfig(StringRef name) const {
  for (const PortConfig &p : portConfigs)
    if (p.name == name)
      return &p;
  return nullptr;
}

bool DeviceMemory::hasGeometry(int64_t width, int64_t depth) const {
  return llvm::any_of(geometries, [&](const Geometry &g) {
    return g.width == width && g.depth == depth;
  });
}

const DeviceMemory *Device::memory(StringRef memId) const {
  for (const DeviceMemory &m : memories)
    if (m.id == memId)
      return &m;
  return nullptr;
}

const ResourceClass *Device::resourceClass(StringRef name) const {
  for (const ResourceClass &c : resourceClasses)
    if (c.name == name)
      return &c;
  return nullptr;
}

std::optional<std::string> Device::toolId(StringRef tool, StringRef key) const {
  const llvm::json::Object *t = toolIds.getObject(tool);
  if (!t)
    return std::nullopt;
  if (std::optional<StringRef> s = t->getString(key))
    return s->str();
  return std::nullopt;
}

int64_t MemoryArchitectureConfig::replicatedSlots() const {
  // One block RAM has two ports: every copy adds its port B as a read port,
  // and the shared port A writes, reading in a cycle without a write.
  constexpr int64_t kPortsPerBlock = 2;
  return replication.maxCopies * (kPortsPerBlock - 1) +
         (replication.sharedWritePortReadsWhenIdle ? 1 : 0);
}

bool MemoryArchitectureConfig::isWidePortSet(
    llvm::ArrayRef<std::string> ports) const {
  std::vector<std::string> sorted(ports.begin(), ports.end());
  llvm::sort(sorted);
  for (const std::vector<std::string> &set : widePortSets) {
    std::vector<std::string> s = set;
    llvm::sort(s);
    if (s == sorted)
      return true;
  }
  return false;
}

const ImplicitBufferConfig *
HlsToolConfig::implicitBuffer(StringRef protocol) const {
  for (const ImplicitBufferConfig &b : implicitBuffers)
    if (b.protocol == protocol)
      return &b;
  return nullptr;
}

static double bandDelay(llvm::ArrayRef<DelayBand> bands, unsigned bits) {
  for (const DelayBand &b : bands)
    if (!b.maxBits || static_cast<int64_t>(bits) <= *b.maxBits)
      return b.ns;
  return bands.empty() ? 0.0 : bands.back().ns;
}

double CallDepthConfig::carryChain(unsigned bits) const {
  return bandDelay(carryChainNs, bits);
}

double CallDepthConfig::ternaryAdder(unsigned bits) const {
  return bandDelay(ternaryAdderNs, bits);
}

int64_t SchedulingConfig::latency(StringRef cls) const {
  auto it = operatorLatencies.find(cls.str());
  return it == operatorLatencies.end() ? 0 : it->second;
}

double Config::periodNs() const {
  const TimingMargin &m = tool.hls.timingMargin;
  if (m.fraction)
    return run.clockNs * (1.0 - *m.fraction);
  if (m.ns)
    return run.clockNs - *m.ns;
  return run.clockNs;
}

const DeviceMemory *Config::blockMemory() const {
  return device.memory(tool.backend.memoryMapper.primitive);
}

int64_t Config::pricedPortWidth(bool wide) const {
  const MemoryArchitectureConfig &m = tool.hls.memoryArchitecture;
  if (const DeviceMemory *mem = blockMemory())
    if (const PortConfig *p =
            mem->portConfig(wide ? m.pricedWide : m.pricedNarrow))
      return p->maxWidth;
  return 0;
}

int64_t Config::blockPorts() const {
  if (const DeviceMemory *mem = blockMemory())
    if (const PortConfig *p =
            mem->portConfig(tool.hls.memoryArchitecture.pricedNarrow))
      return static_cast<int64_t>(p->ports.size());
  return 2;
}
