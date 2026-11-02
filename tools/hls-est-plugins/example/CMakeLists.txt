# An hls-est plugin built out of tree (hls-doc/plugins.md): a modulo scheduler
# (asap-fixed-ii) and an operator timing model (clock-scaled).
#
#   cmake -G Ninja -S tools/hls-est-plugins/example -B /tmp/example-build \
#         -DMLIR_DIR=<llvm build>/lib/cmake/mlir \
#         -DCIRCT_DIR=<circt build>/lib/cmake/circt
#   ninja -C /tmp/example-build
#   hls-est k.mlir --load-plugin=/tmp/example-build/HlsEstExamplePlugin.so \
#           --config-set scheduling.modulo.model=asap-fixed-ii --default-pipeline
#
# The plugin is compiled against the same build trees as the hls-est that
# loads it, with the same assertion setting (the CIRCT build here is a Debug
# build: keep CMAKE_BUILD_TYPE empty or Debug), C++17 and no RTTI, and it
# links nothing: every symbol resolves in the hls-est executable. The CIRCT
# build also builds a copy of it (tools/hls-est-plugins/CMakeLists.txt) for
# the lit test test/hls-est/Plugins/example_plugin.mlir.
cmake_minimum_required(VERSION 3.20)
project(HlsEstExamplePlugin C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(MLIR REQUIRED CONFIG)
find_package(CIRCT REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}" "${MLIR_CMAKE_DIR}")
include(AddLLVM)
include(HandleLLVMOptions)

include_directories(${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS}
                    ${CIRCT_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_llvm_library(HlsEstExamplePlugin MODULE
  AsapFixedII.cpp
  ClockScaledTiming.cpp
  PluginInfo.cpp
)
target_compile_definitions(HlsEstExamplePlugin PRIVATE
  HLS_EST_PLUGIN_ORIGIN="example")
