# The PolarFire example of hls-doc/new-architecture.md, built out of tree: the
# storage selector usram-first, with the device file
# microchip-polarfire.device.json, the profile generic-1.0.profile.json and the
# configuration polarfire.json that names both.
#
#   cmake -G Ninja -S tools/hls-est-plugins/polarfire -B /tmp/polarfire-build \
#         -DMLIR_DIR=<llvm build>/lib/cmake/mlir \
#         -DCIRCT_DIR=<circt build>/lib/cmake/circt
#   ninja -C /tmp/polarfire-build
#   hls-est k.mlir --load-plugin=/tmp/polarfire-build/HlsEstPolarFirePlugin.so \
#           --hls-config=tools/hls-est-plugins/polarfire/polarfire.json \
#           --default-pipeline
#
# The plugin is compiled against the same build trees as the hls-est that
# loads it, with the same assertion setting (the CIRCT build here is a Debug
# build: keep CMAKE_BUILD_TYPE empty or Debug), C++17 and no RTTI, and it
# links nothing: every symbol resolves in the hls-est executable. The CIRCT
# build also builds a copy of it (tools/hls-est-plugins/CMakeLists.txt) for
# the lit test test/hls-est/Plugins/usram_first.mlir.
cmake_minimum_required(VERSION 3.20)
project(HlsEstPolarFirePlugin C CXX)
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

add_llvm_library(HlsEstPolarFirePlugin MODULE
  UsramFirst.cpp
)
target_compile_definitions(HlsEstPolarFirePlugin PRIVATE
  HLS_EST_PLUGIN_ORIGIN="usram-first")
