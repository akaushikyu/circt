# hls-est configuration (hls-doc/configuration.md): the schema, the loader and
# the compiled-in device and tool-profile files under data/, which are
# embedded as string literals at build time.
set(HLS_CONFIG_DATA
  base.json
  amd-xc7z020clg400-1.device.json
  vitis-2025.1.profile.json
)
set(HLS_CONFIG_INCS)
foreach(f ${HLS_CONFIG_DATA})
  set(out ${CMAKE_CURRENT_BINARY_DIR}/${f}.inc)
  add_custom_command(
    OUTPUT ${out}
    COMMAND ${CMAKE_COMMAND} -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/data/${f}
            -DOUTPUT=${out} -P ${CMAKE_CURRENT_SOURCE_DIR}/EmbedJson.cmake
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/data/${f}
            ${CMAKE_CURRENT_SOURCE_DIR}/EmbedJson.cmake
    COMMENT "Embedding hls-est configuration file ${f}")
  list(APPEND HLS_CONFIG_INCS ${out})
endforeach()
add_custom_target(HLSConfigData DEPENDS ${HLS_CONFIG_INCS})

add_circt_library(HLSConfig
  Config.cpp
  Loader.cpp
  Schema.cpp

  DEPENDS
  HLSConfigData

  LINK_LIBS PUBLIC
  LLVMSupport
)
target_include_directories(HLSConfig PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
