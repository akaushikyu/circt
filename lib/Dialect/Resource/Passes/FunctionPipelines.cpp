

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/FunctionPipelines.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Matchers.h"
#include "mlir/Interfaces/ControlFlowInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Demangle/Demangle.h"

#include <cstdlib>

using namespace mlir;

namespace circt::hls_analysis {

namespace {

/// The value an op that only re-expresses a memory address derives from (a
/// view, a cast, the polygeist pointer round trip, an LLVM address
/// computation), or null.
Value addressSource(Operation *def) {
  if (auto view = dyn_cast<ViewLikeOpInterface>(def))
    return view.getViewSource();
  StringRef name = def->getName().getStringRef();
  if (def->getNumOperands() > 0 &&
      (isa<memref::CastOp>(def) || name == "polygeist.subindex" ||
       name == "polygeist.pointer2memref" ||
       name == "polygeist.memref2pointer" || name == "llvm.getelementptr"))
    return def->getOperand(0);
  return Value();
}

/// Whether a value derived from the argument `arg` is carried around a loop
/// or escapes: a pointer walk (`*p++`) makes the pointer an array, and a
/// stored or returned pointer cannot be followed.
bool derivedPointerEscapes(Value arg) {
  SmallVector<Value> work{arg};
  llvm::SmallPtrSet<Operation *, 16> seen;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (user->hasTrait<OpTrait::IsTerminator>() || user->getNumRegions() > 0)
        return true;
      if (addressSource(user) == valueHandle) {
        if (seen.insert(user).second)
          for (Value resultValue : user->getResults())
            work.push_back(resultValue);
        continue;
      }
      StringRef name = user->getName().getStringRef();
      if (name == "llvm.store" && use.getOperandNumber() == 0)
        return true;
    }
  }
  return false;
}

/// Whether the C++ class name `name` belongs to a library namespace whose
/// objects are channels or interfaces, never a user aggregate (hls::stream,
/// tapa::istream / async_mmap, the standard library). Replaces a substring
/// test on "stream" / "tapa" / "mmap" that also matched user structs such as
/// `upstream_cfg` (W9 round 19 review defect 2).
bool isLibraryClass(StringRef name) {
  name = name.trim();
  name.consume_front("const ");
  name.consume_front("volatile ");
  name.consume_front("::");
  return name.starts_with("hls::") || name.starts_with("tapa::") ||
         name.starts_with("std::");
}

/// The C++ name of an identified LLVM struct as cgeist names it
/// (`[opaque@polygeist@mlir@]class.<name>[.<n>]` or `struct.<name>`).
StringRef identifiedClassName(LLVM::LLVMStructType st) {
  StringRef elementCount = st.getName();
  size_t at = elementCount.rfind('@');
  if (at != StringRef::npos)
    elementCount = elementCount.drop_front(at + 1);
  if (!elementCount.consume_front("class.") &&
      !elementCount.consume_front("struct."))
    elementCount.consume_front("union.");
  return elementCount;
}

/// Whether parameter `index` of the C++ function `fn`, by its Itanium
/// mangled symbol, is a pointer to one user class (`plain_cfg*`), not to a
/// builtin type, an array (`int (*) [2]`) or a library class. False for a
/// symbol that does not demangle (a C function) or whose parameter count
/// differs from the function's. cgeist lowers a pointer to a struct whose
/// members all have one type as `memref<?xNxT>`, like a pointer to an array
/// of N elements; the declared parameter type tells them apart.
bool mangledParamIsClassPointer(func::FuncOp fn, unsigned index) {
  StringRef symbolName = fn.getSymName();
  if (!symbolName.starts_with("_Z"))
    return false;

  std::string mangled = symbolName.str();
  llvm::ItaniumPartialDemangler dimensionIndex;
  if (dimensionIndex.partialDemangle(mangled.c_str()) ||
      !dimensionIndex.isFunction())
    return false;
  size_t size = 0;
  char *buf = dimensionIndex.getFunctionParameters(nullptr, &size);
  if (!buf)
    return false;
  std::string params(buf);
  std::free(buf);
  StringRef list = StringRef(params).trim();
  if (!list.consume_front("(") || !list.consume_back(")"))
    return false;
  SmallVector<StringRef> parts;
  int depth = 0;
  size_t start = 0;
  for (size_t loopIndex = 0; loopIndex < list.size(); ++loopIndex) {
    char ch = list[loopIndex];
    if (ch == '<' || ch == '(' || ch == '[')
      ++depth;
    else if (ch == '>' || ch == ')' || ch == ']')
      --depth;
    else if (ch == ',' && depth == 0) {
      parts.push_back(list.slice(start, loopIndex).trim());
      start = loopIndex + 1;
    }
  }
  if (!list.trim().empty())
    parts.push_back(list.drop_front(start).trim());
  if (parts.size() != fn.getNumArguments() || index >= parts.size())
    return false;
  StringRef portValue = parts[index];
  if (!portValue.consume_back("*") || portValue.ends_with("*"))
    return false;
  portValue = portValue.trim();
  portValue.consume_back(" const");
  portValue.consume_back(" volatile");
  if (portValue.empty() ||
      portValue.find_first_of("()[]&") != StringRef::npos ||
      isLibraryClass(portValue))
    return false;
  static const llvm::StringSet<> builtins = {"void",
                                             "bool",
                                             "char",
                                             "signed char",
                                             "unsigned char",
                                             "wchar_t",
                                             "char8_t",
                                             "char16_t",
                                             "char32_t",
                                             "short",
                                             "unsigned short",
                                             "int",
                                             "unsigned int",
                                             "long",
                                             "unsigned long",
                                             "long long",
                                             "unsigned long long",
                                             "__int128",
                                             "unsigned __int128",
                                             "float",
                                             "double",
                                             "long double",
                                             "_Float16",
                                             "__bf16",
                                             "half",
                                             "decltype(nullptr)"};
  StringRef base = portValue;
  base.consume_front("const ");
  base.consume_front("volatile ");
  return !builtins.contains(base) && !base.starts_with("_BitInt(") &&
         !base.starts_with("unsigned _BitInt(");
}

/// Whether every direct load and store of `arg` (through memref.cast) and
/// every llvm.getelementptr over its struct type selects element 0 of the
/// pointer's first dimension: a pointer to one object, not an array of them.
bool selectsOnlyFirstElement(BlockArgument arg, Type elementType) {
  auto isZero = [](Value valueHandle) {
    llvm::APInt candidateValue;
    return matchPattern(valueHandle, m_ConstantInt(&candidateValue)) &&
           candidateValue.isZero();
  };
  SmallVector<Value> work{arg};
  llvm::SmallPtrSet<Operation *, 16> seen;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (!seen.insert(user).second)
        continue;
      if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(user)) {
        auto entryValue = dyn_cast<AffineConstantExpr>(
            lowerIndex.getAffineMap().getResult(0));
        if (!entryValue || entryValue.getValue() != 0)
          return false;
      } else if (auto stringValue = dyn_cast<affine::AffineStoreOp>(user)) {
        if (use.getOperandNumber() == 0)
          continue;
        auto entryValue = dyn_cast<AffineConstantExpr>(
            stringValue.getAffineMap().getResult(0));
        if (!entryValue || entryValue.getValue() != 0)
          return false;
      } else if (auto lowerIndex = dyn_cast<memref::LoadOp>(user)) {
        if (lowerIndex.getIndices().empty() ||
            !isZero(lowerIndex.getIndices()[0]))
          return false;
      } else if (auto stringValue = dyn_cast<memref::StoreOp>(user)) {
        if (stringValue.getIndices().empty() ||
            !isZero(stringValue.getIndices()[0]))
          return false;
      } else if (isa<memref::CastOp>(user) ||
                 user->getName().getStringRef() == "polygeist.memref2pointer") {
        for (Value resultValue : user->getResults())
          work.push_back(resultValue);
      } else if (auto gep = dyn_cast<LLVM::GEPOp>(user)) {
        if (gep.getElemType() != elementType)
          continue;
        auto first = gep.getIndices()[0];
        if (auto attr = llvm::dyn_cast_if_present<IntegerAttr>(first)) {
          if (attr.getInt() != 0)
            return false;
        } else if (!isZero(llvm::cast<Value>(first))) {
          return false;
        }
      }
    }
  }
  return true;
}

/// Whether the top-function argument `arg` is an aggregated struct pointer
/// (N147): a pointer to one struct without a memory or stream interface,
/// not a library (TAPA / hls::stream) object, never walked, never indexed
/// past its first element. cgeist gives it the type
/// `memref<?x!llvm.struct<...>>`, or `memref<?xNxT>` when the members all
/// have one type; that form is accepted when the top's mangled name
/// declares the parameter a pointer to a class (W9 round 19 review defect 2:
/// kernels w9r19r_rv_s / rv_s2, one C semantics, two lowerings).
bool qualifiesAsAggregatedScalar(func::FuncOp fn, BlockArgument arg) {
  auto type = dyn_cast<MemRefType>(arg.getType());
  if (!type || type.getRank() < 1 || !type.isDynamicDim(0))
    return false;
  Type selected;
  if (type.getRank() == 1) {
    auto st = dyn_cast<LLVM::LLVMStructType>(type.getElementType());
    if (!st || st.isOpaque())
      return false;
    if (st.isIdentified() && isLibraryClass(identifiedClassName(st)))
      return false;
    selected = st;
  } else {
    if (type.getRank() != 2 || type.isDynamicDim(1) ||
        !type.getElementType().isIntOrFloat() ||
        !mangledParamIsClassPointer(fn, arg.getArgNumber()))
      return false;
  }
  if (!selectsOnlyFirstElement(arg, selected))
    return false;
  if (auto iface =
          fn.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(), "hls.interface"))
    for (Attribute a : iface)
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(a))
        if (auto mode = dimensionIndex.getAs<StringAttr>("mode")) {
          StringRef memoryOp = mode.getValue();
          if (memoryOp != "ap_none" && memoryOp != "ap_ovld" &&
              memoryOp != "ap_vld" && memoryOp != "ap_hs" &&
              memoryOp != "ap_ack" && memoryOp != "s_axilite")
            return false;
        }
  return !derivedPointerEscapes(arg);
}

/// Whether `op` holds a loop.
bool isLoopOp(Operation *op) {
  return isa<LoopLikeOpInterface, loopschedule::LoopSchedulePipelineOp>(op);
}

/// The memref an access op reads or writes (null for any other op). An LLVM
/// load or store counts when its address derives from a memref (a struct
/// member reached through polygeist.memref2pointer and llvm.getelementptr).
Value accessedMemref(Operation *op) {
  StringRef name = op->getName().getStringRef();
  if ((name == "llvm.load" && op->getNumOperands() >= 1) ||
      (name == "llvm.store" && op->getNumOperands() >= 2)) {
    Value addr = op->getOperand(name == "llvm.load" ? 0 : 1);
    for (unsigned guard = 0; addr && guard < 64; ++guard) {
      if (isa<MemRefType>(addr.getType()))
        return addr;
      Operation *def = addr.getDefiningOp();
      if (!def)
        return Value();
      addr = addressSource(def);
    }
    return Value();
  }
  if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
    return stringValue.getMemRef();
  if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    return stringValue.getMemRef();
  return Value();
}

/// Whether an access of `mem` is an access of a memory in Vitis' module
/// structure (N143): not a one-element variable (a scalar cgeist keeps in
/// memory because its address is taken), not registers. An aggregated
/// struct pointer (N147) counts: a read or write of its members outside the
/// pipelined loop outlines the loop like a memory access (W9 round 19
/// review defect 1; kernels w9r19r_rv_s2_plain_cfg `c->a = c->b * 3 + 1`,
/// w9r19f_fx_s2_rd / fx_s_rd a returned `c->b * 3 + 1`: `top_Pipeline_I`
/// and two g instances, 2 BRAM), although it limits no function pipeline's
/// II and is no array argument (N144 / N145).
bool isMemoryOperand(Value mem) {
  StorageRoot root = storageRoot(mem);
  Operation *def = root.global  ? root.global
                   : root.value ? root.value.getDefiningOp()
                                : nullptr;
  if (def && def->hasAttr(kRegistersAttrName))
    return false;
  if (auto typeValue = dyn_cast<MemRefType>(mem.getType()))
    if (typeValue.hasStaticShape() && typeValue.getNumElements() == 1 && def &&
        isa<memref::AllocaOp, memref::AllocOp>(def))
      return false;
  return true;
}

/// The II a pipelined loop's pragma asks for: its II, 1 when it names none
/// or the loop was pipelined automatically (Vitis: Target II = NA, function
/// pipelines of aes_table's automatically pipelined ecb2 reach II 1).
unsigned targetII(Operation *pipeline) {
  if (auto arr = pipeline->getAttrOfType<ArrayAttr>(kLoopPipelineAttr))
    if (!arr.empty())
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(arr[0]))
        if (!dimensionIndex.get("source"))
          if (auto ii = dimensionIndex.getAs<IntegerAttr>("II");
              ii && ii.getInt() > 1)
            return static_cast<unsigned>(ii.getInt());
  return 1;
}

} // namespace

bool AggregatedScalars::contains(Value mem) const {
  if (roots.empty())
    return false;
  for (unsigned guard = 0; mem && guard < 64; ++guard) {
    if (roots.contains(mem))
      return true;
    Operation *def = mem.getDefiningOp();
    if (!def)
      return false;
    mem = addressSource(def);
  }
  return false;
}

AggregatedScalars computeAggregatedScalars(ModuleOp module) {
  AggregatedScalars out;
  if (!circt::hlsest::Config::get().tool.hls.structs.topPointerScalar)
    return out;
  llvm::DenseMap<Operation *, SmallVector<CallOpInterface>> callers;
  module.walk([&](CallOpInterface callSite) {
    if (func::FuncOp callee = resolveDefinedCallee(callSite))
      callers[callee.getOperation()].push_back(callSite);
  });
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal() || callers.count(fn.getOperation()))
      return;
    for (BlockArgument arg : fn.getArguments())
      if (qualifiesAsAggregatedScalar(fn, arg))
        out.roots.insert(arg);
  });
  if (out.roots.empty())
    return out;

  for (bool changed = true; changed;) {
    changed = false;
    for (auto &[fnOp, calls] : callers) {
      auto fn = cast<func::FuncOp>(fnOp);
      for (BlockArgument arg : fn.getArguments()) {
        if (!isa<MemRefType>(arg.getType()) || out.roots.contains(arg))
          continue;
        unsigned elementCount = arg.getArgNumber();
        if (llvm::all_of(calls, [&](CallOpInterface callSite) {
              return elementCount < callSite.getArgOperands().size() &&
                     out.contains(callSite.getArgOperands()[elementCount]);
            })) {
          out.roots.insert(arg);
          changed = true;
        }
      }
    }
  }
  return out;
}

bool isOutlinedPipeline(Operation *pipeline) {
  auto fn = pipeline->getParentOfType<func::FuncOp>();
  if (!fn)
    return false;
  bool outlined = false;
  fn.walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (op == pipeline)
      return WalkResult::skip();
    if (isLoopOp(op)) {
      outlined = true;
      return WalkResult::interrupt();
    }
    if (Value mem = accessedMemref(op))
      if (isMemoryOperand(mem)) {
        outlined = true;
        return WalkResult::interrupt();
      }
    return WalkResult::advance();
  });
  return outlined;
}

Operation *outlinedPipelineAround(Operation *op, func::FuncOp parent) {
  Operation *found = nullptr;
  for (Operation *portValue = op->getParentOp();
       portValue && portValue != parent.getOperation();
       portValue = portValue->getParentOp())
    if (isa<loopschedule::LoopSchedulePipelineOp>(portValue) &&
        isOutlinedPipeline(portValue))
      found = portValue;
  return found;
}

FunctionPipelineModel computeFunctionPipelines(
    ModuleOp module, const AggregatedScalars &scalars,
    llvm::function_ref<bool(func::FuncOp)> inScope,
    llvm::function_ref<bool(Operation *)> isReadOnlyGlobal) {
  FunctionPipelineModel model;
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.rom.functionPipelineReads)
    return model;
  SymbolTableCollection symbolTable;

  auto ignore = [&](Operation *access, Value mem) {
    if (scalars.contains(mem))
      return true;
    StorageRoot root = storageRoot(mem);
    if (root.global && (root.global->hasAttr(kRegistersAttrName) ||
                        isReadOnlyGlobal(root.global)))
      return true;
    if (root.value)
      if (Operation *def = root.value.getDefiningOp())
        if (def->hasAttr(kRegistersAttrName))
          return true;
    return isa<affine::AffineLoadOp, memref::LoadOp>(access) &&
           access->use_empty();
  };
  llvm::DenseMap<Operation *, bool> loopFree;
  auto isLoopFree = [&](func::FuncOp fn) {
    auto [it, inserted] = loopFree.try_emplace(fn.getOperation(), true);
    if (inserted)
      fn.walk([&](Operation *op) {
        if (isLoopOp(op)) {
          it->second = false;
          return WalkResult::interrupt();
        }
        return WalkResult::advance();
      });
    return it->second;
  };
  llvm::DenseMap<Operation *, unsigned> ownII;
  SmallVector<CallOpInterface> calls;
  module.walk([&](CallOpInterface callSite) {
    func::FuncOp callee = resolveDefinedCallee(callSite);
    auto parent = callSite->getParentOfType<func::FuncOp>();
    if (!callee || !parent || !isKeptCallee(callee) ||
        (inScope && (!inScope(callee) || !inScope(parent))) ||
        !isLoopFree(callee))
      return;
    calls.push_back(callSite);
  });
  for (bool changed = true; changed;) {
    changed = false;
    for (CallOpInterface callSite : calls) {
      func::FuncOp callee = resolveDefinedCallee(callSite);
      auto parent = callSite->getParentOfType<func::FuncOp>();
      std::optional<unsigned> target;
      if (auto pipeline =
              callSite->getParentOfType<loopschedule::LoopSchedulePipelineOp>())
        target = targetII(pipeline);
      else if (std::optional<unsigned> portValue = model.iiOf(parent))
        target = *portValue;
      if (!target)
        continue;
      auto [own, inserted] = ownII.try_emplace(callee.getOperation(), 1u);
      if (inserted) {
        SmallPtrSet<Operation *, 8> stack;
        own->second = estimateCallOccupancy(callee, symbolTable, stack, ignore);
      }
      unsigned ii = std::max(*target, own->second);
      auto [it, fresh] = model.ii.try_emplace(callee.getOperation(), ii);
      if (fresh || ii > it->second) {
        it->second = ii;
        changed = true;
      }
    }
  }
  return model;
}

} // namespace circt::hls_analysis
