# The plugin registries (hls-doc/plugins.md). The builtin implementations are
# compiled into HLSPasses (they share code with the passes); see
# lib/Dialect/Resource/Plugins/Builtin/.
add_circt_library(HLSPlugins
  Registry.cpp

  LINK_LIBS PUBLIC
  HLSConfig
  MLIRIR
  MLIRSupport
  MLIRFuncDialect
  MLIRAffineDialect
  MLIRSCFDialect
  CIRCTScheduling
)
