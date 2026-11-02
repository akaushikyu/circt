//===- StreamFifos.cpp - hls::stream FIFOs for --bram-analysis ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// How Vitis HLS 2025.1 implements an hls::stream (measured with minimal
// kernels and checked against every FIFO row of the HLSFactory corpus; the
// evidence is in hls-doc/notes/VITIS_NOTES.md):
//
//   - Every stream object is one FIFO: each element of an array of streams,
//     each stream member of a struct, local streams with or without dataflow,
//     static streams. A stream argument of the top function is an ap_fifo
//     port and has no FIFO inside the design; a stream passed to a callee is
//     the caller's FIFO, so only storage (allocas and globals) is priced,
//     never a function parameter.
//   - Depth: the `stream depth=` pragma, else the template argument of
//     hls::stream<T, DEPTH>, else 2.
//   - Width: the packed bits of T (a struct is the sum of its members, with no
//     C padding; bool is 1 bit).
//   - A FIFO of depth <= 2 is built from shift registers whatever its width,
//     and so is one of at most 1024 bits (depth x width, inclusive). Anything
//     larger is a block RAM priced like an array by the depth bands, but at
//     the 18-bit port width in every band: a FIFO never uses the 36-bit simple
//     dual-port mode although it has one write and one read port.
//   - A `bind_storage type=fifo` pragma overrides the choice: impl=srl or
//     impl=lutram costs no BRAM, impl=bram is a block RAM at any size.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"

#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Regex.h"

#include <map>
#include <set>
#include <tuple>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

// The FIFO rules are the configuration's tool.hls.streams: the depth of a
// stream without a depth pragma or template argument (default_depth, 2);
// FIFOs at most srl_max_depth (2) deep are shift registers at any width, and
// so are FIFOs of at most srl_max_bits (1024) bits (depth x width).
const circt::hlsest::StreamConfig &streamRules() {
  return circt::hlsest::Config::get().tool.hls.streams;
}

//===----------------------------------------------------------------------===//
// A small Itanium demangler: just enough to step over one type, so that the
// two template arguments of hls::stream<T, DEPTH> can be told apart (T may be
// a template such as ap_uint<16>, whose own `Li16E` must not be mistaken for
// DEPTH).
//===----------------------------------------------------------------------===//
struct Demangler {
  StringRef s;
  size_t i = 0;

  bool atEnd() const { return i >= s.size(); }
  char peek(size_t ahead = 0) const {
    return i + ahead < s.size() ? s[i + ahead] : '\0';
  }

  bool number(int64_t &value) {
    bool negative = false;
    if (peek() == 'n') {
      negative = true;
      ++i;
    }
    size_t start = i;
    while (!atEnd() && llvm::isDigit(peek()))
      ++i;
    if (start == i)
      return false;
    if (s.substr(start, i - start).getAsInteger(10, value))
      return false;
    if (negative)
      value = -value;
    return true;
  }

  bool sourceName() {
    int64_t len;
    if (!number(len) || len <= 0 || i + len > s.size())
      return false;
    i += len;
    return true;
  }

  bool substitution() {
    // S_, S<seq-id>_, St<name>, Sa / Sb / Ss / Si / So / Sd.
    ++i; // 'S'
    if (peek() == 't') {
      ++i;
      return sourceName();
    }
    if (StringRef("absiod").contains(peek())) {
      ++i;
      return true;
    }
    while (!atEnd() && peek() != '_' &&
           (llvm::isDigit(peek()) || llvm::isUpper(peek())))
      ++i;
    if (peek() != '_')
      return false;
    ++i;
    return true;
  }

  bool templateArgs() {
    ++i; // 'I'
    while (!atEnd() && peek() != 'E')
      if (!templateArg())
        return false;
    if (peek() != 'E')
      return false;
    ++i;
    return true;
  }

  bool literal(int64_t *value = nullptr) {
    ++i; // 'L'
    if (peek() == '_')
      return false; // external name: not needed here
    if (!type())
      return false;
    int64_t v;
    if (!number(v))
      return false;
    if (peek() != 'E')
      return false;
    ++i;
    if (value)
      *value = v;
    return true;
  }

  bool templateArg() {
    if (peek() == 'L')
      return literal();
    if (peek() == 'J') {
      ++i;
      while (!atEnd() && peek() != 'E')
        if (!templateArg())
          return false;
      if (peek() != 'E')
        return false;
      ++i;
      return true;
    }
    return type();
  }

  bool nestedName() {
    ++i; // 'N'
    while (StringRef("rVK").contains(peek()) && !atEnd())
      ++i;
    while (!atEnd() && peek() != 'E') {
      if (llvm::isDigit(peek())) {
        if (!sourceName())
          return false;
      } else if (peek() == 'I') {
        if (!templateArgs())
          return false;
      } else if (peek() == 'S') {
        if (!substitution())
          return false;
      } else {
        return false;
      }
    }
    if (peek() != 'E')
      return false;
    ++i;
    return true;
  }

  bool type() {
    if (atEnd())
      return false;
    char c = peek();
    if (StringRef("rVKPRO").contains(c)) {
      ++i;
      return type();
    }
    if (StringRef("vwbcahstijlmxynofdegz").contains(c)) {
      ++i;
      return true;
    }
    if (c == 'D') { // Dh (half), Dn, Di, Ds, Du, ...
      i += 2;
      return true;
    }
    if (c == 'A') { // A<n>_<type>
      ++i;
      int64_t n;
      if (!number(n) || peek() != '_')
        return false;
      ++i;
      return type();
    }
    if (llvm::isDigit(c)) {
      if (!sourceName())
        return false;
      return peek() == 'I' ? templateArgs() : true;
    }
    if (c == 'N')
      return nestedName();
    if (c == 'S') {
      if (!substitution())
        return false;
      return peek() == 'I' ? templateArgs() : true;
    }
    return false;
  }
};

} // namespace

std::optional<StreamTemplate>
circt::hls_analysis::parseStreamMethod(StringRef symbol) {
  StringRef rest;
  if (symbol.starts_with("_ZN3hls6streamI"))
    rest = symbol.drop_front(strlen("_ZN3hls6streamI"));
  else if (symbol.starts_with("_ZNK3hls6streamI"))
    rest = symbol.drop_front(strlen("_ZNK3hls6streamI"));
  else
    return std::nullopt;
  StreamTemplate t;
  Demangler d{rest};
  if (!d.type())
    return t; // an hls::stream method whose arguments we cannot read
  t.elementMangled = rest.substr(0, d.i).str();
  if (d.peek() == 'L') {
    int64_t depth;
    if (!d.literal(&depth))
      return t;
    t.depth = depth;
  }
  if (d.peek() != 'E')
    return t;
  ++d.i;
  t.method = rest.substr(d.i).str();
  return t;
}

std::optional<unsigned>
circt::hls_analysis::mangledElementBits(StringRef elementMangled) {
  StringRef t = elementMangled;
  while (t.consume_front("K") || t.consume_front("V"))
    ;
  static const std::map<std::string, unsigned> builtin = {
      {"b", 1},  {"c", 8},  {"a", 8},  {"h", 8},   {"s", 16},
      {"t", 16}, {"i", 32}, {"j", 32}, {"w", 32},  {"l", 64},
      {"m", 64}, {"x", 64}, {"y", 64}, {"n", 128}, {"o", 128},
      {"f", 32}, {"d", 64}, {"Dh", 16}};
  auto it = builtin.find(t.str());
  if (it != builtin.end())
    return it->second;
  // ap_[u]int<W>, ap_[u]fixed<W, ...>: the first template argument.
  static const llvm::Regex apType(
      "^(7ap_uint|6ap_int|8ap_fixed|9ap_ufixed|11ap_int_base|"
      "13ap_fixed_base)ILi([0-9]+)E");
  SmallVector<StringRef> m;
  if (apType.match(t, &m)) {
    unsigned bits;
    if (!m[2].getAsInteger(10, bits))
      return bits;
  }
  return std::nullopt;
}

unsigned circt::hls_analysis::packedTypeBits(Type type) {
  if (type.isIntOrFloat())
    return type.getIntOrFloatBitWidth();
  if (auto st = dyn_cast<LLVM::LLVMStructType>(type)) {
    unsigned sum = 0;
    for (Type m : st.getBody()) {
      unsigned b = packedTypeBits(m);
      if (b == 0)
        return 0;
      sum += b;
    }
    return sum;
  }
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(type)) {
    unsigned b = packedTypeBits(at.getElementType());
    return b * at.getNumElements();
  }
  if (auto vt = dyn_cast<VectorType>(type)) {
    if (!vt.hasStaticShape())
      return 0;
    return packedTypeBits(vt.getElementType()) * vt.getNumElements();
  }
  return 0;
}

namespace {
/// The C storage of `type` with the natural alignment of a default data
/// layout: bytes and alignment (0 bytes when unknown). An iN is the next
/// power of two bytes up to 8, then whole 8-byte words; a non-packed
/// struct pads each member to its alignment and the whole to the largest.
struct StorageSize {
  uint64_t bytes = 0;
  uint64_t align = 1;
};

StorageSize storageSize(Type type) {
  if (auto it = dyn_cast<IntegerType>(type)) {
    uint64_t bytes = llvm::divideCeil(it.getWidth(), 8);
    bytes = bytes <= 8 ? llvm::PowerOf2Ceil(bytes) : llvm::alignTo(bytes, 8);
    return {bytes, std::min<uint64_t>(bytes, 8)};
  }
  if (type.isF16() || type.isBF16())
    return {2, 2};
  if (type.isF32())
    return {4, 4};
  if (type.isF64())
    return {8, 8};
  if (auto st = dyn_cast<LLVM::LLVMStructType>(type)) {
    StorageSize out;
    for (Type m : st.getBody()) {
      StorageSize ms = storageSize(m);
      if (ms.bytes == 0)
        return {};
      uint64_t a = st.isPacked() ? 1 : ms.align;
      out.bytes = llvm::alignTo(out.bytes, a) + ms.bytes;
      out.align = std::max(out.align, a);
    }
    out.bytes = llvm::alignTo(out.bytes, out.align);
    return out;
  }
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(type)) {
    StorageSize es = storageSize(at.getElementType());
    return {es.bytes * at.getNumElements(), es.align};
  }
  return {};
}
} // namespace

unsigned circt::hls_analysis::storageTypeBits(Type type) {
  return static_cast<unsigned>(storageSize(type).bytes * 8);
}

FifoPrice circt::hls_analysis::priceFifo(
    int64_t depth, unsigned bits, StringRef bindImpl,
    llvm::function_ref<int64_t(int64_t, unsigned)> bandBlocks) {
  FifoPrice p;
  std::string geometry =
      std::to_string(depth) + "x" + std::to_string(bits) + " = " +
      std::to_string(depth * static_cast<int64_t>(bits)) + " bits";
  std::string impl = bindImpl.lower();
  if (impl == "srl" || impl == "lutram") {
    p.reason = "bind_storage impl=" + impl + ": " +
               (impl == "srl" ? "shift registers" : "distributed RAM") +
               ", 0 BRAM";
    return p;
  }
  if (bits == 0) {
    p.reason = "element width unknown: not estimated, 0 BRAM";
    return p;
  }
  // The width the FIFO is priced at (tool.hls.streams.priced_config: tdp,
  // x18) and the wide one it never gets (x36).
  const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
  int64_t pricedWidth = 0;
  if (const circt::hlsest::DeviceMemory *m = cfg.blockMemory())
    if (const circt::hlsest::PortConfig *pc =
            m->portConfig(streamRules().pricedConfig))
      pricedWidth = pc->maxWidth;
  const std::string priced = "x" + std::to_string(pricedWidth);
  const std::string wide = "x" + std::to_string(cfg.pricedPortWidth(true));
  if (impl == "bram") {
    p.bram = static_cast<unsigned>(bandBlocks(depth, bits));
    p.reason = "bind_storage impl=bram: block RAM at any size, " + geometry +
               ", depth bands at " + priced + " -> " + std::to_string(p.bram);
    return p;
  }
  const int64_t srlMaxDepth = streamRules().srlMaxDepth;
  const int64_t srlMaxBits = streamRules().srlMaxBits;
  if (depth <= srlMaxDepth) {
    p.reason = "depth " + std::to_string(depth) + " <= " +
               std::to_string(srlMaxDepth) +
               ": shift registers at any width, 0 BRAM";
    return p;
  }
  if (depth * static_cast<int64_t>(bits) <= srlMaxBits) {
    p.reason = geometry + " <= " + std::to_string(srlMaxBits) +
               ": shift registers, 0 BRAM";
    return p;
  }
  p.bram = static_cast<unsigned>(bandBlocks(depth, bits));
  p.reason = geometry + " > " + std::to_string(srlMaxBits) +
             ": block RAM, depth bands at " + priced + " (never " + wide +
             ") -> " +
             std::to_string(p.bram);
  return p;
}

namespace {

/// One hls::stream method call reached from the storage.
struct ReachedCall {
  std::optional<unsigned> member;
  Operation *call;
  StreamTemplate tmpl;
  /// The element of the storage the handle is, when every index on the way
  /// to the call was a constant (polygeist.subindex); nullopt otherwise.
  std::optional<SmallVector<int64_t, 2>> element;
};

bool isPointerCastLike(Operation *op) {
  StringRef name = op->getName().getStringRef();
  return name == "polygeist.subindex" || name == "polygeist.memref2pointer" ||
         name == "polygeist.pointer2memref" || name == "llvm.bitcast" ||
         name == "llvm.addrspacecast" || isa<memref::CastOp>(op);
}

/// The constant index of a polygeist.subindex, if it is one.
std::optional<int64_t> constantSubindex(Operation *op) {
  if (op->getName().getStringRef() != "polygeist.subindex" ||
      op->getNumOperands() != 2)
    return std::nullopt;
  APInt v;
  if (!matchPattern(op->getOperand(1), m_ConstantInt(&v)))
    return std::nullopt;
  return v.getSExtValue();
}

/// The handle path from the storage to a value: the constant element
/// indices taken so far, `complete` once one index per storage dimension was
/// taken; `known` is false once a non-constant index or an index the model
/// does not follow was taken.
struct ElementPath {
  SmallVector<int64_t, 2> indices;
  bool known = true;
  bool complete(unsigned rank) const {
    return known && indices.size() == rank;
  }
  bool operator<(const ElementPath &o) const {
    return std::tie(known, indices) < std::tie(o.known, o.indices);
  }
};

/// Follows the handle values to the hls::stream methods they reach as the
/// object argument. `structMembers` says whether a constant member GEP
/// selects a struct member (the storage holds structs); `rank` is the
/// storage's rank (how many element indices select one element).
SmallVector<ReachedCall> traceHandles(ArrayRef<Value> roots,
                                      bool structMembers, unsigned rank) {
  SmallVector<ReachedCall> out;
  struct Item {
    Value value;
    std::optional<unsigned> member;
    ElementPath path;
  };
  SmallVector<Item> work;
  std::set<std::tuple<void *, int64_t, ElementPath>> seen;
  auto push = [&](Value v, std::optional<unsigned> member, ElementPath path) {
    if (seen.insert({v.getAsOpaquePointer(), member ? int64_t(*member) : -1,
                     path})
            .second)
      work.push_back({v, member, std::move(path)});
  };
  for (Value r : roots)
    push(r, std::nullopt, ElementPath{});
  while (!work.empty()) {
    Item item = work.pop_back_val();
    Value cur = item.value;
    std::optional<unsigned> member = item.member;
    const ElementPath &path = item.path;
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        auto sym = llvm::dyn_cast_if_present<SymbolRefAttr>(
            call.getCallableForCallee());
        auto args = call.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned n = use.getOperandNumber();
        if (n < first || n - first >= args.size())
          continue;
        unsigned argIndex = n - first;
        if (sym) {
          if (auto t = parseStreamMethod(sym.getLeafReference().getValue())) {
            // Only as the object argument: a handle passed as data (a
            // stream of streams) is not modelled.
            if (argIndex == 0) {
              ReachedCall rc{member, user, *t, std::nullopt};
              if (path.complete(rank))
                rc.element = path.indices;
              out.push_back(std::move(rc));
            }
            continue;
          }
        }
        auto callee = dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
        if (callee && !callee.isExternal() &&
            argIndex < callee.getNumArguments())
          push(callee.getArgument(argIndex), member, path);
        continue;
      }
      if (auto gep = dyn_cast<LLVM::GEPOp>(user)) {
        if (gep.getBase() != cur)
          continue;
        std::optional<unsigned> next = member;
        ElementPath nextPath = path;
        ArrayRef<int32_t> idx = gep.getRawConstantIndices();
        bool memberGep = idx.size() == 2 && idx[0] == 0 &&
                         idx[1] != LLVM::GEPOp::kDynamicIndex;
        if (structMembers && !member && memberGep)
          next = static_cast<unsigned>(idx[1]);
        // A member GEP of one selected element stays in that element; any
        // other offset is not followed element-wise.
        if (!(memberGep && path.complete(rank)))
          nextPath.known = false;
        push(gep.getResult(), next, std::move(nextPath));
        continue;
      }
      bool view = isPointerCastLike(user);
      if (auto v = dyn_cast<ViewLikeOpInterface>(user))
        view = view || v.getViewSource() == cur;
      if (!view)
        continue;
      ElementPath nextPath = path;
      if (user->getName().getStringRef() == "polygeist.subindex") {
        // An index into the storage selects an element when it is a
        // constant; an index past the storage's rank selects inside an
        // element (a member array): not followed element-wise.
        std::optional<int64_t> c = constantSubindex(user);
        if (c && path.known && path.indices.size() < rank)
          nextPath.indices.push_back(*c);
        else
          nextPath.known = false;
      } else if (!isa<memref::CastOp>(user) && !path.complete(rank)) {
        // A pointer conversion or a view before one element is selected may
        // reshape the storage: later indices are not element indices.
        nextPath.known = false;
      }
      // polygeist.subindex on a struct memref without a member index keeps
      // the struct; a struct member is selected by the GEP above.
      for (Value r : user->getResults())
        push(r, member, nextPath);
    }
  }
  return out;
}

/// How many stream handles one struct member holds: a member that is an
/// array of handles holds one per array element (`hls::stream<T> s[4]` in a
/// struct is 4 FIFOs). A handle reached without a member index is member 0.
int64_t handlesPerMember(Type elt, std::optional<unsigned> member) {
  auto st = dyn_cast<LLVM::LLVMStructType>(elt);
  if (!st)
    return 1;
  unsigned idx = member ? *member : 0;
  ArrayRef<Type> body = st.getBody();
  if (idx >= body.size())
    return 1;
  int64_t n = 1;
  Type t = body[idx];
  while (auto at = dyn_cast<LLVM::LLVMArrayType>(t)) {
    n *= at.getNumElements();
    t = at.getElementType();
  }
  return n;
}

/// The data type a read / write call moves, from its IR signature.
Type ioType(Operation *call, StringRef method) {
  if (method.starts_with("C") || method.starts_with("D"))
    return {}; // constructor / destructor: operand 1 is the name string
  if (method.starts_with("4readEv") && call->getNumResults() == 1)
    return call->getResult(0).getType();
  bool dataByReference = method.starts_with("4read") ||
                         method.starts_with("5write") ||
                         method.starts_with("7read_nb") ||
                         method.starts_with("8write_nb") ||
                         method.starts_with("rs") || method.starts_with("ls");
  if (dataByReference && call->getNumOperands() >= 2)
    if (auto mt = dyn_cast<MemRefType>(call->getOperand(1).getType()))
      return mt.getElementType();
  return {};
}

bool isConstructor(StringRef method) {
  return method.starts_with("C1") || method.starts_with("C2") ||
         method.starts_with("D1") || method.starts_with("D2");
}

std::string typeString(Type t) {
  std::string s;
  llvm::raw_string_ostream os(s);
  t.print(os);
  return s;
}

} // namespace

std::optional<StreamHandleRecord> circt::hls_analysis::analyzeStreamHandle(
    Operation *storage, ArrayRef<Value> sites,
    llvm::function_ref<int64_t(int64_t, unsigned)> bandBlocks) {
  MemRefType type;
  if (auto a = dyn_cast<memref::AllocaOp>(storage))
    type = a.getType();
  else if (auto a = dyn_cast<memref::AllocOp>(storage))
    type = a.getType();
  else if (auto g = dyn_cast<memref::GlobalOp>(storage))
    type = g.getType();
  if (!type)
    return std::nullopt;
  // The handle is a word (cgeist's hls::stream holds one int), or a struct
  // whose members include handles.
  Type elt = type.getElementType();
  bool structMembers = isa<LLVM::LLVMStructType>(elt);
  if (!structMembers && !isa<IntegerType>(elt))
    return std::nullopt;

  SmallVector<ReachedCall> calls =
      traceHandles(sites, structMembers, type.getRank());
  if (calls.empty())
    return std::nullopt;

  StreamHandleRecord rec;
  std::set<std::string> methods;
  for (const ReachedCall &c : calls)
    methods.insert(c.tmpl.method.empty() ? "?" : c.tmpl.method);
  rec.methods.assign(methods.begin(), methods.end());

  int64_t elements = 1;
  for (int64_t d : type.getShape()) {
    if (ShapedType::isDynamic(d)) {
      rec.note += "dynamic shape: one FIFO per known element only; ";
      continue;
    }
    elements *= d;
  }

  // The stream pragma (hls.stream: depth, variable) and bind_storage
  // type=fifo (impl) on the storage.
  std::optional<int64_t> pragmaDepth;
  std::string pragmaVariable;
  // A pragma naming one element (`s[0]`, constant subscripts, one per
  // dimension of the storage): that element's depth only, by its linear
  // index (VITIS_NOTES N177, tool.hls.streams.element_depth_pragmas).
  std::map<int64_t, int64_t> elementDepths;
  auto elementOf = [&](StringRef var) -> std::optional<int64_t> {
    size_t open = var.find('[');
    if (open == StringRef::npos || !type.hasStaticShape())
      return std::nullopt;
    StringRef rest = var.drop_front(open);
    int64_t linear = 0;
    unsigned dim = 0;
    while (!rest.empty()) {
      if (!rest.consume_front("["))
        return std::nullopt;
      size_t close = rest.find(']');
      if (close == StringRef::npos)
        return std::nullopt;
      int64_t v;
      if (rest.take_front(close).trim().getAsInteger(10, v) ||
          dim >= type.getRank() || v < 0 || v >= type.getShape()[dim])
        return std::nullopt;
      linear = linear * type.getShape()[dim] + v;
      ++dim;
      rest = rest.drop_front(close + 1);
    }
    if (dim != type.getRank())
      return std::nullopt;
    return linear;
  };
  if (auto arr = storage->getAttrOfType<ArrayAttr>("hls.stream"))
    for (Attribute a : arr)
      if (auto d = dyn_cast<DictionaryAttr>(a)) {
        if (auto depth = d.getAs<IntegerAttr>("depth")) {
          auto v = d.getAs<StringAttr>("variable");
          std::optional<int64_t> element;
          if (v && streamRules().elementDepthPragmas)
            element = elementOf(v.getValue());
          if (element) {
            elementDepths[*element] = depth.getInt();
            continue;
          }
          pragmaDepth = depth.getInt();
          if (v)
            pragmaVariable = v.getValue().str();
        }
      }
  std::string bindImpl;
  if (auto arr = storage->getAttrOfType<ArrayAttr>("hls.bind_storage"))
    for (Attribute a : arr)
      if (auto d = dyn_cast<DictionaryAttr>(a)) {
        auto t = d.getAs<StringAttr>("type");
        auto impl = d.getAs<StringAttr>("impl");
        if (t && impl && t.getValue().equals_insensitive("fifo"))
          bindImpl = impl.getValue().str();
      }

  // Group the reached calls by struct member (none for a plain handle).
  std::map<int64_t, SmallVector<const ReachedCall *>> byMember;
  for (const ReachedCall &c : calls)
    byMember[c.member ? int64_t(*c.member) : -1].push_back(&c);
  // A struct pragma names its member (`ch.a`); the IR has no member names,
  // so it can only be placed when one member holds streams.
  bool memberPragmaResolved = !structMembers || byMember.size() == 1;
  if (pragmaDepth && !memberPragmaResolved)
    rec.note += "stream pragma on '" + pragmaVariable +
                "' not resolved to a struct member (the IR has no member "
                "names): every member uses its template depth; ";
  if (structMembers && byMember.count(-1))
    rec.note += "a handle reached without a member index: counted as one "
                "FIFO per element; ";

  for (auto &[memberKey, memberCalls] : byMember) {
    FifoGroup g;
    if (memberKey >= 0)
      g.member = static_cast<unsigned>(memberKey);
    // Count: one FIFO per element of the storage that a read or write
    // reaches. When every handle is reached through constant indices, only
    // the elements reached count: Vitis removes the streams of an array that
    // nothing reads or writes (kernel: hls::stream<int> mid[3] with only
    // mid[1] used builds one FIFO). Otherwise every element counts.
    std::set<SmallVector<int64_t, 2>> reachedElements;
    bool allConstant = true;
    for (const ReachedCall *c : memberCalls) {
      if (isConstructor(c->tmpl.method))
        continue;
      if (c->element)
        reachedElements.insert(*c->element);
      else
        allConstant = false;
    }
    int64_t perMember = handlesPerMember(elt, g.member);
    if (allConstant && !reachedElements.empty() &&
        static_cast<int64_t>(reachedElements.size()) < elements) {
      g.count = static_cast<int64_t>(reachedElements.size());
      g.countSource = std::to_string(g.count) + " of " +
                      std::to_string(elements) +
                      " elements read or written (constant indices)";
    } else {
      g.count = elements;
      g.countSource = "every element";
    }
    if (perMember > 1) {
      g.count *= perMember;
      g.countSource += " x " + std::to_string(perMember) +
                       " handles of the member array";
    }
    // Depth: the pragma, else the template argument of the variable's own
    // type, else 2. A call through an `hls::stream<T>&` parameter names the
    // base class `stream<T, 0>` even when the object is a `stream<T, D>`
    // (the real headers derive the sized stream from the unsized one), so
    // its 0 says nothing about the object (VITIS_NOTES N49). The depth is
    // the constructor's when one is reached, else the global's declared
    // depth (below), else the largest D any call carries; 0 only when every
    // call carries 0.
    std::optional<int64_t> tmplDepth;
    std::string elementMangled;
    auto takeDepth = [&](const ReachedCall *c) {
      tmplDepth = c->tmpl.depth;
      elementMangled = c->tmpl.elementMangled;
    };
    for (const ReachedCall *c : memberCalls)
      if (c->tmpl.depth && *c->tmpl.depth > 0 &&
          isConstructor(c->tmpl.method)) {
        takeDepth(c);
        break;
      }
    // A namespace-scope `hls::stream<T, D>` has no constructor call in the
    // MLIR (the translation unit's initialiser runs it, and cgeist does not
    // emit it); cgeist keeps D on the global as `hls.stream_depth` (kernel
    // w9r6rev n49b: `static hls::stream<W, 1024> gs;` used only through
    // `hls::stream<W>&` parameters, Vitis 2 BRAM). Then the calls give the
    // element type only.
    std::optional<int64_t> declaredDepth;
    if (auto d = storage->getAttrOfType<IntegerAttr>("hls.stream_depth"))
      if (d.getInt() > 0 && memberKey < 0)
        declaredDepth = d.getInt();
    if ((!tmplDepth || *tmplDepth == 0) && declaredDepth) {
      for (const ReachedCall *c : memberCalls)
        if (!c->tmpl.elementMangled.empty()) {
          elementMangled = c->tmpl.elementMangled;
          break;
        }
      tmplDepth = declaredDepth;
    }
    if (!tmplDepth || *tmplDepth == 0)
      for (const ReachedCall *c : memberCalls)
        if (c->tmpl.depth && (!tmplDepth || *c->tmpl.depth > *tmplDepth))
          takeDepth(c);
    if (pragmaDepth && memberPragmaResolved) {
      g.depth = *pragmaDepth;
      g.depthSource = "pragma";
    } else if (tmplDepth && *tmplDepth > 0) {
      g.depth = *tmplDepth;
      g.depthSource = "template";
    } else {
      g.depth = streamRules().defaultDepth;
      g.depthSource = tmplDepth ? "default" : "default (template unparsed)";
    }
    // Width: the packed bits cgeist recorded from the C++ element type
    // (`hls.stream_element_bits` on the stream member it calls: a struct is
    // the sum of its members, bool 1 bit, VITIS_NOTES N58), else the mangled
    // element type when it says exactly (bool, ap_*), else the packed bits
    // of the data type the reads / writes move (a bool member is an i8
    // there).
    std::optional<unsigned> declaredBits;
    for (const ReachedCall *c : memberCalls) {
      if (!streamRules().declaredElementBits)
        break;
      auto call = dyn_cast<CallOpInterface>(c->call);
      auto callee =
          call ? dyn_cast_or_null<func::FuncOp>(call.resolveCallable())
               : func::FuncOp();
      if (!callee)
        continue;
      if (auto a = callee->getAttrOfType<IntegerAttr>(
              "hls.stream_element_bits"))
        if (a.getInt() > 0) {
          declaredBits = static_cast<unsigned>(a.getInt());
          break;
        }
    }
    // A function-static stream of a struct is as wide as the struct's C
    // storage, padding included (VITIS_NOTES N141: kernels w9r18rv_k9 /
    // k10 / k11 and w9r18fx_sbfst at sizeof * 8 bits, the same structs in
    // a local stream at the packed bits, w9r18fx_k9loc and N58's sb_*;
    // pengzhao lab3 `ArowStream` / `CrowStream` 96 bits). cgeist names a
    // function-static variable `<function>@static@<variable>`.
    std::optional<unsigned> storageBits;
    if (auto glob = dyn_cast<memref::GlobalOp>(storage);
        glob && streamRules().staticStructStorageBits &&
        glob.getSymName().contains("@static@")) {
      for (const ReachedCall *c : memberCalls) {
        if (isConstructor(c->tmpl.method))
          continue;
        Type t = ioType(c->call, c->tmpl.method);
        if (!t || !isa<LLVM::LLVMStructType>(t))
          continue;
        if (unsigned b = storageTypeBits(t))
          storageBits = b;
        break;
      }
    }
    if (storageBits) {
      g.bits = *storageBits;
      g.bitsSource = "static struct storage";
    } else if (declaredBits) {
      g.bits = *declaredBits;
      g.bitsSource = "cgeist hls.stream_element_bits";
    } else if (auto bits = mangledElementBits(elementMangled)) {
      g.bits = *bits;
      g.bitsSource = "mangled " + elementMangled;
    } else {
      for (const ReachedCall *c : memberCalls) {
        if (isConstructor(c->tmpl.method))
          continue;
        if (Type t = ioType(c->call, c->tmpl.method)) {
          if (unsigned b = packedTypeBits(t)) {
            g.bits = b;
            g.bitsSource = "ir " + typeString(t);
            break;
          }
        }
      }
      if (g.bits == 0)
        g.bitsSource = "unknown";
    }
    bool used = llvm::any_of(memberCalls, [](const ReachedCall *c) {
      return !isConstructor(c->tmpl.method);
    });
    // The elements an element pragma names, among the counted ones: one
    // FIFO each at the pragma's depth, out of this group (N177).
    std::vector<FifoGroup> elementGroups;
    if (memberKey < 0 && !structMembers)
      for (auto [linear, depth] : elementDepths) {
        bool counted = true;
        if (allConstant && !reachedElements.empty() &&
            static_cast<int64_t>(reachedElements.size()) < elements) {
          counted = false;
          for (const SmallVector<int64_t, 2> &e : reachedElements) {
            int64_t l = 0;
            for (auto [i, v] : llvm::enumerate(e))
              l = l * type.getShape()[i] + v;
            counted |= l == linear;
          }
        }
        if (!counted || g.count <= 0)
          continue;
        FifoGroup eg = g;
        eg.count = 1;
        eg.countSource = "element " + std::to_string(linear) +
                         " (a stream pragma names it, N177)";
        eg.depth = depth;
        eg.depthSource = "pragma (element)";
        --g.count;
        elementGroups.push_back(std::move(eg));
      }
    auto price = [&](FifoGroup &grp) {
      if (!used) {
        grp.reason = "constructed but never read or written: no FIFO (an "
                     "unused channel is removed; unconfirmed), 0 BRAM";
        return;
      }
      FifoPrice p = priceFifo(grp.depth, grp.bits, bindImpl, bandBlocks);
      grp.bramEach = p.bram;
      grp.reason = p.reason;
      rec.fifos += grp.count;
      rec.bram += static_cast<unsigned>(grp.count) * grp.bramEach;
    };
    if (g.count > 0 || elementGroups.empty()) {
      price(g);
      rec.groups.push_back(std::move(g));
    }
    for (FifoGroup &eg : elementGroups) {
      price(eg);
      rec.groups.push_back(std::move(eg));
    }
  }
  if (!rec.note.empty() && StringRef(rec.note).ends_with("; "))
    rec.note.resize(rec.note.size() - 2);
  return rec;
}
