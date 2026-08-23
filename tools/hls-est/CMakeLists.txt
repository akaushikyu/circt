add_circt_tool(hls-est main.cpp
  DEPENDS
  SUPPORT_PLUGINS
)

target_link_libraries(hls-est PRIVATE
        # Upstream dialects
        MLIRAffineDialect
        MLIRArithDialect
        MLIRMemRefDialect
        MLIRSCFDialect
        MLIRFuncDialect
        MLIRFuncInlinerExtension
        MLIRControlFlowDialect
        MLIRIndexDialect
        MLIRMathDialect
        MLIRDLTIDialect
        MLIRLLVMDialect
        MLIRLLVMIRTransforms
        MLIRTransforms

        # CIRCT dialects
        CIRCTLoopSchedule
        CIRCTHW
        CIRCTComb
        CIRCTSeq
        CIRCTCalyx

        # Your libraries
        HLSConfig
        HLSInterfaces
        HLSPasses
        CIRCTHLS
        

        # Driver infrastructure
        MLIROptLib
)
# Plugins (hls-doc/plugins.md) are loaded with --load-plugin and resolve every
# LLVM / MLIR / CIRCT / hls-est symbol in this executable.
export_executable_symbols_for_plugins(hls-est)
