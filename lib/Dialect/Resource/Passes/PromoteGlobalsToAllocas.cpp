

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
static bool hasNoOrZeroInit(memref::GlobalOp globalOp) {
  if (globalOp.isExternal())
    return false;
  if (globalOp.isUninitialized())
    return true;
  auto initialValue = dyn_cast<ElementsAttr>(*globalOp.getInitialValue());
  if (!initialValue)
    return false;
  if (auto denseValue = dyn_cast<DenseElementsAttr>(initialValue)) {
    if (denseValue.isSplat()) {
      Attribute valueHandle = denseValue.getSplatValue<Attribute>();
      if (auto loopIndex = dyn_cast<IntegerAttr>(valueHandle))
        return loopIndex.getValue().isZero();
      if (auto fieldValue = dyn_cast<FloatAttr>(valueHandle))
        return fieldValue.getValue().isZero();
      return false;
    }
    if (denseValue.getElementType().isIntOrIndex())
      return llvm::all_of(
          denseValue.getValues<APInt>(),
          [](const APInt &arrayValue) { return arrayValue.isZero(); });
    if (isa<FloatType>(denseValue.getElementType()))
      return llvm::all_of(
          denseValue.getValues<APFloat>(),
          [](const APFloat &arrayValue) { return arrayValue.isZero(); });
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
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<memref::MemRefDialect>();
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    SmallVector<memref::GlobalOp> globals(module.getOps<memref::GlobalOp>());
    for (memref::GlobalOp globalOp : globals) {
      if (globalOp.getConstant() || !hasNoOrZeroInit(globalOp))
        continue;
      MemRefType memRefType = globalOp.getType();
      if (!memRefType.hasStaticShape())
        continue;
      std::optional<SymbolTable::UseRange> symbolUses =
          SymbolTable::getSymbolUses(globalOp, module);
      if (!symbolUses)
        continue;
      SmallVector<memref::GetGlobalOp> sites;
      func::FuncOp owner;
      bool eligible = true;
      for (const SymbolTable::SymbolUse &use : *symbolUses) {
        auto globalUse = dyn_cast<memref::GetGlobalOp>(use.getUser());
        auto fn = globalUse ? globalUse->getParentOfType<func::FuncOp>()
                            : func::FuncOp();
        if (!globalUse || !fn || (owner && fn != owner)) {
          eligible = false;
          break;
        }
        owner = fn;
        sites.push_back(globalUse);
      }
      if (!eligible || !owner || sites.empty())
        continue;

      OpBuilder buildPoint(&owner.getBody().front(),
                           owner.getBody().front().begin());
      auto localAlloca =
          memref::AllocaOp::create(buildPoint, globalOp.getLoc(), memRefType);
      StringRef symbolName = globalOp.getSymName();
      for (NamedAttribute arrayValue : globalOp->getDiscardableAttrs())
        if (arrayValue.getName().strref().starts_with("hls."))
          localAlloca->setAttr(arrayValue.getName(), arrayValue.getValue());
      if (auto variableName =
              globalOp->getAttrOfType<StringAttr>("polygeist.varname"))
        localAlloca->setAttr("polygeist.varname", variableName);
      else
        localAlloca->setAttr("polygeist.varname",
                             buildPoint.getStringAttr(symbolName));
      localAlloca->setAttr("hls.preserve", buildPoint.getUnitAttr());
      localAlloca->setAttr("hls.from_global",
                           buildPoint.getStringAttr(symbolName));
      for (memref::GetGlobalOp globalUse : sites) {
        Value replacementValue = localAlloca.getResult();
        if (globalUse.getType() != replacementValue.getType()) {

          OpBuilder callback(globalUse);
          replacementValue =
              memref::CastOp::create(callback, globalUse.getLoc(),
                                     globalUse.getType(), replacementValue);
        }
        globalUse.getResult().replaceAllUsesWith(replacementValue);
        globalUse.erase();
      }
      globalOp.erase();
    }
  }
};

} // namespace

namespace circt::hls_analysis {
std::unique_ptr<Pass> createPromoteGlobalsToAllocasPass() {
  return std::make_unique<PromoteGlobalsToAllocasPass>();
}
} // namespace circt::hls_analysis
