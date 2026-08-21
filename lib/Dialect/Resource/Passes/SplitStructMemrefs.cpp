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
// Vitis disaggregates a struct-typed variable into one memory per leaf by
// default: `struct P { int a; short b; }; P s[1024];` becomes the two
// memories s_a (1024 x 32 bits, 2 BRAM_18K) and s_b (1024 x 16 bits, 1
// BRAM_18K), each priced on its own (VITIS_NOTES.md N29, N37 S1); a struct
// with one array member (std::array, hls::vector, `struct R { short d[8]; }`)
// becomes one memory named after the variable, the member's dimensions after
// the variable's. When an AGGREGATE pragma reaches the variable (cgeist's
// `hls.aggregate`, on the variable itself or carried there from a callee
// parameter or an hls::vector member, N37 S2) Vitis instead builds one memory
// of (product of the variable's dimensions) x (sum of the leaf widths, no
// padding) bits and accesses it one word at a time (N37 S3): a member read is
// a word read and a shift, an iteration that writes every leaf of an element
// stores one word, and one that writes only some leaves reads the word,
// merges and writes it back.
//
// cgeist keeps such a variable as one `memref<dims x !llvm.struct<...>>`
// (a memref.alloca, memref.alloc or memref.global) and reaches the members
// through `polygeist.subindex` element views, `polygeist.memref2pointer`,
// `llvm.getelementptr`, `polygeist.pointer2memref` member views and
// `llvm.load` / `llvm.store`, which hls-est cannot see as memory accesses.
//
// This pass replaces every such variable whose uses it fully understands by
// one memref per scalar leaf of the struct (nested structs are flattened; an
// array member `T m[R][C]` adds its dimensions after the variable's own) or,
// aggregated, by one `memref<dims x iB>`, and rewrites every access as
// memref.load / memref.store of the new memory. Small struct member functions
// that receive a view of the variable (accessors, operator[], copy and move
// constructors and assignments) are inlined first, as Vitis inlines them; a
// member function that only copies one whole element into another, member by
// member or byte by byte in one loop (the implicit copy of a trivially
// copyable struct), becomes one whole-element copy. A variable it does not
// fully understand (a pointer passed to a kept call, compared, stored, an
// array of structs inside the struct, ...) is left unchanged, with a warning;
// its accesses then stay invisible as before.
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
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/Support/MathExtras.h"

#include <functional>
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
  Type member;                     // the member's type (at `path`)
  int64_t bitOffset = 0;           // first bit in the aggregated word
  int64_t count() const {
    int64_t n = 1;
    for (int64_t d : dims)
      n *= d;
    return n;
  }
  int64_t bytes() const { return scalarSize * count(); }
  unsigned scalarBits() const { return scalar.getIntOrFloatBitWidth(); }
  int64_t bits() const { return scalarBits() * count(); }
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
    l.member = t;
    out.push_back(l);
    return true;
  }
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(t)) {
    SmallVector<int64_t> dims;
    Type e = t;
    while (true) {
      if (auto a = dyn_cast<LLVM::LLVMArrayType>(e)) {
        dims.push_back(a.getNumElements());
        e = a.getElementType();
        continue;
      }
      // An array of one-leaf structs without padding (std::array of
      // std::array): its scalars are contiguous, as in a plain array.
      if (auto st = dyn_cast<LLVM::LLVMStructType>(e)) {
        SmallVector<Leaf> inner;
        SmallVector<int64_t> innerPath;
        auto size = layoutOf(st);
        if (!collectLeaves(st, 0, innerPath, inner) || inner.size() != 1 ||
            !size || inner[0].bytes() != size->size)
          return false;
        dims.append(inner[0].dims.begin(), inner[0].dims.end());
        e = inner[0].scalar;
      }
      break;
    }
    if (!isScalar(e))
      return false;
    Leaf l;
    l.offset = base;
    l.scalar = e;
    l.scalarSize = layoutOf(e)->size;
    l.dims = dims;
    l.path.assign(path.begin(), path.end());
    l.member = t;
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

/// The llvm.extractvalue / insertvalue position of scalar `flat` of `leaf`:
/// the member's path, then one index per array level (and the field of a
/// one-leaf struct between array levels).
SmallVector<int64_t> valuePath(const Leaf &leaf, int64_t flat);

/// The multi-dimensional position of element `flat` of an array of `dims`.
SmallVector<int64_t> delinearize(int64_t flat, ArrayRef<int64_t> dims) {
  SmallVector<int64_t> pos(dims.size());
  for (int i = static_cast<int>(dims.size()) - 1; i >= 0; --i) {
    pos[i] = flat % dims[i];
    flat /= dims[i];
  }
  return pos;
}

SmallVector<int64_t> valuePath(const Leaf &leaf, int64_t flat) {
  SmallVector<int64_t> p(leaf.path.begin(), leaf.path.end());
  SmallVector<int64_t> pos = delinearize(flat, leaf.dims);
  unsigned k = 0;
  Type t = leaf.member;
  while (t && !isScalar(t)) {
    if (auto a = dyn_cast<LLVM::LLVMArrayType>(t)) {
      p.push_back(pos[k++]);
      t = a.getElementType();
    } else if (auto st = dyn_cast<LLVM::LLVMStructType>(t)) {
      // A one-leaf struct (collectLeaves): the field that holds the leaf.
      unsigned f = 0;
      for (auto [i, m] : llvm::enumerate(st.getBody()))
        if (layoutOf(m) && layoutOf(m)->size)
          f = i;
      p.push_back(f);
      t = st.getBody()[f];
    } else {
      break;
    }
  }
  return p;
}

/// Whether `a` and `b` compute the same value: the same SSA value, or pure
/// index arithmetic of the same kind on operands that compute the same values
/// (the analysis builds one copy of an element's index per access).
bool sameValue(Value a, Value b, unsigned depth = 0) {
  if (a == b)
    return true;
  if (!a || !b || depth > 8)
    return false;
  Operation *x = a.getDefiningOp(), *y = b.getDefiningOp();
  if (!x || !y || x->getName() != y->getName() ||
      x->getNumOperands() != y->getNumOperands() ||
      x->getAttrDictionary() != y->getAttrDictionary() ||
      x->getNumResults() != 1 || y->getNumResults() != 1 ||
      a.getType() != b.getType())
    return false;
  if (!isa<arith::ArithDialect, affine::AffineDialect>(x->getDialect()) ||
      !isPure(x))
    return false;
  for (auto [u, v] : llvm::zip(x->getOperands(), y->getOperands()))
    if (!sameValue(u, v, depth + 1))
      return false;
  return true;
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
/// the whole struct) of the element at `element` of root `root`; inside an
/// array member, at scalar `inner` (linear over the member's dimensions;
/// `innerConst` when it is a compile-time constant).
struct Access {
  Operation *op;
  unsigned root;
  int leaf; // -1: whole element
  SmallVector<Value> element;
  Value inner;
  std::optional<int64_t> innerConst;
  /// A scalar of a load / store of a sub-aggregate (`s.inner = t`, an
  /// element of an array of structs inside the struct): its position in the
  /// loaded / stored value. Empty for a plain scalar or whole access.
  SmallVector<int64_t> part;
  bool isStore() const {
    return isa<LLVM::StoreOp, memref::StoreOp, affine::AffineStoreOp>(op);
  }
};

/// The memories that replace one struct variable: one per leaf (split), or
/// one word memory (aggregated).
struct NewMemory {
  MemRefType type;
  std::string name;
  std::string note; // hls.struct_member / hls.aggregated text
};

/// How an hls::stream method moves the struct its data argument refers to:
/// `write` / `write_nb` / `<<` read it, `read(T&)` / `read_nb` / `>>` write
/// it (StreamFifos.cpp ioType names the same methods).
enum class StreamData { ReadsElement, WritesElement };
std::optional<StreamData> streamDataAccess(StringRef method) {
  if (method.starts_with("5write") || method.starts_with("8write_nb") ||
      method.starts_with("ls"))
    return StreamData::ReadsElement;
  if ((method.starts_with("4read") && !method.starts_with("4readEv")) ||
      method.starts_with("7read_nb") || method.starts_with("rs"))
    return StreamData::WritesElement;
  return std::nullopt;
}

class StructSplitter {
public:
  /// `roots`: the values the variable is reached through (the allocation's
  /// result, or every memref.get_global of a global).
  StructSplitter(SmallVector<Value> roots, MemRefType type, bool aggregate,
                 std::string name)
      : roots(std::move(roots)), type(type),
        structType(cast<LLVM::LLVMStructType>(type.getElementType())),
        aggregate(aggregate), name(std::move(name)) {}

  /// Analyses every use; true when all are understood. Nothing is changed
  /// when it returns false.
  bool analyse();
  /// The memories to create (after analyse()).
  SmallVector<NewMemory> newMemories() const;
  /// Rewrites the accesses onto `mems[root][i]` (newMemories() order).
  void rewrite(ArrayRef<SmallVector<Value>> mems);
  void setAggregate(bool a) { aggregate = a; }
  MemRefType getType() const { return type; }
  std::string reason;

  /// A root passed whole (no offset) to a call of a function defined in the
  /// module: the callee's argument is the same variable, split with it.
  struct CallEdge {
    func::CallOp call;
    unsigned operand;
    unsigned root;
    SmallVector<Value> lead; // rows selected before the call (`f(a[k])`)
  };
  SmallVector<CallEdge> edges;
  /// An element passed to an hls::stream read / write: a whole-element
  /// write / read of the variable around a temporary the call receives.
  struct StreamUse {
    func::CallOp call;
    unsigned operand;
    unsigned root;
    SmallVector<Value> element;
    StreamData kind;
  };
  SmallVector<StreamUse> streamUses;
  /// Whether the call rewrite selects rows of the new memories.
  bool selectsRows() const {
    return llvm::any_of(edges, [](const CallEdge &e) { return !e.lead.empty(); });
  }

private:
  SmallVector<Value> roots;
  MemRefType type;
  LLVM::LLVMStructType structType;
  bool aggregate;
  std::string name;
  unsigned curRoot = 0;
  int64_t elemSize = 0;
  int64_t wordBits = 0;
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
  bool visitMemberView(Value v, Addr a);
  bool addGep(LLVM::GEPOp gep, Addr &a);
  bool addByteOffset(OpBuilder &b, Location loc, Value off, Addr &a);
  bool recordScalar(Operation *op, Type valueType, const Addr &a,
                    ArrayRef<int64_t> part = {});
  bool recordComposite(Operation *op, Type valueType, const Addr &a);
  bool recordWhole(Operation *op, const Addr &a);
  SmallVector<Value> accessIndices(OpBuilder &b, Operation *user);
  SmallVector<Value> elementIndices(OpBuilder &b, Location loc, const Addr &a);
  SmallVector<Value> leafIndices(OpBuilder &b, Location loc, const Leaf &l,
                                 const Access &acc);
  void rollback();
  void rewriteSplit(ArrayRef<SmallVector<Value>> mems);
  Value addPart(Operation *op, ArrayRef<int64_t> part, Value scalar);
  void finishComposites();
  DenseMap<Operation *, Value> composite;
  llvm::SetVector<Operation *> compositeOps;
  void rewriteAggregated(ArrayRef<SmallVector<Value>> mems);
  void cleanup();
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

/// The indices of a memref / affine load or store, as index values (an
/// affine access gets one affine.apply per map result).
SmallVector<Value> StructSplitter::accessIndices(OpBuilder &b,
                                                 Operation *user) {
  Location loc = user->getLoc();
  SmallVector<Value> idx;
  auto applyAll = [&](AffineMap map, ValueRange operands) {
    for (AffineExpr e : map.getResults()) {
      auto ap = b.create<affine::AffineApplyOp>(
          loc, AffineMap::get(map.getNumDims(), map.getNumSymbols(), e),
          operands);
      created.push_back(ap);
      idx.push_back(ap);
    }
  };
  if (auto al = dyn_cast<affine::AffineLoadOp>(user))
    applyAll(al.getAffineMap(), al.getMapOperands());
  else if (auto as = dyn_cast<affine::AffineStoreOp>(user))
    applyAll(as.getAffineMap(), as.getMapOperands());
  else if (auto ml = dyn_cast<memref::LoadOp>(user))
    idx.assign(ml.getIndices().begin(), ml.getIndices().end());
  else
    idx.assign(cast<memref::StoreOp>(user).getIndices().begin(),
               cast<memref::StoreOp>(user).getIndices().end());
  return idx;
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
      // An element view (`&a[i]`): the index steps over whole elements of
      // the view's first dimension.
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
      SmallVector<Value> idx = accessIndices(b, user);
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
    if (auto call = dyn_cast<func::CallOp>(user)) {
      bool edged = false, other = false;
      auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
          call, call.getCalleeAttr());
      // Whole rows (no offset inside them): the callee's parameter is the
      // same variable, or a row of it.
      bool rows = !a.tail && !a.byteConst && !a.byteDyn;
      std::optional<StreamTemplate> stream =
          callee ? parseStreamMethod(callee.getSymName()) : std::nullopt;
      for (OpOperand &use : user->getOpOperands()) {
        if (use.get() != v)
          continue;
        unsigned n = use.getOperandNumber();
        if (stream && n == 1 && !a.byteConst && !a.byteDyn) {
          if (auto kind = streamDataAccess(stream->method)) {
            OpBuilder b(call);
            streamUses.push_back(StreamUse{
                call, n, curRoot, elementIndices(b, call.getLoc(), a),
                *kind});
            edged = true;
            continue;
          }
        }
        auto at = callee && !callee.isExternal() && n < callee.getNumArguments()
                      ? dyn_cast<MemRefType>(callee.getArgument(n).getType())
                      : MemRefType();
        if (rows && at && at.getElementType() == structType &&
            at.getRank() == type.getRank() - a.lead.size()) {
          edges.push_back(CallEdge{call, n, curRoot, a.lead});
          edged = true;
        } else {
          other = true;
        }
      }
      if (edged && !other)
        continue;
      return fail(Twine("struct array passed to the kept call @") +
                  call.getCallee());
    }
    return fail(Twine("struct array used by ") +
                user->getName().getStringRef());
  }
  return true;
}

/// A memref of scalars that `polygeist.pointer2memref` made from an address
/// inside the element (an array member reached through `operator[]`, a
/// `T *p = s.m` pointer): its indices step over its scalars.
bool StructSplitter::visitMemberView(Value v, Addr a) {
  auto vt = cast<MemRefType>(v.getType());
  auto scalarLayout = layoutOf(vt.getElementType());
  if (!scalarLayout)
    return fail("member view of a type without a layout");
  // Byte stride of dimension `d` of the view (static trailing dims).
  auto byteStride = [&](unsigned d) -> std::optional<int64_t> {
    int64_t s = scalarLayout->size;
    for (unsigned i = d + 1; i < vt.getRank(); ++i) {
      if (ShapedType::isDynamic(vt.getShape()[i]))
        return std::nullopt;
      s *= vt.getShape()[i];
    }
    return s;
  };
  for (Operation *user : v.getUsers()) {
    if (auto cast = dyn_cast<memref::CastOp>(user)) {
      derived.push_back(cast);
      if (!visitMemberView(cast.getResult(), a))
        return false;
      continue;
    }
    if (auto si = dyn_cast<SubIndexOp>(user)) {
      if (si.getSource() != v)
        return fail("member view used as a subindex operand");
      auto s = byteStride(0);
      if (!s)
        return fail("member view with a dynamic inner dimension");
      OpBuilder b(si);
      Addr b2 = a;
      if (!addByteOffset(b, si.getLoc(),
                         mulConst(b, si.getLoc(),
                                  toIndex(b, si.getLoc(), si.getIndex()), *s),
                         b2))
        return false;
      derived.push_back(si);
      if (!visitMemberView(si.getResult(), b2))
        return false;
      continue;
    }
    if (auto m2p = dyn_cast<Memref2PointerOp>(user)) {
      derived.push_back(m2p);
      if (!visitPointer(m2p.getResult(), a))
        return false;
      continue;
    }
    if (isa<memref::LoadOp, affine::AffineLoadOp, memref::StoreOp,
            affine::AffineStoreOp>(user)) {
      if (isa<memref::StoreOp, affine::AffineStoreOp>(user) &&
          user->getOperand(0) == v)
        return fail("a member view stored as a value");
      OpBuilder b(user);
      Location loc = user->getLoc();
      SmallVector<Value> idx = accessIndices(b, user);
      Addr b2 = a;
      for (auto [d, i] : llvm::enumerate(idx)) {
        auto s = byteStride(d);
        if (!s)
          return fail("member view with a dynamic inner dimension");
        if (!addByteOffset(b, loc, mulConst(b, loc, i, *s), b2))
          return false;
      }
      Type valueType = isa<memref::StoreOp, affine::AffineStoreOp>(user)
                           ? user->getOperand(0).getType()
                           : user->getResult(0).getType();
      if (!(isScalar(valueType) ? recordScalar(user, valueType, b2)
                                : recordComposite(user, valueType, b2)))
        return false;
      continue;
    }
    return fail(Twine("member view used by ") +
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
    if (auto p2m = dyn_cast<Pointer2MemrefOp>(user)) {
      auto mt = dyn_cast<MemRefType>(p2m.getResult().getType());
      if (!mt)
        return fail("pointer2memref to a non-memref");
      derived.push_back(p2m);
      if (mt.getElementType() == structType && !a.byteConst && !a.byteDyn) {
        // Back to a view of whole elements.
        if (!visitMemref(p2m.getResult(), a))
          return false;
        continue;
      }
      if (!visitMemberView(p2m.getResult(), a))
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
      if (!(isScalar(ld.getType()) ? recordScalar(ld, ld.getType(), a)
                                   : recordComposite(ld, ld.getType(), a)))
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
      Type t = st.getValue().getType();
      if (!(isScalar(t) ? recordScalar(st, t, a) : recordComposite(st, t, a)))
        return false;
      continue;
    }
    if (auto call = dyn_cast<LLVM::CallOp>(user))
      return fail("struct pointer passed to an llvm.call");
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
                                  const Addr &a, ArrayRef<int64_t> part) {
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
  Access acc{op, curRoot, found, elementIndices(b, loc, a), Value(),
             std::nullopt};
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
    } else {
      acc.innerConst = inner / l.scalarSize;
    }
    if (!lin)
      lin = constIndex(b, loc, 0);
    acc.inner = lin;
  } else {
    acc.innerConst = 0;
  }
  acc.part.assign(part.begin(), part.end());
  accesses.push_back(std::move(acc));
  return true;
}

/// Calls `fn(byteOffset, scalarType, path)` for every scalar of `t`.
static bool forEachScalar(
    Type t, int64_t base, SmallVectorImpl<int64_t> &path,
    llvm::function_ref<bool(int64_t, Type, ArrayRef<int64_t>)> fn) {
  if (isScalar(t))
    return fn(base, t, path);
  if (auto at = dyn_cast<LLVM::LLVMArrayType>(t)) {
    auto e = layoutOf(at.getElementType());
    if (!e)
      return false;
    for (unsigned i = 0; i < at.getNumElements(); ++i) {
      path.push_back(i);
      bool ok = forEachScalar(at.getElementType(), base + i * e->size, path,
                              fn);
      path.pop_back();
      if (!ok)
        return false;
    }
    return true;
  }
  if (auto st = dyn_cast<LLVM::LLVMStructType>(t)) {
    if (st.isOpaque())
      return false;
    for (unsigned i = 0, n = st.getBody().size(); i < n; ++i) {
      path.push_back(i);
      bool ok = forEachScalar(st.getBody()[i], base + fieldOffset(st, i),
                              path, fn);
      path.pop_back();
      if (!ok)
        return false;
    }
    return true;
  }
  return false;
}

bool StructSplitter::recordComposite(Operation *op, Type valueType,
                                     const Addr &a) {
  if (valueType == structType && !a.byteConst && !a.byteDyn)
    return recordWhole(op, a);
  if (!isa<LLVM::LLVMStructType, LLVM::LLVMArrayType>(valueType))
    return fail("access type differs from the member type");
  SmallVector<int64_t> path;
  return forEachScalar(valueType, 0, path,
                       [&](int64_t off, Type scalar, ArrayRef<int64_t> part) {
                         Addr b = a;
                         b.byteConst += off;
                         return recordScalar(op, scalar, b, part);
                       }) ||
         fail("access to a sub-aggregate this pass cannot map");
}

bool StructSplitter::recordWhole(Operation *op, const Addr &a) {
  OpBuilder b(op);
  accesses.push_back(Access{op, curRoot, -1,
                            elementIndices(b, op->getLoc(), a), Value(),
                            std::nullopt});
  return true;
}

/// The indices of `acc`'s scalar in the split memory of leaf `l`: the
/// element's, then the position inside an array member.
SmallVector<Value> StructSplitter::leafIndices(OpBuilder &b, Location loc,
                                               const Leaf &l,
                                               const Access &acc) {
  SmallVector<Value> idx(acc.element.begin(), acc.element.end());
  if (l.dims.empty())
    return idx;
  int64_t s = l.count();
  for (unsigned d = 0; d < l.dims.size(); ++d) {
    s /= l.dims[d];
    Value q = acc.inner;
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
    idx.push_back(q);
  }
  return idx;
}

void StructSplitter::rollback() {
  for (Operation *op : llvm::reverse(created))
    if (op->use_empty())
      op->erase();
  created.clear();
}

bool StructSplitter::analyse() {
  auto l = layoutOf(structType);
  if (!l || l->size == 0)
    return fail("struct without a layout");
  elemSize = l->size;
  SmallVector<int64_t> path;
  if (!collectLeaves(structType, 0, path, leaves))
    return fail("struct member that is not a scalar or an array of scalars");
  // A callee's parameter may have an unknown first dimension (`P p[]`).
  for (int64_t d : type.getShape().drop_front())
    if (ShapedType::isDynamic(d))
      return fail("dynamic inner dimension");
  if (type.getRank() == 0)
    return fail("rank-0 struct memref");
  for (Leaf &leaf : leaves) {
    leaf.bitOffset = wordBits;
    wordBits += leaf.bits();
  }
  for (unsigned r = 0; r < roots.size(); ++r) {
    curRoot = r;
    if (!visitMemref(roots[r], Addr{})) {
      rollback();
      return false;
    }
  }
  return true;
}

SmallVector<NewMemory> StructSplitter::newMemories() const {
  SmallVector<NewMemory> out;
  SmallVector<int64_t> shape(type.getShape().begin(), type.getShape().end());
  std::string dims;
  for (int64_t d : shape)
    dims += (dims.empty() ? "" : "x") + std::to_string(d);
  if (aggregate) {
    MLIRContext *ctx = type.getContext();
    out.push_back(NewMemory{
        MemRefType::get(shape, IntegerType::get(ctx, wordBits),
                        MemRefLayoutAttrInterface(), type.getMemorySpace()),
        name,
        "aggregated (AGGREGATE pragma): " + dims + " words x " +
            std::to_string(wordBits) + " bits, " +
            std::to_string(leaves.size()) +
            (leaves.size() == 1 ? " leaf" : " leaves") +
            " packed without padding; members are read and written one "
            "word at a time"});
    return out;
  }
  for (const Leaf &leaf : leaves) {
    SmallVector<int64_t> s = shape;
    s.append(leaf.dims.begin(), leaf.dims.end());
    // One leaf: the memory is the variable (Vitis names it so: `ra`, `rb`).
    std::string n = name;
    if (leaves.size() > 1)
      for (int64_t p : leaf.path)
        n += "_" + std::to_string(p);
    out.push_back(NewMemory{
        MemRefType::get(s, leaf.scalar, MemRefLayoutAttrInterface(),
                        type.getMemorySpace()),
        n,
        name + " member " +
            std::to_string(leaf.path.empty() ? 0 : leaf.path.front())});
  }
  return out;
}

void StructSplitter::rewrite(ArrayRef<SmallVector<Value>> mems) {
  // Each stream call gets a one-element temporary; the element is copied
  // into it before a write and out of it after a read.
  for (StreamUse &u : streamUses) {
    Value view = u.call.getOperand(u.operand);
    auto viewType = cast<MemRefType>(view.getType());
    auto fn = u.call->getParentOfType<func::FuncOp>();
    OpBuilder eb(&fn.getBody().front(), fn.getBody().front().begin());
    Value tmp = eb.create<memref::AllocaOp>(
        u.call.getLoc(), MemRefType::get({1}, structType));
    Value arg = tmp;
    if (viewType != tmp.getType())
      arg = eb.create<memref::CastOp>(u.call.getLoc(), viewType, tmp);
    OpBuilder b(u.call);
    Location loc = u.call.getLoc();
    Value zero = b.create<arith::ConstantIndexOp>(loc, 0);
    if (u.kind == StreamData::ReadsElement) {
      auto ld = b.create<memref::LoadOp>(loc, view, ValueRange{zero});
      b.create<memref::StoreOp>(loc, ld, tmp, ValueRange{zero});
      accesses.push_back(Access{ld, u.root, -1, u.element, Value(),
                                std::nullopt});
    } else {
      b.setInsertionPointAfter(u.call);
      auto ld = b.create<memref::LoadOp>(loc, tmp, ValueRange{zero});
      auto st = b.create<memref::StoreOp>(loc, ld, view, ValueRange{zero});
      accesses.push_back(Access{st, u.root, -1, u.element, Value(),
                                std::nullopt});
    }
    u.call->setOperand(u.operand, arg);
  }
  if (aggregate)
    rewriteAggregated(mems);
  else
    rewriteSplit(mems);
  cleanup();
}

/// The value of a load of a sub-aggregate, built one scalar at a time.
Value StructSplitter::addPart(Operation *op, ArrayRef<int64_t> part,
                              Value scalar) {
  OpBuilder ob(op);
  Value &cur = composite[op];
  if (!cur)
    cur = ob.create<LLVM::UndefOp>(op->getLoc(), op->getResult(0).getType());
  cur = ob.create<LLVM::InsertValueOp>(op->getLoc(), cur, scalar, part);
  return cur;
}

/// The scalar a store of a sub-aggregate writes at `part`.
static Value storedPart(OpBuilder &ob, Operation *op, ArrayRef<int64_t> part) {
  Value val = op->getOperand(0);
  if (part.empty())
    return val;
  return ob.create<LLVM::ExtractValueOp>(op->getLoc(), val, part);
}

void StructSplitter::finishComposites() {
  for (auto &[op, value] : composite)
    op->getResult(0).replaceAllUsesWith(value);
  for (Operation *op : compositeOps)
    op->erase();
  composite.clear();
  compositeOps.clear();
}

void StructSplitter::rewriteSplit(ArrayRef<SmallVector<Value>> mems) {
  for (Access &acc : accesses) {
    Operation *op = acc.op;
    OpBuilder ob(op);
    Location l = op->getLoc();
    bool isLoad = !acc.isStore();
    if (acc.leaf >= 0) {
      Value mem = mems[acc.root][acc.leaf];
      SmallVector<Value> idx = leafIndices(ob, l, leaves[acc.leaf], acc);
      if (isLoad) {
        auto ld = ob.create<memref::LoadOp>(l, mem, idx);
        if (acc.part.empty())
          op->getResult(0).replaceAllUsesWith(ld);
        else
          addPart(op, acc.part, ld);
      } else {
        ob.create<memref::StoreOp>(l, storedPart(ob, op, acc.part), mem, idx);
      }
      if (acc.part.empty())
        op->erase();
      else
        compositeOps.insert(op);
      continue;
    }
    // A whole element: every scalar of every leaf.
    auto scalarIndices = [&](const Leaf &leaf, int64_t flat) {
      SmallVector<Value> idx(acc.element.begin(), acc.element.end());
      SmallVector<int64_t> pos = delinearize(flat, leaf.dims);
      for (int64_t p : pos)
        idx.push_back(constIndex(ob, l, p));
      return std::make_pair(idx, pos);
    };
    if (isLoad) {
      Value agg = ob.create<LLVM::UndefOp>(l, structType);
      for (auto [i, leaf] : llvm::enumerate(leaves))
        for (int64_t f = 0, n = leaf.count(); f < n; ++f) {
          auto [idx, pos] = scalarIndices(leaf, f);
          Value v = ob.create<memref::LoadOp>(l, mems[acc.root][i], idx);
          agg = ob.create<LLVM::InsertValueOp>(l, agg, v,
                                               valuePath(leaf, f));
        }
      op->getResult(0).replaceAllUsesWith(agg);
    } else {
      Value val = op->getOperand(0);
      for (auto [i, leaf] : llvm::enumerate(leaves))
        for (int64_t f = 0, n = leaf.count(); f < n; ++f) {
          auto [idx, pos] = scalarIndices(leaf, f);
          Value v =
              ob.create<LLVM::ExtractValueOp>(l, val, valuePath(leaf, f));
          ob.create<memref::StoreOp>(l, v, mems[acc.root][i], idx);
        }
    }
    op->erase();
  }
  finishComposites();
}

namespace {
/// Bit-level helpers on the aggregated word.
struct WordBuilder {
  OpBuilder &b;
  Location loc;
  IntegerType word;

  Value constant(const APInt &v) {
    return b.create<arith::ConstantOp>(loc, word, b.getIntegerAttr(word, v));
  }
  /// The bit position of scalar `inner` of `leaf` (index value or constant).
  Value shift(const Leaf &leaf, Value inner, std::optional<int64_t> innerConst) {
    if (innerConst || !inner)
      return constant(APInt(word.getWidth(),
                            leaf.bitOffset +
                                leaf.scalarBits() * innerConst.value_or(0)));
    Value i = b.create<arith::IndexCastOp>(loc, word, inner);
    Value w = constant(APInt(word.getWidth(), leaf.scalarBits()));
    Value off = constant(APInt(word.getWidth(), leaf.bitOffset));
    return b.create<arith::AddIOp>(loc, b.create<arith::MulIOp>(loc, i, w),
                                   off);
  }
  /// The scalar of `leaf` at bit `sh` of `w`.
  Value extract(Value w, const Leaf &leaf, Value sh) {
    Value v = b.create<arith::ShRUIOp>(loc, w, sh);
    auto bits = b.getIntegerType(leaf.scalarBits());
    if (bits != word)
      v = b.create<arith::TruncIOp>(loc, bits, v);
    if (leaf.scalar != bits)
      v = b.create<arith::BitcastOp>(loc, leaf.scalar, v);
    return v;
  }
  /// `w` with the scalar `v` of `leaf` put at bit `sh`.
  Value insert(Value w, const Leaf &leaf, Value sh, Value v) {
    auto bits = b.getIntegerType(leaf.scalarBits());
    if (v.getType() != bits)
      v = b.create<arith::BitcastOp>(loc, bits, v);
    if (bits != word)
      v = b.create<arith::ExtUIOp>(loc, word, v);
    v = b.create<arith::ShLIOp>(loc, v, sh);
    if (!w)
      return v;
    Value ones = constant(APInt::getLowBitsSet(word.getWidth(),
                                               leaf.scalarBits()));
    Value mask = b.create<arith::ShLIOp>(loc, ones, sh);
    Value keep = b.create<arith::XOrIOp>(
        loc, mask, constant(APInt::getAllOnes(word.getWidth())));
    return b.create<arith::OrIOp>(loc, b.create<arith::AndIOp>(loc, w, keep),
                                  v);
  }
};
} // namespace

void StructSplitter::rewriteAggregated(ArrayRef<SmallVector<Value>> mems) {
  auto word = IntegerType::get(type.getContext(), wordBits);
  // Stores: the stores of one block to the same element with no other access
  // to the variable between them form one word write. When they write every
  // bit of the word it is a plain word store; otherwise the word is read
  // first (read-modify-write, VITIS_NOTES N37 S3).
  SmallVector<Access *> stores;
  for (Access &acc : accesses)
    if (acc.isStore())
      stores.push_back(&acc);
  DenseSet<Operation *> accessOps;
  for (Access &acc : accesses)
    accessOps.insert(acc.op);
  llvm::stable_sort(stores, [](Access *x, Access *y) {
    if (x->op->getBlock() != y->op->getBlock())
      return x->op->getBlock() < y->op->getBlock();
    return x->op->isBeforeInBlock(y->op);
  });
  auto touchesVariableBetween = [&](Operation *from, Operation *to) {
    if (from == to) // two scalars of one sub-aggregate store
      return false;
    for (Operation *o = from->getNextNode(); o && o != to;
         o = o->getNextNode()) {
      bool found = false;
      o->walk([&](Operation *inner) {
        if (accessOps.contains(inner))
          found = true;
      });
      if (found)
        return true;
    }
    return false;
  };
  auto sameElement = [](const Access *x, const Access *y) {
    if (x->root != y->root || x->element.size() != y->element.size())
      return false;
    for (auto [u, v] : llvm::zip(x->element, y->element))
      if (!sameValue(u, v))
        return false;
    return true;
  };
  // Group first, while the loads are still the original ops.
  SmallVector<SmallVector<Access *>> groups;
  for (size_t i = 0; i < stores.size();) {
    size_t j = i + 1;
    while (j < stores.size() &&
           stores[j]->op->getBlock() == stores[i]->op->getBlock() &&
           sameElement(stores[i], stores[j]) &&
           !touchesVariableBetween(stores[j - 1]->op, stores[j]->op))
      ++j;
    groups.emplace_back(stores.begin() + i, stores.begin() + j);
    i = j;
  }

  // Loads: a word load, then the member's bits. The members of one element
  // read in one block with no store to the variable in between share one
  // word read (Vitis reads the word once and shifts each member out).
  SmallVector<Access *> loads;
  DenseSet<Operation *> storeOps;
  for (Access &acc : accesses)
    (acc.isStore() ? storeOps.insert(acc.op), void()
                   : loads.push_back(&acc));
  llvm::stable_sort(loads, [](Access *x, Access *y) {
    if (x->op->getBlock() != y->op->getBlock())
      return x->op->getBlock() < y->op->getBlock();
    return x->op->isBeforeInBlock(y->op);
  });
  auto storeBetween = [&](Operation *from, Operation *to) {
    for (Operation *o = from->getNextNode(); o && o != to;
         o = o->getNextNode()) {
      bool found = false;
      o->walk([&](Operation *inner) {
        if (storeOps.contains(inner))
          found = true;
      });
      if (found)
        return true;
    }
    return false;
  };
  SmallVector<std::pair<Access *, Value>> wordReads;
  for (Access *accp : loads) {
    Access &acc = *accp;
    Operation *op = acc.op;
    OpBuilder ob(op);
    Location l = op->getLoc();
    WordBuilder wb{ob, l, word};
    Value w;
    for (auto &[prev, pw] : llvm::reverse(wordReads)) {
      Operation *anchor = pw.getDefiningOp();
      if (anchor->getBlock() != op->getBlock())
        break;
      if (sameElement(prev, &acc) && !storeBetween(anchor, op)) {
        w = pw;
        break;
      }
    }
    if (!w) {
      w = ob.create<memref::LoadOp>(l, mems[acc.root][0], acc.element);
      wordReads.push_back({&acc, w});
    }
    Value result;
    if (acc.leaf >= 0) {
      const Leaf &leaf = leaves[acc.leaf];
      result = wb.extract(w, leaf, wb.shift(leaf, acc.inner, acc.innerConst));
      if (!acc.part.empty()) {
        addPart(op, acc.part, result);
        compositeOps.insert(op);
        continue;
      }
    } else {
      result = ob.create<LLVM::UndefOp>(l, structType);
      for (const Leaf &leaf : leaves)
        for (int64_t f = 0, n = leaf.count(); f < n; ++f) {
          Value v = wb.extract(w, leaf, wb.shift(leaf, Value(), f));
          result = ob.create<LLVM::InsertValueOp>(
              l, result, v, valuePath(leaf, f));
        }
    }
    op->getResult(0).replaceAllUsesWith(result);
    op->erase();
  }

  for (ArrayRef<Access *> group : groups) {
    // Which bits the group writes (constant positions only).
    llvm::BitVector written(wordBits);
    for (Access *acc : group) {
      if (acc->leaf < 0) {
        written.set();
        continue;
      }
      const Leaf &leaf = leaves[acc->leaf];
      if (!acc->innerConst)
        continue;
      int64_t lo = leaf.bitOffset + leaf.scalarBits() * *acc->innerConst;
      written.set(lo, lo + leaf.scalarBits());
    }
    Operation *first = group.front()->op, *last = group.back()->op;
    Value w;
    if (!written.all()) {
      OpBuilder ob(first);
      w = ob.create<memref::LoadOp>(first->getLoc(),
                                    mems[group.front()->root][0],
                                    group.front()->element);
      w.getDefiningOp()->setAttr("hls.read_modify_write", ob.getUnitAttr());
    }
    OpBuilder ob(last);
    Location l = last->getLoc();
    WordBuilder wb{ob, l, word};
    for (Access *acc : group) {
      Value val = storedPart(ob, acc->op, acc->part);
      if (acc->leaf >= 0) {
        const Leaf &leaf = leaves[acc->leaf];
        w = wb.insert(w, leaf, wb.shift(leaf, acc->inner, acc->innerConst),
                      val);
        continue;
      }
      w = Value();
      for (const Leaf &leaf : leaves)
        for (int64_t f = 0, n = leaf.count(); f < n; ++f) {
          Value v = ob.create<LLVM::ExtractValueOp>(
              l, val, valuePath(leaf, f));
          w = wb.insert(w, leaf, wb.shift(leaf, Value(), f), v);
        }
    }
    auto st = ob.create<memref::StoreOp>(l, w, mems[group.back()->root][0],
                                         group.back()->element);
    if (group.size() > 1)
      st->setAttr("hls.merged_member_stores",
                  ob.getI64IntegerAttr(group.size()));
    for (Access *acc : group)
      compositeOps.insert(acc->op);
  }
  finishComposites();
}

void StructSplitter::cleanup() {
  for (Operation *op : llvm::reverse(derived))
    if (op->use_empty())
      op->erase();
  // Index arithmetic built for addresses no access ended up using.
  for (Operation *op : llvm::reverse(created))
    if (op->use_empty())
      op->erase();
}

//===----------------------------------------------------------------------===//
// Member functions that receive a view of the variable
//===----------------------------------------------------------------------===//

/// Whether every affine dimension / symbol operand inside `callee` stays
/// valid once the body is cloned into an arbitrary caller position: a
/// constant, an induction variable of an affine loop of the callee, or an
/// affine.apply of those. A callee argument used as a loop bound or symbol
/// would not be a valid symbol inside the caller's loop.
static bool affineOperandsStayValid(func::FuncOp callee) {
  std::function<bool(Value)> safe = [&](Value v) {
    if (matchPattern(v, m_Constant()))
      return true;
    if (auto ba = dyn_cast<BlockArgument>(v)) {
      Operation *owner = ba.getOwner()->getParentOp();
      return isa<affine::AffineForOp, affine::AffineParallelOp>(owner) &&
             callee->isProperAncestor(owner);
    }
    if (auto ap = v.getDefiningOp<affine::AffineApplyOp>())
      return llvm::all_of(ap.getMapOperands(), safe);
    return false;
  };
  WalkResult r = callee.walk([&](Operation *op) {
    if (!isa<affine::AffineDialect>(op->getDialect()))
      return WalkResult::advance();
    SmallVector<Value> operands;
    if (auto f = dyn_cast<affine::AffineForOp>(op)) {
      operands.append(f.getLowerBoundOperands().begin(),
                      f.getLowerBoundOperands().end());
      operands.append(f.getUpperBoundOperands().begin(),
                      f.getUpperBoundOperands().end());
    } else if (auto ld = dyn_cast<affine::AffineLoadOp>(op)) {
      operands.append(ld.getMapOperands().begin(), ld.getMapOperands().end());
    } else if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
      operands.append(st.getMapOperands().begin(), st.getMapOperands().end());
    } else if (isa<affine::AffineIfOp, affine::AffineApplyOp,
                   affine::AffineMinOp, affine::AffineMaxOp>(op)) {
      operands.append(op->getOperands().begin(), op->getOperands().end());
    } else if (!isa<affine::AffineYieldOp>(op)) {
      return WalkResult::interrupt();
    }
    for (Value v : operands)
      if (!safe(v))
        return WalkResult::interrupt();
    return WalkResult::advance();
  });
  return !r.wasInterrupted();
}

/// When `callee` copies the whole element its argument `src` points to into
/// the one `dst` points to, in one loop of scalar loads and stores at the
/// same position that covers the element exactly (the implicit copy / move
/// constructor or assignment of a trivially copyable struct, which cgeist
/// emits as a byte or member loop; clang emits a memcpy, which Vitis turns
/// into one aggregate copy), returns {dst, src}.
static std::optional<std::pair<unsigned, unsigned>>
wholeElementCopy(func::FuncOp callee) {
  if (callee.isExternal() || !llvm::hasSingleElement(callee.getBody()) ||
      callee.getNumArguments() != 2)
    return std::nullopt;
  auto structOf = [](Type t) -> LLVM::LLVMStructType {
    auto mt = dyn_cast<MemRefType>(t);
    return mt ? dyn_cast<LLVM::LLVMStructType>(mt.getElementType())
              : LLVM::LLVMStructType();
  };
  auto st = structOf(callee.getArgument(0).getType());
  if (!st || st != structOf(callee.getArgument(1).getType()))
    return std::nullopt;
  auto size = layoutOf(st);
  if (!size)
    return std::nullopt;
  Block &body = callee.getBody().front();
  DenseMap<Value, unsigned> argOfPointer;
  affine::AffineForOp loop;
  for (Operation &op : body) {
    if (auto m2p = dyn_cast<Memref2PointerOp>(op)) {
      auto arg = dyn_cast<BlockArgument>(m2p.getSource());
      if (!arg || arg.getOwner() != &body)
        return std::nullopt;
      argOfPointer[m2p.getResult()] = arg.getArgNumber();
      continue;
    }
    if (auto f = dyn_cast<affine::AffineForOp>(op)) {
      if (loop)
        return std::nullopt;
      loop = f;
      continue;
    }
    if (auto ret = dyn_cast<func::ReturnOp>(op)) {
      if (ret.getNumOperands() > 1)
        return std::nullopt;
      continue;
    }
    return std::nullopt;
  }
  if (!loop || !loop.hasConstantBounds() || loop.getConstantLowerBound() != 0 ||
      loop.getStepAsInt() != 1 || loop.getNumIterOperands() != 0)
    return std::nullopt;
  int64_t trips = loop.getConstantUpperBound();
  Value iv = loop.getInductionVar();
  auto isIv = [&](Value v) {
    while (auto c = v.getDefiningOp<arith::IndexCastOp>())
      v = c.getIn();
    return v == iv;
  };
  // gep(p)[iv] of one scalar type: the argument p belongs to.
  auto scalarAt = [&](Value ptr, Type &elem) -> std::optional<unsigned> {
    auto gep = ptr.getDefiningOp<LLVM::GEPOp>();
    if (!gep || gep.getIndices().size() != 1)
      return std::nullopt;
    auto idx = gep.getIndices()[0];
    if (!idx.is<Value>() || !isIv(idx.get<Value>()))
      return std::nullopt;
    auto it = argOfPointer.find(gep.getBase());
    if (it == argOfPointer.end())
      return std::nullopt;
    elem = gep.getElemType();
    return it->second;
  };
  LLVM::LoadOp load;
  LLVM::StoreOp store;
  for (Operation &op : loop.getBody()->without_terminator()) {
    if (isa<arith::IndexCastOp, LLVM::GEPOp>(op))
      continue;
    if (auto l = dyn_cast<LLVM::LoadOp>(op)) {
      if (load)
        return std::nullopt;
      load = l;
      continue;
    }
    if (auto s = dyn_cast<LLVM::StoreOp>(op)) {
      if (store)
        return std::nullopt;
      store = s;
      continue;
    }
    return std::nullopt;
  }
  if (!load || !store || store.getValue() != load.getResult())
    return std::nullopt;
  Type loadElem, storeElem;
  auto src = scalarAt(load.getAddr(), loadElem);
  auto dst = scalarAt(store.getAddr(), storeElem);
  if (!src || !dst || *src == *dst || loadElem != storeElem ||
      loadElem != load.getType())
    return std::nullopt;
  auto scalar = layoutOf(loadElem);
  if (!scalar || scalar->size * trips != size->size)
    return std::nullopt;
  if (auto ret = cast<func::ReturnOp>(body.getTerminator());
      ret.getNumOperands() == 1 && ret.getOperand(0) != callee.getArgument(*dst))
    return std::nullopt;
  return std::make_pair(*dst, *src);
}

/// Replaces a call of a whole-element copy (wholeElementCopy) by a load of
/// the source element and a store to the destination element.
static bool rewriteWholeElementCopy(func::CallOp call, func::FuncOp callee) {
  auto copy = wholeElementCopy(callee);
  if (!copy)
    return false;
  Value dst = call.getOperand(copy->first), src = call.getOperand(copy->second);
  auto rankOf = [](Value v) { return cast<MemRefType>(v.getType()).getRank(); };
  if (rankOf(dst) != 1 || rankOf(src) != 1)
    return false;
  OpBuilder b(call);
  Location loc = call.getLoc();
  Value zero = b.create<arith::ConstantIndexOp>(loc, 0);
  Value v = b.create<memref::LoadOp>(loc, src, ValueRange{zero});
  b.create<memref::StoreOp>(loc, v, dst, ValueRange{zero});
  for (Value r : call.getResults())
    r.replaceAllUsesWith(dst);
  call.erase();
  return true;
}

/// Inlines `call` when its callee is a defined, single-block function that
/// Vitis would inline (not `inline off`, not kept by cgeist): the struct
/// member functions cgeist emits (`operator[]`, `operator=`, copy
/// constructors, accessors taking `P &`). MLIR's inliner refuses them inside
/// an affine.for because of their llvm.load / llvm.store; Vitis inlines them
/// (they have no pragma and are small), and the member accesses must be seen
/// to split the array. A callee with loops is inlined only when its affine
/// operands stay valid in the caller. Returns true when inlined.
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
  if (rewriteWholeElementCopy(call, callee))
    return true;
  Block &body = callee.getBody().front();
  bool hasRegions = llvm::any_of(
      body, [](Operation &op) { return op.getNumRegions() != 0; });
  if (hasRegions && !affineOperandsStayValid(callee))
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

/// Inlines the calls that receive a view or pointer of `root` (see
/// inlineStructCall), until none is left or none can be inlined. True when
/// something was inlined.
static bool inlineCallsOnStruct(Value root) {
  DenseSet<Operation *> refused;
  bool changed = false;
  for (int round = 0; round < 256; ++round) {
    SmallVector<Value> work{root};
    DenseSet<Value> seen{root};
    func::CallOp found;
    while (!work.empty() && !found) {
      Value v = work.pop_back_val();
      for (Operation *user : v.getUsers()) {
        if (auto call = dyn_cast<func::CallOp>(user)) {
          if (!refused.contains(call)) {
            found = call;
            break;
          }
          continue;
        }
        if (isa<memref::CastOp, SubIndexOp, Memref2PointerOp, LLVM::GEPOp,
                Pointer2MemrefOp>(user))
          if (seen.insert(user->getResult(0)).second)
            work.push_back(user->getResult(0));
      }
    }
    if (!found)
      return changed;
    if (inlineStructCall(found))
      changed = true;
    else
      refused.insert(found);
  }
  return changed;
}

} // namespace

std::optional<int64_t> circt::hls_analysis::llvmStorageBits(Type type) {
  if (auto l = layoutOf(type))
    return l->size * 8;
  return std::nullopt;
}

namespace {

/// One storage of a struct-typed variable: an allocation, a global, or a
/// parameter of a function that a call passes the variable to whole.
struct VariableNode {
  enum Kind { Allocation, Global, Argument } kind;
  Operation *op = nullptr; // the allocation or the memref.global
  func::FuncOp fn;         // Argument: its function
  BlockArgument argValue;  // Argument: the parameter (its index changes as
                           // parameters are inserted)
  SmallVector<memref::GetGlobalOp> gets;
  std::unique_ptr<StructSplitter> splitter;
  bool analysed = false;
  std::string reason;
  unsigned group = 0;

  Location loc() const {
    return kind == Argument ? argValue.getLoc() : op->getLoc();
  }
  Attribute attr(StringRef name) {
    return kind == Argument ? fn.getArgAttr(argValue.getArgNumber(), name)
                            : op->getAttr(name);
  }
};

struct SplitStructMemrefsPass
    : PassWrapper<SplitStructMemrefsPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(SplitStructMemrefsPass)

  SplitStructMemrefsPass() = default;
  SplitStructMemrefsPass(const SplitStructMemrefsPass &other)
      : PassWrapper(other) {}

  Option<bool> honorAggregate{
      *this, "aggregate",
      llvm::cl::desc("A variable that carries hls.aggregate (an AGGREGATE "
                     "pragma reached it) becomes one memory of packed words "
                     "instead of one memory per leaf (VITIS_NOTES.md N37 "
                     "S2 / S3)"),
      llvm::cl::init(true)};
  Option<bool> globals{
      *this, "globals",
      llvm::cl::desc("Also split / aggregate struct-typed memref.globals "
                     "(VITIS_NOTES.md N37 S1)"),
      llvm::cl::init(true)};
  Option<bool> throughCalls{
      *this, "through-calls",
      llvm::cl::desc("Split / aggregate a variable passed whole to kept "
                     "calls together with the callees' parameters (one "
                     "variable, as Vitis sees it across `inline off` and "
                     "dataflow processes, VITIS_NOTES.md N37 S2 (b), S7)"),
      llvm::cl::init(true)};

  StringRef getArgument() const final { return "split-struct-memrefs"; }
  StringRef getDescription() const final {
    return "Split each struct-typed variable into one memref per member, as "
           "Vitis disaggregates it, or pack it into one word memref when an "
           "AGGREGATE pragma reaches it (VITIS_NOTES.md N29, N37)";
  }
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect,
                    affine::AffineDialect, LLVM::LLVMDialect>();
  }

  static bool isStructMemref(Type t) {
    auto mt = dyn_cast<MemRefType>(t);
    return mt && isa<LLVM::LLVMStructType>(mt.getElementType());
  }

  static std::string variableName(Operation *op, StringRef fallback) {
    if (auto n = op->getAttrOfType<StringAttr>("polygeist.varname"))
      return n.str();
    return fallback.str();
  }

  static void annotate(Operation *m, const NewMemory &mem, bool aggregate) {
    OpBuilder b(m->getContext());
    if (aggregate)
      m->setAttr("hls.aggregated", b.getStringAttr(mem.note));
    else
      m->setAttr("hls.struct_member", b.getStringAttr(mem.note));
  }

  /// The memref.globals of struct type whose every use is a get_global
  /// (nullopt reason) or why one is not.
  static std::optional<std::string>
  collectGets(memref::GlobalOp global, ModuleOp module,
              SmallVectorImpl<memref::GetGlobalOp> &gets) {
    auto init = global.getInitialValue();
    if (init && !isa<UnitAttr>(*init))
      return std::string("it has an initial value");
    auto uses = SymbolTable::getSymbolUses(global, module);
    if (!uses)
      return std::string("unknown symbol uses");
    for (const SymbolTable::SymbolUse &use : *uses) {
      auto get = dyn_cast<memref::GetGlobalOp>(use.getUser());
      if (!get)
        return "used by " + use.getUser()->getName().getStringRef().str();
      gets.push_back(get);
    }
    return std::nullopt;
  }

  /// Inlines the member functions every struct-typed storage reaches, until
  /// nothing changes (an inlined body can bring new temporaries).
  void inlineMemberCalls(ModuleOp module) {
    for (int round = 0; round < 16; ++round) {
      SmallVector<Value> roots;
      module.walk([&](Operation *op) {
        if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(op) &&
            isStructMemref(op->getResult(0).getType()))
          roots.push_back(op->getResult(0));
        if (auto fn = dyn_cast<func::FuncOp>(op))
          if (!fn.isExternal())
            for (BlockArgument a : fn.getArguments())
              if (isStructMemref(a.getType()))
                roots.push_back(a);
      });
      bool changed = false;
      for (Value r : roots)
        changed |= inlineCallsOnStruct(r);
      if (!changed)
        return;
    }
  }

  // State of one run.
  bool rowsSelected = false;
  DenseMap<std::pair<Operation *, unsigned>, VariableNode *> argNode;
  DenseMap<VariableNode *, SmallVector<SmallVector<Value>>> memsOf;
  SmallVector<VariableNode *> rewritten;
  SmallVector<Operation *> dead;

  void runOnOperation() override {
    ModuleOp module = getOperation();
    inlineMemberCalls(module);
    argNode.clear();
    memsOf.clear();
    rewritten.clear();
    dead.clear();
    rowsSelected = false;

    // The storages.
    SmallVector<std::unique_ptr<VariableNode>> nodes;
    module.walk([&](Operation *op) {
      if (isa<memref::AllocaOp, memref::AllocOp>(op) &&
          isStructMemref(op->getResult(0).getType())) {
        // A storage without a source variable name is a C++ temporary
        // cgeist materializes (a struct returned by value, e.g. from
        // hls::stream::read(), before it is copied into the variable). The
        // Vitis front end elides it or keeps it in registers: no memory
        // (hyungseok_bae_lab2, arati_ganesh lab2: no Vitis row for them).
        if (!op->hasAttr("polygeist.varname"))
          return;
        auto n = std::make_unique<VariableNode>();
        n->kind = VariableNode::Allocation;
        n->op = op;
        n->splitter = std::make_unique<StructSplitter>(
            SmallVector<Value>{op->getResult(0)},
            cast<MemRefType>(op->getResult(0).getType()), false,
            variableName(op, "s"));
        nodes.push_back(std::move(n));
        return;
      }
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        if (!globals || !isStructMemref(g.getType()))
          return;
        auto n = std::make_unique<VariableNode>();
        n->kind = VariableNode::Global;
        n->op = op;
        if (auto why = collectGets(g, module, n->gets)) {
          g.emitWarning("struct global not split into members: ") << *why;
          return;
        }
        if (n->gets.empty())
          return;
        SmallVector<Value> roots;
        for (memref::GetGlobalOp get : n->gets)
          roots.push_back(get.getResult());
        n->splitter = std::make_unique<StructSplitter>(
            roots, g.getType(), false, g.getSymName().str());
        nodes.push_back(std::move(n));
        return;
      }
      if (auto fn = dyn_cast<func::FuncOp>(op)) {
        if (!throughCalls || fn.isExternal())
          return;
        for (BlockArgument a : fn.getArguments()) {
          if (!isStructMemref(a.getType()))
            continue;
          auto n = std::make_unique<VariableNode>();
          n->kind = VariableNode::Argument;
          n->fn = fn;
          n->argValue = a;
          n->splitter = std::make_unique<StructSplitter>(
              SmallVector<Value>{a}, cast<MemRefType>(a.getType()), false,
              "arg");
          argNode[{fn.getOperation(), a.getArgNumber()}] = n.get();
          nodes.push_back(std::move(n));
        }
      }
    });
    for (auto &n : nodes) {
      n->analysed = n->splitter->analyse();
      if (!n->analysed)
        n->reason = n->splitter->reason;
    }

    // Variables: the storages connected by whole-variable call edges.
    DenseMap<VariableNode *, unsigned> index;
    for (auto [i, n] : llvm::enumerate(nodes))
      index[n.get()] = i;
    SmallVector<unsigned> parent(nodes.size());
    for (unsigned i = 0; i < nodes.size(); ++i)
      parent[i] = i;
    std::function<unsigned(unsigned)> find = [&](unsigned i) {
      return parent[i] == i ? i : parent[i] = find(parent[i]);
    };
    // Calls each argument node is reached by.
    DenseMap<VariableNode *, DenseSet<Operation *>> edgeCalls;
    for (auto &n : nodes) {
      if (!n->analysed)
        continue;
      for (StructSplitter::CallEdge &e : n->splitter->edges) {
        auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
            e.call, e.call.getCalleeAttr());
        VariableNode *target = argNode.lookup({callee.getOperation(), e.operand});
        if (!target) { // through-calls off: a kept call is an unknown use
          n->analysed = false;
          n->reason = ("struct array passed to the kept call @" +
                       e.call.getCallee())
                          .str();
          continue;
        }
        edgeCalls[target].insert(e.call);
        parent[find(index[n.get()])] = find(index[target]);
      }
    }
    DenseMap<unsigned, SmallVector<VariableNode *>> groups;
    for (auto &n : nodes)
      groups[find(index[n.get()])].push_back(n.get());

    for (auto &[id, group] : groups) {
      // A variable needs a storage (a parameter chain from a top-level
      // argument is an interface, not a memory).
      if (llvm::none_of(group, [](VariableNode *n) {
            return n->kind != VariableNode::Argument;
          }))
        continue;
      std::string why;
      for (VariableNode *n : group) {
        if (!n->analysed) {
          why = n->kind == VariableNode::Argument
                    ? "in @" + n->fn.getSymName().str() + ": " + n->reason
                    : n->reason;
          break;
        }
        if (n->kind != VariableNode::Argument)
          continue;
        // Every call of the function must pass this variable (or another
        // storage of the same variable) whole.
        auto uses = SymbolTable::getSymbolUses(n->fn, module);
        if (n->fn.isPublic() || !uses) {
          why = "passed to @" + n->fn.getSymName().str() +
                ", which is public or has unknown uses";
          break;
        }
        for (const SymbolTable::SymbolUse &u : *uses)
          if (!edgeCalls[n].contains(u.getUser())) {
            why = "passed to @" + n->fn.getSymName().str() +
                  ", which another call passes something else";
            break;
          }
        if (!why.empty())
          break;
      }
      bool aggregate = false, disaggregate = false;
      for (VariableNode *n : group) {
        aggregate |= honorAggregate && n->attr("hls.aggregate") != nullptr;
        disaggregate |= n->attr("hls.disaggregate") != nullptr;
      }
      if (!why.empty()) {
        for (VariableNode *n : group)
          if (n->kind != VariableNode::Argument)
            emitWarning(n->loc(), n->kind == VariableNode::Global
                                      ? "struct global not split into "
                                        "members: "
                                      : "struct array not split into "
                                        "members: ")
                << why;
        continue;
      }
      if (aggregate && disaggregate) {
        for (VariableNode *n : group)
          if (n->kind != VariableNode::Argument)
            emitError(n->loc(), "unsupported: conflicting aggregate and "
                                "disaggregate pragmas on one variable (Vitis "
                                "[HLS 214-258])");
        return signalPassFailure();
      }
      rewriteVariable(group, aggregate);
    }
    rewriteCalls();
    if (rowsSelected) {
      OpPassManager pm(ModuleOp::getOperationName());
      pm.addPass(createLowerSubIndexPass());
      if (failed(runPipeline(pm, module)))
        return signalPassFailure();
    }
  }

  /// Creates the new memories of every storage of one variable and
  /// rewrites its accesses (the calls that pass it: rewriteCalls).
  void rewriteVariable(ArrayRef<VariableNode *> group, bool aggregate) {
    for (VariableNode *n : group) {
      StructSplitter &s = *n->splitter;
      s.setAggregate(aggregate);
      SmallVector<NewMemory> news = s.newMemories();
      SmallVector<SmallVector<Value>> mems;
      switch (n->kind) {
      case VariableNode::Allocation: {
        OpBuilder b(n->op);
        SmallVector<Value> perRoot;
        for (const NewMemory &mem : news) {
          OperationState st(n->op->getLoc(), n->op->getName());
          st.addTypes(mem.type);
          st.addAttributes(n->op->getAttrs());
          Operation *m = b.create(st);
          m->setAttr("polygeist.varname", b.getStringAttr(mem.name));
          annotate(m, mem, aggregate);
          perRoot.push_back(m->getResult(0));
        }
        mems.push_back(std::move(perRoot));
        dead.push_back(n->op);
        break;
      }
      case VariableNode::Global: {
        auto global = cast<memref::GlobalOp>(n->op);
        SymbolTable symbols(global->getParentOp());
        OpBuilder b(global);
        NamedAttrList attrs(global->getAttrs());
        symbols.remove(global);
        SmallVector<memref::GlobalOp> created;
        for (const NewMemory &mem : news) {
          OperationState st(global.getLoc(), global->getName());
          st.addAttributes(attrs);
          auto g = cast<memref::GlobalOp>(b.create(st));
          g.setSymName(mem.name);
          g.setType(mem.type);
          annotate(g, mem, aggregate);
          symbols.insert(g, Block::iterator(global));
          created.push_back(g);
        }
        for (memref::GetGlobalOp get : n->gets) {
          OpBuilder gb(get);
          SmallVector<Value> perRoot;
          for (memref::GlobalOp g : created)
            perRoot.push_back(gb.create<memref::GetGlobalOp>(
                get.getLoc(), g.getType(), g.getSymName()));
          mems.push_back(std::move(perRoot));
          dead.push_back(get);
        }
        dead.push_back(global);
        break;
      }
      case VariableNode::Argument: {
        unsigned at = n->argValue.getArgNumber();
        DictionaryAttr attrs = n->fn.getArgAttrDict(at);
        Location loc = n->argValue.getLoc();
        SmallVector<Value> perRoot;
        for (auto [i, mem] : llvm::enumerate(news)) {
          n->fn.insertArgument(at + 1 + i, mem.type, attrs, loc);
          perRoot.push_back(n->fn.getArgument(at + 1 + i));
        }
        mems.push_back(std::move(perRoot));
        break;
      }
      }
      s.rewrite(mems);
      memsOf[n] = std::move(mems);
      rewritten.push_back(n);
    }
  }

  /// The calls that pass a rewritten variable: each such operand becomes the
  /// new memories (cast to the callee's new parameter types); then the old
  /// parameters, storages and get_globals go.
  void rewriteCalls() {
    DenseMap<Operation *,
             SmallVector<std::pair<unsigned, SmallVector<Value>>>>
        callOperands;
    SmallVector<Operation *> calls;
    for (VariableNode *n : rewritten)
      for (StructSplitter::CallEdge &e : n->splitter->edges) {
        auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
            e.call, e.call.getCalleeAttr());
        VariableNode *target = argNode.lookup({callee.getOperation(), e.operand});
        SmallVector<Value> vals;
        for (auto [m, want] :
             llvm::zip(memsOf[n][e.root], memsOf[target][0])) {
          Value v = m;
          OpBuilder b(e.call);
          // `f(a[k])`: the row of the new memory, as cgeist selects it
          // (--lower-polygeist-subindex, run again below, gives the callee
          // the whole memory and the row index).
          for (Value idx : e.lead) {
            auto mt = cast<MemRefType>(v.getType());
            auto row = MemRefType::get(mt.getShape().drop_front(),
                                       mt.getElementType());
            v = SubIndexOp::create(b, e.call.getLoc(), row, v, idx);
            rowsSelected = true;
          }
          if (v.getType() != want.getType())
            v = b.create<memref::CastOp>(e.call.getLoc(), want.getType(), v);
          vals.push_back(v);
        }
        if (!callOperands.count(e.call))
          calls.push_back(e.call);
        callOperands[e.call].push_back({e.operand, vals});
      }
    for (Operation *op : calls) {
      auto call = cast<func::CallOp>(op);
      auto &replaced = callOperands[op];
      SmallVector<Value> operands;
      for (auto [i, v] : llvm::enumerate(call.getOperands())) {
        auto it = llvm::find_if(replaced,
                                [&](auto &r) { return r.first == i; });
        if (it == replaced.end())
          operands.push_back(v);
        else
          operands.append(it->second.begin(), it->second.end());
      }
      OpBuilder b(call);
      auto nc = b.create<func::CallOp>(call.getLoc(), call.getCalleeAttr(),
                                       call.getResultTypes(), operands);
      for (NamedAttribute a : call->getDiscardableAttrs())
        nc->setDiscardableAttr(a.getName(), a.getValue());
      call.replaceAllUsesWith(nc.getResults());
      SmallVector<Value> oldOperands(call.getOperands());
      call.erase();
      // The views that only fed the old operands (casts, row selects).
      for (Value v : oldOperands)
        while (Operation *d = v.getDefiningOp()) {
          if (!isa<memref::CastOp, SubIndexOp>(d) || !d->use_empty())
            break;
          v = d->getOperand(0);
          d->erase();
        }
    }
    // Old parameters, highest index first.
    DenseMap<Operation *, SmallVector<BlockArgument>> oldArgs;
    for (VariableNode *n : rewritten)
      if (n->kind == VariableNode::Argument)
        oldArgs[n->fn.getOperation()].push_back(n->argValue);
    for (auto &[fnOp, args] : oldArgs) {
      auto fn = cast<func::FuncOp>(fnOp);
      llvm::sort(args, [](BlockArgument x, BlockArgument y) {
        return x.getArgNumber() > y.getArgNumber();
      });
      for (BlockArgument a : args)
        fn.eraseArgument(a.getArgNumber());
    }
    for (Operation *op : dead)
      if (isa<memref::GlobalOp>(op) || op->use_empty())
        op->erase();
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createSplitStructMemrefsPass() {
  return std::make_unique<SplitStructMemrefsPass>();
}

void circt::hls_analysis::registerSplitStructMemrefsPass() {
  PassRegistration<SplitStructMemrefsPass>();
}
