# In-tree copies of the out-of-tree example plugins (hls-doc/plugins.md), for
# the lit tests of test/hls-est/Plugins. Each subdirectory is also a CMake
# project of its own that builds the same sources against the build trees
# (see its CMakeLists.txt); this file is not that project.
#
#   HlsEstExamplePlugin    example/: the modulo scheduler asap-fixed-ii and the
#                          operator timing model clock-scaled
#   HlsEstPolarFirePlugin  polarfire/: the storage selector usram-first of
#                          hls-doc/new-architecture.md
add_llvm_library(HlsEstExamplePlugin MODULE BUILDTREE_ONLY
  example/AsapFixedII.cpp
  example/ClockScaledTiming.cpp
  example/PluginInfo.cpp

  DEPENDS
  hls-est
  PLUGIN_TOOL
  hls-est
)
target_include_directories(HlsEstExamplePlugin PRIVATE
  ${CIRCT_MAIN_INCLUDE_DIR} ${CIRCT_INCLUDE_DIR})
target_compile_definitions(HlsEstExamplePlugin PRIVATE
  HLS_EST_PLUGIN_ORIGIN="example")

add_llvm_library(HlsEstPolarFirePlugin MODULE BUILDTREE_ONLY
  polarfire/UsramFirst.cpp

  DEPENDS
  hls-est
  PLUGIN_TOOL
  hls-est
)
target_include_directories(HlsEstPolarFirePlugin PRIVATE
  ${CIRCT_MAIN_INCLUDE_DIR} ${CIRCT_INCLUDE_DIR})
target_compile_definitions(HlsEstPolarFirePlugin PRIVATE
  HLS_EST_PLUGIN_ORIGIN="usram-first")
