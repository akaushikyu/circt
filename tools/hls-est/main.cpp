#include "circt/Dialect/LoopSchedule/LoopScheduleDialect.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/Resource/Passes/AffineToLoopScheduleModified.h"
#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/Resource/Passes/MergeConditionalStores.h"
#include "circt/Dialect/Resource/Passes/MemoryBankModified.h"
#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "circt/Dialect/Resource/Passes/InferVitisSplitArray.h"
#include "circt/Dialect/Resource/Passes/DebugUnroll.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"
#include "circt/Dialect/Resource/Passes/HlsInliner.h"      // --inline keeps hls.inline_off callees (W3)
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h" // polygeist.subindex, --lower-polygeist-subindex (W3, O25)
#include "circt/Dialect/Resource/Config/Config.h" // --hls-config et al. (P2)
#include "circt/Dialect/Resource/Plugins/Registry.h" // the builtin plugins
#include "mlir/IR/DialectRegistry.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Tools/Plugins/PassPlugin.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ToolOutputFile.h"
#include "mlir/Transforms/Passes.h"   // createCSEPass, registerCSEPass, registerCanonicalizerPass et al.

#include "mlir/Dialect/Affine/IR/AffineOps.h"          // affine::AffineDialect
#include "mlir/Dialect/Arith/IR/Arith.h"               // arith::ArithDialect
#include "mlir/Dialect/MemRef/IR/MemRef.h"             // memref::MemRefDialect
#include "mlir/Dialect/SCF/IR/SCF.h"                   // scf::SCFDialect
#include "mlir/Dialect/Func/IR/FuncOps.h"              // func::FuncDialect
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"   // cf::ControlFlowDialect
#include "mlir/Dialect/Index/IR/IndexDialect.h"        // index::IndexDialect
#include "mlir/Dialect/Affine/Transforms/Passes.h"     // affine-loop-normalize et al.

// CIRCT dialects

#include "circt/Dialect/HW/HWDialect.h"                // hw::HWDialect
#include "circt/Dialect/Comb/CombDialect.h"            // comb::CombDialect
#include "circt/Dialect/Seq/SeqDialect.h"              // seq::SeqDialect
#include "circt/Dialect/Calyx/CalyxDialect.h"          // calyx::CalyxDialect
#include "circt/Dialect/Resource/HLS/HLSOps.h"         // custom dialect
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/DLTI/DLTI.h"              // dlti.dl_spec module attribute emitted by cgeist
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"    // llvm.linkage attrs / llvm.* ops emitted by cgeist
#include "mlir/Dialect/LLVMIR/Transforms/InlinerInterfaceImpl.h" // --inline with the llvm dialect loaded

//===----------------------------------------------------------------------===//
// The configuration (hls-doc/configuration.md). The options are read after
// the whole command line has been parsed, so a --hls-config file may name
// plugins that a later --load-plugin registers.
//===----------------------------------------------------------------------===//
static llvm::cl::OptionCategory configCategory("hls-est configuration");

static llvm::cl::list<std::string> configFiles(
    "hls-config",
    llvm::cl::desc("Configuration file (JSON) whose keys override the "
                   "compiled-in defaults; repeatable, later files win"),
    llvm::cl::value_desc("file"), llvm::cl::cat(configCategory));
static llvm::cl::alias configFilesAlias("config",
                                        llvm::cl::desc("Alias for --hls-config"),
                                        llvm::cl::aliasopt(configFiles),
                                        llvm::cl::cat(configCategory));
static llvm::cl::list<std::string> configSets(
    "config-set",
    llvm::cl::desc("One key of the configuration: <key.path>=<JSON value> (a "
                   "bare word is a string); repeatable, applied after the "
                   "files"),
    llvm::cl::value_desc("key=value"), llvm::cl::cat(configCategory));
static llvm::cl::opt<bool> dumpDefaultConfigOpt(
    "dump-default-config",
    llvm::cl::desc("Print the compiled-in configuration (every key with a "
                   "description) and exit"),
    llvm::cl::init(false), llvm::cl::cat(configCategory));
static llvm::cl::opt<bool> dumpEffectiveConfigOpt(
    "dump-effective-config",
    llvm::cl::desc("Print the merged configuration (defaults, files, "
                   "--config-set), with _source next to every changed key, to "
                   "stderr, and continue"),
    llvm::cl::init(false), llvm::cl::cat(configCategory));
static llvm::cl::opt<bool> dumpConfigSchemaOpt(
    "dump-config-schema",
    llvm::cl::desc("Print every configuration key (type, unit, default, "
                   "range, description, inventory rows, readers) as JSON and "
                   "exit"),
    llvm::cl::init(false), llvm::cl::cat(configCategory));
/// Loads one hls-est plugin library (--load-plugin): MLIR's pass-plugin
/// loader (entry point mlirGetPassPluginInfo, MLIR_PLUGIN_API_VERSION) plus
/// hls-est's own optional entry point hlsEstGetPluginInfo, whose
/// HLS_EST_PLUGIN_API_VERSION must match; the plugin's static registrars
/// registered its implementations when the library was opened.
static bool pluginLoadFailed = false;
static void loadHlsEstPlugin(const std::string &path) {
  llvm::Expected<mlir::PassPlugin> plugin = mlir::PassPlugin::load(path);
  if (!plugin) {
    llvm::errs() << "error: --load-plugin: " << path << ": "
                 << llvm::toString(plugin.takeError()) << "\n";
    pluginLoadFailed = true;
    return;
  }
  std::string err;
  llvm::sys::DynamicLibrary lib =
      llvm::sys::DynamicLibrary::getPermanentLibrary(path.c_str(), &err);
  auto *infoFn = reinterpret_cast<circt::hlsest::HlsEstPluginInfo (*)()>(
      lib.getAddressOfSymbol("hlsEstGetPluginInfo"));
  if (!infoFn) {
    llvm::errs() << "warning: --load-plugin: " << path
                 << " has no hlsEstGetPluginInfo entry point; its interface "
                    "version is not checked\n";
  } else if (infoFn().apiVersion != HLS_EST_PLUGIN_API_VERSION) {
    llvm::errs() << "error: --load-plugin: " << path << " ("
                 << infoFn().name << ") was built for hls-est plugin API "
                 << infoFn().apiVersion << ", this hls-est has "
                 << HLS_EST_PLUGIN_API_VERSION << "\n";
    pluginLoadFailed = true;
    return;
  }
  plugin->registerPassRegistryCallbacks();
}

static llvm::cl::list<std::string> loadPlugins(
    "load-plugin",
    llvm::cl::desc("Load an hls-est plugin library (its implementations of "
                   "the plugin interfaces become selectable by name in the "
                   "configuration); repeatable"),
    llvm::cl::value_desc("library"), llvm::cl::cat(configCategory),
    llvm::cl::callback([](const std::string &path) { loadHlsEstPlugin(path); }));

static llvm::cl::opt<bool> listPluginsOpt(
    "list-plugins",
    llvm::cl::desc("Print every registered plugin per interface (builtins and "
                   "the ones --load-plugin loaded) and exit"),
    llvm::cl::init(false), llvm::cl::cat(configCategory));
static llvm::cl::opt<bool> defaultPipeline(
    "default-pipeline",
    llvm::cl::desc("Run the configuration's default pipeline (tool.pipeline) "
                   "instead of passes given on the command line"),
    llvm::cl::init(false), llvm::cl::cat(configCategory));

/// Adds the passes of a pipeline string in flag form (`--a --b=opt=1`) to
/// `pm` as the command line would: through each pass's registry entry, so
/// that a function pass nests implicitly.
static mlir::LogicalResult addPipelineFlags(llvm::StringRef flags,
                                            mlir::OpPassManager &pm) {
  llvm::SmallVector<llvm::StringRef> words;
  flags.split(words, ' ', -1, /*KeepEmpty=*/false);
  for (llvm::StringRef w : words) {
    auto [name, opts] = w.ltrim('-').split('=');
    const mlir::PassRegistryEntry *entry = mlir::PassInfo::lookup(name);
    if (!entry)
      entry = mlir::PassPipelineInfo::lookup(name);
    if (!entry) {
      llvm::errs() << "error: tool.pipeline: '" << w
                   << "' is not a registered pass\n";
      return mlir::failure();
    }
    if (failed(entry->addToPipeline(pm, opts, [&](const llvm::Twine &msg) {
          llvm::errs() << "error: tool.pipeline: " << msg << "\n";
          return mlir::failure();
        })))
      return mlir::failure();
  }
  return mlir::success();
}

/// Builds and installs the configuration; prints the requested dumps. Returns
/// an exit code when the driver must stop (an error, or a dump that exits).
static std::optional<int> setUpConfiguration() {
  using namespace circt::hlsest;
  if (dumpDefaultConfigOpt) {
    llvm::outs() << circt::hlsest::dumpDefaultConfig();
    return 0;
  }
  if (dumpConfigSchemaOpt) {
    llvm::outs() << circt::hlsest::dumpConfigSchema();
    return 0;
  }
  if (pluginLoadFailed || circt::hlsest::pluginRegistrationFailed())
    return 1;
  if (listPluginsOpt) {
    for (const auto &[key, entries] : listPlugins()) {
      llvm::outs() << key << ":\n";
      for (const PluginEntry &e : entries)
        llvm::outs() << "  " << e.name << " [" << e.origin << "] "
                     << e.description << "\n";
    }
    return 0;
  }
  ConfigDiagnostics diag;
  std::vector<std::string> files(configFiles.begin(), configFiles.end());
  std::vector<std::string> sets(configSets.begin(), configSets.end());
  Config config = buildConfig(files, sets, diag);
  for (const std::string &w : diag.warnings)
    llvm::errs() << "warning: hls-config: " << w << "\n";
  if (!diag.ok()) {
    for (const std::string &e : diag.errors)
      llvm::errs() << "error: hls-config: " << e << "\n";
    return 1;
  }
  if (dumpEffectiveConfigOpt)
    llvm::errs() << circt::hlsest::dumpEffectiveConfig(config);
  Config::install(std::move(config));
  return std::nullopt;
}

int main(int argc, char **argv) {
  // The builtin plugins first, so that a plugin loaded on the command line
  // cannot take a builtin's name, and the configuration can name them.
  circt::hlsest::registerBuiltinPlugins();
  mlir::DialectRegistry registry;

  registry.insert<
      // Upstream
      mlir::affine::AffineDialect,
      mlir::arith::ArithDialect,
      mlir::memref::MemRefDialect,
      mlir::scf::SCFDialect,
      mlir::func::FuncDialect,
      mlir::cf::ControlFlowDialect,
      mlir::index::IndexDialect,
      mlir::math::MathDialect,
      mlir::DLTIDialect,
      mlir::LLVM::LLVMDialect,
      // CIRCT
      circt::loopschedule::LoopScheduleDialect,
      circt::hw::HWDialect,
      circt::comb::CombDialect,
      circt::seq::SeqDialect,
      circt::calyx::CalyxDialect,
      circt::hls_analysis::HLSDialect,
      // cgeist's polygeist.subindex (a row passed by reference, W3) and its
      // pointer casts pointer2memref / memref2pointer (W8b), O25
      circt::hls_analysis::PolygeistCompatDialect
  >();

  // External interfaces still need their host dialects loaded above.
  // The func dialect's inliner interface lives in an extension; without it
  // `--inline` aborts ("DialectInlinerInterface ... never implemented").
  // hls-est's own interface (HlsInliner.cpp) replaces the stock one: it
  // keeps calls to `hls.inline_off` callees, which Vitis charges once per
  // instance (VITIS_NOTES.md N14; --inline-ignore-inline-off restores the
  // old behaviour).
  circt::hls_analysis::registerHlsInlinerExtension(registry);
  // The llvm dialect also only promises its inliner interface. It is loaded
  // for every cgeist module (the `llvm.linkage` attribute of each function),
  // and the inliner collects the interface of every loaded dialect, so
  // without this `--inline` aborts on any cgeist output ("promised by dialect
  // 'llvm' but never implemented"). The other dialects registered above
  // implement theirs in the dialect itself; only func and llvm promise one.
  mlir::LLVM::registerInlinerInterface(registry);
  // cgeist's arrays of structs (`memref<N x !llvm.struct<...>>`), W8b / O25.
  circt::hls_analysis::registerPolygeistMemRefElementTypes(registry);
  circt::hls_analysis::registerBRAMInterfaceExternalModels(registry);
  circt::hls_analysis::registerBRAMLoopscheduleAnalysisPass();
  circt::hls_analysis::registerAffineToLoopScheduleAnalysisPass();
  circt::hls_analysis::registerMergeConditionalStoresPass();
  circt::hls_analysis::registerMemoryBankingPassModified();
  circt::hls_analysis::registerAutoPipelineUnrollPass();
  circt::hls_analysis::registerDebugUnrollPass();
  circt::hls_analysis::registerInferVitisSplitArray();
  circt::hls_analysis::registerVitisCleanupPasses();
  circt::hls_analysis::registerLowerSubIndexPass();
  circt::hls_analysis::registerSplitStructMemrefsPass();
  // Upstream affine passes (gives you -affine-loop-normalize, -affine-loop-unroll,
  // -affine-loop-coalescing, etc. on the command line).
  mlir::affine::registerAffinePasses();
  mlir::registerCSEPass();
  mlir::registerCanonicalizerPass();
  mlir::registerTransformsPasses();

  auto [inputFilename, outputFilename] = mlir::registerAndParseCLIOptions(
      argc, argv, "HLS BRAM analysis driver\n", registry);
  if (std::optional<int> exitCode = setUpConfiguration())
    return *exitCode;
  if (!defaultPipeline)
    return mlir::asMainReturnCode(
        mlir::MlirOptMain(argc, argv, inputFilename, outputFilename, registry));

  // --default-pipeline: the configuration's tool.pipeline instead of pass
  // flags (as MlirOptMain(argc, argv, input, output, registry) does
  // otherwise). A pass given as well would be dropped silently, so it is an
  // error.
  for (int i = 1; i < argc; ++i) {
    llvm::StringRef arg(argv[i]);
    if (!arg.starts_with("-"))
      continue;
    llvm::StringRef name = arg.ltrim('-').split('=').first;
    if (name == "pass-pipeline" || mlir::PassInfo::lookup(name) ||
        mlir::PassPipelineInfo::lookup(name)) {
      llvm::errs() << "error: --default-pipeline runs the configuration's "
                      "tool.pipeline; '"
                   << arg
                   << "' would be ignored (drop it, or give the whole "
                      "pipeline as pass flags instead of --default-pipeline)\n";
      return 1;
    }
  }
  llvm::InitLLVM initLLVM(argc, argv);
  mlir::MlirOptMainConfig config = mlir::MlirOptMainConfig::createFromCLOptions();
  std::string pipeline = circt::hlsest::Config::get().tool.pipeline;
  config.setPassPipelineSetupFn([pipeline](mlir::PassManager &pm) {
    return addPipelineFlags(pipeline, pm);
  });
  std::string errorMessage;
  auto file = mlir::openInputFile(inputFilename, &errorMessage);
  if (!file) {
    llvm::errs() << errorMessage << "\n";
    return 1;
  }
  auto output = mlir::openOutputFile(outputFilename, &errorMessage);
  if (!output) {
    llvm::errs() << errorMessage << "\n";
    return 1;
  }
  if (failed(mlir::MlirOptMain(output->os(), std::move(file), registry, config)))
    return 1;
  output->keep();
  return 0;
}