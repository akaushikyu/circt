/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ESI.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::esi {

/// A node in the AppID hierarchy
class AppIDHierNodeOp;

} // namespace circt::esi
namespace circt::esi {

/// The root of an appid instance hierarchy
class AppIDHierRootOp;

} // namespace circt::esi
namespace circt::esi {

/// Service against which hardware can call into software
class CallServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// Control options for an ESI channel.
/// A channel buffer (`buffer`) is essentially a set of options on a channel.
/// It always adds at least one cycle of latency (pipeline stage) to the
/// channel, but this is configurable.
/// 
/// This operation is inserted on an ESI dataflow edge. It must exist
/// previous to SystemVerilog emission but can be added in a lowering pass.
/// 
/// A `stages` attribute may be provided to specify a specific number of cycles
/// (pipeline stages) to use on this channel. Must be greater than 0.
/// 
/// A `name` attribute may be provided to assigned a name to a buffered
/// connection.
/// 
/// Example:
/// 
/// ```mlir
/// %esiChan = hw.instance "sender" @Sender () : () -> (!esi.channel<i1>)
/// // Allow automatic selection of options.
/// %bufferedChan = esi.buffer %esiChan : i1
/// hw.instance "recv" @Reciever (%bufferedChan) : (!esi.channel<i1>) -> ()
/// 
/// // Alternatively, specify the number of stages.
/// %fourStageBufferedChan = esi.buffer %esiChan { stages = 4 } : i1
/// ```
class ChannelBufferOp;

} // namespace circt::esi
namespace circt::esi {

/// Channel service
/// Declares a service which provides a single channel connection between the
/// host and client in either direction.
/// 
/// ports:
///   from_host -> channel<any>
///   to_host <- channel<any>
class ChannelServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// A zlib-compressed JSON manifest
class CompressedManifestOp;

} // namespace circt::esi
namespace circt::esi {

/// Co-simulation endpoint receiving data from the host
/// A co-simulation endpoint is a connection from the simulation to some
/// outside process, usually a software application responsible for driving
/// the simulation (driver).
/// 
/// It is uni-directional, in this case receiving data from the host for the
/// simulation.
/// 
/// NOTE: $id MUST be unique across all endpoints at simulation runtime.
class CosimFromHostEndpointOp;

} // namespace circt::esi
namespace circt::esi {

/// Co-simulation endpoint sending data to the host.
/// A co-simulation endpoint is a connection from the simulation to some
/// outside process, usually a software application responsible for driving
/// the simulation (driver).
/// 
/// It is uni-directional, in this case sending data from the simulation to the
/// host.
/// 
/// NOTE: $id MUST be unique across all endpoints at simulation runtime.
class CosimToHostEndpointOp;

} // namespace circt::esi
namespace circt::esi {

/// An ESI service interface declaration
/// A declaration of an ESI service interface. Defines a contract between a
/// service provider and its clients.
/// 
/// Example:
/// 
/// ```mlir
/// esi.service.decl @HostComms {
///   esi.service.port send : !esi.bundle<[!esi.any from "send"]>
///   esi.service.port recieve : !esi.channel<[i8 to "recv"]>
/// }
/// ```
class CustomServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// Inputs become input ports when the module is lowered
/// To create input ports when lowering a pure module op into an HWModuleOp, use
/// this op. This op is typically created by a service implementation generator.
/// 
/// If two 'input' ops exist in the same block, the names match, and the type
/// matches they'll become one port during lowering. Two or more may not exist
/// with the same name and different types. Useful for 'clk' and 'rst'.
class ESIPureModuleInputOp;

} // namespace circt::esi
namespace circt::esi {

/// ESI pure module
/// A module containing only ESI channels and modules with only ESI ports. All
/// non-local connectivity is done through ESI services. If this module is the
/// top level in the design, then the design's actual top level ports are
/// defined by a BSP.
/// 
/// Useful on its own for simulation and BSPs which don't define a top-level.
class ESIPureModuleOp;

} // namespace circt::esi
namespace circt::esi {

/// Outputs become output ports when the module is lowered
/// To create output ports when lowering a pure module op into an HWModuleOp, use
/// this op. This op is typically created by a service implementation generator.
/// 
/// Two 'output' ops with the same name cannot exist in the same block.
class ESIPureModuleOutputOp;

} // namespace circt::esi
namespace circt::esi {

/// Params become module parameters when the module is lowered
/// Allows attaching parameters to modules which become HW module parameters
/// when lowering. Currently, they are ignored. Some low-level BSPs instantiate
/// modules with parameters. This allows the modules produced to accept
/// parameters so those BSPs can instantiate them.
class ESIPureModuleParamOp;

} // namespace circt::esi
namespace circt::esi {

/// A FIFO with ESI channel connections
/// A FIFO is a first-in-first-out buffer. This operation is a simple FIFO
/// which can be used to connect two ESI channels. The ESI channels MUST have
/// FIFO signaling semantics.
class FIFOOp;

} // namespace circt::esi
namespace circt::esi {

/// Function service
/// Declares a service which provides a function call interface to a client.
/// 
/// Ports:
///   to_client call(args: any) -> result: any
///     Client exposes a function call interface to the user and does not allow
///     out-of-order returns.
/// 
///   TODO: ports for out-of-order returns
class FuncServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// Host memory service
/// Declares a service to read/write host memory. Used for DMA services. Must be
/// implemented by a BSP.
class HostMemServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// MMIO service
/// Declares a service to be backed by a MMIO interface, which is platform
/// dependent. Must be implemented by a BSP.
class MMIOServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// An op which never produces messages.
class NullSourceOp;

} // namespace circt::esi
namespace circt::esi {

/// pack channels into a bundle
class PackBundleOp;

} // namespace circt::esi
namespace circt::esi {

/// An elastic buffer stage.
/// An individual elastic pipeline register. Generally lowered to from a
/// ChannelBuffer ('buffer'), though can be inserted anywhere to add an
/// additional pipeline stage. Adding individually could be useful for
/// late-pass latency balancing.
class PipelineStageOp;

} // namespace circt::esi
namespace circt::esi {

/// Random access memory service
/// Declares a service which is backed by a memory of some sort. Allows random
/// access of the inner elements.
/// 
/// Ports:
///   read(address: clog2(depth)) -> data: innerType
///   write({address: clog2(depth), data: innerType}) -> done: i0
/// 
/// Users can ensure R/W ordering by waiting for the write "done" message before
/// issuing a potentially dependant read. Ordering of R/W messages in flight is
/// undefined.
class RandomAccessMemoryDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// Request a connection to receive data
class RequestConnectionOp;

} // namespace circt::esi
namespace circt::esi {

/// An ESI service bundle being received by the client
class ServiceDeclPortOp;

} // namespace circt::esi
namespace circt::esi {

/// Details of a service implementation client connection
/// A record containing all the necessary details of how to connect to a client
/// which the parent service record is servicing. Emitted on a per-client bundle
/// basis. There shall be at most on of these records in the entire manifest for
/// a particular client.
class ServiceImplClientRecordOp;

} // namespace circt::esi
namespace circt::esi {

/// Record of a service implementation
/// A record of a service implementation. Optionally emitted by the service
/// implementation. Contains information necessary to connect to the service and
/// service clients.
class ServiceImplRecordOp;

} // namespace circt::esi
namespace circt::esi {

/// The canonical form of a connection request
class ServiceImplementConnReqOp;

} // namespace circt::esi
namespace circt::esi {

/// Request for a service to be implemented
/// The connect services pass replaces `service.instance`s with this op. The
/// `portReqs` region is the set of connection requests which need to be
/// implemented for this service instance. Channels to/from the requests have
/// been added to the operands/results of this op and consumers/producers have
/// been redirected.
/// 
/// Some other pass or frontend is expected to replace this op with an actual
/// implementation.
class ServiceImplementReqOp;

} // namespace circt::esi
namespace circt::esi {

/// Instantiate a server module
/// Instantiate a service adhering to a service declaration interface.
/// 
/// A pass collects all of the connection requests to the service this op
/// implements from the containing modules' descendants (in the instance
/// hierarchy). It bubbles them all up to the module containing this op,
/// creating the necessary ESI channel ports, groups them appropriately, then
/// replaces this op with a `service.impl_req`.
/// 
/// If 'service_symbol' isn't specified, this instance will be used to implement
/// all of the service requests which get surfaced to here. This option is
/// generally used at the top level to specify host connectivity.
/// 
/// Since implementing the server will usually need "normal" I/O, `inputs` and
/// `results` act like normal `hw.instance` ports.
/// 
/// $identifier is used by frontends to specify or remember the type of
/// implementation to use for this service.
class ServiceInstanceOp;

} // namespace circt::esi
namespace circt::esi {

/// Record of a service request
/// A record of a service request, including the requestor, the service
/// requested, and the parameters of the request. Emitted before connecting the
/// service to preserve metadata about the original request.
class ServiceRequestRecordOp;

} // namespace circt::esi
namespace circt::esi {

/// Get the data and transaction signal from a channel
/// A snoop that observes when a transaction occurs on a channel and provides
/// the data being transmitted. The transaction signal indicates when data is
/// actually being transferred on the channel, regardless of the underlying
/// signaling protocol (ValidReady or FIFO). Like other snoop operations, this
/// does not count as another user of the channel. Useful for monitoring data
/// flow and debugging.
class SnoopTransactionOp;

} // namespace circt::esi
namespace circt::esi {

/// Get the valid, ready, and data signals from a channel
/// A snoop allows one to combinationally observe a channel's internal signals.
/// It does not count as another user of the channel. Useful for constructing
/// control logic which can be combinationally driven. Also potentially useful
/// for debugging.
class SnoopValidReadyOp;

} // namespace circt::esi
namespace circt::esi {

/// Constant values associated with a symbol
class SymbolConstantsOp;

} // namespace circt::esi
namespace circt::esi {

/// Metadata about a symbol
/// Metadata about a symbol, including its name, repository, commit hash,
/// version, and summary. All are optional, but strongly encouraged. Any
/// additional metadata which users wish to attach should go as discardable
/// attributes.
class SymbolMetadataOp;

} // namespace circt::esi
namespace circt::esi {

/// Telemetry service
/// Declares a service to send telemetry data. Has one port 'report' for
/// something to request telemetry data (via a 'get' channel to the client and a
/// 'data' channel for the return value).
class TelemetryServiceDeclOp;

} // namespace circt::esi
namespace circt::esi {

/// unpack channels from a bundle
class UnpackBundleOp;

} // namespace circt::esi
namespace circt::esi {

/// Unwrap a value from an ESI port into a FIFO interface
class UnwrapFIFOOp;

} // namespace circt::esi
namespace circt::esi {

/// Unwrap an SV interface from an ESI port
/// Unwrap an ESI channel into a SystemVerilog interface containing valid,
/// ready, and data signals.
class UnwrapSVInterfaceOp;

} // namespace circt::esi
namespace circt::esi {

/// Unwrap a value from a valid-only ESI port
/// Unwrap a ValidOnly channel into data and valid signals. There is no
/// ready input since ValidOnly has no backpressure.
class UnwrapValidOnlyOp;

} // namespace circt::esi
namespace circt::esi {

/// Unwrap a value from an ESI port
/// Unwrapping a value allows operations on the contained value. Unwrap the
/// channel along with a ready signal that you generate. Result is the data
/// along with a valid signal.
class UnwrapValidReadyOp;

} // namespace circt::esi
namespace circt::esi {

/// unwrap a data window into a union
class UnwrapWindow;

} // namespace circt::esi
namespace circt::esi {

/// Wrap a value into an ESI port with FIFO signaling
class WrapFIFOOp;

} // namespace circt::esi
namespace circt::esi {

/// Wrap an SV interface into an ESI port
/// Wrap a SystemVerilog interface into an ESI channel. Interface MUST look
/// like an interface produced by ESI meaning it MUST contain valid, ready,
/// and data signals. Any other signals will be discarded.
class WrapSVInterfaceOp;

} // namespace circt::esi
namespace circt::esi {

/// Wrap a value into an ESI port with valid-only signaling
/// Wrap data with a valid bit into a ValidOnly ESI channel. Unlike
/// ValidReady, there is no ready backpressure signal. The sender fires
/// data whenever valid is asserted; the receiver must accept it.
class WrapValidOnlyOp;

} // namespace circt::esi
namespace circt::esi {

/// Wrap a value into an ESI port
/// Wrapping a value into an ESI port type allows modules to send values down
/// an ESI port. Wrap data with valid bit, result is the ESI channel and the
/// ready signal from the other end of the channel.
class WrapValidReadyOp;

} // namespace circt::esi
namespace circt::esi {

/// wrap a union into a data window
class WrapWindow;

} // namespace circt::esi
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::AppIDHierNodeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AppIDHierNodeOpGenericAdaptorBase {
public:
  struct Properties {
    using appIDTy = ::circt::esi::AppIDAttr;
    appIDTy appID;

    auto getAppID() const {
      auto &propStorage = this->appID;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setAppID(const ::circt::esi::AppIDAttr &propValue) {
      this->appID = propValue;
    }
    using moduleRefTy = ::mlir::FlatSymbolRefAttr;
    moduleRefTy moduleRef;

    auto getModuleRef() const {
      auto &propStorage = this->moduleRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModuleRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->moduleRef = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.appID == this->appID &&
        rhs.moduleRef == this->moduleRef &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AppIDHierNodeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.hier_node", odsAttrs.getContext());
  }

  AppIDHierNodeOpGenericAdaptorBase(AppIDHierNodeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::AppIDAttr getAppIDAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
    return attr;
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getModuleRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleRef);
    return attr;
  }

  ::llvm::StringRef getModuleRef();
  ::mlir::Region &getChildren() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AppIDHierNodeOpGenericAdaptor : public detail::AppIDHierNodeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AppIDHierNodeOpGenericAdaptorBase;
public:
  AppIDHierNodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AppIDHierNodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AppIDHierNodeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AppIDHierNodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AppIDHierNodeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AppIDHierNodeOpGenericAdaptor(RangeT values, const AppIDHierNodeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AppIDHierNodeOp, typename = std::enable_if_t<std::is_same_v<LateInst, AppIDHierNodeOp>>>
  AppIDHierNodeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AppIDHierNodeOpAdaptor : public AppIDHierNodeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AppIDHierNodeOpGenericAdaptor::AppIDHierNodeOpGenericAdaptor;
  AppIDHierNodeOpAdaptor(AppIDHierNodeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AppIDHierNodeOp : public ::mlir::Op<AppIDHierNodeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<circt::esi::AppIDHierRootOp, circt::esi::AppIDHierNodeOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AppIDHierNodeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AppIDHierNodeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("appID"), ::llvm::StringRef("moduleRef")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAppIDAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAppIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.hier_node");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getChildren() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::AppIDAttr getAppIDAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getModuleRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleRef);
  }

  ::llvm::StringRef getModuleRef();
  void setAppIDAttr(::circt::esi::AppIDAttr attr) {
    getProperties().appID = attr;
  }

  void setModuleRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().moduleRef = attr;
  }

  void setModuleRef(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AppIDHierNodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AppIDHierNodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::AppIDHierNodeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::AppIDHierNodeOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::AppIDHierRootOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AppIDHierRootOpGenericAdaptorBase {
public:
  struct Properties {
    using topModuleRefTy = ::mlir::FlatSymbolRefAttr;
    topModuleRefTy topModuleRef;

    auto getTopModuleRef() const {
      auto &propStorage = this->topModuleRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setTopModuleRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->topModuleRef = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.topModuleRef == this->topModuleRef &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AppIDHierRootOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.hier_root", odsAttrs.getContext());
  }

  AppIDHierRootOpGenericAdaptorBase(AppIDHierRootOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getTopModuleRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().topModuleRef);
    return attr;
  }

  ::llvm::StringRef getTopModuleRef();
  ::mlir::Region &getChildren() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class AppIDHierRootOpGenericAdaptor : public detail::AppIDHierRootOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AppIDHierRootOpGenericAdaptorBase;
public:
  AppIDHierRootOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AppIDHierRootOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AppIDHierRootOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AppIDHierRootOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AppIDHierRootOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AppIDHierRootOpGenericAdaptor(RangeT values, const AppIDHierRootOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AppIDHierRootOp, typename = std::enable_if_t<std::is_same_v<LateInst, AppIDHierRootOp>>>
  AppIDHierRootOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AppIDHierRootOpAdaptor : public AppIDHierRootOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AppIDHierRootOpGenericAdaptor::AppIDHierRootOpGenericAdaptor;
  AppIDHierRootOpAdaptor(AppIDHierRootOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AppIDHierRootOp : public ::mlir::Op<AppIDHierRootOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AppIDHierRootOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AppIDHierRootOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("topModuleRef")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getTopModuleRefAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getTopModuleRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.hier_root");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getChildren() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getTopModuleRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().topModuleRef);
  }

  ::llvm::StringRef getTopModuleRef();
  void setTopModuleRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().topModuleRef = attr;
  }

  void setTopModuleRef(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr topModuleRef);
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr topModuleRef);
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr topModuleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef);
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef);
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef topModuleRef);
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef topModuleRef);
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef topModuleRef);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef);
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef);
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AppIDHierRootOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AppIDHierRootOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::AppIDHierRootOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::AppIDHierRootOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CallServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CallServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CallServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.call", odsAttrs.getContext());
  }

  CallServiceDeclOpGenericAdaptorBase(CallServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class CallServiceDeclOpGenericAdaptor : public detail::CallServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CallServiceDeclOpGenericAdaptorBase;
public:
  CallServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CallServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CallServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CallServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CallServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CallServiceDeclOpGenericAdaptor(RangeT values, const CallServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CallServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, CallServiceDeclOp>>>
  CallServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CallServiceDeclOpAdaptor : public CallServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CallServiceDeclOpGenericAdaptor::CallServiceDeclOpGenericAdaptor;
  CallServiceDeclOpAdaptor(CallServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CallServiceDeclOp : public ::mlir::Op<CallServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CallServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CallServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<CallServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<CallServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.call");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::optional<StringRef> getTypeName() { return "esi.service.std.call"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::CallServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::CallServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ChannelBufferOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ChannelBufferOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using stagesTy = ::mlir::IntegerAttr;
    stagesTy stages;

    auto getStages() const {
      auto &propStorage = this->stages;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setStages(const ::mlir::IntegerAttr &propValue) {
      this->stages = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        rhs.stages == this->stages &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ChannelBufferOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.buffer", odsAttrs.getContext());
  }

  ChannelBufferOpGenericAdaptorBase(ChannelBufferOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getStagesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().stages);
    return attr;
  }

  ::std::optional<uint64_t> getStages();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class ChannelBufferOpGenericAdaptor : public detail::ChannelBufferOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ChannelBufferOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
public:
  ChannelBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ChannelBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ChannelBufferOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ChannelBufferOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ChannelBufferOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ChannelBufferOpGenericAdaptor(RangeT values, const ChannelBufferOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ChannelBufferOp, typename = std::enable_if_t<std::is_same_v<LateInst, ChannelBufferOp>>>
  ChannelBufferOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getInput() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ChannelBufferOpAdaptor : public ChannelBufferOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ChannelBufferOpGenericAdaptor::ChannelBufferOpGenericAdaptor;
  ChannelBufferOpAdaptor(ChannelBufferOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ChannelBufferOp : public ::mlir::Op<ChannelBufferOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::esi::ChannelOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ChannelBufferOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ChannelBufferOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<ChannelBufferOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("stages")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStagesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStagesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.buffer");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getStagesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().stages);
  }

  ::std::optional<uint64_t> getStages();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  void setStagesAttr(::mlir::IntegerAttr attr) {
    getProperties().stages = attr;
  }

  void setStages(::std::optional<uint64_t> attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeStagesAttr() {
      auto attr = getProperties().stages;
      getProperties().stages = {};
      return attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static ChannelBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static ChannelBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static ChannelBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static ChannelBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChannelBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChannelBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChannelBufferOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChannelBufferOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ChannelBufferOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ChannelBufferOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ChannelServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ChannelServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ChannelServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.channel", odsAttrs.getContext());
  }

  ChannelServiceDeclOpGenericAdaptorBase(ChannelServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class ChannelServiceDeclOpGenericAdaptor : public detail::ChannelServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ChannelServiceDeclOpGenericAdaptorBase;
public:
  ChannelServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ChannelServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ChannelServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ChannelServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ChannelServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ChannelServiceDeclOpGenericAdaptor(RangeT values, const ChannelServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ChannelServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, ChannelServiceDeclOp>>>
  ChannelServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ChannelServiceDeclOpAdaptor : public ChannelServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ChannelServiceDeclOpGenericAdaptor::ChannelServiceDeclOpGenericAdaptor;
  ChannelServiceDeclOpAdaptor(ChannelServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ChannelServiceDeclOp : public ::mlir::Op<ChannelServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ChannelServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ChannelServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<ChannelServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<ChannelServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.channel");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChannelServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChannelServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::optional<StringRef> getTypeName() { return "esi.service.std.channel"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ChannelServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ChannelServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CompressedManifestOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompressedManifestOpGenericAdaptorBase {
public:
  struct Properties {
    using compressedManifestTy = ::circt::esi::BlobAttr;
    compressedManifestTy compressedManifest;

    auto getCompressedManifest() const {
      auto &propStorage = this->compressedManifest;
      return ::llvm::cast<::circt::esi::BlobAttr>(propStorage);
    }
    void setCompressedManifest(const ::circt::esi::BlobAttr &propValue) {
      this->compressedManifest = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.compressedManifest == this->compressedManifest &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CompressedManifestOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.compressed", odsAttrs.getContext());
  }

  CompressedManifestOpGenericAdaptorBase(CompressedManifestOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::BlobAttr getCompressedManifestAttr() {
    auto attr = ::llvm::cast<::circt::esi::BlobAttr>(getProperties().compressedManifest);
    return attr;
  }

  ::circt::esi::BlobAttr getCompressedManifest();
};

} // namespace detail
template <typename RangeT>
class CompressedManifestOpGenericAdaptor : public detail::CompressedManifestOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompressedManifestOpGenericAdaptorBase;
public:
  CompressedManifestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompressedManifestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CompressedManifestOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompressedManifestOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CompressedManifestOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompressedManifestOpGenericAdaptor(RangeT values, const CompressedManifestOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompressedManifestOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompressedManifestOp>>>
  CompressedManifestOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompressedManifestOpAdaptor : public CompressedManifestOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompressedManifestOpGenericAdaptor::CompressedManifestOpGenericAdaptor;
  CompressedManifestOpAdaptor(CompressedManifestOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompressedManifestOp : public ::mlir::Op<CompressedManifestOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompressedManifestOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompressedManifestOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("compressedManifest")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCompressedManifestAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCompressedManifestAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.compressed");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::BlobAttr getCompressedManifestAttr() {
    return ::llvm::cast<::circt::esi::BlobAttr>(getProperties().compressedManifest);
  }

  ::circt::esi::BlobAttr getCompressedManifest();
  void setCompressedManifestAttr(::circt::esi::BlobAttr attr) {
    getProperties().compressedManifest = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::BlobAttr compressedManifest);
  static CompressedManifestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::BlobAttr compressedManifest);
  static CompressedManifestOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::BlobAttr compressedManifest);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest);
  static CompressedManifestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest);
  static CompressedManifestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressedManifestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompressedManifestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressedManifestOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompressedManifestOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::CompressedManifestOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::CompressedManifestOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CosimFromHostEndpointOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CosimFromHostEndpointOpGenericAdaptorBase {
public:
  struct Properties {
    using idTy = ::mlir::StringAttr;
    idTy id;

    auto getId() const {
      auto &propStorage = this->id;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setId(const ::mlir::StringAttr &propValue) {
      this->id = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.id == this->id &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CosimFromHostEndpointOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.cosim.from_host", odsAttrs.getContext());
  }

  CosimFromHostEndpointOpGenericAdaptorBase(CosimFromHostEndpointOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getIdAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().id);
    return attr;
  }

  ::llvm::StringRef getId();
};

} // namespace detail
template <typename RangeT>
class CosimFromHostEndpointOpGenericAdaptor : public detail::CosimFromHostEndpointOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CosimFromHostEndpointOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
public:
  CosimFromHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CosimFromHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CosimFromHostEndpointOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CosimFromHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CosimFromHostEndpointOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CosimFromHostEndpointOpGenericAdaptor(RangeT values, const CosimFromHostEndpointOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CosimFromHostEndpointOp, typename = std::enable_if_t<std::is_same_v<LateInst, CosimFromHostEndpointOp>>>
  CosimFromHostEndpointOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CosimFromHostEndpointOpAdaptor : public CosimFromHostEndpointOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CosimFromHostEndpointOpGenericAdaptor::CosimFromHostEndpointOpGenericAdaptor;
  CosimFromHostEndpointOpAdaptor(CosimFromHostEndpointOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CosimFromHostEndpointOp : public ::mlir::Op<CosimFromHostEndpointOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CosimFromHostEndpointOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CosimFromHostEndpointOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("id")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.cosim.from_host");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getFromHost() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getIdAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().id);
  }

  ::llvm::StringRef getId();
  void setIdAttr(::mlir::StringAttr attr) {
    getProperties().id = attr;
  }

  void setId(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CosimFromHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CosimFromHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::CosimFromHostEndpointOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::CosimFromHostEndpointOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CosimToHostEndpointOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CosimToHostEndpointOpGenericAdaptorBase {
public:
  struct Properties {
    using idTy = ::mlir::StringAttr;
    idTy id;

    auto getId() const {
      auto &propStorage = this->id;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setId(const ::mlir::StringAttr &propValue) {
      this->id = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.id == this->id &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CosimToHostEndpointOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.cosim.to_host", odsAttrs.getContext());
  }

  CosimToHostEndpointOpGenericAdaptorBase(CosimToHostEndpointOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getIdAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().id);
    return attr;
  }

  ::llvm::StringRef getId();
};

} // namespace detail
template <typename RangeT>
class CosimToHostEndpointOpGenericAdaptor : public detail::CosimToHostEndpointOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CosimToHostEndpointOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_toHost = 2;
public:
  CosimToHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CosimToHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CosimToHostEndpointOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CosimToHostEndpointOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CosimToHostEndpointOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CosimToHostEndpointOpGenericAdaptor(RangeT values, const CosimToHostEndpointOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CosimToHostEndpointOp, typename = std::enable_if_t<std::is_same_v<LateInst, CosimToHostEndpointOp>>>
  CosimToHostEndpointOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getToHost() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CosimToHostEndpointOpAdaptor : public CosimToHostEndpointOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CosimToHostEndpointOpGenericAdaptor::CosimToHostEndpointOpGenericAdaptor;
  CosimToHostEndpointOpAdaptor(CosimToHostEndpointOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CosimToHostEndpointOp : public ::mlir::Op<CosimToHostEndpointOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CosimToHostEndpointOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CosimToHostEndpointOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_toHost = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("id")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.cosim.to_host");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getToHost() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getToHostMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getIdAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().id);
  }

  ::llvm::StringRef getId();
  void setIdAttr(::mlir::StringAttr attr) {
    getProperties().id = attr;
  }

  void setId(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CosimToHostEndpointOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CosimToHostEndpointOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::CosimToHostEndpointOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::CosimToHostEndpointOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CustomServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CustomServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CustomServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.decl", odsAttrs.getContext());
  }

  CustomServiceDeclOpGenericAdaptorBase(CustomServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::Region &getPorts() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class CustomServiceDeclOpGenericAdaptor : public detail::CustomServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CustomServiceDeclOpGenericAdaptorBase;
public:
  CustomServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CustomServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CustomServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CustomServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CustomServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CustomServiceDeclOpGenericAdaptor(RangeT values, const CustomServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CustomServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, CustomServiceDeclOp>>>
  CustomServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CustomServiceDeclOpAdaptor : public CustomServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CustomServiceDeclOpGenericAdaptor::CustomServiceDeclOpGenericAdaptor;
  CustomServiceDeclOpAdaptor(CustomServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CustomServiceDeclOp : public ::mlir::Op<CustomServiceDeclOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CustomServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CustomServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<CustomServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<CustomServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.decl");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getPorts() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CustomServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CustomServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::CustomServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::CustomServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleInputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ESIPureModuleInputOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ESIPureModuleInputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.pure_module.input", odsAttrs.getContext());
  }

  ESIPureModuleInputOpGenericAdaptorBase(ESIPureModuleInputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
};

} // namespace detail
template <typename RangeT>
class ESIPureModuleInputOpGenericAdaptor : public detail::ESIPureModuleInputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ESIPureModuleInputOpGenericAdaptorBase;
public:
  ESIPureModuleInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ESIPureModuleInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ESIPureModuleInputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ESIPureModuleInputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ESIPureModuleInputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ESIPureModuleInputOpGenericAdaptor(RangeT values, const ESIPureModuleInputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ESIPureModuleInputOp, typename = std::enable_if_t<std::is_same_v<LateInst, ESIPureModuleInputOp>>>
  ESIPureModuleInputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ESIPureModuleInputOpAdaptor : public ESIPureModuleInputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ESIPureModuleInputOpGenericAdaptor::ESIPureModuleInputOpGenericAdaptor;
  ESIPureModuleInputOpAdaptor(ESIPureModuleInputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ESIPureModuleInputOp : public ::mlir::Op<ESIPureModuleInputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ESIPureModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ESIPureModuleInputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ESIPureModuleInputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.pure_module.input");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::StringAttr name);
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::StringAttr name);
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name);
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name);
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::llvm::StringRef name);
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::llvm::StringRef name);
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleInputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleInputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleInputOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleInputOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ESIPureModuleOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ESIPureModuleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.pure_module", odsAttrs.getContext());
  }

  ESIPureModuleOpGenericAdaptorBase(ESIPureModuleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ESIPureModuleOpGenericAdaptor : public detail::ESIPureModuleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ESIPureModuleOpGenericAdaptorBase;
public:
  ESIPureModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ESIPureModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ESIPureModuleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ESIPureModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ESIPureModuleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ESIPureModuleOpGenericAdaptor(RangeT values, const ESIPureModuleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ESIPureModuleOp, typename = std::enable_if_t<std::is_same_v<LateInst, ESIPureModuleOp>>>
  ESIPureModuleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ESIPureModuleOpAdaptor : public ESIPureModuleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ESIPureModuleOpGenericAdaptor::ESIPureModuleOpGenericAdaptor;
  ESIPureModuleOpAdaptor(ESIPureModuleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ESIPureModuleOp : public ::mlir::Op<ESIPureModuleOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::RegionKindInterface::Trait, circt::hw::PortList::Trait, ::circt::igraph::ModuleOpInterface::Trait, circt::hw::HWModuleLike::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ESIPureModuleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ESIPureModuleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.pure_module");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getBody() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<::circt::hw::PortInfo> getPortList();
  ::circt::hw::PortInfo getPort(size_t idx);
  size_t getPortIdForInputId(size_t idx);
  size_t getPortIdForOutputId(size_t idx);
  size_t getNumPorts();
  size_t getNumInputPorts();
  size_t getNumOutputPorts();
  ::circt::hw::ModuleType getHWModuleType();
  ArrayRef<Attribute> getAllPortAttrs();
  void setAllPortAttrs(ArrayRef<Attribute> attrs);
  void removeAllPortAttrs();
  SmallVector<Location> getAllPortLocs();
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);
  void setHWModuleType(::circt::hw::ModuleType type);
  void setAllPortNames(ArrayRef<Attribute> names);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph;}

};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleOutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ESIPureModuleOutputOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ESIPureModuleOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.pure_module.output", odsAttrs.getContext());
  }

  ESIPureModuleOutputOpGenericAdaptorBase(ESIPureModuleOutputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
};

} // namespace detail
template <typename RangeT>
class ESIPureModuleOutputOpGenericAdaptor : public detail::ESIPureModuleOutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ESIPureModuleOutputOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  ESIPureModuleOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ESIPureModuleOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ESIPureModuleOutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ESIPureModuleOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ESIPureModuleOutputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ESIPureModuleOutputOpGenericAdaptor(RangeT values, const ESIPureModuleOutputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ESIPureModuleOutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, ESIPureModuleOutputOp>>>
  ESIPureModuleOutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ESIPureModuleOutputOpAdaptor : public ESIPureModuleOutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ESIPureModuleOutputOpGenericAdaptor::ESIPureModuleOutputOpGenericAdaptor;
  ESIPureModuleOutputOpAdaptor(ESIPureModuleOutputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ESIPureModuleOutputOp : public ::mlir::Op<ESIPureModuleOutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<ESIPureModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ESIPureModuleOutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ESIPureModuleOutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.pure_module.output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value);
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleOutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleOutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleOutputOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleOutputOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleParamOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ESIPureModuleParamOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        rhs.type == this->type &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ESIPureModuleParamOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.pure_module.param", odsAttrs.getContext());
  }

  ESIPureModuleParamOpGenericAdaptorBase(ESIPureModuleParamOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
};

} // namespace detail
template <typename RangeT>
class ESIPureModuleParamOpGenericAdaptor : public detail::ESIPureModuleParamOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ESIPureModuleParamOpGenericAdaptorBase;
public:
  ESIPureModuleParamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ESIPureModuleParamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ESIPureModuleParamOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ESIPureModuleParamOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ESIPureModuleParamOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ESIPureModuleParamOpGenericAdaptor(RangeT values, const ESIPureModuleParamOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ESIPureModuleParamOp, typename = std::enable_if_t<std::is_same_v<LateInst, ESIPureModuleParamOp>>>
  ESIPureModuleParamOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ESIPureModuleParamOpAdaptor : public ESIPureModuleParamOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ESIPureModuleParamOpGenericAdaptor::ESIPureModuleParamOpGenericAdaptor;
  ESIPureModuleParamOpAdaptor(ESIPureModuleParamOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ESIPureModuleParamOp : public ::mlir::Op<ESIPureModuleParamOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ESIPureModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ESIPureModuleParamOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ESIPureModuleParamOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.pure_module.param");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Type type);
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Type type);
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Type type);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type);
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type);
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleParamOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ESIPureModuleParamOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleParamOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleParamOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::FIFOOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FIFOOpGenericAdaptorBase {
public:
  struct Properties {
    using depthTy = ::mlir::IntegerAttr;
    depthTy depth;

    auto getDepth() const {
      auto &propStorage = this->depth;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDepth(const ::mlir::IntegerAttr &propValue) {
      this->depth = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.depth == this->depth &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FIFOOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.fifo", odsAttrs.getContext());
  }

  FIFOOpGenericAdaptorBase(FIFOOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDepthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
    return attr;
  }

  uint64_t getDepth();
};

} // namespace detail
template <typename RangeT>
class FIFOOpGenericAdaptor : public detail::FIFOOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FIFOOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
public:
  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FIFOOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FIFOOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FIFOOpGenericAdaptor(RangeT values, const FIFOOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FIFOOp, typename = std::enable_if_t<std::is_same_v<LateInst, FIFOOp>>>
  FIFOOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getInput() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FIFOOpAdaptor : public FIFOOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FIFOOpGenericAdaptor::FIFOOpGenericAdaptor;
  FIFOOpAdaptor(FIFOOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FIFOOp : public ::mlir::Op<FIFOOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FIFOOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FIFOOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depth")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDepthAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDepthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.fifo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getDepthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
  }

  uint64_t getDepth();
  void setDepthAttr(::mlir::IntegerAttr attr) {
    getProperties().depth = attr;
  }

  void setDepth(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::FIFOOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::FIFOOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::FuncServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FuncServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FuncServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.func", odsAttrs.getContext());
  }

  FuncServiceDeclOpGenericAdaptorBase(FuncServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class FuncServiceDeclOpGenericAdaptor : public detail::FuncServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FuncServiceDeclOpGenericAdaptorBase;
public:
  FuncServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FuncServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FuncServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FuncServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FuncServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FuncServiceDeclOpGenericAdaptor(RangeT values, const FuncServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FuncServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, FuncServiceDeclOp>>>
  FuncServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FuncServiceDeclOpAdaptor : public FuncServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FuncServiceDeclOpGenericAdaptor::FuncServiceDeclOpGenericAdaptor;
  FuncServiceDeclOpAdaptor(FuncServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FuncServiceDeclOp : public ::mlir::Op<FuncServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FuncServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FuncServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<FuncServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<FuncServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.func");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FuncServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FuncServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::optional<StringRef> getTypeName() { return "esi.service.std.func"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::FuncServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::FuncServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::HostMemServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HostMemServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  HostMemServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.hostmem", odsAttrs.getContext());
  }

  HostMemServiceDeclOpGenericAdaptorBase(HostMemServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class HostMemServiceDeclOpGenericAdaptor : public detail::HostMemServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HostMemServiceDeclOpGenericAdaptorBase;
public:
  HostMemServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HostMemServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HostMemServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HostMemServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HostMemServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HostMemServiceDeclOpGenericAdaptor(RangeT values, const HostMemServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HostMemServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, HostMemServiceDeclOp>>>
  HostMemServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class HostMemServiceDeclOpAdaptor : public HostMemServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HostMemServiceDeclOpGenericAdaptor::HostMemServiceDeclOpGenericAdaptor;
  HostMemServiceDeclOpAdaptor(HostMemServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HostMemServiceDeclOp : public ::mlir::Op<HostMemServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HostMemServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HostMemServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<HostMemServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<HostMemServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.hostmem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostMemServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HostMemServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  ServicePortInfo readPortInfo();
  ServicePortInfo writePortInfo();
  std::optional<StringRef> getTypeName() { return "esi.service.std.hostmem"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::HostMemServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::HostMemServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::MMIOServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MMIOServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MMIOServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.mmio", odsAttrs.getContext());
  }

  MMIOServiceDeclOpGenericAdaptorBase(MMIOServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class MMIOServiceDeclOpGenericAdaptor : public detail::MMIOServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MMIOServiceDeclOpGenericAdaptorBase;
public:
  MMIOServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MMIOServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MMIOServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MMIOServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MMIOServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MMIOServiceDeclOpGenericAdaptor(RangeT values, const MMIOServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MMIOServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, MMIOServiceDeclOp>>>
  MMIOServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MMIOServiceDeclOpAdaptor : public MMIOServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MMIOServiceDeclOpGenericAdaptor::MMIOServiceDeclOpGenericAdaptor;
  MMIOServiceDeclOpAdaptor(MMIOServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MMIOServiceDeclOp : public ::mlir::Op<MMIOServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MMIOServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MMIOServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<MMIOServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<MMIOServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.mmio");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MMIOServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MMIOServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::optional<StringRef> getTypeName() { return "esi.service.std.mmio"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::MMIOServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::MMIOServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::NullSourceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NullSourceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NullSourceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.null", odsAttrs.getContext());
  }

  NullSourceOpGenericAdaptorBase(NullSourceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class NullSourceOpGenericAdaptor : public detail::NullSourceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NullSourceOpGenericAdaptorBase;
public:
  NullSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NullSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : NullSourceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NullSourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NullSourceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NullSourceOpGenericAdaptor(RangeT values, const NullSourceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NullSourceOp, typename = std::enable_if_t<std::is_same_v<LateInst, NullSourceOp>>>
  NullSourceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class NullSourceOpAdaptor : public NullSourceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NullSourceOpGenericAdaptor::NullSourceOpGenericAdaptor;
  NullSourceOpAdaptor(NullSourceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NullSourceOp : public ::mlir::Op<NullSourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NullSourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NullSourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.null");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type out);
  static NullSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type out);
  static NullSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type out);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static NullSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static NullSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NullSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NullSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NullSourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NullSourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::NullSourceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::PackBundleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PackBundleOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PackBundleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.bundle.pack", odsAttrs.getContext());
  }

  PackBundleOpGenericAdaptorBase(PackBundleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class PackBundleOpGenericAdaptor : public detail::PackBundleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PackBundleOpGenericAdaptorBase;
  static constexpr int odsIndex_toChannels = 0;
public:
  PackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PackBundleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PackBundleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PackBundleOpGenericAdaptor(RangeT values, const PackBundleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PackBundleOp, typename = std::enable_if_t<std::is_same_v<LateInst, PackBundleOp>>>
  PackBundleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getToChannels() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PackBundleOpAdaptor : public PackBundleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PackBundleOpGenericAdaptor::PackBundleOpGenericAdaptor;
  PackBundleOpAdaptor(PackBundleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PackBundleOp : public ::mlir::Op<PackBundleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PackBundleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PackBundleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_toChannels = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<PackBundleOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PackBundleOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PackBundleOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.bundle.pack");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getToChannels() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getToChannelsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelBundleType> getBundle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelBundleType>>(*getODSResults(0).begin());
  }

  ::mlir::Operation::result_range getFromChannels() {
    return getODSResults(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ChannelBundleType bundleType, mlir::ValueRange toChannels);
  static PackBundleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ChannelBundleType bundleType, mlir::ValueRange toChannels);
  static PackBundleOp create(::mlir::ImplicitLocOpBuilder &builder, ChannelBundleType bundleType, mlir::ValueRange toChannels);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(PackBundleOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::PackBundleOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::PipelineStageOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PipelineStageOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PipelineStageOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.stage", odsAttrs.getContext());
  }

  PipelineStageOpGenericAdaptorBase(PipelineStageOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class PipelineStageOpGenericAdaptor : public detail::PipelineStageOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PipelineStageOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
public:
  PipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PipelineStageOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PipelineStageOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PipelineStageOpGenericAdaptor(RangeT values, const PipelineStageOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PipelineStageOp, typename = std::enable_if_t<std::is_same_v<LateInst, PipelineStageOp>>>
  PipelineStageOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  ValueT getInput() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PipelineStageOpAdaptor : public PipelineStageOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PipelineStageOpGenericAdaptor::PipelineStageOpGenericAdaptor;
  PipelineStageOpAdaptor(PipelineStageOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PipelineStageOp : public ::mlir::Op<PipelineStageOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::esi::ChannelOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PipelineStageOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PipelineStageOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  static constexpr int odsIndex_input = 2;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<PipelineStageOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.stage");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::PipelineStageOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::RandomAccessMemoryDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RandomAccessMemoryDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using depthTy = ::mlir::IntegerAttr;
    depthTy depth;

    auto getDepth() const {
      auto &propStorage = this->depth;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDepth(const ::mlir::IntegerAttr &propValue) {
      this->depth = propValue;
    }
    using innerTypeTy = ::mlir::TypeAttr;
    innerTypeTy innerType;

    auto getInnerType() const {
      auto &propStorage = this->innerType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setInnerType(const ::mlir::TypeAttr &propValue) {
      this->innerType = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.depth == this->depth &&
        rhs.innerType == this->innerType &&
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RandomAccessMemoryDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.mem.ram", odsAttrs.getContext());
  }

  RandomAccessMemoryDeclOpGenericAdaptorBase(RandomAccessMemoryDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getInnerTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().innerType);
    return attr;
  }

  ::mlir::Type getInnerType();
  ::mlir::IntegerAttr getDepthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
    return attr;
  }

  uint64_t getDepth();
};

} // namespace detail
template <typename RangeT>
class RandomAccessMemoryDeclOpGenericAdaptor : public detail::RandomAccessMemoryDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RandomAccessMemoryDeclOpGenericAdaptorBase;
public:
  RandomAccessMemoryDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RandomAccessMemoryDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RandomAccessMemoryDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RandomAccessMemoryDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RandomAccessMemoryDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RandomAccessMemoryDeclOpGenericAdaptor(RangeT values, const RandomAccessMemoryDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RandomAccessMemoryDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, RandomAccessMemoryDeclOp>>>
  RandomAccessMemoryDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RandomAccessMemoryDeclOpAdaptor : public RandomAccessMemoryDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RandomAccessMemoryDeclOpGenericAdaptor::RandomAccessMemoryDeclOpGenericAdaptor;
  RandomAccessMemoryDeclOpAdaptor(RandomAccessMemoryDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RandomAccessMemoryDeclOp : public ::mlir::Op<RandomAccessMemoryDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RandomAccessMemoryDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RandomAccessMemoryDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<RandomAccessMemoryDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<RandomAccessMemoryDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("depth"), ::llvm::StringRef("innerType"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDepthAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDepthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInnerTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInnerTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.mem.ram");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getInnerTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().innerType);
  }

  ::mlir::Type getInnerType();
  ::mlir::IntegerAttr getDepthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
  }

  uint64_t getDepth();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setInnerTypeAttr(::mlir::TypeAttr attr) {
    getProperties().innerType = attr;
  }

  void setInnerType(::mlir::Type attrValue);
  void setDepthAttr(::mlir::IntegerAttr attr) {
    getProperties().depth = attr;
  }

  void setDepth(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RandomAccessMemoryDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RandomAccessMemoryDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  ServicePortInfo readPortInfo();
  ServicePortInfo writePortInfo();
  static constexpr auto ReqDirChannelIdx = 0;
  static constexpr auto RespDirChannelIdx = 0;
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::RandomAccessMemoryDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::RandomAccessMemoryDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::RequestConnectionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RequestConnectionOpGenericAdaptorBase {
public:
  struct Properties {
    using appIDTy = ::circt::esi::AppIDAttr;
    appIDTy appID;

    auto getAppID() const {
      auto &propStorage = this->appID;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setAppID(const ::circt::esi::AppIDAttr &propValue) {
      this->appID = propValue;
    }
    using servicePortTy = ::circt::hw::InnerRefAttr;
    servicePortTy servicePort;

    auto getServicePort() const {
      auto &propStorage = this->servicePort;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setServicePort(const ::circt::hw::InnerRefAttr &propValue) {
      this->servicePort = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.appID == this->appID &&
        rhs.servicePort == this->servicePort &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RequestConnectionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.req", odsAttrs.getContext());
  }

  RequestConnectionOpGenericAdaptorBase(RequestConnectionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerRefAttr getServicePortAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
    return attr;
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::circt::esi::AppIDAttr getAppIDAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
    return attr;
  }

  ::circt::esi::AppIDAttr getAppID();
};

} // namespace detail
template <typename RangeT>
class RequestConnectionOpGenericAdaptor : public detail::RequestConnectionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RequestConnectionOpGenericAdaptorBase;
public:
  RequestConnectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RequestConnectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RequestConnectionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RequestConnectionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RequestConnectionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RequestConnectionOpGenericAdaptor(RangeT values, const RequestConnectionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RequestConnectionOp, typename = std::enable_if_t<std::is_same_v<LateInst, RequestConnectionOp>>>
  RequestConnectionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RequestConnectionOpAdaptor : public RequestConnectionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RequestConnectionOpGenericAdaptor::RequestConnectionOpGenericAdaptor;
  RequestConnectionOpAdaptor(RequestConnectionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RequestConnectionOp : public ::mlir::Op<RequestConnectionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelBundleType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::HasAppID::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RequestConnectionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RequestConnectionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::HasAppID::Trait<RequestConnectionOp>::getAppID;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("appID"), ::llvm::StringRef("servicePort")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAppIDAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAppIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getServicePortAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getServicePortAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.req");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelBundleType> getToClient() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelBundleType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::circt::esi::AppIDAttr getAppIDAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
  }

  ::circt::esi::AppIDAttr getAppID();
  void setServicePortAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().servicePort = attr;
  }

  void setAppIDAttr(::circt::esi::AppIDAttr attr) {
    getProperties().appID = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static RequestConnectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static RequestConnectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static RequestConnectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static RequestConnectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RequestConnectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RequestConnectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RequestConnectionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RequestConnectionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::RequestConnectionOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::RequestConnectionOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceDeclPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceDeclPortOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::mlir::StringAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInnerSym(const ::mlir::StringAttr &propValue) {
      this->inner_sym = propValue;
    }
    using toClientTypeTy = ::mlir::TypeAttr;
    toClientTypeTy toClientType;

    auto getToClientType() const {
      auto &propStorage = this->toClientType;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setToClientType(const ::mlir::TypeAttr &propValue) {
      this->toClientType = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.toClientType == this->toClientType &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceDeclPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.port", odsAttrs.getContext());
  }

  ServiceDeclPortOpGenericAdaptorBase(ServiceDeclPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getInnerSymAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().inner_sym);
    return attr;
  }

  ::llvm::StringRef getInnerSym();
  ::mlir::TypeAttr getToClientTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().toClientType);
    return attr;
  }

  ::circt::esi::ChannelBundleType getToClientType();
};

} // namespace detail
template <typename RangeT>
class ServiceDeclPortOpGenericAdaptor : public detail::ServiceDeclPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceDeclPortOpGenericAdaptorBase;
public:
  ServiceDeclPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceDeclPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceDeclPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceDeclPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceDeclPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceDeclPortOpGenericAdaptor(RangeT values, const ServiceDeclPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceDeclPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceDeclPortOp>>>
  ServiceDeclPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceDeclPortOpAdaptor : public ServiceDeclPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceDeclPortOpGenericAdaptor::ServiceDeclPortOpGenericAdaptor;
  ServiceDeclPortOpAdaptor(ServiceDeclPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceDeclPortOp : public ::mlir::Op<ServiceDeclPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<::circt::esi::CustomServiceDeclOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceDeclPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceDeclPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("toClientType")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getToClientTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getToClientTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getInnerSymAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().inner_sym);
  }

  ::llvm::StringRef getInnerSym();
  ::mlir::TypeAttr getToClientTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().toClientType);
  }

  ::circt::esi::ChannelBundleType getToClientType();
  void setInnerSymAttr(::mlir::StringAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setInnerSym(::llvm::StringRef attrValue);
  void setToClientTypeAttr(::mlir::TypeAttr attr) {
    getProperties().toClientType = attr;
  }

  void setToClientType(::circt::esi::ChannelBundleType attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceDeclPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceDeclPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceDeclPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceDeclPortOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplClientRecordOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceImplClientRecordOpGenericAdaptorBase {
public:
  struct Properties {
    using channelAssignmentsTy = ::mlir::DictionaryAttr;
    channelAssignmentsTy channelAssignments;

    auto getChannelAssignments() const {
      auto &propStorage = this->channelAssignments;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setChannelAssignments(const ::mlir::DictionaryAttr &propValue) {
      this->channelAssignments = propValue;
    }
    using implDetailsTy = ::mlir::DictionaryAttr;
    implDetailsTy implDetails;

    auto getImplDetails() const {
      auto &propStorage = this->implDetails;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setImplDetails(const ::mlir::DictionaryAttr &propValue) {
      this->implDetails = propValue;
    }
    using relAppIDPathTy = ::mlir::ArrayAttr;
    relAppIDPathTy relAppIDPath;

    auto getRelAppIDPath() const {
      auto &propStorage = this->relAppIDPath;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setRelAppIDPath(const ::mlir::ArrayAttr &propValue) {
      this->relAppIDPath = propValue;
    }
    using servicePortTy = ::circt::hw::InnerRefAttr;
    servicePortTy servicePort;

    auto getServicePort() const {
      auto &propStorage = this->servicePort;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setServicePort(const ::circt::hw::InnerRefAttr &propValue) {
      this->servicePort = propValue;
    }
    using typeIDTy = ::mlir::TypeAttr;
    typeIDTy typeID;

    auto getTypeID() const {
      auto &propStorage = this->typeID;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setTypeID(const ::mlir::TypeAttr &propValue) {
      this->typeID = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.channelAssignments == this->channelAssignments &&
        rhs.implDetails == this->implDetails &&
        rhs.relAppIDPath == this->relAppIDPath &&
        rhs.servicePort == this->servicePort &&
        rhs.typeID == this->typeID &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceImplClientRecordOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.impl_conn", odsAttrs.getContext());
  }

  ServiceImplClientRecordOpGenericAdaptorBase(ServiceImplClientRecordOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getRelAppIDPathAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().relAppIDPath);
    return attr;
  }

  ::mlir::ArrayAttr getRelAppIDPath();
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
    return attr;
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::TypeAttr getTypeIDAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().typeID);
    return attr;
  }

  ::circt::esi::ChannelBundleType getTypeID();
  ::mlir::DictionaryAttr getChannelAssignmentsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().channelAssignments);
    return attr;
  }

  ::std::optional< ::mlir::DictionaryAttr > getChannelAssignments();
  ::mlir::DictionaryAttr getImplDetailsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().implDetails);
    return attr;
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplDetails();
};

} // namespace detail
template <typename RangeT>
class ServiceImplClientRecordOpGenericAdaptor : public detail::ServiceImplClientRecordOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceImplClientRecordOpGenericAdaptorBase;
public:
  ServiceImplClientRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceImplClientRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceImplClientRecordOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceImplClientRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceImplClientRecordOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceImplClientRecordOpGenericAdaptor(RangeT values, const ServiceImplClientRecordOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceImplClientRecordOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceImplClientRecordOp>>>
  ServiceImplClientRecordOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceImplClientRecordOpAdaptor : public ServiceImplClientRecordOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceImplClientRecordOpGenericAdaptor::ServiceImplClientRecordOpGenericAdaptor;
  ServiceImplClientRecordOpAdaptor(ServiceImplClientRecordOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceImplClientRecordOp : public ::mlir::Op<ServiceImplClientRecordOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ServiceImplRecordOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::IsManifestData::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceImplClientRecordOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceImplClientRecordOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::IsManifestData::Trait<ServiceImplClientRecordOp>::getSymbolRefAttr;
  using circt::esi::IsManifestData::Trait<ServiceImplClientRecordOp>::getDetails;
  using circt::esi::IsManifestData::Trait<ServiceImplClientRecordOp>::getDetailsAsDict;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("channelAssignments"), ::llvm::StringRef("implDetails"), ::llvm::StringRef("relAppIDPath"), ::llvm::StringRef("servicePort"), ::llvm::StringRef("typeID")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getChannelAssignmentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getChannelAssignmentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getImplDetailsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getImplDetailsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRelAppIDPathAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRelAppIDPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getServicePortAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getServicePortAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getTypeIDAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getTypeIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.impl_conn");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getRelAppIDPathAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().relAppIDPath);
  }

  ::mlir::ArrayAttr getRelAppIDPath();
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::TypeAttr getTypeIDAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().typeID);
  }

  ::circt::esi::ChannelBundleType getTypeID();
  ::mlir::DictionaryAttr getChannelAssignmentsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().channelAssignments);
  }

  ::std::optional< ::mlir::DictionaryAttr > getChannelAssignments();
  ::mlir::DictionaryAttr getImplDetailsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().implDetails);
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplDetails();
  void setRelAppIDPathAttr(::mlir::ArrayAttr attr) {
    getProperties().relAppIDPath = attr;
  }

  void setServicePortAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().servicePort = attr;
  }

  void setTypeIDAttr(::mlir::TypeAttr attr) {
    getProperties().typeID = attr;
  }

  void setTypeID(::circt::esi::ChannelBundleType attrValue);
  void setChannelAssignmentsAttr(::mlir::DictionaryAttr attr) {
    getProperties().channelAssignments = attr;
  }

  void setImplDetailsAttr(::mlir::DictionaryAttr attr) {
    getProperties().implDetails = attr;
  }

  ::mlir::Attribute removeChannelAssignmentsAttr() {
      auto attr = getProperties().channelAssignments;
      getProperties().channelAssignments = {};
      return attr;
  }

  ::mlir::Attribute removeImplDetailsAttr() {
      auto attr = getProperties().implDetails;
      getProperties().implDetails = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplClientRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplClientRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  StringRef getManifestClass();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Get information which needs to appear in the manifest for the host to
  // connect to this client through the parent service.
  void getDetails(SmallVectorImpl<NamedAttribute> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplClientRecordOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplClientRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplRecordOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceImplRecordOpGenericAdaptorBase {
public:
  struct Properties {
    using appIDTy = ::circt::esi::AppIDAttr;
    appIDTy appID;

    auto getAppID() const {
      auto &propStorage = this->appID;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setAppID(const ::circt::esi::AppIDAttr &propValue) {
      this->appID = propValue;
    }
    using implDetailsTy = ::mlir::DictionaryAttr;
    implDetailsTy implDetails;

    auto getImplDetails() const {
      auto &propStorage = this->implDetails;
      return ::llvm::cast<::mlir::DictionaryAttr>(propStorage);
    }
    void setImplDetails(const ::mlir::DictionaryAttr &propValue) {
      this->implDetails = propValue;
    }
    using isEngineTy = ::mlir::UnitAttr;
    isEngineTy isEngine;

    auto getIsEngine() const {
      auto &propStorage = this->isEngine;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsEngine(const ::mlir::UnitAttr &propValue) {
      this->isEngine = propValue;
    }
    using serviceTy = ::mlir::FlatSymbolRefAttr;
    serviceTy service;

    auto getService() const {
      auto &propStorage = this->service;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setService(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->service = propValue;
    }
    using serviceImplNameTy = ::mlir::StringAttr;
    serviceImplNameTy serviceImplName;

    auto getServiceImplName() const {
      auto &propStorage = this->serviceImplName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setServiceImplName(const ::mlir::StringAttr &propValue) {
      this->serviceImplName = propValue;
    }
    using stdServiceTy = ::mlir::StringAttr;
    stdServiceTy stdService;

    auto getStdService() const {
      auto &propStorage = this->stdService;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setStdService(const ::mlir::StringAttr &propValue) {
      this->stdService = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.appID == this->appID &&
        rhs.implDetails == this->implDetails &&
        rhs.isEngine == this->isEngine &&
        rhs.service == this->service &&
        rhs.serviceImplName == this->serviceImplName &&
        rhs.stdService == this->stdService &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceImplRecordOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.service_impl", odsAttrs.getContext());
  }

  ServiceImplRecordOpGenericAdaptorBase(ServiceImplRecordOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::AppIDAttr getAppIDAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
    return attr;
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::UnitAttr getIsEngineAttr();
  bool getIsEngine();
  ::mlir::FlatSymbolRefAttr getServiceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getService();
  ::mlir::StringAttr getStdServiceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::StringAttr getServiceImplNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().serviceImplName);
    return attr;
  }

  ::llvm::StringRef getServiceImplName();
  ::mlir::DictionaryAttr getImplDetailsAttr() {
    auto attr = ::llvm::cast<::mlir::DictionaryAttr>(getProperties().implDetails);
    return attr;
  }

  ::mlir::DictionaryAttr getImplDetails();
  ::mlir::Region &getReqDetails() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ServiceImplRecordOpGenericAdaptor : public detail::ServiceImplRecordOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceImplRecordOpGenericAdaptorBase;
public:
  ServiceImplRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceImplRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceImplRecordOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceImplRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceImplRecordOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceImplRecordOpGenericAdaptor(RangeT values, const ServiceImplRecordOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceImplRecordOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceImplRecordOp>>>
  ServiceImplRecordOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceImplRecordOpAdaptor : public ServiceImplRecordOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceImplRecordOpGenericAdaptor::ServiceImplRecordOpGenericAdaptor;
  ServiceImplRecordOpAdaptor(ServiceImplRecordOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceImplRecordOp : public ::mlir::Op<ServiceImplRecordOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::IsManifestData::Trait, circt::esi::HasAppID::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceImplRecordOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceImplRecordOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::IsManifestData::Trait<ServiceImplRecordOp>::getSymbolRefAttr;
  using circt::esi::IsManifestData::Trait<ServiceImplRecordOp>::getDetails;
  using circt::esi::IsManifestData::Trait<ServiceImplRecordOp>::getDetailsAsDict;
  using circt::esi::HasAppID::Trait<ServiceImplRecordOp>::getAppID;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("appID"), ::llvm::StringRef("implDetails"), ::llvm::StringRef("isEngine"), ::llvm::StringRef("service"), ::llvm::StringRef("serviceImplName"), ::llvm::StringRef("stdService")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAppIDAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAppIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getImplDetailsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getImplDetailsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getIsEngineAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getIsEngineAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getServiceAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getServiceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getServiceImplNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getServiceImplNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getStdServiceAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getStdServiceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.service_impl");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Region &getReqDetails() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::AppIDAttr getAppIDAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::UnitAttr getIsEngineAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isEngine);
  }

  bool getIsEngine();
  ::mlir::FlatSymbolRefAttr getServiceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service);
  }

  ::std::optional< ::llvm::StringRef > getService();
  ::mlir::StringAttr getStdServiceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::StringAttr getServiceImplNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().serviceImplName);
  }

  ::llvm::StringRef getServiceImplName();
  ::mlir::DictionaryAttr getImplDetailsAttr() {
    return ::llvm::cast<::mlir::DictionaryAttr>(getProperties().implDetails);
  }

  ::mlir::DictionaryAttr getImplDetails();
  void setAppIDAttr(::circt::esi::AppIDAttr attr) {
    getProperties().appID = attr;
  }

  void setIsEngineAttr(::mlir::UnitAttr attr) {
    getProperties().isEngine = attr;
  }

  void setIsEngine(bool attrValue);
  void setServiceAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().service = attr;
  }

  void setService(::std::optional<::llvm::StringRef> attrValue);
  void setStdServiceAttr(::mlir::StringAttr attr) {
    getProperties().stdService = attr;
  }

  void setStdService(::std::optional<::llvm::StringRef> attrValue);
  void setServiceImplNameAttr(::mlir::StringAttr attr) {
    getProperties().serviceImplName = attr;
  }

  void setServiceImplName(::llvm::StringRef attrValue);
  void setImplDetailsAttr(::mlir::DictionaryAttr attr) {
    getProperties().implDetails = attr;
  }

  ::mlir::Attribute removeServiceAttr() {
      auto attr = getProperties().service;
      getProperties().service = {};
      return attr;
  }

  ::mlir::Attribute removeStdServiceAttr() {
      auto attr = getProperties().stdService;
      getProperties().stdService = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void populateDefaultProperties(::mlir::OperationName opName, Properties &properties);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  StringRef getManifestClass();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Get information which needs to appear in the manifest for the host to
  // connect to this service.
  void getDetails(SmallVectorImpl<NamedAttribute> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplRecordOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplementConnReqOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceImplementConnReqOpGenericAdaptorBase {
public:
  struct Properties {
    using relativeAppIDPathTy = ::mlir::ArrayAttr;
    relativeAppIDPathTy relativeAppIDPath;

    auto getRelativeAppIDPath() const {
      auto &propStorage = this->relativeAppIDPath;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setRelativeAppIDPath(const ::mlir::ArrayAttr &propValue) {
      this->relativeAppIDPath = propValue;
    }
    using servicePortTy = ::circt::hw::InnerRefAttr;
    servicePortTy servicePort;

    auto getServicePort() const {
      auto &propStorage = this->servicePort;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setServicePort(const ::circt::hw::InnerRefAttr &propValue) {
      this->servicePort = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.relativeAppIDPath == this->relativeAppIDPath &&
        rhs.servicePort == this->servicePort &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceImplementConnReqOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.impl_req.req", odsAttrs.getContext());
  }

  ServiceImplementConnReqOpGenericAdaptorBase(ServiceImplementConnReqOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerRefAttr getServicePortAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
    return attr;
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::ArrayAttr getRelativeAppIDPathAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().relativeAppIDPath);
    return attr;
  }

  ::mlir::ArrayAttr getRelativeAppIDPath();
};

} // namespace detail
template <typename RangeT>
class ServiceImplementConnReqOpGenericAdaptor : public detail::ServiceImplementConnReqOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceImplementConnReqOpGenericAdaptorBase;
public:
  ServiceImplementConnReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceImplementConnReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceImplementConnReqOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceImplementConnReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceImplementConnReqOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceImplementConnReqOpGenericAdaptor(RangeT values, const ServiceImplementConnReqOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceImplementConnReqOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceImplementConnReqOp>>>
  ServiceImplementConnReqOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceImplementConnReqOpAdaptor : public ServiceImplementConnReqOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceImplementConnReqOpGenericAdaptor::ServiceImplementConnReqOpGenericAdaptor;
  ServiceImplementConnReqOpAdaptor(ServiceImplementConnReqOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceImplementConnReqOp : public ::mlir::Op<ServiceImplementConnReqOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelBundleType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceImplementConnReqOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceImplementConnReqOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("relativeAppIDPath"), ::llvm::StringRef("servicePort")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRelativeAppIDPathAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRelativeAppIDPathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getServicePortAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getServicePortAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.impl_req.req");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelBundleType> getToClient() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelBundleType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::ArrayAttr getRelativeAppIDPathAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().relativeAppIDPath);
  }

  ::mlir::ArrayAttr getRelativeAppIDPath();
  void setServicePortAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().servicePort = attr;
  }

  void setRelativeAppIDPathAttr(::mlir::ArrayAttr attr) {
    getProperties().relativeAppIDPath = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static ServiceImplementConnReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static ServiceImplementConnReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static ServiceImplementConnReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static ServiceImplementConnReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplementConnReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplementConnReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplementConnReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplementConnReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  ChannelBundleType getBundleType() { return getToClient().getType(); }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplementConnReqOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplementConnReqOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplementReqOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceImplementReqOpGenericAdaptorBase {
public:
  struct Properties {
    using appIDTy = ::circt::esi::AppIDAttr;
    appIDTy appID;

    auto getAppID() const {
      auto &propStorage = this->appID;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setAppID(const ::circt::esi::AppIDAttr &propValue) {
      this->appID = propValue;
    }
    using impl_optsTy = ::mlir::DictionaryAttr;
    impl_optsTy impl_opts;

    auto getImplOpts() const {
      auto &propStorage = this->impl_opts;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setImplOpts(const ::mlir::DictionaryAttr &propValue) {
      this->impl_opts = propValue;
    }
    using impl_typeTy = ::mlir::StringAttr;
    impl_typeTy impl_type;

    auto getImplType() const {
      auto &propStorage = this->impl_type;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setImplType(const ::mlir::StringAttr &propValue) {
      this->impl_type = propValue;
    }
    using service_symbolTy = ::mlir::FlatSymbolRefAttr;
    service_symbolTy service_symbol;

    auto getServiceSymbol() const {
      auto &propStorage = this->service_symbol;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setServiceSymbol(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->service_symbol = propValue;
    }
    using stdServiceTy = ::mlir::StringAttr;
    stdServiceTy stdService;

    auto getStdService() const {
      auto &propStorage = this->stdService;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setStdService(const ::mlir::StringAttr &propValue) {
      this->stdService = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.appID == this->appID &&
        rhs.impl_opts == this->impl_opts &&
        rhs.impl_type == this->impl_type &&
        rhs.service_symbol == this->service_symbol &&
        rhs.stdService == this->stdService &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceImplementReqOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.impl_req", odsAttrs.getContext());
  }

  ServiceImplementReqOpGenericAdaptorBase(ServiceImplementReqOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::AppIDAttr getAppIDAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
    return attr;
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getServiceSymbolAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service_symbol);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getServiceSymbol();
  ::mlir::StringAttr getImplTypeAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().impl_type);
    return attr;
  }

  ::llvm::StringRef getImplType();
  ::mlir::StringAttr getStdServiceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::DictionaryAttr getImplOptsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().impl_opts);
    return attr;
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplOpts();
  ::mlir::Region &getPortReqs() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ServiceImplementReqOpGenericAdaptor : public detail::ServiceImplementReqOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceImplementReqOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ServiceImplementReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceImplementReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceImplementReqOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceImplementReqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceImplementReqOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceImplementReqOpGenericAdaptor(RangeT values, const ServiceImplementReqOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceImplementReqOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceImplementReqOp>>>
  ServiceImplementReqOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceImplementReqOpAdaptor : public ServiceImplementReqOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceImplementReqOpGenericAdaptor::ServiceImplementReqOpGenericAdaptor;
  ServiceImplementReqOpAdaptor(ServiceImplementReqOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceImplementReqOp : public ::mlir::Op<ServiceImplementReqOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::HasAppID::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceImplementReqOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceImplementReqOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::HasAppID::Trait<ServiceImplementReqOp>::getAppID;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("appID"), ::llvm::StringRef("impl_opts"), ::llvm::StringRef("impl_type"), ::llvm::StringRef("service_symbol"), ::llvm::StringRef("stdService")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAppIDAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAppIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getImplOptsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getImplOptsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getImplTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getImplTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getServiceSymbolAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getServiceSymbolAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getStdServiceAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getStdServiceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.impl_req");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getOutputs() {
    return getODSResults(0);
  }

  ::mlir::Region &getPortReqs() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::AppIDAttr getAppIDAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getServiceSymbolAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service_symbol);
  }

  ::std::optional< ::llvm::StringRef > getServiceSymbol();
  ::mlir::StringAttr getImplTypeAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().impl_type);
  }

  ::llvm::StringRef getImplType();
  ::mlir::StringAttr getStdServiceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::DictionaryAttr getImplOptsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().impl_opts);
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplOpts();
  void setAppIDAttr(::circt::esi::AppIDAttr attr) {
    getProperties().appID = attr;
  }

  void setServiceSymbolAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().service_symbol = attr;
  }

  void setServiceSymbol(::std::optional<::llvm::StringRef> attrValue);
  void setImplTypeAttr(::mlir::StringAttr attr) {
    getProperties().impl_type = attr;
  }

  void setImplType(::llvm::StringRef attrValue);
  void setStdServiceAttr(::mlir::StringAttr attr) {
    getProperties().stdService = attr;
  }

  void setStdService(::std::optional<::llvm::StringRef> attrValue);
  void setImplOptsAttr(::mlir::DictionaryAttr attr) {
    getProperties().impl_opts = attr;
  }

  ::mlir::Attribute removeServiceSymbolAttr() {
      auto attr = getProperties().service_symbol;
      getProperties().service_symbol = {};
      return attr;
  }

  ::mlir::Attribute removeStdServiceAttr() {
      auto attr = getProperties().stdService;
      getProperties().stdService = {};
      return attr;
  }

  ::mlir::Attribute removeImplOptsAttr() {
      auto attr = getProperties().impl_opts;
      getProperties().impl_opts = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceImplementReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceImplementReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceImplementReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceImplementReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplementReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceImplementReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplementReqOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceImplementReqOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplementReqOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplementReqOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceInstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceInstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using appIDTy = ::circt::esi::AppIDAttr;
    appIDTy appID;

    auto getAppID() const {
      auto &propStorage = this->appID;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setAppID(const ::circt::esi::AppIDAttr &propValue) {
      this->appID = propValue;
    }
    using impl_optsTy = ::mlir::DictionaryAttr;
    impl_optsTy impl_opts;

    auto getImplOpts() const {
      auto &propStorage = this->impl_opts;
      return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(propStorage);
    }
    void setImplOpts(const ::mlir::DictionaryAttr &propValue) {
      this->impl_opts = propValue;
    }
    using impl_typeTy = ::mlir::StringAttr;
    impl_typeTy impl_type;

    auto getImplType() const {
      auto &propStorage = this->impl_type;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setImplType(const ::mlir::StringAttr &propValue) {
      this->impl_type = propValue;
    }
    using service_symbolTy = ::mlir::FlatSymbolRefAttr;
    service_symbolTy service_symbol;

    auto getServiceSymbol() const {
      auto &propStorage = this->service_symbol;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setServiceSymbol(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->service_symbol = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.appID == this->appID &&
        rhs.impl_opts == this->impl_opts &&
        rhs.impl_type == this->impl_type &&
        rhs.service_symbol == this->service_symbol &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceInstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.instance", odsAttrs.getContext());
  }

  ServiceInstanceOpGenericAdaptorBase(ServiceInstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::AppIDAttr getAppIDAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
    return attr;
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getServiceSymbolAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service_symbol);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getServiceSymbol();
  ::mlir::StringAttr getImplTypeAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().impl_type);
    return attr;
  }

  ::llvm::StringRef getImplType();
  ::mlir::DictionaryAttr getImplOptsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().impl_opts);
    return attr;
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplOpts();
};

} // namespace detail
template <typename RangeT>
class ServiceInstanceOpGenericAdaptor : public detail::ServiceInstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceInstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ServiceInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceInstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceInstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceInstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceInstanceOpGenericAdaptor(RangeT values, const ServiceInstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceInstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceInstanceOp>>>
  ServiceInstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceInstanceOpAdaptor : public ServiceInstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceInstanceOpGenericAdaptor::ServiceInstanceOpGenericAdaptor;
  ServiceInstanceOpAdaptor(ServiceInstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceInstanceOp : public ::mlir::Op<ServiceInstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::HasAppID::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceInstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceInstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::HasAppID::Trait<ServiceInstanceOp>::getAppID;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("appID"), ::llvm::StringRef("impl_opts"), ::llvm::StringRef("impl_type"), ::llvm::StringRef("service_symbol")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAppIDAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAppIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getImplOptsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getImplOptsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getImplTypeAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getImplTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getServiceSymbolAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getServiceSymbolAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.instance");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::AppIDAttr getAppIDAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().appID);
  }

  ::circt::esi::AppIDAttr getAppID();
  ::mlir::FlatSymbolRefAttr getServiceSymbolAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().service_symbol);
  }

  ::std::optional< ::llvm::StringRef > getServiceSymbol();
  ::mlir::StringAttr getImplTypeAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().impl_type);
  }

  ::llvm::StringRef getImplType();
  ::mlir::DictionaryAttr getImplOptsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::DictionaryAttr>(getProperties().impl_opts);
  }

  ::std::optional< ::mlir::DictionaryAttr > getImplOpts();
  void setAppIDAttr(::circt::esi::AppIDAttr attr) {
    getProperties().appID = attr;
  }

  void setServiceSymbolAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().service_symbol = attr;
  }

  void setServiceSymbol(::std::optional<::llvm::StringRef> attrValue);
  void setImplTypeAttr(::mlir::StringAttr attr) {
    getProperties().impl_type = attr;
  }

  void setImplType(::llvm::StringRef attrValue);
  void setImplOptsAttr(::mlir::DictionaryAttr attr) {
    getProperties().impl_opts = attr;
  }

  ::mlir::Attribute removeServiceSymbolAttr() {
      auto attr = getProperties().service_symbol;
      getProperties().service_symbol = {};
      return attr;
  }

  ::mlir::Attribute removeImplOptsAttr() {
      auto attr = getProperties().impl_opts;
      getProperties().impl_opts = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static ServiceInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceInstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceInstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceInstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceInstanceOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceRequestRecordOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ServiceRequestRecordOpGenericAdaptorBase {
public:
  struct Properties {
    using requestorTy = ::circt::esi::AppIDAttr;
    requestorTy requestor;

    auto getRequestor() const {
      auto &propStorage = this->requestor;
      return ::llvm::cast<::circt::esi::AppIDAttr>(propStorage);
    }
    void setRequestor(const ::circt::esi::AppIDAttr &propValue) {
      this->requestor = propValue;
    }
    using servicePortTy = ::circt::hw::InnerRefAttr;
    servicePortTy servicePort;

    auto getServicePort() const {
      auto &propStorage = this->servicePort;
      return ::llvm::cast<::circt::hw::InnerRefAttr>(propStorage);
    }
    void setServicePort(const ::circt::hw::InnerRefAttr &propValue) {
      this->servicePort = propValue;
    }
    using stdServiceTy = ::mlir::StringAttr;
    stdServiceTy stdService;

    auto getStdService() const {
      auto &propStorage = this->stdService;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setStdService(const ::mlir::StringAttr &propValue) {
      this->stdService = propValue;
    }
    using typeIDTy = ::mlir::TypeAttr;
    typeIDTy typeID;

    auto getTypeID() const {
      auto &propStorage = this->typeID;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setTypeID(const ::mlir::TypeAttr &propValue) {
      this->typeID = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.requestor == this->requestor &&
        rhs.servicePort == this->servicePort &&
        rhs.stdService == this->stdService &&
        rhs.typeID == this->typeID &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ServiceRequestRecordOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.req", odsAttrs.getContext());
  }

  ServiceRequestRecordOpGenericAdaptorBase(ServiceRequestRecordOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::esi::AppIDAttr getRequestorAttr() {
    auto attr = ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().requestor);
    return attr;
  }

  ::circt::esi::AppIDAttr getRequestor();
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    auto attr = ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
    return attr;
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::StringAttr getStdServiceAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::TypeAttr getTypeIDAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().typeID);
    return attr;
  }

  ::circt::esi::ChannelBundleType getTypeID();
};

} // namespace detail
template <typename RangeT>
class ServiceRequestRecordOpGenericAdaptor : public detail::ServiceRequestRecordOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ServiceRequestRecordOpGenericAdaptorBase;
public:
  ServiceRequestRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ServiceRequestRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ServiceRequestRecordOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ServiceRequestRecordOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ServiceRequestRecordOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ServiceRequestRecordOpGenericAdaptor(RangeT values, const ServiceRequestRecordOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ServiceRequestRecordOp, typename = std::enable_if_t<std::is_same_v<LateInst, ServiceRequestRecordOp>>>
  ServiceRequestRecordOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ServiceRequestRecordOpAdaptor : public ServiceRequestRecordOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ServiceRequestRecordOpGenericAdaptor::ServiceRequestRecordOpGenericAdaptor;
  ServiceRequestRecordOpAdaptor(ServiceRequestRecordOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ServiceRequestRecordOp : public ::mlir::Op<ServiceRequestRecordOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::IsManifestData::Trait, circt::esi::HasAppID::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ServiceRequestRecordOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ServiceRequestRecordOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::IsManifestData::Trait<ServiceRequestRecordOp>::getSymbolRefAttr;
  using circt::esi::IsManifestData::Trait<ServiceRequestRecordOp>::getDetails;
  using circt::esi::IsManifestData::Trait<ServiceRequestRecordOp>::getDetailsAsDict;
  using circt::esi::HasAppID::Trait<ServiceRequestRecordOp>::getAppID;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("requestor"), ::llvm::StringRef("servicePort"), ::llvm::StringRef("stdService"), ::llvm::StringRef("typeID")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getRequestorAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getRequestorAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getServicePortAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getServicePortAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getStdServiceAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getStdServiceAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getTypeIDAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getTypeIDAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.req");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::circt::esi::AppIDAttr getRequestorAttr() {
    return ::llvm::cast<::circt::esi::AppIDAttr>(getProperties().requestor);
  }

  ::circt::esi::AppIDAttr getRequestor();
  ::circt::hw::InnerRefAttr getServicePortAttr() {
    return ::llvm::cast<::circt::hw::InnerRefAttr>(getProperties().servicePort);
  }

  ::circt::hw::InnerRefAttr getServicePort();
  ::mlir::StringAttr getStdServiceAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().stdService);
  }

  ::std::optional< ::llvm::StringRef > getStdService();
  ::mlir::TypeAttr getTypeIDAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().typeID);
  }

  ::circt::esi::ChannelBundleType getTypeID();
  void setRequestorAttr(::circt::esi::AppIDAttr attr) {
    getProperties().requestor = attr;
  }

  void setServicePortAttr(::circt::hw::InnerRefAttr attr) {
    getProperties().servicePort = attr;
  }

  void setStdServiceAttr(::mlir::StringAttr attr) {
    getProperties().stdService = attr;
  }

  void setStdService(::std::optional<::llvm::StringRef> attrValue);
  void setTypeIDAttr(::mlir::TypeAttr attr) {
    getProperties().typeID = attr;
  }

  void setTypeID(::circt::esi::ChannelBundleType attrValue);
  ::mlir::Attribute removeStdServiceAttr() {
      auto attr = getProperties().stdService;
      getProperties().stdService = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceRequestRecordOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ServiceRequestRecordOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  StringRef getManifestClass();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  AppIDAttr getAppID() {
    return getRequestor();
  }
  // Misc information about the original request which must appear in the
  // manifest.
  void getDetails(SmallVectorImpl<NamedAttribute> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::ServiceRequestRecordOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceRequestRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SnoopTransactionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SnoopTransactionOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SnoopTransactionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.snoop.xact", odsAttrs.getContext());
  }

  SnoopTransactionOpGenericAdaptorBase(SnoopTransactionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class SnoopTransactionOpGenericAdaptor : public detail::SnoopTransactionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SnoopTransactionOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  SnoopTransactionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SnoopTransactionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SnoopTransactionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SnoopTransactionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SnoopTransactionOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SnoopTransactionOpGenericAdaptor(RangeT values, const SnoopTransactionOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SnoopTransactionOp, typename = std::enable_if_t<std::is_same_v<LateInst, SnoopTransactionOp>>>
  SnoopTransactionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SnoopTransactionOpAdaptor : public SnoopTransactionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SnoopTransactionOpGenericAdaptor::SnoopTransactionOpGenericAdaptor;
  SnoopTransactionOpAdaptor(SnoopTransactionOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SnoopTransactionOp : public ::mlir::Op<SnoopTransactionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SnoopTransactionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SnoopTransactionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.snoop.xact");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTransaction() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopTransactionOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopTransactionOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::SnoopTransactionOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SnoopValidReadyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SnoopValidReadyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SnoopValidReadyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.snoop.vr", odsAttrs.getContext());
  }

  SnoopValidReadyOpGenericAdaptorBase(SnoopValidReadyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class SnoopValidReadyOpGenericAdaptor : public detail::SnoopValidReadyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SnoopValidReadyOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  SnoopValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SnoopValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SnoopValidReadyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SnoopValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SnoopValidReadyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SnoopValidReadyOpGenericAdaptor(RangeT values, const SnoopValidReadyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SnoopValidReadyOp, typename = std::enable_if_t<std::is_same_v<LateInst, SnoopValidReadyOp>>>
  SnoopValidReadyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SnoopValidReadyOpAdaptor : public SnoopValidReadyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SnoopValidReadyOpGenericAdaptor::SnoopValidReadyOpGenericAdaptor;
  SnoopValidReadyOpAdaptor(SnoopValidReadyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SnoopValidReadyOp : public ::mlir::Op<SnoopValidReadyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SnoopValidReadyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SnoopValidReadyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.snoop.vr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReady() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SnoopValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::SnoopValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SymbolConstantsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SymbolConstantsOpGenericAdaptorBase {
public:
  struct Properties {
    using constantsTy = ::mlir::DictionaryAttr;
    constantsTy constants;

    auto getConstants() const {
      auto &propStorage = this->constants;
      return ::llvm::cast<::mlir::DictionaryAttr>(propStorage);
    }
    void setConstants(const ::mlir::DictionaryAttr &propValue) {
      this->constants = propValue;
    }
    using symbolRefTy = ::mlir::FlatSymbolRefAttr;
    symbolRefTy symbolRef;

    auto getSymbolRef() const {
      auto &propStorage = this->symbolRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setSymbolRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->symbolRef = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.constants == this->constants &&
        rhs.symbolRef == this->symbolRef &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SymbolConstantsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.constants", odsAttrs.getContext());
  }

  SymbolConstantsOpGenericAdaptorBase(SymbolConstantsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getSymbolRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().symbolRef);
    return attr;
  }

  ::llvm::StringRef getSymbolRef();
  ::mlir::DictionaryAttr getConstantsAttr() {
    auto attr = ::llvm::cast<::mlir::DictionaryAttr>(getProperties().constants);
    return attr;
  }

  ::mlir::DictionaryAttr getConstants();
};

} // namespace detail
template <typename RangeT>
class SymbolConstantsOpGenericAdaptor : public detail::SymbolConstantsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SymbolConstantsOpGenericAdaptorBase;
public:
  SymbolConstantsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SymbolConstantsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SymbolConstantsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SymbolConstantsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SymbolConstantsOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SymbolConstantsOpGenericAdaptor(RangeT values, const SymbolConstantsOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SymbolConstantsOp, typename = std::enable_if_t<std::is_same_v<LateInst, SymbolConstantsOp>>>
  SymbolConstantsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SymbolConstantsOpAdaptor : public SymbolConstantsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SymbolConstantsOpGenericAdaptor::SymbolConstantsOpGenericAdaptor;
  SymbolConstantsOpAdaptor(SymbolConstantsOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SymbolConstantsOp : public ::mlir::Op<SymbolConstantsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::IsManifestData::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SymbolConstantsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SymbolConstantsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::IsManifestData::Trait<SymbolConstantsOp>::getSymbolRefAttr;
  using circt::esi::IsManifestData::Trait<SymbolConstantsOp>::getDetails;
  using circt::esi::IsManifestData::Trait<SymbolConstantsOp>::getDetailsAsDict;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("constants"), ::llvm::StringRef("symbolRef")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConstantsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConstantsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymbolRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymbolRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.constants");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getSymbolRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().symbolRef);
  }

  ::llvm::StringRef getSymbolRef();
  ::mlir::DictionaryAttr getConstantsAttr() {
    return ::llvm::cast<::mlir::DictionaryAttr>(getProperties().constants);
  }

  ::mlir::DictionaryAttr getConstants();
  void setSymbolRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().symbolRef = attr;
  }

  void setSymbolRef(::llvm::StringRef attrValue);
  void setConstantsAttr(::mlir::DictionaryAttr attr) {
    getProperties().constants = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolConstantsOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolConstantsOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  StringRef getManifestClass();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Get information which needs to appear in the manifest for the host to
  // connect to this service.
  void getDetails(SmallVectorImpl<NamedAttribute> &results);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::SymbolConstantsOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::SymbolConstantsOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SymbolMetadataOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SymbolMetadataOpGenericAdaptorBase {
public:
  struct Properties {
    using commitHashTy = ::mlir::StringAttr;
    commitHashTy commitHash;

    auto getCommitHash() const {
      auto &propStorage = this->commitHash;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setCommitHash(const ::mlir::StringAttr &propValue) {
      this->commitHash = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using repoTy = ::mlir::StringAttr;
    repoTy repo;

    auto getRepo() const {
      auto &propStorage = this->repo;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setRepo(const ::mlir::StringAttr &propValue) {
      this->repo = propValue;
    }
    using summaryTy = ::mlir::StringAttr;
    summaryTy summary;

    auto getSummary() const {
      auto &propStorage = this->summary;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSummary(const ::mlir::StringAttr &propValue) {
      this->summary = propValue;
    }
    using symbolRefTy = ::mlir::FlatSymbolRefAttr;
    symbolRefTy symbolRef;

    auto getSymbolRef() const {
      auto &propStorage = this->symbolRef;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setSymbolRef(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->symbolRef = propValue;
    }
    using versionTy = ::mlir::StringAttr;
    versionTy version;

    auto getVersion() const {
      auto &propStorage = this->version;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setVersion(const ::mlir::StringAttr &propValue) {
      this->version = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.commitHash == this->commitHash &&
        rhs.name == this->name &&
        rhs.repo == this->repo &&
        rhs.summary == this->summary &&
        rhs.symbolRef == this->symbolRef &&
        rhs.version == this->version &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SymbolMetadataOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.manifest.sym", odsAttrs.getContext());
  }

  SymbolMetadataOpGenericAdaptorBase(SymbolMetadataOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getSymbolRefAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().symbolRef);
    return attr;
  }

  ::llvm::StringRef getSymbolRef();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::StringAttr getRepoAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().repo);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getRepo();
  ::mlir::StringAttr getCommitHashAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().commitHash);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getCommitHash();
  ::mlir::StringAttr getVersionAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().version);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getVersion();
  ::mlir::StringAttr getSummaryAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().summary);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSummary();
};

} // namespace detail
template <typename RangeT>
class SymbolMetadataOpGenericAdaptor : public detail::SymbolMetadataOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SymbolMetadataOpGenericAdaptorBase;
public:
  SymbolMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SymbolMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SymbolMetadataOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SymbolMetadataOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SymbolMetadataOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SymbolMetadataOpGenericAdaptor(RangeT values, const SymbolMetadataOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SymbolMetadataOp, typename = std::enable_if_t<std::is_same_v<LateInst, SymbolMetadataOp>>>
  SymbolMetadataOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SymbolMetadataOpAdaptor : public SymbolMetadataOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SymbolMetadataOpGenericAdaptor::SymbolMetadataOpGenericAdaptor;
  SymbolMetadataOpAdaptor(SymbolMetadataOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SymbolMetadataOp : public ::mlir::Op<SymbolMetadataOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::esi::IsManifestData::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SymbolMetadataOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SymbolMetadataOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::IsManifestData::Trait<SymbolMetadataOp>::getSymbolRefAttr;
  using circt::esi::IsManifestData::Trait<SymbolMetadataOp>::getDetails;
  using circt::esi::IsManifestData::Trait<SymbolMetadataOp>::getDetailsAsDict;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("commitHash"), ::llvm::StringRef("name"), ::llvm::StringRef("repo"), ::llvm::StringRef("summary"), ::llvm::StringRef("symbolRef"), ::llvm::StringRef("version")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCommitHashAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCommitHashAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRepoAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRepoAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSummaryAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSummaryAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSymbolRefAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymbolRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getVersionAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getVersionAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.manifest.sym");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::FlatSymbolRefAttr getSymbolRefAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().symbolRef);
  }

  ::llvm::StringRef getSymbolRef();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::StringAttr getRepoAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().repo);
  }

  ::std::optional< ::llvm::StringRef > getRepo();
  ::mlir::StringAttr getCommitHashAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().commitHash);
  }

  ::std::optional< ::llvm::StringRef > getCommitHash();
  ::mlir::StringAttr getVersionAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().version);
  }

  ::std::optional< ::llvm::StringRef > getVersion();
  ::mlir::StringAttr getSummaryAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().summary);
  }

  ::std::optional< ::llvm::StringRef > getSummary();
  void setSymbolRefAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().symbolRef = attr;
  }

  void setSymbolRef(::llvm::StringRef attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setRepoAttr(::mlir::StringAttr attr) {
    getProperties().repo = attr;
  }

  void setRepo(::std::optional<::llvm::StringRef> attrValue);
  void setCommitHashAttr(::mlir::StringAttr attr) {
    getProperties().commitHash = attr;
  }

  void setCommitHash(::std::optional<::llvm::StringRef> attrValue);
  void setVersionAttr(::mlir::StringAttr attr) {
    getProperties().version = attr;
  }

  void setVersion(::std::optional<::llvm::StringRef> attrValue);
  void setSummaryAttr(::mlir::StringAttr attr) {
    getProperties().summary = attr;
  }

  void setSummary(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeRepoAttr() {
      auto attr = getProperties().repo;
      getProperties().repo = {};
      return attr;
  }

  ::mlir::Attribute removeCommitHashAttr() {
      auto attr = getProperties().commitHash;
      getProperties().commitHash = {};
      return attr;
  }

  ::mlir::Attribute removeVersionAttr() {
      auto attr = getProperties().version;
      getProperties().version = {};
      return attr;
  }

  ::mlir::Attribute removeSummaryAttr() {
      auto attr = getProperties().summary;
      getProperties().summary = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolMetadataOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolMetadataOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  StringRef getManifestClass();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::SymbolMetadataOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::SymbolMetadataOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::TelemetryServiceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TelemetryServiceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TelemetryServiceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.service.std.telemetry", odsAttrs.getContext());
  }

  TelemetryServiceDeclOpGenericAdaptorBase(TelemetryServiceDeclOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
};

} // namespace detail
template <typename RangeT>
class TelemetryServiceDeclOpGenericAdaptor : public detail::TelemetryServiceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TelemetryServiceDeclOpGenericAdaptorBase;
public:
  TelemetryServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TelemetryServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TelemetryServiceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TelemetryServiceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TelemetryServiceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TelemetryServiceDeclOpGenericAdaptor(RangeT values, const TelemetryServiceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TelemetryServiceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, TelemetryServiceDeclOp>>>
  TelemetryServiceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TelemetryServiceDeclOpAdaptor : public TelemetryServiceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TelemetryServiceDeclOpGenericAdaptor::TelemetryServiceDeclOpGenericAdaptor;
  TelemetryServiceDeclOpAdaptor(TelemetryServiceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TelemetryServiceDeclOp : public ::mlir::Op<TelemetryServiceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<::mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::esi::ServiceDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TelemetryServiceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TelemetryServiceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ServiceDeclOpInterface::Trait<TelemetryServiceDeclOp>::getTypeName;
  using circt::esi::ServiceDeclOpInterface::Trait<TelemetryServiceDeclOp>::getPortInfo;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.service.std.telemetry");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TelemetryServiceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TelemetryServiceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getPortList(llvm::SmallVectorImpl<ServicePortInfo>&ports);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  std::optional<StringRef> getTypeName() { return "esi.service.std.telemetry"; }
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::TelemetryServiceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::detail::TelemetryServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnpackBundleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnpackBundleOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnpackBundleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.bundle.unpack", odsAttrs.getContext());
  }

  UnpackBundleOpGenericAdaptorBase(UnpackBundleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnpackBundleOpGenericAdaptor : public detail::UnpackBundleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnpackBundleOpGenericAdaptorBase;
  static constexpr int odsIndex_bundle = 0;
  static constexpr int odsIndex_fromChannels = 1;
public:
  UnpackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnpackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnpackBundleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnpackBundleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnpackBundleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnpackBundleOpGenericAdaptor(RangeT values, const UnpackBundleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnpackBundleOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnpackBundleOp>>>
  UnpackBundleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getBundle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getFromChannels() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnpackBundleOpAdaptor : public UnpackBundleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnpackBundleOpGenericAdaptor::UnpackBundleOpGenericAdaptor;
  UnpackBundleOpAdaptor(UnpackBundleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnpackBundleOp : public ::mlir::Op<UnpackBundleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnpackBundleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnpackBundleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_bundle = 0;
  static constexpr int odsIndex_fromChannels = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<UnpackBundleOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<UnpackBundleOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<UnpackBundleOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.bundle.unpack");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelBundleType> getBundle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelBundleType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getFromChannels() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getBundleMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getFromChannelsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getToChannels() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value bundle, mlir::ValueRange fromChannels);
  static UnpackBundleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value bundle, mlir::ValueRange fromChannels);
  static UnpackBundleOp create(::mlir::ImplicitLocOpBuilder &builder, Value bundle, mlir::ValueRange fromChannels);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(UnpackBundleOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnpackBundleOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapFIFOOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnwrapFIFOOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnwrapFIFOOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.unwrap.fifo", odsAttrs.getContext());
  }

  UnwrapFIFOOpGenericAdaptorBase(UnwrapFIFOOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnwrapFIFOOpGenericAdaptor : public detail::UnwrapFIFOOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnwrapFIFOOpGenericAdaptorBase;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_rden = 1;
public:
  UnwrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnwrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnwrapFIFOOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnwrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnwrapFIFOOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnwrapFIFOOpGenericAdaptor(RangeT values, const UnwrapFIFOOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnwrapFIFOOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnwrapFIFOOp>>>
  UnwrapFIFOOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getChanInput() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRden() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnwrapFIFOOpAdaptor : public UnwrapFIFOOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnwrapFIFOOpGenericAdaptor::UnwrapFIFOOpGenericAdaptor;
  UnwrapFIFOOpAdaptor(UnwrapFIFOOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnwrapFIFOOp : public ::mlir::Op<UnwrapFIFOOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, circt::esi::ChannelOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnwrapFIFOOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnwrapFIFOOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_rden = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<UnwrapFIFOOp>::refineReturnTypes;
  using circt::esi::ChannelOpInterface::Trait<UnwrapFIFOOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.unwrap.fifo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRden() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getChanInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRdenMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEmpty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput, ::mlir::Value rden);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden);
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(UnwrapFIFOOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static LogicalResult mergeAndErase(UnwrapFIFOOp, WrapFIFOOp, PatternRewriter&);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapFIFOOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapSVInterfaceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnwrapSVInterfaceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnwrapSVInterfaceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.unwrap.iface", odsAttrs.getContext());
  }

  UnwrapSVInterfaceOpGenericAdaptorBase(UnwrapSVInterfaceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnwrapSVInterfaceOpGenericAdaptor : public detail::UnwrapSVInterfaceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnwrapSVInterfaceOpGenericAdaptorBase;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_interfaceSource = 1;
public:
  UnwrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnwrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnwrapSVInterfaceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnwrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnwrapSVInterfaceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnwrapSVInterfaceOpGenericAdaptor(RangeT values, const UnwrapSVInterfaceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnwrapSVInterfaceOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnwrapSVInterfaceOp>>>
  UnwrapSVInterfaceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getChanInput() {
    return (*getODSOperands(0).begin());
  }

  ValueT getInterfaceSource() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnwrapSVInterfaceOpAdaptor : public UnwrapSVInterfaceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnwrapSVInterfaceOpGenericAdaptor::UnwrapSVInterfaceOpGenericAdaptor;
  UnwrapSVInterfaceOpAdaptor(UnwrapSVInterfaceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnwrapSVInterfaceOp : public ::mlir::Op<UnwrapSVInterfaceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, circt::esi::ChannelOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnwrapSVInterfaceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnwrapSVInterfaceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_interfaceSource = 1;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<UnwrapSVInterfaceOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.unwrap.iface");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getInterfaceSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getChanInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getInterfaceSourceMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static UnwrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static UnwrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static UnwrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static UnwrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapSVInterfaceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapValidOnlyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnwrapValidOnlyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnwrapValidOnlyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.unwrap.vo", odsAttrs.getContext());
  }

  UnwrapValidOnlyOpGenericAdaptorBase(UnwrapValidOnlyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnwrapValidOnlyOpGenericAdaptor : public detail::UnwrapValidOnlyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnwrapValidOnlyOpGenericAdaptorBase;
  static constexpr int odsIndex_chanInput = 0;
public:
  UnwrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnwrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnwrapValidOnlyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnwrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnwrapValidOnlyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnwrapValidOnlyOpGenericAdaptor(RangeT values, const UnwrapValidOnlyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnwrapValidOnlyOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnwrapValidOnlyOp>>>
  UnwrapValidOnlyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getChanInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnwrapValidOnlyOpAdaptor : public UnwrapValidOnlyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnwrapValidOnlyOpGenericAdaptor::UnwrapValidOnlyOpGenericAdaptor;
  UnwrapValidOnlyOpAdaptor(UnwrapValidOnlyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnwrapValidOnlyOp : public ::mlir::Op<UnwrapValidOnlyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, circt::esi::ChannelOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnwrapValidOnlyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnwrapValidOnlyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_chanInput = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<UnwrapValidOnlyOp>::refineReturnTypes;
  using circt::esi::ChannelOpInterface::Trait<UnwrapValidOnlyOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.unwrap.vo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getChanInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getRawOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput);
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(UnwrapValidOnlyOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static LogicalResult mergeAndErase(UnwrapValidOnlyOp, WrapValidOnlyOp,
                                     PatternRewriter&);
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapValidOnlyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapValidReadyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnwrapValidReadyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnwrapValidReadyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.unwrap.vr", odsAttrs.getContext());
  }

  UnwrapValidReadyOpGenericAdaptorBase(UnwrapValidReadyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnwrapValidReadyOpGenericAdaptor : public detail::UnwrapValidReadyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnwrapValidReadyOpGenericAdaptorBase;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_ready = 1;
public:
  UnwrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnwrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnwrapValidReadyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnwrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnwrapValidReadyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnwrapValidReadyOpGenericAdaptor(RangeT values, const UnwrapValidReadyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnwrapValidReadyOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnwrapValidReadyOp>>>
  UnwrapValidReadyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getChanInput() {
    return (*getODSOperands(0).begin());
  }

  ValueT getReady() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnwrapValidReadyOpAdaptor : public UnwrapValidReadyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnwrapValidReadyOpGenericAdaptor::UnwrapValidReadyOpGenericAdaptor;
  UnwrapValidReadyOpAdaptor(UnwrapValidReadyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnwrapValidReadyOp : public ::mlir::Op<UnwrapValidReadyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, circt::esi::ChannelOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnwrapValidReadyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnwrapValidReadyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_chanInput = 0;
  static constexpr int odsIndex_ready = 1;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<UnwrapValidReadyOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.unwrap.vr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReady() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getChanInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getReadyMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getRawOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value inChan, mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value inChan, mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value inChan, mlir::Value ready);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready);
  static UnwrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  circt::esi::ChannelType channelType();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapWindow declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnwrapWindowGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UnwrapWindowGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.window.unwrap", odsAttrs.getContext());
  }

  UnwrapWindowGenericAdaptorBase(UnwrapWindow op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class UnwrapWindowGenericAdaptor : public detail::UnwrapWindowGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnwrapWindowGenericAdaptorBase;
  static constexpr int odsIndex_window = 0;
public:
  UnwrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnwrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnwrapWindowGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnwrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnwrapWindowGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnwrapWindowGenericAdaptor(RangeT values, const UnwrapWindowGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnwrapWindow, typename = std::enable_if_t<std::is_same_v<LateInst, UnwrapWindow>>>
  UnwrapWindowGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getWindow() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnwrapWindowAdaptor : public UnwrapWindowGenericAdaptor<::mlir::ValueRange> {
public:
  using UnwrapWindowGenericAdaptor::UnwrapWindowGenericAdaptor;
  UnwrapWindowAdaptor(UnwrapWindow op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnwrapWindow : public ::mlir::Op<UnwrapWindow, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnwrapWindowAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnwrapWindowGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_window = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<UnwrapWindow>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.window.unwrap");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::WindowType> getWindow() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::WindowType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getWindowMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getFrame() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type frame, ::mlir::Value window);
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type frame, ::mlir::Value window);
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type frame, ::mlir::Value window);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value window);
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value window);
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value window);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value window);
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value window);
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value window);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnwrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapWindow)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapFIFOOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WrapFIFOOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WrapFIFOOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.wrap.fifo", odsAttrs.getContext());
  }

  WrapFIFOOpGenericAdaptorBase(WrapFIFOOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WrapFIFOOpGenericAdaptor : public detail::WrapFIFOOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WrapFIFOOpGenericAdaptorBase;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_empty = 1;
public:
  WrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WrapFIFOOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WrapFIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WrapFIFOOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WrapFIFOOpGenericAdaptor(RangeT values, const WrapFIFOOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WrapFIFOOp, typename = std::enable_if_t<std::is_same_v<LateInst, WrapFIFOOp>>>
  WrapFIFOOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getData() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEmpty() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WrapFIFOOpAdaptor : public WrapFIFOOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WrapFIFOOpGenericAdaptor::WrapFIFOOpGenericAdaptor;
  WrapFIFOOpAdaptor(WrapFIFOOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WrapFIFOOp : public ::mlir::Op<WrapFIFOOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, circt::esi::ChannelOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WrapFIFOOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WrapFIFOOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_data = 0;
  static constexpr int odsIndex_empty = 1;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<WrapFIFOOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.wrap.fifo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEmpty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getEmptyMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRden() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty);
  static WrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty);
  static WrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty);
  static WrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty);
  static WrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapFIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapFIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(WrapFIFOOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WrapFIFOOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapSVInterfaceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WrapSVInterfaceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WrapSVInterfaceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.wrap.iface", odsAttrs.getContext());
  }

  WrapSVInterfaceOpGenericAdaptorBase(WrapSVInterfaceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WrapSVInterfaceOpGenericAdaptor : public detail::WrapSVInterfaceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WrapSVInterfaceOpGenericAdaptorBase;
  static constexpr int odsIndex_interfaceSink = 0;
public:
  WrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WrapSVInterfaceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WrapSVInterfaceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WrapSVInterfaceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WrapSVInterfaceOpGenericAdaptor(RangeT values, const WrapSVInterfaceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WrapSVInterfaceOp, typename = std::enable_if_t<std::is_same_v<LateInst, WrapSVInterfaceOp>>>
  WrapSVInterfaceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInterfaceSink() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WrapSVInterfaceOpAdaptor : public WrapSVInterfaceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WrapSVInterfaceOpGenericAdaptor::WrapSVInterfaceOpGenericAdaptor;
  WrapSVInterfaceOpAdaptor(WrapSVInterfaceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WrapSVInterfaceOp : public ::mlir::Op<WrapSVInterfaceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, circt::esi::ChannelOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WrapSVInterfaceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WrapSVInterfaceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_interfaceSink = 0;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<WrapSVInterfaceOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.wrap.iface");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInterfaceSink() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInterfaceSinkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value interfaceSink);
  static WrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value interfaceSink);
  static WrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value interfaceSink);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink);
  static WrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink);
  static WrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapSVInterfaceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapSVInterfaceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WrapSVInterfaceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapValidOnlyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WrapValidOnlyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WrapValidOnlyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.wrap.vo", odsAttrs.getContext());
  }

  WrapValidOnlyOpGenericAdaptorBase(WrapValidOnlyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WrapValidOnlyOpGenericAdaptor : public detail::WrapValidOnlyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WrapValidOnlyOpGenericAdaptorBase;
  static constexpr int odsIndex_rawInput = 0;
  static constexpr int odsIndex_valid = 1;
public:
  WrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WrapValidOnlyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WrapValidOnlyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WrapValidOnlyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WrapValidOnlyOpGenericAdaptor(RangeT values, const WrapValidOnlyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WrapValidOnlyOp, typename = std::enable_if_t<std::is_same_v<LateInst, WrapValidOnlyOp>>>
  WrapValidOnlyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRawInput() {
    return (*getODSOperands(0).begin());
  }

  ValueT getValid() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WrapValidOnlyOpAdaptor : public WrapValidOnlyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WrapValidOnlyOpGenericAdaptor::WrapValidOnlyOpGenericAdaptor;
  WrapValidOnlyOpAdaptor(WrapValidOnlyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WrapValidOnlyOp : public ::mlir::Op<WrapValidOnlyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::ChannelType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait, circt::esi::ChannelOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WrapValidOnlyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WrapValidOnlyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rawInput = 0;
  static constexpr int odsIndex_valid = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<WrapValidOnlyOp>::refineReturnTypes;
  using circt::esi::ChannelOpInterface::Trait<WrapValidOnlyOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.wrap.vo");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getRawInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRawInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValidMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rawInput, ::mlir::Value valid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidOnlyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidOnlyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(WrapValidOnlyOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  circt::esi::ChannelType channelType();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WrapValidOnlyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapValidReadyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WrapValidReadyOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WrapValidReadyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.wrap.vr", odsAttrs.getContext());
  }

  WrapValidReadyOpGenericAdaptorBase(WrapValidReadyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WrapValidReadyOpGenericAdaptor : public detail::WrapValidReadyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WrapValidReadyOpGenericAdaptorBase;
  static constexpr int odsIndex_rawInput = 0;
  static constexpr int odsIndex_valid = 1;
public:
  WrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WrapValidReadyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WrapValidReadyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WrapValidReadyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WrapValidReadyOpGenericAdaptor(RangeT values, const WrapValidReadyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WrapValidReadyOp, typename = std::enable_if_t<std::is_same_v<LateInst, WrapValidReadyOp>>>
  WrapValidReadyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getRawInput() {
    return (*getODSOperands(0).begin());
  }

  ValueT getValid() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WrapValidReadyOpAdaptor : public WrapValidReadyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WrapValidReadyOpGenericAdaptor::WrapValidReadyOpGenericAdaptor;
  WrapValidReadyOpAdaptor(WrapValidReadyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WrapValidReadyOp : public ::mlir::Op<WrapValidReadyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, circt::esi::ChannelOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WrapValidReadyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WrapValidReadyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_rawInput = 0;
  static constexpr int odsIndex_valid = 1;
  using Properties = FoldAdaptor::Properties;
  using circt::esi::ChannelOpInterface::Trait<WrapValidReadyOp>::innerType;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.wrap.vr");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getRawInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getValid() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getRawInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValidMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::ChannelType> getChanOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::ChannelType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReady() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value data, mlir::Value valid);
  static WrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value data, mlir::Value valid);
  static WrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value data, mlir::Value valid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static WrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidReadyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapValidReadyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(WrapValidReadyOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  circt::esi::ChannelType channelType();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WrapValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapWindow declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WrapWindowGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WrapWindowGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("esi.window.wrap", odsAttrs.getContext());
  }

  WrapWindowGenericAdaptorBase(WrapWindow op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class WrapWindowGenericAdaptor : public detail::WrapWindowGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WrapWindowGenericAdaptorBase;
  static constexpr int odsIndex_frame = 0;
public:
  WrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WrapWindowGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WrapWindowGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WrapWindowGenericAdaptor(values, attrs, Properties{}, {}) {}

  WrapWindowGenericAdaptor(RangeT values, const WrapWindowGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WrapWindow, typename = std::enable_if_t<std::is_same_v<LateInst, WrapWindow>>>
  WrapWindowGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFrame() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WrapWindowAdaptor : public WrapWindowGenericAdaptor<::mlir::ValueRange> {
public:
  using WrapWindowGenericAdaptor::WrapWindowGenericAdaptor;
  WrapWindowAdaptor(WrapWindow op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WrapWindow : public ::mlir::Op<WrapWindow, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::esi::WindowType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WrapWindowAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WrapWindowGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_frame = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("esi.window.wrap");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getFrame() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFrameMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::esi::WindowType> getWindow() {
    return ::llvm::cast<::mlir::TypedValue<::circt::esi::WindowType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type window, ::mlir::Value frame);
  static WrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type window, ::mlir::Value frame);
  static WrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type window, ::mlir::Value frame);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value frame);
  static WrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value frame);
  static WrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value frame);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapWindow create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WrapWindow create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(WrapWindow op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::esi
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::esi::WrapWindow)


#endif // GET_OP_CLASSES

