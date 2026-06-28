/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::emit {

class Emittable;

} // namespace circt::emit
namespace circt::emit {

namespace detail {
struct EmittableInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::emit::Emittable;
    Model() : Concept{} {}

  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::emit::Emittable;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct EmittableTrait;

} // namespace detail
class Emittable : public ::mlir::OpInterface<Emittable, detail::EmittableInterfaceTraits> {
public:
  using ::mlir::OpInterface<Emittable, detail::EmittableInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::EmittableTrait<ConcreteOp> {};
};

} // namespace circt::emit
namespace circt::emit::detail {

  template <typename ConcreteOp>
  struct EmittableTrait : public ::mlir::OpInterface<Emittable, detail::EmittableInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::emit::detail
namespace circt::emit {


} // namespace circt::emit
