

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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

  static CVal ofInt(llvm::APInt valueHandle) {
    CVal candidateValue;
    candidateValue.kind = Kind::Int;
    candidateValue.i = std::move(valueHandle);
    return candidateValue;
  }
  static CVal ofFloat(llvm::APFloat valueHandle) {
    CVal candidateValue;
    candidateValue.kind = Kind::Float;
    candidateValue.f = std::move(valueHandle);
    return candidateValue;
  }
  static CVal poison() { return CVal(); }
  bool isInt() const { return kind == Kind::Int; }
  bool isFloat() const { return kind == Kind::Float; }
  bool isPoison() const { return kind == Kind::Poison; }
};

constexpr unsigned kIndexBits = 64;

static unsigned bitsOf(Type typeValue) {
  if (typeValue.isIndex())
    return kIndexBits;
  if (auto it = dyn_cast<IntegerType>(typeValue))
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
  void enableArrays(DenseMap<Value, ArrayState> *arrayValue) {
    arrays = arrayValue;
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
  bool call(func::FuncOp fn, ArrayRef<CVal> args,
            SmallVectorImpl<CVal> &results) {
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
    for (auto [arrayValue, valueHandle] : llvm::zip(entry.getArguments(), args))
      env[arrayValue] = valueHandle;
    bool ok = runRegionFrom(fn.getBody(), env, results);
    --depth;
    return ok;
  }

private:
  static constexpr unsigned kMaxDepth = 32;

  /// Runs a function body (possibly several blocks with cf branches is not
  /// supported: one block that ends in func.return).
  bool runRegionFrom(Region &resultValue, DenseMap<Value, CVal> &env,
                     SmallVectorImpl<CVal> &results) {
    if (!resultValue.hasOneBlock())
      return false;
    Operation *term = nullptr;
    if (!runBlock(resultValue.front(), env, term))
      return false;
    auto returnOp = dyn_cast_or_null<func::ReturnOp>(term);
    if (!returnOp)
      return false;
    for (Value valueHandle : returnOp.getOperands())
      results.push_back(lookup(env, valueHandle));
    return true;
  }

  /// Runs the operations of `b` up to its terminator, which is returned
  /// unexecuted in `term` (the caller reads its operands).
  bool runBlock(Block &buildPoint, DenseMap<Value, CVal> &env,
                Operation *&term) {
    for (Operation &op : buildPoint) {
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
  bool runNested(Region &resultValue, ArrayRef<CVal> args,
                 DenseMap<Value, CVal> &env, SmallVectorImpl<CVal> &out,
                 Operation **termOut = nullptr) {
    if (!resultValue.hasOneBlock())
      return false;
    Block &buildPoint = resultValue.front();
    if (buildPoint.getNumArguments() != args.size())
      return false;
    for (auto [arrayValue, valueHandle] :
         llvm::zip(buildPoint.getArguments(), args))
      env[arrayValue] = valueHandle;
    Operation *term = nullptr;
    if (!runBlock(buildPoint, env, term))
      return false;
    out.clear();
    for (Value valueHandle : term->getOperands())
      out.push_back(lookup(env, valueHandle));
    if (termOut)
      *termOut = term;
    return true;
  }

  CVal lookup(DenseMap<Value, CVal> &env, Value valueHandle) {
    auto it = env.find(valueHandle);
    if (it != env.end())
      return it->second;

    if (auto candidateValue = valueHandle.getDefiningOp<arith::ConstantOp>())
      if (std::optional<CVal> cv = constantValue(candidateValue.getValue()))
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
    MemRefType typeValue = it->second.type;
    if (static_cast<int64_t>(indices.size()) != typeValue.getRank())
      return std::nullopt;
    int64_t linear = 0;
    for (auto [i, valueHandle] : llvm::enumerate(indices)) {
      int64_t extent = typeValue.getShape()[i];
      if (valueHandle < 0 || valueHandle >= extent)
        return std::nullopt;
      linear = linear * extent + valueHandle;
    }
    return static_cast<size_t>(linear);
  }
  bool loadElement(Value mem, ArrayRef<int64_t> indices, Value result,
                   DenseMap<Value, CVal> &env) {
    std::optional<size_t> entryValue = elementIndex(mem, indices);
    if (!entryValue)
      return false;
    env[result] = (*arrays)[mem].elems[*entryValue];
    return true;
  }
  bool storeElement(Value mem, ArrayRef<int64_t> indices, CVal valueHandle) {
    std::optional<size_t> entryValue = elementIndex(mem, indices);
    if (!entryValue)
      return false;
    (*arrays)[mem].elems[*entryValue] = std::move(valueHandle);
    if (writtenArrays)
      writtenArrays->insert(mem);
    return true;
  }
  bool indexValues(ValueRange vs, DenseMap<Value, CVal> &env,
                   SmallVectorImpl<int64_t> &out) {
    out.clear();
    for (Value valueHandle : vs) {
      CVal candidateValue = lookup(env, valueHandle);
      if (!candidateValue.isInt())
        return false;
      out.push_back(candidateValue.i.getSExtValue());
    }
    return true;
  }

  static std::optional<CVal> constantValue(Attribute arrayValue) {
    if (auto ia = dyn_cast<IntegerAttr>(arrayValue)) {
      unsigned widthValue = bitsOf(ia.getType());
      if (!widthValue)
        return std::nullopt;
      return CVal::ofInt(ia.getValue().sextOrTrunc(widthValue));
    }
    if (auto fa = dyn_cast<FloatAttr>(arrayValue))
      return CVal::ofFloat(fa.getValue());
    return std::nullopt;
  }

  /// The affine map `map` applied to `operands` (all integers).
  bool applyMap(AffineMap map, ValueRange operands, DenseMap<Value, CVal> &env,
                SmallVectorImpl<int64_t> &out) {
    SmallVector<Attribute> attrs;
    MLIRContext *context = map.getContext();
    for (Value valueHandle : operands) {
      CVal candidateValue = lookup(env, valueHandle);
      if (!candidateValue.isInt())
        return false;
      attrs.push_back(IntegerAttr::get(IndexType::get(context),
                                       candidateValue.i.getSExtValue()));
    }
    SmallVector<Attribute> passResult;
    if (failed(map.constantFold(attrs, passResult)))
      return false;
    out.clear();
    for (Attribute arrayValue : passResult) {
      auto ia = dyn_cast_or_null<IntegerAttr>(arrayValue);
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

static CVal indexVal(int64_t valueHandle) {
  return CVal::ofInt(llvm::APInt(kIndexBits, valueHandle, true));
}

bool Evaluator::execInt(Operation &op, DenseMap<Value, CVal> &env) {
  auto operand = [&](unsigned keyValue) {
    return lookup(env, op.getOperand(keyValue));
  };
  auto setResult = [&](CVal valueHandle) {
    env[op.getResult(0)] = std::move(valueHandle);
    return true;
  };

  auto binary = [&](auto fn) -> bool {
    CVal arrayValue = operand(0), buildPoint = operand(1);
    if (arrayValue.isPoison() || buildPoint.isPoison())
      return setResult(CVal::poison());
    if (!arrayValue.isInt() || !buildPoint.isInt())
      return false;
    std::optional<llvm::APInt> resultValue = fn(arrayValue.i, buildPoint.i);
    if (!resultValue)
      return false;
    return setResult(CVal::ofInt(*resultValue));
  };
  using llvm::APInt;
  using Opt = std::optional<APInt>;
  return llvm::TypeSwitch<Operation *, bool>(&op)
      .Case([&](arith::AddIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue + buildPoint;
        });
      })
      .Case([&](arith::SubIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue - buildPoint;
        });
      })
      .Case([&](arith::MulIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue * buildPoint;
        });
      })
      .Case([&](arith::AndIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue & buildPoint;
        });
      })
      .Case([&](arith::OrIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue | buildPoint;
        });
      })
      .Case([&](arith::XOrIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue ^ buildPoint;
        });
      })
      .Case([&](arith::DivSIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          if (buildPoint.isZero() ||
              (arrayValue.isMinSignedValue() && buildPoint.isAllOnes()))
            return std::nullopt;
          return arrayValue.sdiv(buildPoint);
        });
      })
      .Case([&](arith::DivUIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          if (buildPoint.isZero())
            return std::nullopt;
          return arrayValue.udiv(buildPoint);
        });
      })
      .Case([&](arith::RemSIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          if (buildPoint.isZero() ||
              (arrayValue.isMinSignedValue() && buildPoint.isAllOnes()))
            return std::nullopt;
          return arrayValue.srem(buildPoint);
        });
      })
      .Case([&](arith::RemUIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          if (buildPoint.isZero())
            return std::nullopt;
          return arrayValue.urem(buildPoint);
        });
      })
      .Case([&](arith::MaxSIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue.sge(buildPoint) ? arrayValue : buildPoint;
        });
      })
      .Case([&](arith::MinSIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue.sle(buildPoint) ? arrayValue : buildPoint;
        });
      })
      .Case([&](arith::MaxUIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue.uge(buildPoint) ? arrayValue : buildPoint;
        });
      })
      .Case([&](arith::MinUIOp) {
        return binary([](APInt arrayValue, APInt buildPoint) -> Opt {
          return arrayValue.ule(buildPoint) ? arrayValue : buildPoint;
        });
      })
      .Case([&](arith::ShLIOp) {
        CVal arrayValue = operand(0), buildPoint = operand(1);
        if (arrayValue.isPoison() || buildPoint.isPoison())
          return setResult(CVal::poison());
        if (!arrayValue.isInt() || !buildPoint.isInt())
          return false;

        if (buildPoint.i.uge(arrayValue.i.getBitWidth()))
          return setResult(
              CVal::ofInt(llvm::APInt(arrayValue.i.getBitWidth(), 0)));
        return setResult(
            CVal::ofInt(arrayValue.i.shl(buildPoint.i.getZExtValue())));
      })
      .Case([&](arith::ShRUIOp) {
        CVal arrayValue = operand(0), buildPoint = operand(1);
        if (arrayValue.isPoison() || buildPoint.isPoison())
          return setResult(CVal::poison());
        if (!arrayValue.isInt() || !buildPoint.isInt())
          return false;

        if (buildPoint.i.uge(arrayValue.i.getBitWidth()))
          return setResult(
              CVal::ofInt(llvm::APInt(arrayValue.i.getBitWidth(), 0)));
        return setResult(
            CVal::ofInt(arrayValue.i.lshr(buildPoint.i.getZExtValue())));
      })
      .Case([&](arith::ShRSIOp) {
        CVal arrayValue = operand(0), buildPoint = operand(1);
        if (arrayValue.isPoison() || buildPoint.isPoison())
          return setResult(CVal::poison());
        if (!arrayValue.isInt() || !buildPoint.isInt())
          return false;

        if (buildPoint.i.uge(arrayValue.i.getBitWidth()))
          return setResult(CVal::ofInt(
              (arrayValue.i.isNegative()
                   ? llvm::APInt::getAllOnes(arrayValue.i.getBitWidth())
                   : llvm::APInt(arrayValue.i.getBitWidth(), 0))));
        return setResult(
            CVal::ofInt(arrayValue.i.ashr(buildPoint.i.getZExtValue())));
      })
      .Case([&](arith::ExtSIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isInt())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        return setResult(
            CVal::ofInt(arrayValue.i.sext(bitsOf(entryValue.getType()))));
      })
      .Case([&](arith::ExtUIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isInt())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        return setResult(
            CVal::ofInt(arrayValue.i.zext(bitsOf(entryValue.getType()))));
      })
      .Case([&](arith::TruncIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isInt())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        return setResult(
            CVal::ofInt(arrayValue.i.trunc(bitsOf(entryValue.getType()))));
      })
      .Case([&](arith::IndexCastOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isInt())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        return setResult(CVal::ofInt(
            arrayValue.i.sextOrTrunc(bitsOf(entryValue.getType()))));
      })
      .Case([&](arith::IndexCastUIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isInt())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        return setResult(CVal::ofInt(
            arrayValue.i.zextOrTrunc(bitsOf(entryValue.getType()))));
      })
      .Case([&](arith::CmpIOp candidateValue) {
        CVal arrayValue = operand(0), buildPoint = operand(1);
        if (arrayValue.isPoison() || buildPoint.isPoison())
          return setResult(CVal::poison());
        if (!arrayValue.isInt() || !buildPoint.isInt())
          return false;
        bool resultValue = false;
        switch (candidateValue.getPredicate()) {
        case arith::CmpIPredicate::eq:
          resultValue = arrayValue.i == buildPoint.i;
          break;
        case arith::CmpIPredicate::ne:
          resultValue = arrayValue.i != buildPoint.i;
          break;
        case arith::CmpIPredicate::slt:
          resultValue = arrayValue.i.slt(buildPoint.i);
          break;
        case arith::CmpIPredicate::sle:
          resultValue = arrayValue.i.sle(buildPoint.i);
          break;
        case arith::CmpIPredicate::sgt:
          resultValue = arrayValue.i.sgt(buildPoint.i);
          break;
        case arith::CmpIPredicate::sge:
          resultValue = arrayValue.i.sge(buildPoint.i);
          break;
        case arith::CmpIPredicate::ult:
          resultValue = arrayValue.i.ult(buildPoint.i);
          break;
        case arith::CmpIPredicate::ule:
          resultValue = arrayValue.i.ule(buildPoint.i);
          break;
        case arith::CmpIPredicate::ugt:
          resultValue = arrayValue.i.ugt(buildPoint.i);
          break;
        case arith::CmpIPredicate::uge:
          resultValue = arrayValue.i.uge(buildPoint.i);
          break;
        }
        return setResult(CVal::ofInt(llvm::APInt(1, resultValue ? 1 : 0)));
      })
      .Default([](Operation *) { return false; });
}

bool Evaluator::execFloat(Operation &op, DenseMap<Value, CVal> &env) {
  auto operand = [&](unsigned keyValue) {
    return lookup(env, op.getOperand(keyValue));
  };
  auto setResult = [&](CVal valueHandle) {
    env[op.getResult(0)] = std::move(valueHandle);
    return true;
  };
  constexpr auto rm = llvm::APFloat::rmNearestTiesToEven;
  auto binary = [&](auto fn) -> bool {
    CVal arrayValue = operand(0), buildPoint = operand(1);
    if (arrayValue.isPoison() || buildPoint.isPoison())
      return setResult(CVal::poison());
    if (!arrayValue.isFloat() || !buildPoint.isFloat())
      return false;
    llvm::APFloat resultValue = arrayValue.f;
    fn(resultValue, buildPoint.f);
    return setResult(CVal::ofFloat(resultValue));
  };

  auto semantics = [](Type typeValue) -> const llvm::fltSemantics * {
    if (auto ft = dyn_cast<FloatType>(typeValue))
      return &ft.getFloatSemantics();
    return nullptr;
  };
  using llvm::APFloat;
  return llvm::TypeSwitch<Operation *, bool>(&op)
      .Case([&](arith::AddFOp) {
        return binary([&](APFloat &arrayValue, const APFloat &buildPoint) {
          arrayValue.add(buildPoint, rm);
        });
      })
      .Case([&](arith::SubFOp) {
        return binary([&](APFloat &arrayValue, const APFloat &buildPoint) {
          arrayValue.subtract(buildPoint, rm);
        });
      })
      .Case([&](arith::MulFOp) {
        return binary([&](APFloat &arrayValue, const APFloat &buildPoint) {
          arrayValue.multiply(buildPoint, rm);
        });
      })
      .Case([&](arith::DivFOp) {
        return binary([&](APFloat &arrayValue, const APFloat &buildPoint) {
          arrayValue.divide(buildPoint, rm);
        });
      })
      .Case([&](arith::NegFOp) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isFloat())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APFloat resultValue = arrayValue.f;
        resultValue.changeSign();
        return setResult(CVal::ofFloat(resultValue));
      })
      .Case([&](arith::CmpFOp candidateValue) {
        CVal arrayValue = operand(0), buildPoint = operand(1);
        if (arrayValue.isPoison() || buildPoint.isPoison())
          return setResult(CVal::poison());
        if (!arrayValue.isFloat() || !buildPoint.isFloat())
          return false;
        auto cmp = arrayValue.f.compare(buildPoint.f);
        bool unordered = cmp == llvm::APFloat::cmpUnordered;
        bool lt = cmp == llvm::APFloat::cmpLessThan;
        bool gt = cmp == llvm::APFloat::cmpGreaterThan;
        bool eq = cmp == llvm::APFloat::cmpEqual;
        bool resultValue = false;
        using P = arith::CmpFPredicate;
        switch (candidateValue.getPredicate()) {
        case P::AlwaysFalse:
          resultValue = false;
          break;
        case P::OEQ:
          resultValue = eq;
          break;
        case P::OGT:
          resultValue = gt;
          break;
        case P::OGE:
          resultValue = gt || eq;
          break;
        case P::OLT:
          resultValue = lt;
          break;
        case P::OLE:
          resultValue = lt || eq;
          break;
        case P::ONE:
          resultValue = lt || gt;
          break;
        case P::ORD:
          resultValue = !unordered;
          break;
        case P::UEQ:
          resultValue = unordered || eq;
          break;
        case P::UGT:
          resultValue = unordered || gt;
          break;
        case P::UGE:
          resultValue = unordered || gt || eq;
          break;
        case P::ULT:
          resultValue = unordered || lt;
          break;
        case P::ULE:
          resultValue = unordered || lt || eq;
          break;
        case P::UNE:
          resultValue = !eq;
          break;
        case P::UNO:
          resultValue = unordered;
          break;
        case P::AlwaysTrue:
          resultValue = true;
          break;
        }
        return setResult(CVal::ofInt(llvm::APInt(1, resultValue ? 1 : 0)));
      })
      .Case([&](arith::SIToFPOp entryValue) {
        CVal arrayValue = operand(0);
        const llvm::fltSemantics *stringValue = semantics(entryValue.getType());
        if (!arrayValue.isInt() || !stringValue)
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APFloat resultValue(*stringValue);
        resultValue.convertFromAPInt(arrayValue.i, true, rm);
        return setResult(CVal::ofFloat(resultValue));
      })
      .Case([&](arith::UIToFPOp entryValue) {
        CVal arrayValue = operand(0);
        const llvm::fltSemantics *stringValue = semantics(entryValue.getType());
        if (!arrayValue.isInt() || !stringValue)
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APFloat resultValue(*stringValue);
        resultValue.convertFromAPInt(arrayValue.i, false, rm);
        return setResult(CVal::ofFloat(resultValue));
      })
      .Case([&](arith::FPToSIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isFloat())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APSInt resultValue(bitsOf(entryValue.getType()), false);
        bool exact = false;
        if (arrayValue.f.convertToInteger(resultValue,
                                          llvm::APFloat::rmTowardZero, &exact) &
            llvm::APFloat::opInvalidOp)
          return setResult(CVal::poison());
        return setResult(CVal::ofInt(resultValue));
      })
      .Case([&](arith::FPToUIOp entryValue) {
        CVal arrayValue = operand(0);
        if (!arrayValue.isFloat())
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APSInt resultValue(bitsOf(entryValue.getType()), true);
        bool exact = false;
        if (arrayValue.f.convertToInteger(resultValue,
                                          llvm::APFloat::rmTowardZero, &exact) &
            llvm::APFloat::opInvalidOp)
          return setResult(CVal::poison());
        return setResult(CVal::ofInt(resultValue));
      })
      .Case([&](arith::ExtFOp entryValue) {
        CVal arrayValue = operand(0);
        const llvm::fltSemantics *stringValue = semantics(entryValue.getType());
        if (!arrayValue.isFloat() || !stringValue)
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APFloat resultValue = arrayValue.f;
        bool lost = false;
        resultValue.convert(*stringValue, rm, &lost);
        return setResult(CVal::ofFloat(resultValue));
      })
      .Case([&](arith::TruncFOp entryValue) {
        CVal arrayValue = operand(0);
        const llvm::fltSemantics *stringValue = semantics(entryValue.getType());
        if (!arrayValue.isFloat() || !stringValue)
          return arrayValue.isPoison() ? setResult(arrayValue) : false;
        llvm::APFloat resultValue = arrayValue.f;
        bool lost = false;
        resultValue.convert(*stringValue, rm, &lost);
        return setResult(CVal::ofFloat(resultValue));
      })
      .Case([&](arith::BitcastOp entryValue) {
        CVal arrayValue = operand(0);
        if (arrayValue.isPoison())
          return setResult(arrayValue);
        if (const llvm::fltSemantics *stringValue =
                semantics(entryValue.getType())) {
          if (!arrayValue.isInt())
            return false;
          return setResult(
              CVal::ofFloat(llvm::APFloat(*stringValue, arrayValue.i)));
        }
        if (!arrayValue.isFloat() || !bitsOf(entryValue.getType()))
          return false;
        return setResult(CVal::ofInt(arrayValue.f.bitcastToAPInt()));
      })
      .Default([](Operation *) { return false; });
}

bool Evaluator::exec(Operation &op, DenseMap<Value, CVal> &env) {
  if (auto candidateValue = dyn_cast<arith::ConstantOp>(op)) {
    std::optional<CVal> valueHandle = constantValue(candidateValue.getValue());
    if (!valueHandle)
      return false;
    env[candidateValue.getResult()] = *valueHandle;
    return true;
  }
  if (isa<LLVM::UndefOp, LLVM::PoisonOp>(op)) {

    unsigned widthValue = bitsOf(op.getResult(0).getType());
    if (widthValue) {
      env[op.getResult(0)] = CVal::ofInt(llvm::APInt(widthValue, 0));
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
    CVal candidateValue = lookup(env, sel.getCondition());
    if (!candidateValue.isInt())
      return false;
    env[sel.getResult()] =
        lookup(env, candidateValue.i.isZero() ? sel.getFalseValue()
                                              : sel.getTrueValue());
    return true;
  }
  if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
    CVal candidateValue = lookup(env, ifOp.getCondition());
    if (!candidateValue.isInt())
      return false;
    Region &resultValue =
        candidateValue.i.isZero() ? ifOp.getElseRegion() : ifOp.getThenRegion();
    SmallVector<CVal> out;
    if (resultValue.empty()) {
      if (ifOp.getNumResults())
        return false;
      return true;
    }
    if (!runNested(resultValue, {}, env, out) ||
        out.size() != ifOp.getNumResults())
      return false;
    for (auto [passResult, valueHandle] : llvm::zip(ifOp.getResults(), out))
      env[passResult] = valueHandle;
    return true;
  }
  if (auto forOp = dyn_cast<scf::ForOp>(op)) {
    CVal lb = lookup(env, forOp.getLowerBound()),
         ub = lookup(env, forOp.getUpperBound()),
         st = lookup(env, forOp.getStep());
    if (!lb.isInt() || !ub.isInt() || !st.isInt() || !st.i.isStrictlyPositive())
      return false;
    const bool isUnsigned = false;
    SmallVector<CVal> iter;
    for (Value valueHandle : forOp.getInitArgs())
      iter.push_back(lookup(env, valueHandle));
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
    for (auto [passResult, valueHandle] : llvm::zip(forOp.getResults(), iter))
      env[passResult] = valueHandle;
    return true;
  }
  if (auto whileOp = dyn_cast<scf::WhileOp>(op)) {
    SmallVector<CVal> args;
    for (Value valueHandle : whileOp.getInits())
      args.push_back(lookup(env, valueHandle));
    while (true) {
      SmallVector<CVal> out;
      Operation *term = nullptr;
      if (!runNested(whileOp.getBefore(), args, env, out, &term))
        return false;
      auto cond = cast<scf::ConditionOp>(term);
      CVal candidateValue = lookup(env, cond.getCondition());
      if (!candidateValue.isInt())
        return false;
      SmallVector<CVal> fwd(out.begin() + 1, out.end());
      if (candidateValue.i.isZero()) {
        for (auto [passResult, valueHandle] :
             llvm::zip(whileOp.getResults(), fwd))
          env[passResult] = valueHandle;
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
    for (Value valueHandle : forOp.getInits())
      iter.push_back(lookup(env, valueHandle));
    for (int64_t iv = lb; iv < ub; iv += step) {
      SmallVector<CVal> args{indexVal(iv)};
      args.append(iter);
      SmallVector<CVal> out;
      if (!runNested(forOp.getRegion(), args, env, out))
        return false;
      iter = out;
    }
    for (auto [passResult, valueHandle] : llvm::zip(forOp.getResults(), iter))
      env[passResult] = valueHandle;
    return true;
  }
  if (auto ifOp = dyn_cast<affine::AffineIfOp>(op)) {
    IntegerSet set = ifOp.getIntegerSet();
    SmallVector<int64_t> vals;
    AffineMap memoryOp = AffineMap::get(set.getNumDims(), set.getNumSymbols(),
                                        set.getConstraints(), set.getContext());
    if (!applyMap(memoryOp, ifOp.getOperands(), env, vals))
      return false;
    bool holds = true;
    for (unsigned keyValue = 0; keyValue < vals.size(); ++keyValue)
      holds &= set.isEq(keyValue) ? vals[keyValue] == 0 : vals[keyValue] >= 0;
    Region &resultValue = holds ? ifOp.getThenRegion() : ifOp.getElseRegion();
    if (resultValue.empty())
      return ifOp.getNumResults() == 0;
    SmallVector<CVal> out;
    if (!runNested(resultValue, {}, env, out) ||
        out.size() != ifOp.getNumResults())
      return false;
    for (auto [passResult, valueHandle] : llvm::zip(ifOp.getResults(), out))
      env[passResult] = valueHandle;
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
    env[op.getResult(0)] =
        indexVal(isMin ? *llvm::min_element(vals) : *llvm::max_element(vals));
    return true;
  }
  if (arrays) {
    SmallVector<int64_t> indexValue;
    if (auto ld = dyn_cast<affine::AffineLoadOp>(op))
      return applyMap(ld.getAffineMap(), ld.getMapOperands(), env,
                      indexValue) &&
             loadElement(ld.getMemRef(), indexValue, ld.getResult(), env);
    if (auto st = dyn_cast<affine::AffineStoreOp>(op))
      return applyMap(st.getAffineMap(), st.getMapOperands(), env,
                      indexValue) &&
             storeElement(st.getMemRef(), indexValue,
                          lookup(env, st.getValueToStore()));
    if (auto ld = dyn_cast<memref::LoadOp>(op))
      return indexValues(ld.getIndices(), env, indexValue) &&
             loadElement(ld.getMemRef(), indexValue, ld.getResult(), env);
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return indexValues(st.getIndices(), env, indexValue) &&
             storeElement(st.getMemRef(), indexValue,
                          lookup(env, st.getValueToStore()));
  }
  if (auto call = dyn_cast<func::CallOp>(op)) {
    if (arrays)
      return false;
    auto callee = symbols.lookupNearestSymbolFrom<func::FuncOp>(
        call, call.getCalleeAttr());
    if (!callee)
      return false;
    SmallVector<CVal> args, results;
    for (Value valueHandle : call.getOperands())
      args.push_back(lookup(env, valueHandle));
    if (!this->call(callee, args, results) ||
        results.size() != call.getNumResults())
      return false;
    for (auto [passResult, valueHandle] : llvm::zip(call.getResults(), results))
      env[passResult] = valueHandle;
    return true;
  }
  if (op.getNumResults() != 1 || op.getNumRegions() != 0)
    return false;
  Type typeValue = op.getResult(0).getType();
  if (isa<FloatType>(typeValue) ||
      isa<arith::CmpFOp, arith::FPToSIOp, arith::FPToUIOp, arith::BitcastOp>(
          op))
    return execFloat(op, env);
  if (bitsOf(typeValue))
    return execInt(op, env);
  return false;
}

/// A result of the evaluation as an attribute of `t`, or null.
static TypedAttr toAttr(const CVal &valueHandle, Type typeValue) {
  if (valueHandle.isInt() && bitsOf(typeValue) == valueHandle.i.getBitWidth())
    return IntegerAttr::get(typeValue, valueHandle.i);
  if (valueHandle.isFloat())
    if (auto ft = dyn_cast<FloatType>(typeValue))
      if (&ft.getFloatSemantics() == &valueHandle.f.getSemantics())
        return FloatAttr::get(typeValue, valueHandle.f);
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
    for (Type typeValue : call.getResultTypes())
      if (!bitsOf(typeValue) && !isa<FloatType>(typeValue))
        return;
    for (Value valueHandle : call.getOperands()) {
      auto candidateValue = valueHandle.getDefiningOp<arith::ConstantOp>();
      if (!candidateValue || (!isa<IntegerAttr>(candidateValue.getValue()) &&
                              !isa<FloatAttr>(candidateValue.getValue())))
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

    if (!callee || callee.isExternal() || callee->hasAttr("hls.inline_off"))
      continue;
    Evaluator ev(symbols, maxSteps);
    SmallVector<CVal> args, results;
    for (Value valueHandle : call.getOperands()) {
      Attribute arrayValue =
          valueHandle.getDefiningOp<arith::ConstantOp>().getValue();
      if (auto ia = dyn_cast<IntegerAttr>(arrayValue))
        args.push_back(
            CVal::ofInt(ia.getValue().sextOrTrunc(bitsOf(ia.getType()))));
      else
        args.push_back(CVal::ofFloat(cast<FloatAttr>(arrayValue).getValue()));
    }
    if (!ev.call(callee, args, results) ||
        results.size() != call.getNumResults()) {
      LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: not evaluated "
                              << callee.getSymName() << "\n");
      continue;
    }
    SmallVector<TypedAttr> attrs;
    for (auto [valueHandle, typeValue] :
         llvm::zip(results, call.getResultTypes()))
      if (TypedAttr arrayValue = toAttr(valueHandle, typeValue))
        attrs.push_back(arrayValue);
    if (attrs.size() != call.getNumResults()) {
      LLVM_DEBUG(llvm::dbgs() << "constant-call-eval: undefined result of "
                              << callee.getSymName() << "\n");
      continue;
    }
    OpBuilder buildPoint(call);
    std::string detail;
    llvm::raw_string_ostream os(detail);
    StringRef name = callee.getSymName();
    if (auto orig = callee->getAttrOfType<StringAttr>("hls.orig_name"))
      name = orig.getValue();
    os << name << " of constant arguments evaluated:";
    for (auto [passResult, arrayValue] : llvm::zip(call.getResults(), attrs)) {
      os << " " << arrayValue;
      passResult.replaceAllUsesWith(
          buildPoint.create<arith::ConstantOp>(call.getLoc(), arrayValue));
    }
    std::string func;
    if (auto fn = call->getParentOfType<func::FuncOp>())
      func = fn.getName().str();
    notes.push_back(
        {"constant-call", call.getLoc(), callee.getLoc(), os.str(), func});
    call.erase();
    ++folded;
  }
  return folded;
}

/// Whether `op` (or an op nested in it) uses `mem` other than as the memref
/// of a load or store.
static bool onlyLoadsAndStores(Value mem) {
  for (OpOperand &use : mem.getUses()) {
    Operation *useValue = use.getOwner();
    if (auto ld = dyn_cast<affine::AffineLoadOp>(useValue);
        ld && ld.getMemRef() == mem)
      continue;
    if (auto st = dyn_cast<affine::AffineStoreOp>(useValue);
        st && st.getMemRef() == mem && st.getValueToStore() != mem)
      continue;
    if (auto ld = dyn_cast<memref::LoadOp>(useValue);
        ld && ld.getMemRef() == mem)
      continue;
    if (auto st = dyn_cast<memref::StoreOp>(useValue);
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
static bool registerArray(memref::AllocaOp arrayValue) {
  auto spec = arrayValue->getAttrOfType<ArrayAttr>("hls.array_partition");
  if (!spec)
    return false;
  MemRefType typeValue = arrayValue.getType();
  for (int64_t dimensionIndex = 0; dimensionIndex < typeValue.getRank();
       ++dimensionIndex) {
    if (typeValue.getShape()[dimensionIndex] <= 1)
      continue;
    bool complete = llvm::any_of(spec, [&](Attribute entryValue) {
      auto dict = dyn_cast<DictionaryAttr>(entryValue);
      auto kind = dict ? dict.getAs<StringAttr>("kind") : StringAttr();
      auto dim = dict ? dict.getAs<IntegerAttr>("dim") : IntegerAttr();
      return kind && kind.getValue() == "complete" &&
             (!dim || dim.getInt() == 0 || dim.getInt() == dimensionIndex + 1);
    });
    if (!complete)
      return false;
  }
  return true;
}

/// The arrays among `cands` that `op` (or a nested op) stores to.
static void storedArrays(Operation *op, const DenseSet<Value> &cands,
                         SmallPtrSetImpl<Value> &out) {
  op->walk([&](Operation *exprValue) {
    Value mem;
    if (auto st = dyn_cast<affine::AffineStoreOp>(exprValue))
      mem = st.getMemRef();
    else if (auto st = dyn_cast<memref::StoreOp>(exprValue))
      mem = st.getMemRef();
    if (mem && cands.contains(mem))
      out.insert(mem);
  });
}

unsigned
foldConstantFillPrefixes(ModuleOp module, int64_t maxSteps, int64_t maxElements,
                         SmallVectorImpl<circt::hlsest::FoldNote> &notes) {
  SymbolTableCollection symbols;
  unsigned folded = 0;
  unsigned globalCounter = 0;
  SmallVector<func::FuncOp> funcs(module.getOps<func::FuncOp>());
  for (func::FuncOp fn : funcs) {
    if (fn.isExternal() || !fn.getBody().hasOneBlock())
      continue;
    Block &entry = fn.getBody().front();

    DenseSet<Value> cands;
    DenseMap<Value, Evaluator::ArrayState> arrays;
    for (Operation &op : entry)
      if (auto arrayValue = dyn_cast<memref::AllocaOp>(op)) {
        MemRefType typeValue = arrayValue.getType();
        if (!typeValue.hasStaticShape() ||
            !typeValue.getLayout().isIdentity() ||
            typeValue.getNumElements() > maxElements ||
            !registerArray(arrayValue) ||
            !(isa<IntegerType>(typeValue.getElementType()) ||
              isa<FloatType>(typeValue.getElementType())) ||
            !onlyLoadsAndStores(arrayValue.getResult()))
          continue;
        cands.insert(arrayValue.getResult());
        arrays[arrayValue.getResult()] = {
            typeValue, std::vector<CVal>(typeValue.getNumElements())};
      }
    if (cands.empty())
      continue;
    Evaluator ev(symbols, maxSteps);
    ev.enableArrays(&arrays);
    DenseMap<Value, CVal> env;

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

      SmallPtrSet<Value, 4> stores;
      storedArrays(&op, cands, stores);

      if (stores.empty()) {
        SmallPtrSet<Value, 4> none;
        if (op.getNumRegions() == 0 && isMemoryEffectFree(&op) &&
            !ev.runOp(op, env, none))
          for (Value resultValue : op.getResults())
            env.erase(resultValue);
        continue;
      }
      bool readsTainted = false;
      op.walk([&](Operation *exprValue) {
        for (Value valueHandle : exprValue->getOperands())
          if (tainted.contains(valueHandle))
            readsTainted = true;
      });
      DenseMap<Value, Evaluator::ArrayState> before;
      for (Value memoryOp : stores)
        before[memoryOp] = arrays[memoryOp];
      SmallPtrSet<Value, 4> written;
      bool ok = !readsTainted && ev.runOp(op, env, written);
      if (ok) {
        evaluated.push_back(&op);
        writesOf[&op] = written;
        continue;
      }

      for (auto &[memoryOp, st] : before)
        arrays[memoryOp] = st;
      for (Value memoryOp : stores)
        tainted.insert(memoryOp);
      for (Value resultValue : op.getResults())
        env.erase(resultValue);
    }

    DenseSet<Value> fold;
    for (Operation *op : evaluated)
      for (Value memoryOp : writesOf[op])
        if (!tainted.contains(memoryOp))
          fold.insert(memoryOp);

    bool changed = true;
    DenseSet<Operation *> keep;
    while (changed) {
      changed = false;
      for (Operation *op : evaluated) {
        if (keep.contains(op))
          continue;
        SmallPtrSet<Value, 4> stores;
        storedArrays(op, cands, stores);
        bool keepOp = llvm::any_of(
            stores, [&](Value memoryOp) { return !fold.contains(memoryOp); });

        for (Value resultValue : op->getResults()) {
          auto it = env.find(resultValue);
          if (it == env.end() || !(it->second.isInt() || it->second.isFloat()))
            keepOp = true;
        }
        if (keepOp) {
          keep.insert(op);
          for (Value memoryOp : stores)
            changed |= fold.erase(memoryOp);
        }
      }
    }
    if (fold.empty())
      continue;
    OpBuilder buildPoint(module.getContext());

    for (Operation *op : evaluated) {
      if (keep.contains(op))
        continue;
      buildPoint.setInsertionPoint(op);
      for (Value resultValue : op->getResults()) {
        TypedAttr arrayValue = toAttr(env[resultValue], resultValue.getType());
        if (!arrayValue) {
          if (auto it = dyn_cast<IndexType>(resultValue.getType());
              it && env[resultValue].isInt())
            arrayValue =
                IntegerAttr::get(it, env[resultValue].i.getSExtValue());
        }
        if (!arrayValue)
          continue;
        resultValue.replaceAllUsesWith(
            buildPoint.create<arith::ConstantOp>(op->getLoc(), arrayValue));
      }
    }
    for (Operation *op : evaluated)
      if (!keep.contains(op))
        op->erase();

    for (Value memoryOp : fold) {
      auto localAlloca = memoryOp.getDefiningOp<memref::AllocaOp>();
      Evaluator::ArrayState &st = arrays[memoryOp];
      Type elt = st.type.getElementType();
      SmallVector<Attribute> vals;
      for (const CVal &valueHandle : st.elems) {
        Attribute arrayValue;
        if (auto it = dyn_cast<IntegerType>(elt))
          arrayValue = IntegerAttr::get(
              it, valueHandle.isInt() &&
                          valueHandle.i.getBitWidth() == it.getWidth()
                      ? valueHandle.i
                      : llvm::APInt(it.getWidth(), 0));
        else {
          auto ft = cast<FloatType>(elt);
          arrayValue = FloatAttr::get(
              ft, valueHandle.isFloat() && &valueHandle.f.getSemantics() ==
                                               &ft.getFloatSemantics()
                      ? valueHandle.f
                      : llvm::APFloat::getZero(ft.getFloatSemantics()));
        }
        vals.push_back(arrayValue);
      }
      auto tensorTy = RankedTensorType::get(st.type.getShape(), elt);
      auto initialValue = DenseElementsAttr::get(tensorTy, vals);
      std::string name =
          (fn.getName() + "__hls_const_fill_" + llvm::Twine(globalCounter++))
              .str();
      buildPoint.setInsertionPoint(fn);
      auto global = buildPoint.create<memref::GlobalOp>(
          localAlloca.getLoc(), name, buildPoint.getStringAttr("private"),
          st.type, initialValue, true, IntegerAttr());

      for (NamedAttribute na : localAlloca->getAttrs())
        if (na.getName().getValue().starts_with("polygeist.") ||
            na.getName().getValue().starts_with("hls."))
          global->setAttr(na.getName(), na.getValue());
      global->setAttr("hls.constant_fill_evaluated", buildPoint.getUnitAttr());
      buildPoint.setInsertionPoint(localAlloca);
      auto get = buildPoint.create<memref::GetGlobalOp>(
          localAlloca.getLoc(), st.type, global.getSymName());
      localAlloca.getResult().replaceAllUsesWith(get.getResult());
      std::string detail;
      llvm::raw_string_ostream os(detail);
      StringRef var = "array";
      if (auto valueHandle =
              localAlloca->getAttrOfType<StringAttr>("polygeist.varname"))
        var = valueHandle.getValue();
      os << var << " filled from constants by loops evaluated at compile "
         << "time: a constant table (N174)";
      notes.push_back({"constant-fill-loops", localAlloca.getLoc(),
                       localAlloca.getLoc(), os.str(), fn.getName().str()});
      localAlloca.erase();
      ++folded;
    }

    for (memref::GlobalOp globalOp :
         llvm::make_early_inc_range(module.getOps<memref::GlobalOp>()))
      if (globalOp->hasAttr("hls.constant_fill_evaluated") &&
          SymbolTable::symbolKnownUseEmpty(globalOp, module))
        globalOp.erase();
    for (Operation &op : llvm::make_early_inc_range(entry))
      if (auto get = dyn_cast<memref::GetGlobalOp>(op))
        if (get.getResult().use_empty())
          if (auto globalOp = symbols.lookupNearestSymbolFrom<memref::GlobalOp>(
                  get, get.getNameAttr());
              globalOp && globalOp->hasAttr("hls.constant_fill_evaluated")) {
            get.erase();
            if (SymbolTable::symbolKnownUseEmpty(globalOp, module))
              globalOp.erase();
          }
  }
  return folded;
}

} // namespace circt::hls_analysis
