//===- SplitStructMemrefs.cpp - one memory per field of a struct array ----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// --split-struct-memrefs
//
// Vitis disaggregates a local array of structs into one memory per field:
// `struct P { int a; short b; }; P s[1024];` becomes the two memories s_a
// (1024 x 32 bits, 2 BRAM_18K) and s_b (1024 x 16 bits, 1 BRAM_18K), each
// priced on its own (VITIS_NOTES.md N29, vitis_adhoc kernels w8b3_st1 /
// w8b3_st2 / w8b3_sp1). cgeist keeps such an array as one
// `memref<1024 x !llvm.struct<(i32, i16)>>` and reaches the fields through
// `polygeist.memref2pointer`, `llvm.getelementptr` and `llvm.load` /
// `llvm.store`, which hls-est cannot see as memory accesses.
//
// This pass replaces every memref.alloca / memref.alloc of LLVM struct
// elements whose uses it fully understands by one memref per scalar leaf of
// the struct (nested structs are flattened; an array member `T m[R][C]` adds
// its dimensions after the array's own), and rewrites every access as a
// memref.load / memref.store of the leaf memory. A memref it does not fully
// understand (a pointer passed to a call, compared, stored, converted back
// with pointer2memref, an array of structs inside the struct, ...) is left
// unchanged; its accesses then stay invisible as before.
//
// Address arithmetic. An address derived from the array is tracked as
//   (leading indices from row selects, a linear element offset over the
//    remaining dimensions, a constant byte offset inside the element, a
//    dynamic byte offset inside the element)
// using the LLVM x86-64 data layout cgeist compiles for (natural alignment).
// A dynamic byte offset that is not a proven multiple of the element size is
// taken to stay inside the array member it starts in, as C requires of
// pointer arithmetic within an array subobject.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/MathExtras.h"

#include <optional>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

//===----------------------------------------------------------------------===//
// Data layout (x86-64, natural alignment: what cgeist's byte offsets use)
//===----------------------------------------------------------------------===//

struct SizeAlign {
  int64_t size = 0;
  int64_t align = 1;
};

std::optional<SizeAlign> layoutOf(Type t) {
  if (auto it = dyn_cast<IntegerType>(t)) {
    int64_t bytes = std::max<int64_t>(1, (it.getWidth() + 7) / 8);
    // LLVM rounds an integer up to the next specified integer alignment
    // (i8 / i16 / i32 / i64 / i128 on x86-64).
    int64_t align = std::min<int64_t>(llvm::PowerOf2Ceil(bytes), 16);
    return SizeAlign{static_cast<int64_t>(llvm::alignTo(bytes, align)), align};
  }
  if (auto ft = dyn_cast<FloatType>(t)) {
    int64_t bytes = (ft.getWidth() + 7) / 8;
    int64_t align = std::min<int64_t>(llvm::PowerOf2Ceil(bytes), 16);
    return SizeAlign{static_cast<int64_t>(llvm::alignTo(bytes, align)), align};
  }
  if (isa<LLVM::LLVMPointerType>(t))
    return SizeAlign{8, 8};
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(t)) {
    auto e = layoutOf(at.getElementType());
    if (!e)
      return std::nullopt;
    return SizeAlign{e->size * static_cast<int64_t>(at.getNumElements()),
                     e->align};
  }
  if (auto st = dyn_cast<LLVM::LLVMStructType>(t)) {
    if (st.isOpaque())
      return std::nullopt;
    int64_t off = 0, align = 1;
    for (Type f : st.getBody()) {
      auto l = layoutOf(f);
      if (!l)
        return std::nullopt;
      int64_t fa = st.isPacked() ? 1 : l->align;
      off = llvm::alignTo(off, fa) + l->size;
      align = std::max(align, fa);
    }
    return SizeAlign{static_cast<int64_t>(llvm::alignTo(off, align)), align};
  }
  return std::nullopt;
}

/// Byte offset of field `index` of `st`.
int64_t fieldOffset(LLVM::LLVMStructType st, unsigned index) {
  int64_t off = 0;
  for (auto [i, f] : llvm::enumerate(st.getBody())) {
    auto l = *layoutOf(f);
    off = llvm::alignTo(off, st.isPacked() ? 1 : l.align);
    if (i == index)
      return off;
    off += l.size;
  }
  return off;
}

/// One scalar leaf of a struct: a scalar member, or an array member of
/// scalars (with its dimensions).
struct Leaf {
  int64_t offset = 0;              // bytes from the start of the element
  Type scalar;                     // element type of the leaf memory
  int64_t scalarSize = 0;          // bytes per scalar
  SmallVector<int64_t> dims;       // array member dimensions (empty: scalar)
  SmallVector<int64_t> path;       // llvm.extractvalue position
  int64_t bytes() const {
    int64_t n = scalarSize;
    for (int64_t d : dims)
      n *= d;
    return n;
  }
};

bool isScalar(Type t) {
  return isa<IntegerType, FloatType>(t);
}

/// Flattens `t` at byte `base` into leaves; false for anything that is not a
/// struct / array of scalars (pointers, arrays of structs).
bool collectLeaves(Type t, int64_t base, SmallVectorImpl<int64_t> &path,
                   SmallVectorImpl<Leaf> &out) {
  if (isScalar(t)) {
    Leaf l;
    l.offset = base;
    l.scalar = t;
    l.scalarSize = layoutOf(t)->size;
    l.path.assign(path.begin(), path.end());
    out.push_back(l);
    return true;
  }
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(t)) {
    SmallVector<int64_t> dims;
    Type e = t;
    while (auto a = dyn_cast<LLVM::LLVMArrayType>(e)) {
      dims.push_back(a.getNumElements());
      e = a.getElementType();
    }
    if (!isScalar(e))
      return false;
    Leaf l;
    l.offset = base;
    l.scalar = e;
    l.scalarSize = layoutOf(e)->size;
    l.dims = dims;
    l.path.assign(path.begin(), path.end());
    out.push_back(l);
    return true;
  }
  if (auto st = dyn_cast<LLVM::LLVMStructType>(t)) {
    if (st.isOpaque() || st.getBody().empty())
      return false;
    for (unsigned i = 0, e = st.getBody().size(); i < e; ++i) {
      path.push_back(i);
      bool ok = collectLeaves(st.getBody()[i], base + fieldOffset(st, i), path,
                              out);
      path.pop_back();
      if (!ok)
        return false;
    }
    return true;
  }
  return false;
}

//===----------------------------------------------------------------------===//
// Address tracking
//===----------------------------------------------------------------------===//

/// Where a memref / pointer derived from the struct array points.
struct Addr {
  SmallVector<Value> lead; // indices of leading dimensions fixed by row selects
  Value tail;              // element offset over the remaining dims (or null)
  int64_t byteConst = 0;   // constant byte offset inside the element
  Value byteDyn;           // dynamic byte offset inside the element (or null)
};

/// One access to rewrite: `op` reads or writes `leaf` (or, with leaf < 0,
/// the whole struct) at the given leaf-memory indices.
struct Access {
  Operation *op;
  int leaf; // -1: whole element
  SmallVector<Value> indices;
};

class StructSplitter {
public:
  StructSplitter(Operation *alloc, MemRefType type)
      : alloc(alloc), type(type),
        structType(cast<LLVM::LLVMStructType>(type.getElementType())) {}

  /// Analyses and, when every use is understood, rewrites. Returns true when
  /// the array was split.
  bool run();
  std::string reason;

private:
  Operation *alloc;
  MemRefType type;
  LLVM::LLVMStructType structType;
  int64_t elemSize = 0;
  SmallVector<Leaf> leaves;
  SmallVector<Operation *> created; // index arithmetic built while analysing
  SmallVector<Operation *> derived; // casts / views / pointers to erase
  SmallVector<Access> accesses;

  bool fail(const Twine &why) {
    if (reason.empty())
      reason = why.str();
    return false;
  }

  Value toIndex(OpBuilder &b, Location loc, Value v);
  Value add(OpBuilder &b, Location loc, Value a, Value c);
  Value mulConst(OpBuilder &b, Location loc, Value v, int64_t k);
  Value constIndex(OpBuilder &b, Location loc, int64_t k);
  /// The element stride (in elements) of dimension `dim` of the array.
  int64_t stride(unsigned dim) const;
  bool visitMemref(Value v, Addr a);
  bool visitPointer(Value v, Addr a);
  bool addGep(LLVM::GEPOp gep, Addr &a);
  bool addByteOffset(OpBuilder &b, Location loc, Value off, Addr &a);
  bool recordScalar(Operation *op, Type valueType, const Addr &a);
  bool recordWhole(Operation *op, const Addr &a);
  SmallVector<Value> elementIndices(OpBuilder &b, Location loc, const Addr &a);
  void rollback();
  void rewrite();
};

Value StructSplitter::constIndex(OpBuilder &b, Location loc, int64_t k) {
  auto c = b.create<arith::ConstantIndexOp>(loc, k);
  created.push_back(c);
  return c;
}

Value StructSplitter::toIndex(OpBuilder &b, Location loc, Value v) {
  if (v.getType().isIndex())
    return v;
  auto c = b.create<arith::IndexCastOp>(loc, b.getIndexType(), v);
  created.push_back(c);
  return c;
}

Value StructSplitter::add(OpBuilder &b, Location loc, Value a, Value c) {
  if (!a)
    return c;
  if (!c)
    return a;
  auto s = b.create<arith::AddIOp>(loc, a, c);
  created.push_back(s);
  return s;
}

Value StructSplitter::mulConst(OpBuilder &b, Location loc, Value v,
                               int64_t k) {
  if (k == 1)
    return v;
  auto m = b.create<arith::MulIOp>(loc, v, constIndex(b, loc, k));
  created.push_back(m);
  return m;
}

int64_t StructSplitter::stride(unsigned dim) const {
  int64_t s = 1;
  for (unsigned d = dim + 1; d < type.getRank(); ++d)
    s *= type.getShape()[d];
  return s;
}

/// Matches `v` = (index_cast / ext of) `x * k` with constant k; returns x.
static Value matchMulConst(Value v, int64_t &k) {
  while (Operation *d = v.getDefiningOp()) {
    if (isa<arith::IndexCastOp, arith::ExtSIOp, arith::ExtUIOp,
            arith::IndexCastUIOp>(d)) {
      v = d->getOperand(0);
      continue;
    }
    break;
  }
  auto mul = v.getDefiningOp<arith::MulIOp>();
  if (!mul)
    return {};
  APInt c;
  if (matchPattern(mul.getRhs(), m_ConstantInt(&c))) {
    k = c.getSExtValue();
    return mul.getLhs();
  }
  if (matchPattern(mul.getLhs(), m_ConstantInt(&c))) {
    k = c.getSExtValue();
    return mul.getRhs();
  }
  return {};
}

bool StructSplitter::addByteOffset(OpBuilder &b, Location loc, Value off,
                                   Addr &a) {
  APInt c;
  if (matchPattern(off, m_ConstantInt(&c))) {
    int64_t k = c.getSExtValue();
    // Whole elements go to the element offset, the rest stays in bytes.
    int64_t whole = k / elemSize, rest = k % elemSize;
    if (rest < 0) {
      rest += elemSize;
      --whole;
    }
    if (whole)
      a.tail = add(b, loc, a.tail, constIndex(b, loc, whole));
    a.byteConst += rest;
    return true;
  }
  if (auto add0 = off.getDefiningOp<arith::AddIOp>())
    return addByteOffset(b, loc, add0.getLhs(), a) &&
           addByteOffset(b, loc, add0.getRhs(), a);
  int64_t k = 0;
  if (Value x = matchMulConst(off, k))
    if (k != 0 && k % elemSize == 0) {
      a.tail = add(b, loc, a.tail, mulConst(b, loc, toIndex(b, loc, x),
                                            k / elemSize));
      return true;
    }
  a.byteDyn = add(b, loc, a.byteDyn, toIndex(b, loc, off));
  return true;
}

bool StructSplitter::addGep(LLVM::GEPOp gep, Addr &a) {
  OpBuilder b(gep);
  Location loc = gep.getLoc();
  Type elem = gep.getElemType();
  auto elemLayout = layoutOf(elem);
  if (!elemLayout)
    return fail("getelementptr over a type without a layout");
  auto indices = gep.getIndices();
  // The first index steps over whole `elem` objects.
  Type cur = elem;
  for (auto [pos, idx] : llvm::enumerate(indices)) {
    int64_t stepBytes;
    if (pos == 0) {
      stepBytes = elemLayout->size;
    } else if (auto st = dyn_cast<LLVM::LLVMStructType>(cur)) {
      auto attr = idx.dyn_cast<IntegerAttr>();
      if (!attr)
        return fail("dynamic struct field index");
      unsigned f = attr.getInt();
      if (f >= st.getBody().size())
        return fail("struct field index out of range");
      a.byteConst += fieldOffset(st, f);
      cur = st.getBody()[f];
      continue;
    } else if (auto at = dyn_cast<LLVM::LLVMArrayType>(cur)) {
      cur = at.getElementType();
      stepBytes = layoutOf(cur)->size;
    } else {
      return fail("getelementptr into a scalar");
    }
    if (auto attr = idx.dyn_cast<IntegerAttr>()) {
      int64_t k = attr.getInt() * stepBytes;
      if (k)
        if (!addByteOffset(b, loc, constIndex(b, loc, k), a))
          return false;
      continue;
    }
    Value v = idx.get<Value>();
    if (pos == 0 && stepBytes % elemSize == 0) {
      a.tail = add(b, loc, a.tail,
                   mulConst(b, loc, toIndex(b, loc, v), stepBytes / elemSize));
      continue;
    }
    if (stepBytes == 1) {
      if (!addByteOffset(b, loc, v, a))
        return false;
      continue;
    }
    a.byteDyn =
        add(b, loc, a.byteDyn, mulConst(b, loc, toIndex(b, loc, v), stepBytes));
  }
  // Fold whole elements of the constant byte offset into the element offset.
  if (a.byteConst >= elemSize || a.byteConst < 0) {
    int64_t whole = a.byteConst / elemSize, rest = a.byteConst % elemSize;
    if (rest < 0) {
      rest += elemSize;
      --whole;
    }
    a.tail = add(b, loc, a.tail, constIndex(b, loc, whole));
    a.byteConst = rest;
  }
  return true;
}

bool StructSplitter::visitMemref(Value v, Addr a) {
  for (Operation *user : v.getUsers()) {
    if (auto cast = dyn_cast<memref::CastOp>(user)) {
      derived.push_back(cast);
      if (!visitMemref(cast.getResult(), a))
        return false;
      continue;
    }
    if (auto si = dyn_cast<SubIndexOp>(user)) {
      if (si.getSource() != v)
        return fail("struct array used as a subindex operand");
      auto src = cast<MemRefType>(v.getType());
      auto res = dyn_cast<MemRefType>(si.getResult().getType());
      if (!res || a.byteConst || a.byteDyn)
        return fail("subindex of an inner address");
      OpBuilder b(si);
      unsigned dim = a.lead.size();
      if (res.getRank() + 1 == src.getRank()) {
        if (a.tail)
          return fail("row select after pointer arithmetic");
        a.lead.push_back(toIndex(b, si.getLoc(), si.getIndex()));
        derived.push_back(si);
        bool ok = visitMemref(si.getResult(), a);
        a.lead.pop_back();
        if (!ok)
          return false;
        continue;
      }
      if (res.getRank() != src.getRank())
        return fail("subindex changing the rank by more than one");
      Addr b2 = a;
      b2.tail = add(b, si.getLoc(), a.tail,
                    mulConst(b, si.getLoc(),
                             toIndex(b, si.getLoc(), si.getIndex()),
                             stride(dim)));
      derived.push_back(si);
      if (!visitMemref(si.getResult(), b2))
        return false;
      continue;
    }
    if (auto m2p = dyn_cast<Memref2PointerOp>(user)) {
      derived.push_back(m2p);
      if (!visitPointer(m2p.getResult(), a))
        return false;
      continue;
    }
    if (isa<memref::DeallocOp>(user)) {
      derived.push_back(user);
      continue;
    }
    if (isa<memref::LoadOp, affine::AffineLoadOp, memref::StoreOp,
            affine::AffineStoreOp>(user)) {
      if (isa<memref::StoreOp, affine::AffineStoreOp>(user) &&
          user->getOperand(0) == v)
        return fail("the array itself stored as a value");
      // Indices of the access, applied to the view.
      OpBuilder b(user);
      Location loc = user->getLoc();
      SmallVector<Value> idx;
      if (auto al = dyn_cast<affine::AffineLoadOp>(user)) {
        for (AffineExpr e : al.getAffineMap().getResults()) {
          auto ap = b.create<affine::AffineApplyOp>(
              loc, AffineMap::get(al.getAffineMap().getNumDims(),
                                  al.getAffineMap().getNumSymbols(), e),
              al.getMapOperands());
          created.push_back(ap);
          idx.push_back(ap);
        }
      } else if (auto as = dyn_cast<affine::AffineStoreOp>(user)) {
        for (AffineExpr e : as.getAffineMap().getResults()) {
          auto ap = b.create<affine::AffineApplyOp>(
              loc, AffineMap::get(as.getAffineMap().getNumDims(),
                                  as.getAffineMap().getNumSymbols(), e),
              as.getMapOperands());
          created.push_back(ap);
          idx.push_back(ap);
        }
      } else if (auto ml = dyn_cast<memref::LoadOp>(user)) {
        idx.assign(ml.getIndices().begin(), ml.getIndices().end());
      } else {
        auto ms = cast<memref::StoreOp>(user);
        idx.assign(ms.getIndices().begin(), ms.getIndices().end());
      }
      if (a.byteConst || a.byteDyn)
        return fail("whole-element access at an inner address");
      Addr b2 = a;
      unsigned dim = a.lead.size();
      auto vt = cast<MemRefType>(v.getType());
      // A view of the remaining dims: its indices add to the element offset.
      for (unsigned i = 0; i < idx.size(); ++i) {
        unsigned d = dim + i;
        int64_t s = (d < type.getRank()) ? stride(d) : 1;
        if (vt.getRank() == type.getRank() - dim)
          b2.tail = add(b, loc, b2.tail, mulConst(b, loc, idx[i], s));
        else
          return fail("access through a view of unexpected rank");
      }
      if (!recordWhole(user, b2))
        return false;
      continue;
    }
    return fail(Twine("struct array used by ") +
                user->getName().getStringRef());
  }
  return true;
}

bool StructSplitter::visitPointer(Value v, Addr a) {
  for (Operation *user : v.getUsers()) {
    if (auto gep = dyn_cast<LLVM::GEPOp>(user)) {
      if (gep.getBase() != v)
        return fail("struct pointer used as a getelementptr index");
      Addr b2 = a;
      if (!addGep(gep, b2))
        return false;
      derived.push_back(gep);
      if (!visitPointer(gep.getResult(), b2))
        return false;
      continue;
    }
    if (auto ld = dyn_cast<LLVM::LoadOp>(user)) {
      if (ld.getType() == structType) {
        if (a.byteConst || a.byteDyn)
          return fail("struct load at an inner address");
        if (!recordWhole(ld, a))
          return false;
        continue;
      }
      if (!recordScalar(ld, ld.getType(), a))
        return false;
      continue;
    }
    if (auto st = dyn_cast<LLVM::StoreOp>(user)) {
      if (st.getValue() == v)
        return fail("struct pointer stored as a value");
      if (st.getValue().getType() == structType) {
        if (a.byteConst || a.byteDyn)
          return fail("struct store at an inner address");
        if (!recordWhole(st, a))
          return false;
        continue;
      }
      if (!recordScalar(st, st.getValue().getType(), a))
        return false;
      continue;
    }
    return fail(Twine("struct pointer used by ") +
                user->getName().getStringRef());
  }
  return true;
}

SmallVector<Value> StructSplitter::elementIndices(OpBuilder &b, Location loc,
                                                  const Addr &a) {
  SmallVector<Value> idx(a.lead.begin(), a.lead.end());
  unsigned rest = type.getRank() - a.lead.size();
  if (rest == 0)
    return idx;
  if (!a.tail) {
    for (unsigned i = 0; i < rest; ++i)
      idx.push_back(constIndex(b, loc, 0));
    return idx;
  }
  if (rest == 1) {
    idx.push_back(a.tail);
    return idx;
  }
  // Delinearise the element offset over the remaining dimensions.
  for (unsigned d = a.lead.size(); d < type.getRank(); ++d) {
    int64_t s = stride(d);
    Value q = a.tail;
    if (s != 1) {
      auto div = b.create<arith::DivUIOp>(loc, q, constIndex(b, loc, s));
      created.push_back(div);
      q = div;
    }
    if (d != a.lead.size()) {
      auto rem = b.create<arith::RemUIOp>(
          loc, q, constIndex(b, loc, type.getShape()[d]));
      created.push_back(rem);
      q = rem;
    }
    idx.push_back(q);
  }
  return idx;
}

bool StructSplitter::recordScalar(Operation *op, Type valueType,
                                  const Addr &a) {
  int found = -1;
  for (auto [i, l] : llvm::enumerate(leaves))
    if (a.byteConst >= l.offset && a.byteConst < l.offset + l.bytes()) {
      found = i;
      break;
    }
  if (found < 0)
    return fail("access to struct padding");
  const Leaf &l = leaves[found];
  if (valueType != l.scalar)
    return fail("access type differs from the member type");
  int64_t inner = a.byteConst - l.offset;
  if (inner % l.scalarSize)
    return fail("misaligned member access");
  if (l.dims.empty() && a.byteDyn)
    return fail("dynamic offset into a scalar member");
  OpBuilder b(op);
  Location loc = op->getLoc();
  Access acc{op, found, elementIndices(b, loc, a)};
  if (!l.dims.empty()) {
    // The scalar index inside the array member.
    Value lin = inner ? constIndex(b, loc, inner / l.scalarSize) : Value();
    if (a.byteDyn) {
      Value dyn = a.byteDyn;
      if (l.scalarSize != 1) {
        auto div = b.create<arith::DivUIOp>(loc, dyn,
                                            constIndex(b, loc, l.scalarSize));
        created.push_back(div);
        dyn = div;
      }
      lin = add(b, loc, lin, dyn);
    }
    if (!lin)
      lin = constIndex(b, loc, 0);
    int64_t s = 1;
    for (int64_t d : l.dims)
      s *= d;
    for (unsigned d = 0; d < l.dims.size(); ++d) {
      s /= l.dims[d];
      Value q = lin;
      if (s != 1) {
        auto div = b.create<arith::DivUIOp>(loc, q, constIndex(b, loc, s));
        created.push_back(div);
        q = div;
      }
      if (d != 0) {
        auto rem =
            b.create<arith::RemUIOp>(loc, q, constIndex(b, loc, l.dims[d]));
        created.push_back(rem);
        q = rem;
      }
      acc.indices.push_back(q);
    }
  }
  accesses.push_back(std::move(acc));
  return true;
}

bool StructSplitter::recordWhole(Operation *op, const Addr &a) {
  for (const Leaf &l : leaves)
    if (!l.dims.empty())
      return fail("whole-struct copy of a struct with an array member");
  OpBuilder b(op);
  accesses.push_back(Access{op, -1, elementIndices(b, op->getLoc(), a)});
  return true;
}

void StructSplitter::rollback() {
  for (Operation *op : llvm::reverse(created))
    if (op->use_empty())
      op->erase();
  created.clear();
}

bool StructSplitter::run() {
  auto l = layoutOf(structType);
  if (!l || l->size == 0)
    return fail("struct without a layout");
  elemSize = l->size;
  SmallVector<int64_t> path;
  if (!collectLeaves(structType, 0, path, leaves))
    return fail("struct member that is not a scalar or an array of scalars");
  if (!type.hasStaticShape())
    return fail("dynamic shape");
  if (!visitMemref(alloc->getResult(0), Addr{})) {
    rollback();
    return false;
  }
  rewrite();
  return true;
}

void StructSplitter::rewrite() {
  OpBuilder b(alloc);
  Location loc = alloc->getLoc();
  std::string base = "s";
  if (auto n = alloc->getAttrOfType<StringAttr>("polygeist.varname"))
    base = n.str();
  SmallVector<Value> mems;
  for (const Leaf &leaf : leaves) {
    SmallVector<int64_t> shape(type.getShape().begin(), type.getShape().end());
    shape.append(leaf.dims.begin(), leaf.dims.end());
    auto mt = MemRefType::get(shape, leaf.scalar, MemRefLayoutAttrInterface(),
                              type.getMemorySpace());
    OperationState st(loc, alloc->getName());
    st.addTypes(mt);
    st.addAttributes(alloc->getAttrs());
    Operation *m = b.create(st);
    std::string name = base;
    for (int64_t p : leaf.path)
      name += "_" + std::to_string(p);
    m->setAttr("polygeist.varname", b.getStringAttr(name));
    m->setAttr("hls.struct_member",
               b.getStringAttr(base + " member " +
                               std::to_string(leaf.path.empty()
                                                  ? 0
                                                  : leaf.path.front())));
    mems.push_back(m->getResult(0));
  }
  for (Access &acc : accesses) {
    Operation *op = acc.op;
    OpBuilder ob(op);
    Location l = op->getLoc();
    bool isLoad = isa<LLVM::LoadOp, memref::LoadOp, affine::AffineLoadOp>(op);
    if (acc.leaf >= 0) {
      Value mem = mems[acc.leaf];
      if (isLoad) {
        auto ld = ob.create<memref::LoadOp>(l, mem, acc.indices);
        op->getResult(0).replaceAllUsesWith(ld);
      } else {
        Value val = cast<LLVM::StoreOp>(op).getValue();
        ob.create<memref::StoreOp>(l, val, mem, acc.indices);
      }
      op->erase();
      continue;
    }
    if (isLoad) {
      Value agg = ob.create<LLVM::UndefOp>(l, structType);
      for (auto [i, leaf] : llvm::enumerate(leaves)) {
        Value v = ob.create<memref::LoadOp>(l, mems[i], acc.indices);
        agg = ob.create<LLVM::InsertValueOp>(l, agg, v, leaf.path);
      }
      op->getResult(0).replaceAllUsesWith(agg);
    } else {
      Value val = op->getOperand(0);
      for (auto [i, leaf] : llvm::enumerate(leaves)) {
        Value v = ob.create<LLVM::ExtractValueOp>(l, val, leaf.path);
        ob.create<memref::StoreOp>(l, v, mems[i], acc.indices);
      }
    }
    op->erase();
  }
  for (Operation *op : llvm::reverse(derived))
    if (op->use_empty())
      op->erase();
  if (alloc->use_empty())
    alloc->erase();
  // Index arithmetic built for addresses no access ended up using.
  for (Operation *op : llvm::reverse(created))
    if (op->use_empty())
      op->erase();
}

/// Inlines `call` when its callee is a defined, single-block function without
/// nested regions that Vitis would inline (not `inline off`, not kept by
/// cgeist): the struct member functions cgeist emits (`operator=`, copy
/// constructors, accessors taking `P &`). MLIR's inliner refuses them inside
/// an affine.for because of their llvm.load / llvm.store; Vitis inlines them
/// (they have no pragma and are tiny), and the member accesses must be seen
/// to split the array. Returns true when inlined.
static bool inlineStructCall(func::CallOp call) {
  auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
      call, call.getCalleeAttr());
  // `hls.inline_auto_off`: a call cgeist kept because Vitis would not inline
  // it automatically (cgeist --hls-auto-inline).
  constexpr llvm::StringLiteral inlineAutoOff = "hls.inline_auto_off";
  if (!callee || callee.isExternal() || callee->hasAttr(kInlineOffAttr) ||
      callee->hasAttr(inlineAutoOff) || call->hasAttr(inlineAutoOff) ||
      !llvm::hasSingleElement(callee.getBody()))
    return false;
  Block &body = callee.getBody().front();
  for (Operation &op : body)
    if (op.getNumRegions() != 0)
      return false;
  auto ret = dyn_cast<func::ReturnOp>(body.getTerminator());
  if (!ret)
    return false;
  IRMapping map;
  map.map(body.getArguments(), call.getOperands());
  OpBuilder b(call);
  for (Operation &op : body.without_terminator())
    b.clone(op, map);
  for (auto [res, v] : llvm::zip(call.getResults(), ret.getOperands()))
    res.replaceAllUsesWith(map.lookupOrDefault(v));
  call.erase();
  return true;
}

/// Inlines the calls that receive a view or pointer of `alloc` (see
/// inlineStructCall), until none is left or none can be inlined.
static void inlineCallsOnStruct(Operation *alloc) {
  for (int round = 0; round < 32; ++round) {
    SmallVector<Value> work{alloc->getResult(0)};
    func::CallOp found;
    while (!work.empty() && !found) {
      Value v = work.pop_back_val();
      for (Operation *user : v.getUsers()) {
        if (auto call = dyn_cast<func::CallOp>(user)) {
          found = call;
          break;
        }
        if (isa<memref::CastOp, SubIndexOp, Memref2PointerOp, LLVM::GEPOp>(
                user))
          work.push_back(user->getResult(0));
      }
    }
    if (!found || !inlineStructCall(found))
      return;
  }
}

struct SplitStructMemrefsPass
    : PassWrapper<SplitStructMemrefsPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(SplitStructMemrefsPass)

  StringRef getArgument() const final { return "split-struct-memrefs"; }
  StringRef getDescription() const final {
    return "Split each local array of structs into one memref per member, "
           "as Vitis disaggregates it (VITIS_NOTES.md N29)";
  }
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect,
                    affine::AffineDialect, LLVM::LLVMDialect>();
  }

  void runOnOperation() override {
    SmallVector<Operation *> candidates;
    getOperation().walk([&](Operation *op) {
      if (!isa<memref::AllocaOp, memref::AllocOp>(op))
        return;
      auto mt = dyn_cast<MemRefType>(op->getResult(0).getType());
      if (mt && isa<LLVM::LLVMStructType>(mt.getElementType()))
        candidates.push_back(op);
    });
    for (Operation *op : candidates) {
      inlineCallsOnStruct(op);
      StructSplitter s(op, cast<MemRefType>(op->getResult(0).getType()));
      if (!s.run())
        op->emitWarning("struct array not split into members: ") << s.reason;
    }
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createSplitStructMemrefsPass() {
  return std::make_unique<SplitStructMemrefsPass>();
}

void circt::hls_analysis::registerSplitStructMemrefsPass() {
  PassRegistration<SplitStructMemrefsPass>();
}
