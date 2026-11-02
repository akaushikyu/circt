#ifndef HLS_PASSES_INFERVITISSPLITARRAY_H
#define HLS_PASSES_INFERVITISSPLITARRAY_H

#include "mlir/Pass/Pass.h"
#include <memory>

namespace circt::hls_analysis {
    std::unique_ptr<mlir::Pass> createInferVitisSplitArray();
    void registerInferVitisSplitArray();
} // namespace circt::hls_analysis

#endif