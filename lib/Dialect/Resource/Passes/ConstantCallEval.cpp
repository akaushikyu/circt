//===- ConstantCallEval.cpp - evaluate pure calls of constants ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See ConstantCallEval.h. Evidence: VITIS_NOTES N130 (kernels w9r17p_sq_*:
// `scale = (data_t)1.0 / hls::sqrt((data_t)4)` gives no sqrt core and a 15-bit
// `buf`; a scale Vitis cannot know keeps 16 bits) and N14 R8 (all-constant
// library calls are folded at compile time).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/ConstantCallEval.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/TypeSwitch.h"

#include "llvm/Support/Debug.h"

#include <optional>

#define DEBUG_TYPE "constant-call-eval"

using namespace mlir;

namespace {

/// One value of the interpreter: an integer (index as 64 bits), a float, or
/// LLVM's undefined value / poison (which may flow through arithmetic but
/// must not decide control flow or reach a result).
struct CVal {
  enum class Kind { Int, Float, Poison } kind = Kind::Poison;
  llvm::APInt i;
  llvm::APFloat f{0.0};

  static CVal ofInt(llvm::APInt v) {
    CVal c;
    c.kind = Kind::Int;
    c.i = std::move(v);
    return c;
  }
  static CVal ofFloat(llvm::APFloat v) {
    CVal c;
    c.kind = Kind::Float;
    c.f = std::move(v);
    return c;
  }
  static CVal poison() { return CVal(); }
  bool isInt() const { return kind == Kind::Int; }
  bool isFloat() const { return kind == Kind::Float; }
  bool isPoison() const { return kind == Kind::Poison; }
};

constexpr unsigned kIndexBits = 64;

static unsigned bitsOf(Type t) {
  if (t.isIndex())
    return kIndexBits;
  if (auto it = dyn_cast<IntegerType>(t))
    return it.getWidth();
  return 0;
}

/// The interpreter. Every method returns false when the evaluation has to
/// stop (an unsupported operation, an undefined decision, the step budget).
class Evaluator {
public:
  Evaluator(SymbolTableCollection &symbols, int64_t maxSteps)
      : symbols(symbols), stepsLeft(maxSteps) {}

  /// The contents of a local array the evaluation may read and write
  /// (foldConstantFillPrefixes): row-major elements, poison until stored.
  struct ArrayState {
    MemRefType type;
    std::vector<CVal> elems;
  };
  /// Enables loads and stores of the arrays in `a` (keyed by their alloca),
  /// and makes a value that is neither computed by the evaluation nor a
  /// constant stop it (instead of reading as poison).
  void enableArrays(DenseMap<Value, ArrayState> *a) {
    arrays = a;
    strictValues = true;
  }
  /// Runs one operation in `env` (the arrays enabled); false when it cannot
  /// be evaluated. `written` receives the arrays it stored to.
  bool runOp(Operation &op, DenseMap<Value, CVal> &env,
             SmallPtrSetImpl<Value> &written) {
    unknownSeen = false;
    writtenArrays = &written;
    bool ok = exec(op, env) && !unknownSeen;
    writtenArrays = nullptr;
    return ok;
  }

  /// Runs `fn` on `args`; `results` receives the returned values.
  bool call(func::FuncOp fn, ArrayRef<CVal> args, SmallVectorImpl<CVal> &results) {
    if (fn.isExternal() || ++depth > kMaxDepth) {
      --depth;
      return false;
    }
    Block &entry = fn.getBody().front();
    if (entry.getNumArguments() != args.size()) {
      --depth;
      return false;
    }
    DenseMap<Value, CVal> env;
    for (auto [a, v] : llvm::zip(entry.getArguments(), args))
      env[a] = v;
    bool ok = runRegionFrom(fn.getBody(), env, results);
    --depth;
    return ok;
  }

private:
  static constexpr unsigned kMaxDepth = 32;

  /// Runs a function body (possibly several blocks with cf branches is not
  /// supported: one block that ends in func.return).
  bool runRegionFrom(Region &r, DenseMap<Value, CVal> &env,
                     SmallVectorImpl<CVal> &results) {
    if (!r.hasOneBlock())
      return false;
    Operation *term = nullptr;
    if (!runBlock(r.front(), env, term))
      return false;
    auto ret = dyn_cast_or_null<func::ReturnOp>(term);
    if (!ret)
      return false;
    for (Value v : ret.getOperands())
      results.push_back(lookup(env, v));
    return true;
  }

  /// Runs the operations of `b` up to its terminator, which is returned
  /// unexecuted in `term` (the caller reads its operands).
  bool runBlock(Block &b, DenseMap<Value, CVal> &env, Operation *&term) {
    for (Operation &op : b) {
      if (op.hasTrait<OpTrait::IsTerminator>()) {
        term = &op;
        return true;
      }
      if (--stepsLeft < 0)
        return false;
      if (!exec(op, env)) {
        LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: stops at "
                                << op.getName() << " " << op.getLoc() << "\n");
        return false;
      }
    }
    return false;
  }

  /// Runs a single-block region with `args` bound to its arguments and
  /// collects the terminator's operands (a yield / condition).
  bool runNested(Region &r, ArrayRef<CVal> args, DenseMap<Value, CVal> &env,
                 SmallVectorImpl<CVal> &out, Operation **termOut = nullptr) {
    if (!r.hasOneBlock())
      return false;
    Block &b = r.front();
    if (b.getNumArguments() != args.size())
      return false;
    for (auto [a, v] : llvm::zip(b.getArguments(), args))
      env[a] = v;
    Operation *term = nullptr;
    if (!runBlock(b, env, term))
      return false;
    out.clear();
    for (Value v : term->getOperands())
      out.push_back(lookup(env, v));
    if (termOut)
      *termOut = term;
    return true;
  }

  CVal lookup(DenseMap<Value, CVal> &env, Value v) {
    auto it = env.find(v);
    if (it != env.end())
      return it->second;
    // A value defined outside the evaluated code (a constant hoisted out of
    // the callee by an earlier pass cannot happen; a block argument of an
    // enclosing function is never reached): only constants are read.
    if (auto c = v.getDefiningOp<arith::ConstantOp>())
      if (std::optional<CVal> cv = constantValue(c.getValue()))
        return *cv;
    if (strictValues)
      unknownSeen = true;
    return CVal::poison();
  }

  /// The element of a registered array at `indices`, nullopt when `mem` is
  /// not one or an index is unknown / outside the array.
  std::optional<size_t> elementIndex(Value mem, ArrayRef<int64_t> indices) {
    if (!arrays)
      return std::nullopt;
    auto it = arrays->find(mem);
    if (it == arrays->end())
      return std::nullopt;
    MemRefType t = it->second.type;
    if (static_cast<int64_t>(indices.size()) != t.getRank())
      return std::nullopt;
    int64_t linear = 0;
    for (auto [i, v] : llvm::enumerate(indices)) {
      int64_t extent = t.getShape()[i];
      if (v < 0 || v >= extent)
        return std::nullopt;
      linear = linear * extent + v;
    }
    return static_cast<size_t>(linear);
  }
  bool loadElement(Value mem, ArrayRef<int64_t> indices, Value result,
                   DenseMap<Value, CVal> &env) {
    std::optional<size_t> e = elementIndex(mem, indices);
    if (!e)
      return false;
    env[result] = (*arrays)[mem].elems[*e];
    return true;
  }
  bool storeElement(Value mem, ArrayRef<int64_t> indices, CVal v) {
    std::optional<size_t> e = elementIndex(mem, indices);
    if (!e)
      return false;
    (*arrays)[mem].elems[*e] = std::move(v);
    if (writtenArrays)
      writtenArrays->insert(mem);
    return true;
  }
  bool indexValues(ValueRange vs, DenseMap<Value, CVal> &env,
                   SmallVectorImpl<int64_t> &out) {
    out.clear();
    for (Value v : vs) {
      CVal c = lookup(env, v);
      if (!c.isInt())
        return false;
      out.push_back(c.i.getSExtValue());
    }
    return true;
  }

  static std::optional<CVal> constantValue(Attribute a) {
    if (auto ia = dyn_cast<IntegerAttr>(a)) {
      unsigned w = bitsOf(ia.getType());
      if (!w)
        return std::nullopt;
      return CVal::ofInt(ia.getValue().sextOrTrunc(w));
    }
    if (auto fa = dyn_cast<FloatAttr>(a))
      return CVal::ofFloat(fa.getValue());
    return std::nullopt;
  }

  /// The affine map `map` applied to `operands` (all integers).
  bool applyMap(AffineMap map, ValueRange operands, DenseMap<Value, CVal> &env,
                SmallVectorImpl<int64_t> &out) {
    SmallVector<Attribute> attrs;
    MLIRContext *ctx = map.getContext();
    for (Value v : operands) {
      CVal c = lookup(env, v);
      if (!c.isInt())
        return false;
      attrs.push_back(IntegerAttr::get(IndexType::get(ctx), c.i.getSExtValue()));
    }
    SmallVector<Attribute> res;
    if (failed(map.constantFold(attrs, res)))
      return false;
    out.clear();
    for (Attribute a : res) {
      auto ia = dyn_cast_or_null<IntegerAttr>(a);
      if (!ia)
        return false;
      out.push_back(ia.getInt());
    }
    return true;
  }

  bool exec(Operation &op, DenseMap<Value, CVal> &env);
  bool execInt(Operation &op, DenseMap<Value, CVal> &env);
  bool execFloat(Operation &op, DenseMap<Value, CVal> &env);

  SymbolTableCollection &symbols;
  int64_t stepsLeft;
  unsigned depth = 0;
  DenseMap<Value, ArrayState> *arrays = nullptr;
  bool strictValues = false, unknownSeen = false;
  SmallPtrSetImpl<Value> *writtenArrays = nullptr;
};

static CVal indexVal(int64_t v) {
  return CVal::ofInt(llvm::APInt(kIndexBits, v, /*isSigned=*/true));
}

bool Evaluator::execInt(Operation &op, DenseMap<Value, CVal> &env) {
  auto operand = [&](unsigned k) { return lookup(env, op.getOperand(k)); };
  auto setResult = [&](CVal v) {
    env[op.getResult(0)] = std::move(v);
    return true;
  };
  // Binary integer operations: poison in, poison out.
  auto binary = [&](auto fn) -> bool {
    CVal a = operand(0), b = operand(1);
    if (a.isPoison() || b.isPoison())
      return setResult(CVal::poison());
    if (!a.isInt() || !b.isInt())
      return false;
    std::optional<llvm::APInt> r = fn(a.i, b.i);
    if (!r)
      return false; // a division by zero: Vitis' N13 rules decide, not us
    return setResult(CVal::ofInt(*r));
  };
  using llvm::APInt;
  using Opt = std::optional<APInt>;
  return llvm::TypeSwitch<Operation *, bool>(&op)
      .Case([&](arith::AddIOp) { return binary([](APInt a, APInt b) -> Opt { return a + b; }); })
      .Case([&](arith::SubIOp) { return binary([](APInt a, APInt b) -> Opt { return a - b; }); })
      .Case([&](arith::MulIOp) { return binary([](APInt a, APInt b) -> Opt { return a * b; }); })
      .Case([&](arith::AndIOp) { return binary([](APInt a, APInt b) -> Opt { return a & b; }); })
      .Case([&](arith::OrIOp) { return binary([](APInt a, APInt b) -> Opt { return a | b; }); })
      .Case([&](arith::XOrIOp) { return binary([](APInt a, APInt b) -> Opt { return a ^ b; }); })
      .Case([&](arith::DivSIOp) {
        return binary([](APInt a, APInt b) -> Opt {
          if (b.isZero() || (a.isMinSignedValue() && b.isAllOnes()))
            return std::nullopt;
          return a.sdiv(b);
        });
      })
      .Case([&](arith::DivUIOp) {
        return binary([](APInt a, APInt b) -> Opt {
          if (b.isZero())
            return std::nullopt;
          return a.udiv(b);
        });
      })
      .Case([&](arith::RemSIOp) {
        return binary([](APInt a, APInt b) -> Opt {
          if (b.isZero() || (a.isMinSignedValue() && b.isAllOnes()))
            return std::nullopt;
          return a.srem(b);
        });
      })
      .Case([&](arith::RemUIOp) {
        return binary([](APInt a, APInt b) -> Opt {
          if (b.isZero())
            return std::nullopt;
          return a.urem(b);
        });
      })
      .Case([&](arith::MaxSIOp) { return binary([](APInt a, APInt b) -> Opt { return a.sge(b) ? a : b; }); })
      .Case([&](arith::MinSIOp) { return binary([](APInt a, APInt b) -> Opt { return a.sle(b) ? a : b; }); })
      .Case([&](arith::MaxUIOp) { return binary([](APInt a, APInt b) -> Opt { return a.uge(b) ? a : b; }); })
      .Case([&](arith::MinUIOp) { return binary([](APInt a, APInt b) -> Opt { return a.ule(b) ? a : b; }); })
      .Case([&](arith::ShLIOp) {
        CVal a = operand(0), b = operand(1);
        if (a.isPoison() || b.isPoison())
          return setResult(CVal::poison());
        if (!a.isInt() || !b.isInt())
          return false;
        // A shift by the width or more: cgeist narrows C's int shifts to the
        // operand's width, so the C value (of the wider type) is meant: all
        // bits shifted out (the sign bits for an arithmetic right shift).
        if (b.i.uge(a.i.getBitWidth()))
          return setResult(CVal::ofInt(llvm::APInt(a.i.getBitWidth(), 0)));
        return setResult(CVal::ofInt(a.i.shl(b.i.getZExtValue())));
      })
      .Case([&](arith::ShRUIOp) {
        CVal a = operand(0), b = operand(1);
        if (a.isPoison() || b.isPoison())
          return setResult(CVal::poison());
        if (!a.isInt() || !b.isInt())
          return false;
        // A shift by the width or more: cgeist narrows C's int shifts to the
        // operand's width, so the C value (of the wider type) is meant: all
        // bits shifted out (the sign bits for an arithmetic right shift).
        if (b.i.uge(a.i.getBitWidth()))
          return setResult(CVal::ofInt(llvm::APInt(a.i.getBitWidth(), 0)));
        return setResult(CVal::ofInt(a.i.lshr(b.i.getZExtValue())));
      })
      .Case([&](arith::ShRSIOp) {
        CVal a = operand(0), b = operand(1);
        if (a.isPoison() || b.isPoison())
          return setResult(CVal::poison());
        if (!a.isInt() || !b.isInt())
          return false;
        // A shift by the width or more: cgeist narrows C's int shifts to the
        // operand's width, so the C value (of the wider type) is meant: all
        // bits shifted out (the sign bits for an arithmetic right shift).
        if (b.i.uge(a.i.getBitWidth()))
          return setResult(CVal::ofInt((a.i.isNegative() ? llvm::APInt::getAllOnes(a.i.getBitWidth()) : llvm::APInt(a.i.getBitWidth(), 0))));
        return setResult(CVal::ofInt(a.i.ashr(b.i.getZExtValue())));
      })
      .Case([&](arith::ExtSIOp e) {
        CVal a = operand(0);
        if (!a.isInt())
          return a.isPoison() ? setResult(a) : false;
        return setResult(CVal::ofInt(a.i.sext(bitsOf(e.getType()))));
      })
      .Case([&](arith::ExtUIOp e) {
        CVal a = operand(0);
        if (!a.isInt())
          return a.isPoison() ? setResult(a) : false;
        return setResult(CVal::ofInt(a.i.zext(bitsOf(e.getType()))));
      })
      .Case([&](arith::TruncIOp e) {
        CVal a = operand(0);
        if (!a.isInt())
          return a.isPoison() ? setResult(a) : false;
        return setResult(CVal::ofInt(a.i.trunc(bitsOf(e.getType()))));
      })
      .Case([&](arith::IndexCastOp e) {
        CVal a = operand(0);
        if (!a.isInt())
          return a.isPoison() ? setResult(a) : false;
        return setResult(CVal::ofInt(a.i.sextOrTrunc(bitsOf(e.getType()))));
      })
      .Case([&](arith::IndexCastUIOp e) {
        CVal a = operand(0);
        if (!a.isInt())
          return a.isPoison() ? setResult(a) : false;
        return setResult(CVal::ofInt(a.i.zextOrTrunc(bitsOf(e.getType()))));
      })
      .Case([&](arith::CmpIOp c) {
        CVal a = operand(0), b = operand(1);
        if (a.isPoison() || b.isPoison())
          return setResult(CVal::poison());
        if (!a.isInt() || !b.isInt())
          return false;
        bool r = false;
        switch (c.getPredicate()) {
        case arith::CmpIPredicate::eq: r = a.i == b.i; break;
        case arith::CmpIPredicate::ne: r = a.i != b.i; break;
        case arith::CmpIPredicate::slt: r = a.i.slt(b.i); break;
        case arith::CmpIPredicate::sle: r = a.i.sle(b.i); break;
        case arith::CmpIPredicate::sgt: r = a.i.sgt(b.i); break;
        case arith::CmpIPredicate::sge: r = a.i.sge(b.i); break;
        case arith::CmpIPredicate::ult: r = a.i.ult(b.i); break;
        case arith::CmpIPredicate::ule: r = a.i.ule(b.i); break;
        case arith::CmpIPredicate::ugt: r = a.i.ugt(b.i); break;
        case arith::CmpIPredicate::uge: r = a.i.uge(b.i); break;
        }
        return setResult(CVal::ofInt(llvm::APInt(1, r ? 1 : 0)));
      })
      .Default([](Operation *) { return false; });
}

bool Evaluator::execFloat(Operation &op, DenseMap<Value, CVal> &env) {
  auto operand = [&](unsigned k) { return lookup(env, op.getOperand(k)); };
  auto setResult = [&](CVal v) {
    env[op.getResult(0)] = std::move(v);
    return true;
  };
  constexpr auto rm = llvm::APFloat::rmNearestTiesToEven;
  auto binary = [&](auto fn) -> bool {
    CVal a = operand(0), b = operand(1);
    if (a.isPoison() || b.isPoison())
      return setResult(CVal::poison());
    if (!a.isFloat() || !b.isFloat())
      return false;
    llvm::APFloat r = a.f;
    fn(r, b.f);
    return setResult(CVal::ofFloat(r));
  };
  // The float semantics of a float type.
  auto semantics = [](Type t) -> const llvm::fltSemantics * {
    if (auto ft = dyn_cast<FloatType>(t))
      return &ft.getFloatSemantics();
    return nullptr;
  };
  using llvm::APFloat;
  return llvm::TypeSwitch<Operation *, bool>(&op)
      .Case([&](arith::AddFOp) { return binary([&](APFloat &a, const APFloat &b) { a.add(b, rm); }); })
      .Case([&](arith::SubFOp) { return binary([&](APFloat &a, const APFloat &b) { a.subtract(b, rm); }); })
      .Case([&](arith::MulFOp) { return binary([&](APFloat &a, const APFloat &b) { a.multiply(b, rm); }); })
      .Case([&](arith::DivFOp) { return binary([&](APFloat &a, const APFloat &b) { a.divide(b, rm); }); })
      .Case([&](arith::NegFOp) {
        CVal a = operand(0);
        if (!a.isFloat())
          return a.isPoison() ? setResult(a) : false;
        llvm::APFloat r = a.f;
        r.changeSign();
        return setResult(CVal::ofFloat(r));
      })
      .Case([&](arith::CmpFOp c) {
        CVal a = operand(0), b = operand(1);
        if (a.isPoison() || b.isPoison())
          return setResult(CVal::poison());
        if (!a.isFloat() || !b.isFloat())
          return false;
        auto cmp = a.f.compare(b.f);
        bool unordered = cmp == llvm::APFloat::cmpUnordered;
        bool lt = cmp == llvm::APFloat::cmpLessThan;
        bool gt = cmp == llvm::APFloat::cmpGreaterThan;
        bool eq = cmp == llvm::APFloat::cmpEqual;
        bool r = false;
        using P = arith::CmpFPredicate;
        switch (c.getPredicate()) {
        case P::AlwaysFalse: r = false; break;
        case P::OEQ: r = eq; break;
        case P::OGT: r = gt; break;
        case P::OGE: r = gt || eq; break;
        case P::OLT: r = lt; break;
        case P::OLE: r = lt || eq; break;
        case P::ONE: r = lt || gt; break;
        case P::ORD: r = !unordered; break;
        case P::UEQ: r = unordered || eq; break;
        case P::UGT: r = unordered || gt; break;
        case P::UGE: r = unordered || gt || eq; break;
        case P::ULT: r = unordered || lt; break;
        case P::ULE: r = unordered || lt || eq; break;
        case P::UNE: r = !eq; break;
        case P::UNO: r = unordered; break;
        case P::AlwaysTrue: r = true; break;
        }
        return setResult(CVal::ofInt(llvm::APInt(1, r ? 1 : 0)));
      })
      .Case([&](arith::SIToFPOp e) {
        CVal a = operand(0);
        const llvm::fltSemantics *s = semantics(e.getType());
        if (!a.isInt() || !s)
          return a.isPoison() ? setResult(a) : false;
        llvm::APFloat r(*s);
        r.convertFromAPInt(a.i, /*IsSigned=*/true, rm);
        return setResult(CVal::ofFloat(r));
      })
      .Case([&](arith::UIToFPOp e) {
        CVal a = operand(0);
        const llvm::fltSemantics *s = semantics(e.getType());
        if (!a.isInt() || !s)
          return a.isPoison() ? setResult(a) : false;
        llvm::APFloat r(*s);
        r.convertFromAPInt(a.i, /*IsSigned=*/false, rm);
        return setResult(CVal::ofFloat(r));
      })
      .Case([&](arith::FPToSIOp e) {
        CVal a = operand(0);
        if (!a.isFloat())
          return a.isPoison() ? setResult(a) : false;
        llvm::APSInt r(bitsOf(e.getType()), /*isUnsigned=*/false);
        bool exact = false;
        if (a.f.convertToInteger(r, llvm::APFloat::rmTowardZero, &exact) &
            llvm::APFloat::opInvalidOp)
          return setResult(CVal::poison()); // out of range: poison
        return setResult(CVal::ofInt(r));
      })
      .Case([&](arith::FPToUIOp e) {
        CVal a = operand(0);
        if (!a.isFloat())
          return a.isPoison() ? setResult(a) : false;
        llvm::APSInt r(bitsOf(e.getType()), /*isUnsigned=*/true);
        bool exact = false;
        if (a.f.convertToInteger(r, llvm::APFloat::rmTowardZero, &exact) &
            llvm::APFloat::opInvalidOp)
          return setResult(CVal::poison());
        return setResult(CVal::ofInt(r));
      })
      .Case([&](arith::ExtFOp e) {
        CVal a = operand(0);
        const llvm::fltSemantics *s = semantics(e.getType());
        if (!a.isFloat() || !s)
          return a.isPoison() ? setResult(a) : false;
        llvm::APFloat r = a.f;
        bool lost = false;
        r.convert(*s, rm, &lost);
        return setResult(CVal::ofFloat(r));
      })
      .Case([&](arith::TruncFOp e) {
        CVal a = operand(0);
        const llvm::fltSemantics *s = semantics(e.getType());
        if (!a.isFloat() || !s)
          return a.isPoison() ? setResult(a) : false;
        llvm::APFloat r = a.f;
        bool lost = false;
        r.convert(*s, rm, &lost);
        return setResult(CVal::ofFloat(r));
      })
      .Case([&](arith::BitcastOp e) {
        CVal a = operand(0);
        if (a.isPoison())
          return setResult(a);
        if (const llvm::fltSemantics *s = semantics(e.getType())) {
          if (!a.isInt())
            return false;
          return setResult(CVal::ofFloat(llvm::APFloat(*s, a.i)));
        }
        if (!a.isFloat() || !bitsOf(e.getType()))
          return false;
        return setResult(CVal::ofInt(a.f.bitcastToAPInt()));
      })
      .Default([](Operation *) { return false; });
}

bool Evaluator::exec(Operation &op, DenseMap<Value, CVal> &env) {
  if (auto c = dyn_cast<arith::ConstantOp>(op)) {
    std::optional<CVal> v = constantValue(c.getValue());
    if (!v)
      return false;
    env[c.getResult()] = *v;
    return true;
  }
  if (isa<LLVM::UndefOp, LLVM::PoisonOp>(op)) {
    // An uninitialised variable (cgeist's undef for a declared ap_int that
    // the code then sets bit by bit): its value is a register's reset, 0.
    // The library code never lets the result depend on it.
    unsigned w = bitsOf(op.getResult(0).getType());
    if (w) {
      env[op.getResult(0)] = CVal::ofInt(llvm::APInt(w, 0));
      return true;
    }
    if (auto ft = dyn_cast<FloatType>(op.getResult(0).getType())) {
      env[op.getResult(0)] =
          CVal::ofFloat(llvm::APFloat::getZero(ft.getFloatSemantics()));
      return true;
    }
    env[op.getResult(0)] = CVal::poison();
    return true;
  }
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    CVal c = lookup(env, sel.getCondition());
    if (!c.isInt())
      return false; // an undefined condition decides nothing we can know
    env[sel.getResult()] = lookup(env, c.i.isZero() ? sel.getFalseValue()
                                                     : sel.getTrueValue());
    return true;
  }
  if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
    CVal c = lookup(env, ifOp.getCondition());
    if (!c.isInt())
      return false;
    Region &r = c.i.isZero() ? ifOp.getElseRegion() : ifOp.getThenRegion();
    SmallVector<CVal> out;
    if (r.empty()) {
      if (ifOp.getNumResults())
        return false;
      return true;
    }
    if (!runNested(r, {}, env, out) || out.size() != ifOp.getNumResults())
      return false;
    for (auto [res, v] : llvm::zip(ifOp.getResults(), out))
      env[res] = v;
    return true;
  }
  if (auto forOp = dyn_cast<scf::ForOp>(op)) {
    CVal lb = lookup(env, forOp.getLowerBound()),
         ub = lookup(env, forOp.getUpperBound()),
         st = lookup(env, forOp.getStep());
    if (!lb.isInt() || !ub.isInt() || !st.isInt() || !st.i.isStrictlyPositive())
      return false;
    const bool isUnsigned = false; // scf.for compares signed here
    SmallVector<CVal> iter;
    for (Value v : forOp.getInitArgs())
      iter.push_back(lookup(env, v));
    llvm::APInt iv = lb.i;
    while (isUnsigned ? iv.ult(ub.i) : iv.slt(ub.i)) {
      SmallVector<CVal> args{CVal::ofInt(iv)};
      args.append(iter);
      SmallVector<CVal> out;
      if (!runNested(forOp.getRegion(), args, env, out))
        return false;
      iter = out;
      bool overflow = false;
      iv = isUnsigned ? iv.uadd_ov(st.i, overflow) : iv.sadd_ov(st.i, overflow);
      if (overflow)
        break;
    }
    for (auto [res, v] : llvm::zip(forOp.getResults(), iter))
      env[res] = v;
    return true;
  }
  if (auto whileOp = dyn_cast<scf::WhileOp>(op)) {
    SmallVector<CVal> args;
    for (Value v : whileOp.getInits())
      args.push_back(lookup(env, v));
    while (true) {
      SmallVector<CVal> out;
      Operation *term = nullptr;
      if (!runNested(whileOp.getBefore(), args, env, out, &term))
        return false;
      auto cond = cast<scf::ConditionOp>(term);
      CVal c = lookup(env, cond.getCondition());
      if (!c.isInt())
        return false;
      SmallVector<CVal> fwd(out.begin() + 1, out.end());
      if (c.i.isZero()) {
        for (auto [res, v] : llvm::zip(whileOp.getResults(), fwd))
          env[res] = v;
        return true;
      }
      if (!runNested(whileOp.getAfter(), fwd, env, args))
        return false;
    }
  }
  if (auto forOp = dyn_cast<affine::AffineForOp>(op)) {
    SmallVector<int64_t> lbs, ubs;
    if (!applyMap(forOp.getLowerBoundMap(), forOp.getLowerBoundOperands(), env,
                  lbs) ||
        !applyMap(forOp.getUpperBoundMap(), forOp.getUpperBoundOperands(), env,
                  ubs) ||
        lbs.empty() || ubs.empty())
      return false;
    int64_t lb = *llvm::max_element(lbs), ub = *llvm::min_element(ubs);
    int64_t step = forOp.getStepAsInt();
    SmallVector<CVal> iter;
    for (Value v : forOp.getInits())
      iter.push_back(lookup(env, v));
    for (int64_t iv = lb; iv < ub; iv += step) {
      SmallVector<CVal> args{indexVal(iv)};
      args.append(iter);
      SmallVector<CVal> out;
      if (!runNested(forOp.getRegion(), args, env, out))
        return false;
      iter = out;
    }
    for (auto [res, v] : llvm::zip(forOp.getResults(), iter))
      env[res] = v;
    return true;
  }
  if (auto ifOp = dyn_cast<affine::AffineIfOp>(op)) {
    IntegerSet set = ifOp.getIntegerSet();
    SmallVector<int64_t> vals;
    AffineMap m = AffineMap::get(set.getNumDims(), set.getNumSymbols(),
                                 set.getConstraints(), set.getContext());
    if (!applyMap(m, ifOp.getOperands(), env, vals))
      return false;
    bool holds = true;
    for (unsigned k = 0; k < vals.size(); ++k)
      holds &= set.isEq(k) ? vals[k] == 0 : vals[k] >= 0;
    Region &r = holds ? ifOp.getThenRegion() : ifOp.getElseRegion();
    if (r.empty())
      return ifOp.getNumResults() == 0;
    SmallVector<CVal> out;
    if (!runNested(r, {}, env, out) || out.size() != ifOp.getNumResults())
      return false;
    for (auto [res, v] : llvm::zip(ifOp.getResults(), out))
      env[res] = v;
    return true;
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(op)) {
    SmallVector<int64_t> vals;
    if (!applyMap(apply.getAffineMap(), apply.getMapOperands(), env, vals) ||
        vals.size() != 1)
      return false;
    env[apply.getResult()] = indexVal(vals[0]);
    return true;
  }
  if (isa<affine::AffineMinOp, affine::AffineMaxOp>(op)) {
    bool isMin = isa<affine::AffineMinOp>(op);
    AffineMap map = isMin ? cast<affine::AffineMinOp>(op).getAffineMap()
                          : cast<affine::AffineMaxOp>(op).getAffineMap();
    SmallVector<int64_t> vals;
    if (!applyMap(map, op.getOperands(), env, vals) || vals.empty())
      return false;
    env[op.getResult(0)] = indexVal(isMin ? *llvm::min_element(vals)
                                          : *llvm::max_element(vals));
    return true;
  }
  if (arrays) {
    SmallVector<int64_t> idx;
    if (auto ld = dyn_cast<affine::AffineLoadOp>(op))
      return applyMap(ld.getAffineMap(), ld.getMapOperands(), env, idx) &&
             loadElement(ld.getMemRef(), idx, ld.getResult(), env);
    if (auto st = dyn_cast<affine::AffineStoreOp>(op))
      return applyMap(st.getAffineMap(), st.getMapOperands(), env, idx) &&
             storeElement(st.getMemRef(), idx,
                          lookup(env, st.getValueToStore()));
    if (auto ld = dyn_cast<memref::LoadOp>(op))
      return indexValues(ld.getIndices(), env, idx) &&
             loadElement(ld.getMemRef(), idx, ld.getResult(), env);
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return indexValues(st.getIndices(), env, idx) &&
             storeElement(st.getMemRef(), idx,
                          lookup(env, st.getValueToStore()));
  }
  if (auto call = dyn_cast<func::CallOp>(op)) {
    if (arrays)
      return false; // a call may touch the arrays through its operands
    auto callee = symbols.lookupNearestSymbolFrom<func::FuncOp>(
        call, call.getCalleeAttr());
    if (!callee)
      return false;
    SmallVector<CVal> args, results;
    for (Value v : call.getOperands())
      args.push_back(lookup(env, v));
    if (!this->call(callee, args, results) ||
        results.size() != call.getNumResults())
      return false;
    for (auto [res, v] : llvm::zip(call.getResults(), results))
      env[res] = v;
    return true;
  }
  if (op.getNumResults() != 1 || op.getNumRegions() != 0)
    return false;
  Type t = op.getResult(0).getType();
  if (isa<FloatType>(t) || isa<arith::CmpFOp, arith::FPToSIOp, arith::FPToUIOp,
                               arith::BitcastOp>(op))
    return execFloat(op, env);
  if (bitsOf(t))
    return execInt(op, env);
  return false;
}

/// A result of the evaluation as an attribute of `t`, or null.
static TypedAttr toAttr(const CVal &v, Type t) {
  if (v.isInt() && bitsOf(t) == v.i.getBitWidth())
    return IntegerAttr::get(t, v.i);
  if (v.isFloat())
    if (auto ft = dyn_cast<FloatType>(t))
      if (&ft.getFloatSemantics() == &v.f.getSemantics())
        return FloatAttr::get(t, v.f);
  return nullptr;
}

} // namespace

namespace circt::hls_analysis {

unsigned foldConstantCalls(ModuleOp module, int64_t maxSteps,
                           SmallVectorImpl<circt::hlsest::FoldNote> &notes) {
  SymbolTableCollection symbols;
  SmallVector<func::CallOp> candidates;
  module.walk([&](func::CallOp call) {
    if (call.getNumResults() == 0)
      return;
    for (Type t : call.getResultTypes())
      if (!bitsOf(t) && !isa<FloatType>(t))
        return;
    for (Value v : call.getOperands()) {
      auto c = v.getDefiningOp<arith::ConstantOp>();
      if (!c || (!isa<IntegerAttr>(c.getValue()) && !isa<FloatAttr>(c.getValue())))
        return;
    }
    candidates.push_back(call);
  });
  LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: " << candidates.size()
                          << " candidate call(s)\n");
  unsigned folded = 0;
  for (func::CallOp call : candidates) {
    auto callee = symbols.lookupNearestSymbolFrom<func::FuncOp>(
        call, call.getCalleeAttr());
    // A user `inline off` keeps a module whose output Vitis does not
    // propagate (unmeasured); an external function has no body.
    if (!callee || callee.isExternal() || callee->hasAttr("hls.inline_off"))
      continue;
    Evaluator ev(symbols, maxSteps);
    SmallVector<CVal> args, results;
    for (Value v : call.getOperands()) {
      Attribute a = v.getDefiningOp<arith::ConstantOp>().getValue();
      if (auto ia = dyn_cast<IntegerAttr>(a))
        args.push_back(CVal::ofInt(ia.getValue().sextOrTrunc(bitsOf(ia.getType()))));
      else
        args.push_back(CVal::ofFloat(cast<FloatAttr>(a).getValue()));
    }
    if (!ev.call(callee, args, results) ||
        results.size() != call.getNumResults()) {
      LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: not evaluated "
                              << callee.getSymName() << "\n");
      continue;
    }
    SmallVector<TypedAttr> attrs;
    for (auto [v, t] : llvm::zip(results, call.getResultTypes()))
      if (TypedAttr a = toAttr(v, t))
        attrs.push_back(a);
    if (attrs.size() != call.getNumResults()) {
      LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: undefined result of "
                              << callee.getSymName() << "\n");
      continue;
    }
    OpBuilder b(call);
    std::string detail;
    llvm::raw_string_ostream os(detail);
    StringRef name = callee.getSymName();
    if (auto orig = callee->getAttrOfType<StringAttr>("hls.orig_name"))
      name = orig.getValue();
    os << name << " of constant arguments evaluated:";
    for (auto [res, a] : llvm::zip(call.getResults(), attrs)) {
      os << " " << a;
      res.replaceAllUsesWith(b.create<arith::ConstantOp>(call.getLoc(), a));
    }
    std::string func;
    if (auto fn = call->getParentOfType<func::FuncOp>())
      func = fn.getName().str();
    notes.push_back({"constant-call", call.getLoc(), callee.getLoc(), os.str(),
                     func});
    call.erase();
    ++folded;
  }
  return folded;
}

/// Whether `op` (or an op nested in it) uses `mem` other than as the memref
/// of a load or store.
static bool onlyLoadsAndStores(Value mem) {
  for (OpOperand &use : mem.getUses()) {
    Operation *u = use.getOwner();
    if (auto ld = dyn_cast<affine::AffineLoadOp>(u); ld && ld.getMemRef() == mem)
      continue;
    if (auto st = dyn_cast<affine::AffineStoreOp>(u);
        st && st.getMemRef() == mem && st.getValueToStore() != mem)
      continue;
    if (auto ld = dyn_cast<memref::LoadOp>(u); ld && ld.getMemRef() == mem)
      continue;
    if (auto st = dyn_cast<memref::StoreOp>(u);
        st && st.getMemRef() == mem && st.getValueToStore() != mem)
      continue;
    return false;
  }
  return true;
}

/// Whether every dimension of `a` (of more than one element) is completely
/// partitioned by its pragmas: a register array (VITIS_NOTES N174 is about
/// such arrays; a plain filled array is a ROM, N26: held-out automl's
/// `weights` / `biases`, Vitis ROM_AUTO_1R).
static bool registerArray(memref::AllocaOp a) {
  auto spec = a->getAttrOfType<ArrayAttr>("hls.array_partition");
  if (!spec)
    return false;
  MemRefType t = a.getType();
  for (int64_t d = 0; d < t.getRank(); ++d) {
    if (t.getShape()[d] <= 1)
      continue;
    bool complete = llvm::any_of(spec, [&](Attribute e) {
      auto dict = dyn_cast<DictionaryAttr>(e);
      auto kind = dict ? dict.getAs<StringAttr>("kind") : StringAttr();
      auto dim = dict ? dict.getAs<IntegerAttr>("dim") : IntegerAttr();
      return kind && kind.getValue() == "complete" &&
             (!dim || dim.getInt() == 0 || dim.getInt() == d + 1);
    });
    if (!complete)
      return false;
  }
  return true;
}

/// The arrays among `cands` that `op` (or a nested op) stores to.
static void storedArrays(Operation *op, const DenseSet<Value> &cands,
                         SmallPtrSetImpl<Value> &out) {
  op->walk([&](Operation *x) {
    Value mem;
    if (auto st = dyn_cast<affine::AffineStoreOp>(x))
      mem = st.getMemRef();
    else if (auto st = dyn_cast<memref::StoreOp>(x))
      mem = st.getMemRef();
    if (mem && cands.contains(mem))
      out.insert(mem);
  });
}

unsigned foldConstantFillPrefixes(ModuleOp module, int64_t maxSteps,
                                  int64_t maxElements,
                                  SmallVectorImpl<circt::hlsest::FoldNote> &notes) {
  SymbolTableCollection symbols;
  unsigned folded = 0;
  unsigned globalCounter = 0;
  SmallVector<func::FuncOp> funcs(module.getOps<func::FuncOp>());
  for (func::FuncOp fn : funcs) {
    if (fn.isExternal() || !fn.getBody().hasOneBlock())
      continue;
    Block &entry = fn.getBody().front();
    // The local arrays: allocas of the entry block with a static shape of
    // integer or float elements, used only by loads and stores.
    DenseSet<Value> cands;
    DenseMap<Value, Evaluator::ArrayState> arrays;
    for (Operation &op : entry)
      if (auto a = dyn_cast<memref::AllocaOp>(op)) {
        MemRefType t = a.getType();
        if (!t.hasStaticShape() || !t.getLayout().isIdentity() ||
            t.getNumElements() > maxElements || !registerArray(a) ||
            !(isa<IntegerType>(t.getElementType()) ||
              isa<FloatType>(t.getElementType())) ||
            !onlyLoadsAndStores(a.getResult()))
          continue;
        cands.insert(a.getResult());
        arrays[a.getResult()] = {t, std::vector<CVal>(t.getNumElements())};
      }
    if (cands.empty())
      continue;
    Evaluator ev(symbols, maxSteps);
    ev.enableArrays(&arrays);
    DenseMap<Value, CVal> env;
    // Arrays some op that is not evaluated stores to: their contents are not
    // known from there on.
    DenseSet<Value> tainted;
    SmallVector<Operation *> evaluated;
    DenseMap<Operation *, SmallPtrSet<Value, 4>> writesOf;
    for (Operation &op : entry) {
      if (op.hasTrait<OpTrait::IsTerminator>() || isa<memref::AllocaOp>(op))
        continue;
      if (isa<arith::ConstantOp>(op)) {
        (void)ev.runOp(op, env, writesOf[&op]);
        continue;
      }
      // Only ops that touch a candidate array or produce values are worth
      // evaluating; a loop that reads a tainted array cannot be.
      SmallPtrSet<Value, 4> stores;
      storedArrays(&op, cands, stores);
      // A side-effect-free op outside the loops (a bound, an index): its
      // value when it has one.
      if (stores.empty()) {
        SmallPtrSet<Value, 4> none;
        if (op.getNumRegions() == 0 && isMemoryEffectFree(&op) &&
            !ev.runOp(op, env, none))
          for (Value r : op.getResults())
            env.erase(r);
        continue;
      }
      bool readsTainted = false;
      op.walk([&](Operation *x) {
        for (Value v : x->getOperands())
          if (tainted.contains(v))
            readsTainted = true;
      });
      DenseMap<Value, Evaluator::ArrayState> before;
      for (Value m : stores)
        before[m] = arrays[m];
      SmallPtrSet<Value, 4> written;
      bool ok = !readsTainted && ev.runOp(op, env, written);
      if (ok) {
        evaluated.push_back(&op);
        writesOf[&op] = written;
        continue;
      }
      // Undo partial writes; the arrays it may store to are unknown now.
      for (auto &[m, st] : before)
        arrays[m] = st;
      for (Value m : stores)
        tainted.insert(m);
      for (Value r : op.getResults())
        env.erase(r);
    }
    // Arrays to fold: written by an evaluated op, never by anything else.
    DenseSet<Value> fold;
    for (Operation *op : evaluated)
      for (Value m : writesOf[op])
        if (!tainted.contains(m))
          fold.insert(m);
    // An evaluated op that stores to an array that is not folded stays, so
    // every array it stores to stays (it would store into a constant).
    bool changed = true;
    DenseSet<Operation *> keep;
    while (changed) {
      changed = false;
      for (Operation *op : evaluated) {
        if (keep.contains(op))
          continue;
        SmallPtrSet<Value, 4> stores;
        storedArrays(op, cands, stores);
        bool keepOp = llvm::any_of(stores, [&](Value m) {
          return !fold.contains(m);
        });
        // A result that is no constant keeps the op.
        for (Value r : op->getResults()) {
          auto it = env.find(r);
          if (it == env.end() || !(it->second.isInt() || it->second.isFloat()))
            keepOp = true;
        }
        if (keepOp) {
          keep.insert(op);
          for (Value m : stores)
            changed |= fold.erase(m);
        }
      }
    }
    if (fold.empty())
      continue;
    OpBuilder b(module.getContext());
    // The evaluated ops that go: results become constants.
    for (Operation *op : evaluated) {
      if (keep.contains(op))
        continue;
      b.setInsertionPoint(op);
      for (Value r : op->getResults()) {
        TypedAttr a = toAttr(env[r], r.getType());
        if (!a) {
          if (auto it = dyn_cast<IndexType>(r.getType()); it && env[r].isInt())
            a = IntegerAttr::get(it, env[r].i.getSExtValue());
        }
        if (!a)
          continue; // unreachable: keepOp checked the kinds
        r.replaceAllUsesWith(b.create<arith::ConstantOp>(op->getLoc(), a));
      }
    }
    for (Operation *op : evaluated)
      if (!keep.contains(op))
        op->erase();
    // Each folded array becomes a constant global of its contents (an element
    // never stored reads as 0, the reset value).
    for (Value m : fold) {
      auto alloca = m.getDefiningOp<memref::AllocaOp>();
      Evaluator::ArrayState &st = arrays[m];
      Type elt = st.type.getElementType();
      SmallVector<Attribute> vals;
      for (const CVal &v : st.elems) {
        Attribute a;
        if (auto it = dyn_cast<IntegerType>(elt))
          a = IntegerAttr::get(
              it, v.isInt() && v.i.getBitWidth() == it.getWidth()
                      ? v.i
                      : llvm::APInt(it.getWidth(), 0));
        else {
          auto ft = cast<FloatType>(elt);
          a = FloatAttr::get(
              ft, v.isFloat() && &v.f.getSemantics() == &ft.getFloatSemantics()
                      ? v.f
                      : llvm::APFloat::getZero(ft.getFloatSemantics()));
        }
        vals.push_back(a);
      }
      auto tensorTy = RankedTensorType::get(st.type.getShape(), elt);
      auto init = DenseElementsAttr::get(tensorTy, vals);
      std::string name = (fn.getName() + "__hls_const_fill_" +
                          llvm::Twine(globalCounter++))
                             .str();
      b.setInsertionPoint(fn);
      auto global = b.create<memref::GlobalOp>(
          alloca.getLoc(), name, b.getStringAttr("private"), st.type, init,
          /*constant=*/true, /*alignment=*/IntegerAttr());
      // Keep what the reports read off the array (its name, pragmas).
      for (NamedAttribute na : alloca->getAttrs())
        if (na.getName().getValue().starts_with("polygeist.") ||
            na.getName().getValue().starts_with("hls."))
          global->setAttr(na.getName(), na.getValue());
      global->setAttr("hls.constant_fill_evaluated",
                      b.getUnitAttr());
      b.setInsertionPoint(alloca);
      auto get = b.create<memref::GetGlobalOp>(alloca.getLoc(), st.type,
                                               global.getSymName());
      alloca.getResult().replaceAllUsesWith(get.getResult());
      std::string detail;
      llvm::raw_string_ostream os(detail);
      StringRef var = "array";
      if (auto v = alloca->getAttrOfType<StringAttr>("polygeist.varname"))
        var = v.getValue();
      os << var << " filled from constants by loops evaluated at compile "
         << "time: a constant table (N174)";
      notes.push_back({"constant-fill-loops", alloca.getLoc(), alloca.getLoc(),
                       os.str(), fn.getName().str()});
      alloca.erase();
      ++folded;
    }
    // A folded table nothing reads any more is deleted.
    for (memref::GlobalOp g :
         llvm::make_early_inc_range(module.getOps<memref::GlobalOp>()))
      if (g->hasAttr("hls.constant_fill_evaluated") &&
          SymbolTable::symbolKnownUseEmpty(g, module))
        g.erase();
    for (Operation &op : llvm::make_early_inc_range(entry))
      if (auto get = dyn_cast<memref::GetGlobalOp>(op))
        if (get.getResult().use_empty())
          if (auto g = symbols.lookupNearestSymbolFrom<memref::GlobalOp>(
                  get, get.getNameAttr());
              g && g->hasAttr("hls.constant_fill_evaluated")) {
            get.erase();
            if (SymbolTable::symbolKnownUseEmpty(g, module))
              g.erase();
          }
  }
  return folded;
}

} // namespace circt::hls_analysis
