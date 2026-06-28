/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

/// Common methods for types which can be indexed by a FieldID.
/// FieldID is a depth-first numbering of the elements of a type.  For example:
/// ```
/// struct a  /* 0 */ {
///   int b; /* 1 */
///   struct c /* 2 */ {
///     int d; /* 3 */
///   }
/// }
/// 
/// int e; /* 0 */
/// ```
class FieldIDTypeInterface;

} // namespace circt::hw
namespace circt::hw {

/// Type interface for types that have a statically computable bit width.
/// This allows types from different dialects to participate in bit width
/// calculations, enabling operations like hw.bitcast to work with non-HW types.
class BitWidthTypeInterface;

} // namespace circt::hw
namespace circt::hw {

/// Common methods for types which can be indexed by a FieldID.
/// FieldID is a depth-first numbering of the elements of a type.  For example:
/// ```
/// struct a  /* 0 */ {
///   int b; /* 1 */
///   struct c /* 2 */ {
///     int d; /* 3 */
///   }
/// }
/// 
/// int e; /* 0 */
/// ```
namespace detail {
struct FieldIDTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    uint64_t (*getMaxFieldID)(const Concept *impl, ::mlir::Type );
    std::pair<::mlir::Type, uint64_t> (*getSubTypeByFieldID)(const Concept *impl, ::mlir::Type , uint64_t);
    std::pair<uint64_t, bool> (*projectToChildFieldID)(const Concept *impl, ::mlir::Type , uint64_t, uint64_t);
    uint64_t (*getIndexForFieldID)(const Concept *impl, ::mlir::Type , uint64_t);
    uint64_t (*getFieldID)(const Concept *impl, ::mlir::Type , uint64_t);
    std::pair<uint64_t, uint64_t> (*getIndexAndSubfieldID)(const Concept *impl, ::mlir::Type , uint64_t);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = circt::hw::FieldIDTypeInterface;
    Model() : Concept{getMaxFieldID, getSubTypeByFieldID, projectToChildFieldID, getIndexForFieldID, getFieldID, getIndexAndSubfieldID} {}

    static inline uint64_t getMaxFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
    static inline std::pair<uint64_t, bool> projectToChildFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID, uint64_t index);
    static inline uint64_t getIndexForFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
    static inline uint64_t getFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t index);
    static inline std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::FieldIDTypeInterface;
    FallbackModel() : Concept{getMaxFieldID, getSubTypeByFieldID, projectToChildFieldID, getIndexForFieldID, getFieldID, getIndexAndSubfieldID} {}

    static inline uint64_t getMaxFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val);
    static inline std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
    static inline std::pair<uint64_t, bool> projectToChildFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID, uint64_t index);
    static inline uint64_t getIndexForFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
    static inline uint64_t getFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t index);
    static inline std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct FieldIDTypeInterfaceTrait;

} // namespace detail
class FieldIDTypeInterface : public ::mlir::TypeInterface<FieldIDTypeInterface, detail::FieldIDTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<FieldIDTypeInterface, detail::FieldIDTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::FieldIDTypeInterfaceTrait<ConcreteType> {};

  /// Get the maximum field ID for this type
  uint64_t getMaxFieldID() const;

  /// Get the sub-type of a type for a field ID, and the subfield's ID. Strip
  /// off a single layer of this type and return the sub-type and a field ID
  /// targeting the same field, but rebased on the sub-type.
  /// 
  /// The resultant type *may* not be a FieldIDTypeInterface if the resulting 
  /// fieldID is zero.  This means that leaf types may be ground without 
  /// implementing an interface.  An empty aggregate will also appear as a 
  /// zero.
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;

  /// Returns the effective field id when treating the index field as the
  /// root of the type.  Essentially maps a fieldID to a fieldID after a
  /// subfield op. Returns the new id and whether the id is in the given
  /// child.
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;

  /// Returns the index (e.g. struct or vector element) for a given FieldID.
  /// This returns the containing index in the case that the fieldID points to a
  /// child field of a field.
  uint64_t getIndexForFieldID(uint64_t fieldID) const;

  /// Return the fieldID of a given index (e.g. struct or vector element).
  /// Field IDs start at 1, and are assigned
  /// to each field in a recursive depth-first walk of all
  /// elements. A field ID of 0 is used to reference the type itself.
  uint64_t getFieldID(uint64_t index) const;

  /// Find the index of the element that contains the given fieldID.
  /// As well, rebase the fieldID to the element.
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};

} // namespace circt::hw
namespace circt::hw {

/// Type interface for types that have a statically computable bit width.
/// This allows types from different dialects to participate in bit width
/// calculations, enabling operations like hw.bitcast to work with non-HW types.
namespace detail {
struct BitWidthTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    std::optional<int64_t> (*getBitWidth)(const Concept *impl, ::mlir::Type );
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = circt::hw::BitWidthTypeInterface;
    Model() : Concept{getBitWidth} {}

    static inline std::optional<int64_t> getBitWidth(const Concept *impl, ::mlir::Type tablegen_opaque_val);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::hw::BitWidthTypeInterface;
    FallbackModel() : Concept{getBitWidth} {}

    static inline std::optional<int64_t> getBitWidth(const Concept *impl, ::mlir::Type tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct BitWidthTypeInterfaceTrait;

} // namespace detail
class BitWidthTypeInterface : public ::mlir::TypeInterface<BitWidthTypeInterface, detail::BitWidthTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<BitWidthTypeInterface, detail::BitWidthTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::BitWidthTypeInterfaceTrait<ConcreteType> {};

  /// Return the hardware bit width of the type. Does not reflect any encoding,
  /// padding, or storage scheme, just the bit (and wire width) of a
  /// statically-sized type. Reflects the number of wires needed to transmit a
  /// value of this type. Returns std::nullopt if the type's bit width cannot
  /// be statically computed.
  std::optional<int64_t> getBitWidth() const;
};

} // namespace circt::hw
namespace circt::hw::detail {

  template <typename ConcreteType>
  struct FieldIDTypeInterfaceTrait : public ::mlir::TypeInterface<FieldIDTypeInterface, detail::FieldIDTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace circt::hw::detail
namespace circt::hw::detail {

  template <typename ConcreteType>
  struct BitWidthTypeInterfaceTrait : public ::mlir::TypeInterface<BitWidthTypeInterface, detail::BitWidthTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace circt::hw::detail
namespace circt::hw {

template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::getMaxFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getMaxFieldID();
}
template<typename ConcreteType>
std::pair<::mlir::Type, uint64_t> detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::getSubTypeByFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getSubTypeByFieldID(fieldID);
}
template<typename ConcreteType>
std::pair<uint64_t, bool> detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::projectToChildFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID, uint64_t index) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).projectToChildFieldID(fieldID, index);
}
template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::getIndexForFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getIndexForFieldID(fieldID);
}
template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::getFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t index) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getFieldID(index);
}
template<typename ConcreteType>
std::pair<uint64_t, uint64_t> detail::FieldIDTypeInterfaceInterfaceTraits::Model<ConcreteType>::getIndexAndSubfieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getIndexAndSubfieldID(fieldID);
}
template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getMaxFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getMaxFieldID(tablegen_opaque_val);
}
template<typename ConcreteType>
std::pair<::mlir::Type, uint64_t> detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getSubTypeByFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return static_cast<const ConcreteType *>(impl)->getSubTypeByFieldID(tablegen_opaque_val, fieldID);
}
template<typename ConcreteType>
std::pair<uint64_t, bool> detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::projectToChildFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID, uint64_t index) {
  return static_cast<const ConcreteType *>(impl)->projectToChildFieldID(tablegen_opaque_val, fieldID, index);
}
template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getIndexForFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return static_cast<const ConcreteType *>(impl)->getIndexForFieldID(tablegen_opaque_val, fieldID);
}
template<typename ConcreteType>
uint64_t detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getFieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t index) {
  return static_cast<const ConcreteType *>(impl)->getFieldID(tablegen_opaque_val, index);
}
template<typename ConcreteType>
std::pair<uint64_t, uint64_t> detail::FieldIDTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getIndexAndSubfieldID(const Concept *impl, ::mlir::Type tablegen_opaque_val, uint64_t fieldID) {
  return static_cast<const ConcreteType *>(impl)->getIndexAndSubfieldID(tablegen_opaque_val, fieldID);
}

} // namespace circt::hw
namespace circt::hw {

template<typename ConcreteType>
std::optional<int64_t> detail::BitWidthTypeInterfaceInterfaceTraits::Model<ConcreteType>::getBitWidth(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getBitWidth();
}
template<typename ConcreteType>
std::optional<int64_t> detail::BitWidthTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getBitWidth(const Concept *impl, ::mlir::Type tablegen_opaque_val) {
  return static_cast<const ConcreteType *>(impl)->getBitWidth(tablegen_opaque_val);
}

} // namespace circt::hw
