// RUN: hls-est %s '--infer-vitis-split-array=td=off annotate-pressure=false' --config-set tool.hls.partitioning.constant_index.non_affine_arrays=false --config-set tool.hls.partitioning.constant_index.after_user_partition=false | FileCheck %s --check-prefix=OFF
// The RUN lines pin the rule (b) of before W9r7-impl 5/10 (no rule (b) on
// non-affine arrays or after a user partition); the new rule is tested in
// w9r7_partition_{after_user,non_affine}.mlir.
// RUN: hls-est %s '--infer-vitis-split-array=td=auto annotate-pressure=false' --config-set tool.hls.partitioning.constant_index.non_affine_arrays=false --config-set tool.hls.partitioning.constant_index.after_user_partition=false | FileCheck %s --check-prefix=AUTO
// RUN: hls-est %s '--infer-vitis-split-array=td=auto auto-partitions=true annotate-pressure=false' --config-set tool.hls.partitioning.constant_index.non_affine_arrays=false --config-set tool.hls.partitioning.constant_index.after_user_partition=false | FileCheck %s --check-prefix=AUTOP
// The defaults (rule (b) also on arrays without an affine access, N57)
// differ from the pinned lines only in @memref_only:
// RUN: hls-est %s '--infer-vitis-split-array=td=off annotate-pressure=false' | FileCheck %s --check-prefix=DEF
// RUN: not hls-est %s --infer-vitis-split-array=td=on 2>&1 | FileCheck %s --check-prefix=BAD
// RUN: hls-est %s '--infer-vitis-split-array=td=off annotate-pressure=false emit-remarks=true' 2>&1 --config-set tool.hls.partitioning.constant_index.non_affine_arrays=false --config-set tool.hls.partitioning.constant_index.after_user_partition=false | FileCheck %s --check-prefix=REMARK

// --infer-vitis-split-array td=off: only the automatic partitions Vitis 2025.1
// still makes with syn.array_partition.throughput_driven=off (VITIS_NOTES.md
// N7, exp-notes/partition.md R5, partition_chk.md R5):
//  (a) <= 4 elements in total -> registers ([HLS 214-421]; small_w32_n4 vs
//      small_w32_n5, small_2d_2x2);
//  (b) a dimension every access indexes with a constant -> complete on that
//      dimension ([HLS 214-449]; ci2d_cc_64x8 -> 8 banks, ci2d_cc_8x64 ->
//      dim 1);
//  (c) every access constant in every dimension -> registers (ci_both_n64);
// and nothing else: a variable index anywhere on the dimension blocks (b)
// (ci2d_64x8, partition_chk_ci2d_mixed: RAM_1WNR instead), a 1-D array
// written with a variable index and read at constants stays whole (ci_rd_n64),
// and a user pragma is left alone. td=auto (the default) is the port-pressure
// inference, unchanged unless auto-partitions is set.
// The inputs are what --auto-pipeline-unroll leaves: inner loops unrolled
// into constant indices.

// BAD: td must be 'auto' or 'off', got 'on'

// (a) int A[4] -> registers.
// OFF-LABEL: func.func @small_n4
// OFF: memref.alloca() {hls.registers, hls.registers_reason = "4 element(s) <= complete-threshold 4: completely partitioned into registers {{.*}}214-421{{.*}}"{{.*}}} : memref<4xi32>
// AUTO-LABEL: func.func @small_n4
// AUTO-NOT: hls.registers
// AUTO: return
// AUTOP-LABEL: func.func @small_n4
// AUTOP: memref.alloca() {hls.registers
func.func @small_n4(%in: memref<4xi32>, %out: memref<4xi32>) {
  %c3 = arith.constant 3 : i32
  %A = memref.alloca() {polygeist.varname = "A"} : memref<4xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.load %in[%i] : memref<4xi32>
    affine.store %0, %A[%i] : memref<4xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  affine.for %i = 0 to 4 {
    %0 = affine.load %A[%i] : memref<4xi32>
    %1 = arith.muli %0, %c3 : i32
    affine.store %1, %out[%i] : memref<4xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}

// int A[5] stays a RAM (0 BRAM by the LUTRAM rule, not registers); int[2][2]
// and char[4] are registers: the threshold counts elements, not bits.
// OFF-LABEL: func.func @small_n5_2x2_w8
// OFF: memref.alloca() {polygeist.varname = "A5"} : memref<5xi32>
// OFF: memref.alloca() {hls.registers, {{.*}}"4 element(s){{.*}}polygeist.varname = "A22"} : memref<2x2xi32>
// OFF: memref.alloca() {hls.registers, {{.*}}"4 element(s){{.*}}polygeist.varname = "C4"} : memref<4xi8>
func.func @small_n5_2x2_w8(%in: memref<5xi32>, %out: memref<5xi32>, %c: memref<4xi8>) {
  %A5 = memref.alloca() {polygeist.varname = "A5"} : memref<5xi32>
  %A22 = memref.alloca() {polygeist.varname = "A22"} : memref<2x2xi32>
  %C4 = memref.alloca() {polygeist.varname = "C4"} : memref<4xi8>
  affine.for %i = 0 to 5 {
    %0 = affine.load %in[%i] : memref<5xi32>
    affine.store %0, %A5[%i] : memref<5xi32>
  }
  affine.for %i = 0 to 2 {
    affine.for %j = 0 to 2 {
      %0 = affine.load %A5[%i * 2 + %j] : memref<5xi32>
      affine.store %0, %A22[%i, %j] : memref<2x2xi32>
    }
  }
  affine.for %i = 0 to 5 {
    %0 = affine.load %A5[%i] : memref<5xi32>
    affine.store %0, %out[%i] : memref<5xi32>
  }
  affine.for %i = 0 to 4 {
    %0 = affine.load %c[%i] : memref<4xi8>
    affine.store %0, %C4[%i] : memref<4xi8>
  }
  return
}

// (b) int A[64][8], j unrolled in the copy-in and in the read loop: dimension
// 2 only ever sees constants -> complete dim=2, 8 banks of 64 words. Under
// td=auto the same array is split by port pressure (8 reads per iteration)
// with the inference's own provenance.
// OFF-LABEL: func.func @const_dim2
// OFF: memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "complete", source = "constant-index", variable = "A"}], hls.partition_reason = "every one of the 16 access(es) indexes dimension(s) 2 with a constant{{.*}}214-449{{.*}}"
// AUTO-LABEL: func.func @const_dim2
// AUTO: memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "complete", source = "infer-from-design", variable = "A"}]
// AUTOP-LABEL: func.func @const_dim2
// AUTOP: memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "complete", source = "constant-index", variable = "A"}]
func.func @const_dim2(%in: memref<64x8xi32>, %out: memref<64x8xi32>) {
  %c0 = arith.constant 0 : index
  %A = memref.alloca() {polygeist.varname = "A"} : memref<64x8xi32>
  affine.for %i = 0 to 64 {
    %v0 = affine.load %in[%i, 0] : memref<64x8xi32>
    affine.store %v0, %A[%i, %c0] : memref<64x8xi32>
    %c1 = affine.apply affine_map<(d0) -> (d0 + 1)>(%c0)
    %v1 = affine.load %in[%i, 1] : memref<64x8xi32>
    affine.store %v1, %A[%i, %c1] : memref<64x8xi32>
    %v2 = affine.load %in[%i, 2] : memref<64x8xi32>
    affine.store %v2, %A[%i, 2] : memref<64x8xi32>
    %v3 = affine.load %in[%i, 3] : memref<64x8xi32>
    affine.store %v3, %A[%i, 3] : memref<64x8xi32>
    %v4 = affine.load %in[%i, 4] : memref<64x8xi32>
    affine.store %v4, %A[%i, 4] : memref<64x8xi32>
    %v5 = affine.load %in[%i, 5] : memref<64x8xi32>
    affine.store %v5, %A[%i, 5] : memref<64x8xi32>
    %v6 = affine.load %in[%i, 6] : memref<64x8xi32>
    affine.store %v6, %A[%i, 6] : memref<64x8xi32>
    %v7 = affine.load %in[%i, 7] : memref<64x8xi32>
    affine.store %v7, %A[%i, 7] : memref<64x8xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  affine.for %i = 0 to 64 {
    %r0 = affine.load %A[%i, 7] : memref<64x8xi32>
    affine.store %r0, %out[%i, 0] : memref<64x8xi32>
    %r1 = affine.load %A[%i, 6] : memref<64x8xi32>
    affine.store %r1, %out[%i, 1] : memref<64x8xi32>
    %r2 = affine.load %A[%i, 5] : memref<64x8xi32>
    affine.store %r2, %out[%i, 2] : memref<64x8xi32>
    %r3 = affine.load %A[%i, 4] : memref<64x8xi32>
    affine.store %r3, %out[%i, 3] : memref<64x8xi32>
    %r4 = affine.load %A[%i, 3] : memref<64x8xi32>
    affine.store %r4, %out[%i, 4] : memref<64x8xi32>
    %r5 = affine.load %A[%i, 2] : memref<64x8xi32>
    affine.store %r5, %out[%i, 5] : memref<64x8xi32>
    %r6 = affine.load %A[%i, 1] : memref<64x8xi32>
    affine.store %r6, %out[%i, 6] : memref<64x8xi32>
    %r7 = affine.load %A[%i, 0] : memref<64x8xi32>
    affine.store %r7, %out[%i, 7] : memref<64x8xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}

// (b) on dimension 1 (ci2d_cc_8x64 shape, rows unrolled); one row index is the
// counter of a loop that runs exactly once, which is a constant too. The
// rows are written in a loop that is not pipelined: every access counts.
// OFF-LABEL: func.func @const_dim1
// OFF: memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "complete", source = "constant-index", variable = "A"}]
func.func @const_dim1(%in: memref<4x64xi32>, %out: memref<64xi32>) {
  %A = memref.alloca() {polygeist.varname = "A"} : memref<4x64xi32>
  affine.for %j = 0 to 64 {
    %v0 = affine.load %in[0, %j] : memref<4x64xi32>
    affine.store %v0, %A[0, %j] : memref<4x64xi32>
    %v1 = affine.load %in[1, %j] : memref<4x64xi32>
    affine.store %v1, %A[1, %j] : memref<4x64xi32>
    %v2 = affine.load %in[2, %j] : memref<4x64xi32>
    affine.store %v2, %A[2, %j] : memref<4x64xi32>
    affine.for %t = 3 to 4 {
      %v3 = affine.load %in[%t, %j] : memref<4x64xi32>
      affine.store %v3, %A[%t, %j] : memref<4x64xi32>
    }
  } {hls.pipeline_off}
  affine.for %j = 0 to 64 {
    %a = affine.load %A[0, %j] : memref<4x64xi32>
    %b = affine.load %A[3, %j] : memref<4x64xi32>
    %s = arith.addi %a, %b : i32
    affine.store %s, %out[%j] : memref<64xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}

// (c) int B[8], both loops unrolled: every access constant -> scalarised.
// OFF-LABEL: func.func @all_const
// OFF: memref.alloca() {hls.registers, hls.registers_reason = "every one of the 16 access(es) uses a constant index in every dimension: scalarised{{.*}}"{{.*}}} : memref<8xi32>
// AUTO-LABEL: func.func @all_const
// AUTO-NOT: hls.registers
// AUTO: return
func.func @all_const(%in: memref<8xi32>, %out: memref<8xi32>) {
  %B = memref.alloca() {polygeist.varname = "B"} : memref<8xi32>
  %v0 = affine.load %in[0] : memref<8xi32>
  affine.store %v0, %B[0] : memref<8xi32>
  %v1 = affine.load %in[1] : memref<8xi32>
  affine.store %v1, %B[1] : memref<8xi32>
  %v2 = affine.load %in[2] : memref<8xi32>
  affine.store %v2, %B[2] : memref<8xi32>
  %v3 = affine.load %in[3] : memref<8xi32>
  affine.store %v3, %B[3] : memref<8xi32>
  %v4 = affine.load %in[4] : memref<8xi32>
  affine.store %v4, %B[4] : memref<8xi32>
  %v5 = affine.load %in[5] : memref<8xi32>
  affine.store %v5, %B[5] : memref<8xi32>
  %v6 = affine.load %in[6] : memref<8xi32>
  affine.store %v6, %B[6] : memref<8xi32>
  %v7 = affine.load %in[7] : memref<8xi32>
  affine.store %v7, %B[7] : memref<8xi32>
  %c7 = arith.constant 7 : index
  %r0 = memref.load %B[%c7] : memref<8xi32>
  affine.store %r0, %out[0] : memref<8xi32>
  %r1 = affine.load %B[6] : memref<8xi32>
  affine.store %r1, %out[1] : memref<8xi32>
  %r2 = affine.load %B[5] : memref<8xi32>
  affine.store %r2, %out[2] : memref<8xi32>
  %r3 = affine.load %B[4] : memref<8xi32>
  affine.store %r3, %out[3] : memref<8xi32>
  %r4 = affine.load %B[3] : memref<8xi32>
  affine.store %r4, %out[4] : memref<8xi32>
  %r5 = affine.load %B[2] : memref<8xi32>
  affine.store %r5, %out[5] : memref<8xi32>
  %r6 = affine.load %B[1] : memref<8xi32>
  affine.store %r6, %out[6] : memref<8xi32>
  %r7 = affine.load %B[0] : memref<8xi32>
  affine.store %r7, %out[7] : memref<8xi32>
  return
}

// Not partitioned: a 1-D array written with a variable index and read only at
// constant indices (ci_rd_n64: one ram_2p, 2 BRAM), and a dimension that one
// loop indexes with its counter although another reads it at constants
// (ci2d_64x8 / partition_chk_ci2d_mixed: RAM_1WNR with 7 copies instead).
// Under td=auto the second one is split by port pressure.
// OFF-LABEL: func.func @not_partitioned
// OFF: memref.alloca() {polygeist.varname = "B"} : memref<64xi32>
// OFF: memref.alloca() {polygeist.varname = "A"} : memref<64x8xi32>
// AUTO-LABEL: func.func @not_partitioned
// AUTO: memref.alloca() {polygeist.varname = "B"} : memref<64xi32>
// AUTO: memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "complete", source = "infer-from-design", variable = "A"}]
func.func @not_partitioned(%in: memref<64xi32>, %in2: memref<64x8xi32>, %out: memref<64xi32>) {
  %B = memref.alloca() {polygeist.varname = "B"} : memref<64xi32>
  %A = memref.alloca() {polygeist.varname = "A"} : memref<64x8xi32>
  affine.for %i = 0 to 64 {
    %0 = affine.load %in[%i] : memref<64xi32>
    affine.store %0, %B[%i] : memref<64xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  %b0 = affine.load %B[63] : memref<64xi32>
  %b1 = affine.load %B[62] : memref<64xi32>
  %bs = arith.addi %b0, %b1 : i32
  affine.store %bs, %out[0] : memref<64xi32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %in2[%i, %j] : memref<64x8xi32>
      affine.store %0, %A[%i, %j] : memref<64x8xi32>
    }
  }
  affine.for %i = 0 to 64 {
    %r0 = affine.load %A[%i, 0] : memref<64x8xi32>
    %r1 = affine.load %A[%i, 1] : memref<64x8xi32>
    %r2 = affine.load %A[%i, 2] : memref<64x8xi32>
    %r3 = affine.load %A[%i, 3] : memref<64x8xi32>
    %r4 = affine.load %A[%i, 4] : memref<64x8xi32>
    %r5 = affine.load %A[%i, 5] : memref<64x8xi32>
    %r6 = affine.load %A[%i, 6] : memref<64x8xi32>
    %r7 = affine.load %A[%i, 7] : memref<64x8xi32>
    %s0 = arith.addi %r0, %r1 : i32
    %s1 = arith.addi %r2, %r3 : i32
    %s2 = arith.addi %r4, %r5 : i32
    %s3 = arith.addi %r6, %r7 : i32
    %s4 = arith.addi %s0, %s1 : i32
    %s5 = arith.addi %s2, %s3 : i32
    %s6 = arith.addi %s4, %s5 : i32
    affine.store %s6, %out[%i] : memref<64xi32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}

// Left alone: a user pragma decides (p2d_cyc4_d1 keeps its 4 cyclic banks;
// a small array with a pragma is not turned into registers either), and an
// array that escapes into a call cannot be analysed for constant indices -
// but rule (a) does not look at the accesses, so a small array passed to a
// call still becomes registers.
// OFF-LABEL: func.func @left_alone
// OFF: memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "P"}], polygeist.varname = "P"} : memref<4xi32>
// OFF: memref.alloca() {polygeist.varname = "E"} : memref<16x8xi32>
// OFF: memref.alloca() {hls.registers, {{.*}}polygeist.varname = "S"} : memref<3xi32>
func.func private @use(memref<16x8xi32>, memref<3xi32>)
func.func @left_alone(%in: memref<4xi32>) {
  %P = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "P"}], polygeist.varname = "P"} : memref<4xi32>
  %E = memref.alloca() {polygeist.varname = "E"} : memref<16x8xi32>
  %S = memref.alloca() {polygeist.varname = "S"} : memref<3xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.load %in[%i] : memref<4xi32>
    affine.store %0, %P[%i] : memref<4xi32>
  }
  %v = affine.load %in[0] : memref<4xi32>
  affine.store %v, %E[0, 0] : memref<16x8xi32>
  func.call @use(%E, %S) : (memref<16x8xi32>, memref<3xi32>) -> ()
  return
}

// Rule (b) needs an affine access: memory banking only splits an array that
// has one (and then rewrites its memref.load / memref.store too), so an array
// reached only through memref.load / memref.store gets no spec - it would be
// priced as one memory anyway - and the decision is reported as a remark.
// Rule (c) needs no banking and still applies to such an array.
// DEF-LABEL: func.func @memref_only
// DEF: memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "complete", source = "constant-index", variable = "M"}]{{.*}} : memref<64x8xi32>
// OFF-LABEL: func.func @memref_only
// OFF: memref.alloca() {polygeist.varname = "M"} : memref<64x8xi32>
// OFF: memref.alloca() {hls.registers, {{.*}}polygeist.varname = "N"} : memref<8xi32>
// REMARK: remark: array 'M' left whole: every one of the 4 access(es) indexes dimension(s) 2 with a constant, but none is an affine access, so memory banking cannot split the array: left whole
func.func @memref_only(%in: memref<64x8xi32>, %out: memref<64xi32>) {
  %c0 = arith.constant 0 : index
  %c3 = arith.constant 3 : index
  %M = memref.alloca() {polygeist.varname = "M"} : memref<64x8xi32>
  %N = memref.alloca() {polygeist.varname = "N"} : memref<8xi32>
  affine.for %i = 0 to 64 {
    %v = memref.load %in[%i, %c0] : memref<64x8xi32>
    memref.store %v, %M[%i, %c0] : memref<64x8xi32>
    memref.store %v, %M[%i, %c3] : memref<64x8xi32>
    memref.store %v, %N[%c3] : memref<8xi32>
  }
  affine.for %i = 0 to 64 {
    %a = memref.load %M[%i, %c0] : memref<64x8xi32>
    %b = memref.load %M[%i, %c3] : memref<64x8xi32>
    %n = memref.load %N[%c3] : memref<8xi32>
    %s = arith.addi %a, %b : i32
    %t = arith.addi %s, %n : i32
    memref.store %t, %out[%i] : memref<64xi32>
  }
  return
}
