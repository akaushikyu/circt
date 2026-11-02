# Wraps a JSON file into a C++ raw string literal (one #include-able token).
# cmake -DINPUT=<file.json> -DOUTPUT=<file.json.inc> -P EmbedJson.cmake
file(READ "${INPUT}" content)
file(WRITE "${OUTPUT}.tmp" "R\"hlsestjson(${content})hlsestjson\"\n")
file(COPY_FILE "${OUTPUT}.tmp" "${OUTPUT}" ONLY_IF_DIFFERENT)
file(REMOVE "${OUTPUT}.tmp")
