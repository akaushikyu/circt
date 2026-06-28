/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::systemc {

/// a SystemC sc_logic type
/// Represents a single bit with with a value corresponding to one of the four
/// logic states '0', '1', 'Z', and 'X' in SystemC as described in
/// IEEE 1666-2011 §7.9.2.
/// A value of this type can be created using the 'emitc.constant' operation
/// with a string attribute containing "0", "1", "X", "Z", "x", or "z" or an
/// i1 attribute representing "true" or "false". Any other value will be
/// interpreted as 'X' (unknown state).
class LogicType;
/// a SystemC sc_in<T> type
/// Represents the specialized SystemC port class sc_in<T> as described in
/// IEEE 1666-2011 §6.8.
class InputType;
/// a SystemC sc_inout<T> type
/// Represents the specialized SystemC port class sc_inout<T> as described in
/// IEEE 1666-2011 §6.10.
class InOutType;
/// a SystemC sc_out<T> type
/// Represents the specialized SystemC port class sc_out<T> as described in
/// IEEE 1666-2011 §6.12.
class OutputType;
/// a SystemC sc_signal<T> type
/// Represents the predefined primitive channel sc_signal<T> as described in
/// IEEE 1666-2011 §6.4.
class SignalType;
/// a SystemC module type
/// Represents a SystemC module instantiation. Example:
/// `!systemc.module<moduleName(portName1: type1, portName2: type2)>`
class ModuleType;
class LogicType : public ::mlir::Type::TypeBase<LogicType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "systemc.logic";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"logic"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};
namespace detail {

struct InputTypeStorage;

} // namespace detail
class InputType : public ::mlir::Type::TypeBase<InputType, ::mlir::Type, detail::InputTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "systemc.in";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static InputType get(::mlir::MLIRContext *context, ::mlir::Type baseType);
  static InputType get(::mlir::Type baseType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"in"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getBaseType() const;
};
namespace detail {

struct InOutTypeStorage;

} // namespace detail
class InOutType : public ::mlir::Type::TypeBase<InOutType, ::mlir::Type, detail::InOutTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "systemc.inout";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static InOutType get(::mlir::MLIRContext *context, ::mlir::Type baseType);
  static InOutType get(::mlir::Type baseType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"inout"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getBaseType() const;
};
namespace detail {

struct OutputTypeStorage;

} // namespace detail
class OutputType : public ::mlir::Type::TypeBase<OutputType, ::mlir::Type, detail::OutputTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "systemc.out";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static OutputType get(::mlir::MLIRContext *context, ::mlir::Type baseType);
  static OutputType get(::mlir::Type baseType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"out"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getBaseType() const;
};
namespace detail {

struct SignalTypeStorage;

} // namespace detail
class SignalType : public ::mlir::Type::TypeBase<SignalType, ::mlir::Type, detail::SignalTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "systemc.signal";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static SignalType get(::mlir::MLIRContext *context, ::mlir::Type baseType);
  static SignalType get(::mlir::Type baseType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"signal"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getBaseType() const;
};
namespace detail {

struct ModuleTypeStorage;

} // namespace detail
class ModuleType : public ::mlir::Type::TypeBase<ModuleType, ::mlir::Type, detail::ModuleTypeStorage> {
public:
  using Base::Base;
  using PortInfo = ::circt::systemc::detail::PortInfo;
  static constexpr ::llvm::StringLiteral name = "systemc.module";
  static constexpr ::llvm::StringLiteral dialectName = "systemc";
  static ModuleType get(::mlir::MLIRContext *context, mlir::StringAttr moduleName, ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> ports);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"module"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::StringAttr getModuleName() const;
  ::llvm::ArrayRef<::circt::systemc::ModuleType::PortInfo> getPorts() const;
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::LogicType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::InputType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::InOutType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::OutputType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SignalType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::ModuleType)

#endif // GET_TYPEDEF_CLASSES

