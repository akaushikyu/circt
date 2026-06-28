/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// "Returns the channel type of this operation."
circt::esi::ChannelType circt::esi::ChannelOpInterface::channelType() {
      return getImpl()->channelType(getImpl(), getOperation());
  }

/// "Returns the inner type of this channel. This will be the type of the
///            data value of the channel, if the channel carries data semantics. Else,
///            return NoneType."
mlir::Type circt::esi::ChannelOpInterface::innerType() {
      return getImpl()->innerType(getImpl(), getOperation());
  }

/// Returns the AppID of this operation.
::circt::esi::AppIDAttr circt::esi::HasAppID::getAppID() {
      return getImpl()->getAppID(getImpl(), getOperation());
  }

/// Get the class name for this op.
StringRef circt::esi::IsManifestData::getManifestClass() {
      return getImpl()->getManifestClass(getImpl(), getOperation());
  }

/// Get the symbol to which this manifest data is referring, if any.
FlatSymbolRefAttr circt::esi::IsManifestData::getSymbolRefAttr() {
      return getImpl()->getSymbolRefAttr(getImpl(), getOperation());
  }

/// Populate results with the manifest data.
void circt::esi::IsManifestData::getDetails(SmallVectorImpl<NamedAttribute>& results) {
      return getImpl()->getDetails(getImpl(), getOperation(), results);
  }

/// Get the manifest data from this op as an attribute.
DictionaryAttr circt::esi::IsManifestData::getDetailsAsDict() {
      return getImpl()->getDetailsAsDict(getImpl(), getOperation());
  }

/// Returns the list of interface ports for this service interface.
void circt::esi::ServiceDeclOpInterface::getPortList(llvm::SmallVectorImpl<ServicePortInfo>& ports) {
      return getImpl()->getPortList(getImpl(), getOperation(), ports);
  }

/// Return a well-known name for this service type.
std::optional<StringRef> circt::esi::ServiceDeclOpInterface::getTypeName() {
      return getImpl()->getTypeName(getImpl(), getOperation());
  }

/// Get info on a particular port.
FailureOr<ServicePortInfo> circt::esi::ServiceDeclOpInterface::getPortInfo(StringAttr portName) {
      return getImpl()->getPortInfo(getImpl(), getOperation(), portName);
  }
