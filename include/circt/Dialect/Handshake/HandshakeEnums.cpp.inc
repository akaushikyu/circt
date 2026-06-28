/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Handshake.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

::llvm::StringRef stringifyBufferTypeEnum(BufferTypeEnum val) {
  switch (val) {
    case BufferTypeEnum::seq: return "seq";
    case BufferTypeEnum::fifo: return "fifo";
  }
  return "";
}

::std::optional<BufferTypeEnum> symbolizeBufferTypeEnum(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<BufferTypeEnum>>(str)
      .Case("seq", BufferTypeEnum::seq)
      .Case("fifo", BufferTypeEnum::fifo)
      .Default(::std::nullopt);
}
::std::optional<BufferTypeEnum> symbolizeBufferTypeEnum(uint32_t value) {
  switch (value) {
  case 0: return BufferTypeEnum::seq;
  case 1: return BufferTypeEnum::fifo;
  default: return ::std::nullopt;
  }
}

