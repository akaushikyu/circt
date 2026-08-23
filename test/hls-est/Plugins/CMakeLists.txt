# The plugin the lit tests of this directory load with --load-plugin
# (hls-doc/plugins.md): a MODULE that links nothing, every symbol resolves in
# the hls-est executable (export_executable_symbols_for_plugins).
add_llvm_library(HlsEstTestPlugin MODULE BUILDTREE_ONLY
  TestPlugin.cpp

  DEPENDS
  hls-est
  PLUGIN_TOOL
  hls-est
)
target_include_directories(HlsEstTestPlugin PRIVATE
  ${CIRCT_MAIN_INCLUDE_DIR} ${CIRCT_INCLUDE_DIR})
target_compile_definitions(HlsEstTestPlugin PRIVATE
  HLS_EST_PLUGIN_ORIGIN="test")
