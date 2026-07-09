// RUN: hls-est %s --symbol-privatize=exclude=attn --symbol-dce --inline --symbol-dce --vitis-fold --canonicalize --sccp --dead-memory-elimination | FileCheck %s --check-prefix=IR
// RUN: hls-est %s --symbol-privatize=exclude=attn_ctrl --symbol-dce --inline --symbol-dce --vitis-fold --canonicalize --sccp --dead-memory-elimination | FileCheck %s --check-prefix=CTRL
// RUN: hls-est %s --symbol-privatize=exclude=attn --symbol-dce --inline --symbol-dce --vitis-fold --canonicalize --sccp --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: hls-est %s --symbol-privatize=exclude=attn_ctrl --symbol-dce --inline --symbol-dce --vitis-fold --canonicalize --sccp --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=CTRLBRAM

// The forgebench attention kernel (CLAUDE.md step 2, VITIS_NOTES.md N1/N1a,
// dead_globals.md R5, kernels dg_d_apfixed16 / dg_d_apfixed4) in the integer
// form Vitis sees: data_t = ap_fixed<16,5> is an i16 with 11 fraction bits.
//   (data_t)16 wraps to raw 0x8000 = -16; hls::sqrt(-16) = 0 (raw 0x0);
//   scale = (data_t)1.0 / 0 = 2048 / 0 -> 0 (Vitis folds x/0 to 0, a.o.1.ll:50);
//   scores[i][j] = sum(Q*K) ... scores[i][j] *= scale -> store 0;
// (cgeist inlines every callee into the top, O10; here --inline does it) so
// the Q.K accumulation is overwritten before any read, the Q / K arrays
// and their QKV multiply-accumulates are dead, and only V and scores remain
// (Vitis: 2 BRAM, `Q`, `K` absent at a.o.1). The control @attn_ctrl has a
// non-zero square root (head_dim = 4: sqrt = 2.0 = raw 4096, scale = 0.5 =
// raw 1024): Q and K stay (dg_d_apfixed4: 8 BRAM).
//
// The fixed-point product is (sext(a) * sext(b)) >> 11, truncated to i16; the
// division 1.0/x is (2048 << 11) / x. The constant 0 that hls::sqrt returns
// for -16 is what a width-exact frontend would fold (OPEN_ISSUES.md O6); the
// x/0 fold and everything after it is hls-est's (--vitis-fold, DME).

// IR: hls.dead_memrefs = [{{.*}}name = "Q"{{.*}}name = "K"{{.*}}name = "scores_tmp"
// IR-LABEL: func.func @attn
// IR-NOT: varname = "Q"
// IR-NOT: varname = "K"
// IR-DAG: varname = "V"
// IR-DAG: varname = "scores"
// IR-NOT: varname = "Q"
// IR-NOT: varname = "K"
// IR: return

// CTRL-LABEL: func.func @attn_ctrl
// CTRL-DAG: varname = "Q"
// CTRL-DAG: varname = "K"
// CTRL-DAG: varname = "V"
// CTRL-DAG: varname = "scores"

// DBG: [attn#{{[0-9]+}}] V (alloca)
// DBG: bram: 2
// DBG: [attn#{{[0-9]+}}] scores (alloca)
// DBG: bram: 1
// DBG: [attn#dead{{[0-9]+}}] Q (alloca)
// DBG: status: eliminated_dead -- removed by --dead-memory-elimination: no load from it reaches a side effect that leaves the function
// DBG-SAME: affine.load at dme_attention_int.mlir:{{[0-9]+}}:{{[0-9]+}} -> arith.extsi
// DBG-SAME: -> arith.addi (dme_attention_int.mlir:{{[0-9]+}}:{{[0-9]+}}) [its store to 'scores' at dme_attention_int.mlir:{{[0-9]+}}:{{[0-9]+}} is overwritten by the store at dme_attention_int.mlir:{{[0-9]+}}:{{[0-9]+}} before any read]
// DBG-SAME: -> out of affine.for (dme_attention_int.mlir:{{[0-9]+}}:{{[0-9]+}}) -> stored into 'scores_tmp' (dead)
// DBG: bram: 0
// DBG: [attn#dead{{[0-9]+}}] K (alloca)
// DBG: status: eliminated_dead
// DBG: [attn#dead{{[0-9]+}}] scores_tmp (alloca)
// DBG: status: eliminated_dead -- removed by --dead-memory-elimination: write-only: never read
// DBG: Total BRAM: 3

// The control keeps Q and K (2 BRAM each): 7 BRAM in all.
// CTRLBRAM-COUNT-4: kind=
// CTRLBRAM: Total BRAM: 7

module {
  func.func @attn(%x: memref<8x256xi16>, %wq: memref<256x256xi16>, %wk: memref<256x256xi16>, %wv: memref<256x256xi16>, %out: memref<8x256xi16>) {
    %sqrt = arith.constant 0 : i32            // hls::sqrt((data_t)16) = sqrt(-16) -> 0
    %c2048 = arith.constant 4194304 : i32     // (data_t)1.0 = 2048, pre-shifted by 11 for the quotient
    %scale32 = arith.divsi %c2048, %sqrt : i32
    %scale = arith.trunci %scale32 : i32 to i16
    func.call @body(%x, %wq, %wk, %wv, %out, %scale) : (memref<8x256xi16>, memref<256x256xi16>, memref<256x256xi16>, memref<256x256xi16>, memref<8x256xi16>, i16) -> ()
    return
  }
  func.func @attn_ctrl(%x: memref<8x256xi16>, %wq: memref<256x256xi16>, %wk: memref<256x256xi16>, %wv: memref<256x256xi16>, %out: memref<8x256xi16>) {
    %sqrt = arith.constant 4096 : i32         // hls::sqrt((data_t)4) = 2.0
    %c2048 = arith.constant 4194304 : i32
    %scale32 = arith.divsi %c2048, %sqrt : i32
    %scale = arith.trunci %scale32 : i32 to i16
    func.call @body(%x, %wq, %wk, %wv, %out, %scale) : (memref<8x256xi16>, memref<256x256xi16>, memref<256x256xi16>, memref<256x256xi16>, memref<8x256xi16>, i16) -> ()
    return
  }
  // cgeist's form of the kernel (forgebench attention_op_p1 top.cpp:63-130):
  // the accumulators are iter_args and the running value is also stored in
  // every iteration.
  func.func @body(%x: memref<8x256xi16>, %wq: memref<256x256xi16>, %wk: memref<256x256xi16>, %wv: memref<256x256xi16>, %out: memref<8x256xi16>, %scale: i16) {
    %c0 = arith.constant 0 : i16
    %c11 = arith.constant 11 : i32
    %Q = memref.alloca() {hls.preserve, polygeist.varname = "Q"} : memref<8x256xi16>
    %K = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<8x256xi16>
    %V = memref.alloca() {hls.preserve, polygeist.varname = "V"} : memref<8x256xi16>
    %scores = memref.alloca() {hls.preserve, polygeist.varname = "scores"} : memref<8x8xi16>
    %scores_tmp = memref.alloca() {polygeist.varname = "scores_tmp"} : memref<8x8xi16>
    affine.for %i = 0 to 8 {
      affine.for %j = 0 to 256 {
        affine.store %c0, %Q[%i, %j] : memref<8x256xi16>
        affine.store %c0, %K[%i, %j] : memref<8x256xi16>
        affine.store %c0, %V[%i, %j] : memref<8x256xi16>
        %acc:3 = affine.for %k = 0 to 256 iter_args(%aq = %c0, %ak = %c0, %av = %c0) -> (i16, i16, i16) {
          %xv = affine.load %x[%i, %k] : memref<8x256xi16>
          %xe = arith.extsi %xv : i16 to i32
          %q = affine.load %wq[%j, %k] : memref<256x256xi16>
          %qe = arith.extsi %q : i16 to i32
          %qm = arith.muli %xe, %qe : i32
          %qs = arith.shrsi %qm, %c11 : i32
          %qt = arith.trunci %qs : i32 to i16
          %nq = arith.addi %aq, %qt : i16
          affine.store %nq, %Q[%i, %j] : memref<8x256xi16>
          %kv = affine.load %wk[%j, %k] : memref<256x256xi16>
          %ke = arith.extsi %kv : i16 to i32
          %km = arith.muli %xe, %ke : i32
          %ks = arith.shrsi %km, %c11 : i32
          %kt = arith.trunci %ks : i32 to i16
          %nk = arith.addi %ak, %kt : i16
          affine.store %nk, %K[%i, %j] : memref<8x256xi16>
          %vv = affine.load %wv[%j, %k] : memref<256x256xi16>
          %ve = arith.extsi %vv : i16 to i32
          %vm = arith.muli %xe, %ve : i32
          %vs = arith.shrsi %vm, %c11 : i32
          %vt = arith.trunci %vs : i32 to i16
          %nv = arith.addi %av, %vt : i16
          affine.store %nv, %V[%i, %j] : memref<8x256xi16>
          affine.yield %nq, %nk, %nv : i16, i16, i16
        }
      }
    }
    affine.for %i = 0 to 8 {
      affine.for %j = 0 to 8 {
        affine.store %c0, %scores[%i, %j] : memref<8x8xi16>
        %s = affine.for %d = 0 to 16 iter_args(%a = %c0) -> (i16) {
          %qv = affine.load %Q[%i, %d] : memref<8x256xi16>
          %kv = affine.load %K[%j, %d] : memref<8x256xi16>
          %qe = arith.extsi %qv : i16 to i32
          %ke = arith.extsi %kv : i16 to i32
          %m = arith.muli %qe, %ke : i32
          %sh = arith.shrsi %m, %c11 : i32
          %t = arith.trunci %sh : i32 to i16
          %n = arith.addi %a, %t : i16
          affine.store %n, %scores[%i, %j] : memref<8x8xi16>
          affine.yield %n : i16
        }
        // A scratch copy that nothing reads (write-only: removed).
        affine.store %s, %scores_tmp[%i, %j] : memref<8x8xi16>
        // scores[i][j] *= scale
        %sv = affine.load %scores[%i, %j] : memref<8x8xi16>
        %se = arith.extsi %sv : i16 to i32
        %sc = arith.extsi %scale : i16 to i32
        %p = arith.muli %se, %sc : i32
        %ps = arith.shrsi %p, %c11 : i32
        %pt = arith.trunci %ps : i32 to i16
        affine.store %pt, %scores[%i, %j] : memref<8x8xi16>
      }
    }
    affine.for %i = 0 to 8 {
      affine.for %d = 0 to 16 {
        %ctx = affine.for %j = 0 to 8 iter_args(%a = %c0) -> (i16) {
          %sv = affine.load %scores[%i, %j] : memref<8x8xi16>
          %vv = affine.load %V[%j, %d] : memref<8x256xi16>
          %se = arith.extsi %sv : i16 to i32
          %ve = arith.extsi %vv : i16 to i32
          %m = arith.muli %se, %ve : i32
          %sh = arith.shrsi %m, %c11 : i32
          %t = arith.trunci %sh : i32 to i16
          %n = arith.addi %a, %t : i16
          affine.yield %n : i16
        }
        affine.store %ctx, %out[%i, %d] : memref<8x256xi16>
      }
    }
    return
  }
}
