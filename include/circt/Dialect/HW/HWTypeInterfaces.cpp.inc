/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Return the hardware bit width of the type. Does not reflect any encoding,
/// padding, or storage scheme, just the bit (and wire width) of a
/// statically-sized type. Reflects the number of wires needed to transmit a
/// value of this type. Returns std::nullopt if the type's bit width cannot
/// be statically computed.
std::optional<int64_t> circt::hw::BitWidthTypeInterface::getBitWidth() const {
      return getImpl()->getBitWidth(getImpl(), *this);
  }

/// Get the maximum field ID for this type
uint64_t circt::hw::FieldIDTypeInterface::getMaxFieldID() const {
      return getImpl()->getMaxFieldID(getImpl(), *this);
  }

/// Get the sub-type of a type for a field ID, and the subfield's ID. Strip
/// off a single layer of this type and return the sub-type and a field ID
/// targeting the same field, but rebased on the sub-type.
/// 
/// The resultant type *may* not be a FieldIDTypeInterface if the resulting 
/// fieldID is zero.  This means that leaf types may be ground without 
/// implementing an interface.  An empty aggregate will also appear as a 
/// zero.
std::pair<::mlir::Type, uint64_t> circt::hw::FieldIDTypeInterface::getSubTypeByFieldID(uint64_t fieldID) const {
      return getImpl()->getSubTypeByFieldID(getImpl(), *this, fieldID);
  }

/// Returns the effective field id when treating the index field as the
/// root of the type.  Essentially maps a fieldID to a fieldID after a
/// subfield op. Returns the new id and whether the id is in the given
/// child.
std::pair<uint64_t, bool> circt::hw::FieldIDTypeInterface::projectToChildFieldID(uint64_t fieldID, uint64_t index) const {
      return getImpl()->projectToChildFieldID(getImpl(), *this, fieldID, index);
  }

/// Returns the index (e.g. struct or vector element) for a given FieldID.
/// This returns the containing index in the case that the fieldID points to a
/// child field of a field.
uint64_t circt::hw::FieldIDTypeInterface::getIndexForFieldID(uint64_t fieldID) const {
      return getImpl()->getIndexForFieldID(getImpl(), *this, fieldID);
  }

/// Return the fieldID of a given index (e.g. struct or vector element).
/// Field IDs start at 1, and are assigned
/// to each field in a recursive depth-first walk of all
/// elements. A field ID of 0 is used to reference the type itself.
uint64_t circt::hw::FieldIDTypeInterface::getFieldID(uint64_t index) const {
      return getImpl()->getFieldID(getImpl(), *this, index);
  }

/// Find the index of the element that contains the given fieldID.
/// As well, rebase the fieldID to the element.
std::pair<uint64_t, uint64_t> circt::hw::FieldIDTypeInterface::getIndexAndSubfieldID(uint64_t fieldID) const {
      return getImpl()->getIndexAndSubfieldID(getImpl(), *this, fieldID);
  }
