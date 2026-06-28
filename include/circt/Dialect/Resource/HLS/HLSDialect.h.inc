/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HLS.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hls_analysis {

/// HLS resource and scheduling decisions made explicit.
/// Ops that carry Vitis-HLS implementation decisions the rest of the pipeline
/// would otherwise have to reconstruct: starting with a predicated
/// (write-enable) memory write that models a BRAM port whose write-enable is
/// driven by a runtime guard, instead of the read-modify-write `arith.select`
/// demux that fabricates a phantom read port.
class HLSDialect : public ::mlir::Dialect {
  explicit HLSDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~HLSDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("hls");
  }
};

} // namespace circt::hls_analysis
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::HLSDialect)
