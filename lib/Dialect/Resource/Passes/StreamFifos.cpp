

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/StreamFifos.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"

#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Regex.h"

#include <map>
#include <set>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

/// Default depth of a stream without a depth pragma or template argument.
constexpr int64_t kDefaultStreamDepth = 2;
/// FIFOs this shallow are shift registers at any width.
constexpr int64_t kShiftRegisterMaxDepth = 2;
/// FIFOs of at most this many bits (depth x width) are shift registers.
constexpr int64_t kShiftRegisterMaxBits = 1024;

struct Demangler {
  StringRef stringValue;
  size_t loopIndex = 0;

  bool atEnd() const { return loopIndex >= stringValue.size(); }
  char peek(size_t ahead = 0) const {
    return loopIndex + ahead < stringValue.size()
               ? stringValue[loopIndex + ahead]
               : '\0';
  }

  bool number(int64_t &value) {
    bool negative = false;
    if (peek() == 'n') {
      negative = true;
      ++loopIndex;
    }
    size_t start = loopIndex;
    while (!atEnd() && llvm::isDigit(peek()))
      ++loopIndex;
    if (start == loopIndex)
      return false;
    if (stringValue.substr(start, loopIndex - start).getAsInteger(10, value))
      return false;
    if (negative)
      value = -value;
    return true;
  }

  bool sourceName() {
    int64_t len;
    if (!number(len) || len <= 0 || loopIndex + len > stringValue.size())
      return false;
    loopIndex += len;
    return true;
  }

  bool substitution() {

    ++loopIndex;
    if (peek() == 't') {
      ++loopIndex;
      return sourceName();
    }
    if (StringRef("absiod").contains(peek())) {
      ++loopIndex;
      return true;
    }
    while (!atEnd() && peek() != '_' &&
           (llvm::isDigit(peek()) || llvm::isUpper(peek())))
      ++loopIndex;
    if (peek() != '_')
      return false;
    ++loopIndex;
    return true;
  }

  bool templateArgs() {
    ++loopIndex;
    while (!atEnd() && peek() != 'E')
      if (!templateArg())
        return false;
    if (peek() != 'E')
      return false;
    ++loopIndex;
    return true;
  }

  bool literal(int64_t *value = nullptr) {
    ++loopIndex;
    if (peek() == '_')
      return false;
    if (!type())
      return false;
    int64_t valueHandle;
    if (!number(valueHandle))
      return false;
    if (peek() != 'E')
      return false;
    ++loopIndex;
    if (value)
      *value = valueHandle;
    return true;
  }

  bool templateArg() {
    if (peek() == 'L')
      return literal();
    if (peek() == 'J') {
      ++loopIndex;
      while (!atEnd() && peek() != 'E')
        if (!templateArg())
          return false;
      if (peek() != 'E')
        return false;
      ++loopIndex;
      return true;
    }
    return type();
  }

  bool nestedName() {
    ++loopIndex;
    while (StringRef("rVK").contains(peek()) && !atEnd())
      ++loopIndex;
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
    ++loopIndex;
    return true;
  }

  bool type() {
    if (atEnd())
      return false;
    char candidateValue = peek();
    if (StringRef("rVKPRO").contains(candidateValue)) {
      ++loopIndex;
      return type();
    }
    if (StringRef("vwbcahstijlmxynofdegz").contains(candidateValue)) {
      ++loopIndex;
      return true;
    }
    if (candidateValue == 'D') {
      loopIndex += 2;
      return true;
    }
    if (candidateValue == 'A') {
      ++loopIndex;
      int64_t elementCount;
      if (!number(elementCount) || peek() != '_')
        return false;
      ++loopIndex;
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
  Demangler demangler{rest};
  if (!demangler.type())
    return typeValue;
  typeValue.elementMangled = rest.substr(0, demangler.loopIndex).str();
  if (demangler.peek() == 'L') {
    int64_t depth;
    if (!demangler.literal(&depth))
      return typeValue;
    typeValue.depth = depth;
  }
  if (demangler.peek() != 'E')
    return typeValue;
  ++demangler.loopIndex;
  typeValue.method = rest.substr(demangler.loopIndex).str();
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
  if (impl == "bram") {
    portValue.bram = static_cast<unsigned>(bandBlocks(depth, bits));
    portValue.reason = "bind_storage impl=bram: block RAM at any size, " +
                       geometry + ", depth bands at x18 -> " +
                       std::to_string(portValue.bram);
    return portValue;
  }
  if (depth <= kShiftRegisterMaxDepth) {
    portValue.reason = "depth " + std::to_string(depth) +
                       " <= " + std::to_string(kShiftRegisterMaxDepth) +
                       ": shift registers at any width, 0 BRAM";
    return portValue;
  }
  if (depth * static_cast<int64_t>(bits) <= kShiftRegisterMaxBits) {
    portValue.reason = geometry +
                       " <= " + std::to_string(kShiftRegisterMaxBits) +
                       ": shift registers, 0 BRAM";
    return portValue;
  }
  portValue.bram = static_cast<unsigned>(bandBlocks(depth, bits));
  portValue.reason = geometry + " > " + std::to_string(kShiftRegisterMaxBits) +
                     ": block RAM, depth bands at x18 (never x36) -> " +
                     std::to_string(portValue.bram);
  return portValue;
}

namespace {

/// One hls::stream method call reached from the storage.
struct ReachedCall {
  std::optional<unsigned> member;
  Operation *callSite;
  StreamTemplate tmpl;
};

bool isPointerCastLike(Operation *op) {
  StringRef name = op->getName().getStringRef();
  return name == "polygeist.subindex" || name == "polygeist.memref2pointer" ||
         name == "polygeist.pointer2memref" || name == "llvm.bitcast" ||
         name == "llvm.addrspacecast" || isa<memref::CastOp>(op);
}

/// Follows the handle values to the hls::stream methods they reach as the
/// object argument. `structMembers` says whether a constant member GEP
/// selects a struct member (the storage holds structs).
SmallVector<ReachedCall> traceHandles(ArrayRef<Value> roots,
                                      bool structMembers) {
  SmallVector<ReachedCall> out;
  using Item = std::pair<Value, std::optional<unsigned>>;
  SmallVector<Item> work;
  std::set<std::pair<void *, int64_t>> seen;
  auto push = [&](Value valueHandle, std::optional<unsigned> member) {
    if (seen.insert({valueHandle.getAsOpaquePointer(),
                     member ? int64_t(*member) : -1})
            .second)
      work.push_back({valueHandle, member});
  };
  for (Value resultValue : roots)
    push(resultValue, std::nullopt);
  while (!work.empty()) {
    auto [cur, member] = work.pop_back_val();
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto callSite = dyn_cast<CallOpInterface>(user)) {
        auto symbolName = llvm::dyn_cast_if_present<SymbolRefAttr>(
            callSite.getCallableForCallee());
        auto args = callSite.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned elementCount = use.getOperandNumber();
        if (elementCount < first || elementCount - first >= args.size())
          continue;
        unsigned argIndex = elementCount - first;
        if (symbolName) {
          if (auto typeValue =
                  parseStreamMethod(symbolName.getLeafReference().getValue())) {

            if (argIndex == 0)
              out.push_back({member, user, *typeValue});
            continue;
          }
        }
        auto callee =
            dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
        if (callee && !callee.isExternal() &&
            argIndex < callee.getNumArguments())
          push(callee.getArgument(argIndex), member);
        continue;
      }
      if (auto gep = dyn_cast<LLVM::GEPOp>(user)) {
        if (gep.getBase() != cur)
          continue;
        std::optional<unsigned> next = member;
        if (structMembers && !member) {
          ArrayRef<int32_t> indexValue = gep.getRawConstantIndices();
          if (indexValue.size() == 2 && indexValue[0] == 0 &&
              indexValue[1] != LLVM::GEPOp::kDynamicIndex)
            next = static_cast<unsigned>(indexValue[1]);
        }
        push(gep.getResult(), next);
        continue;
      }
      bool view = isPointerCastLike(user);
      if (auto valueHandle = dyn_cast<ViewLikeOpInterface>(user))
        view = view || valueHandle.getViewSource() == cur;
      if (!view)
        continue;

      for (Value resultValue : user->getResults())
        push(resultValue, member);
    }
  }
  return out;
}

/// The data type a read / write call moves, from its IR signature.
Type ioType(Operation *callSite, StringRef method) {
  if (method.starts_with("C") || method.starts_with("D"))
    return {};
  if (method.starts_with("4readEv") && callSite->getNumResults() == 1)
    return callSite->getResult(0).getType();
  bool dataByReference =
      method.starts_with("4read") || method.starts_with("5write") ||
      method.starts_with("7read_nb") || method.starts_with("8write_nb") ||
      method.starts_with("rs") || method.starts_with("ls");
  if (dataByReference && callSite->getNumOperands() >= 2)
    if (auto mt = dyn_cast<MemRefType>(callSite->getOperand(1).getType()))
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
  if (auto arrayValue = dyn_cast<memref::AllocaOp>(storage))
    type = arrayValue.getType();
  else if (auto arrayValue = dyn_cast<memref::AllocOp>(storage))
    type = arrayValue.getType();
  else if (auto globalOp = dyn_cast<memref::GlobalOp>(storage))
    type = globalOp.getType();
  if (!type)
    return std::nullopt;

  Type elt = type.getElementType();
  bool structMembers = isa<LLVM::LLVMStructType>(elt);
  if (!structMembers && !isa<IntegerType>(elt))
    return std::nullopt;

  SmallVector<ReachedCall> calls = traceHandles(sites, structMembers);
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
    for (Attribute arrayValue : arr)
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(arrayValue)) {
        if (auto depth = dimensionIndex.getAs<IntegerAttr>("depth")) {
          pragmaDepth = depth.getInt();
          if (auto valueHandle = dimensionIndex.getAs<StringAttr>("variable"))
            pragmaVariable = valueHandle.getValue().str();
        }
      }
  std::string bindImpl;
  if (auto arr = storage->getAttrOfType<ArrayAttr>("hls.bind_storage"))
    for (Attribute arrayValue : arr)
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(arrayValue)) {
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
    globalOp.count = elements;
    if (memberKey >= 0)
      globalOp.member = static_cast<unsigned>(memberKey);

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
      globalOp.depth = kDefaultStreamDepth;
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
                ioType(candidateValue->callSite, candidateValue->tmpl.method)) {
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
