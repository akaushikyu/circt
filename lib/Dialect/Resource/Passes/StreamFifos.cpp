

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Config/Config.h"

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

const circt::hlsest::StreamConfig &streamRules() {
  return circt::hlsest::Config::get().tool.hls.streams;
}

struct Demangler {
  StringRef stringValue;
  size_t i = 0;

  bool atEnd() const { return i >= stringValue.size(); }
  char peek(size_t ahead = 0) const {
    return i + ahead < stringValue.size() ? stringValue[i + ahead] : '\0';
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
    if (stringValue.substr(start, i - start).getAsInteger(10, value))
      return false;
    if (negative)
      value = -value;
    return true;
  }

  bool sourceName() {
    int64_t len;
    if (!number(len) || len <= 0 || i + len > stringValue.size())
      return false;
    i += len;
    return true;
  }

  bool substitution() {

    ++i;
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
    ++i;
    while (!atEnd() && peek() != 'E')
      if (!templateArg())
        return false;
    if (peek() != 'E')
      return false;
    ++i;
    return true;
  }

  bool literal(int64_t *value = nullptr) {
    ++i;
    if (peek() == '_')
      return false;
    if (!type())
      return false;
    int64_t valueHandle;
    if (!number(valueHandle))
      return false;
    if (peek() != 'E')
      return false;
    ++i;
    if (value)
      *value = valueHandle;
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
    ++i;
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
    char candidateValue = peek();
    if (StringRef("rVKPRO").contains(candidateValue)) {
      ++i;
      return type();
    }
    if (StringRef("vwbcahstijlmxynofdegz").contains(candidateValue)) {
      ++i;
      return true;
    }
    if (candidateValue == 'D') {
      i += 2;
      return true;
    }
    if (candidateValue == 'A') {
      ++i;
      int64_t elementCount;
      if (!number(elementCount) || peek() != '_')
        return false;
      ++i;
      return type();
    }
    if (llvm::isDigit(candidateValue)) {
      if (!sourceName())
        return false;
      return peek() == 'I' ? templateArgs() : true;
    }
    if (candidateValue == 'N')
      return nestedName();
    if (candidateValue == 'S') {
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
  StreamTemplate typeValue;
  Demangler dimensionIndex{rest};
  if (!dimensionIndex.type())
    return typeValue;
  typeValue.elementMangled = rest.substr(0, dimensionIndex.i).str();
  if (dimensionIndex.peek() == 'L') {
    int64_t depth;
    if (!dimensionIndex.literal(&depth))
      return typeValue;
    typeValue.depth = depth;
  }
  if (dimensionIndex.peek() != 'E')
    return typeValue;
  ++dimensionIndex.i;
  typeValue.method = rest.substr(dimensionIndex.i).str();
  return typeValue;
}

std::optional<unsigned>
circt::hls_analysis::mangledElementBits(StringRef elementMangled) {
  StringRef typeValue = elementMangled;
  while (typeValue.consume_front("K") || typeValue.consume_front("V"))
    ;
  static const std::map<std::string, unsigned> builtin = {
      {"b", 1},  {"c", 8},   {"a", 8},   {"h", 8},  {"s", 16}, {"t", 16},
      {"i", 32}, {"j", 32},  {"w", 32},  {"l", 64}, {"m", 64}, {"x", 64},
      {"y", 64}, {"n", 128}, {"o", 128}, {"f", 32}, {"d", 64}, {"Dh", 16}};
  auto it = builtin.find(typeValue.str());
  if (it != builtin.end())
    return it->second;

  static const llvm::Regex apType(
      "^(7ap_uint|6ap_int|8ap_fixed|9ap_ufixed|11ap_int_base|"
      "13ap_fixed_base)ILi([0-9]+)E");
  SmallVector<StringRef> memoryOp;
  if (apType.match(typeValue, &memoryOp)) {
    unsigned bits;
    if (!memoryOp[2].getAsInteger(10, bits))
      return bits;
  }
  return std::nullopt;
}

unsigned circt::hls_analysis::packedTypeBits(Type type) {
  if (type.isIntOrFloat())
    return type.getIntOrFloatBitWidth();
  if (auto st = dyn_cast<LLVM::LLVMStructType>(type)) {
    unsigned sum = 0;
    for (Type memoryOp : st.getBody()) {
      unsigned buildPoint = packedTypeBits(memoryOp);
      if (buildPoint == 0)
        return 0;
      sum += buildPoint;
    }
    return sum;
  }
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(type)) {
    unsigned buildPoint = packedTypeBits(at.getElementType());
    return buildPoint * at.getNumElements();
  }
  if (auto vt = dyn_cast<VectorType>(type)) {
    if (!vt.hasStaticShape())
      return 0;
    return packedTypeBits(vt.getElementType()) * vt.getNumElements();
  }
  return 0;
}

FifoPrice circt::hls_analysis::priceFifo(
    int64_t depth, unsigned bits, StringRef bindImpl,
    llvm::function_ref<int64_t(int64_t, unsigned)> bandBlocks) {
  FifoPrice portValue;
  std::string geometry =
      std::to_string(depth) + "x" + std::to_string(bits) + " = " +
      std::to_string(depth * static_cast<int64_t>(bits)) + " bits";
  std::string impl = bindImpl.lower();
  if (impl == "srl" || impl == "lutram") {
    portValue.reason = "bind_storage impl=" + impl + ": " +
                       (impl == "srl" ? "shift registers" : "distributed RAM") +
                       ", 0 BRAM";
    return portValue;
  }
  if (bits == 0) {
    portValue.reason = "element width unknown: not estimated, 0 BRAM";
    return portValue;
  }

  const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
  int64_t pricedWidth = 0;
  if (const circt::hlsest::DeviceMemory *memoryOp = cfg.blockMemory())
    if (const circt::hlsest::PortConfig *pc =
            memoryOp->portConfig(streamRules().pricedConfig))
      pricedWidth = pc->maxWidth;
  const std::string priced = "x" + std::to_string(pricedWidth);
  const std::string wide = "x" + std::to_string(cfg.pricedPortWidth(true));
  if (impl == "bram") {
    portValue.bram = static_cast<unsigned>(bandBlocks(depth, bits));
    portValue.reason = "bind_storage impl=bram: block RAM at any size, " +
                       geometry + ", depth bands at " + priced + " -> " +
                       std::to_string(portValue.bram);
    return portValue;
  }
  const int64_t srlMaxDepth = streamRules().srlMaxDepth;
  const int64_t srlMaxBits = streamRules().srlMaxBits;
  if (depth <= srlMaxDepth) {
    portValue.reason = "depth " + std::to_string(depth) +
                       " <= " + std::to_string(srlMaxDepth) +
                       ": shift registers at any width, 0 BRAM";
    return portValue;
  }
  if (depth * static_cast<int64_t>(bits) <= srlMaxBits) {
    portValue.reason = geometry + " <= " + std::to_string(srlMaxBits) +
                       ": shift registers, 0 BRAM";
    return portValue;
  }
  portValue.bram = static_cast<unsigned>(bandBlocks(depth, bits));
  portValue.reason = geometry + " > " + std::to_string(srlMaxBits) +
                     ": block RAM, depth bands at " + priced + " (never " +
                     wide + ") -> " + std::to_string(portValue.bram);
  return portValue;
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
  APInt valueHandle;
  if (!matchPattern(op->getOperand(1), m_ConstantInt(&valueHandle)))
    return std::nullopt;
  return valueHandle.getSExtValue();
}

/// The handle path from the storage to a value: the constant element
/// indices taken so far, `complete` once one index per storage dimension was
/// taken; `known` is false once a non-constant index or an index the model
/// does not follow was taken.
struct ElementPath {
  SmallVector<int64_t, 2> indices;
  bool known = true;
  bool complete(unsigned rank) const { return known && indices.size() == rank; }
  bool operator<(const ElementPath &opHandle) const {
    return std::tie(known, indices) <
           std::tie(opHandle.known, opHandle.indices);
  }
};

/// Follows the handle values to the hls::stream methods they reach as the
/// object argument. `structMembers` says whether a constant member GEP
/// selects a struct member (the storage holds structs); `rank` is the
/// storage's rank (how many element indices select one element).
SmallVector<ReachedCall> traceHandles(ArrayRef<Value> roots, bool structMembers,
                                      unsigned rank) {
  SmallVector<ReachedCall> out;
  struct Item {
    Value value;
    std::optional<unsigned> member;
    ElementPath path;
  };
  SmallVector<Item> work;
  std::set<std::tuple<void *, int64_t, ElementPath>> seen;
  auto push = [&](Value valueHandle, std::optional<unsigned> member,
                  ElementPath path) {
    if (seen.insert({valueHandle.getAsOpaquePointer(),
                     member ? int64_t(*member) : -1, path})
            .second)
      work.push_back({valueHandle, member, std::move(path)});
  };
  for (Value resultValue : roots)
    push(resultValue, std::nullopt, ElementPath{});
  while (!work.empty()) {
    Item item = work.pop_back_val();
    Value cur = item.value;
    std::optional<unsigned> member = item.member;
    const ElementPath &path = item.path;
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        auto symbolName = llvm::dyn_cast_if_present<SymbolRefAttr>(
            call.getCallableForCallee());
        auto args = call.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned elementCount = use.getOperandNumber();
        if (elementCount < first || elementCount - first >= args.size())
          continue;
        unsigned argIndex = elementCount - first;
        if (symbolName) {
          if (auto typeValue =
                  parseStreamMethod(symbolName.getLeafReference().getValue())) {

            if (argIndex == 0) {
              ReachedCall rc{member, user, *typeValue, std::nullopt};
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
        ArrayRef<int32_t> indexValue = gep.getRawConstantIndices();
        bool memberGep = indexValue.size() == 2 && indexValue[0] == 0 &&
                         indexValue[1] != LLVM::GEPOp::kDynamicIndex;
        if (structMembers && !member && memberGep)
          next = static_cast<unsigned>(indexValue[1]);

        if (!(memberGep && path.complete(rank)))
          nextPath.known = false;
        push(gep.getResult(), next, std::move(nextPath));
        continue;
      }
      bool view = isPointerCastLike(user);
      if (auto valueHandle = dyn_cast<ViewLikeOpInterface>(user))
        view = view || valueHandle.getViewSource() == cur;
      if (!view)
        continue;
      ElementPath nextPath = path;
      if (user->getName().getStringRef() == "polygeist.subindex") {

        std::optional<int64_t> candidateValue = constantSubindex(user);
        if (candidateValue && path.known && path.indices.size() < rank)
          nextPath.indices.push_back(*candidateValue);
        else
          nextPath.known = false;
      } else if (!isa<memref::CastOp>(user) && !path.complete(rank)) {

        nextPath.known = false;
      }

      for (Value resultValue : user->getResults())
        push(resultValue, member, nextPath);
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
  unsigned indexValue = member ? *member : 0;
  ArrayRef<Type> body = st.getBody();
  if (indexValue >= body.size())
    return 1;
  int64_t elementCount = 1;
  Type typeValue = body[indexValue];
  while (auto at = dyn_cast<LLVM::LLVMArrayType>(typeValue)) {
    elementCount *= at.getNumElements();
    typeValue = at.getElementType();
  }
  return elementCount;
}

/// The data type a read / write call moves, from its IR signature.
Type ioType(Operation *call, StringRef method) {
  if (method.starts_with("C") || method.starts_with("D"))
    return {};
  if (method.starts_with("4readEv") && call->getNumResults() == 1)
    return call->getResult(0).getType();
  bool dataByReference =
      method.starts_with("4read") || method.starts_with("5write") ||
      method.starts_with("7read_nb") || method.starts_with("8write_nb") ||
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

std::string typeString(Type typeValue) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  typeValue.print(os);
  return stringValue;
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
  else if (auto globalOp = dyn_cast<memref::GlobalOp>(storage))
    type = globalOp.getType();
  if (!type)
    return std::nullopt;

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
  for (const ReachedCall &candidateValue : calls)
    methods.insert(
        candidateValue.tmpl.method.empty() ? "?" : candidateValue.tmpl.method);
  rec.methods.assign(methods.begin(), methods.end());

  int64_t elements = 1;
  for (int64_t dimensionIndex : type.getShape()) {
    if (ShapedType::isDynamic(dimensionIndex)) {
      rec.note += "dynamic shape: one FIFO per known element only; ";
      continue;
    }
    elements *= dimensionIndex;
  }

  std::optional<int64_t> pragmaDepth;
  std::string pragmaVariable;
  if (auto arr = storage->getAttrOfType<ArrayAttr>("hls.stream"))
    for (Attribute a : arr)
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(a)) {
        if (auto depth = dimensionIndex.getAs<IntegerAttr>("depth")) {
          pragmaDepth = depth.getInt();
          if (auto valueHandle = dimensionIndex.getAs<StringAttr>("variable"))
            pragmaVariable = valueHandle.getValue().str();
        }
      }
  std::string bindImpl;
  if (auto arr = storage->getAttrOfType<ArrayAttr>("hls.bind_storage"))
    for (Attribute a : arr)
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(a)) {
        auto typeValue = dimensionIndex.getAs<StringAttr>("type");
        auto impl = dimensionIndex.getAs<StringAttr>("impl");
        if (typeValue && impl &&
            typeValue.getValue().equals_insensitive("fifo"))
          bindImpl = impl.getValue().str();
      }

  std::map<int64_t, SmallVector<const ReachedCall *>> byMember;
  for (const ReachedCall &candidateValue : calls)
    byMember[candidateValue.member ? int64_t(*candidateValue.member) : -1]
        .push_back(&candidateValue);

  bool memberPragmaResolved = !structMembers || byMember.size() == 1;
  if (pragmaDepth && !memberPragmaResolved)
    rec.note += "stream pragma on '" + pragmaVariable +
                "' not resolved to a struct member (the IR has no member "
                "names): every member uses its template depth; ";
  if (structMembers && byMember.count(-1))
    rec.note += "a handle reached without a member index: counted as one "
                "FIFO per element; ";

  for (auto &[memberKey, memberCalls] : byMember) {
    FifoGroup globalOp;
    if (memberKey >= 0)
      globalOp.member = static_cast<unsigned>(memberKey);

    std::set<SmallVector<int64_t, 2>> reachedElements;
    bool allConstant = true;
    for (const ReachedCall *candidateValue : memberCalls) {
      if (isConstructor(candidateValue->tmpl.method))
        continue;
      if (candidateValue->element)
        reachedElements.insert(*candidateValue->element);
      else
        allConstant = false;
    }
    int64_t perMember = handlesPerMember(elt, globalOp.member);
    if (allConstant && !reachedElements.empty() &&
        static_cast<int64_t>(reachedElements.size()) < elements) {
      globalOp.count = static_cast<int64_t>(reachedElements.size());
      globalOp.countSource = std::to_string(globalOp.count) + " of " +
                             std::to_string(elements) +
                             " elements read or written (constant indices)";
    } else {
      globalOp.count = elements;
      globalOp.countSource = "every element";
    }
    if (perMember > 1) {
      globalOp.count *= perMember;
      globalOp.countSource +=
          " x " + std::to_string(perMember) + " handles of the member array";
    }

    std::optional<int64_t> tmplDepth;
    std::string elementMangled;
    for (const ReachedCall *candidateValue : memberCalls)
      if (candidateValue->tmpl.depth) {
        tmplDepth = candidateValue->tmpl.depth;
        elementMangled = candidateValue->tmpl.elementMangled;
        break;
      }
    if (pragmaDepth && memberPragmaResolved) {
      globalOp.depth = *pragmaDepth;
      globalOp.depthSource = "pragma";
    } else if (tmplDepth && *tmplDepth > 0) {
      globalOp.depth = *tmplDepth;
      globalOp.depthSource = "template";
    } else {
      globalOp.depth = streamRules().defaultDepth;
      globalOp.depthSource =
          tmplDepth ? "default" : "default (template unparsed)";
    }

    if (auto bits = mangledElementBits(elementMangled)) {
      globalOp.bits = *bits;
      globalOp.bitsSource = "mangled " + elementMangled;
    } else {
      for (const ReachedCall *candidateValue : memberCalls) {
        if (isConstructor(candidateValue->tmpl.method))
          continue;
        if (Type typeValue =
                ioType(candidateValue->call, candidateValue->tmpl.method)) {
          if (unsigned buildPoint = packedTypeBits(typeValue)) {
            globalOp.bits = buildPoint;
            globalOp.bitsSource = "ir " + typeString(typeValue);
            break;
          }
        }
      }
      if (globalOp.bits == 0)
        globalOp.bitsSource = "unknown";
    }
    bool used =
        llvm::any_of(memberCalls, [](const ReachedCall *candidateValue) {
          return !isConstructor(candidateValue->tmpl.method);
        });
    if (!used) {
      globalOp.reason =
          "constructed but never read or written: no FIFO (an unused "
          "channel is removed; unconfirmed), 0 BRAM";
    } else {
      FifoPrice portValue =
          priceFifo(globalOp.depth, globalOp.bits, bindImpl, bandBlocks);
      globalOp.bramEach = portValue.bram;
      globalOp.reason = portValue.reason;
      rec.fifos += globalOp.count;
      rec.bram += static_cast<unsigned>(globalOp.count) * globalOp.bramEach;
    }
    rec.groups.push_back(std::move(globalOp));
  }
  if (!rec.note.empty() && StringRef(rec.note).ends_with("; "))
    rec.note.resize(rec.note.size() - 2);
  return rec;
}
