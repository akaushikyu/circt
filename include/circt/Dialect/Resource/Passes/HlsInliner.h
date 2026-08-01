//===- HlsInliner.h - func-dialect inliner that honours inline off --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_HLSINLINER_H
#define CIRCT_DIALECT_RESOURCE_PASSES_HLSINLINER_H

namespace mlir {
class DialectRegistry;
}

namespace circt::hls_analysis {

/// Registers hls-est's inliner interface for the func dialect, in place of
/// mlir::func::registerInlinerExtension: `--inline` then keeps every call
/// whose callee carries `hls.inline_off` (`#pragma HLS inline off`), as
/// Vitis HLS does (VITIS_NOTES.md N14), and inlines everything else as the
/// stock interface would. `--inline-ignore-inline-off` restores the old
/// behaviour for comparisons.
void registerHlsInlinerExtension(mlir::DialectRegistry &registry);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_HLSINLINER_H
