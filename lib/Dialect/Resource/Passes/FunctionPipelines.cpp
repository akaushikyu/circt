//===- FunctionPipelines.cpp - kept callees of pipelined loops ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See FunctionPipelines.h. Evidence: VITIS_NOTES N143 - N145, N147 (kernels
// ~/hls-est-work/exp-src/w9r19p/{fp,ol,iu}/, runs experiments/w9r19p_*).
//
//===----------------------------------------------------------------------===//

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
    Value v = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (user->hasTrait<OpTrait::IsTerminator>() ||
          user->getNumRegions() > 0)
        return true; // yielded, branched, returned, or a loop's init value
      if (addressSource(user) == v) {
        if (seen.insert(user).second)
          for (Value r : user->getResults())
            work.push_back(r);
        continue;
      }
      StringRef name = user->getName().getStringRef();
      if (name == "llvm.store" && use.getOperandNumber() == 0)
        return true; // the pointer itself is stored
      // Loads, stores through it, and calls are uses of the memory.
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
  StringRef n = st.getName();
  size_t at = n.rfind('@');
  if (at != StringRef::npos)
    n = n.drop_front(at + 1);
  if (!n.consume_front("class.") && !n.consume_front("struct."))
    n.consume_front("union.");
  return n;
}

/// Whether parameter `index` of the C++ function `fn`, by its Itanium
/// mangled symbol, is a pointer to one user class (`plain_cfg*`), not to a
/// builtin type, an array (`int (*) [2]`) or a library class. False for a
/// symbol that does not demangle (a C function) or whose parameter count
/// differs from the function's. cgeist lowers a pointer to a struct whose
/// members all have one type as `memref<?xNxT>`, like a pointer to an array
/// of N elements; the declared parameter type tells them apart.
bool mangledParamIsClassPointer(func::FuncOp fn, unsigned index) {
  StringRef sym = fn.getSymName();
  if (!sym.starts_with("_Z"))
    return false;
  // The demangler's nodes point into the mangled string, so it must outlive
  // every query below (a temporary here made the parameter text read freed
  // memory: lit w9r19f_n147_homogeneous_struct gave 4 or 1 from run to run).
  std::string mangled = sym.str();
  llvm::ItaniumPartialDemangler d;
  if (d.partialDemangle(mangled.c_str()) || !d.isFunction())
    return false;
  size_t size = 0;
  char *buf = d.getFunctionParameters(nullptr, &size);
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
  for (size_t i = 0; i < list.size(); ++i) {
    char ch = list[i];
    if (ch == '<' || ch == '(' || ch == '[')
      ++depth;
    else if (ch == '>' || ch == ')' || ch == ']')
      --depth;
    else if (ch == ',' && depth == 0) {
      parts.push_back(list.slice(start, i).trim());
      start = i + 1;
    }
  }
  if (!list.trim().empty())
    parts.push_back(list.drop_front(start).trim());
  if (parts.size() != fn.getNumArguments() || index >= parts.size())
    return false;
  StringRef p = parts[index];
  if (!p.consume_back("*") || p.ends_with("*"))
    return false;
  p = p.trim();
  p.consume_back(" const");
  p.consume_back(" volatile");
  if (p.empty() || p.find_first_of("()[]&") != StringRef::npos ||
      isLibraryClass(p))
    return false;
  static const llvm::StringSet<> builtins = {
      "void", "bool", "char", "signed char", "unsigned char", "wchar_t",
      "char8_t", "char16_t", "char32_t", "short", "unsigned short", "int",
      "unsigned int", "long", "unsigned long", "long long",
      "unsigned long long", "__int128", "unsigned __int128", "float",
      "double", "long double", "_Float16", "__bf16", "half",
      "decltype(nullptr)"};
  StringRef base = p;
  base.consume_front("const ");
  base.consume_front("volatile ");
  return !builtins.contains(base) && !base.starts_with("_BitInt(") &&
         !base.starts_with("unsigned _BitInt(");
}

/// Whether every direct load and store of `arg` (through memref.cast) and
/// every llvm.getelementptr over its struct type selects element 0 of the
/// pointer's first dimension: a pointer to one object, not an array of them.
bool selectsOnlyFirstElement(BlockArgument arg, Type elementType) {
  auto isZero = [](Value v) {
    llvm::APInt c;
    return matchPattern(v, m_ConstantInt(&c)) && c.isZero();
  };
  SmallVector<Value> work{arg};
  llvm::SmallPtrSet<Operation *, 16> seen;
  while (!work.empty()) {
    Value v = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (!seen.insert(user).second)
        continue;
      if (auto l = dyn_cast<affine::AffineLoadOp>(user)) {
        auto e = dyn_cast<AffineConstantExpr>(l.getAffineMap().getResult(0));
        if (!e || e.getValue() != 0)
          return false;
      } else if (auto s = dyn_cast<affine::AffineStoreOp>(user)) {
        if (use.getOperandNumber() == 0)
          continue; // the memref is the stored value: not an access of it
        auto e = dyn_cast<AffineConstantExpr>(s.getAffineMap().getResult(0));
        if (!e || e.getValue() != 0)
          return false;
      } else if (auto l = dyn_cast<memref::LoadOp>(user)) {
        if (l.getIndices().empty() || !isZero(l.getIndices()[0]))
          return false;
      } else if (auto s = dyn_cast<memref::StoreOp>(user)) {
        if (s.getIndices().empty() || !isZero(s.getIndices()[0]))
          return false;
      } else if (isa<memref::CastOp>(user) ||
                 user->getName().getStringRef() ==
                     "polygeist.memref2pointer") {
        for (Value r : user->getResults())
          work.push_back(r);
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
  if (auto iface = fn.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(),
                                                  "hls.interface"))
    for (Attribute a : iface)
      if (auto d = dyn_cast<DictionaryAttr>(a))
        if (auto mode = d.getAs<StringAttr>("mode")) {
          StringRef m = mode.getValue();
          if (m != "ap_none" && m != "ap_ovld" && m != "ap_vld" &&
              m != "ap_hs" && m != "ap_ack" && m != "s_axilite")
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
  if (auto l = dyn_cast<affine::AffineLoadOp>(op))
    return l.getMemRef();
  if (auto s = dyn_cast<affine::AffineStoreOp>(op))
    return s.getMemRef();
  if (auto l = dyn_cast<memref::LoadOp>(op))
    return l.getMemRef();
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return s.getMemRef();
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
  Operation *def = root.global ? root.global
                   : root.value ? root.value.getDefiningOp()
                                : nullptr;
  if (def && def->hasAttr(kRegistersAttrName))
    return false;
  if (auto t = dyn_cast<MemRefType>(mem.getType()))
    if (t.hasStaticShape() && t.getNumElements() == 1 && def &&
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
      if (auto d = dyn_cast<DictionaryAttr>(arr[0]))
        if (!d.get("source"))
          if (auto ii = d.getAs<IntegerAttr>("II"); ii && ii.getInt() > 1)
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
  module.walk([&](CallOpInterface call) {
    if (func::FuncOp callee = resolveDefinedCallee(call))
      callers[callee.getOperation()].push_back(call);
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
  // Parameters every call site binds to one, to a fixpoint (a context
  // passed down through two kept functions).
  for (bool changed = true; changed;) {
    changed = false;
    for (auto &[fnOp, calls] : callers) {
      auto fn = cast<func::FuncOp>(fnOp);
      for (BlockArgument arg : fn.getArguments()) {
        if (!isa<MemRefType>(arg.getType()) || out.roots.contains(arg))
          continue;
        unsigned n = arg.getArgNumber();
        if (llvm::all_of(calls, [&](CallOpInterface call) {
              return n < call.getArgOperands().size() &&
                     out.contains(call.getArgOperands()[n]);
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
  for (Operation *p = op->getParentOp(); p && p != parent.getOperation();
       p = p->getParentOp())
    if (isa<loopschedule::LoopSchedulePipelineOp>(p) &&
        isOutlinedPipeline(p))
      found = p;
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
  // A memory that limits a function pipeline's II: not a ROM (replicated
  // instead), not registers, not an aggregated scalar; an unused load is
  // removed.
  auto ignore = [&](Operation *access, Value mem) {
    if (scalars.contains(mem))
      return true;
    StorageRoot root = storageRoot(mem);
    if (root.global &&
        (root.global->hasAttr(kRegistersAttrName) ||
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
  module.walk([&](CallOpInterface call) {
    func::FuncOp callee = resolveDefinedCallee(call);
    auto parent = call->getParentOfType<func::FuncOp>();
    if (!callee || !parent || !isKeptCallee(callee) ||
        (inScope && (!inScope(callee) || !inScope(parent))) ||
        !isLoopFree(callee))
      return;
    calls.push_back(call);
  });
  for (bool changed = true; changed;) {
    changed = false;
    for (CallOpInterface call : calls) {
      func::FuncOp callee = resolveDefinedCallee(call);
      auto parent = call->getParentOfType<func::FuncOp>();
      std::optional<unsigned> target;
      if (auto pipeline =
              call->getParentOfType<loopschedule::LoopSchedulePipelineOp>())
        target = targetII(pipeline);
      else if (std::optional<unsigned> p = model.iiOf(parent))
        target = *p;
      if (!target)
        continue;
      auto [own, inserted] = ownII.try_emplace(callee.getOperation(), 1u);
      if (inserted) {
        SmallPtrSet<Operation *, 8> stack;
        own->second =
            estimateCallOccupancy(callee, symbolTable, stack, ignore);
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
