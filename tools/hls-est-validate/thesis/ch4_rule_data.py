"""The rule catalogue of thesis chapter 4 ("The inferred decision model"), as data.

Each rule is a hand-written statement of a Vitis HLS 2025.1 behaviour recorded in
hls-doc/notes/VITIS_NOTES.md (cited by N-number), with the minimal kernels that show it. The prose holds
no measured number: every Vitis number is read by make_ch4_rules.py from the kernel's own run
(`~/hls-est-work/experiments/<kernel>/<hash>/result.json`), either in the rule's kernel table or through
an inline reference `[[kernel]]` (total BRAM_18K), `[[kernel:ii:LOOP]]` (achieved II),
`[[kernel:lat:LOOP]]` (iteration latency) or `[[kernel:mem:ARRAY]]` (the memory row). The constants of a
rule itself (64 trips, 1024 bits, 16 copies, the depth bands) are part of its statement, as the notes
state them. Catalogue effects are verbatim excerpts of the CHANGELOG entry named in `effect`.

Fields: id, stage, title, notes, statement, kernels [(name, what it shows, options)], evidence,
status, hlsest (status of the model in hls-est), mechanism (passes / tools), keys (configuration keys,
checked against the default configuration), effect (CHANGELOG heading substring, phrase or None).
"""

STAGES = [
    ("fe", "Front end, folding and dead memories",
     "What reaches the memory model at all: the C++ dialect, pragmas Vitis tolerates, the folds and "
     "the dead-code removal of the first optimisation stage (`a.o.1.ll`), ROMs and the element width "
     "a memory finally has (`a.o.2.ll`), and how struct and vector variables become memories."),
    ("fn", "Functions: inlining, instances and library cores",
     "Which functions survive as hardware modules, how many instances of each Vitis builds, and what a "
     "library math core costs; these decide how many times a memory is paid for."),
    ("lp", "Loop pipeline, unroll and flatten decision",
     "The automatic decision (`config_compile -pipeline_loops`, default 64) that fixes which loop is "
     "pipelined, which loops are completely unrolled into it and which nests are flattened. It decides "
     "the reads per iteration that every later stage counts."),
    ("pa", "Array partitioning and banking",
     "Banks from user pragmas, how pragmas combine and propagate across calls, the automatic partitions "
     "that remain under `throughput_driven=off`, and how a read with a run-time index finds its bank."),
    ("st", "Storage selection and RAM kinds",
     "Distributed RAM against BRAM, the port mode (one port, two ports, true dual port), and RAM_1WNR "
     "replication: when Vitis copies a memory to serve more reads per cycle, how many copies, and what "
     "stops it."),
    ("bf", "BRAM formula and aspect modes",
     "The RAMB18 count of one bank of D words x W bits: the depth bands of the 7-series primitive, the "
     "simple-dual-port x36 mode, and ROMs with several read ports."),
    ("df", "Streams, FIFOs, ping-pong buffers and dataflow",
     "hls::stream FIFOs, the FIFOs Vitis adds for dataflow arguments, ping-pong (PIPO) channels between "
     "dataflow processes, and the process merges that decide what a channel is."),
    ("if", "Interfaces",
     "Top-level arrays (ap_memory, s_axilite) and the m_axi adapters, whose read FIFOs and write "
     "buffers hold BRAM outside every memory table."),
    ("sc", "Scheduling-derived rules",
     "Rules on the achieved initiation interval (II), which sets the RAM_1WNR copy count: reduction "
     "reassociation, floating-point operator latencies, calls inside pipelines, user II targets and "
     "stream accesses."),
]

RULES = [
    # ------------------------------------------------------------------ front end
    dict(
        id="FE-1", stage="fe", title="The front end compiles C++14 with the synthesis macros defined",
        notes=["N19"],
        statement=(
            "Vitis's clang front end compiles C++ sources as C++14 and C sources as gnu99, and defines "
            "`__SYNTHESIS__`, `__VITIS_HLS__`, `AESL_SYN` and `__HLS_SYN__`. A `static_assert` on "
            "`__cplusplus == 201402L` synthesises, the C++17 twin stops with `[HLS 207-3504]`, and an "
            "`#ifdef __SYNTHESIS__ #error` fires. Code under `#ifndef __SYNTHESIS__` (testbench "
            "printing, file I/O) is therefore absent from what Vitis builds, and an estimator front end "
            "must compile with the same macros and standard."),
        kernels=[("w8a_std_cxx14", "static_assert(__cplusplus == 201402L)", {}),
                 ("w8a_std_cxx17neg", "static_assert(__cplusplus == 201703L)", {}),
                 ("w8a_std_synmacro", "#ifndef __SYNTHESIS__ #error", {})],
        evidence=["error message", "front-end command line (db/autopilot.flow.log)"],
        status="confirmed",
        hlsest="frontend: the harness compiles with the real headers' flags (`shim/real/cgeist_flags`)",
        mechanism=["cgeist", "run_hlsest.py --shim real"], keys=[], effect=None),
    dict(
        id="FE-2", stage="fe", title="Malformed or misplaced pragmas are warnings, and the pragma is dropped",
        notes=["N20", "N22", "N32", "N23"],
        statement=(
            "Vitis is lenient where a strict parser is not: an `unroll` outside a loop body "
            "(`[HLS 207-5589]`), an `array_partition` whose `dim` exceeds the array's rank "
            "(`[HLS 214-253]`) and a number or other token where an option name is expected "
            "(`[HLS 207-5571]`) are warnings, and the pragma has no effect. Two INTERFACE pragmas on one "
            "port are accepted and the later one decides the bundle. A partition of an undeclared "
            "variable, and source code clang rejects, are errors in Vitis as well, so such designs leave "
            "the comparison rather than counting as estimator failures."),
        kernels=[("w8b_pragma_unroll_outside", "unroll pragma in the function body", {"loops": ["VITIS"]}),
                 ("w8b_pragma_dim_range", "dim=3 on a 2-D array", {}),
                 ("w8b_pragma_undeclared", "partition of an undeclared variable", {}),
                 ("w8bfix_peq", "`#pragma HLS pipeline =2`", {"loops": ["L1"]}),
                 ("w8b_iface_two_maxi_bundle", "two m_axi pragmas, bundles fm then wt", {})],
        evidence=["log warnings [HLS 207-*]/[HLS 214-253]", "loop table", "error message"],
        status="confirmed",
        hlsest="frontend: cgeist warns and drops the pragma the same way",
        mechanism=["cgeist PragmaParser"], keys=[], effect=None),
    dict(
        id="FE-3", stage="fe", title="Console stream output is removed; side effects of its arguments stay",
        notes=["N30"],
        statement=(
            "Calls on `std::cout` and other standard streams are present in `a.g.ld.5.gdce.ll` and gone "
            "in `a.o.1.ll`; an increment written inside the printed expression is still performed."),
        kernels=[("w8b7_cout1", "a fill loop that prints `k++` per element", {})],
        evidence=["IR a.g.ld.5 vs a.o.1", "memory table"],
        status="confirmed",
        hlsest="frontend: cgeist drops calls whose object is a standard stream",
        mechanism=["cgeist VisitCallExpr"], keys=[], effect=None),
    dict(
        id="FE-4", stage="fe", title="Dead memories are deleted before allocation, but load-store cycles are kept",
        notes=["N1", "N1a", "N66", "N73"],
        statement=(
            "An array (local, global or static) whose loads never reach a top-level output is removed in "
            "the first optimisation stage, together with the computation that only fed it; no message "
            "reports it, the array simply has no memory row. The test is not a whole-program liveness: a "
            "store is deleted only once its array has no used load (that this is LLVM's dead-store and "
            "dead-global deletion is our interpretation of the behaviour, not observed directly), so a write-only array or "
            "one whose loaded values are unused disappears, but an array whose loads feed stores into "
            "itself (a histogram `t[x]++` never read otherwise) or into another array of such a cycle is "
            "kept. Arrays Vitis has already turned into registers do not keep a cycle alive, and an "
            "accumulator that LICM holds in a register leaves no load behind. There is no cross-loop "
            "dead-store elimination: a store loop followed by an overwriting store loop keeps both. A "
            "load right after a store of the same element is forwarded, so a flag that is only re-stored "
            "dies."),
        kernels=[("dg_d_apfixed16", "Q, K multiplied by a scale that folds to 0 (attention)", {}),
                 ("dg_d_apfixed4", "control: a scale that does not fold", {}),
                 ("w9r8p_dm_wo", "write-only array", {}),
                 ("w9r8p_dm_rd", "loads whose values are unused", {}),
                 ("w9r8p_dm_self", "`cnt[k] = cnt[k] + 1`, never read otherwise", {}),
                 ("w9r8i_dm_cyc2", "a cycle through two arrays", {}),
                 ("w9r8i_dm_acc0", "accumulator kept in a register by LICM", {}),
                 ("w9r8f_fw7", "a struct flag that is only re-stored", {})],
        evidence=["IR a.g.ld.5 vs a.o.1", "memory table"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--dead-memory-elimination", "--vitis-fold"],
        keys=["tool.hls.middle_end.dead_memory.load_store_cycles",
              "tool.hls.middle_end.dead_memory.overwritten_stores"],
        effect=("W9r8-impl 1-5", None)),
    dict(
        id="FE-5", stage="fe", title="Arrays written only by kept callees: the call form decides",
        notes=["N17", "N25"],
        statement=(
            "When an array is written only by a non-inlined callee and nothing reads it, Vitis deletes "
            "the call (and the array) if no live call of the same callee in the same argument form "
            "remains; otherwise the array stays at full cost as a `RAM_AUTO_0R0W` memory. This holds for "
            "locals and globals alike. A kept call whose only output is never read again is deleted "
            "together with the reads it made."),
        kernels=[("fbh3_g_callee_wr", "global written by a single-site callee", {}),
                 ("fbh3_g_callee_wr_shared", "the filler also fills a live array", {}),
                 ("w7_dl_local", "the same with a local array", {}),
                 ("fbrf_deadcall", "a call whose 1-element output is never read", {}),
                 ("fbrf_deadcall_shared", "the same with a shared filler", {})],
        evidence=["memory table (RAM_AUTO_0R0W rows)", "IR a.o.1 vs a.o.2 (call counts)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--dead-memory-elimination=dead-calls"],
        keys=["tool.hls.middle_end.dead_memory.dead_calls"],
        effect=("deletes a kept call whose written arrays", 'whole catalogue: exact')),
    dict(
        id="FE-6", stage="fe", title="Division by a constant zero: an undefined value folded per use",
        notes=["N13", "N1a"],
        statement=(
            "The first back-end transform turns an integer `sdiv`, `udiv` or `srem` by a constant 0 into "
            "an undefined value U and then folds it use by use, as LLVM's undef folds would (the "
            "behaviour per use is measured; that LLVM's folds produce it is our interpretation): a store of U is "
            "deleted, `x * U` and `sext U` become 0, `x + U` stays U, a compare of U is decided by "
            "`isTrueWhenEqual`. An unsigned `urem x, 0` is 0. Because the fixed-point operators "
            "sign-extend their operands first, every ap_fixed use sees `sext(U) = 0`: an ap_fixed `x / 0` "
            "behaves as 0. This is what deletes the Q and K arrays of the forgebench attention kernel "
            "(FE-4): the scale `1 / sqrt(16)` wraps to `1 / 0` in `ap_fixed<16,5>`."),
        kernels=[("dg_d_fold_steps", "the attention scale folded to 0", {}),
                 ("dg_d_fold_divrem0", "C int / and % by 0 per operator", {}),
                 ("dg_d_fold_divrem0b", "ap_fixed / by 0", {}),
                 ("t8_undef_cint", "37 output slots, one per use of U", {})],
        evidence=["IR a.o.1 (remaining stores)", "memory table"],
        status="confirmed (one narrowing order is not predictable from the source, N13)",
        hlsest="modelled (default)",
        mechanism=["--vitis-fold (undef rules)"],
        keys=["tool.hls.folding.rule_set"],
        effect=("undefined value of an integer x / 0", 'dg_d_fold_divrem0 12')),
    dict(
        id="FE-7", stage="fe", title="An array written only with one constant is a ROM; a ROM is as wide as its values",
        notes=["N26", "N52", "N1a"],
        statement=(
            "One store that is reached once and writes a constant (a full fill, a half or strided fill, "
            "or a filler callee called once) turns the array into a ROM of that constant; two fill loops, "
            "a conditional store or a folded constant leave a RAM. The ROM's element width comes from "
            "its values: with no negative value, the values are cut to the unsigned width A of the "
            "largest one and then read as signed numbers, and the width is the most signed bits any of "
            "them needs, so a fill of 6 (110b, read as -2) is narrower than a fill of 7 (see the "
            "table). An "
            "all-zero ROM disappears. The conversion happens at `a.o.1`, before the algebraic folds of "
            "FE-6, and the narrowing at `a.o.2`."),
        kernels=[("w7_rf9u", "fill with 300", {}),
                 ("w7_rf6", "fill with 6", {}),
                 ("w7_rf7", "fill with 7", {}),
                 ("w7_rf17u", "fill with 100000", {}),
                 ("w7_rfneg", "fill with -300", {}),
                 ("dg_c_const5", "512-word fill with 5", {}),
                 ("dg_c_const01", "two fill loops (0 then 1)", {}),
                 ("w7rv_cond0", "a conditional constant store", {}),
                 ("w7_rf_iota", "computed fill `buf[i] = i`", {})],
        evidence=["memory table (core ROM_AUTO_1R, Bits)", "IR a.o.1 (constant global), a.o.2 (narrowed type)"],
        status="confirmed",
        hlsest="modelled for constant fills (default); computed fills are not (OPEN_ISSUES O18)",
        mechanism=["--mark-constant-fills", "--bram-analysis"], keys=[],
        effect=("an array filled by one constant store is a ROM", 'whole catalogue: exact')),
    dict(
        id="FE-8", stage="fe", title="RAM element width: min(stored-value bits, demanded bits), decided after partitioning",
        notes=["N35", "N41"],
        statement=(
            "Between `a.o.1.ll` and `a.o.2.ll` Vitis narrows every local and global RAM to W = min(Wr, Wd). "
            "Wr is the bits of the union of the stored values' ranges (unsigned width when none is "
            "negative), with ranges propagated through masks, clamps, casts, loop counters, copies and "
            "callee parameters, but not around a cycle of arrays: a value loaded from the same array is "
            "full range. Wd is one plus the highest bit any load's users demand: an index into a table "
            "of N words demands ceil(log2 N) bits of the flattened address, a mask demands up to its "
            "highest set bit, a compare or an arithmetic use of the high bits demands everything. An "
            "ap_memory array argument demands the bits of its own address like a local; an m_axi pointer "
            "demands all bits. Partitioning comes first (every bank gets the array's width) and the "
            "LUTRAM test of ST-1 sees the narrowed width."),
        kernels=[("w9n_h1_t64", "values used only as an index into 64 words", {}),
                 ("w9n_h1_t4096", "index into 4096 words", {}),
                 ("w9n_h1_2dfirst", "index on the first dimension of [64][64]", {}),
                 ("w9n_h1_2dlast", "index on the last dimension", {}),
                 ("w9n_h3_relu", "ReLU outputs", {}),
                 ("w9n_h1_lut64", "64 words used as an index: narrowed below the LUTRAM threshold", {}),
                 ("w9i_self", "a stored value that depends on the array itself", {}),
                 ("w9i_noself", "control: the same values into another array", {}),
                 ("w9p5_idx_mem256", "index into an ap_memory argument of 256 words", {}),
                 ("w9p5_idx_maxi256", "the same argument on m_axi", {})],
        evidence=["memory table (Bits)", "IR a.o.1 vs a.o.2 (alloca element type)"],
        status="confirmed (ranges through loop-carried recurrences unconfirmed)",
        hlsest="modelled (default)",
        mechanism=["--narrow-ram-widths"],
        keys=["tool.hls.narrowing.stored_ranges", "tool.hls.narrowing.load_demand",
              "tool.hls.narrowing.full_address_interface_modes"],
        effect=("RAM element-width narrowing", 'compared 671')),
    dict(
        id="FE-9", stage="fe", title="Fold timing: scalar globals fold before the pipeline decision, small tables after it",
        notes=["N52"],
        statement=(
            "A never-written scalar global used as a loop bound is a constant before the automatic "
            "pipeline decision, so the loop it bounds is unrolled into its pipelined parent. A small "
            "never-written table whose elements all hold one value folds only after the decision: it is "
            "first partitioned into registers because of the pipeline pragma the decision set, and only "
            "then is its load a constant. A large uniform table (2913 elements) is never folded and "
            "stays a ROM."),
        kernels=[("rvsf_g1", "inner bound a scalar global `ksz = 16`", {"loops": ["VITIS"]}),
                 ("rvsf_rc16", "inner bound `cnt[sel & 1]` from `const int cnt[2] = {16, 16}`", {"loops": ["VITIS"]}),
                 ("rvsf_g3", "both k loops bounded by `ksz`", {}),
                 ("shafix_v3a", "`cnt = {256, 256}` as an outer bound", {"loops": ["VITIS"]}),
                 ("shafix_v3e", "2913-element table of one value", {})],
        evidence=["loop table", "log [HLS 214-421] (small array partitioned)", "memory table"],
        status="confirmed",
        hlsest="modelled: --vitis-fold folds one-element globals only",
        mechanism=["--vitis-fold"], keys=["tool.hls.folding.rule_set"],
        effect=("sha fix review fixes", 'exact 604')),
    dict(
        id="FE-10", stage="fe", title="Structs are disaggregated per leaf unless an AGGREGATE pragma reaches them",
        notes=["N29", "N37", "N81"],
        statement=(
            "A struct variable (local, global, an array of structs, a `std::array`) becomes one memory "
            "per scalar leaf, named `<var>_<member>`, each priced and narrowed on its own; an array member "
            "keeps its dimensions after the variable's. Exactly when an AGGREGATE pragma reaches the "
            "variable (on the variable, on a callee parameter that receives it, or through an hls::vector "
            "member function) it is one memory of prod(dims) x sum(leaf bits) words without padding, "
            "accessed one word at a time, so writing one leaf is a read-modify-write. An m_axi struct "
            "pointer is always aggregated at its C storage size. The elements of a global array of "
            "`std::array` are split into one memory each."),
        kernels=[("w8b3_st1", "`struct {int a; short b;} s[1024]`", {}),
                 ("w8b3_sp1", "2-D struct array and a struct with an array member", {}),
                 ("w9s_a", "AGGREGATE on variables and through hls::vector", {}),
                 ("w9s_b", "AGGREGATE on a callee parameter", {}),
                 ("w9r4rev_r4s_aggb", "AGGREGATE with a bool member (1 bit)", {}),
                 ("w9r9rev_e77_sarr", "global array of std::array<int,4>, complete dim 1", {})],
        evidence=["memory table (names, Words, Bits)", "log [HLS 214-241]", "IR a.o.3 (word loads)"],
        status="partly confirmed (the non-trivial hls::vector members other than operator[] are read from the header only)",
        hlsest="modelled (default); element access through a pointer GEP is not split (OPEN_ISSUES O108)",
        mechanism=["--split-struct-memrefs", "cgeist (AGGREGATE reaches the variable)"],
        keys=["tool.hls.structs.aggregate", "tool.hls.structs.through_calls", "tool.hls.structs.element_copy_loops"],
        effect=("struct-typed variables: one memory per leaf", 'full v2 catalogue compared 671')),
    dict(
        id="FE-11", stage="fe", title="An array of hls::vector is aggregated unless its elements are copied by value",
        notes=["N44", "N51", "N62"],
        statement=(
            "The real `hls_vector.h` runs `#pragma HLS AGGREGATE variable=this` in its member functions, "
            "so an array of `hls::vector<T, N>` is a memory of N x W-bit words. When an element is copied "
            "by value, which the binary operators of the header do with their left operand "
            "(`operator OP(vector lhs, const vector &rhs)`), the copy reads the array lane by lane at "
            "constant indices and Vitis completely partitions the lane dimension (`[HLS 214-270]`) "
            "before aggregation can apply. Swapping the operands of a product swaps which array is split. "
            "An `array_partition` on a single vector object (not an array of vectors) is ignored with "
            "`[HLS 214-253]`."),
        kernels=[("w11b_vec1", "`hls::vector<ap_fixed<16,5>,32> K[400][4]`, complete dim 2", {}),
                 ("w9r6_vx_var", "`(q[..] * k[..]).reduce_add()`", {}),
                 ("w9r7_vx_swap", "`(k[..] * q[..]).reduce_add()`", {}),
                 ("w9r7_vx_ref", "only reduce_add on references", {}),
                 ("w9r7_vx_copy", "an explicit copy `V t = q[..]`", {}),
                 ("w9r7fix_vp_local", "array_partition on a single vector", {})],
        evidence=["memory table (Words x Bits per bank)", "log [HLS 214-270]/[HLS 214-449]/[HLS 214-253]"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--split-struct-memrefs", "cgeist"],
        keys=["tool.hls.structs.element_copy_loops", "tool.hls.structs.temporary_registers"],
        effect=("W9r7-impl 2/10", None)),
    dict(
        id="FE-12", stage="fe", title="Arbitrary-precision corner cases differ between C simulation and synthesis",
        notes=["N10", "N11"],
        statement=(
            "Two semantic details of the Vitis headers matter for bit-exact front ends: `ap_int<W>` "
            "constructed from a double keeps only 25 signed bits of the integer part for "
            "2^24 <= |d| < 2^52 (the constructor shifts the mantissa into a 25-bit temporary), and "
            "fixed-point division differs between C simulation (which wraps the type's minimum divided "
            "by -1) and synthesis (which gives the exact quotient). Neither changes a memory; both are "
            "why the semantic check compares against synthesis behaviour, not against g++ alone."),
        kernels=[("rfx_d2k_dbl2int", "ap_int<32> from doubles around 2^24..2^52", {}),
                 ("rfx_divk_overflow", "ap_fixed<8,8>(-128) / -1", {})],
        evidence=["IR a.o.3 (stored constants)", "g++ with the real headers"],
        status="confirmed",
        hlsest="frontend: the real headers since W11 (the corner of N11 is a known category of check_shim.py)",
        mechanism=["cgeist --shim real"], keys=[], effect=None),
    # ------------------------------------------------------------------ functions
    dict(
        id="FN-1", stage="fn", title="Automatic inlining: size x calls <= 100, bottom up",
        notes=["N18", "N46", "N68"],
        statement=(
            "In its Unroll/Inline step Vitis visits the call graph bottom up and, for a caller C and a "
            "callee F without an inline pragma, inlines all calls of F in C if size(F) x calls(F in C) "
            "<= 100, otherwise none (`[HLS 214-178]`). size(F) is F's instruction count after user unroll "
            "pragmas and Vitis's own simplification, without integer casts, plus what was inlined into F "
            "first; calls are counted per caller after unrolling, and loops nested in a pipelined loop are "
            "unrolled before counting. A callee returning a pointer or reference is always inlined; "
            "`inline off`, dataflow processes and functions holding a dataflow region are always kept; "
            "always_inline callees and the ap class members are inlined before the count. The rule "
            "applies across translation units. A second, later inliner (`[XFORM 203-602]`) removes some "
            "small multi-call callees; its threshold is unconfirmed."),
        kernels=[("ai_sc_k1_n100", "one call of a 100-instruction callee", {"inst": True}),
                 ("ai_sc_k1_n101", "one call, 101 instructions", {"inst": True}),
                 ("ai_sc_k2_n50", "two calls, 50 instructions", {"inst": True}),
                 ("ai_sc_k2_n51", "two calls, 51 instructions (kept by 214-178, inlined later by 203-602)", {"inst": True}),
                 ("ai_m_ptrret_big", "a large callee returning a pointer", {"inst": True}),
                 ("ai_m_df_region", "small dataflow processes", {"inst": True}),
                 ("w9r8i_tu2", "a callee defined in another translation unit, 3 calls", {"inst": True})],
        evidence=["log [HLS 214-178]/[HLS 214-131]", "complexity dumps db/cmplx.3.*.json", "instance table"],
        status="confirmed (the proxy's and the corpus agreement are recorded in N18)",
        hlsest="frontend: cgeist --hls-auto-inline keeps the calls Vitis keeps",
        mechanism=["cgeist HLSAutoInline", "--inline"], keys=["tool.hls.inlining.honour_inline_off"],
        effect=None),
    dict(
        id="FN-2", stage="fn", title="A kept function's memories are paid once per instance; instances follow concurrency",
        notes=["N14", "N48", "N59"],
        statement=(
            "A non-inlined callee's local arrays are listed once in its module and counted once per "
            "instance. Within one parent, calls of the same function get one instance per call that can "
            "run at the same time: calls are ordered (and share an instance) by a scalar data dependence, "
            "by accessing a common array (read or write, local or port), by `allocation ... limit`, or by "
            "lying in exclusive branches; the instance count is the largest set of mutually concurrent "
            "calls. A callee called from two parents has one instance in each, so a module's multiplicity "
            "is the product down the instance tree. In a dataflow region every call site is its own "
            "process and instance, also the unrolled copies of a call loop; distinct constant elements "
            "of an array of streams are distinct objects and do not order calls."),
        kernels=[("inl_b2_twice_indep", "two calls on disjoint arrays", {"inst": True}),
                 ("inl_b1_twice_dep", "two calls through a common array", {"inst": True}),
                 ("w3r2_k5_branches", "calls in the two arms of an if", {"inst": True}),
                 ("w3r2_k6_join", "two concurrent calls, then a join", {"inst": True}),
                 ("inl_d1_two_parents", "one callee under two parents", {"inst": True}),
                 ("w9r6_dfi4", "one process function called 4 times in a dataflow chain", {"inst": True}),
                 ("w9r7_ci_s4", "4 unrolled calls on distinct stream elements", {"inst": True}),
                 ("w9r7_ci_s4seq", "control: the loop not unrolled", {"inst": True})],
        evidence=["instance table", "module latency (csynth.xml)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (CallInstances: groupConcurrentCalls)"],
        keys=["tool.hls.streams.distinct_element_instances"],
        effect=("in a dataflow region every call site is its own instance", None)),
    dict(
        id="FN-3", stage="fn", title="Clones and outlined loops multiply modules (trigger unconfirmed)",
        notes=["N14"],
        statement=(
            "Vitis clones a callee (`work.1`) when its call sites in one function pass different array "
            "argument forms (a row of a 2-D array against a whole array, or the first copy of an unrolled "
            "call loop against the rest), and outlines a caller loop that contains a call into a module "
            "`<fn>_Outline_<loop>` when the same function also calls a function outside any loop. Each "
            "clone or outlined loop is its own module with its own copy of the callee's arrays, even under "
            "`allocation ... limit=1`. The observations are confirmed; what triggers them in general is "
            "not."),
        kernels=[("inl_c5_unrolled_loop", "`work(in[k], out[k])` in an unrolled loop", {"inst": True}),
                 ("inl_c10_loop_two_sites", "row argument and whole-array argument", {"inst": True}),
                 ("inl_c8_loop_and_direct_limit1", "a call in a loop and a direct call, limit=1", {"inst": True})],
        evidence=["instance table", "IR a.o.1 (cloned function)", "[SYN 201-103] legalised names"],
        status="partly confirmed (observed; trigger unconfirmed)",
        hlsest="partly modelled: only the clone per row-argument form",
        mechanism=["--lower-polygeist-subindex"], keys=[], effect=None),
    dict(
        id="FN-4", stage="fn", title="Library math cores cost a fixed BRAM per instance",
        notes=["N16", "N45"],
        statement=(
            "Every (function, element type, argument form) of `hls::` / `std::` math is implemented by "
            "one core whose BRAM is the same in every context: IP operators (float exp, log, sqrt) cost "
            "none, library modules hold ROM tables (`pow_generic<float>`, `sin_or_cos<double>`). In a "
            "pipelined loop the instances are ceil(calls per iteration / achieved II); in sequential code "
            "one per concurrently runnable call, and unrolled copies in a sequential loop are bounded by "
            "the read ports of the memory their arguments come from. A constant base removes pow's log "
            "stage; all-constant calls fold. The CORDIC table of ap_fixed sin / cos vanishes only when a "
            "user pipeline pragma unrolls the CORDIC loop; under automatic pipelining that loop stays "
            "and the caller nest is flattened into it."),
        kernels=[("mc_v1_pow_f32_hls", "one powf call", {}),
                 ("mc_v4_powf_f32_hls", "4 calls per iteration at II 1", {"loops": ["VITIS"]}),
                 ("mc_v4ii4_powf_f32_hls", "4 calls per iteration at II 4", {"loops": ["VITIS"]}),
                 ("mc_v3n_sin_fx16_5_hls", "ap_fixed sin in a pipeline-off loop", {}),
                 ("mc_v3_sin_fx16_5_hls", "ap_fixed sin under a pipeline pragma", {}),
                 ("w2i_sin_auto128", "ap_fixed sin under automatic pipelining", {"loops": ["VITIS"]}),
                 ("w11rv_r3", "exp in a sequential loop unrolled by 3, unpartitioned input", {"inst": True})],
        evidence=["instance table (BRAM per core)", "memory table of the core module", "loop table"],
        status="confirmed (the inlining of cores into pipelined callers, R6, is unconfirmed)",
        hlsest="modelled (default) from the cost table math_costs.json",
        mechanism=["--bram-analysis math-costs=", "MathCores.cpp"],
        keys=["tool.hls.math_library.table", "scheduling.call_depth.ports_per_memory"],
        effect=None),
    dict(
        id="FN-5", stage="fn", title="Tables computed from the loop index are evaluated at compile time",
        notes=["N16", "N60"],
        statement=(
            "A loop that fills an array from its index and constants through math calls (a window of "
            "cosines, a twiddle table) is evaluated at compile time: the array becomes a ROM of the "
            "results and no math core is built. The exception is a local array of `std::complex`, whose "
            "constructor Vitis does not fold: it is computed at run time by a `sin_or_cos` core. A user "
            "struct of two floats, or a global `std::complex` table, is folded."),
        kernels=[("w2i_ivtab64", "`tab[i] = 0.54 - 0.46 cos(2 pi i / 63)`", {}),
                 ("w2i_ivdata64", "control: the cos combined with input data", {}),
                 ("w9r7i_mc_flt_loc", "local float table of cos", {}),
                 ("w9r7i_mc_cplx_loc", "local std::complex table", {}),
                 ("w9r7i_mc_cplx_glob", "global std::complex table", {}),
                 ("w9r7rev_mc_ustruct", "local table of a user struct", {})],
        evidence=["memory table (ROM rows)", "instance table (no math core)"],
        status="confirmed (why local std::complex is not folded is unknown)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (MathCores: onlyFillsArrays)"],
        keys=["tool.hls.math_library.local_struct_tables_at_run_time"],
        effect=("W9r7-impl 3/10", None)),
    # ------------------------------------------------------------------ loops
    dict(
        id="LP-1", stage="lp", title="Automatic pipelining: the 64-trip rule, top down, with flattening",
        notes=["N3"],
        statement=(
            "With `pipeline_loops` = 64 the decision works top down on the loop forest after collapsing "
            "perfect nests: a loop is pipelined iff every loop nested in it (also in kept callees) has a "
            "constant trip count and every nesting path inside it has a trip-count product <= 64; "
            "everything inside is then completely unrolled (`[HLS 214-291]`). A loop without inner loops "
            "is always pipelined, never unrolled on its own. If the test fails, the decision recurses into "
            "the children; a non-pipelined parent with exactly one pipelined child and constant bounds is "
            "made perfect and flattened into it (`[HLS 200-2061]`, `[XFORM 203-541]`). The trip count, not "
            "the bound, counts, 64 is included, and nothing else (body size, data-dependent exits, float "
            "chains) gates the unroll. `pipeline_loops=0` disables all of it."),
        kernels=[("pu_red_m8_n16", "8 x 16 reduction nest", {"loops": ["VITIS_LOOP_10"]}),
                 ("pu_red_m8_n64", "inner trip 64 (included)", {"loops": ["VITIS_LOOP_10"]}),
                 ("pu_red_m8_n65", "inner trip 65", {"loops": ["VITIS_LOOP_10"]}),
                 ("pu_st_m64_n64", "perfect 64 x 64 nest", {"loops": ["VITIS_LOOP_10"]}),
                 ("pu_sib_m8_n16_n65", "siblings of 16 and 65 trips", {}),
                 ("pu_cfg_pl0_red_m8_n16", "pipeline_loops = 0", {})],
        evidence=["log [HLS 214-376]/[HLS 214-291]/[HLS 214-186]/[XFORM 203-541]", "loop table"],
        status="confirmed",
        hlsest="modelled (default); decisions equal Vitis on the pipeline-unroll kernels (check_pipeline_unroll.py)",
        mechanism=["--auto-pipeline-unroll"],
        keys=["tool.hls.options.pipeline_loops", "tool.hls.pipeline_decision.policy"],
        effect=("Vitis automatic pipeline/unroll/flatten decision", 'Without `--infer-vitis-split-array`: exact 34/74')),
    dict(
        id="LP-2", stage="lp", title="Perfectness depends on the element type of an invariant load",
        notes=["N3"],
        statement=(
            "Whether a nest counts as perfect is judged after loop-invariant code motion: an inner-"
            "invariant load of an integer element makes the nest imperfect (the inner loop is unrolled "
            "into the pipelined outer loop), the same load of a floating-point element does not (the nest "
            "is converted into a perfect nest and flattened). It is the loaded element's type that "
            "decides, not the arithmetic. The mechanism is unknown: `a.o.1.ll` shows the load hoisted in "
            "both cases. Polybench atax and bicg are flattened for this reason."),
        kernels=[("rv_rmw_hoist_f_m8_n64", "float `lo[i][j] += la[i][j] * lb[i]`", {"loops": ["VITIS_LOOP_4", "VITIS_LOOP_12"]}),
                 ("rv_rmw_hoist_m8_n64", "the int twin", {"loops": ["VITIS_LOOP_4", "VITIS_LOOP_12"]}),
                 ("rv_rmw_hoist_f_m64_n64", "float, 64 x 64", {}),
                 ("rv_rmw_hoist_m64_n64", "int, 64 x 64", {})],
        evidence=["log [HLS 200-2061]/[XFORM 203-541] vs [HLS 214-186]", "loop table", "memory table"],
        status="confirmed (rule); mechanism unknown",
        hlsest="modelled (default)",
        mechanism=["--auto-pipeline-unroll"], keys=["tool.hls.pipeline_decision.float_loads_perfect"],
        effect=None),
    dict(
        id="LP-3", stage="lp", title="User unroll pragmas: partial factors block, factors inside a pipeline are overridden",
        notes=["N3", "N43"],
        statement=(
            "A user `unroll` is applied before the decision. A loop that keeps a partial unroll (a factor "
            "below its trip count, `factor=1` included) is never completely unrolled for an enclosing "
            "automatic pipeline: it is pipelined itself and no loop around it is auto-pipelined. Inside a "
            "loop that is pipelined (by pragma or automatically), however, a partial factor is overridden "
            "by the complete unroll the pipeline implies (`[HLS 214-291]`)."),
        kernels=[("w9p5_acp_part8", "`unroll factor=8` inside a pipelined loop", {"loops": ["comp"]}),
                 ("w9p5_acp_n64", "control: the same without the factor", {"loops": ["comp"]})],
        evidence=["log [HLS 214-291]", "loop table", "corpus loop tables (forgebench diff_dims_p1, spector fir)"],
        status="confirmed",
        hlsest="modelled (the override inside a pipeline is not: OPEN_ISSUES O61)",
        mechanism=["--auto-pipeline-unroll"], keys=[], effect=None),
    dict(
        id="LP-4", stage="lp", title="`inline off` stops flattening; a kept callee's loops count in the 64-trip test",
        notes=["N14"],
        statement=(
            "A caller loop around a kept call is auto-pipelined when the callee's loop nest has at most "
            "64 trips in total; the callee's loops are then unrolled inside the callee and the caller's "
            "II is the callee's port occupancy (two accesses per cycle of its busiest memory). Otherwise "
            "the callee's loops are pipelined in the callee and the caller loop stays sequential: "
            "flattening never crosses the call boundary."),
        kernels=[("inl_f1_flat_off", "caller 8-trip loop around a kept 128-trip loop", {}),
                 ("inl_f1_flat_on", "the same inlined", {}),
                 ("w3h_cb_flat64", "kept callee with a 64-trip loop", {}),
                 ("w3h_cb_nest256", "kept callee nest of 256 trips", {"loops": ["VITIS"]})],
        evidence=["loop table", "log [HLS 214-186] in function <callee>"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--auto-pipeline-unroll", "--convert-affine-to-loopschedule (call occupancy)"],
        keys=["tool.hls.pipeline_decision.flatten_across_calls"],
        effect=None),
    dict(
        id="LP-5", stage="lp", title="A narrow counter against a wider run-time bound is not collapsed with its nest",
        notes=["N15"],
        statement=(
            "`for (uint8_t i = 0; i < n; i++)` with `int n` is pipelined like an `int` loop, but it is "
            "not collapsed with its perfect inner nest before the decision: its exit test compares the "
            "zero-extended counter with the bound and has no computable trip count, so it is treated as "
            "the outer loop of an imperfect nest; its small inner loop is unrolled and the reads per "
            "iteration multiply. Counters whose range Vitis can bound behave like `int`."),
        kernels=[("nc_q_u8", "uint8_t counter, int bound, 16-trip perfect inner loop", {}),
                 ("nc_q_int", "control: int counter", {}),
                 ("nc_r_u8", "uint8_t counter, partitioned store target", {}),
                 ("nc_r_int_pp", "int counter with a pipeline pragma on the outer loop", {})],
        evidence=["loop table (trip ?)", "IR a.o.1 (exit compare)", "log [HLS 214-291]"],
        status="confirmed (mechanism unconfirmed)",
        hlsest="frontend + modelled: cgeist marks such loops `hls.uncounted`; --auto-pipeline-unroll does not collapse them",
        mechanism=["cgeist CanonicalizeFor", "--auto-pipeline-unroll"], keys=[],
        effect=("narrow-counter loops against runtime bounds", 'the MLIR of all 112 designs')),
    dict(
        id="LP-6", stage="lp", title="Loops of unknown trip count are pipeline candidates like any other",
        notes=["N53"],
        statement=(
            "A loop whose trip count is unknown (a bound loaded inside an enclosing loop, a data-"
            "dependent `while`) is auto-pipelined under the same test: every loop inside it must have a "
            "constant trip count with products <= 64; its own trip count does not matter. A variable-"
            "bound loop whose body is a perfect constant-trip nest is flattened into that nest's pipeline "
            "instead, and a `while` with a constant exit test is a counted loop. An array that becomes "
            "constant-indexed only through such an implied unroll stays a memory when it lives in the "
            "function of the pipelined loop (mechanism unconfirmed, OPEN_ISSUES O73)."),
        kernels=[("o72_fa", "runtime-bound i loop around a 16-trip k loop", {"loops": ["VITIS_LOOP_8"]}),
                 ("o72_fb", "runtime-bound i loop around a 128-trip k loop", {"loops": ["VITIS_LOOP_8"]}),
                 ("o72_wa", "data-dependent while", {"loops": ["VITIS_LOOP_7"]}),
                 ("o72r_pf3", "variable bound around a perfect 4 x 4 nest", {}),
                 ("o72r_cdw", "`while (i--)` from 16", {}),
                 ("o72_xii", "SHA transform inlined in a pipelined while", {})],
        evidence=["loop table (trip ? or ranges)", "log [HLS 214-376]/[HLS 214-291]"],
        status="partly confirmed (O73 mechanism unconfirmed)",
        hlsest="modelled; the exit-test recurrence of a pipelined while is not (o72_wa)",
        mechanism=["--auto-pipeline-unroll", "--vitis-fold (constant-trip while)"], keys=[],
        effect=("O72: loops with a runtime trip count", None)),
    dict(
        id="LP-7", stage="lp", title="A pipeline pragma on a trip-1 loop unrolls its inner loops and then disappears",
        notes=["N40"],
        statement=(
            "A `pipeline` pragma on a loop whose trip count is 1 first unrolls the loops nested in it, as "
            "any pipeline pragma does; then the trip-1 loop is removed together with its pipeline and "
            "flatten pragmas, and the automatic decision runs on what is left. Here that pipelines the "
            "parent at a target II of NA with hundreds of unrolled reads per iteration."),
        kernels=[("w9p5_t1_flat", "trip-1 loop with pipeline + loop_flatten", {"loops": ["l72"]}),
                 ("w9p5_t2_flat", "control: trip 2", {"loops": ["l72"]}),
                 ("w9p5_t1_l74", "control: the pragma one level up", {"loops": ["l72"]})],
        evidence=["log [HLS 214-291]/[HLS 214-376] (Target II = NA)", "loop table", "memory table"],
        status="confirmed",
        hlsest="frontend, opt-in: cgeist --hls-trip-one-pipeline-unroll (off by default, OPEN_ISSUES O57)",
        mechanism=["cgeist HLSPragmaSema"], keys=[],
        effect=("W9r5-impl 4/4", None)),
    dict(
        id="LP-8", stage="lp", title="Invariant inner loops are not hoisted before the decision",
        notes=["N14"],
        statement=(
            "Vitis does not hoist an inner loop whose bounds and body are invariant in the enclosing loop "
            "before it decides; the invariant loop is unrolled or flattened where it stands. (Clang-based "
            "front ends at every -O level do hoist it, which changes the structure the decision sees.)"),
        kernels=[("inl_o5_f8", "invariant 8-trip loop in a 64 x 64 nest (float)", {"loops": ["lp1"]}),
                 ("inl_o5_i100", "the same with 100 trips (int)", {"loops": ["lp1"]})],
        evidence=["log [HLS 200-2061]/[XFORM 203-541]", "loop table", "log [HLS 200-2167]"],
        status="confirmed",
        hlsest="frontend, opt-in: cgeist --hls-keep-invariant-loops, which the harness does not pass (OPEN_ISSUES O5)",
        mechanism=["cgeist"], keys=[], effect=None),
    dict(
        id="LP-9", stage="lp", title="A stream read or write around one inner pipeline does not stop flattening",
        notes=["N55"],
        statement=(
            "In the perfectness test, a single stream read before one inner pipelined loop, whose value is "
            "used only inside it, and a single stream write after it of a value the loop finished, do not "
            "make the nest imperfect: Vitis guards them with first- and last-iteration predicates and "
            "flattens the nest. A loop in the tail does make it imperfect."),
        kernels=[("w9r7_sf_tail", "one `out.write(tmp)` after the inner loop", {"loops": ["VITIS"]}),
                 ("w9r7_sf_tailloop", "control: a loop of writes in the tail", {"loops": ["VITIS"]}),
                 ("w9r7_sf_head", "one `in.read()` before the inner loop", {"loops": ["VITIS"]})],
        evidence=["loop table", "log (perfect_nest message)"],
        status="confirmed",
        hlsest="not modelled (OPEN_ISSUES O77 (b); needs the stream timing of SC-5)",
        mechanism=[], keys=[], effect=None),
    dict(
        id="LP-10", stage="lp", title="Some parents are not flattened with an automatically pipelined child",
        notes=["N64", "N76"],
        statement=(
            "Vitis sometimes refuses to flatten a parent with its automatically pipelined child, logging "
            "`[HLS 200-960] Cannot flatten loop ... do-while loop`; the child then runs alone and its "
            "invariant loads are hoisted out of the pipeline. In every refused kernel `a.o.1.ll` shows "
            "the parent in rotated (do-while) form, its increment taken from a hoisted `l + 1`. Explicit "
            "pragmas avoid it, and so do some guards inside the unrolled loop. A candidate rule (child "
            "pipelined only by `pipeline_loops`, a sub-loop only that pipeline unrolls, no branch on the "
            "child's or sub-loop's index) agrees with every kernel but is unconfirmed."),
        kernels=[("w9r8p_ie_acc", "ECG conv1d nest, accumulation in both arms of an if", {"loops": ["VITIS"]}),
                 ("w9r8p_dw_noif", "the same without the if", {"loops": ["VITIS"]}),
                 ("w9r8p_dw_ifc", "if on `(c + k) & 1`", {"loops": ["VITIS"]}),
                 ("w9r9p_n64_cpipe", "explicit `pipeline II=1` on c", {"loops": ["VITIS"]}),
                 ("w9r9p_n64_iflonly", "guard on `(l + k) & 1`", {"loops": ["VITIS"]}),
                 ("w9r9p_n64_ifkonly", "guard on `k & 1`", {"loops": ["VITIS"]})],
        evidence=["log [HLS 200-960]/[HLS 200-2061]", "IR a.o.1 (loop rotation)", "loop table"],
        status="unconfirmed (trigger); the observations are confirmed",
        hlsest="not modelled: hls-est always flattens",
        mechanism=[], keys=[], effect=None),
    dict(
        id="LP-11", stage="lp", title="Code sunk into a flattened pipeline counts in its port demand",
        notes=["N65"],
        statement=(
            "When a non-pipelined parent is made perfect and flattened with its child (LP-1), the "
            "parent's straight-line code before the child moves into the pipelined body under a "
            "first-iteration guard, and its memory accesses are allocated ports in every iteration."),
        kernels=[("w9r8p_fl_pre", "64 reads of Bl before a partially unrolled child", {"loops": ["VITIS"]}),
                 ("w9r8p_fl_pre2", "the same, child not unrolled", {"loops": ["VITIS"]})],
        evidence=["loop table", "memory table (RAM_1WNR copies)"],
        status="confirmed",
        hlsest="modelled (default); the II of fl_pre differs (OPEN_ISSUES O87)",
        mechanism=["--convert-affine-to-loopschedule (sink-flattened-parent-code)"],
        keys=["tool.hls.pipeline_decision.sink_parent_code"],
        effect=None),
    # ------------------------------------------------------------------ partitioning
    dict(
        id="PA-1", stage="pa", title="Partition and reshape pragmas: banks, words and what stays a memory",
        notes=["N7", "N21"],
        statement=(
            "`array_partition cyclic|block factor=F dim=d` gives exactly F banks of ceil(N_d / F) x (the "
            "other dimensions) words, priced each by the formula; cyclic and block cost the same. "
            "`complete` on one dimension of a multi-dimensional array gives N_d memory banks (BRAM, not "
            "registers); only `complete dim=0`, or `complete` on a 1-D array, turns the array into "
            "registers. `array_reshape factor=F` gives one memory of N/F words x F*W bits. A factor "
            "larger than the dimension is a complete partition of it, without a message."),
        kernels=[("part_p1d_cyc4", "1-D, cyclic 4", {}),
                 ("part_p1d_comp", "1-D, complete", {}),
                 ("part_p2d_comp_d1", "64 x 64, complete dim 1", {}),
                 ("part_p2d_comp_d0", "64 x 64, complete dim 0", {}),
                 ("part_p1d_resh_cyc4", "1-D, reshape cyclic 4", {}),
                 ("part_p2d_resh_comp_d2", "64 x 64, reshape complete dim 2", {}),
                 ("w8b_factor_cyclic16_dim4", "cyclic 16 on a dimension of 4", {})],
        evidence=["memory table (banks)", "log [HLS 214-248]"],
        status="confirmed",
        hlsest="modelled (default); `complete dim=0` is still banked on dim 1 in hls-est",
        mechanism=["--memory-banking-bram"], keys=["tool.hls.partitioning.policy"], effect=None),
    dict(
        id="PA-2", stage="pa", title="How pragmas combine and which arrays they reach",
        notes=["N17", "N24", "N28", "N47", "N69"],
        statement=(
            "Pragmas on different dimensions combine; `dim=0` partitions every dimension. Two pragmas of "
            "the same type on one dimension keep the larger factor in either order, `complete` beats "
            "cyclic or block, and cyclic against block is an error (`[HLS 214-290]`); no message names a "
            "dropped pragma. A callee parameter's pragma partitions the arrays passed to that parameter, "
            "transitively and also through inlined callees, with the dimension shifted by the subscripts "
            "of a row argument, except that a single-row array is not split; the callee is cloned per "
            "argument partition. The conditional operator on lvalues and a static local reached only in a "
            "kept callee do not stop a pragma."),
        kernels=[("w7_p2d", "cyclic 4 dim 1 + cyclic 8 dim 2", {}),
                 ("w7_dim0c", "cyclic 2 dim 0 on [8][64]", {}),
                 ("w10k_loc_cyc2_cyc4", "cyclic 2 then cyclic 4", {}),
                 ("w10k_cyc4_cpl", "cyclic 4 then complete", {}),
                 ("w10k_cyc2_blk4", "cyclic 2 then block 4", {}),
                 ("w7_prop_conflict", "array cyclic 2, parameter cyclic 4", {}),
                 ("fbh1_prop_row_var", "parameter pragma, row argument `f(A[k])`", {}),
                 ("w7_prop_row1", "row argument of a [1][1024] array", {}),
                 ("w9r8i_sel1", "`(j == 0) ? B[i][j] : loc[i][j - 1]`", {})],
        evidence=["log [HLS 214-248]/[HLS 214-290]", "memory table"],
        status="confirmed (pragmas on one global in two functions, and reshape conflicts, unconfirmed)",
        hlsest="modelled (default): merging in cgeist, propagation and cloning in --memory-banking-bram",
        mechanism=["cgeist HLSPragmaSema (mergePartition)", "--memory-banking-bram (PartitionLayout)",
                   "--lower-polygeist-subindex"],
        keys=[], effect=("`--memory-banking-bram` partitions the way Vitis does", 'whole catalogue (95 compared)')),
    dict(
        id="PA-3", stage="pa", title="Automatic partitions that remain under throughput_driven=off",
        notes=["N2", "N7", "N43", "N61", "N57", "N77"],
        statement=(
            "With `throughput_driven=off` (the ground-truth setting) Vitis no longer partitions for port "
            "pressure, but three automatic partitions remain: (a) an array of at most 4 elements becomes "
            "registers (`[HLS 214-421]`), globals and statics included; (b) a dimension of 2..64 "
            "elements whose every access is a constant index after unrolling is completely partitioned "
            "(`[HLS 214-449]`, `[HLS 214-270]`), also after a user cyclic or block partition (then per "
            "part), also for statics, whatever the other indices are; a larger dimension stays whole; "
            "(c) an array accessed only at constant indices is scalarised. A 1-D array written at a "
            "variable index and read only at constants is not partitioned, and the reading loop becomes "
            "port-bound instead."),
        kernels=[("part_small_w32_n4", "4-element array", {}),
                 ("w9rv_r1_glob4", "a global and a static of 4 elements", {}),
                 ("w9p5_acp_gs_base", "gesummv as C++ (dim 2 constant after the unroll)", {}),
                 ("w9p5_acp_gs_fillpipe", "the same with a pipelined fill (variable index)", {}),
                 ("w9p5_acp_n64", "1-D, variable write, 64 constant reads", {"loops": ["comp"]}),
                 ("w9r7_ap_cyc", "user cyclic 4, dim 2 constant after the unroll", {}),
                 ("w9r7fix_ap_e65", "constant-index dimension of 65", {}),
                 ("w9r7fix_ap_e64r256", "constant-index dimension of 64", {}),
                 ("w9r9p_o79_static", "a static local", {})],
        evidence=["log [HLS 214-421]/[HLS 214-449]/[HLS 214-270]", "memory table"],
        status="confirmed (the 64-element limit's origin is unknown; rule (c) beyond 64 untested)",
        hlsest="modelled (default)",
        mechanism=["--infer-vitis-split-array=td=off"],
        keys=["tool.hls.options.array_partition.throughput_driven",
              "tool.hls.options.array_partition.complete_threshold",
              "tool.hls.partitioning.constant_index.max_extent",
              "tool.hls.partitioning.constant_index.after_user_partition",
              "tool.hls.partitioning.constant_index.globals"],
        effect=("W9r5-impl 1/4", None)),
    dict(
        id="PA-4", stage="pa", title="Run-time indexed reads of a partitioned array find their bank by residue class",
        notes=["N27", "N74", "N86"],
        statement=(
            "Unrolled reads `A[base + c_k]` of a cyclically partitioned dimension, with a run-time base "
            "and constant offsets, are steered: each bank is read once per offset in its residue class, "
            "so a bank sees max over residues r of #{k : c_k = r mod F} reads per iteration, multiplied "
            "over the partitioned dimensions; a 3 x 3 window over a factor-3 partition reads every bank "
            "once and needs no copies, while over factor 2 each bank is read four times. A block-"
            "partitioned access whose index stays in one block over the loop's iteration range has one "
            "bank."),
        kernels=[("w7rv_rt4", "4 unrolled reads at base + 0..3, cyclic 4", {}),
                 ("w9r9p_o92_f3_w3x3", "3 x 3 window, cyclic 3 on both dimensions", {}),
                 ("w9r9p_o92_f2_w3x3", "3 x 3 window, cyclic 2", {}),
                 ("w9r9p_o92_f3_w9x1", "9 x 1 window, cyclic 3 (3 per class)", {}),
                 ("w9r9p_o92_f3_w3x1s3", "rows i, i+3, i+6 (one class)", {}),
                 ("w9r10fx_fx_blk2", "block 3, stores `buf[i + 64k]` in a 64-trip loop", {})],
        evidence=["memory table (per-bank core and BRAM)", "bind report (sparsemux per bank)"],
        status="confirmed (stores are not steered; the II > 1 behaviour is ST-8)",
        hlsest="modelled (default) for reads; masked block indices are not (OPEN_ISSUES O116)",
        mechanism=["--memory-banking-bram (steerLoadGroups, residueClassGroups, constantBankThroughRanges)"],
        keys=["tool.hls.partitioning.steer_window_groups", "tool.hls.partitioning.steer_affine_loads",
              "tool.hls.partitioning.block_bank_from_loop_range"],
        effect=("W9r9-impl", None)),
    dict(
        id="PA-5", stage="pa", title="Partition banks can be merged back after a.o.3 (corpus only)",
        notes=["N9"],
        statement=(
            "For a few corpus arrays with several allocas at `a.o.3.ll` the scheduler's report shows a "
            "single memory: the banks of machsuite fft_transpose `DATA_x` and of polybench k3mm's arrays "
            "are merged back before binding. No `[HLS 214-*]` message names them, and no standalone "
            "kernel reproduces it, so the bank count read from the IR is not the physical one in these "
            "cases. The mechanism is unconfirmed."),
        kernels=[],
        evidence=["IR a.o.3 vs db/<module>.verbose.rpt", "memory table", "RTL"],
        status="unconfirmed (corpus observation, no kernel)",
        hlsest="not modelled",
        mechanism=[], keys=[], effect=None),
    # ------------------------------------------------------------------ storage
    dict(
        id="ST-1", stage="st", title="LUTRAM below 1024 bits, BRAM from 1024 bits on",
        notes=["N5"],
        statement=(
            "A RAM of Words x Bits < 1024 (exact element width, after narrowing) is distributed RAM and "
            "costs no BRAM; 1024 bits and more is BRAM. The threshold is inclusive and depth alone does "
            "not decide (128 x 4 is LUTRAM). Library ROMs that the headers bind to LUTRAM cost none at "
            "any size."),
        kernels=[("lutram_d64_w16", "64 x 16 = 1024 bits", {}),
                 ("lutram_chk_d64_w15", "64 x 15 = 960 bits", {}),
                 ("lutram_chk_d93_w11", "93 x 11 = 1023 bits", {}),
                 ("lutram_d16_w64", "16 x 64", {}),
                 ("lutram_chk_d128_w4", "128 x 4", {})],
        evidence=["memory table (BRAM_18K, LUT)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (storage selector)"],
        keys=["tool.backend.storage_selector.min_block_bits", "tool.backend.storage_selector.inclusive"],
        effect=None),
    dict(
        id="ST-2", stage="st", title="Two accesses in one cycle or state make a two-port RAM",
        notes=["N7", "N12"],
        statement=(
            "A bank whose accesses never share a cycle is single-port (and may use the x36 mode, BF-1). "
            "Two accesses in one cycle of a pipeline, or in one state of a sequential region, bind "
            "`ram_2p` (two reads, or a read and a write) or `ram_t2p` (two writes), with the x18 "
            "ceiling: an in-place update `acc[i] += ...` in a pipelined loop doubles a 64 x 32 array. In "
            "a sequential region at most two accesses share a state and nothing is replicated; two "
            "accesses share a state when they lie in one basic block (if-arms are predicated in, but the "
            "two arms of one if share a port) and neither depends on the other through SSA or memory "
            "order. Exceptions arise where Vitis's list schedule has slack around an outlined loop call; "
            "their criterion is unconfirmed."),
        kernels=[("t6_sp_8ld", "8 independent loads in a sequential body", {}),
                 ("t6_sp_2st", "two independent stores", {}),
                 ("t6_sp_ifarms", "one load in each arm of an if", {}),
                 ("t6_sp_dd", "`a[a[i] & 63]`: dependent loads", {}),
                 ("t6_sp_sib", "loads in two sibling `pipeline off` loops", {}),
                 ("part_rmw_w32_d64", "in-place update in a pipelined loop", {})],
        evidence=["schedule reports db/<module>.verbose.sched.rpt", "bind optype", "memory table"],
        status="partly confirmed (exceptions with slack unconfirmed, OPEN_ISSUES O21)",
        hlsest="modelled (default) as a per-stretch rule",
        mechanism=["--bram-analysis (sequential scopes)"],
        keys=["tool.hls.memory_architecture.sequential_scope.model"],
        effect=None),
    dict(
        id="ST-3", stage="st", title="RAM_1WNR replication: copies = ceil((R+W)/II) - 1, at most 16",
        notes=["N4", "N38", "N9"],
        statement=(
            "For a bank read R times and written W times per iteration of a pipelined loop (after "
            "unrolling, load merging and invariant hoisting), Vitis builds a `RAM_1WNR` of "
            "min(16, ceil((R+W)/II) - 1) copies when that exceeds a plain two-port RAM, where II is the "
            "final II of the loop that reads the bank; every copy is written through the shared port, "
            "so up to 17 reads per cycle are served and the loop's II is ceil((R+W)/17) when nothing else "
            "limits it. If any loop body stores the bank more than once, there is no replication: the "
            "bank stays a two-port RAM and the reading loop's II becomes ceil(R/2). A copy is priced at "
            "the x18 ceiling, and replication applies per partition bank. There is no BRAM budget."),
        kernels=[("w9r_b0", "8 reads per iteration at II 1", {"loops": ["rd"]}),
                 ("pu_red_m8_n16", "16 reads per iteration", {"loops": ["VITIS_LOOP_10"]}),
                 ("rep_inv_R16", "16 reads", {}),
                 ("rep_inv_R17", "17 reads (the cap)", {}),
                 ("rep_inv_R18", "18 reads", {}),
                 ("rep_wr2_R08", "two stores per iteration", {}),
                 ("fu_part_rep", "cyclic 2, 8 reads per iteration", {})],
        evidence=["log [HLS 200-2167] (copies)/[HLS 200-1457]", "memory table (RAM_1WNR)", "loop table", "RTL (ram0..ramK)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--memory-banking-bram (classification)", "--convert-affine-to-loopschedule (17 slots)",
                   "--bram-analysis"],
        keys=["tool.hls.memory_architecture.replication.max_copies",
              "tool.hls.memory_architecture.replication.max_stores_per_iteration",
              "tool.hls.memory_architecture.replication.shared_write_port_reads_when_idle"],
        effect=("Vitis storage model", 'Canonical pipeline: exact 31/73')),
    dict(
        id="ST-4", stage="st", title="What counts as a store: exclusive arms once, ap_fixed compound assignments twice",
        notes=["N38"],
        statement=(
            "Stores in the two arms of one if count once for replicability, whatever their addresses, and "
            "same-address loads and stores repeated in one iteration, also across if/else arms, become one "
            "load and one store. In the other direction, an ap_fixed compound assignment (`/=`, `*=`, `+=`, "
            "`-=`, `++`) to an element whose bank is chosen at run time leaves two stores per bank: the "
            "cross-format `operator=` stores 0 first and Vitis's dead-store elimination does not remove "
            "it across the per-bank switch. That second store forbids replication and halves the "
            "loop's port budget."),
        kernels=[("w9r_e1ifelse", "`if (in > 0) A[i] = in; else A[i] = 0;`", {}),
                 ("w9r4rev_r4r_ifn", "exclusive stores to different addresses", {}),
                 ("w9r_d1div", "ap_fixed `/=` on a partitioned array, variable bank", {"loops": ["VITIS", "md", "rd"]}),
                 ("w9r_d4asg", "control: plain assignment", {}),
                 ("w9r7rev_rc_inc", "ap_fixed `++`", {}),
                 ("w9r7rev_rc_or", "control: `|=` (not a compound arithmetic operator)", {})],
        evidence=["schedule report (store i16 0 per bank)", "memory table", "loop table"],
        status="confirmed",
        hlsest="modelled (default); cgeist marks compound-assignment stores",
        mechanism=["--convert-affine-to-loopschedule (merge-if-else-accesses)", "--memory-banking-bram"],
        keys=["tool.hls.middle_end.merge_if_else_accesses",
              "tool.hls.memory_architecture.replication.exclusive_arm_stores_once",
              "tool.hls.partitioning.compound_assign_two_stores"],
        effect=("W9r7-impl 1/10", None)),
    dict(
        id="ST-5", stage="st", title="What counts as a read: hoisting, GVN and registers",
        notes=["N4", "N38", "N42", "N70", "N71", "N73"],
        statement=(
            "Loop-invariant loads are hoisted out of the pipelined loop (not counted) when the array is "
            "not stored in that loop and the nest is not flattened, also when they sit under a condition "
            "or an early break. Loads of one address in non-exclusive ifs of one iteration are one read "
            "(consistent with LLVM's GVN load PRE; our interpretation) unless a store intervenes; `c ? A[i] : A[j]` on lvalues of one array is "
            "one read at a selected address. A scalar running value (`m = a[..]; if (a[..] > m) m = ...`) "
            "is a register and carries no memory recurrence."),
        kernels=[("w9r_b9condinv", "32 invariant loads under a break", {}),
                 ("w9r8f_pr1", "same address in two non-exclusive ifs", {}),
                 ("w9r8f_pr2", "control: different addresses", {}),
                 ("w9r8f_pr3", "control: a store between the ifs", {}),
                 ("w9r8rev_c1", "`c ? A[i] : A[j]` twice per iteration", {}),
                 ("w9p5_mp", "2 x 2 max pool with a running max", {"loops": ["VITIS"]})],
        evidence=["IR a.o.3 (scalar arguments of the pipeline)", "memory table", "loop table"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--convert-affine-to-loopschedule (hoist, load CSE, mergeConditionalLoads)",
                   "--lower-polygeist-subindex (mergeSameArrayViewConditional)"],
        keys=["tool.hls.middle_end.licm_hoist_invariant_loads", "tool.hls.middle_end.licm_hoist_conditional",
              "tool.hls.middle_end.gvn_conditional_loads", "tool.hls.middle_end.gvn_loads"],
        effect=None),
    dict(
        id="ST-6", stage="st", title="Port-bound arrays are never replicated",
        notes=["N14", "N38", "N75", "N85", "N33"],
        statement=(
            "Some arrays keep two ports whatever their read count, and the reading loop's II rises "
            "instead: an array read inside a callee module that is instantiated at more than one place, "
            "an array bound to a callee parameter that receives different arrays at different call sites "
            "(then in every callee that reads it), a writable file-scope global or `static` array, and "
            "every dataflow ping-pong channel. A local of the top read in a kept callee through a "
            "parameter is replicated as if the loop were inlined, and constant tables are ROMs with their "
            "own port rule (BF-2)."),
        kernels=[("w9r_b5callrd", "single-call callee reading the array", {}),
                 ("w9r_b8shared", "one callee called with two arrays", {}),
                 ("w9r9p_rs_same_arr", "two calls with the same array", {}),
                 ("w9r9rev_e75_mixed", "one array bound with another, then read alone in a second callee", {}),
                 ("w9r10p_gp_glob_top", "file-scope global read 16 times per iteration", {"loops": ["VITIS"]}),
                 ("w9r10p_gp_static_top", "static local, same reads", {}),
                 ("w9r10p_gp_loc_param", "local of the top read in a kept callee", {"loops": ["VITIS"]})],
        evidence=["memory table (RAM_AUTO_1R1W vs RAM_1WNR)", "loop table (II)", "log [HLS 200-885]"],
        status="confirmed (direct accesses in the owner of an array bound with another are untested)",
        hlsest="modelled (default)",
        mechanism=["--auto-pipeline-unroll (markPortBoundArgs)", "--bram-analysis (CallInstances)"],
        keys=["tool.hls.memory_architecture.replication.port_bound_several_arrays",
              "tool.hls.memory_architecture.replication.port_bound_writable_globals",
              "tool.hls.globals.attribute_accesses"],
        effect=("W9r10-impl", None)),
    dict(
        id="ST-7", stage="st", title="Replication at II > 1 for steered window reads does not follow ceil(R/II) - 1",
        notes=["N80"],
        statement=(
            "For a one-dimensional window whose reads are steered to banks (PA-4), Vitis keeps R - 1 BRAM "
            "per bank at II 1, 2 and 3 and only spreads the reads at II 4; two-dimensional windows drop "
            "with the II instead. No tried rule fits both tables; the schedule Vitis gives the reads is the "
            "likely variable. This is recorded as data, not as a rule."),
        kernels=[("w9r9fix_d2_r4_ii1", "R = 4 reads per bank, II 1", {}),
                 ("w9r9fix_d2_r4_ii2", "II 2", {}),
                 ("w9r9fix_d2_r4_ii3", "II 3", {}),
                 ("w9r9fix_d2_r4_ii4", "II 4", {})],
        evidence=["memory table", "loop table"],
        status="unconfirmed (data only)",
        hlsest="not modelled (OPEN_ISSUES O106); no catalogue design is affected",
        mechanism=[], keys=[], effect=None),
    # ------------------------------------------------------------------ formula
    dict(
        id="BF-1", stage="bf", title="The 7-series depth bands with x36 only in simple dual port",
        notes=["N6", "N8"],
        statement=(
            "One bank of D words x W bits costs: ceil(W/36) RAMB18 for D <= 512 in simple-dual-port mode "
            "(one used port, a write-only and a read-only port, or two read-only ports), else ceil(W/18); "
            "ceil(W/18) for 513..1024; ceil(W/9) for 1025..2048; min(ceil(W/4), 2 ceil(W/9)) for "
            "2049..4096; ceil(W/2) for 4097..8192; and 2^ceil(log2 ceil(D/16384)) x W deeper. The band "
            "edges are powers of two, so the address space, not the word count, decides (2500 words "
            "cost as 4096); parity bits count; above 4096 words Vitis never stacks 2Kx9 or 1Kx18 "
            "columns. This is the open-source `MemoryQuerier::queryBRAM` 7-series path, and the "
            "measured model and the transcription disagree only where new kernels decided for the "
            "transcription."),
        kernels=[("aspect_1p_w36_d512", "512 x 36, one port", {}),
                 ("aspect_2r_w36_d512", "512 x 36, two reads per cycle", {}),
                 ("aspect_1p_w9_d2048", "2048 x 9", {}),
                 ("aspect_chk_1p_w18_d2500", "2500 x 18", {}),
                 ("fr_1p_w9_d8192", "8192 x 9", {}),
                 ("fr_1p_w27_d6000", "6000 x 27", {}),
                 ("fr_1p_w18_d16384", "16384 x 18", {})],
        evidence=["memory table", "open source (CoreQuerier.cpp, tag 2025.1)", "bind port vectors"],
        status="confirmed",
        hlsest="modelled (default formula `band`)",
        mechanism=["--bram-analysis (estimateBlocksBand)"],
        keys=["tool.backend.memory_mapper.depth_bands", "tool.backend.memory_mapper.depth_rounding",
              "tool.hls.memory_architecture.wide_port_sets"],
        effect=("the 7-series depth-band formula is the default", None)),
    dict(
        id="BF-2", stage="bf", title="ROMs: two reads are still SDP, more reads cost ceil(n/2) ROMs",
        notes=["N8"],
        statement=(
            "The x36 test is a property of the bound port vector, not of the core type. A ROM read twice "
            "per cycle is SDP (512 x 32 = 1). A read-only memory with n > 2 read ports is not replicated "
            "like a RAM (n - 1 copies) but built from ceil(n/2) dual-port ROMs at x18. An explicitly bound "
            "`ram_2p` whose read and write sit in different loops binds one port each and is SDP too."),
        kernels=[("fr_rom1r_w32_d512", "ROM, one read per cycle", {}),
                 ("fr_rom2r_w32_d512", "two reads", {}),
                 ("fr_rom3r_w32_d512", "three reads", {}),
                 ("fr_rom4r_w32_d512", "four reads", {}),
                 ("aspect_bs2p_w32_d512", "bind_storage ram_2p, R and W in different loops", {})],
        evidence=["memory table", "bind port vectors (MemPortTyVec)", "open source (isSDPMode)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (ROM_NP)"],
        keys=["tool.hls.memory_architecture.rom.copies", "tool.hls.memory_architecture.rom.sdp_max_reads"],
        effect=None),
    # ------------------------------------------------------------------ streams / dataflow
    dict(
        id="DF-1", stage="df", title="FIFO pricing: shift registers up to depth 2 or 1024 bits, else x18 bands",
        notes=["N31"],
        statement=(
            "An `hls::stream` FIFO of depth D and width W costs no BRAM when D <= 2 (at any width) or "
            "D x W <= 1024 bits (shift registers, `[RTMG 210-285]`); otherwise it costs the depth bands of "
            "BF-1 at the x18 ceiling, never x36, although the FIFO RAM has one write and one read port. "
            "The 1024-bit threshold is inclusive here, unlike arrays (ST-1), and moves with "
            "`config_storage fifo -auto_srl_max_bits`. The depth is the declared depth, default 2; one "
            "FIFO per element of an array of streams that is accessed; top-level stream arguments are "
            "ports and have no FIFO; the width is the packed width of the element without padding."),
        kernels=[("fifo_ctl_w32d32", "32 x 32 = 1024 bits", {}),
                 ("fifo_ctl_w18d57", "57 x 18 = 1026 bits", {}),
                 ("fifo_ctl_w36d512", "512 x 36", {}),
                 ("rvf_def_w520", "default depth, 520 bits wide", {}),
                 ("rvf_struct", "structs {char,int}, {char,double}, ...", {}),
                 ("fifo_d_axis_nodf", "top-level stream arguments only", {}),
                 ("fifo_e_srlbits", "`-auto_srl_max_bits 2048`", {})],
        evidence=["FIFO table", "log [RTMG 210-285]", "open source (disagrees: threshold and depth)"],
        status="confirmed (the mechanism of the depth <= 2 rule is unknown)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (StreamFifos)"],
        keys=["tool.hls.streams.srl_max_bits", "tool.hls.streams.srl_max_depth", "tool.hls.streams.default_depth"],
        effect=("hls::stream objects priced as the FIFOs Vitis builds", None)),
    dict(
        id="DF-2", stage="df", title="Where a FIFO's depth and width come from",
        notes=["N49", "N58", "N67", "N72", "N54"],
        statement=(
            "A stream's depth is its `stream` pragma, else its own type's template depth, also when every "
            "access goes through a base-class reference `hls::stream<T>&` (whose type carries none). A "
            "stream of a struct is as wide as the sum of its members' bit widths, bool = 1 bit. A local "
            "array with `#pragma HLS stream` in a dataflow region is a FIFO of the pragma's depth, or as "
            "deep as the array without one. A dataflow top forwards its scalar and pointer arguments to "
            "later processes through FIFOs `<arg>_c` as deep as the longest process chain to the reader "
            "(plus one when the first process does not read it); a non-top region has none."),
        kernels=[("w9r6_sd256", "depth 256 through `hls::stream<W>&` parameters", {}),
                 ("w9r6_sdprag", "template 256, pragma depth 64", {}),
                 ("w9r7_sb_f_bit", "stream of {float, bool}, depth 64", {}),
                 ("w9r7_sb_s_none", "stream of {short, bool}", {}),
                 ("w9r8p_st_d256", "array with `stream depth=256`", {}),
                 ("w9r8p_st_d4", "array with `stream depth=4`", {}),
                 ("w9r8rev_s1", "array with `stream` and no depth", {}),
                 ("w9r7_sc_k8", "dataflow top with 8 pass-through processes", {}),
                 ("w9r7_sc_k16", "16 processes", {})],
        evidence=["FIFO table (Depth, Bits)", "log [RTMG 210-285] (fifo_w<W>_d<D>)"],
        status="confirmed (longest path on DAGs confirmed by one kernel)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (StreamFifos, ProcessMerges::argumentFifos)", "cgeist (stream element bits)"],
        keys=["tool.hls.streams.declared_element_bits", "tool.hls.streams.stream_pragma_arrays",
              "tool.hls.streams.dataflow_argument_fifos"],
        effect=("W9r7-impl 7/10", None)),
    dict(
        id="DF-3", stage="df", title="Ping-pong channels: one memory or a memory per block",
        notes=["N33"],
        statement=(
            "A local array of a dataflow region written by one process and read by a later one is a PIPO "
            "of N blocks (the `stream type=pipo depth`, else 2, but 1 in a non-top region whose callers "
            "are not dataflow regions). It is one true-dual-port memory of N x D words "
            "(`[HLS 200-741]`, priced F(N x D) at x18) unless some process drives a second port of the "
            "channel, i.e. makes two accesses that can happen in the same cycle on one control path, or "
            "the channel is bound to RAM_2P / S2P; then each block is its own memory (`[HLS 200-740]`, "
            "N x F(D)). Accesses in exclusive branch arms share a port. It is never replicated: extra "
            "reads raise the consumer's II. The decision is not a cost choice; at some shapes both modes cost the "
            "same (a 1024 x 32 channel of 2 blocks), so the mode is read from the `[HLS 200-740/741]` lines."),
        kernels=[("pipo_m_base", "one access per iteration on each side", {}),
                 ("pipo_m_r2", "consumer reads twice per iteration", {}),
                 ("pipo_m_r4", "four reads per iteration", {"loops": ["VITIS_LOOP_13"]}),
                 ("pipo_c_d3", "`stream type=pipo depth=3`, one access per side", {}),
                 ("pipo_c_d3sep", "depth 3, a process drives two ports", {}),
                 ("pipo_g_sub", "region in a non-top function called once", {}),
                 ("pipofix_excl2", "exclusive and non-exclusive access pairs", {}),
                 ("pipo_c_bind2p", "bind_storage ram_2p", {})],
        evidence=["log [HLS 200-740]/[HLS 200-741]/[HLS 200-1019]", "memory table", "RTL (<arg>_address1)",
                  "open source comment (pipo_1bank)"],
        status="confirmed (why the binder gives the second port is inferred)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (DataflowChannels)"],
        keys=["tool.hls.dataflow_channels.enabled", "tool.hls.dataflow_channels.default_blocks"],
        effect=("dataflow ping-pong channels (PIPO) priced", None)),
    dict(
        id="DF-4", stage="df", title="Writers of one array are merged into one process, with everything between them",
        notes=["N36", "N84"],
        statement=(
            "All processes of a dataflow region that write one region-local array become one process "
            "(`[HLS 214-475]`), together with every process on a dependence path between them, whatever "
            "carries the path (an array, a stream, a scalar result). The array is still a PIPO when a "
            "process outside the merged group reads it, and an ordinary memory of the merged process when "
            "the group holds every accessor. A producer that contains its own dataflow loop does not "
            "change the outer region: its channels stay PIPOs."),
        kernels=[("w9m_ll2", "two loops write one array", {}),
                 ("w9m_rmw", "one writer is a read-modify-write", {}),
                 ("w9m_cyc", "a path through another array", {}),
                 ("w9v_m_half", "a process with a path to only one writer", {}),
                 ("w9r4rev_r4m_scal", "a path through a scalar result", {}),
                 ("w9r10p_pc_flat", "producer is one pipelined nest", {}),
                 ("w9r10p_pc_nest", "producer holds its own dataflow loop", {})],
        evidence=["log [HLS 214-475]", "memory table"],
        status="confirmed (region arguments as path carriers unconfirmed)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (ProcessMerges, DataflowChannels)"],
        keys=["tool.hls.dataflow_channels.through_nested_regions"],
        effect=("dataflow process merges", None)),
    # ------------------------------------------------------------------ interfaces
    dict(
        id="IF-1", stage="if", title="Top-level arrays cost nothing, except s_axilite arrays",
        notes=["N1a", "N41"],
        statement=(
            "Top-level array arguments on ap_memory never appear in the memory tables. An s_axilite array "
            "argument, however, is stored inside `s_axi_control` and costs BRAM there, outside every "
            "memory row."),
        kernels=[("dg_g_apmem", "ap_memory arguments", {}),
                 ("w9rv_n41_mc", "an s_axilite array argument of 300 words", {})],
        evidence=["memory table", "instance table (s_axi_control)"],
        status="confirmed",
        hlsest="ap_memory modelled; the s_axilite array is not counted (OPEN_ISSUES O62)",
        mechanism=["--bram-analysis"], keys=[], effect=None),
    dict(
        id="IF-2", stage="if", title="m_axi adapters: a read FIFO of burst x outstanding words and a write buffer",
        notes=["N1a"],
        statement=(
            "Every m_axi bundle adds an adapter instance `<bundle>_m_axi_U` whose BRAM comes from its read "
            "FIFO and write buffer, not from a memory row. The read FIFO is "
            "`max_read_burst_length x num_read_outstanding` words (default 16 x 16 = 256) of the bus "
            "width (at least 32 bits): 32 words or fewer cost nothing, deeper ones the x18 bands. The "
            "write buffer costs nothing at the default burst of 16 and ceil(W/18) from 32 on, "
            "independently of the outstanding count. Read and write sides add up; ports without "
            "`bundle=` share `gmem`; accesses inside callees count for the bundle."),
        kernels=[("dg_g_maxi_r", "one read port, defaults", {}),
                 ("mx_r_w64_b64", "64-bit read port", {}),
                 ("mx_r_d2048", "read depth 2048", {}),
                 ("dg_g_maxi_r_b256", "read burst 256", {}),
                 ("mx_w_o32", "write, burst 16, 32 outstanding", {}),
                 ("mx_w_b32", "write burst 32", {}),
                 ("mx_rw_wb64", "read + write burst 64", {}),
                 ("mx_nobundle2", "two read ports without bundle=", {}),
                 ("mx_call_rw2", "read and write inside kept callees", {})],
        evidence=["instance table (adapter BRAM)", "RTL port widths"],
        status="confirmed (write bursts 17-31 and read depths above 4096 untested)",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (MAxiBuffers)"], keys=["tool.hls.implicit_buffers"],
        effect=None),
    dict(
        id="IF-3", stage="if", title="m_axi read FIFOs: one per channel, as wide as the widest cast read, rounded to 2^n",
        notes=["N56", "N63", "N37", "N50"],
        statement=(
            "A bundle has one read FIFO per distinct `channel=` value (ports without one are channel 0). Its "
            "width is the widest read access on that channel counting the type a pointer is cast to "
            "before the load (`reinterpret_cast<ap_uint<512>*>`), rounded up to a power of two and capped "
            "at the 1024-bit AXI bus (a wider element takes two beats). `max_widen_bitwidth` alone does "
            "not widen; an earlier reading (N50) that attributed the 29-BRAM adapters to it is "
            "superseded."),
        kernels=[("w9r6_mw_512", "max_widen_bitwidth=512, 16-bit reads", {}),
                 ("w9r6_mw_sh3", "three 256-bit ports, one channel", {}),
                 ("w9r7_mx_ch3", "three 256-bit ports, channels 0/1/2", {}),
                 ("w9r7_mx_cast512nw", "short port read through a 512-bit cast", {}),
                 ("w9r7i_mx_w2048", "2048-bit element", {}),
                 ("w9r8p_mx_i9", "std::array<int,9> elements (288 bits)", {}),
                 ("w9r8p_mx_i8", "control: std::array<int,8> (256 bits)", {})],
        evidence=["instance table (adapter BRAM)", "log [HLS 214-115] (burst bit width)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--bram-analysis (MAxiBuffers)"], keys=["tool.hls.implicit_buffers"],
        effect=("W9r7-impl 4/10", None)),
    # ------------------------------------------------------------------ scheduling
    dict(
        id="SC-1", stage="sc", title="Integer reductions are reassociated, float reductions are not",
        notes=["N39"],
        statement=(
            "An unrolled integer or fixed-point `sum +=` chain in a pipelined loop is rebalanced into a "
            "tree feeding one loop-carried add (`[XFORM 203-11]`), so the recurrence costs one adder and "
            "the loop reaches II 1 at 8 and 32 terms. A floating-point chain is not reassociated and the "
            "recurrence spans every add. The II then decides the copy count of ST-3 (32 reads at II 2 "
            "is the 16-memory cap)."),
        kernels=[("w9p5_bal_int_u32_p", "32-term int sum, partitioned reads", {"loops": ["VITIS_LOOP_11"]}),
                 ("w9p5_bal_fix_u8_p", "8-term ap_fixed sum", {"loops": ["VITIS_LOOP_11"]}),
                 ("w9p5_bal_flt_u8_p", "8-term float sum", {"loops": ["VITIS_LOOP_11"]}),
                 ("w9p5_bal_int_u32_np", "32-term int sum, unpartitioned", {"loops": ["VITIS_LOOP_9"]})],
        evidence=["loop table (II)", "log [XFORM 203-11]", "memory table"],
        status="confirmed",
        hlsest="modelled (default; the greedy scheduler needs its recurrence repair, OPEN_ISSUES O56)",
        mechanism=["--convert-affine-to-loopschedule (simplex and greedy modulo schedulers)"],
        keys=["scheduling.modulo.recurrence_repair_rounds"],
        effect=None),
    dict(
        id="SC-2", stage="sc", title="Floating-point latencies depend on the type, and on chain versus recurrence",
        notes=["N78", "N79", "N83"],
        statement=(
            "On this part and clock a recurrence through a divider runs at II "
            "[[w9r9p_lat_div32:ii:VITIS_LOOP_9]] in single precision and [[w9r9p_lat_div64:ii:VITIS_LOOP_9]] "
            "in double, so the latency is a property of the operator and its type, not of a class. Adders "
            "and multipliers have a recurrence latency (the II of `s = s op a[i]`) that differs from their "
            "latency inside a chain (the growth of the iteration latency with the chain length; compare "
            "`w9r10p_ch_fadd1` and `w9r10p_ch_fadd4` in the table). A divide by a "
            "power-of-two constant is rewritten into a multiply by its exact reciprocal; any other "
            "constant keeps the divider. The latency matters for BRAM only where a recurrence sets the "
            "II of a loop that reads an array more than II times."),
        kernels=[("w9r9p_lat_div32", "`s = s / t`, float", {"loops": ["VITIS_LOOP_9"]}),
                 ("w9r9p_lat_div64", "`s = s / t`, double", {"loops": ["VITIS_LOOP_9"]}),
                 ("w9r9p_lat_div64r32", "the double divide with 32 reads per iteration", {"loops": ["VITIS_LOOP_9"]}),
                 ("w9r10p_rc_fadd", "`s = s + a[i]`, float", {}),
                 ("w9r10p_rc_dmul", "`s = s * a[i]`, double", {}),
                 ("w9r10p_ch_fadd1", "one fadd in a chain", {"lat": True}),
                 ("w9r10p_ch_fadd4", "four chained fadds", {"lat": True}),
                 ("w9r9rev_e78_div2", "`s / 2.0 + t`, double", {"loops": ["VITIS_LOOP_8"]}),
                 ("w9r9fix_f78_div3", "`s / 3.0 + t`, double", {"loops": ["VITIS_LOOP_8"]})],
        evidence=["loop table (II, iteration latency)", "IR a.o.3 (fmul by the reciprocal)"],
        status="confirmed",
        hlsest="partly modelled: typed divide / sqrt latencies and the reciprocal rewrite; one add / multiply latency per class (OPEN_ISSUES O107)",
        mechanism=["--convert-affine-to-loopschedule (operator timing)", "--auto-pipeline-unroll (floatCycles)"],
        keys=["scheduling.timing.operator_latencies.fpdiv_f32", "scheduling.timing.operator_latencies.fpdiv_f64",
              "scheduling.timing.operator_latencies.fpsqrt_f32", "scheduling.timing.operator_latencies.fpsqrt_f64"],
        effect=None),
    dict(
        id="SC-3", stage="sc", title="Calls sharing an instance in a pipeline run one after the other",
        notes=["N14"],
        statement=(
            "In a pipelined loop, calls that share one instance (for example because they access a "
            "common array) are serialised: each occupies the instance for its whole depth (latency + 1 "
            "states), and the II is the sum of their depths. The depth follows Vitis's operator delays, "
            "including the grouping of two adds into one three-input `TernaryAdder` that starts when all "
            "three inputs are ready. Reads made inside such a callee go through its instance's port and "
            "are not replicated."),
        kernels=[("inl_e3_arg_pipe_twocalls", "two calls of a latency-1 callee", {"loops": ["VITIS_LOOP_9"]}),
                 ("w3fx_d4_three", "three calls", {"loops": ["VITIS_LOOP_9"]}),
                 ("w3fx_d4_mul", "two calls of a latency-3 callee", {"loops": ["VITIS_LOOP_9"]}),
                 ("w3r2_k8_unrolled_calls", "four calls from an unrolled loop", {"loops": ["VITIS"]})],
        evidence=["loop table (II)", "log [HLS 200-880]", "verbose schedule reports (TernaryAdder)"],
        status="confirmed",
        hlsest="modelled (default)",
        mechanism=["--auto-pipeline-unroll (hls.call_depth)", "--convert-affine-to-loopschedule"],
        keys=["scheduling.call_depth.ternary_adder_ns", "scheduling.call_depth.ports_per_memory"],
        effect=("non-inlined calls review fixes", 'exactclass: 56 / 95')),
    dict(
        id="SC-4", stage="sc", title="A user II is a target, and copies are sized at the final II",
        notes=["N38"],
        statement=(
            "A user `pipeline II=N` is the II Vitis aims for, not a floor: the copies of ST-3 are sized at "
            "the final II of the reading loop. Corpus loops also finish below their target (unexplained) "
            "and above it when other limits bind."),
        kernels=[("w9v_r_iifl", "`pipeline II=2`, 8 reads per iteration", {"loops": ["rd"]})],
        evidence=["log [HLS 200-1470] (Target II, Final II)", "memory table"],
        status="confirmed (when Vitis finishes below the target is unconfirmed)",
        hlsest="modelled (default): scheduled at the target unless other limits need more",
        mechanism=["--convert-affine-to-loopschedule"], keys=["scheduling.modulo.user_ii_target"],
        effect=("a loop with a user `pipeline II=N` is scheduled at N", None)),
    dict(
        id="SC-5", stage="sc", title="A stream access in a pipeline is one operation on that stream's single port",
        notes=["N82"],
        statement=(
            "A blocking `hls::stream` read or write in a pipelined body is an ordinary operation (a read "
            "adds two cycles, a write one to the iteration latency) on a resource of one access per cycle "
            "per stream object: the II is at least the accesses to one stream per iteration, while "
            "accesses to different streams do not share it. The arrays of the loop are priced as for the "
            "same loop without the stream call."),
        kernels=[("w9r10p_sc_base", "control: the result stored to an array", {"loops": ["VITIS_LOOP_13"]}),
                 ("w9r10p_sc_sw", "one `out.write(s)` per iteration", {"loops": ["VITIS_LOOP_13"]}),
                 ("w9r10p_sc_2s", "one write to each of two streams", {"loops": ["VITIS_LOOP_13"]}),
                 ("w9r10p_sc_2w", "two writes to one stream", {"loops": ["VITIS_LOOP_13"]}),
                 ("w9r10p_sc_2r", "two reads of one stream", {"loops": ["VITIS_LOOP_13"]})],
        evidence=["loop table (II, iteration latency)", "memory table"],
        status="confirmed",
        hlsest="modelled opt-in only: adopting it fails the rule-4 test until memory recurrences are scheduled (OPEN_ISSUES O114, O1)",
        mechanism=["--convert-affine-to-loopschedule (stream timing, opt-in)"],
        keys=["scheduling.timing.operator_latencies"],
        effect=None),
]

# Behaviours that surprised us: each is one paragraph, citing the rule and the kernels whose runs
# show it (numbers through [[...]] references only).
SURPRISES = [
    ("Division by zero deletes memories", ["N1", "N13"], "FE-6",
     "In `ap_fixed<16,5>`, `(ap_fixed<16,5>)16` wraps to -16, `hls::sqrt(-16)` is 0 and `1.0 / 0` is the "
     "undefined value that every fixed-point use sees as 0. The attention kernel's score scaling therefore "
     "stores 0, and the Q and K projections (and the global weights that feed them) are deleted: "
     "`dg_d_apfixed16` costs [[dg_d_apfixed16]] BRAM_18K where its non-folding twin `dg_d_apfixed4` costs "
     "[[dg_d_apfixed4]]."),
    ("Folds happen at different times", ["N52"], "FE-9",
     "A scalar global bound folds before the pipeline decision (`rvsf_g1`: [[rvsf_g1]] BRAM_18K, the inner "
     "loop unrolled and the buffer replicated), but a two-element table of one value folds only after it "
     "(`rvsf_rc16`: [[rvsf_rc16]]), because the table must first become registers through the pipeline "
     "pragma the decision itself sets."),
    ("A ROM's width is a signed reading of its values", ["N26"], "FE-7",
     "Filling with 6 gives a 2-bit ROM ([[w7_rf6:mem:buf_r]]) because 110b read as a signed number is -2, "
     "and filling with 100000 gives 16 bits ([[w7_rf17u:mem:buf_r]]), not 17."),
    ("Replicated copies always pay the true-dual-port price", ["N4", "N6"], "ST-3",
     "Every RAM_1WNR copy is priced at the x18 ceiling even though each copy serves a single read port: "
     "`pu_red_m8_n16`'s 16 reads per iteration of a 128 x 32 array cost [[pu_red_m8_n16:mem:la]], two "
     "RAMB18 per copy, where the same array with one live port fits a single RAMB18 in the x36 mode "
     "(`pu_cfg_pl0_red_m8_n16`: [[pu_cfg_pl0_red_m8_n16:mem:la]])."),
    ("The left operand of an hls::vector operator is taken by value", ["N51"], "FE-11",
     "`(q * k).reduce_add()` disaggregates q into lanes and keeps k aggregated; `(k * q)` does the "
     "opposite. The only difference is which operand the header's `operator*(vector lhs, const vector &rhs)` "
     "copies (`w9r6_vx_var` [[w9r6_vx_var]], `w9r7_vx_swap` [[w9r7_vx_swap]], references only "
     "`w9r7_vx_ref` [[w9r7_vx_ref]] BRAM_18K)."),
    ("An ap_fixed compound assignment is two stores", ["N38"], "ST-4",
     "`A[b][i] /= x` with a run-time bank goes through a cross-format `operator=` that first stores 0; the "
     "second store forbids replication (`w9r_d1div`: [[w9r_d1div]] BRAM_18K) where the plain assignment "
     "`A = w * A` replicates (`w9r_d4asg`: [[w9r_d4asg]])."),
    ("Nested dataflow does not hide the outer channels", ["N84"], "DF-4",
     "A producer process that runs its own dataflow loop over rows leaves the outer channels ping-pong "
     "buffers: `w9r10p_pc_nest` costs [[w9r10p_pc_nest]] against [[w9r10p_pc_flat]] for the flat producer, "
     "the difference being the inner region's own channel."),
    ("Window reads are counted per residue class", ["N74"], "PA-4",
     "A 3 x 3 window over a factor-3 cyclic partition reads every bank once per iteration and needs no "
     "copies (`w9r9p_o92_f3_w3x3`: [[w9r9p_o92_f3_w3x3]] BRAM_18K for 9 banks), whereas over a factor-2 "
     "partition two of the three offsets fall in one class on each dimension (`w9r9p_o92_f2_w3x3`: "
     "[[w9r9p_o92_f2_w3x3]])."),
    ("A FIFO of 1024 bits is free, an array of 1024 bits is not", ["N5", "N31"], "DF-1",
     "The FIFO threshold is `D x W <= 1024` (`fifo_ctl_w32d32`: [[fifo_ctl_w32d32]] BRAM_18K) while an array "
     "of exactly 1024 bits is a BRAM (`lutram_d64_w16`: [[lutram_d64_w16]]); and a FIFO never uses the x36 "
     "mode although it has one write and one read port (`fifo_ctl_w36d512`: [[fifo_ctl_w36d512]])."),
    ("Integer and float invariant loads decide differently", ["N3"], "LP-2",
     "The same nest is flattened for a float invariant load and unrolled for an int one: "
     "`rv_rmw_hoist_f_m8_n64` [[rv_rmw_hoist_f_m8_n64]] against `rv_rmw_hoist_m8_n64` "
     "[[rv_rmw_hoist_m8_n64]] BRAM_18K, with no visible difference in `a.o.1.ll`."),
    ("A written global is never replicated", ["N85"], "ST-6",
     "The same 16 reads per iteration replicate a local of the top ([[w9r10p_gp_loc_param]] BRAM_18K, II "
     "[[w9r10p_gp_loc_param:ii:VITIS_LOOP_8_1]]) but not a file-scope global ([[w9r10p_gp_glob_top]], II "
     "[[w9r10p_gp_glob_top:ii:VITIS_LOOP_13]])."),
    ("A histogram is never dead", ["N66"], "FE-4",
     "`cnt[k] = cnt[k] + 1` keeps `cnt` ([[w9r8p_dm_self]] BRAM_18K) although nothing read from it ever "
     "leaves the kernel, while the same array with unused loads disappears ([[w9r8p_dm_rd]])."),
    ("A divide by two is a multiply", ["N79"], "SC-2",
     "`s / 2.0` is rewritten to `s * 0.5`, so the recurrence runs through a multiplier (II "
     "[[w9r9rev_e78_div2:ii:VITIS_LOOP_8]]) and the array it reads needs more copies "
     "([[w9r9rev_e78_div2]] BRAM_18K) than with `s / 3.0` (II [[w9r9fix_f78_div3:ii:VITIS_LOOP_8]], "
     "[[w9r9fix_f78_div3]])."),
    ("A second write to the same stream halves the copies", ["N82"], "SC-5",
     "One `out.write()` per iteration leaves the loop at II [[w9r10p_sc_sw:ii:VITIS_LOOP_13]] with "
     "[[w9r10p_sc_sw]] BRAM_18K of copies; two writes to the same stream force II "
     "[[w9r10p_sc_2w:ii:VITIS_LOOP_13]], and the same array then needs [[w9r10p_sc_2w]]."),
]
