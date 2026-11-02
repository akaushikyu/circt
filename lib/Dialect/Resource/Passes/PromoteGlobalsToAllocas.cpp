//===- PromoteGlobalsToAllocas.cpp - file-scope arrays as local arrays ----===//
//
// --promote-globals-to-allocas
//
// Vitis HLS treats a file-scope array exactly like a local one: both
// linkages become `internal unnamed_addr global` by a.o.1, a write-only global
// is removed at the same stage as a dead local, and a live global gets the
// same core, replication and BRAM as the identical kernel written with
// locals (VITIS_NOTES.md N1a; dg_e_globals_static = dg_e_globals_extern =
// dg_e_locals = 4 BRAM, identical FF/LUT).
//
// hls-est's passes were written for allocas: banking, the storage-mode
// classification of the scheduler and the access attribution of
// --bram-analysis all key on the alloca's SSA value (OPEN_ISSUES.md O4). This
// pass therefore turns every eligible global into an alloca, so everything
// downstream treats it like a local:
//
//   memref.global @G : memref<...> = uninitialized     (or = dense<0>)
//   func.func @f() { %0 = memref.get_global @G ... }   (all uses in @f)
//     ->
//   func.func @f() { %0 = memref.alloca() {polygeist.varname = "G",
//                          hls.preserve, hls.from_global = "G"} ... }
//
// Eligible: not `constant`, no initial value or an all-zero one (the alloca
// has none; for BRAM accounting and liveness an all-zero start value is the
// same as an unknown one), a static shape, and every symbol use is a
// memref.get_global inside one func.func. The `hls.*` attributes of the
// global (array_partition, bind_storage pragmas) are copied to the alloca.
//
// Left as globals: constant-initialised ROM tables (--bram-analysis attributes
// their get_global accesses itself), globals with a non-zero initial value,
// and globals used by several functions (their stores escape the function).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Pass/Pass.h"

using namespace mlir;

namespace {

/// True for `= uninitialized` and for a splat or dense all-zero initializer.
static bool hasNoOrZeroInit(memref::GlobalOp g) {
  if (g.isExternal())
    return false; // a declaration: the definition lives elsewhere
  if (g.isUninitialized())
    return true;
  auto init = dyn_cast<ElementsAttr>(*g.getInitialValue());
  if (!init)
    return false;
  if (auto dense = dyn_cast<DenseElementsAttr>(init)) {
    if (dense.isSplat()) {
      Attribute v = dense.getSplatValue<Attribute>();
      if (auto i = dyn_cast<IntegerAttr>(v))
        return i.getValue().isZero();
      if (auto f = dyn_cast<FloatAttr>(v))
        return f.getValue().isZero();
      return false;
    }
    if (dense.getElementType().isIntOrIndex())
      return llvm::all_of(dense.getValues<APInt>(),
                          [](const APInt &a) { return a.isZero(); });
    if (isa<FloatType>(dense.getElementType()))
      return llvm::all_of(dense.getValues<APFloat>(),
                          [](const APFloat &a) { return a.isZero(); });
  }
  return false;
}

struct PromoteGlobalsToAllocasPass
    : PassWrapper<PromoteGlobalsToAllocasPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(PromoteGlobalsToAllocasPass)

  StringRef getArgument() const final { return "promote-globals-to-allocas"; }
  StringRef getDescription() const final {
    return "Turn a non-constant, uninitialised (or zero-initialised) "
           "memref.global used by a single function into a memref.alloca at "
           "that function's entry (Vitis treats file-scope arrays like local "
           "ones, VITIS_NOTES.md N1a)";
  }
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<memref::MemRefDialect>();
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    SmallVector<memref::GlobalOp> globals(module.getOps<memref::GlobalOp>());
    for (memref::GlobalOp g : globals) {
      if (g.getConstant() || !hasNoOrZeroInit(g))
        continue;
      MemRefType ty = g.getType();
      if (!ty.hasStaticShape())
        continue;
      std::optional<SymbolTable::UseRange> uses =
          SymbolTable::getSymbolUses(g, module);
      if (!uses)
        continue; // unknown symbol uses: leave it alone
      SmallVector<memref::GetGlobalOp> sites;
      func::FuncOp owner;
      bool eligible = true;
      for (const SymbolTable::SymbolUse &use : *uses) {
        auto gg = dyn_cast<memref::GetGlobalOp>(use.getUser());
        auto fn = gg ? gg->getParentOfType<func::FuncOp>() : func::FuncOp();
        if (!gg || !fn || (owner && fn != owner)) {
          eligible = false;
          break;
        }
        owner = fn;
        sites.push_back(gg);
      }
      if (!eligible || !owner || sites.empty())
        continue; // used by several functions, by a non-get_global, or unused

      OpBuilder b(&owner.getBody().front(), owner.getBody().front().begin());
      auto alloca = memref::AllocaOp::create(b, g.getLoc(), ty);
      StringRef sym = g.getSymName();
      for (NamedAttribute a : g->getDiscardableAttrs())
        if (a.getName().strref().starts_with("hls."))
          alloca->setAttr(a.getName(), a.getValue());
      if (auto vn = g->getAttrOfType<StringAttr>("polygeist.varname"))
        alloca->setAttr("polygeist.varname", vn);
      else
        alloca->setAttr("polygeist.varname", b.getStringAttr(sym));
      alloca->setAttr("hls.preserve", b.getUnitAttr());
      alloca->setAttr("hls.from_global", b.getStringAttr(sym));
      for (memref::GetGlobalOp gg : sites) {
        Value repl = alloca.getResult();
        if (gg.getType() != repl.getType()) {
          // Same symbol, a different (layout-only) view: keep the type.
          OpBuilder cb(gg);
          repl = memref::CastOp::create(cb, gg.getLoc(), gg.getType(), repl);
        }
        gg.getResult().replaceAllUsesWith(repl);
        gg.erase();
      }
      g.erase();
    }
  }
};

} // namespace

namespace circt::hls_analysis {
std::unique_ptr<Pass> createPromoteGlobalsToAllocasPass() {
  return std::make_unique<PromoteGlobalsToAllocasPass>();
}
} // namespace circt::hls_analysis
