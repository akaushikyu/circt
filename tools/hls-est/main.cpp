

#include "circt/Dialect/LoopSchedule/LoopScheduleDialect.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/Resource/Passes/AffineToLoopScheduleModified.h"
#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/Resource/Passes/DebugUnroll.h"
#include "circt/Dialect/Resource/Passes/InferVitisSplitArray.h"
#include "circt/Dialect/Resource/Passes/MemoryBankModified.h"
#include "circt/Dialect/Resource/Passes/MergeConditionalStores.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Transforms/Passes.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/Transforms/Passes.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/Func/Extensions/InlinerExtension.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Index/IR/IndexDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

#include "circt/Dialect/Calyx/CalyxDialect.h"
#include "circt/Dialect/Comb/CombDialect.h"
#include "circt/Dialect/HW/HWDialect.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Seq/SeqDialect.h"
#include "mlir/Dialect/DLTI/DLTI.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Math/IR/Math.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry targetRegistry;

  targetRegistry.insert<

      mlir::affine::AffineDialect, mlir::arith::ArithDialect,
      mlir::memref::MemRefDialect, mlir::scf::SCFDialect,
      mlir::func::FuncDialect, mlir::cf::ControlFlowDialect,
      mlir::index::IndexDialect, mlir::math::MathDialect, mlir::DLTIDialect,
      mlir::LLVM::LLVMDialect,

      circt::loopschedule::LoopScheduleDialect, circt::hw::HWDialect,
      circt::comb::CombDialect, circt::seq::SeqDialect,
      circt::calyx::CalyxDialect, circt::hls_analysis::HLSDialect>();

  mlir::func::registerInlinerExtension(targetRegistry);
  circt::hls_analysis::registerBRAMInterfaceExternalModels(targetRegistry);
  circt::hls_analysis::registerBRAMLoopscheduleAnalysisPass();
  circt::hls_analysis::registerAffineToLoopScheduleAnalysisPass();
  circt::hls_analysis::registerMergeConditionalStoresPass();
  circt::hls_analysis::registerMemoryBankingPassModified();
  circt::hls_analysis::registerAutoPipelineUnrollPass();
  circt::hls_analysis::registerDebugUnrollPass();
  circt::hls_analysis::registerInferVitisSplitArray();
  circt::hls_analysis::registerVitisCleanupPasses();

  mlir::affine::registerAffinePasses();
  mlir::registerCSEPass();
  mlir::registerCanonicalizerPass();
  mlir::registerTransformsPasses();

  return mlir::asMainReturnCode(mlir::MlirOptMain(
      argc, argv, "HLS BRAM analysis driver\n", targetRegistry));
}