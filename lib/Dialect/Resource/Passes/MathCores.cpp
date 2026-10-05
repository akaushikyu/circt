//===- MathCores.cpp - hls:: math-function cores for --bram-analysis ------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// --bram-analysis=math-costs=<file>: the BRAM of the cores Vitis HLS 2025.1
// builds for hls:: math calls, read from the programmer's cost table
// (tools/hls-est-validate/math_costs.json). Vitis implements every (function,
// element type, argument form) with one core - a floating-point operator IP,
// a math-library module, or library code inlined into the caller - whose
// BRAM_18K is the same wherever it is used: its ROM tables. What changes is
// how many instances it builds, and that follows the call structure.
//
// Which calls: a math dialect op (math.exp, math.powf, ...), a func.call of an
// external libm function (exp / expf, tanh / tanhf, ...), the type being the
// element type of the first argument (f16 half, f32 float, f64 double), or a
// call of the exactclass shim's marker __hlsest_math_<function>(<double
// arguments>, W, I, S), whose three trailing integer constants give the
// ap_fixed type the double computation lost (S = 1 ap_fixed<W,I>, 0
// ap_ufixed<W,I>; shim/exactclass/hls_math.h "math-core markers"). Rounding,
// min / max and the like are not cores and are never listed.
//
// Free calls:
//   - folded: every data argument is a constant. Vitis evaluates such a call
//     at compile time and builds no core (hls::log of a constant, std::sin of
//     a literal, powf of two literals all cost 0); so does a call that only
//     fills an array from loop indices and constants (a coefficient table),
//     see onlyFillsArrays;
//   - dead: no result reaches a store, a return, a loop-carried value or a
//     call with side effects (pure ops in between are followed); Vitis's
//     dead-code removal deletes the call with its core.
// The argument form selects the entry: pow with a constant base / exponent
// uses the "constant base" / "constant exponent" entry when there is one (a
// constant base removes pow's logarithm stage and most of its tables).
//
// Instances of one core in one function:
//   - pipelined loop (a loopschedule.pipeline, or a loop that keeps its
//     hls.pipeline tag because it could not be scheduled - then the requested
//     II, or 1, is assumed): ceil(calls per iteration / II), chained or not -
//     a core is busy one cycle per call, so one instance serves II calls of an
//     iteration. Vitis outlines each pipelined loop into a module of its own
//     (<f>_Pipeline_<loop>), so the instances of different pipelined loops add
//     up.
//   - sequential code: one instance per call that can run at the same time as
//     another, over all the sequential code of the function (the rule for
//     non-inlined callees, groupConcurrentCalls): two calls are ordered, and
//     share an instance, when a value of one reaches an operand of the other
//     (through SSA values, region results and memory) or when they lie in
//     different arms of one conditional (`if (c) r = exp(x); else r =
//     exp(y);`: Vitis builds one exp core); the instances are a minimum
//     cover of that order by chains (two independent calls 2, f(f(x)) 1, k
//     unrolled copies k, one call site in a loop 1). Only calls of one
//     straight-line stretch, or calls in two loops of the function body that
//     access no common array, can overlap (Vitis runs such loops
//     concurrently); the other pairs run one after the other and share
//     (mayOverlapInSequentialCode).
//   - shares_instance_with: a call of a listed function of the same type on an
//     equivalent argument (the same SSA value, or equal pure ops / loads of the
//     same address) joins the call's instance (ap_fixed sin + cos of one
//     argument are computed by one CORDIC).
//   - cordic_loop entries: the CORDIC sin / cos / tanh of ap_fixed is a loop
//     reading a 128-word arctan table. A pipelined loop around the call
//     unrolls it completely, the table indices become constants and the table
//     folds (bram_18k_if_cordic_loop_unrolled, 0); elsewhere the table costs
//     bram_18k per instance. With cordic_loop_unrolled_in = user_pipeline
//     (sin / cos) only a loop with a pipeline pragma does that: under
//     automatic pipelining (an hls.pipeline tag with source = "auto", or an
//     untagged innermost loop) Vitis keeps the sin / cos CORDIC loop, makes it
//     the innermost pipelined loop and flattens the caller nest into it, one
//     table per call site; tanh's (any_pipeline) is unrolled by either.
//   - the function's own instances: a math core inside a callee Vitis keeps
//     as a module is built once per instance of that module (multiplied by
//     the instance count the caller gives, `instancesOf`).
// Not modelled: a library core that Vitis inlines into a pipelined caller,
// whose tables are then ordinary caller ROMs (cheaper above 2 reads per
// cycle than whole instances).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/MathCores.h"
#include <algorithm>
#include <deque>
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"

#include "mlir/Analysis/SliceAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/MemoryBuffer.h"

#include <algorithm>
#include <functional>
#include <map>
#include <set>

using namespace mlir;
using circt::loopschedule::LoopSchedulePipelineOp;
using circt::loopschedule::LoopSchedulePipelineStageOp;

namespace circt::hls_analysis {

//===----------------------------------------------------------------------===//
// The cost table.
//===----------------------------------------------------------------------===//

static std::string normalizedType(StringRef t) {
  std::string out;
  for (char c : t)
    if (c != ' ' && c != '\t')
      out.push_back(c);
  return out;
}

bool MathCostConfig::load(StringRef file, std::string &error) {
  path = file.str();
  entries.clear();
  auto buf = llvm::MemoryBuffer::getFile(file);
  if (!buf) {
    error = "cannot read '" + path + "': " + buf.getError().message();
    return false;
  }
  llvm::Expected<llvm::json::Value> doc = llvm::json::parse((*buf)->getBuffer());
  if (!doc) {
    error = "'" + path + "' is not valid JSON: " + llvm::toString(doc.takeError());
    return false;
  }
  const llvm::json::Object *root = doc->getAsObject();
  if (!root) {
    error = "'" + path + "': the top level is not a JSON object";
    return false;
  }
  if (std::optional<int64_t> v = root->getInteger("version"); v && *v != 1) {
    error = "'" + path + "': version " + std::to_string(*v) +
            " is not supported (this hls-est reads version 1)";
    return false;
  }
  const llvm::json::Array *list = root->getArray("entries");
  if (!list) {
    error = "'" + path + "': no \"entries\" array";
    return false;
  }
  static const llvm::StringSet<> kRules = {"per_concurrent_call", "operator",
                                           "logic_only", "cordic_loop",
                                           "inline_tables"};
  static const llvm::StringSet<> kForms = {"any", "constant base",
                                           "constant exponent"};
  std::set<std::string> seen;
  for (size_t i = 0; i < list->size(); ++i) {
    std::string where = "'" + path + "': entries[" + std::to_string(i) + "]";
    const llvm::json::Object *o = (*list)[i].getAsObject();
    if (!o) {
      error = where + " is not an object";
      return false;
    }
    MathCostEntry e;
    e.index = static_cast<unsigned>(i);
    auto needString = [&](StringRef key, std::string &out) {
      std::optional<StringRef> s = o->getString(key);
      if (!s || s->empty()) {
        error = where + ": \"" + key.str() + "\" is missing or not a string";
        return false;
      }
      out = s->str();
      return true;
    };
    if (!needString("function", e.function) || !needString("type", e.type) ||
        !needString("instancing", e.instancing))
      return false;
    e.type = normalizedType(e.type);
    if (!kRules.contains(e.instancing)) {
      error = where + ": unknown instancing rule \"" + e.instancing +
              "\" (per_concurrent_call | operator | logic_only | cordic_loop "
              "| inline_tables)";
      return false;
    }
    if (const llvm::json::Value *a = o->get("arguments")) {
      std::optional<StringRef> s = a->getAsString();
      if (!s || !kForms.contains(*s)) {
        error = where + ": \"arguments\" must be \"any\", \"constant base\" "
                        "or \"constant exponent\"";
        return false;
      }
      e.arguments = s->str();
    }
    std::optional<int64_t> bram = o->getInteger("bram_18k");
    if (!bram || *bram < 0) {
      error = where + ": \"bram_18k\" is missing or not a non-negative integer";
      return false;
    }
    e.bram = *bram;
    // logic_only means the core has no memory at all. The other rules than
    // cordic_loop (operator, inline_tables) are counted like
    // per_concurrent_call: their measured entries all cost 0 BRAM, so how
    // Vitis shares them cannot change a BRAM estimate yet.
    if (e.instancing == "logic_only" && e.bram != 0) {
      error = where + ": instancing \"logic_only\" (no memory) needs "
                      "\"bram_18k\": 0";
      return false;
    }
    if (std::optional<StringRef> k = o->getString("core_kind"))
      e.coreKind = k->str();
    if (const llvm::json::Value *c = o->get("core")) {
      if (const llvm::json::Array *arr = c->getAsArray()) {
        for (const llvm::json::Value &x : *arr)
          if (std::optional<StringRef> s = x.getAsString())
            e.cores.push_back(s->str());
      } else if (std::optional<StringRef> s = c->getAsString()) {
        if (!s->starts_with("(")) // "(inlined into the caller)"
          e.cores.push_back(s->str());
      }
    }
    if (const llvm::json::Array *tabs = o->getArray("tables"))
      for (const llvm::json::Value &t : *tabs)
        if (const llvm::json::Object *to = t.getAsObject()) {
          if (std::optional<StringRef> n = to->getString("name"))
            if (e.tableName.empty())
              e.tableName = n->str();
          std::optional<int64_t> words = to->getInteger("words");
          std::optional<int64_t> bits = to->getInteger("bits");
          if (words && bits && *words > 0 && *bits > 0)
            e.tableShapes.push_back({*words, static_cast<unsigned>(*bits)});
        }
    e.cordicTrips = o->getInteger("cordic_loop_trip_count");
    e.bramIfUnrolled = o->getInteger("bram_18k_if_cordic_loop_unrolled");
    if (const llvm::json::Value *u = o->get("cordic_loop_unrolled_in")) {
      std::optional<StringRef> s = u->getAsString();
      if (!s || (*s != "any_pipeline" && *s != "user_pipeline")) {
        error = where + ": \"cordic_loop_unrolled_in\" must be "
                        "\"any_pipeline\" or \"user_pipeline\"";
        return false;
      }
      e.cordicUnrolledIn = s->str();
    }
    if (const llvm::json::Value *b = o->get("blocks_automatic_pipelining")) {
      std::optional<bool> v = b->getAsBoolean();
      if (!v) {
        error = where + ": \"blocks_automatic_pipelining\" must be true or "
                        "false";
        return false;
      }
      e.blocksAutoPipelining = *v;
    }
    if (const llvm::json::Value *s = o->get("shares_instance_with")) {
      const llvm::json::Array *arr = s->getAsArray();
      if (!arr) {
        error = where + ": \"shares_instance_with\" must be an array of "
                        "function names";
        return false;
      }
      for (const llvm::json::Value &x : *arr) {
        std::optional<StringRef> n = x.getAsString();
        if (!n) {
          error = where + ": \"shares_instance_with\" must be an array of "
                          "function names";
          return false;
        }
        e.sharesInstanceWith.push_back(n->str());
      }
    }
    std::string key = e.function + "|" + e.type + "|" + e.arguments;
    if (!seen.insert(key).second) {
      error = where + ": a second entry for " + e.function + " of " + e.type +
              " (arguments \"" + e.arguments + "\")";
      return false;
    }
    entries.push_back(std::move(e));
  }
  return true;
}

const MathCostEntry *MathCostConfig::lookup(StringRef function, StringRef type,
                                            StringRef arguments) const {
  std::string t = normalizedType(type);
  const MathCostEntry *any = nullptr;
  for (const MathCostEntry &e : entries) {
    if (e.function != function || e.type != t)
      continue;
    if (e.arguments == arguments)
      return &e;
    if (e.arguments == "any")
      any = &e;
  }
  return any;
}

//===----------------------------------------------------------------------===//
// Recognising the calls.
//===----------------------------------------------------------------------===//

// hls_math.h functions that can be a core (the table lists the measured
// ones; any other of these is reported as an unlisted pair).
static const llvm::StringSet<> &coreFunctions() {
  static const llvm::StringSet<> s = {
      "exp",   "exp2",  "exp10", "expm1", "log",   "log2",  "log10",
      "log1p", "logb",  "sqrt",  "rsqrt", "cbrt",  "recip", "sin",
      "cos",   "tan",   "sinpi", "cospi", "asin",  "acos",  "atan",
      "atan2", "sinh",  "cosh",  "tanh",  "asinh", "acosh", "atanh",
      "pow",   "erf",   "erfc",  "hypot", "fmod",  "remainder", "abs",
      // generic_round's mask / one-half ROMs (VITIS_NOTES N170, kernel
      // w9r22p_d9_round: round(double) 4 BRAM in the caller).
      "round"};
  return s;
}

// libm functions without side effects that are not cores (followed by the
// liveness test, never listed).
static const llvm::StringSet<> &pureLibmHelpers() {
  static const llvm::StringSet<> s = {
      "floor", "floorf", "ceil", "ceilf", "trunc", "truncf", "rint",
      "rintf", "nearbyint", "nearbyintf", "fmin", "fminf",
      "fmax", "fmaxf", "copysign", "copysignf", "fdim", "fdimf", "ldexp",
      "ldexpf"};
  return s;
}

static StringRef mathOpFunction(Operation *op) {
  static const llvm::StringMap<StringRef> m = {
      {"math.exp", "exp"},     {"math.exp2", "exp2"},   {"math.expm1", "expm1"},
      {"math.log", "log"},     {"math.log2", "log2"},   {"math.log10", "log10"},
      {"math.log1p", "log1p"}, {"math.sqrt", "sqrt"},   {"math.rsqrt", "rsqrt"},
      {"math.cbrt", "cbrt"},   {"math.sin", "sin"},     {"math.cos", "cos"},
      {"math.tan", "tan"},     {"math.tanh", "tanh"},   {"math.sinh", "sinh"},
      {"math.cosh", "cosh"},   {"math.asin", "asin"},   {"math.acos", "acos"},
      {"math.atan", "atan"},   {"math.atan2", "atan2"}, {"math.asinh", "asinh"},
      {"math.acosh", "acosh"}, {"math.atanh", "atanh"}, {"math.erf", "erf"},
      {"math.erfc", "erfc"},   {"math.powf", "pow"},    {"math.fpowi", "pow"},
      {"math.absf", "abs"},
      // cgeist lowers C `pow(x, 2)` of a double to llvm.intr.powi; Vitis
      // builds pow_generic_double_s for it (OPEN_ISSUES O145: HLSFactory
      // Monte-Carlo Paths, kernel w2i_powce_f64 = math_costs' "pow double
      // constant exponent").
      {"llvm.intr.powi", "pow"}};
  auto it = m.find(op->getName().getStringRef());
  return it == m.end() ? StringRef() : it->second;
}

static constexpr StringLiteral kMarkerPrefix = "__hlsest_math_";
static constexpr StringLiteral kMathCoreAttr = "hls.math_core";

static std::string scalarTypeName(Type t) {
  t = getElementTypeOrSelf(t);
  if (t.isF16())
    return "half";
  if (t.isBF16())
    return "bfloat16";
  if (t.isF32())
    return "float";
  if (t.isF64())
    return "double";
  std::string s;
  llvm::raw_string_ostream os(s);
  t.print(os);
  return s;
}

static func::FuncOp externalCallee(func::CallOp call) {
  auto fn = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
      call, call.getCalleeAttr());
  return fn && fn.isExternal() ? fn : func::FuncOp();
}

// libm name -> function ("expf" -> "exp", "fabs" -> "abs"); empty if none.
static std::string libmFunction(StringRef name) {
  if (name == "fabs" || name == "fabsf")
    return "abs";
  if (name == "abs") // int abs: not a floating-point core
    return "";
  if (coreFunctions().contains(name))
    return name.str();
  if (name.size() > 1 && name.back() == 'f' &&
      coreFunctions().contains(name.drop_back()))
    return name.drop_back().str();
  return "";
}

// A call the liveness test can look through (no side effects).
static bool isPureCall(Operation *op) {
  auto call = dyn_cast<func::CallOp>(op);
  if (!call)
    return false;
  func::FuncOp fn = externalCallee(call);
  if (!fn)
    return false;
  StringRef n = fn.getName();
  return n.starts_with(kMarkerPrefix) || !libmFunction(n).empty() ||
         pureLibmHelpers().contains(n) || call->hasAttr(kMathCoreAttr);
}

namespace {

struct Site {
  Operation *op = nullptr;
  int result = -1; // the result this call produces (-1: all; math.sincos 0 / 1)
  std::string function, type, typeSource, argForm = "any", opText;
  SmallVector<Value, 2> args; // data arguments
  const MathCostEntry *entry = nullptr;
  bool folded = false, dead = false;
  // A copy made for the remainder iterations of a partial user unroll
  // (hls.unroll_remainder): Vitis runs those in the exit-checked copies of
  // the unrolled loop body, so the call is not a call site of its own.
  bool remainder = false;
  // Folded because it only fills an array from loop indices (`fillOnly`).
  bool fillOnly = false;
  // Region.
  Operation *pipeline = nullptr;
  unsigned ii = 1;
  bool iiAssumed = false;
  bool userPipeline = false; // the pipeline comes from a pragma (not automatic)
  Operation *scope = nullptr; // sequential scope (loop or function)
  Block *block = nullptr;
  unsigned stretch = 0;
  // A core that keeps Vitis from pipelining the loops around it, met in a
  // loop hls-est pipelined automatically: the calls are sequential, and the
  // copies hls-est's automatic unrolling made count once (`unrollCopies`).
  bool notPipelined = false;
  unsigned unrollCopies = 1;
  // Instance sharing: index of the site whose instance this one joins.
  int sharedWith = -1;
  std::string func;
  Operation *funcOp = nullptr;
};

} // namespace

// The calls one op makes (none, one, or math.sincos's two).
static void recognise(Operation *op, SmallVectorImpl<Site> &out) {
  if (StringRef fn = mathOpFunction(op); !fn.empty()) {
    if (op->getNumOperands() == 0)
      return;
    Site s;
    s.op = op;
    s.function = fn.str();
    // The core computes in its result type: `std::pow(float, int)` is the
    // double overload (C++11 promotion; W9r14 review kernel w9r14rv_pw_f32,
    // Vitis pow_generic<double>, 30), which older cgeist builds emitted as
    // llvm.intr.powi(f32, i32) -> f64 (OPEN_ISSUES O145).
    Type coreType = op->getOperand(0).getType();
    if (op->getNumResults() == 1 &&
        isa<FloatType>(getElementTypeOrSelf(op->getResult(0).getType())))
      coreType = op->getResult(0).getType();
    s.type = scalarTypeName(coreType);
    s.typeSource = "mlir";
    s.opText = op->getName().getStringRef().str();
    s.args.append(op->operand_begin(), op->operand_end());
    out.push_back(std::move(s));
    return;
  }
  if (op->getName().getStringRef() == "math.sincos" &&
      op->getNumOperands() == 1 && op->getNumResults() == 2) {
    for (int r = 0; r < 2; ++r) {
      Site s;
      s.op = op;
      s.result = r;
      s.function = r == 0 ? "sin" : "cos";
      s.type = scalarTypeName(op->getOperand(0).getType());
      s.typeSource = "mlir";
      s.opText = "math.sincos";
      s.args.push_back(op->getOperand(0));
      out.push_back(std::move(s));
    }
    return;
  }
  auto call = dyn_cast<func::CallOp>(op);
  if (!call || call.getNumOperands() == 0)
    return;
  func::FuncOp callee = externalCallee(call);
  if (!callee)
    return;
  StringRef name = callee.getName();
  Site s;
  s.op = op;
  s.opText = ("func.call @" + name).str();
  // A call cgeist marked as a core of the real hls_math.h (--xlx-headers,
  // Polygeist XlxMathCore.h): the function, and for a fixed-point overload
  // the argument's ap_fixed<W,I> / ap_ufixed<W,I>; a float / double / half
  // overload's type is its operand's (--lower-polygeist-subindex dropped the
  // callee's body).
  if (auto core = call->getAttrOfType<DictionaryAttr>(kMathCoreAttr)) {
    auto fn = core.getAs<StringAttr>("function");
    if (!fn)
      return;
    s.function = fn.getValue().str();
    if (auto t = core.getAs<StringAttr>("type")) {
      s.type = t.getValue().str();
      s.typeSource = "cgeist";
    } else {
      s.type = scalarTypeName(call.getOperand(0).getType());
      s.typeSource = "mlir";
    }
    s.args.append(call.operand_begin(), call.operand_end());
    out.push_back(std::move(s));
    return;
  }
  if (name.starts_with(kMarkerPrefix)) {
    s.function = name.drop_front(kMarkerPrefix.size()).str();
    s.typeSource = "marker";
    unsigned n = call.getNumOperands();
    APInt w, i, sg;
    if (n >= 4 && matchPattern(call.getOperand(n - 3), m_ConstantInt(&w)) &&
        matchPattern(call.getOperand(n - 2), m_ConstantInt(&i)) &&
        matchPattern(call.getOperand(n - 1), m_ConstantInt(&sg))) {
      s.type = (sg.isZero() ? "ap_ufixed<" : "ap_fixed<") +
               std::to_string(w.getSExtValue()) + "," +
               std::to_string(i.getSExtValue()) + ">";
    } else {
      s.type = "ap_fixed<?,?>"; // the marker lost its constants
    }
    for (unsigned k = 0; k + 3 < n; ++k)
      s.args.push_back(call.getOperand(k));
    out.push_back(std::move(s));
    return;
  }
  std::string fn = libmFunction(name);
  if (fn.empty())
    return;
  s.function = fn;
  s.type = scalarTypeName(call.getOperand(0).getType());
  s.typeSource = "mlir";
  s.args.append(call.operand_begin(), call.operand_end());
  out.push_back(std::move(s));
}

//===----------------------------------------------------------------------===//
// Liveness, equivalent arguments, dependence.
//===----------------------------------------------------------------------===//

namespace {

// Whether a value reaches anything Vitis keeps: a store, a return, a yield
// (loop-carried or region result), or a call / op with side effects. Pure ops
// and the pure libm / marker calls in between are followed.
class LiveValues {
public:
  bool live(Value root) {
    auto it = memo.find(root);
    if (it != memo.end())
      return it->second;
    SmallVector<Value> work{root};
    llvm::DenseSet<Value> seen{root};
    bool result = false;
    while (!work.empty() && !result) {
      Value v = work.pop_back_val();
      for (Operation *user : v.getUsers()) {
        bool followable = user->getNumRegions() == 0 &&
                          !user->hasTrait<OpTrait::IsTerminator>() &&
                          (isMemoryEffectFree(user) || isPureCall(user));
        if (!followable) {
          result = true;
          break;
        }
        for (Value r : user->getResults())
          if (seen.insert(r).second)
            work.push_back(r);
      }
    }
    memo[root] = result;
    return result;
  }

private:
  llvm::DenseMap<Value, bool> memo;
};

} // namespace

//===----------------------------------------------------------------------===//
// Calls Vitis evaluates at compile time: array fills from loop indices.
//===----------------------------------------------------------------------===//
//
// A loop that fills an array with values computed from its own indices and
// constants only (a coefficient table: tab[i] = 0.54 - 0.46 * cos(2 pi i /
// (N - 1))) is evaluated by Vitis at compile time; the array becomes a ROM of
// the results and no math core is built (64- and 1024-entry tables of cos of
// double: no sin_or_cos core; the same cos combined with an input value in
// the loop: one core; the vitis_examples hamming and window tables). So a
// call is free when its arguments, and every value its result reaches, are
// functions of loop indices and constants, and the result ends in stores to
// a local or global array (not an argument: those values are outputs).

// The storage a store writes (through views), or null.
/// A one-element register a value passes through on its way to the table: a
/// struct temporary or a single struct variable --split-struct-memrefs made
/// registers, a scalar local (`auto t = complex<float>(cos(a), sin(a));
/// tw[i] = t;`).
static bool n60() {
  return circt::hlsest::Config::get().tool.hls.localStructTablesAtRunTime;
}

static bool isPassThroughRegister(Operation *storage) {
  if (!n60())
    return false;
  auto alloca = dyn_cast_or_null<memref::AllocaOp>(storage);
  return alloca && alloca.getType().hasStaticShape() &&
         alloca.getType().getNumElements() == 1 &&
         (alloca->hasAttr("hls.struct_temporary") ||
          alloca->hasAttr(circt::hls_analysis::kRegistersAttrName));
}

static Operation *storageOf(Value mem) {
  while (Operation *def = mem.getDefiningOp()) {
    if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(def))
      return def;
    auto view = dyn_cast<ViewLikeOpInterface>(def);
    if (!view)
      return nullptr;
    mem = view.getViewSource();
  }
  return nullptr;
}

namespace {
class IndexOnlyValues {
public:
  /// Whether `v` is a compile-time function of constants and the induction
  /// variables of loops with constant bounds.
  bool of(Value v, unsigned depth = 0) {
    auto it = memo.find(v);
    if (it != memo.end())
      return it->second;
    memo[v] = false; // a cycle (a loop-carried value) is not index-only
    bool r = compute(v, depth);
    memo[v] = r;
    return r;
  }

private:
  bool compute(Value v, unsigned depth) {
    if (depth > 64)
      return false;
    if (matchPattern(v, m_Constant()))
      return true;
    if (auto ba = dyn_cast<BlockArgument>(v))
      return isInductionVariable(ba);
    Operation *op = v.getDefiningOp();
    if (auto stage = dyn_cast<LoopSchedulePipelineStageOp>(op)) {
      // A stage result is what its register terminator passes on.
      Operation *term = stage.getBodyBlock().getTerminator();
      unsigned k = cast<OpResult>(v).getResultNumber();
      return k < term->getNumOperands() && of(term->getOperand(k), depth + 1);
    }
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
      // A side-effect-free conditional (the double -> ap_fixed conversion):
      // its condition and the values each branch yields.
      if (!isMemoryEffectFree(op) || !of(ifOp.getCondition(), depth + 1))
        return false;
      unsigned k = cast<OpResult>(v).getResultNumber();
      for (Region &r : op->getRegions())
        for (Block &b : r)
          if (auto y = dyn_cast<scf::YieldOp>(b.getTerminator()))
            if (k >= y.getNumOperands() || !of(y.getOperand(k), depth + 1))
              return false;
      return true;
    }
    if (op->getNumRegions() != 0)
      return false;
    // A load of a struct temporary --split-struct-memrefs made registers
    // (the std::complex built from cos / sin on its way to the table): what
    // every store into the temporary stores.
    if (isa<affine::AffineLoadOp, memref::LoadOp>(op)) {
      Operation *storage = storageOf(op->getOperand(0));
      if (isPassThroughRegister(storage)) {
        for (Operation *u : storage->getResult(0).getUsers())
          if (isa<affine::AffineStoreOp, memref::StoreOp>(u) &&
              !of(u->getOperand(0), depth + 1))
            return false;
        return true;
      }
    }
    if (!isMemoryEffectFree(op) && !isPureCall(op))
      return false;
    for (Value x : op->getOperands())
      if (!of(x, depth + 1))
        return false;
    return true;
  }

  static bool constantBounds(affine::AffineForOp f) {
    return f.hasConstantLowerBound() && f.hasConstantUpperBound();
  }

  // The induction variable of an affine.for / scf.for with constant bounds,
  // or of a loopschedule.pipeline with a trip count: the iter_arg that the
  // terminator advances by a constant (iv + step).
  bool isInductionVariable(BlockArgument ba) {
    Operation *owner = ba.getOwner()->getParentOp();
    if (auto f = dyn_cast<affine::AffineForOp>(owner))
      return ba == f.getInductionVar() && constantBounds(f);
    if (auto f = dyn_cast<scf::ForOp>(owner))
      return ba == f.getInductionVar() &&
             matchPattern(f.getLowerBound(), m_Constant()) &&
             matchPattern(f.getUpperBound(), m_Constant()) &&
             matchPattern(f.getStep(), m_Constant());
    auto pipe = dyn_cast<LoopSchedulePipelineOp>(owner);
    if (!pipe || !pipe.getTripCount())
      return false;
    unsigned k = ba.getArgNumber();
    auto term = dyn_cast<circt::loopschedule::LoopScheduleTerminatorOp>(
        pipe.getStagesBlock().getTerminator());
    if (!term || k >= term.getIterArgs().size())
      return false;
    Value next = term.getIterArgs()[k];
    // Through the stage that computes it.
    if (auto stage = next.getDefiningOp<LoopSchedulePipelineStageOp>()) {
      Operation *reg = stage.getBodyBlock().getTerminator();
      unsigned r = cast<OpResult>(next).getResultNumber();
      if (r >= reg->getNumOperands())
        return false;
      next = reg->getOperand(r);
    }
    auto add = next.getDefiningOp<arith::AddIOp>();
    if (!add)
      return false;
    auto isArgK = [&](Value x) {
      auto a = dyn_cast<BlockArgument>(x);
      return a && a.getArgNumber() == k &&
             a.getOwner()->getParentOp() == owner;
    };
    return (isArgK(add.getLhs()) && matchPattern(add.getRhs(), m_Constant())) ||
           (isArgK(add.getRhs()) && matchPattern(add.getLhs(), m_Constant()));
  }

  llvm::DenseMap<Value, bool> memo;
};
} // namespace

// The storage a store writes: true for an alloca or a global, false for a
// function argument (whose contents leave the function).
static bool storesToLocalArray(Value mem) {
  while (Operation *def = mem.getDefiningOp()) {
    // A member memory of a local struct array (--split-struct-memrefs):
    // Vitis computes such a table at run time and builds the core (kernel
    // w9r7i_mc_cplx_loc: `complex<float> tw[128]` filled from cos / sin of
    // the index, sin_or_cos core, 18 BRAM; the same table of float,
    // w9r7i_mc_flt_loc, and as a static global, w9r7i_mc_cplx_glob, are
    // ROMs; VITIS_NOTES N60).
    if (n60() && isa<memref::AllocaOp, memref::AllocOp>(def) &&
        (def->hasAttr("hls.struct_member") || def->hasAttr("hls.aggregated"))) {
      auto type = cast<MemRefType>(def->getResult(0).getType());
      if (!type.hasStaticShape() || type.getNumElements() > 1)
        return false;
    }
    if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(def))
      return true;
    auto view = dyn_cast<ViewLikeOpInterface>(def);
    if (!view)
      return false;
    mem = view.getViewSource();
  }
  return false;
}

// Whether every value `site`'s result reaches is an index-only value that
// ends in a store to a local or global array (see above).
static bool onlyFillsArrays(Operation *site, IndexOnlyValues &idx) {
  SmallVector<Value> work(site->getResults().begin(), site->getResults().end());
  llvm::DenseSet<Value> seen(work.begin(), work.end());
  bool stored = false;
  // A store into a struct temporary --split-struct-memrefs made registers
  // (the std::complex built from cos / sin on its way to the table): the
  // value goes on through the temporary's loads.
  auto throughTemporary = [&](Value mem) {
    Operation *storage = storageOf(mem);
    if (!isPassThroughRegister(storage))
      return false;
    for (Operation *u : storage->getResult(0).getUsers())
      if (isa<affine::AffineLoadOp, memref::LoadOp>(u))
        if (seen.insert(u->getResult(0)).second)
          work.push_back(u->getResult(0));
    return true;
  };
  while (!work.empty()) {
    Value v = work.pop_back_val();
    if (!idx.of(v))
      return false;
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (auto st = dyn_cast<affine::AffineStoreOp>(user)) {
        if (use.getOperandNumber() != 0)
          return false;
        if (throughTemporary(st.getMemRef()))
          continue;
        if (!storesToLocalArray(st.getMemRef()))
          return false;
        stored = true;
        continue;
      }
      if (auto st = dyn_cast<memref::StoreOp>(user)) {
        if (use.getOperandNumber() != 0)
          return false;
        if (throughTemporary(st.getMemRef()))
          continue;
        if (!storesToLocalArray(st.getMemRef()))
          return false;
        stored = true;
        continue;
      }
      // A store whose bank is chosen at run time (memory banking's
      // hls.store_enable per bank of a partitioned table).
      if (n60() && user->getName().getStringRef() == "hls.store_enable") {
        if (use.getOperandNumber() != 0 || !storesToLocalArray(user->getOperand(2)))
          return false;
        stored = true;
        continue;
      }
      if (auto y = dyn_cast<scf::YieldOp>(user)) {
        auto ifOp = dyn_cast<scf::IfOp>(user->getParentOp());
        if (!ifOp)
          return false;
        Value r = ifOp->getResult(use.getOperandNumber());
        if (seen.insert(r).second)
          work.push_back(r);
        continue;
      }
      if (auto ifOp = dyn_cast<scf::IfOp>(user)) {
        if (!isMemoryEffectFree(user))
          return false;
        for (Value r : user->getResults())
          if (seen.insert(r).second)
            work.push_back(r);
        continue;
      }
      if (isa<circt::loopschedule::LoopScheduleRegisterOp>(user)) {
        auto stage = cast<LoopSchedulePipelineStageOp>(user->getParentOp());
        Value r = stage->getResult(use.getOperandNumber());
        if (seen.insert(r).second)
          work.push_back(r);
        continue;
      }
      if (user->getNumRegions() != 0 ||
          (!isMemoryEffectFree(user) && !isPureCall(user)))
        return false;
      for (Value r : user->getResults())
        if (seen.insert(r).second)
          work.push_back(r);
    }
  }
  return stored;
}

static bool siteLive(const Site &s, LiveValues &lv) {
  if (s.result >= 0)
    return lv.live(s.op->getResult(s.result));
  for (Value r : s.op->getResults())
    if (lv.live(r))
      return true;
  return false;
}

static bool mayWrite(Operation *op) {
  if (auto iface = dyn_cast<MemoryEffectOpInterface>(op))
    return iface.hasEffect<MemoryEffects::Write>();
  return true; // unknown effects (a call, an op with regions)
}

// The same argument value: the same SSA value, or equal pure ops (or loads
// of the same address with no write in between) on equal operands.
static bool sameValue(Value a, Value b, unsigned depth = 8) {
  if (a == b)
    return true;
  if (depth == 0)
    return false;
  Operation *da = a.getDefiningOp(), *db = b.getDefiningOp();
  if (!da || !db || da->getName() != db->getName() ||
      da->getNumOperands() != db->getNumOperands() ||
      da->getNumRegions() != 0 || db->getNumRegions() != 0 ||
      da->getAttrDictionary() != db->getAttrDictionary() ||
      cast<OpResult>(a).getResultNumber() != cast<OpResult>(b).getResultNumber())
    return false;
  if (!isMemoryEffectFree(da)) {
    if (!isa<affine::AffineLoadOp, memref::LoadOp>(da) ||
        da->getBlock() != db->getBlock())
      return false;
    Operation *first = da->isBeforeInBlock(db) ? da : db;
    Operation *last = first == da ? db : da;
    for (Operation *o = first->getNextNode(); o && o != last; o = o->getNextNode())
      if (mayWrite(o))
        return false;
  }
  for (auto [x, y] : llvm::zip(da->getOperands(), db->getOperands()))
    if (!sameValue(x, y, depth - 1))
      return false;
  return true;
}

//===----------------------------------------------------------------------===//
// Regions.
//===----------------------------------------------------------------------===//

static bool isLoop(Operation *op) {
  return isa<LoopLikeOpInterface, LoopSchedulePipelineOp>(op);
}

static bool containsLoop(Operation *op) {
  if (isLoop(op))
    return true;
  bool found = false;
  op->walk([&](Operation *inner) {
    if (inner != op && isLoop(inner)) {
      found = true;
      return WalkResult::interrupt();
    }
    return WalkResult::advance();
  });
  return found;
}

// Whether a pipelined loop comes from a pragma: an hls.pipeline tag without
// source = "auto". Untagged (the conversion's default for an innermost loop)
// and --auto-pipeline-unroll's tags are automatic pipelining.
static bool isUserPipeline(Operation *loop) {
  Attribute tag = loop->getAttr(kLoopPipelineAttr);
  if (!tag)
    return false;
  if (auto arr = dyn_cast<ArrayAttr>(tag))
    tag = arr.empty() ? Attribute() : arr[0];
  if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
    if (auto s = dict.getAs<StringAttr>("source"))
      return s.getValue() != kLoopPipelineAutoSource;
  return true;
}

// The requested II of an hls.pipeline tag (0 when absent / automatic).
static unsigned requestedII(Operation *loop) {
  Attribute tag = loop->getAttr(kLoopPipelineAttr);
  if (auto arr = dyn_cast_or_null<ArrayAttr>(tag))
    tag = arr.empty() ? Attribute() : arr[0];
  if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
    if (auto ii = dict.getAs<IntegerAttr>("II"))
      return ii.getInt() > 0 ? static_cast<unsigned>(ii.getInt()) : 0;
  return 0;
}

// The II a pipelined loop that hls-est could not schedule reaches at least:
// each array (each bank after partitioning) has two ports, so a loop body
// that accesses one array n times per iteration needs ceil(n / 2) cycles per
// iteration (softmax loops with 4 unrolled exp calls next to 8 accesses of
// one array reach II 4 in Vitis and build one exp core). Loops hls-est leaves
// unscheduled are typically those with a math call in them: the scheduler
// does not take external calls.
static unsigned portBoundII(Operation *loop) {
  llvm::DenseMap<const void *, unsigned> perArray;
  loop->walk([&](Operation *op) {
    Value mem;
    if (auto l = dyn_cast<affine::AffineLoadOp>(op))
      mem = l.getMemRef();
    else if (auto s = dyn_cast<affine::AffineStoreOp>(op))
      mem = s.getMemRef();
    else if (auto l = dyn_cast<memref::LoadOp>(op))
      mem = l.getMemRef();
    else if (auto s = dyn_cast<memref::StoreOp>(op))
      mem = s.getMemRef();
    if (!mem)
      return;
    StorageRoot root = storageRoot(mem);
    const void *key = root.global ? static_cast<const void *>(root.global)
                                  : root.value.getAsOpaquePointer();
    ++perArray[key];
  });
  unsigned ii = 1;
  for (auto &[key, n] : perArray)
    ii = std::max(ii, (n + 1) / 2);
  return ii;
}

// The number of copies --auto-pipeline-unroll made of a loop body when it
// unrolled the inner loops of `loop` into it (the product of the factors in
// hls.auto_unrolled; 1 without).
static unsigned autoUnrollCopies(Operation *loop) {
  uint64_t copies = 1;
  if (auto arr = loop->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
    for (Attribute a : arr)
      if (auto dict = dyn_cast<DictionaryAttr>(a))
        if (auto f = dict.getAs<IntegerAttr>("factor"))
          if (f.getInt() > 1)
            copies = std::min<uint64_t>(copies * f.getInt(), 1u << 20);
  return static_cast<unsigned>(copies);
}

// A pipelined loop around a call of a core that keeps Vitis from pipelining
// automatically (blocks_automatic_pipelining: the double sin / cos core has
// loops of variable trip count inside): unless the loop carries a pipeline
// pragma, Vitis leaves it, and the loops it would have unrolled into it,
// sequential; the call runs as sequential code once per original call site.
static bool keptSequential(const Site &s, Operation *loop) {
  return s.entry && s.entry->blocksAutoPipelining && !isUserPipeline(loop);
}

static void placeSite(Site &s,
                      llvm::DenseMap<Block *, llvm::DenseMap<Operation *, unsigned>>
                          &stretchOf) {
  for (Operation *p = s.op->getParentOp(); p && !isa<func::FuncOp>(p);
       p = p->getParentOp()) {
    if (isa<LoopSchedulePipelineOp>(p) ||
        (isa<affine::AffineForOp, scf::ForOp>(p) &&
         p->hasAttr(kLoopPipelineAttr) && !p->hasAttr(kLoopPipelineOffAttr))) {
      if (keptSequential(s, p)) {
        // One stretch for the whole loop body (its stages included).
        s.notPipelined = true;
        s.unrollCopies = autoUnrollCopies(p);
        s.scope = p;
        s.block = nullptr;
        s.stretch = 0;
        return;
      }
    }
    if (auto pl = dyn_cast<LoopSchedulePipelineOp>(p)) {
      s.pipeline = p;
      s.ii = std::max<unsigned>(1, static_cast<unsigned>(pl.getII()));
      s.userPipeline = isUserPipeline(p);
      return;
    }
    if (isa<affine::AffineForOp, scf::ForOp>(p) &&
        p->hasAttr(kLoopPipelineAttr) && !p->hasAttr(kLoopPipelineOffAttr)) {
      s.pipeline = p;
      // Not scheduled: the requested II, raised to what the ports allow.
      s.ii = std::max(requestedII(p), portBoundII(p));
      s.iiAssumed = true;
      s.userPipeline = isUserPipeline(p);
      return;
    }
  }
  Operation *cur = s.op;
  while (true) {
    Operation *p = cur->getParentOp();
    if (!p || isa<func::FuncOp>(p) || isLoop(p)) {
      s.scope = p;
      break;
    }
    cur = p;
  }
  s.block = cur->getBlock();
  auto &index = stretchOf[s.block];
  if (index.empty()) {
    unsigned k = 0;
    for (Operation &o : *s.block) {
      index[&o] = k;
      if (containsLoop(&o))
        ++k; // a nested loop ends the stretch
    }
  }
  s.stretch = index.lookup(cur);
}

// The storage roots of the arrays the ops inside `op` access.
static void accessedRoots(Operation *op, SmallVectorImpl<StorageRoot> &out) {
  op->walk([&](Operation *inner) {
    for (Value v : inner->getOperands())
      if (isa<BaseMemRefType>(v.getType())) {
        StorageRoot r = storageRoot(v);
        if (!llvm::is_contained(out, r))
          out.push_back(r);
      }
  });
}

// Whether two calls of sequential code may run at the same time (they do
// when neither depends on the other, which groupConcurrentCalls decides):
//   - calls of one straight-line stretch (two independent calls: two cores);
//   - calls inside two different loops of the function body that access no
//     common array: Vitis outlines such loops into modules of their own and
//     runs them concurrently (two `pipeline off` loops, one exp call each on
//     disjoint arrays: two exp cores, one per outlined loop, and the latency
//     of one loop).
// Every other pair runs one after the other and shares the instances: two
// such loops that both read one input array, or where the second reads what
// the first wrote; the same two loops nested in an outer loop; calls in
// straight-line code before and after a loop, also when the loop calls the
// function too (one exp core and the summed latency in each case).
// Unconfirmed: loops inside a conditional of the function body.
static bool mayOverlapInSequentialCode(const Site &a, const Site &b) {
  if (a.scope == b.scope && a.block == b.block && a.stretch == b.stretch)
    return true;
  // The ops holding a and b in their innermost common block.
  llvm::DenseMap<Block *, Operation *> holderOfA;
  for (Operation *p = a.op; p; p = p->getParentOp())
    holderOfA.try_emplace(p->getBlock(), p);
  for (Operation *q = b.op; q; q = q->getParentOp()) {
    auto it = holderOfA.find(q->getBlock());
    if (it == holderOfA.end())
      continue;
    Operation *x = it->second;
    if (x == q || !isLoop(x) || !isLoop(q) ||
        !isa<func::FuncOp>(q->getParentOp()))
      return false;
    SmallVector<StorageRoot, 8> rootsA, rootsB;
    accessedRoots(x, rootsA);
    accessedRoots(q, rootsB);
    return llvm::none_of(rootsA, [&](const StorageRoot &r) {
      return llvm::is_contained(rootsB, r);
    });
  }
  return false;
}

static std::string locText(Location loc) {
  std::string out;
  llvm::raw_string_ostream os(out);
  loc.print(os);
  return out;
}

//===----------------------------------------------------------------------===//
// Analysis.
//===----------------------------------------------------------------------===//

/// N178 widened (W9r23 review D5): Vitis hoists the library core of a kept
/// callee into its caller when the caller is no dataflow region, so the
/// cores of the caller's own code and of its sibling callees are one set of
/// instances, used one call after another (kernels w9r23rev_m8_pow_inlineoff2
/// (fb reads what fa writes) and w9r23fx_f3_pow_inlineoff_indep (no data
/// shared): pow in two `inline off` functions called by top, one
/// pow_generic_double_s instance in top, 30; hls-est 60 before). Applies to
/// the cores of callees instantiated once (one call site, in that caller),
/// and only when every function of the group uses one instance of the core
/// (held-out cubic_spline: a callee that needs two keeps them); a record of
/// the group keeps its instances, the most BRAM, and the others count 0
/// (shared_with_function). Cores inlined into a pipeline (shared tables, a
/// kept CORDIC loop) are not instances and stay. Unconfirmed: a callee
/// instantiated twice, and callees of callees (one level only).
static void shareCoresOfSequentialCallees(ModuleOp module,
                                          std::vector<MathCoreRecord> &records) {
  if (!circt::hlsest::Config::get().tool.hls.sequentialCoreSharing)
    return;
  // The caller of every function with exactly one call site.
  llvm::StringMap<unsigned> callCount;
  llvm::StringMap<func::FuncOp> callerOf;
  module.walk([&](func::CallOp call) {
    StringRef callee = call.getCallee();
    ++callCount[callee];
    callerOf[callee] = call->getParentOfType<func::FuncOp>();
  });
  // The group of a record: its function's caller when the function is such a
  // callee of a non-dataflow caller, else the function itself.
  auto groupOf = [&](const MathCoreRecord &r) -> std::string {
    auto it = callCount.find(r.func);
    if (it == callCount.end() || it->second != 1 || r.functionInstances != 1)
      return r.func;
    func::FuncOp caller = callerOf.lookup(r.func);
    if (!caller || caller->hasAttr("hls.dataflow"))
      return r.func;
    return caller.getName().str();
  };
  auto inlined = [](const MathCoreRecord &r) {
    return llvm::any_of(r.regions, [](const MathRegionRecord &g) {
      return g.sharedTables || g.cordicKept;
    });
  };
  std::map<std::pair<std::string, std::string>, SmallVector<size_t>> groups;
  for (size_t i = 0; i < records.size(); ++i) {
    const MathCoreRecord &r = records[i];
    if (r.status != "counted" || r.bram <= 0 || r.coreName.empty() ||
        inlined(r))
      continue;
    groups[{groupOf(r), r.coreName}].push_back(i);
  }
  for (auto &[key, members] : groups) {
    // Per function, the instances and the BRAM of its records of the core
    // (sin and cos of one function that can run together are two records,
    // two instances: N169). Vitis moves the core to the caller only when
    // every function of the group uses one instance: a callee that needs
    // two keeps them, and so do the others (held-out quantitative_finance
    // cubic_spline: pow twice in the sequential code of CS, once in CS1,
    // both called by dut: 2 + 1 pow_generic_double_s, 90; kernel
    // w9r23fx_f5_pow_inlineoff_seq, one straight-line pow in each of two
    // callees: one instance in top, 30).
    std::map<std::string, int64_t> perFunction;
    std::map<std::string, unsigned> instancesOf;
    for (size_t i : members) {
      perFunction[records[i].func] += records[i].bram;
      instancesOf[records[i].func] += records[i].instances;
    }
    if (perFunction.size() < 2 ||
        llvm::any_of(instancesOf, [](const auto &kv) { return kv.second != 1; }))
      continue;
    std::string keep = perFunction.begin()->first;
    for (auto &[fn, b] : perFunction)
      if (b > perFunction[keep])
        keep = fn;
    for (size_t i : members) {
      MathCoreRecord &r = records[i];
      if (r.func == keep)
        continue;
      r.sharedWithFunction = keep;
      r.reason += "; shares the " + r.coreName + " instance(s) of @" + keep +
                  ": Vitis makes the core once in @" + key.first +
                  ", which runs its callees one after another (N178) -> 0";
      r.instances = 0;
      r.bram = 0;
    }
  }
}

std::vector<MathCoreRecord>
analyzeMathCores(ModuleOp module, const MathCostConfig &config,
                 llvm::function_ref<bool(Operation *)> covers,
                 llvm::function_ref<unsigned(Operation *)> instancesOf,
                 llvm::function_ref<void(Location, const std::string &)> warn,
                 llvm::function_ref<int64_t(int64_t, unsigned, unsigned)>
                     romBlocks) {
  std::vector<Site> sites;
  module.walk([&](Operation *op) {
    if (!covers(op) || !op->getParentOfType<func::FuncOp>())
      return;
    SmallVector<Site, 2> found;
    recognise(op, found);
    for (Site &s : found) {
      if (!coreFunctions().contains(s.function) &&
          !llvm::any_of(config.entries, [&](const MathCostEntry &e) {
            return e.function == s.function;
          }))
        continue;
      auto fn = op->getParentOfType<func::FuncOp>();
      s.func = fn.getName().str();
      s.funcOp = fn.getOperation();
      sites.push_back(std::move(s));
    }
  });

  // VITIS_NOTES N106: an ap_fixed hls::exp the cost table does not list
  // costs the ROM tables of the template branch its type selects, which
  // cgeist emitted and --lower-polygeist-subindex recorded on the core
  // (hls.core_tables) before dropping its body; each table is a one-read
  // ROM; one set per instance (per_concurrent_call). Kernels w9r14p_ex_21_9
  // / ex_24_12 (256x50, 256x46, 32x32: 5), ex_32_8 (7).
  std::deque<MathCostEntry> synthesised;
  llvm::StringMap<const MathCostEntry *> synthesisedFor;
  auto tableEntry = [&](const Site &s) -> const MathCostEntry * {
    if (!romBlocks ||
        !circt::hlsest::Config::get().tool.hls.fixedExpTablesWhenUnlisted ||
        s.function != "exp" ||
        !(StringRef(s.type).starts_with("ap_fixed<") ||
          StringRef(s.type).starts_with("ap_ufixed<")))
      return nullptr;
    auto call = dyn_cast<func::CallOp>(s.op);
    func::FuncOp callee = call ? externalCallee(call) : func::FuncOp();
    auto tables =
        callee ? callee->getAttrOfType<ArrayAttr>("hls.core_tables") : nullptr;
    if (!tables)
      return nullptr;
    auto [it, inserted] = synthesisedFor.try_emplace(callee.getName(), nullptr);
    if (!inserted)
      return it->second;
    MathCostEntry e;
    e.index = static_cast<unsigned>(config.entries.size() + synthesised.size());
    e.function = s.function;
    e.type = s.type;
    e.coreKind = "library_module";
    e.instancing = "per_concurrent_call";
    // exp_<W>_<I>_s, the module Vitis builds.
    std::string wi = s.type.substr(s.type.find('<') + 1);
    wi = wi.substr(0, wi.find('>'));
    std::replace(wi.begin(), wi.end(), ',', '_');
    e.cores.push_back("exp_" + wi + "_s");
    for (Attribute t : tables) {
      auto a = dyn_cast<ArrayAttr>(t);
      if (!a || a.size() < 2)
        continue;
      auto words = dyn_cast<IntegerAttr>(a[0]);
      auto bits = dyn_cast<IntegerAttr>(a[1]);
      if (!words || !bits)
        continue;
      int64_t blocks =
          romBlocks(words.getInt(), static_cast<unsigned>(bits.getInt()), 1);
      e.bram += blocks;
      e.tableShapes.push_back(
          {words.getInt(), static_cast<unsigned>(bits.getInt())});
      if (blocks && e.tableName.empty() && a.size() > 2)
        if (auto n = dyn_cast<StringAttr>(a[2]))
          e.tableName = n.getValue().str();
    }
    synthesised.push_back(std::move(e));
    return it->second = &synthesised.back();
  };

  LiveValues lv;
  IndexOnlyValues idx;
  llvm::DenseMap<Block *, llvm::DenseMap<Operation *, unsigned>> stretchOf;
  for (Site &s : sites) {
    auto isConst = [](Value v) { return matchPattern(v, m_Constant()); };
    s.folded = !s.args.empty() && llvm::all_of(s.args, isConst);
    if (s.function == "pow" && s.args.size() == 2 && !s.folded) {
      if (isConst(s.args[0]))
        s.argForm = "constant base";
      else if (isConst(s.args[1]))
        s.argForm = "constant exponent";
    }
    s.entry = config.lookup(s.function, s.type, s.argForm);
    if (!s.entry)
      s.entry = tableEntry(s);
    if (!s.folded && llvm::all_of(s.args, [&](Value a) { return idx.of(a); }) &&
        onlyFillsArrays(s.op, idx)) {
      s.folded = true;
      s.fillOnly = true;
    }
    s.dead = !s.folded && !siteLive(s, lv);
    s.remainder = !s.folded && !s.dead &&
                  s.op->hasAttr(circt::hls_analysis::kUnrollRemainderAttr);
    placeSite(s, stretchOf);
  }

  // Shared instances (shares_instance_with): pair each call with at most one
  // call of each listed function on an equivalent argument in its region.
  auto sameRegion = [](const Site &a, const Site &b) {
    if (a.pipeline || b.pipeline)
      return a.pipeline == b.pipeline;
    return a.scope == b.scope && a.block == b.block && a.stretch == b.stretch;
  };
  auto counted = [](const Site &s) {
    return !s.folded && !s.dead && !s.remainder;
  };
  for (size_t i = 0; i < sites.size(); ++i) {
    Site &s = sites[i];
    if (!counted(s) || !s.entry || s.sharedWith >= 0 ||
        s.entry->sharesInstanceWith.empty() || s.args.empty())
      continue;
    llvm::StringSet<> taken;
    for (size_t j = 0; j < sites.size(); ++j) {
      Site &t = sites[j];
      if (j == i || !counted(t) || t.sharedWith >= 0 || t.func != s.func ||
          t.type != s.type || t.args.empty() || taken.contains(t.function) ||
          !llvm::is_contained(s.entry->sharesInstanceWith, t.function) ||
          !sameRegion(s, t) || !sameValue(s.args[0], t.args[0]))
        continue;
      // t must not own an instance others already joined.
      if (llvm::any_of(sites, [&](const Site &u) {
            return u.sharedWith == static_cast<int>(j);
          }))
        continue;
      t.sharedWith = static_cast<int>(i);
      taken.insert(t.function);
    }
  }

  // Records: one per (function, entry or unlisted pair).
  std::vector<MathCoreRecord> records;
  std::map<std::string, size_t> recordOf;
  std::vector<std::vector<size_t>> members; // site indices per record
  std::vector<const MathCostEntry *> recordEntries; // per record
  // Calls of different functions whose entries name one library module (sin
  // and cos of double: sin_or_cos_double_s) are calls of that module when
  // no call of one function can run together with a call of the other: they
  // then form one record, whose instances are counted like the calls of one
  // function. Such a pair lies in exclusive arms of an if (VITIS_NOTES N169
  // w9r22p_d3_sincos_branch: one module), in two stretches of sequential
  // code that run one after the other (W9 round 22 review kernel
  // w9r22rv_k12_sin_then_cos, sin in one loop and cos in the next reading
  // the same array: one module, 8), or in one stretch with the result of one
  // reaching the other within the iteration (w9r22fx_f4_sin_cos_seq,
  // `cos(in[1] + sin(in[0]))`: 8). Calls that can run together keep a module
  // each: sin and cos in one loop body linked only across iterations (N107
  // w9r14p_dc_live: two modules, 16), sin and cos in two loops on disjoint
  // arrays, which Vitis outlines and runs concurrently (w9r22fx_f3: 16).
  const bool sharedModules =
      circt::hlsest::Config::get().tool.hls.sharedLibraryModules;
  auto sharableModule = [&](const Site &s) -> std::string {
    if (!sharedModules || !s.entry || s.entry->coreKind != "library_module" ||
        s.entry->arguments != "any" || s.entry->cores.empty())
      return "";
    return s.entry->cores.front();
  };
  DenseSet<size_t> sharedSites;
  {
    std::map<std::pair<std::string, std::string>, SmallVector<size_t>> byModule;
    for (size_t i = 0; i < sites.size(); ++i)
      if (std::string m = sharableModule(sites[i]); !m.empty())
        byModule[{sites[i].func, m}].push_back(i);
    // Whether b uses a value a computes within one iteration (SSA uses,
    // not across a loop's iterations).
    auto feeds = [](const Site &a, const Site &b) {
      SetVector<Operation *> slice;
      getForwardSlice(a.op, &slice);
      return slice.contains(b.op);
    };
    auto cannotOverlap = [&](const Site &a, const Site &b) {
      if (a.pipeline || b.pipeline)
        return false;
      if (circt::hls_analysis::inExclusiveArms(a.op, b.op))
        return true;
      if (!mayOverlapInSequentialCode(a, b))
        return true;
      return a.scope == b.scope && a.block == b.block &&
             a.stretch == b.stretch && (feeds(a, b) || feeds(b, a));
    };
    for (auto &[key, idx] : byModule) {
      bool sharable = true, severalFunctions = false;
      for (size_t x = 0; x < idx.size() && sharable; ++x)
        for (size_t y = x + 1; y < idx.size() && sharable; ++y) {
          const Site &a = sites[idx[x]], &b = sites[idx[y]];
          if (a.function == b.function)
            continue;
          severalFunctions = true;
          sharable = cannotOverlap(a, b);
        }
      if (sharable && severalFunctions)
        sharedSites.insert(idx.begin(), idx.end());
    }
  }
  auto keyOf = [&](const Site &s) {
    std::string k = s.func + "|";
    size_t index = static_cast<size_t>(&s - sites.data());
    if (sharedSites.contains(index))
      return k + "core:" + sharableModule(s);
    if (s.entry)
      return k + "#" + std::to_string(s.entry->index);
    return k + s.function + "|" + s.type + "|" + s.argForm;
  };
  for (size_t i = 0; i < sites.size(); ++i) {
    const Site &s = sites[i];
    const Site &owner = s.sharedWith >= 0 ? sites[s.sharedWith] : s;
    std::string key = keyOf(owner);
    auto [it, inserted] = recordOf.try_emplace(key, records.size());
    if (inserted) {
      MathCoreRecord r;
      r.func = owner.func;
      r.functionInstances = std::max(1u, instancesOf(owner.funcOp));
      r.function = owner.function;
      r.type = owner.type;
      r.arguments = owner.argForm;
      r.typeSource = owner.typeSource;
      r.loc = locText(owner.op->getLoc());
      r.configPath = config.path;
      recordEntries.push_back(owner.entry);
      if (const MathCostEntry *e = owner.entry) {
        if (e->index < config.entries.size())
          r.entry = e->index;
        r.entryInfo = *e;
        r.arguments = e->arguments;
        r.coreKind = e->coreKind;
        r.instancing = e->instancing;
        r.bramPerInstance = e->bram;
        r.coreName = !e->cores.empty()      ? e->cores.front()
                     : !e->tableName.empty() ? e->tableName
                                             : e->function + "_" + e->type;
      } else {
        r.coreName = owner.function + "(" + owner.type + ")";
      }
      records.push_back(std::move(r));
      members.emplace_back();
    }
    members[it->second].push_back(i);
    // A record shared by several functions (sin and cos of one module,
    // N169) names them all: "cos,sin".
    MathCoreRecord &rec = records[it->second];
    if (owner.function != rec.function) {
      SmallVector<StringRef> names;
      StringRef(rec.function).split(names, ',');
      if (!llvm::is_contained(names, StringRef(owner.function))) {
        std::vector<std::string> all(names.begin(), names.end());
        all.push_back(owner.function);
        llvm::sort(all);
        rec.function = llvm::join(all, ",");
      }
    }
  }

  std::set<std::string> warnedPairs;
  for (size_t ri = 0; ri < records.size(); ++ri) {
    MathCoreRecord &r = records[ri];
    const MathCostEntry *e = recordEntries[ri];
    // Group the instance owners by region.
    std::vector<Operation *> pipeOrder;
    llvm::DenseMap<Operation *, SmallVector<const Site *>> perPipe;
    std::vector<std::tuple<Operation *, Block *, unsigned>> seqOrder;
    std::map<std::tuple<Operation *, Block *, unsigned>, SmallVector<const Site *>>
        perStretch;
    unsigned live = 0, folded = 0, dead = 0;
    const Site *firstLive = nullptr;
    for (size_t si : members[ri]) {
      const Site &s = sites[si];
      if (!s.folded && !s.dead && !firstLive)
        firstLive = &s;
      MathSiteRecord sr;
      sr.op = s.opText;
      sr.loc = locText(s.op->getLoc());
      if (s.folded) {
        sr.status = "folded";
        sr.detail = s.fillOnly
                        ? "fills an array from loop indices and constants: "
                          "evaluated at compile time"
                        : "every argument is a constant (const_fold)";
        ++folded;
      } else if (s.dead) {
        sr.status = "dead";
        sr.detail = "the result reaches no output";
        ++dead;
      } else if (s.remainder) {
        sr.status = "remainder";
        sr.detail = "a remainder iteration of a partial unroll: Vitis runs it "
                    "in the exit-checked copies of the unrolled loop, whose "
                    "calls are counted";
        ++live;
      } else if (s.sharedWith >= 0) {
        sr.status = "shared";
        sr.detail = "shares the instance of the " +
                    sites[s.sharedWith].function + " call at " +
                    locText(sites[s.sharedWith].op->getLoc()) +
                    " (same argument)";
        ++live;
      } else {
        sr.status = "counted";
        ++live;
        if (s.pipeline) {
          if (!perPipe.count(s.pipeline))
            pipeOrder.push_back(s.pipeline);
          perPipe[s.pipeline].push_back(&s);
          sr.detail = "pipelined loop at " + locText(s.pipeline->getLoc());
        } else {
          auto key = std::make_tuple(s.scope, s.block, s.stretch);
          if (!perStretch.count(key))
            seqOrder.push_back(key);
          perStretch[key].push_back(&s);
          sr.detail = std::string(s.notPipelined
                                      ? "sequential (a loop Vitis does not "
                                        "pipeline around this core), stretch "
                                      : "sequential, stretch ") +
                      std::to_string(s.stretch) +
                      " of " +
                      (s.scope ? locText(s.scope->getLoc())
                               : std::string("the function"));
        }
      }
      r.sites.push_back(std::move(sr));
    }

    int64_t perInst = e ? e->bram : 0;
    bool cordic = e && e->instancing == "cordic_loop";
    const bool shareTables =
        romBlocks &&
        circt::hlsest::Config::get().tool.hls.inlinedTablesInPipelines;
    unsigned pipeInst = 0;
    int64_t bram = 0;
    // N178 (tool.hls.math_library.sequential_core_sharing): exclusive arms
    // share, and the pipelined loops of a function that is no dataflow
    // region run one after another and share. Calls of sequential code keep
    // the readiness grouping below (N116): two pow of scalar arguments in
    // straight-line code are 2 cores in Vitis (held-out adam_optimizer,
    // cubic_spline), though kernel w9r23p_m6 (inputs read from an array)
    // shows 1 (OPEN_ISSUES O247).
    const bool coreSharing =
        circt::hlsest::Config::get().tool.hls.sequentialCoreSharing &&
        !cordic;
    const bool dataflowOwner =
        firstLive && firstLive->funcOp &&
        firstLive->funcOp->hasAttr("hls.dataflow");
    unsigned maxPipeInst = 0;
    int64_t maxPipeBram = 0;
    bool pipeInlinedTables = false; // a region's core is inlined (N16 R6)
    for (Operation *p : pipeOrder) {
      const auto &v = perPipe[p];
      const Site *first = v.front();
      MathRegionRecord reg;
      reg.kind = "pipeline";
      reg.loc = locText(p->getLoc());
      reg.ii = first->ii;
      reg.iiAssumed = first->iiAssumed;
      reg.source = first->userPipeline ? "user" : "auto";
      reg.calls = v.size();
      unsigned perIteration = reg.calls;
      if (coreSharing && v.size() > 1) {
        SmallVector<Operation *> ops;
        for (const Site *s : v)
          ops.push_back(s->op);
        perIteration = std::max(
            1u, circt::hls_analysis::maxStoresInOneIteration(ops, p));
      }
      reg.instances = (perIteration + reg.ii - 1) / reg.ii;
      reg.bramPerInstance = perInst;
      if (cordic) {
        // The CORDIC loop is unrolled into this pipeline (its table folds)
        // unless the entry is unrolled only by a pragma and this pipeline is
        // automatic: then the CORDIC loop stays a loop, the innermost
        // pipelined one, one per call site.
        reg.cordicKept =
            e->cordicUnrolledIn == "user_pipeline" && !first->userPipeline;
        if (reg.cordicKept) {
          llvm::StringSet<> locs;
          for (const Site *s : v)
            locs.insert(locText(s->op->getLoc()));
          reg.instances = locs.size();
        } else if (e->bramIfUnrolled) {
          reg.bramPerInstance = *e->bramIfUnrolled;
        }
      }
      // VITIS_NOTES N16 R6: Vitis inlines an ap_fixed library core into a
      // pipelined caller; its tables become caller ROMs read by every
      // concurrent call (v3x2 exp_32_16: two calls per cycle, 5 = one set;
      // v4: four, 16; W9r14 review kernel w9r14rv_ex_21_9u2: 5).
      // The copies of a user `unroll` pragma keep the core a module per copy
      // (corpus: anuvab / ayush / kaihong / ritik lab2 `unroll factor=F`,
      // ben_hall lab2 a complete `unroll` in the pipeline: exp_*_s modules;
      // inlined: zijun_wang lab2, the pipeline's own unroll of an inner
      // loop, and the kernels' textual calls).
      bool userUnrolled = llvm::any_of(v, [](const Site *s) {
        return s->op->hasAttr(circt::hls_analysis::kUserUnrollCopyAttr);
      });
      if (shareTables && e && !cordic && reg.instances > 1 && !userUnrolled &&
          e->coreKind == "library_module" && !e->tableShapes.empty() &&
          (StringRef(e->type).starts_with("ap_fixed<") ||
           StringRef(e->type).starts_with("ap_ufixed<"))) {
        reg.sharedTables = true;
        for (auto [words, bits] : e->tableShapes)
          reg.sharedTablesBram += romBlocks(words, bits, reg.instances);
      }
      int64_t regionBram = reg.sharedTables
                               ? reg.sharedTablesBram
                               : reg.instances * reg.bramPerInstance;
      pipeInst += reg.instances;
      bram += regionBram;
      pipeInlinedTables |= reg.sharedTables || reg.cordicKept;
      maxPipeInst = std::max(maxPipeInst, reg.instances);
      maxPipeBram = std::max(maxPipeBram, regionBram);
      r.regions.push_back(std::move(reg));
    }
    if (coreSharing && !dataflowOwner && pipeOrder.size() > 1) {
      pipeInst = maxPipeInst;
      bram = maxPipeBram;
    }
    // Sequential code: the calls of every stretch together, grouped into
    // instances like the calls of a non-inlined callee. Copies of one call
    // site made by hls-est's automatic unrolling of a loop Vitis leaves
    // sequential run one after the other: one copy of the body stands for
    // them.
    std::vector<Operation *> seqOps;
    std::vector<const Site *> seqSites;
    std::vector<size_t> seqRegion; // region record of each entry of seqOps
    size_t firstSeqRegion = r.regions.size();
    for (const auto &key : seqOrder) {
      const auto &v = perStretch[key];
      MathRegionRecord reg;
      reg.kind = "sequential";
      Operation *scope = std::get<0>(key);
      reg.loc = (scope ? locText(scope->getLoc()) : std::string("function")) +
                " stretch " + std::to_string(std::get<2>(key));
      reg.calls = v.size();
      std::vector<const Site *> kept(v.begin(), v.end());
      if (v.front()->notPipelined) {
        unsigned copies = v.front()->unrollCopies;
        reg.kind = "sequential (loop not pipelined by Vitis)";
        reg.unrollCopies = copies;
        // The unrolled body is the original body `copies` times in a row:
        // its first ceil(n / copies) calls are one copy.
        kept.resize(std::max<size_t>(1, (v.size() + copies - 1) / copies));
      }
      for (const Site *s : kept) {
        seqOps.push_back(s->op);
        seqSites.push_back(s);
        seqRegion.push_back(r.regions.size());
      }
      reg.bramPerInstance = perInst;
      r.regions.push_back(std::move(reg));
    }
    unsigned seqInst = 0;
    std::string seqRule;
    if (!seqOps.empty()) {
      SmallVector<unsigned> group;
      seqInst = groupConcurrentCalls(
          cast<func::FuncOp>(firstLive->funcOp), seqOps, std::nullopt, group,
          &seqRule, [&](unsigned i, unsigned j) {
            return !mayOverlapInSequentialCode(*seqSites[i], *seqSites[j]);
          });
      // Per region: the instances its own calls use.
      std::map<size_t, std::set<unsigned>> used;
      for (size_t k = 0; k < seqOps.size(); ++k)
        used[seqRegion[k]].insert(group[k]);
      for (size_t ri2 = firstSeqRegion; ri2 < r.regions.size(); ++ri2)
        r.regions[ri2].instances = used[ri2].size();
    }
    // N178 widened (W9r23 review D5): the sequential code of a function that
    // is no dataflow region runs before or after its pipelined loops, never
    // during them, so the two share the core's instances (kernel
    // w9r23rev_m9_pow_pipe_seq, pow in a pipelined loop and in a `pipeline
    // off` loop: Vitis one pow_generic_double_s, 30; hls-est 60 before;
    // w9r23fx_f4_pow_seq_then_pipe, a straight-line pow before the loop).
    // An inlined core (shared tables, a kept CORDIC loop) is no instance.
    // As across callees (shareCoresOfSequentialCallees), only when each side
    // uses one instance (more is unconfirmed: held-out cubic_spline keeps a
    // callee's two pow instances apart from its sibling's one).
    if (coreSharing && !dataflowOwner && pipeInst == 1 && seqInst == 1 &&
        !pipeInlinedTables) {
      int64_t seqBram = static_cast<int64_t>(seqInst) * perInst;
      r.sharedAcrossRegions = true;
      r.instances = std::max(pipeInst, seqInst);
      bram = std::max(bram, seqBram);
    } else {
      bram += seqInst * perInst;
      r.instances = pipeInst + seqInst;
    }
    // A callee kept as a module carries its cores in every instance.
    unsigned mult = r.functionInstances;
    r.instances *= mult;
    bram *= mult;

    if (!e) {
      r.status = live ? "unknown_cost" : folded ? "folded" : "dead";
      r.bram = 0;
      r.bramPerInstance = 0;
      r.reason = "no entry for " + r.function + " of " + r.type +
                 (r.arguments != "any" ? " (" + r.arguments + ")" : "") +
                 " in " + config.path + ": unknown cost, 0 assumed";
      // One warning per unlisted (function, type, argument form), however
      // many functions call it.
      if (live && warnedPairs
                      .insert(r.function + "|" + r.type + "|" + r.arguments)
                      .second)
        warn(firstLive ? firstLive->op->getLoc()
                       : UnknownLoc::get(module.getContext()),
             r.reason);
      continue;
    }
    r.bram = bram;
    if (!live) {
      r.status = folded ? "folded" : "dead";
      r.reason = folded ? "every call is evaluated at compile time (constant "
                          "arguments, or an array fill from loop indices)"
                        : "no call result reaches an output";
      continue;
    }
    r.status = "counted";
    std::string why = e->instancing + ": ";
    bool firstPart = true;
    for (const MathRegionRecord &reg : r.regions) {
      if (!firstPart)
        why += "; ";
      firstPart = false;
      if (reg.kind == "pipeline" && reg.cordicKept)
        why += std::to_string(reg.calls) +
               " call(s) in an automatically pipelined loop: the CORDIC loop "
               "stays a loop (one per call site) -> " +
               std::to_string(reg.instances) + " x " +
               std::to_string(reg.bramPerInstance);
      else if (reg.kind == "pipeline" && reg.sharedTables)
        why += std::to_string(reg.calls) + " call(s) per iteration at II " +
               std::to_string(reg.ii) + (reg.iiAssumed ? " (estimated)" : "") +
               " -> the core is inlined: one set of tables read " +
               std::to_string(reg.instances) + " times per cycle (N16 R6) = " +
               std::to_string(reg.sharedTablesBram);
      else if (reg.kind == "pipeline")
        why += std::to_string(reg.calls) + " call(s) per iteration at II " +
               std::to_string(reg.ii) + (reg.iiAssumed ? " (estimated)" : "") +
               " -> " + std::to_string(reg.instances) + " x " +
               std::to_string(reg.bramPerInstance);
      else
        why += std::to_string(reg.calls) + " sequential call(s) using " +
               std::to_string(reg.instances) + " instance(s)";
    }
    if (seqInst)
      why += "; sequential code: " + seqRule + " x " +
             std::to_string(perInst);
    if (r.sharedAcrossRegions)
      why += "; the pipelined loops and the sequential code run one after "
             "another and share the instances (N178) -> " +
             std::to_string(r.instances);
    if (mult != 1)
      why += "; x " + std::to_string(mult) + " instance(s) of @" + r.func;
    r.reason = why;
  }
  shareCoresOfSequentialCallees(module, records);
  return records;
}

//===----------------------------------------------------------------------===//
// Debug output.
//===----------------------------------------------------------------------===//

llvm::json::Object mathCoreJson(const MathCoreRecord &r) {
  llvm::json::Object o;
  o["function"] = r.function;
  o["type"] = r.type;
  o["type_source"] = r.typeSource;
  o["arguments"] = r.arguments;
  o["config"] = r.configPath;
  o["config_entry"] = r.entry ? llvm::json::Value(static_cast<int64_t>(*r.entry))
                              : llvm::json::Value(nullptr);
  o["core"] = r.coreName;
  o["core_kind"] = r.coreKind.empty() ? llvm::json::Value(nullptr)
                                      : llvm::json::Value(r.coreKind);
  o["instancing"] = r.instancing.empty() ? llvm::json::Value(nullptr)
                                         : llvm::json::Value(r.instancing);
  o["bram_per_instance"] = r.bramPerInstance;
  o["instances"] = static_cast<int64_t>(r.instances);
  o["function_instances"] = static_cast<int64_t>(r.functionInstances);
  if (r.sharedAcrossRegions)
    o["shared_across_regions"] = true;
  if (!r.sharedWithFunction.empty())
    o["shared_with_function"] = r.sharedWithFunction;
  o["reason"] = r.reason;
  llvm::json::Array regions;
  for (const MathRegionRecord &g : r.regions) {
    llvm::json::Object x;
    x["kind"] = g.kind;
    x["loc"] = g.loc;
    if (g.kind == "pipeline") {
      x["ii"] = static_cast<int64_t>(g.ii);
      x["ii_assumed"] = g.iiAssumed;
      x["source"] = g.source;
      x["cordic_loop_kept"] = g.cordicKept;
    }
    if (g.unrollCopies > 1)
      x["unroll_copies"] = static_cast<int64_t>(g.unrollCopies);
    x["calls"] = static_cast<int64_t>(g.calls);
    x["instances"] = static_cast<int64_t>(g.instances);
    x["bram_per_instance"] = g.bramPerInstance;
    if (g.sharedTables) {
      x["shared_tables"] = true;
      x["shared_tables_bram"] = g.sharedTablesBram;
    }
    regions.push_back(std::move(x));
  }
  o["regions"] = std::move(regions);
  llvm::json::Array sites;
  for (const MathSiteRecord &s : r.sites)
    sites.push_back(llvm::json::Object{{"op", s.op},
                                       {"loc", s.loc},
                                       {"status", s.status},
                                       {"detail", s.detail}});
  o["sites"] = std::move(sites);
  return o;
}

void printMathCoreText(const MathCoreRecord &r, llvm::raw_ostream &os) {
  os << "  function: " << r.function << " of " << r.type << " (type from "
     << (r.typeSource == "marker"   ? "the shim marker"
          : r.typeSource == "cgeist" ? "cgeist's hls.math_core attribute"
                                     : "the MLIR element type")
     << "), arguments " << r.arguments << "\n";
  if (r.entryInfo) {
    const MathCostEntry &e = *r.entryInfo;
    os << "  config: " << r.configPath << " entries[" << e.index << "]: core "
       << r.coreName << " (" << e.coreKind << "), " << e.bram
       << " BRAM per instance, instancing " << e.instancing;
    if (e.bramIfUnrolled)
      os << ", " << *e.bramIfUnrolled << " when a "
         << (e.cordicUnrolledIn == "user_pipeline" ? "pragma-" : "")
         << "pipelined loop unrolls the CORDIC loop";
    if (!e.sharesInstanceWith.empty()) {
      os << ", shares its instance with";
      for (const std::string &f : e.sharesInstanceWith)
        os << " " << f;
    }
    os << "\n";
  } else {
    os << "  config: " << r.configPath << ": no entry (unknown cost)\n";
  }
  for (const MathRegionRecord &g : r.regions) {
    os << "  " << g.kind << " " << g.loc << ": " << g.calls << " call(s)";
    if (g.kind == "pipeline")
      os << " per iteration, " << g.source << " pipeline, II " << g.ii
         << (g.iiAssumed ? " (estimated: loop not scheduled, the requested II "
                           "or two ports per array)"
                         : "")
         << (g.cordicKept ? ", CORDIC loop kept (one per call site)" : "");
    if (g.sharedTables)
      os << " -> inlined, one set of tables read " << g.instances
         << " times per cycle = " << g.sharedTablesBram << "\n";
    else
      os << " -> " << g.instances << " instance(s) x " << g.bramPerInstance
         << "\n";
  }
  for (const MathSiteRecord &s : r.sites)
    os << "  call " << s.op << " @ " << s.loc << ": " << s.status << " ("
       << s.detail << ")\n";
  os << "  => " << r.instances << " instance(s), " << r.bram << " BRAM: "
     << r.reason << "\n";
}

void printMathCoreLine(const MathCoreRecord &r, llvm::raw_ostream &os) {
  os << "math.core function=" << r.function << " type=" << r.type;
  if (r.arguments != "any") {
    std::string a = r.arguments;
    std::replace(a.begin(), a.end(), ' ', '_');
    os << " arguments=" << a;
  }
  os << " func=@" << r.func << " instances=" << r.instances
     << " bram=" << r.bram << " (";
  if (r.status == "counted")
    os << r.coreName << ", " << r.instancing;
  else if (r.status == "unknown_cost")
    os << "unknown cost: no entry";
  else if (r.status == "folded")
    os << "folded: evaluated at compile time";
  else
    os << "dead: no call result reaches an output";
  os << ")\n";
}

} // namespace circt::hls_analysis
