// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D4): the same with a cyclic array_partition pragma
// (kernel w9r22fx_f1_rom_part, Vitis 0).
// CHECK: Total BRAM: 0
module {
  memref.global "private" @_ZL3tab : memref<64xi32> = dense<[998642, 1012557, 998068, 723414, 717918, 1023161, 719505, 622983, 992574, 842427, 672970, 619362, 568202, 939691, 999287, 689432, 540017, 590521, 586731, 561672, 723735, 777983, 555831, 1010758, 866431, 986218, 729097, 769283, 832728, 1048338, 529104, 613405, 1003833, 815962, 950826, 611533, 790620, 854880, 765110, 827368, 555485, 597922, 637457, 944137, 637327, 829321, 929576, 594360, 541998, 524859, 748160, 744192, 579152, 1017105, 917989, 941017, 964471, 600874, 732419, 807168, 877545, 615665, 850614, 873029]> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "tab"}]}
  func.func @_Z3topPKiPi(%arg0: memref<64xi32>, %arg1: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = memref.get_global @_ZL3tab : memref<64xi32>
    affine.for %arg2 = 0 to 64 {
      %1 = affine.load %arg0[%arg2] : memref<64xi32>
      %2 = affine.load %0[%arg2] : memref<64xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = affine.load %0[-%arg2 + 63] : memref<64xi32>
      %5 = arith.addi %3, %4 : i32
      affine.store %5, %arg1[%arg2] : memref<64xi32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    return
  }
}
