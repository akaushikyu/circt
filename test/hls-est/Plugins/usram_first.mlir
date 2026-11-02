// The worked non-AMD target of hls-doc/new-architecture.md: a Microchip
// PolarFire description (tools/hls-est-plugins/polarfire: device file,
// generic-1.0 profile, the storage selector usram-first in
// HlsEstPolarFirePlugin). No ground truth: the numbers are the model's, and
// the document says what to measure to validate them.

// a[64] x 12 fits one uSRAM; b[1024] x 20 is one LSRAM at 1Kx20; c[512] x 40,
// read and written per cycle, is one LSRAM in the 512x40 two-port (sdp)
// configuration (port_set_rule by_demand: [r, w] is a wide set). Every block
// adds its fabric overhead (36 / 12 4LUT and DFF), and stdout prints one
// total per reported class.
// RUN: hls-est %S/Inputs/polarfire_kernel.mlir --load-plugin=%hlsest_polarfire_plugin --hls-config=%hlsest_polarfire_dir/polarfire.json --default-pipeline -o /dev/null | FileCheck %s
// CHECK:      memref.alloca
// CHECK-NEXT:   kind=RAM_1P  4LUT=12 DFF=12 uSRAM=1{{$}}
// CHECK-NEXT:     64x12b -> RAM_1P (x12/port) = 1 uSRAM
// CHECK:      memref.alloca
// CHECK-NEXT:   kind=RAM_1P  4LUT=36 DFF=36 LSRAM=1{{$}}
// CHECK-NEXT:     1024x20b -> RAM_1P (x20/port) = 1 LSRAM
// CHECK:      memref.alloca
// CHECK-NEXT:   kind=RAM_2P  4LUT=36 DFF=36 LSRAM=1{{$}}
// CHECK-NEXT:     512x40b -> RAM_2P (x40/port) = 1 LSRAM
// CHECK-NOT:  Total BRAM
// CHECK:      Total LSRAM: 2{{$}}
// CHECK-NEXT: Total uSRAM: 1{{$}}
// CHECK-NEXT: Total 4LUT: 84{{$}}
// CHECK-NEXT: Total DFF: 84{{$}}

// Two reads of c per cycle: [r, r] is not a wide set, so the bank is priced
// in the tdp configuration (x20 per port): two LSRAM.
// RUN: hls-est %S/Inputs/polarfire_kernel_2r.mlir --load-plugin=%hlsest_polarfire_plugin --hls-config=%hlsest_polarfire_dir/polarfire.json --default-pipeline -o /dev/null | FileCheck %s --check-prefix=TWO
// TWO:      512x40b -> RAM_2P (x20/port) = 2 LSRAM
// TWO:      Total LSRAM: 3{{$}}
// TWO-NEXT: Total uSRAM: 1{{$}}
// TWO-NEXT: Total 4LUT: 120{{$}}

// max_tiles 0: no uSRAM.
// RUN: hls-est %S/Inputs/polarfire_kernel.mlir --load-plugin=%hlsest_polarfire_plugin --hls-config=%hlsest_polarfire_dir/polarfire.json --config-set plugins.usram-first.max_tiles=0 --default-pipeline -o /dev/null | FileCheck %s --check-prefix=NOU
// NOU:      Total LSRAM: 3{{$}}
// NOU-NEXT: Total uSRAM: 0{{$}}

// The Vitis profile refuses the device (no RAMB18 model), and the PolarFire
// profile without its plugin names an unknown selector.
// RUN: not hls-est %S/Inputs/polarfire_kernel.mlir --config-set run.device=%hlsest_polarfire_dir/microchip-polarfire.device.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=VITIS
// VITIS: error: hls-config: {{.*}}vitis-band7{{.*}}microchip-polarfire
// RUN: not hls-est %S/Inputs/polarfire_kernel.mlir --hls-config=%hlsest_polarfire_dir/polarfire.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=NOPLUGIN
// NOPLUGIN: no storage_selector plugin named 'usram-first' is registered

// A uSRAM bank read and written in one cycle: by_demand prices it at [r, w]
// (sdp, which uSRAM has); by_kind prices a 2-port RAM at the narrow
// configuration tdp, which uSRAM lacks: the run fails and names the bank
// instead of pricing it with another memory's numbers.
// RUN: hls-est %S/Inputs/polarfire_rmw.mlir --load-plugin=%hlsest_polarfire_plugin --hls-config=%hlsest_polarfire_dir/polarfire.json --default-pipeline -o /dev/null | FileCheck %s --check-prefix=RMW
// RMW: 64x12b -> RAM_2P (x12/port) = 1 uSRAM
// RUN: not hls-est %S/Inputs/polarfire_rmw.mlir --load-plugin=%hlsest_polarfire_plugin --hls-config=%hlsest_polarfire_dir/polarfire.json --config-set tool.hls.memory_architecture.port_set_rule=by_kind --default-pipeline -o /dev/null 2>&1 | FileCheck %s --check-prefix=NOTDP
// NOTDP: polarfire_rmw.mlir:4:10: error: --bram-analysis: the memory architecture policy prices this bank at port configuration 'tdp', which memory 'usram' (tier hard-small) does not have
