

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/MathCores.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"

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

static std::string normalizedType(StringRef typeValue) {
  std::string out;
  for (char candidateValue : typeValue)
    if (candidateValue != ' ' && candidateValue != '\t')
      out.push_back(candidateValue);
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
  llvm::Expected<llvm::json::Value> doc =
      llvm::json::parse((*buf)->getBuffer());
  if (!doc) {
    error =
        "'" + path + "' is not valid JSON: " + llvm::toString(doc.takeError());
    return false;
  }
  const llvm::json::Object *root = doc->getAsObject();
  if (!root) {
    error = "'" + path + "': the top level is not a JSON object";
    return false;
  }
  if (std::optional<int64_t> valueHandle = root->getInteger("version");
      valueHandle && *valueHandle != 1) {
    error = "'" + path + "': version " + std::to_string(*valueHandle) +
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
  for (size_t loopIndex = 0; loopIndex < list->size(); ++loopIndex) {
    std::string where =
        "'" + path + "': entries[" + std::to_string(loopIndex) + "]";
    const llvm::json::Object *opHandle = (*list)[loopIndex].getAsObject();
    if (!opHandle) {
      error = where + " is not an object";
      return false;
    }
    MathCostEntry entryValue;
    entryValue.index = static_cast<unsigned>(loopIndex);
    auto needString = [&](StringRef key, std::string &out) {
      std::optional<StringRef> stringValue = opHandle->getString(key);
      if (!stringValue || stringValue->empty()) {
        error = where + ": \"" + key.str() + "\" is missing or not a string";
        return false;
      }
      out = stringValue->str();
      return true;
    };
    if (!needString("function", entryValue.function) ||
        !needString("type", entryValue.type) ||
        !needString("instancing", entryValue.instancing))
      return false;
    entryValue.type = normalizedType(entryValue.type);
    if (!kRules.contains(entryValue.instancing)) {
      error = where + ": unknown instancing rule \"" + entryValue.instancing +
              "\" (per_concurrent_call | operator | logic_only | cordic_loop "
              "| inline_tables)";
      return false;
    }
    if (const llvm::json::Value *arrayValue = opHandle->get("arguments")) {
      std::optional<StringRef> stringValue = arrayValue->getAsString();
      if (!stringValue || !kForms.contains(*stringValue)) {
        error = where + ": \"arguments\" must be \"any\", \"constant base\" "
                        "or \"constant exponent\"";
        return false;
      }
      entryValue.arguments = stringValue->str();
    }
    std::optional<int64_t> bram = opHandle->getInteger("bram_18k");
    if (!bram || *bram < 0) {
      error = where + ": \"bram_18k\" is missing or not a non-negative integer";
      return false;
    }
    entryValue.bram = *bram;

    if (entryValue.instancing == "logic_only" && entryValue.bram != 0) {
      error = where + ": instancing \"logic_only\" (no memory) needs "
                      "\"bram_18k\": 0";
      return false;
    }
    if (std::optional<StringRef> keyValue = opHandle->getString("core_kind"))
      entryValue.coreKind = keyValue->str();
    if (const llvm::json::Value *candidateValue = opHandle->get("core")) {
      if (const llvm::json::Array *arr = candidateValue->getAsArray()) {
        for (const llvm::json::Value &exprValue : *arr)
          if (std::optional<StringRef> stringValue = exprValue.getAsString())
            entryValue.cores.push_back(stringValue->str());
      } else if (std::optional<StringRef> stringValue =
                     candidateValue->getAsString()) {
        if (!stringValue->starts_with("("))
          entryValue.cores.push_back(stringValue->str());
      }
    }
    if (const llvm::json::Array *tabs = opHandle->getArray("tables"))
      for (const llvm::json::Value &typeValue : *tabs)
        if (const llvm::json::Object *to = typeValue.getAsObject())
          if (std::optional<StringRef> elementCount = to->getString("name")) {
            entryValue.tableName = elementCount->str();
            break;
          }
    entryValue.cordicTrips = opHandle->getInteger("cordic_loop_trip_count");
    entryValue.bramIfUnrolled =
        opHandle->getInteger("bram_18k_if_cordic_loop_unrolled");
    if (const llvm::json::Value *useValue =
            opHandle->get("cordic_loop_unrolled_in")) {
      std::optional<StringRef> stringValue = useValue->getAsString();
      if (!stringValue ||
          (*stringValue != "any_pipeline" && *stringValue != "user_pipeline")) {
        error = where + ": \"cordic_loop_unrolled_in\" must be "
                        "\"any_pipeline\" or \"user_pipeline\"";
        return false;
      }
      entryValue.cordicUnrolledIn = stringValue->str();
    }
    if (const llvm::json::Value *buildPoint =
            opHandle->get("blocks_automatic_pipelining")) {
      std::optional<bool> valueHandle = buildPoint->getAsBoolean();
      if (!valueHandle) {
        error = where + ": \"blocks_automatic_pipelining\" must be true or "
                        "false";
        return false;
      }
      entryValue.blocksAutoPipelining = *valueHandle;
    }
    if (const llvm::json::Value *stringValue =
            opHandle->get("shares_instance_with")) {
      const llvm::json::Array *arr = stringValue->getAsArray();
      if (!arr) {
        error = where + ": \"shares_instance_with\" must be an array of "
                        "function names";
        return false;
      }
      for (const llvm::json::Value &exprValue : *arr) {
        std::optional<StringRef> elementCount = exprValue.getAsString();
        if (!elementCount) {
          error = where + ": \"shares_instance_with\" must be an array of "
                          "function names";
          return false;
        }
        entryValue.sharesInstanceWith.push_back(elementCount->str());
      }
    }
    std::string key = entryValue.function + "|" + entryValue.type + "|" +
                      entryValue.arguments;
    if (!seen.insert(key).second) {
      error = where + ": a second entry for " + entryValue.function + " of " +
              entryValue.type + " (arguments \"" + entryValue.arguments + "\")";
      return false;
    }
    entries.push_back(std::move(entryValue));
  }
  return true;
}

const MathCostEntry *MathCostConfig::lookup(StringRef function, StringRef type,
                                            StringRef arguments) const {
  std::string typeValue = normalizedType(type);
  const MathCostEntry *any = nullptr;
  for (const MathCostEntry &entryValue : entries) {
    if (entryValue.function != function || entryValue.type != typeValue)
      continue;
    if (entryValue.arguments == arguments)
      return &entryValue;
    if (entryValue.arguments == "any")
      any = &entryValue;
  }
  return any;
}

static const llvm::StringSet<> &coreFunctions() {
  static const llvm::StringSet<> stringValue = {
      "exp",   "exp2", "exp10", "expm1", "log",   "log2",      "log10",
      "log1p", "logb", "sqrt",  "rsqrt", "cbrt",  "recip",     "sin",
      "cos",   "tan",  "sinpi", "cospi", "asin",  "acos",      "atan",
      "atan2", "sinh", "cosh",  "tanh",  "asinh", "acosh",     "atanh",
      "pow",   "erf",  "erfc",  "hypot", "fmod",  "remainder", "abs"};
  return stringValue;
}

static const llvm::StringSet<> &pureLibmHelpers() {
  static const llvm::StringSet<> stringValue = {
      "floor", "floorf", "ceil",  "ceilf", "trunc",     "truncf",
      "round", "roundf", "rint",  "rintf", "nearbyint", "nearbyintf",
      "fmin",  "fminf",  "fmax",  "fmaxf", "copysign",  "copysignf",
      "fdim",  "fdimf",  "ldexp", "ldexpf"};
  return stringValue;
}

static StringRef mathOpFunction(Operation *op) {
  static const llvm::StringMap<StringRef> memoryOp = {
      {"math.exp", "exp"},     {"math.exp2", "exp2"},   {"math.expm1", "expm1"},
      {"math.log", "log"},     {"math.log2", "log2"},   {"math.log10", "log10"},
      {"math.log1p", "log1p"}, {"math.sqrt", "sqrt"},   {"math.rsqrt", "rsqrt"},
      {"math.cbrt", "cbrt"},   {"math.sin", "sin"},     {"math.cos", "cos"},
      {"math.tan", "tan"},     {"math.tanh", "tanh"},   {"math.sinh", "sinh"},
      {"math.cosh", "cosh"},   {"math.asin", "asin"},   {"math.acos", "acos"},
      {"math.atan", "atan"},   {"math.atan2", "atan2"}, {"math.asinh", "asinh"},
      {"math.acosh", "acosh"}, {"math.atanh", "atanh"}, {"math.erf", "erf"},
      {"math.erfc", "erfc"},   {"math.powf", "pow"},    {"math.fpowi", "pow"},
      {"math.absf", "abs"}};
  auto it = memoryOp.find(op->getName().getStringRef());
  return it == memoryOp.end() ? StringRef() : it->second;
}

static constexpr StringLiteral kMarkerPrefix = "__hlsest_math_";

static std::string scalarTypeName(Type typeValue) {
  typeValue = getElementTypeOrSelf(typeValue);
  if (typeValue.isF16())
    return "half";
  if (typeValue.isBF16())
    return "bfloat16";
  if (typeValue.isF32())
    return "float";
  if (typeValue.isF64())
    return "double";
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  typeValue.print(os);
  return stringValue;
}

static func::FuncOp externalCallee(func::CallOp callSite) {
  auto fn = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
      callSite, callSite.getCalleeAttr());
  return fn && fn.isExternal() ? fn : func::FuncOp();
}

static std::string libmFunction(StringRef name) {
  if (name == "fabs" || name == "fabsf")
    return "abs";
  if (name == "abs")
    return "";
  if (coreFunctions().contains(name))
    return name.str();
  if (name.size() > 1 && name.back() == 'f' &&
      coreFunctions().contains(name.drop_back()))
    return name.drop_back().str();
  return "";
}

static bool isPureCall(Operation *op) {
  auto callSite = dyn_cast<func::CallOp>(op);
  if (!callSite)
    return false;
  func::FuncOp fn = externalCallee(callSite);
  if (!fn)
    return false;
  StringRef elementCount = fn.getName();
  return elementCount.starts_with(kMarkerPrefix) ||
         !libmFunction(elementCount).empty() ||
         pureLibmHelpers().contains(elementCount);
}

namespace {

struct Site {
  Operation *op = nullptr;
  int result = -1;
  std::string function, type, typeSource, argForm = "any", opText;
  SmallVector<Value, 2> args;
  const MathCostEntry *entry = nullptr;
  bool folded = false, dead = false;

  bool fillOnly = false;

  Operation *pipeline = nullptr;
  unsigned ii = 1;
  bool iiAssumed = false;
  bool userPipeline = false;
  Operation *scope = nullptr;
  Block *block = nullptr;
  unsigned stretch = 0;

  bool notPipelined = false;
  unsigned unrollCopies = 1;

  int sharedWith = -1;
  std::string func;
  Operation *funcOp = nullptr;
};

} // namespace

static void recognise(Operation *op, SmallVectorImpl<Site> &out) {
  if (StringRef fn = mathOpFunction(op); !fn.empty()) {
    if (op->getNumOperands() == 0)
      return;
    Site stringValue;
    stringValue.op = op;
    stringValue.function = fn.str();
    stringValue.type = scalarTypeName(op->getOperand(0).getType());
    stringValue.typeSource = "mlir";
    stringValue.opText = op->getName().getStringRef().str();
    stringValue.args.append(op->operand_begin(), op->operand_end());
    out.push_back(std::move(stringValue));
    return;
  }
  if (op->getName().getStringRef() == "math.sincos" &&
      op->getNumOperands() == 1 && op->getNumResults() == 2) {
    for (int resultValue = 0; resultValue < 2; ++resultValue) {
      Site stringValue;
      stringValue.op = op;
      stringValue.result = resultValue;
      stringValue.function = resultValue == 0 ? "sin" : "cos";
      stringValue.type = scalarTypeName(op->getOperand(0).getType());
      stringValue.typeSource = "mlir";
      stringValue.opText = "math.sincos";
      stringValue.args.push_back(op->getOperand(0));
      out.push_back(std::move(stringValue));
    }
    return;
  }
  auto callSite = dyn_cast<func::CallOp>(op);
  if (!callSite || callSite.getNumOperands() == 0)
    return;
  func::FuncOp callee = externalCallee(callSite);
  if (!callee)
    return;
  StringRef name = callee.getName();
  Site stringValue;
  stringValue.op = op;
  stringValue.opText = ("func.call @" + name).str();
  if (name.starts_with(kMarkerPrefix)) {
    stringValue.function = name.drop_front(kMarkerPrefix.size()).str();
    stringValue.typeSource = "marker";
    unsigned elementCount = callSite.getNumOperands();
    APInt widthValue, loopIndex, sg;
    if (elementCount >= 4 &&
        matchPattern(callSite.getOperand(elementCount - 3),
                     m_ConstantInt(&widthValue)) &&
        matchPattern(callSite.getOperand(elementCount - 2),
                     m_ConstantInt(&loopIndex)) &&
        matchPattern(callSite.getOperand(elementCount - 1),
                     m_ConstantInt(&sg))) {
      stringValue.type = (sg.isZero() ? "ap_ufixed<" : "ap_fixed<") +
                         std::to_string(widthValue.getSExtValue()) + "," +
                         std::to_string(loopIndex.getSExtValue()) + ">";
    } else {
      stringValue.type = "ap_fixed<?,?>";
    }
    for (unsigned keyValue = 0; keyValue + 3 < elementCount; ++keyValue)
      stringValue.args.push_back(callSite.getOperand(keyValue));
    out.push_back(std::move(stringValue));
    return;
  }
  std::string fn = libmFunction(name);
  if (fn.empty())
    return;
  stringValue.function = fn;
  stringValue.type = scalarTypeName(callSite.getOperand(0).getType());
  stringValue.typeSource = "mlir";
  stringValue.args.append(callSite.operand_begin(), callSite.operand_end());
  out.push_back(std::move(stringValue));
}

namespace {

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
      Value valueHandle = work.pop_back_val();
      for (Operation *user : valueHandle.getUsers()) {
        bool followable = user->getNumRegions() == 0 &&
                          !user->hasTrait<OpTrait::IsTerminator>() &&
                          (isMemoryEffectFree(user) || isPureCall(user));
        if (!followable) {
          result = true;
          break;
        }
        for (Value resultValue : user->getResults())
          if (seen.insert(resultValue).second)
            work.push_back(resultValue);
      }
    }
    memo[root] = result;
    return result;
  }

private:
  llvm::DenseMap<Value, bool> memo;
};

} // namespace

namespace {
class IndexOnlyValues {
public:
  /// Whether `v` is a compile-time function of constants and the induction
  /// variables of loops with constant bounds.
  bool of(Value valueHandle, unsigned depth = 0) {
    auto it = memo.find(valueHandle);
    if (it != memo.end())
      return it->second;
    memo[valueHandle] = false;
    bool resultValue = compute(valueHandle, depth);
    memo[valueHandle] = resultValue;
    return resultValue;
  }

private:
  bool compute(Value valueHandle, unsigned depth) {
    if (depth > 64)
      return false;
    if (matchPattern(valueHandle, m_Constant()))
      return true;
    if (auto ba = dyn_cast<BlockArgument>(valueHandle))
      return isInductionVariable(ba);
    Operation *op = valueHandle.getDefiningOp();
    if (auto stage = dyn_cast<LoopSchedulePipelineStageOp>(op)) {

      Operation *term = stage.getBodyBlock().getTerminator();
      unsigned keyValue = cast<OpResult>(valueHandle).getResultNumber();
      return keyValue < term->getNumOperands() &&
             of(term->getOperand(keyValue), depth + 1);
    }
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {

      if (!isMemoryEffectFree(op) || !of(ifOp.getCondition(), depth + 1))
        return false;
      unsigned keyValue = cast<OpResult>(valueHandle).getResultNumber();
      for (Region &resultValue : op->getRegions())
        for (Block &buildPoint : resultValue)
          if (auto rowValue =
                  dyn_cast<scf::YieldOp>(buildPoint.getTerminator()))
            if (keyValue >= rowValue.getNumOperands() ||
                !of(rowValue.getOperand(keyValue), depth + 1))
              return false;
      return true;
    }
    if (op->getNumRegions() != 0)
      return false;
    if (!isMemoryEffectFree(op) && !isPureCall(op))
      return false;
    for (Value exprValue : op->getOperands())
      if (!of(exprValue, depth + 1))
        return false;
    return true;
  }

  static bool constantBounds(affine::AffineForOp fieldValue) {
    return fieldValue.hasConstantLowerBound() &&
           fieldValue.hasConstantUpperBound();
  }

  bool isInductionVariable(BlockArgument ba) {
    Operation *owner = ba.getOwner()->getParentOp();
    if (auto fieldValue = dyn_cast<affine::AffineForOp>(owner))
      return ba == fieldValue.getInductionVar() && constantBounds(fieldValue);
    if (auto fieldValue = dyn_cast<scf::ForOp>(owner))
      return ba == fieldValue.getInductionVar() &&
             matchPattern(fieldValue.getLowerBound(), m_Constant()) &&
             matchPattern(fieldValue.getUpperBound(), m_Constant()) &&
             matchPattern(fieldValue.getStep(), m_Constant());
    auto pipe = dyn_cast<LoopSchedulePipelineOp>(owner);
    if (!pipe || !pipe.getTripCount())
      return false;
    unsigned keyValue = ba.getArgNumber();
    auto term = dyn_cast<circt::loopschedule::LoopScheduleTerminatorOp>(
        pipe.getStagesBlock().getTerminator());
    if (!term || keyValue >= term.getIterArgs().size())
      return false;
    Value next = term.getIterArgs()[keyValue];

    if (auto stage = next.getDefiningOp<LoopSchedulePipelineStageOp>()) {
      Operation *reg = stage.getBodyBlock().getTerminator();
      unsigned resultValue = cast<OpResult>(next).getResultNumber();
      if (resultValue >= reg->getNumOperands())
        return false;
      next = reg->getOperand(resultValue);
    }
    auto add = next.getDefiningOp<arith::AddIOp>();
    if (!add)
      return false;
    auto isArgK = [&](Value exprValue) {
      auto arrayValue = dyn_cast<BlockArgument>(exprValue);
      return arrayValue && arrayValue.getArgNumber() == keyValue &&
             arrayValue.getOwner()->getParentOp() == owner;
    };
    return (isArgK(add.getLhs()) && matchPattern(add.getRhs(), m_Constant())) ||
           (isArgK(add.getRhs()) && matchPattern(add.getLhs(), m_Constant()));
  }

  llvm::DenseMap<Value, bool> memo;
};
} // namespace

static bool storesToLocalArray(Value mem) {
  while (Operation *def = mem.getDefiningOp()) {
    if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(def))
      return true;
    auto view = dyn_cast<ViewLikeOpInterface>(def);
    if (!view)
      return false;
    mem = view.getViewSource();
  }
  return false;
}

static bool onlyFillsArrays(Operation *site, IndexOnlyValues &indexValue) {
  SmallVector<Value> work(site->getResults().begin(), site->getResults().end());
  llvm::DenseSet<Value> seen(work.begin(), work.end());
  bool stored = false;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    if (!indexValue.of(valueHandle))
      return false;
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (auto st = dyn_cast<affine::AffineStoreOp>(user)) {
        if (use.getOperandNumber() != 0 || !storesToLocalArray(st.getMemRef()))
          return false;
        stored = true;
        continue;
      }
      if (auto st = dyn_cast<memref::StoreOp>(user)) {
        if (use.getOperandNumber() != 0 || !storesToLocalArray(st.getMemRef()))
          return false;
        stored = true;
        continue;
      }
      if (auto rowValue = dyn_cast<scf::YieldOp>(user)) {
        auto ifOp = dyn_cast<scf::IfOp>(user->getParentOp());
        if (!ifOp)
          return false;
        Value resultValue = ifOp->getResult(use.getOperandNumber());
        if (seen.insert(resultValue).second)
          work.push_back(resultValue);
        continue;
      }
      if (auto ifOp = dyn_cast<scf::IfOp>(user)) {
        if (!isMemoryEffectFree(user))
          return false;
        for (Value resultValue : user->getResults())
          if (seen.insert(resultValue).second)
            work.push_back(resultValue);
        continue;
      }
      if (isa<circt::loopschedule::LoopScheduleRegisterOp>(user)) {
        auto stage = cast<LoopSchedulePipelineStageOp>(user->getParentOp());
        Value resultValue = stage->getResult(use.getOperandNumber());
        if (seen.insert(resultValue).second)
          work.push_back(resultValue);
        continue;
      }
      if (user->getNumRegions() != 0 ||
          (!isMemoryEffectFree(user) && !isPureCall(user)))
        return false;
      for (Value resultValue : user->getResults())
        if (seen.insert(resultValue).second)
          work.push_back(resultValue);
    }
  }
  return stored;
}

static bool siteLive(const Site &stringValue, LiveValues &lv) {
  if (stringValue.result >= 0)
    return lv.live(stringValue.op->getResult(stringValue.result));
  for (Value resultValue : stringValue.op->getResults())
    if (lv.live(resultValue))
      return true;
  return false;
}

static bool mayWrite(Operation *op) {
  if (auto iface = dyn_cast<MemoryEffectOpInterface>(op))
    return iface.hasEffect<MemoryEffects::Write>();
  return true;
}

static bool sameValue(Value arrayValue, Value buildPoint, unsigned depth = 8) {
  if (arrayValue == buildPoint)
    return true;
  if (depth == 0)
    return false;
  Operation *da = arrayValue.getDefiningOp(), *db = buildPoint.getDefiningOp();
  if (!da || !db || da->getName() != db->getName() ||
      da->getNumOperands() != db->getNumOperands() ||
      da->getNumRegions() != 0 || db->getNumRegions() != 0 ||
      da->getAttrDictionary() != db->getAttrDictionary() ||
      cast<OpResult>(arrayValue).getResultNumber() !=
          cast<OpResult>(buildPoint).getResultNumber())
    return false;
  if (!isMemoryEffectFree(da)) {
    if (!isa<affine::AffineLoadOp, memref::LoadOp>(da) ||
        da->getBlock() != db->getBlock())
      return false;
    Operation *first = da->isBeforeInBlock(db) ? da : db;
    Operation *last = first == da ? db : da;
    for (Operation *opHandle = first->getNextNode();
         opHandle && opHandle != last; opHandle = opHandle->getNextNode())
      if (mayWrite(opHandle))
        return false;
  }
  for (auto [exprValue, rowValue] :
       llvm::zip(da->getOperands(), db->getOperands()))
    if (!sameValue(exprValue, rowValue, depth - 1))
      return false;
  return true;
}

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

static bool isUserPipeline(Operation *loop) {
  Attribute tag = loop->getAttr(kLoopPipelineAttr);
  if (!tag)
    return false;
  if (auto arr = dyn_cast<ArrayAttr>(tag))
    tag = arr.empty() ? Attribute() : arr[0];
  if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
    if (auto stringValue = dict.getAs<StringAttr>("source"))
      return stringValue.getValue() != kLoopPipelineAutoSource;
  return true;
}

static unsigned requestedII(Operation *loop) {
  Attribute tag = loop->getAttr(kLoopPipelineAttr);
  if (auto arr = dyn_cast_or_null<ArrayAttr>(tag))
    tag = arr.empty() ? Attribute() : arr[0];
  if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
    if (auto ii = dict.getAs<IntegerAttr>("II"))
      return ii.getInt() > 0 ? static_cast<unsigned>(ii.getInt()) : 0;
  return 0;
}

static unsigned portBoundII(Operation *loop) {
  llvm::DenseMap<const void *, unsigned> perArray;
  loop->walk([&](Operation *op) {
    Value mem;
    if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
      mem = lowerIndex.getMemRef();
    else if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
      mem = stringValue.getMemRef();
    else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
      mem = lowerIndex.getMemRef();
    else if (auto stringValue = dyn_cast<memref::StoreOp>(op))
      mem = stringValue.getMemRef();
    if (!mem)
      return;
    StorageRoot root = storageRoot(mem);
    const void *key = root.global ? static_cast<const void *>(root.global)
                                  : root.value.getAsOpaquePointer();
    ++perArray[key];
  });
  unsigned ii = 1;
  for (auto &[key, elementCount] : perArray)
    ii = std::max(ii, (elementCount + 1) / 2);
  return ii;
}

static unsigned autoUnrollCopies(Operation *loop) {
  uint64_t copies = 1;
  if (auto arr = loop->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
    for (Attribute arrayValue : arr)
      if (auto dict = dyn_cast<DictionaryAttr>(arrayValue))
        if (auto fieldValue = dict.getAs<IntegerAttr>("factor"))
          if (fieldValue.getInt() > 1)
            copies = std::min<uint64_t>(copies * fieldValue.getInt(), 1u << 20);
  return static_cast<unsigned>(copies);
}

static bool keptSequential(const Site &stringValue, Operation *loop) {
  return stringValue.entry && stringValue.entry->blocksAutoPipelining &&
         !isUserPipeline(loop);
}

static void placeSite(
    Site &stringValue,
    llvm::DenseMap<Block *, llvm::DenseMap<Operation *, unsigned>> &stretchOf) {
  for (Operation *portValue = stringValue.op->getParentOp();
       portValue && !isa<func::FuncOp>(portValue);
       portValue = portValue->getParentOp()) {
    if (isa<LoopSchedulePipelineOp>(portValue) ||
        (isa<affine::AffineForOp, scf::ForOp>(portValue) &&
         portValue->hasAttr(kLoopPipelineAttr) &&
         !portValue->hasAttr(kLoopPipelineOffAttr))) {
      if (keptSequential(stringValue, portValue)) {

        stringValue.notPipelined = true;
        stringValue.unrollCopies = autoUnrollCopies(portValue);
        stringValue.scope = portValue;
        stringValue.block = nullptr;
        stringValue.stretch = 0;
        return;
      }
    }
    if (auto pl = dyn_cast<LoopSchedulePipelineOp>(portValue)) {
      stringValue.pipeline = portValue;
      stringValue.ii = std::max<unsigned>(1, static_cast<unsigned>(pl.getII()));
      stringValue.userPipeline = isUserPipeline(portValue);
      return;
    }
    if (isa<affine::AffineForOp, scf::ForOp>(portValue) &&
        portValue->hasAttr(kLoopPipelineAttr) &&
        !portValue->hasAttr(kLoopPipelineOffAttr)) {
      stringValue.pipeline = portValue;

      stringValue.ii = std::max(requestedII(portValue), portBoundII(portValue));
      stringValue.iiAssumed = true;
      stringValue.userPipeline = isUserPipeline(portValue);
      return;
    }
  }
  Operation *cur = stringValue.op;
  while (true) {
    Operation *portValue = cur->getParentOp();
    if (!portValue || isa<func::FuncOp>(portValue) || isLoop(portValue)) {
      stringValue.scope = portValue;
      break;
    }
    cur = portValue;
  }
  stringValue.block = cur->getBlock();
  auto &index = stretchOf[stringValue.block];
  if (index.empty()) {
    unsigned keyValue = 0;
    for (Operation &opHandle : *stringValue.block) {
      index[&opHandle] = keyValue;
      if (containsLoop(&opHandle))
        ++keyValue;
    }
  }
  stringValue.stretch = index.lookup(cur);
}

static void accessedRoots(Operation *op, SmallVectorImpl<StorageRoot> &out) {
  op->walk([&](Operation *inner) {
    for (Value valueHandle : inner->getOperands())
      if (isa<BaseMemRefType>(valueHandle.getType())) {
        StorageRoot resultValue = storageRoot(valueHandle);
        if (!llvm::is_contained(out, resultValue))
          out.push_back(resultValue);
      }
  });
}

static bool mayOverlapInSequentialCode(const Site &arrayValue,
                                       const Site &buildPoint) {
  if (arrayValue.scope == buildPoint.scope &&
      arrayValue.block == buildPoint.block &&
      arrayValue.stretch == buildPoint.stretch)
    return true;

  llvm::DenseMap<Block *, Operation *> holderOfA;
  for (Operation *portValue = arrayValue.op; portValue;
       portValue = portValue->getParentOp())
    holderOfA.try_emplace(portValue->getBlock(), portValue);
  for (Operation *queueValue = buildPoint.op; queueValue;
       queueValue = queueValue->getParentOp()) {
    auto it = holderOfA.find(queueValue->getBlock());
    if (it == holderOfA.end())
      continue;
    Operation *exprValue = it->second;
    if (exprValue == queueValue || !isLoop(exprValue) || !isLoop(queueValue) ||
        !isa<func::FuncOp>(queueValue->getParentOp()))
      return false;
    SmallVector<StorageRoot, 8> rootsA, rootsB;
    accessedRoots(exprValue, rootsA);
    accessedRoots(queueValue, rootsB);
    return llvm::none_of(rootsA, [&](const StorageRoot &resultValue) {
      return llvm::is_contained(rootsB, resultValue);
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

std::vector<MathCoreRecord>
analyzeMathCores(ModuleOp module, const MathCostConfig &config,
                 llvm::function_ref<bool(Operation *)> covers,
                 llvm::function_ref<unsigned(Operation *)> instancesOf,
                 llvm::function_ref<void(Location, const std::string &)> warn) {
  std::vector<Site> sites;
  module.walk([&](Operation *op) {
    if (!covers(op) || !op->getParentOfType<func::FuncOp>())
      return;
    SmallVector<Site, 2> found;
    recognise(op, found);
    for (Site &stringValue : found) {
      if (!coreFunctions().contains(stringValue.function) &&
          !llvm::any_of(config.entries, [&](const MathCostEntry &entryValue) {
            return entryValue.function == stringValue.function;
          }))
        continue;
      auto fn = op->getParentOfType<func::FuncOp>();
      stringValue.func = fn.getName().str();
      stringValue.funcOp = fn.getOperation();
      sites.push_back(std::move(stringValue));
    }
  });

  LiveValues lv;
  IndexOnlyValues indexValue;
  llvm::DenseMap<Block *, llvm::DenseMap<Operation *, unsigned>> stretchOf;
  for (Site &stringValue : sites) {
    auto isConst = [](Value valueHandle) {
      return matchPattern(valueHandle, m_Constant());
    };
    stringValue.folded =
        !stringValue.args.empty() && llvm::all_of(stringValue.args, isConst);
    if (stringValue.function == "pow" && stringValue.args.size() == 2 &&
        !stringValue.folded) {
      if (isConst(stringValue.args[0]))
        stringValue.argForm = "constant base";
      else if (isConst(stringValue.args[1]))
        stringValue.argForm = "constant exponent";
    }
    stringValue.entry = config.lookup(stringValue.function, stringValue.type,
                                      stringValue.argForm);
    if (!stringValue.folded &&
        llvm::all_of(
            stringValue.args,
            [&](Value arrayValue) { return indexValue.of(arrayValue); }) &&
        onlyFillsArrays(stringValue.op, indexValue)) {
      stringValue.folded = true;
      stringValue.fillOnly = true;
    }
    stringValue.dead = !stringValue.folded && !siteLive(stringValue, lv);
    placeSite(stringValue, stretchOf);
  }

  auto sameRegion = [](const Site &arrayValue, const Site &buildPoint) {
    if (arrayValue.pipeline || buildPoint.pipeline)
      return arrayValue.pipeline == buildPoint.pipeline;
    return arrayValue.scope == buildPoint.scope &&
           arrayValue.block == buildPoint.block &&
           arrayValue.stretch == buildPoint.stretch;
  };
  auto counted = [](const Site &stringValue) {
    return !stringValue.folded && !stringValue.dead;
  };
  for (size_t loopIndex = 0; loopIndex < sites.size(); ++loopIndex) {
    Site &stringValue = sites[loopIndex];
    if (!counted(stringValue) || !stringValue.entry ||
        stringValue.sharedWith >= 0 ||
        stringValue.entry->sharesInstanceWith.empty() ||
        stringValue.args.empty())
      continue;
    llvm::StringSet<> taken;
    for (size_t innerIndex = 0; innerIndex < sites.size(); ++innerIndex) {
      Site &typeValue = sites[innerIndex];
      if (innerIndex == loopIndex || !counted(typeValue) ||
          typeValue.sharedWith >= 0 || typeValue.func != stringValue.func ||
          typeValue.type != stringValue.type || typeValue.args.empty() ||
          taken.contains(typeValue.function) ||
          !llvm::is_contained(stringValue.entry->sharesInstanceWith,
                              typeValue.function) ||
          !sameRegion(stringValue, typeValue) ||
          !sameValue(stringValue.args[0], typeValue.args[0]))
        continue;

      if (llvm::any_of(sites, [&](const Site &useValue) {
            return useValue.sharedWith == static_cast<int>(innerIndex);
          }))
        continue;
      typeValue.sharedWith = static_cast<int>(loopIndex);
      taken.insert(typeValue.function);
    }
  }

  std::vector<MathCoreRecord> records;
  std::map<std::string, size_t> recordOf;
  std::vector<std::vector<size_t>> members;
  auto keyOf = [](const Site &stringValue) {
    std::string keyValue = stringValue.func + "|";
    if (stringValue.entry)
      return keyValue + "#" + std::to_string(stringValue.entry->index);
    return keyValue + stringValue.function + "|" + stringValue.type + "|" +
           stringValue.argForm;
  };
  for (size_t loopIndex = 0; loopIndex < sites.size(); ++loopIndex) {
    const Site &stringValue = sites[loopIndex];
    const Site &owner = stringValue.sharedWith >= 0
                            ? sites[stringValue.sharedWith]
                            : stringValue;
    std::string key = keyOf(owner);
    auto [it, inserted] = recordOf.try_emplace(key, records.size());
    if (inserted) {
      MathCoreRecord resultValue;
      resultValue.func = owner.func;
      resultValue.functionInstances = std::max(1u, instancesOf(owner.funcOp));
      resultValue.function = owner.function;
      resultValue.type = owner.type;
      resultValue.arguments = owner.argForm;
      resultValue.typeSource = owner.typeSource;
      resultValue.loc = locText(owner.op->getLoc());
      resultValue.configPath = config.path;
      if (const MathCostEntry *entryValue = owner.entry) {
        resultValue.entry = entryValue->index;
        resultValue.entryInfo = *entryValue;
        resultValue.arguments = entryValue->arguments;
        resultValue.coreKind = entryValue->coreKind;
        resultValue.instancing = entryValue->instancing;
        resultValue.bramPerInstance = entryValue->bram;
        resultValue.coreName =
            !entryValue->cores.empty() ? entryValue->cores.front()
            : !entryValue->tableName.empty()
                ? entryValue->tableName
                : entryValue->function + "_" + entryValue->type;
      } else {
        resultValue.coreName = owner.function + "(" + owner.type + ")";
      }
      records.push_back(std::move(resultValue));
      members.emplace_back();
    }
    members[it->second].push_back(loopIndex);
  }

  std::set<std::string> warnedPairs;
  for (size_t ri = 0; ri < records.size(); ++ri) {
    MathCoreRecord &resultValue = records[ri];
    const MathCostEntry *entryValue =
        resultValue.entry ? &config.entries[*resultValue.entry] : nullptr;

    std::vector<Operation *> pipeOrder;
    llvm::DenseMap<Operation *, SmallVector<const Site *>> perPipe;
    std::vector<std::tuple<Operation *, Block *, unsigned>> seqOrder;
    std::map<std::tuple<Operation *, Block *, unsigned>,
             SmallVector<const Site *>>
        perStretch;
    unsigned live = 0, folded = 0, dead = 0;
    const Site *firstLive = nullptr;
    for (size_t si : members[ri]) {
      const Site &stringValue = sites[si];
      if (!stringValue.folded && !stringValue.dead && !firstLive)
        firstLive = &stringValue;
      MathSiteRecord sr;
      sr.op = stringValue.opText;
      sr.loc = locText(stringValue.op->getLoc());
      if (stringValue.folded) {
        sr.status = "folded";
        sr.detail = stringValue.fillOnly
                        ? "fills an array from loop indices and constants: "
                          "evaluated at compile time"
                        : "every argument is a constant (const_fold)";
        ++folded;
      } else if (stringValue.dead) {
        sr.status = "dead";
        sr.detail = "the result reaches no output";
        ++dead;
      } else if (stringValue.sharedWith >= 0) {
        sr.status = "shared";
        sr.detail = "shares the instance of the " +
                    sites[stringValue.sharedWith].function + " call at " +
                    locText(sites[stringValue.sharedWith].op->getLoc()) +
                    " (same argument)";
        ++live;
      } else {
        sr.status = "counted";
        ++live;
        if (stringValue.pipeline) {
          if (!perPipe.count(stringValue.pipeline))
            pipeOrder.push_back(stringValue.pipeline);
          perPipe[stringValue.pipeline].push_back(&stringValue);
          sr.detail =
              "pipelined loop at " + locText(stringValue.pipeline->getLoc());
        } else {
          auto key = std::make_tuple(stringValue.scope, stringValue.block,
                                     stringValue.stretch);
          if (!perStretch.count(key))
            seqOrder.push_back(key);
          perStretch[key].push_back(&stringValue);
          sr.detail = std::string(stringValue.notPipelined
                                      ? "sequential (a loop Vitis does not "
                                        "pipeline around this core), stretch "
                                      : "sequential, stretch ") +
                      std::to_string(stringValue.stretch) + " of " +
                      (stringValue.scope ? locText(stringValue.scope->getLoc())
                                         : std::string("the function"));
        }
      }
      resultValue.sites.push_back(std::move(sr));
    }

    int64_t perInst = entryValue ? entryValue->bram : 0;
    bool cordic = entryValue && entryValue->instancing == "cordic_loop";
    unsigned pipeInst = 0;
    int64_t bram = 0;
    for (Operation *portValue : pipeOrder) {
      const auto &valueHandle = perPipe[portValue];
      const Site *first = valueHandle.front();
      MathRegionRecord reg;
      reg.kind = "pipeline";
      reg.loc = locText(portValue->getLoc());
      reg.ii = first->ii;
      reg.iiAssumed = first->iiAssumed;
      reg.source = first->userPipeline ? "user" : "auto";
      reg.calls = valueHandle.size();
      reg.instances = (reg.calls + reg.ii - 1) / reg.ii;
      reg.bramPerInstance = perInst;
      if (cordic) {

        reg.cordicKept = entryValue->cordicUnrolledIn == "user_pipeline" &&
                         !first->userPipeline;
        if (reg.cordicKept) {
          llvm::StringSet<> locs;
          for (const Site *stringValue : valueHandle)
            locs.insert(locText(stringValue->op->getLoc()));
          reg.instances = locs.size();
        } else if (entryValue->bramIfUnrolled) {
          reg.bramPerInstance = *entryValue->bramIfUnrolled;
        }
      }
      pipeInst += reg.instances;
      bram += reg.instances * reg.bramPerInstance;
      resultValue.regions.push_back(std::move(reg));
    }

    std::vector<Operation *> seqOps;
    std::vector<const Site *> seqSites;
    std::vector<size_t> seqRegion;
    size_t firstSeqRegion = resultValue.regions.size();
    for (const auto &key : seqOrder) {
      const auto &valueHandle = perStretch[key];
      MathRegionRecord reg;
      reg.kind = "sequential";
      Operation *scope = std::get<0>(key);
      reg.loc = (scope ? locText(scope->getLoc()) : std::string("function")) +
                " stretch " + std::to_string(std::get<2>(key));
      reg.calls = valueHandle.size();
      std::vector<const Site *> kept(valueHandle.begin(), valueHandle.end());
      if (valueHandle.front()->notPipelined) {
        unsigned copies = valueHandle.front()->unrollCopies;
        reg.kind = "sequential (loop not pipelined by Vitis)";
        reg.unrollCopies = copies;

        kept.resize(
            std::max<size_t>(1, (valueHandle.size() + copies - 1) / copies));
      }
      for (const Site *stringValue : kept) {
        seqOps.push_back(stringValue->op);
        seqSites.push_back(stringValue);
        seqRegion.push_back(resultValue.regions.size());
      }
      reg.bramPerInstance = perInst;
      resultValue.regions.push_back(std::move(reg));
    }
    unsigned seqInst = 0;
    std::string seqRule;
    if (!seqOps.empty()) {
      SmallVector<unsigned> group;
      seqInst = groupConcurrentCalls(
          cast<func::FuncOp>(firstLive->funcOp), seqOps, std::nullopt, group,
          &seqRule, [&](unsigned loopIndex, unsigned innerIndex) {
            return !mayOverlapInSequentialCode(*seqSites[loopIndex],
                                               *seqSites[innerIndex]);
          });

      std::map<size_t, std::set<unsigned>> used;
      for (size_t keyValue = 0; keyValue < seqOps.size(); ++keyValue)
        used[seqRegion[keyValue]].insert(group[keyValue]);
      for (size_t ri2 = firstSeqRegion; ri2 < resultValue.regions.size(); ++ri2)
        resultValue.regions[ri2].instances = used[ri2].size();
    }
    bram += seqInst * perInst;
    resultValue.instances = pipeInst + seqInst;

    unsigned mult = resultValue.functionInstances;
    resultValue.instances *= mult;
    bram *= mult;

    if (!entryValue) {
      resultValue.status = live ? "unknown_cost" : folded ? "folded" : "dead";
      resultValue.bram = 0;
      resultValue.bramPerInstance = 0;
      resultValue.reason =
          "no entry for " + resultValue.function + " of " + resultValue.type +
          (resultValue.arguments != "any" ? " (" + resultValue.arguments + ")"
                                          : "") +
          " in " + config.path + ": unknown cost, 0 assumed";

      if (live && warnedPairs
                      .insert(resultValue.function + "|" + resultValue.type +
                              "|" + resultValue.arguments)
                      .second)
        warn(firstLive ? firstLive->op->getLoc()
                       : UnknownLoc::get(module.getContext()),
             resultValue.reason);
      continue;
    }
    resultValue.bram = bram;
    if (!live) {
      resultValue.status = folded ? "folded" : "dead";
      resultValue.reason =
          folded ? "every call is evaluated at compile time (constant "
                   "arguments, or an array fill from loop indices)"
                 : "no call result reaches an output";
      continue;
    }
    resultValue.status = "counted";
    std::string why = entryValue->instancing + ": ";
    bool firstPart = true;
    for (const MathRegionRecord &reg : resultValue.regions) {
      if (!firstPart)
        why += "; ";
      firstPart = false;
      if (reg.kind == "pipeline" && reg.cordicKept)
        why += std::to_string(reg.calls) +
               " call(s) in an automatically pipelined loop: the CORDIC loop "
               "stays a loop (one per call site) -> " +
               std::to_string(reg.instances) + " x " +
               std::to_string(reg.bramPerInstance);
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
      why += "; sequential code: " + seqRule + " x " + std::to_string(perInst);
    if (mult != 1)
      why += "; x " + std::to_string(mult) + " instance(s) of @" +
             resultValue.func;
    resultValue.reason = why;
  }
  return records;
}

llvm::json::Object mathCoreJson(const MathCoreRecord &resultValue) {
  llvm::json::Object opHandle;
  opHandle["function"] = resultValue.function;
  opHandle["type"] = resultValue.type;
  opHandle["type_source"] = resultValue.typeSource;
  opHandle["arguments"] = resultValue.arguments;
  opHandle["config"] = resultValue.configPath;
  opHandle["config_entry"] =
      resultValue.entry
          ? llvm::json::Value(static_cast<int64_t>(*resultValue.entry))
          : llvm::json::Value(nullptr);
  opHandle["core"] = resultValue.coreName;
  opHandle["core_kind"] = resultValue.coreKind.empty()
                              ? llvm::json::Value(nullptr)
                              : llvm::json::Value(resultValue.coreKind);
  opHandle["instancing"] = resultValue.instancing.empty()
                               ? llvm::json::Value(nullptr)
                               : llvm::json::Value(resultValue.instancing);
  opHandle["bram_per_instance"] = resultValue.bramPerInstance;
  opHandle["instances"] = static_cast<int64_t>(resultValue.instances);
  opHandle["function_instances"] =
      static_cast<int64_t>(resultValue.functionInstances);
  opHandle["reason"] = resultValue.reason;
  llvm::json::Array regions;
  for (const MathRegionRecord &globalOp : resultValue.regions) {
    llvm::json::Object exprValue;
    exprValue["kind"] = globalOp.kind;
    exprValue["loc"] = globalOp.loc;
    if (globalOp.kind == "pipeline") {
      exprValue["ii"] = static_cast<int64_t>(globalOp.ii);
      exprValue["ii_assumed"] = globalOp.iiAssumed;
      exprValue["source"] = globalOp.source;
      exprValue["cordic_loop_kept"] = globalOp.cordicKept;
    }
    if (globalOp.unrollCopies > 1)
      exprValue["unroll_copies"] = static_cast<int64_t>(globalOp.unrollCopies);
    exprValue["calls"] = static_cast<int64_t>(globalOp.calls);
    exprValue["instances"] = static_cast<int64_t>(globalOp.instances);
    exprValue["bram_per_instance"] = globalOp.bramPerInstance;
    regions.push_back(std::move(exprValue));
  }
  opHandle["regions"] = std::move(regions);
  llvm::json::Array sites;
  for (const MathSiteRecord &stringValue : resultValue.sites)
    sites.push_back(llvm::json::Object{{"op", stringValue.op},
                                       {"loc", stringValue.loc},
                                       {"status", stringValue.status},
                                       {"detail", stringValue.detail}});
  opHandle["sites"] = std::move(sites);
  return opHandle;
}

void printMathCoreText(const MathCoreRecord &resultValue,
                       llvm::raw_ostream &os) {
  os << "  function: " << resultValue.function << " of " << resultValue.type
     << " (type from "
     << (resultValue.typeSource == "marker" ? "the shim marker"
                                            : "the MLIR element type")
     << "), arguments " << resultValue.arguments << "\n";
  if (resultValue.entryInfo) {
    const MathCostEntry &entryValue = *resultValue.entryInfo;
    os << "  config: " << resultValue.configPath << " entries["
       << entryValue.index << "]: core " << resultValue.coreName << " ("
       << entryValue.coreKind << "), " << entryValue.bram
       << " BRAM per instance, instancing " << entryValue.instancing;
    if (entryValue.bramIfUnrolled)
      os << ", " << *entryValue.bramIfUnrolled << " when a "
         << (entryValue.cordicUnrolledIn == "user_pipeline" ? "pragma-" : "")
         << "pipelined loop unrolls the CORDIC loop";
    if (!entryValue.sharesInstanceWith.empty()) {
      os << ", shares its instance with";
      for (const std::string &fieldValue : entryValue.sharesInstanceWith)
        os << " " << fieldValue;
    }
    os << "\n";
  } else {
    os << "  config: " << resultValue.configPath
       << ": no entry (unknown cost)\n";
  }
  for (const MathRegionRecord &globalOp : resultValue.regions) {
    os << "  " << globalOp.kind << " " << globalOp.loc << ": " << globalOp.calls
       << " call(s)";
    if (globalOp.kind == "pipeline")
      os << " per iteration, " << globalOp.source << " pipeline, II "
         << globalOp.ii
         << (globalOp.iiAssumed
                 ? " (estimated: loop not scheduled, the requested II "
                   "or two ports per array)"
                 : "")
         << (globalOp.cordicKept ? ", CORDIC loop kept (one per call site)"
                                 : "");
    os << " -> " << globalOp.instances << " instance(s) x "
       << globalOp.bramPerInstance << "\n";
  }
  for (const MathSiteRecord &stringValue : resultValue.sites)
    os << "  call " << stringValue.op << " @ " << stringValue.loc << ": "
       << stringValue.status << " (" << stringValue.detail << ")\n";
  os << "  => " << resultValue.instances << " instance(s), " << resultValue.bram
     << " BRAM: " << resultValue.reason << "\n";
}

void printMathCoreLine(const MathCoreRecord &resultValue,
                       llvm::raw_ostream &os) {
  os << "math.core function=" << resultValue.function
     << " type=" << resultValue.type;
  if (resultValue.arguments != "any") {
    std::string arrayValue = resultValue.arguments;
    std::replace(arrayValue.begin(), arrayValue.end(), ' ', '_');
    os << " arguments=" << arrayValue;
  }
  os << " func=@" << resultValue.func << " instances=" << resultValue.instances
     << " bram=" << resultValue.bram << " (";
  if (resultValue.status == "counted")
    os << resultValue.coreName << ", " << resultValue.instancing;
  else if (resultValue.status == "unknown_cost")
    os << "unknown cost: no entry";
  else if (resultValue.status == "folded")
    os << "folded: evaluated at compile time";
  else
    os << "dead: no call result reaches an output";
  os << ")\n";
}

} // namespace circt::hls_analysis
